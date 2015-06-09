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

K_PLUGIN_FACTORY(PropertiesdFactory, registerPlugin<Propertiesd>();)

// key/value size maximums
#include "sys/system_properties.h"

// for the name of the pipe the server should listen on
#include "cutils/properties.h"

Propertiesd::Propertiesd(QObject *parent, const QVariantList &)
    : KDEDModule(parent),
      m_properties(QString::fromLatin1("org.kde.shashlik"), QString::fromLatin1("propertiesd"))
{
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
        return;
    }

    QByteArray data = dev->read(PROP_NAME_MAX);
    if (data.size() < 2) {
        return;
    }

    if (data[0] == (char)kSystemPropertyGet) {
        // Read a property
        const QString key = QString::fromLatin1(data.right(data.size() - 1));
        QByteArray rv = readProperty(key).toLatin1();
        if (rv.size() < 1) {
            rv.append((char)0);
        } else {
            rv.prepend((char)1);
        }
        dev->write(rv);
    } else if (data[0] == (char)kSystemPropertySet) {
        // Write a property
        // the offsets used can be found in android-core/libcutils/properties.c
        // let's hope they never change
        const QString key = QString::fromLatin1(data.mid(1, PROPERTY_KEY_MAX));
        const QString value = QString::fromLatin1(data.right(data.size() - 1 - PROPERTY_KEY_MAX));
        writeProperty(key, value);
        char rv[1];
        rv[0] = 1;
        dev->write(rv);
    } else if (data[0] == (char)kSystemPropertyList) {
        // List a property .. doesn't actually do anything
        // since this doesn't seem to be actually USED in the
        // Android code base?
        // the property_list function is actually a does-nothing stub in libcutils!
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

    writeProperty(QString::fromLatin1("ro.build.version.sdk"), QString::fromLatin1("19"));
    writeProperty(QString::fromLatin1("ro.kernel.qemu"), QString::fromLatin1("1"));
    writeProperty(QString::fromLatin1("ro.secure"), QString::fromLatin1("0"));
    writeProperty(QString::fromLatin1("ro.debuggable"), QString::fromLatin1("0"));
}

#include "propertiesd.moc"

