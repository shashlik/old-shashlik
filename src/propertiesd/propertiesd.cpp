/* This file is part of Shashlik

   Copyright (C) 2014 Aaron Seigo <aseigo@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
*/

#include "propertiesd.h"

#include <KPluginFactory>

#include <QFile>
#include <QLocalSocket>
#include <QDebug>

K_PLUGIN_FACTORY_WITH_JSON(PropertiesdFactory, "kded_shashlik_propertiesd.json", registerPlugin<Propertiesd>();)

// key/value size maximums
#include "sys/system_properties.h"

// for the name of the pipe the server should listen on
#include "cutils/properties.h"

Propertiesd::Propertiesd(QObject *parent, const QVariantList &)
    : KDEDModule(parent),
      m_properties(QString::fromLatin1("org.kde.shashlik"), QString::fromLatin1("propertiesd"))
{

    qDebug()  << "I AM THE PRPOPERTIES DAEMON, HEAR ME ROAR!!!!";

    if (QFile::exists(QString::fromLatin1(SYSTEM_PROPERTY_PIPE_NAME))) {
        QFile::remove(QString::fromLatin1(SYSTEM_PROPERTY_PIPE_NAME));
    }

    m_server.listen(QString::fromLatin1(SYSTEM_PROPERTY_PIPE_NAME));
    connect(&m_server, &QLocalServer::newConnection,
            this, &Propertiesd::newConnection);

    initProperties();
}

Propertiesd::~Propertiesd()
{
    m_server.close();
}

void Propertiesd::newConnection()
{
    while (QLocalSocket *socket = m_server.nextPendingConnection()) {
        // delete the socket when it is done.
        connect(socket, &QLocalSocket::disconnected,
                socket, &QObject::deleteLater);

        // and now listen to it
        connect(socket, &QIODevice::readyRead,
                this, &Propertiesd::readRequest);
    }
}

void Propertiesd::readRequest()
{
    QIODevice *dev = qobject_cast<QIODevice *>(sender());
    if (!dev) {
        qDebug() << "Sender was not a QIODevice!";
        return;
    }

    QByteArray data = dev->read(PROP_NAME_MAX + PROP_VALUE_MAX + 1);
    if (data.size() < 2) {
        qDebug() << "data is too small!" << data;
        return;
    }

    if (data[0] == (char)kSystemPropertyUnknown) {
        qDebug() << "OK, so something is wrong, and the property command is unknown...";
    } else if (data[0] == (char)kSystemPropertyGet) {
        // Read a property
        const QString key = QString::fromLatin1(data.right(data.size() - 1));
        QByteArray rv = readProperty(key).toLatin1();
        qDebug() << "Read  property:" << key << "as far as we know with the value" << rv;
        char resp[PROP_VALUE_MAX + 1];
        if(rv.size() < 1)
            resp[0] = 0;
        else
            resp[0] = 1;
        strcpy(&resp[1], rv.constData());
        resp[rv.size() + 2] = '\0';
        dev->write(resp, PROP_VALUE_MAX + 1);
    } else if (data[0] == (char)kSystemPropertySet) {
        // Write a property
        // the offsets used can be found in android-core/libcutils/properties.c
        // let's hope they never change
        const QString key = QString::fromLatin1(data.mid(1, PROPERTY_KEY_MAX));
        const QString value = QString::fromLatin1(data.mid(PROPERTY_KEY_MAX + 1));
        qDebug() << "Writing property" << key << "and setting it to value" << value;
        writeProperty(key, value);
        char rv[1];
        rv[0] = 1;
        dev->write(rv);
    } else if (data[0] == (char)kSystemPropertyList) {
        qDebug() << "List properties...?!";
        // List a property .. doesn't actually do anything
        // since this doesn't seem to be actually USED in the
        // Android code base?
        // the property_list function is actually a does-nothing stub in libcutils!
    }
    else {
        qDebug() << "OK, so something is terribly wrong here... Command is not only unknown but out of bounds. Command value is" << (int)data[0] << "and the rest is" << data;
        dev->write("00");
    }
}

void Propertiesd::writeProperty(const QString &key, const QString &value)
{
    if (key.isEmpty()) {
        return;
    }

    QStringList groups = key.split(QChar::fromLatin1('.'), QString::SkipEmptyParts);
    for (int i = 0; i < groups.size() - 1; ++i) {
        m_properties.beginGroup(groups.at(i));
    }

    QString writeValue = value;
    writeValue.truncate(PROP_VALUE_MAX);
    m_properties.setValue(groups.last(), value);

    for (int i = 0; i < groups.size() - 1; ++i) {
        m_properties.endGroup();
    }
}

QString Propertiesd::readProperty(const QString &key)
{
    if (key.isEmpty()) {
        return QString();
    }

    QStringList groups = key.split(QChar::fromLatin1('.'), QString::SkipEmptyParts);
    for (int i = 0; i < groups.size() - 1; ++i) {
        m_properties.beginGroup(groups.at(i));
    }

    const QString value = m_properties.value(groups.last(), QString()).toString();

    for (int i = 0; i < groups.size() - 1; ++i) {
        m_properties.endGroup();
    }

    return value;
}

void Propertiesd::initProperties()
{
    if (!m_properties.childKeys().isEmpty()) {
        // we already have values, let's just use those
        return;
    }

    writeProperty(QString::fromLatin1("ro.factorytest"), QString::fromLatin1("0"));
    writeProperty(QString::fromLatin1("ro.build.display.id"), QString::fromLatin1("Shashlik"));
    writeProperty(QString::fromLatin1("ro.build.version.incremental"), QString::fromLatin1("1234567"));
    writeProperty(QString::fromLatin1("ro.build.version.sdk"), QString::fromLatin1("19"));
    writeProperty(QString::fromLatin1("ro.build.version.codename"), QString::fromLatin1("REL"));
    writeProperty(QString::fromLatin1("ro.build.version.release"), QString::fromLatin1("4.4.2"));
    writeProperty(QString::fromLatin1("ro.build.version.date"), QString::fromLatin1("Thu Jun 18 17:49:04 PDT 2015"));
    writeProperty(QString::fromLatin1("ro.build.type"), QString::fromLatin1("eng"));
    writeProperty(QString::fromLatin1("ro.build.tags"), QString::fromLatin1("test-keys"));
    writeProperty(QString::fromLatin1("ro.product.model"), QString::fromLatin1("sdk"));
    writeProperty(QString::fromLatin1("ro.product.name"), QString::fromLatin1("sdk"));

    writeProperty(QString::fromLatin1("ro.build.user"), QString::fromLatin1("generic"));
    writeProperty(QString::fromLatin1("ro.build.host"), QString::fromLatin1("generic"));
    writeProperty(QString::fromLatin1("ro.product.brand"), QString::fromLatin1("generic"));
    writeProperty(QString::fromLatin1("ro.product.manufacturer"), QString::fromLatin1("generic"));
    writeProperty(QString::fromLatin1("ro.product.device"), QString::fromLatin1("generic"));
    writeProperty(QString::fromLatin1("ro.build.product"), QString::fromLatin1("generic"));

    writeProperty(QString::fromLatin1("ro.kernel.qemu"), QString::fromLatin1("0"));
    writeProperty(QString::fromLatin1("ro.kernel.android.checkjni"), QString::fromLatin1("1"));
    writeProperty(QString::fromLatin1("ro.secure"), QString::fromLatin1("0"));
    writeProperty(QString::fromLatin1("ro.debuggable"), QString::fromLatin1("0"));
    writeProperty(QString::fromLatin1("ro.config.low_ram"), QString::fromLatin1("0"));
    writeProperty(QString::fromLatin1("ro.config.headless"), QString::fromLatin1("0"));

    writeProperty(QString::fromLatin1("ro.zygote.disable_gl_preload"), QString::fromLatin1("false"));

    writeProperty(QString::fromLatin1("debug.egl.trace"), QString::fromLatin1("error"));
    writeProperty(QString::fromLatin1("debug.egl.callstack"), QString::fromLatin1("0"));

    writeProperty(QString::fromLatin1("debug.sf.showupdates"), QString::fromLatin1("0"));
    writeProperty(QString::fromLatin1("debug.sf.ddms"), QString::fromLatin1("0"));
    writeProperty(QString::fromLatin1("debug.sf.no_hw_vsync"), QString::fromLatin1("0"));

    writeProperty(QString::fromLatin1("ro.bq.gpu_to_cpu_unsupported"), QString::fromLatin1("0"));
    writeProperty(QString::fromLatin1("ro.hardware.hwcomposer"), QString::fromLatin1("shashlik"));
    writeProperty(QString::fromLatin1("ro.hardware.gralloc"), QString::fromLatin1("shashlik"));
//     writeProperty(QString::fromLatin1("ro.hardware"), QString::fromLatin1("0"));
//     writeProperty(QString::fromLatin1("ro.product.board"), QString::fromLatin1("0"));
//     writeProperty(QString::fromLatin1("ro.board.platform"), QString::fromLatin1("0"));
//     writeProperty(QString::fromLatin1("ro.arch"), QString::fromLatin1("0"));

    writeProperty(QString::fromLatin1("log.redirect-stdio"), QString::fromLatin1("false"));
    writeProperty(QString::fromLatin1("dalvik.vm.checkjni"), QString::fromLatin1("1"));
    writeProperty(QString::fromLatin1("dalvik.vm.execution-mode"), QString::fromLatin1("int:jit"));
    writeProperty(QString::fromLatin1("dalvik.vm.stack-trace-file"), QString::fromLatin1(""));
    writeProperty(QString::fromLatin1("dalvik.vm.check-dex-sum"), QString::fromLatin1("false"));
    writeProperty(QString::fromLatin1("dalvik.vm.enableassertions"), QString::fromLatin1("false"));
    writeProperty(QString::fromLatin1("dalvik.vm.jniopts"), QString::fromLatin1(""));
    writeProperty(QString::fromLatin1("dalvik.vm.heapstartsize"), QString::fromLatin1("8m"));
    writeProperty(QString::fromLatin1("dalvik.vm.heapgrowthlimit"), QString::fromLatin1("192m"));
    writeProperty(QString::fromLatin1("dalvik.vm.heapsize"), QString::fromLatin1("512m"));
    writeProperty(QString::fromLatin1("dalvik.vm.heaptargetutilization"), QString::fromLatin1("0.75"));
    writeProperty(QString::fromLatin1("dalvik.vm.heapminfree"), QString::fromLatin1("512k"));
    writeProperty(QString::fromLatin1("dalvik.vm.heapmaxfree"), QString::fromLatin1("8m"));
    writeProperty(QString::fromLatin1("dalvik.vm.dexopt-flags"), QString::fromLatin1(""));
    writeProperty(QString::fromLatin1("dalvik.vm.lockprof.threshold"), QString::fromLatin1(""));
    writeProperty(QString::fromLatin1("dalvik.vm.extra-opts"), QString::fromLatin1(""));
    writeProperty(QString::fromLatin1("dalvik.vm.jit.codecachesize"), QString::fromLatin1(""));
    writeProperty(QString::fromLatin1("dalvik.vm.jit.op"), QString::fromLatin1(""));
    writeProperty(QString::fromLatin1("dalvik.vm.jit.method"), QString::fromLatin1(""));

    writeProperty(QString::fromLatin1("persist.sys.language"), QString::fromLatin1("en"));
    writeProperty(QString::fromLatin1("persist.sys.country"), QString::fromLatin1("US"));


    writeProperty(QString::fromLatin1("ro.sf.lcd_density"), QString::fromLatin1("200"));

    writeProperty(QString::fromLatin1("system_init.startsensorservice"), QString::fromLatin1("1"));
    writeProperty(QString::fromLatin1("sys.shutdown.requested"), QString::fromLatin1("0"));
    writeProperty(QString::fromLatin1("config.disable_systemui"), QString::fromLatin1("0"));

    writeProperty(QString::fromLatin1("config.disable_storage"), QString::fromLatin1("1"));
    writeProperty(QString::fromLatin1("config.disable_media"), QString::fromLatin1("1"));
    writeProperty(QString::fromLatin1("config.disable_location"), QString::fromLatin1("1"));
    writeProperty(QString::fromLatin1("config.disable_noncore"), QString::fromLatin1("1"));
    writeProperty(QString::fromLatin1("config.disable_network"), QString::fromLatin1("1"));
    writeProperty(QString::fromLatin1("persist.sys.strictmode.disable"), QString::fromLatin1("1"));

//     writeProperty(QString::fromLatin1(""), QString::fromLatin1(""));
}

#include "propertiesd.moc"

