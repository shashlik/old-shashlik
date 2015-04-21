/*
 * This file is part of the Shashlik project
 *
 * Copyright (C) 2015 Dan Leinir Turthra Jensen <admin@leinir.dk>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "Controller.h"

#include <QCoreApplication>
#include <QDebug>
#include <qdir.h>
#include <qmetaobject.h>

class Controller::Private
{
public:
    Private()
        : serviceManager(0)
        , surfaceflinger(0)
        , zygote(0)
    {
        appDir = qApp->applicationDirPath();
        QDir thisAppDir(appDir);
        thisAppDir.cdUp();
        libraryRoot = thisAppDir.canonicalPath();
        thisAppDir.cd("lib64/android");
        androidRootDir = thisAppDir.canonicalPath();
    }

    QProcess* serviceManager;
    QProcess* surfaceflinger;
    QProcess* zygote;

    QString appDir;
    QString libraryRoot;
    QString androidRootDir;

    // Returns a QProcess with the environment set up
    // so as to reflect the correct Androidiness of the
    // installed Shashlik
    QProcess* environment(QObject* parent)
    {
        QProcess* process = new QProcess(parent);
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();

        // TODO make this a little less assumptioney
        // Heuristic: Unless we're told otherwise, the android root is one level up from the
        // installation location, and inside lib64/android. Yup, not entirely sensible, but
        // works for now.

        QStringList path = QStringList() << env.value("PATH") << appDir << "ANDROID_ROOT/sbin" << "ANDROID_ROOT/vendor/bin" << "ANDROID_ROOT/system/sbin" << "ANDROID_ROOT/system/bin" << "ANDROID_ROOT/system/xbin";
        path.replaceInStrings("ANDROID_ROOT", androidRootDir);
        env.insert("PATH", path.join(QLatin1String(":")));

        QStringList ldpath = QStringList() << env.value("LD_LIBRARY_PATH") << "LIBPATH/lib64" << "LIBPATH/lib64/egl" << "ANDROID_ROOT/vendor/lib" << "ANDROID_ROOT/system/lib";
        ldpath.replaceInStrings("LIBPATH", libraryRoot);
        ldpath.replaceInStrings("ANDROID_ROOT", androidRootDir);
        env.insert("LD_LIBRARY_PATH", ldpath.join(QLatin1String(":")));

        QString jarPath = QString("/system/framework").prepend(androidRootDir);
        QStringList bootclasspath = QStringList() << "JARPATH/core.jar" << "JARPATH/conscrypt.jar" << "JARPATH/bouncycastle.jar" << "JARPATH/okhttp.jar" << "JARPATH/ext.jar" << "JARPATH/framework.jar" << "JARPATH/telephony-common.jar" << "JARPATH/voip-common.jar" << "JARPATH/framework2.jar";
        bootclasspath.replaceInStrings("JARPATH", jarPath);
        env.insert("BOOTCLASSPATH", bootclasspath.join(QLatin1String(":")));

        env.insert("ANDROID_ROOT", QString("/system").prepend(androidRootDir));
        env.insert("ANDROID_ASSETS", QString("/system/app").prepend(androidRootDir));
        env.insert("ANDROID_DATA", QString("/data").prepend(androidRootDir));
        env.insert("ANDROID_STORAGE", QString("/storage").prepend(androidRootDir));
        env.insert("ASEC_MOUNTPOINT", QString("/mnt/asec").prepend(androidRootDir));
        env.insert("LOOP_MOUNTPOINT", QString("/mnt/obb").prepend(androidRootDir));
        env.insert("HAL_LIBRARY_PATH1", QString("/lib64/hw").prepend(libraryRoot));

        env.insert("ANDROID_BOOTLOGO", "1");

        // TODO this should probably use some XDG type thing to sniff what this really is...
        env.insert("EXTERNAL_STORAGE", "/mnt");

        process->setProcessEnvironment(env);
        return process;
    }
};

Controller::Controller(QObject* parent)
    : QObject(parent)
    , d(new Private)
{

}

Controller::~Controller()
{
    delete d;
}

void Controller::logSomething()
{
    QProcess* proc = qobject_cast<QProcess*>(sender());
    if(proc) {
        QString output = proc->readAll();
        printf(qPrintable(output));
    }
}

void Controller::processExited(int exitCode, QProcess::ExitStatus exitStatus)
{
    QProcess* proc = qobject_cast<QProcess*>(sender());
    if(proc) {
        qDebug() << "******\n*" << proc->program() << "has exited\n******";
    }
}

void Controller::startZygote()
{
    d->zygote = d->environment(this);
    connect(d->zygote, SIGNAL(readyRead()), this, SLOT(logSomething()));
    connect(d->zygote, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processExited(int,QProcess::ExitStatus)));
    d->zygote->setProcessChannelMode(QProcess::MergedChannels);
    qDebug() << "Attempting to start the Zygote...";
    d->zygote->start(d->androidRootDir + "/system/bin/shashlik_launcher", QStringList() << "-Xzygote" << d->androidRootDir + "/system/bin/" << "--zygote" << "--start-system-server");
    d->zygote->waitForStarted();
    // get process ID now
}

void Controller::startSurfaceflinger()
{
    d->surfaceflinger = d->environment(this);
    connect(d->surfaceflinger, SIGNAL(readyRead()), this, SLOT(logSomething()));
    connect(d->surfaceflinger, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processExited(int,QProcess::ExitStatus)));
    d->surfaceflinger->setProcessChannelMode(QProcess::MergedChannels);
    qDebug() << "Attempting to start SurfaceFlinger...";
    d->surfaceflinger->start(d->androidRootDir + "/system/bin/surfaceflinger");
    d->surfaceflinger->waitForStarted();
    // get process ID now
}


void Controller::startServicemanager()
{
    d->serviceManager = d->environment(this);
    connect(d->serviceManager, SIGNAL(readyRead()), this, SLOT(logSomething()));
    connect(d->serviceManager, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processExited(int,QProcess::ExitStatus)));
    d->serviceManager->setProcessChannelMode(QProcess::MergedChannels);
    qDebug() << "Attempting to start the Service Manager...";
    d->serviceManager->start(d->androidRootDir + "/system/bin/servicemanager");
    d->serviceManager->waitForStarted();
    // get process ID now
}

void Controller::stop()
{
    // TODO this should be done on PID... for now, we simply kill all instances of the applications in question, because there really should be only the one
    QProcess::startDetached("killall surfaceflinger");
    QProcess::startDetached("killall servicemanager");
    QProcess::startDetached("killall shashlik_launcher");
}
