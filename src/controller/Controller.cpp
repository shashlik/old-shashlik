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
#include "ProcessTracker.h"

#include <KLocalizedString>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QMetaObject>
#include <QTimer>

class Controller::Private
{
public:
    Private()
        : quitOnError(true)
        , adbd(0)
        , adbdTracker(0)
        , bootanimation(0)
        , bootanimationTracker(0)
        , installd(0)
        , installdTracker(0)
        , serviceManager(0)
        , serviceManagerTracker(0)
        , surfaceflinger(0)
        , surfaceflingerTracker(0)
        , zygote(0)
        , zygoteTracker(0)
    {
        appDir = qApp->applicationDirPath();
        QDir thisAppDir(appDir);
        thisAppDir.cdUp();
        libraryRoot = thisAppDir.canonicalPath();
        thisAppDir.cd("android");
        androidRootDir = thisAppDir.canonicalPath();
    }
    ~Private()
    {
        if(zygote) zygote->terminate();
        if(serviceManager) serviceManager->terminate();
        if(surfaceflinger) surfaceflinger->terminate();
        if(installd) installd->terminate();
        if(adbd) adbd->terminate();
        if(bootanimation) bootanimation->terminate();
        Q_FOREACH(QProcess* proc, applications) {
            proc->terminate();
        }
    }

    bool quitOnError;

    QProcess* adbd;
    ProcessTracker* adbdTracker;
    QProcess* bootanimation;
    ProcessTracker* bootanimationTracker;
    QProcess* installd;
    ProcessTracker* installdTracker;
    QProcess* serviceManager;
    ProcessTracker* serviceManagerTracker;
    QProcess* surfaceflinger;
    ProcessTracker* surfaceflingerTracker;
    QProcess* zygote;
    ProcessTracker* zygoteTracker;

    QList<QProcess*> applications;
    QList<ProcessTracker*> applicationTrackers;

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

        QStringList ldpath = QStringList() << env.value("LD_LIBRARY_PATH") <<  "/usr/lib" << "LIBPATH/lib64" << "LIBPATH/lib64/egl" << "ANDROID_ROOT/vendor/lib" << "ANDROID_ROOT/system/lib";
        ldpath.replaceInStrings("LIBPATH", libraryRoot);
        ldpath.replaceInStrings("ANDROID_ROOT", androidRootDir);
        env.insert("LD_LIBRARY_PATH", ldpath.join(QLatin1String(":")));

        QString jarPath = QString("/system/framework").prepend(androidRootDir);
        QStringList bootclasspath = QStringList() << "JARPATH/core.jar" << "JARPATH/conscrypt.jar" << "JARPATH/bouncycastle.jar" << "JARPATH/okhttp.jar" << "JARPATH/ext.jar" << "JARPATH/framework.jar" << "JARPATH/telephony-common.jar" << "JARPATH/voip-common.jar" << "JARPATH/framework2.jar" << "JARPATH/shashlik.jar";
        bootclasspath.replaceInStrings("JARPATH", jarPath);
        env.insert("BOOTCLASSPATH", bootclasspath.join(QLatin1String(":")));

        env.insert("SHASHLIK_ROOT", androidRootDir);
        env.insert("ANDROID_ROOT", QString("/system").prepend(androidRootDir));
        env.insert("ANDROID_ASSETS", QString("/system/app").prepend(androidRootDir));
        env.insert("ANDROID_DATA", QString("/data").prepend(androidRootDir));
        env.insert("ANDROID_STORAGE", QString("/storage").prepend(androidRootDir));
        env.insert("ASEC_MOUNTPOINT", QString("/mnt/asec").prepend(androidRootDir));
        env.insert("LOOP_MOUNTPOINT", QString("/mnt/obb").prepend(androidRootDir));
        env.insert("HAL_LIBRARY_PATH1", QString("/system/lib/hw").prepend(androidRootDir));
        env.insert("DOWNLOAD_CACHE", QString("/cache").prepend(androidRootDir));

//         env.insert("ANDROID_BOOTLOGO", "1");
        env.insert("ANDROID_WINDOW_SIZE", "200x200");
        env.insert("EGL_PLATFORM", "wayland");

        // TODO this should probably use some XDG type thing to sniff what this really is...
        env.insert("EXTERNAL_STORAGE", "/mnt");

        process->setProcessEnvironment(env);
        return process;
    }

    // We may need to ensure that zygote is actually ready to take connections before attempting to do certain things
    bool waitForZygoteReady() {
        // show the throbber dialogue
        // check zygote, keep checking
        // if zygote takes a long time, tell the user
        return true;
    }
};

Controller::Controller(QObject* parent)
    : QObject(parent)
    , d(new Private)
{
    QList<ProcessTracker*> trackers;
    trackers = ProcessTracker::getTrackers(d->androidRootDir + "/system/bin/servicemanager", this);
    if(trackers.count() > 0)
        d->serviceManagerTracker = trackers.at(0);
    trackers = ProcessTracker::getTrackers(d->androidRootDir + "/system/bin/surfaceflinger", this);
    if(trackers.count() > 0)
        d->surfaceflingerTracker = trackers.at(0);
    trackers = ProcessTracker::getTrackers(d->androidRootDir + "/system/bin/installd", this);
    if(trackers.count() > 0)
        d->installdTracker = trackers.at(0);
    trackers = ProcessTracker::getTrackers(d->androidRootDir + "/system/bin/bootanimation", this);
    if(trackers.count() > 0)
        d->bootanimationTracker = trackers.at(0);
    trackers = ProcessTracker::getTrackers(d->androidRootDir + "/system/bin/adbd", this);
    if(trackers.count() > 0)
        d->adbdTracker = trackers.at(0);
    trackers = ProcessTracker::getTrackers(d->androidRootDir + "/system/bin/shashlik_launcher", this);
    QString zygoteArg("-Xzygote");
    Q_FOREACH(ProcessTracker* tracker, trackers) {
        bool isZygote;
        Q_FOREACH(QString arg, tracker->arguments()) {
            if(arg == zygoteArg) {
                isZygote = true;
                break;
            }
        }
        if(isZygote)
            d->zygoteTracker = tracker;
        else
            d->applicationTrackers.append(tracker);
    }
}

Controller::~Controller()
{
    delete d;
}

bool Controller::quitOnError() const
{
    return d->quitOnError;
}

void Controller::setQuitOnError(bool newValue)
{
    d->quitOnError = newValue;
    emit quitOnErrorChanged();
}

void Controller::logSomething()
{
    QProcess* proc = qobject_cast<QProcess*>(sender());
    if(proc) {
        QString origin;
        if(proc == d->zygote) {
            origin = "Zygote";
        } else if(proc == d->serviceManager) {
            origin = "Servicemanager";
        } else if(proc == d->surfaceflinger) {
            origin = "SurfaceFlinger";
        } else if(proc == d->installd) {
            origin = "Installer Daemon";
        } else if(proc == d->bootanimation) {
            origin = "Bootanimation";
        } else if(proc == d->adbd) {
            origin = "ADBD";
        } else if(d->applications.contains(proc)) {
            origin = proc->objectName();
        } else {
            origin = QString("Unknown Process (%1)").arg(QString::number(proc->processId()));
        }
        while(proc->canReadLine()) {
            QString output = QString("%1: %2").arg(origin).arg(QString(proc->readLine()));
            printf(qPrintable(output));
        }
    }
}

void Controller::processExited(int exitCode, QProcess::ExitStatus exitStatus)
{
    QProcess* proc = qobject_cast<QProcess*>(sender());
    if(proc) {
        if(proc == d->zygote) {
            emit error("Zygote has exited - if zygote exits, everything should be killed!", CriticalLevel);
            stop();
            // grace to allow things to shut down...
            if(d->quitOnError) QTimer::singleShot(1000, qApp, SLOT(quit()));
        }
        else if(proc == d->serviceManager) {
            emit error("The service manager has exited - if this happens, nothing will work and we should just cut our losses and quit everything else.", CriticalLevel);
            stop();
            // grace to allow things to shut down...
            if(d->quitOnError) QTimer::singleShot(1000, qApp, SLOT(quit()));
        }
        else if(proc == d->surfaceflinger) {
            emit error(QString("SurfaceFlinger has exited. This is a terrible thing! We should try and restart it and see if that helps (and then quit if it still doesn't). Exit code %1 and exit status %2").arg(QString::number(exitCode)).arg(QString::number(exitStatus)), CriticalLevel);
            // grace to allow things to shut down...
            if(d->quitOnError) QTimer::singleShot(1000, qApp, SLOT(quit()));
        }
        else if(proc == d->installd) {
            emit error("The Installer daemon has exited. We'll just let that slide.", WarningLevel);
        }
        else if(proc == d->bootanimation) {
            emit error(QString("The boot animation has exited. We'll just let that slide. Exit code was %1 and exit status was %2").arg(exitCode).arg(exitStatus), WarningLevel);
        }
        else if(proc == d->adbd) {
            emit error("The android debugger daemon has exited. We'll just let that slide.", WarningLevel);
        }
        else if(d->applications.contains(proc)) {
            if(proc->exitCode() == QProcess::CrashExit) {
                emit error(QString("The application %1 has quit unexpectedly. Something gone done blown up.").arg(proc->objectName()), WarningLevel);
            }
            else {
                // This is not always true - the launcher will exit cleanly, even if the vm died for some reason or another. This needs fixing.
                printf("Normal exit from application %s\n", proc->objectName().toLocal8Bit().data());
            }
            if(d->quitOnError) QTimer::singleShot(1000, qApp, SLOT(quit()));
        }
        else {
            emit error(QString("%1 has exited").arg(proc->program()), WarningLevel);
        }
    }
}

void Controller::processExited()
{
    if(sender() == d->installdTracker) {
        d->installdTracker->deleteLater();
        d->installdTracker = 0;
        emit installdRunningChanged();
    }
    else if(sender() == d->bootanimationTracker) {
        d->bootanimationTracker->deleteLater();
        d->bootanimationTracker = 0;
        emit bootanimationRunningChanged();
    }
    else if(sender() == d->adbdTracker) {
        d->adbdTracker->deleteLater();
        d->adbdTracker = 0;
        emit adbdRunningChanged();
    }
    else if(sender() == d->serviceManagerTracker) {
        d->serviceManagerTracker->deleteLater();
        d->serviceManagerTracker = 0;
        emit servicemanagerRunningChanged();
    }
    else if(sender() == d->surfaceflingerTracker) {
        d->surfaceflingerTracker->deleteLater();
        d->surfaceflingerTracker = 0;
        emit surfaceflingerRunningChanged();
    }
    else if(sender() == d->zygoteTracker) {
        d->zygoteTracker->deleteLater();
        d->zygoteTracker = 0;
        emit zygoteRunningChanged();
    }
    else {
        Q_FOREACH(ProcessTracker* tracker, d->applicationTrackers) {
            if(tracker->processId()) {
                d->applicationTrackers.removeAll(tracker);
                tracker->deleteLater();
                break;
            }
        }
    }
}

void Controller::runApk(QString apkFile)
{
    // We only accept local files, no URLs here.
    /// TODO make sure we accept URLs at some point. KIO support would be very nice here.
    if(apkFile.toLower().startsWith("file://"))
        apkFile = apkFile.mid(7);
    if(QFile::exists(apkFile) && d->waitForZygoteReady()) {
        QProcess* process = d->environment(this);
        d->applications.append(process);
        connect(process, SIGNAL(readyRead()), this, SLOT(logSomething()));
        connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processExited(int,QProcess::ExitStatus)));
        process->setProcessChannelMode(QProcess::MergedChannels);
        QProcessEnvironment env = process->processEnvironment();
        env.insert("CLASSPATH", d->androidRootDir + "/system/framework/launch.jar");
        process->setProcessEnvironment(env);
//         qDebug() << "Installing the application contained within" << apkFile;
//         process->start(d->androidRootDir + "/system/bin/adb", QStringList() << "install" << apkFile);

        process->setObjectName(apkFile.split("/").last());
//         process->waitForFinished(10000);

        qDebug() << "Launching the application contained within" << apkFile;
        process->start(d->androidRootDir + "/system/bin/shashlik_launcher", QStringList() << d->androidRootDir + "/system/bin/" << "com.android.commands.launch.Launch" << apkFile);

        ProcessTracker* tracker = new ProcessTracker(process->processId());
        connect(tracker, SIGNAL(processExited()), SLOT(processExited()));
        d->applicationTrackers.append(tracker);
    }
}

void Controller::runAM(const QString& arguments)
{
    if(d->waitForZygoteReady()) {
        QProcess* process = d->environment(this);
        d->applications.append(process);
        connect(process, SIGNAL(readyRead()), this, SLOT(logSomething()));
        connect(process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processExited(int,QProcess::ExitStatus)));
        process->setProcessChannelMode(QProcess::MergedChannels);
        QProcessEnvironment env = process->processEnvironment();
        env.insert("CLASSPATH", d->androidRootDir + "/system/framework/am.jar");
        process->setProcessEnvironment(env);
        qDebug() << "Launching the activity manager with the arguents" << arguments;
        process->start(d->androidRootDir + "/system/bin/shashlik_launcher", QStringList() << d->androidRootDir + "/system/bin/" << "com.android.commands.am.Am" << arguments);
        process->setObjectName("ActivityManager");
        process->waitForStarted();
    }
}

bool Controller::zygoteRunning() const
{
    return (d->zygoteTracker != 0);
}

void Controller::startZygote()
{
    if(zygoteRunning())
        return;
    d->zygote = d->environment(this);
    connect(d->zygote, SIGNAL(readyRead()), this, SLOT(logSomething()));
    connect(d->zygote, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processExited(int,QProcess::ExitStatus)));
    d->zygote->setProcessChannelMode(QProcess::MergedChannels);
    qDebug() << "Attempting to start the Zygote...";
//     d->zygote->start("strace " + d->androidRootDir + "/system/bin/shashlik_launcher", QStringList() << "-Xzygote" << d->androidRootDir + "/system/bin/" << "--zygote" << "--start-system-server");
    d->zygote->start(d->androidRootDir + "/system/bin/shashlik_launcher", QStringList() << "-Xzygote" << d->androidRootDir + "/system/bin/" << "--zygote" << "--start-system-server");

    
//      d->zygote->start(d->androidRootDir + "/system/lib/emulator_test_renderer");
//      d->zygote->start("gdbserver localhost:1234 " + d->androidRootDir + "/system/lib/emulator_test_renderer");
//      d->zygote->start("strace " + d->androidRootDir + "/system/lib/emulator_test_renderer 2> /home/leinir/derp");
    d->zygote->waitForStarted();

    d->zygoteTracker = new ProcessTracker(d->zygote->processId(), this);
    connect(d->zygoteTracker, SIGNAL(processExited()), SLOT(processExited()));
    emit zygoteRunningChanged();
}

bool Controller::surfaceflingerRunning() const
{
    return (d->surfaceflingerTracker != 0);
}

void Controller::startSurfaceflinger()
{
    if(surfaceflingerRunning())
        return;
    d->surfaceflinger = d->environment(this);
    connect(d->surfaceflinger, SIGNAL(readyRead()), this, SLOT(logSomething()));
    connect(d->surfaceflinger, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processExited(int,QProcess::ExitStatus)));
    d->surfaceflinger->setProcessChannelMode(QProcess::MergedChannels);
    qDebug() << "Attempting to start SurfaceFlinger...";
//     d->surfaceflinger->start("gdbserver localhost:1234 " + d->androidRootDir + "/system/bin/surfaceflinger");
    d->surfaceflinger->start(d->androidRootDir + "/system/bin/surfaceflinger");
    d->surfaceflinger->waitForStarted();
    d->surfaceflingerTracker = new ProcessTracker(d->surfaceflinger->processId(), this);
    connect(d->surfaceflingerTracker, SIGNAL(processExited()), SLOT(processExited()));
    emit surfaceflingerRunningChanged();
}

bool Controller::servicemanagerRunning() const
{
    return (d->serviceManagerTracker != 0);
}

void Controller::startServicemanager()
{
    if(servicemanagerRunning()) {
        emit error("A service manager is already running. If you believe this to be in error, please stop all Shashlik services and try again.", CriticalLevel);
        if(d->quitOnError) QTimer::singleShot(1000, qApp, SLOT(quit()));
        return;
    }
    d->serviceManager = d->environment(this);
    connect(d->serviceManager, SIGNAL(readyRead()), this, SLOT(logSomething()));
    connect(d->serviceManager, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processExited(int,QProcess::ExitStatus)));
    d->serviceManager->setProcessChannelMode(QProcess::MergedChannels);
    qDebug() << "Attempting to start the Service Manager...";
    d->serviceManager->start(d->androidRootDir + "/system/bin/servicemanager");
    d->serviceManager->waitForStarted();
    d->serviceManagerTracker = new ProcessTracker(d->serviceManager->processId(), this);
    connect(d->serviceManagerTracker, SIGNAL(processExited()), SLOT(processExited()));
    emit servicemanagerRunningChanged();
}

bool Controller::adbdRunning() const
{
    return (d->adbdTracker != 0);
}

void Controller::startAdbd()
{
    if(adbdRunning())
        return;
    d->adbd = d->environment(this);
    connect(d->adbd, SIGNAL(readyRead()), this, SLOT(logSomething()));
    connect(d->adbd, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processExited(int,QProcess::ExitStatus)));
    d->adbd->setProcessChannelMode(QProcess::MergedChannels);
    qDebug() << "Attempting to start the android debugger daemon...";
    d->adbd->start(d->androidRootDir + "/system/bin/adbd");
//     d->adbd->start("gdbserver localhost:1234 " + d->androidRootDir + "/system/bin/adbd");
    d->adbd->waitForStarted();
    d->adbdTracker = new ProcessTracker(d->adbd->processId(), this);
    connect(d->adbdTracker, SIGNAL(processExited()), SLOT(processExited()));
    emit adbdRunningChanged();
}

bool Controller::installdRunning() const
{
    return (d->installdTracker != 0);
}

void Controller::startInstalld()
{
    if(installdRunning())
        return;
    d->installd = d->environment(this);
    connect(d->installd, SIGNAL(readyRead()), this, SLOT(logSomething()));
    connect(d->installd, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processExited(int,QProcess::ExitStatus)));
    d->installd->setProcessChannelMode(QProcess::MergedChannels);
    qDebug() << "Attempting to start the installer daemon...";
    d->installd->start(d->androidRootDir + "/system/bin/installd");
    d->installd->waitForStarted();
    d->installdTracker = new ProcessTracker(d->installd->processId(), this);
    connect(d->installdTracker, SIGNAL(processExited()), SLOT(processExited()));
    emit installdRunningChanged();
}

bool Controller::bootanimationRunning() const
{
    return (d->bootanimationTracker != 0);
}

void Controller::startBootanimation()
{
    if(bootanimationRunning())
        return;
    d->bootanimation = d->environment(this);
    connect(d->bootanimation, SIGNAL(readyRead()), this, SLOT(logSomething()));
    connect(d->bootanimation, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processExited(int,QProcess::ExitStatus)));
    d->bootanimation->setProcessChannelMode(QProcess::MergedChannels);
    qDebug() << "Attempting to start the boot animation...";
    d->bootanimation->start(d->androidRootDir + "/system/bin/bootanimation");
    d->bootanimation->waitForStarted();
    d->bootanimationTracker = new ProcessTracker(d->bootanimation->processId(), this);
    connect(d->bootanimationTracker, SIGNAL(processExited()), SLOT(processExited()));
    emit bootanimationRunningChanged();
}

void Controller::stop()
{
    if(surfaceflingerRunning()) {
        d->surfaceflingerTracker->killProcess();
    }
    if(installdRunning()) {
        d->installdTracker->killProcess();
    }
    if(bootanimationRunning()) {
        d->bootanimationTracker->killProcess();
    }
    if(servicemanagerRunning()) {
        d->serviceManagerTracker->killProcess();
    }
    if(adbdRunning()) {
        d->adbdTracker->killProcess();
    }
    if(zygoteRunning()) {
        d->zygoteTracker->killProcess();
    }
    Q_FOREACH(ProcessTracker* tracker, d->applicationTrackers) {
        tracker->killProcess();
        tracker->deleteLater();
    }
    d->applicationTrackers.clear();
}
