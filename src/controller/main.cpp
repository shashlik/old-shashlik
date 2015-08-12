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

#include <stdio.h>

#include <QApplication>
#include <QDebug>
#include <QStringList>
#include <QCommandLineParser>
#include <QTimer>
#include <QFile>
#include <QIcon>
#include <QDir>
#include <QDebug>
#include <QMessageBox>

#include <KLocalizedString>
#include <KAboutData>

#include "Controller.h"
#include "init_util.h"
#include "View.h"

void showMessage(QString errorMessage, Controller::ErrorLevel errorLevel) {
    switch(errorLevel) {
        case Controller::CriticalLevel:
            qCritical() << "Shashlik ERROR:" << errorMessage;
            break;
        case Controller::WarningLevel:
            qWarning() << "Shashlik Warning:" << errorMessage;
            break;
        case Controller::DebugLevel:
        default:
            qDebug() << "Shashlik Debug:" << errorMessage;
            break;
    }
}

void showMessageBox(QString errorMessage, Controller::ErrorLevel errorLevel) {
    switch(errorLevel) {
        case Controller::CriticalLevel:
            QMessageBox::critical(0, i18n("Shashlik Controller"), errorMessage);
            break;
        case Controller::WarningLevel:
            QMessageBox::warning(0, i18n("Shashlik Controller"), errorMessage);
            break;
        case Controller::DebugLevel:
        default:
            // don't show debug messages in the gui, because that's just silly...
            break;
    }
}

int main(int argc, char *argv[])
{
    QLatin1String socketDir(ANDROID_SOCKET_DIR);
    if(!QDir::root().exists(socketDir)) {
        QDir::root().mkdir(socketDir);
    }

    QCoreApplication *app = new QCoreApplication(argc, argv);
    app->setApplicationName("shashlik-launcher");
    app->setApplicationVersion("0.1");

    KLocalizedString::setApplicationDomain("shashlik-controller");

    // About data
    KAboutData aboutData("shashlik-controller", i18n("Shashlik Controller"), "0.1", i18n("Controller application for the Shashlik Android Runtime"), KAboutLicense::GPL, i18n("Copyright 2015, Dan Leinir Turthra Jensen"));
    aboutData.addAuthor(i18n("Dan Leinir Turthra Jensen"), i18n("Maintainer"), "admin@leinir.dk");
    KAboutData::setApplicationData(aboutData);

    QCommandLineParser parser;
    parser.setApplicationDescription("Controller interface for the Shashlik Android application launcher");
    QCommandLineOption helpArgument =  parser.addHelpOption();
    QCommandLineOption versionArgument = parser.addVersionOption();

    //QCommandLineOption apkArgument("apk", i18n("Run the apk passed as an argument. This will install and run the apk, and launch any services required to do so. Optional."), "[apkfile]");
    parser.addPositionalArgument("apkfile", i18n("Run the apk passed as an argument. This will install and run the apk, and launch any services required to do so. When passing an APK, don't pass any other options. Optional."), "[apkfile]");

    QCommandLineOption amArgument("launcham", i18n("Launch the activity manager application, with the arguments passed as amargs"), "amargs");
    parser.addOption(amArgument);

    QCommandLineOption guiArgument("ui", i18n("Start the graphical UI. Default behaviour."));
    parser.addOption(guiArgument);

    QCommandLineOption zygoteArgument("zygote", i18n("Start zygote only"));
    parser.addOption(zygoteArgument);

    QCommandLineOption surfaceflingerArgument("surfaceflinger", i18n("Start surfaceflinger only"));
    parser.addOption(surfaceflingerArgument);

    QCommandLineOption servicemanagerArgument("servicemanager", i18n("Start the servicemanager only"));
    parser.addOption(servicemanagerArgument);

    QCommandLineOption installdArgument("installd", i18n("Start the installer daemon only"));
    parser.addOption(installdArgument);

    QCommandLineOption adbdArgument("adbd", i18n("Start the android debugger daemon only"));
    parser.addOption(adbdArgument);

    QCommandLineOption startArgument("start", i18n("Start everything needed to launch applications (equivalent to running with --servicemanager, surfaceflinger and --zygote separately and in that order)"));
    parser.addOption(startArgument);
    QCommandLineOption stopArgument("stop", i18n("Stop everything needed to launch applications"));
    parser.addOption(stopArgument);
    QCommandLineOption restartArgument("restart", i18n("Stop and start all services (equivalent to running shashlik-controller first with --stop and then with --start)"));
    parser.addOption(restartArgument);
    QCommandLineOption statusArgument("status", i18n("See the status of the various services"));
    parser.addOption(statusArgument);

    parser.process(*app);
    QStringList apkfile = parser.positionalArguments();

    // If the socket file already exists, assume it was created for us, and just needs to be opened...
    if(QFile::exists(QString("%1/ANDROID_SOCKET_installd").arg(ANDROID_SOCKET_DIR)) || parser.isSet(stopArgument)) {
    }
    else {
        int fd = create_socket("installd", SOCK_STREAM, 0666, getuid(), getgid());
        if(fd < 0)
            return fd;
        int size = snprintf(NULL, 0, "%d", fd) + 1;
        char *ANDROID_SOCKET_installd = (char *)alloca(size);
        ANDROID_SOCKET_installd[size] = '\0';
        snprintf(ANDROID_SOCKET_installd, size, "%d", fd);
        setenv("ANDROID_SOCKET_installd", ANDROID_SOCKET_installd, 1);

        fd = create_socket("zygote", SOCK_STREAM, 0666, getuid(), getgid());
        if(fd < 0)
            return fd;
        size = snprintf(NULL, 0, "%d", fd) + 1;
        char *ANDROID_SOCKET_zygote = (char *)alloca(size);
        ANDROID_SOCKET_zygote[size] = '\0';
        snprintf(ANDROID_SOCKET_zygote, size, "%d", fd);
        setenv("ANDROID_SOCKET_zygote", ANDROID_SOCKET_zygote, 1);

        fd = create_socket("adbd", SOCK_STREAM, 0666, getuid(), getgid());
        if(fd < 0)
            return fd;
        size = snprintf(NULL, 0, "%d", fd) + 1;
        char *ANDROID_SOCKET_adbd = (char *)alloca(size);
        ANDROID_SOCKET_adbd[size] = '\0';
        snprintf(ANDROID_SOCKET_adbd, size, "%d", fd);
        setenv("ANDROID_SOCKET_adbd", ANDROID_SOCKET_adbd, 1);
    }

    bool haveGui = false;
    if(apkfile.length() < 1 && !parser.isSet(amArgument) && !parser.isSet(startArgument) && !parser.isSet(zygoteArgument) && !parser.isSet(surfaceflingerArgument) && !parser.isSet(servicemanagerArgument) && !parser.isSet(installdArgument) && !parser.isSet(restartArgument) && !parser.isSet(stopArgument) && !parser.isSet(statusArgument)) {
        // YES this looks silly. We do this to avoid having to maintain two mains and whatnot.
        delete app;
        QApplication *theApp = new QApplication(argc, argv);

        KLocalizedString::setApplicationDomain("shashlik-controller");

        // About data
        KAboutData aboutData("shashlik-controller", i18n("Shashlik Controller"), "0.1", i18n("Controller application for the Shashlik Android Runtime"), KAboutLicense::GPL, i18n("Copyright 2015, Dan Leinir Turthra Jensen"));
        aboutData.addAuthor(i18n("Dan Leinir Turthra Jensen"), i18n("Maintainer"), "admin@leinir.dk");
        KAboutData::setApplicationData(aboutData);
        theApp->setWindowIcon(QIcon::fromTheme("shashlik-controller"));
        app = theApp;
        haveGui = true;
    }

    Controller* controller = new Controller(app);
    QObject::connect(controller, &Controller::error, showMessage);
    if(haveGui) {
        QObject::connect(controller, &Controller::error, showMessageBox);
    }

    if(apkfile.length() > 0) {
        // do a thing with this thing...
        if(!controller->zygoteRunning() || !controller->servicemanagerRunning() || !controller->surfaceflingerRunning()) {
            // if any one of the services above isn't running, restart everything - we must assume something's broken
            controller->restart();
        }
        if(!controller->zygoteRunning() || !controller->servicemanagerRunning() || !controller->surfaceflingerRunning()) {
            // If this happens when the check is actually functional, we should be quitting with a useful error
            emit controller->error(i18n("We are unable to start an Android environment to run your application inside. Please check your installation and try again."), Controller::CriticalLevel);
            QTimer::singleShot(0, app, SLOT(quit()));
        }
        controller->runApk(apkfile.at(0));
    }
    else if(parser.isSet(amArgument)) {
        controller->runAM(parser.value(amArgument));
    }
    else if(parser.isSet(startArgument)) {
        controller->start();
    }
    else if(parser.isSet(zygoteArgument)) {
        controller->startZygote();
    }
    else if(parser.isSet(surfaceflingerArgument)) {
        controller->startSurfaceflinger();
    }
    else if(parser.isSet(servicemanagerArgument)) {
        controller->startServicemanager();
    }
    else if(parser.isSet(installdArgument)) {
        controller->startInstalld();
    }
    else if(parser.isSet(adbdArgument)) {
        controller->startAdbd();
    }
    else if(parser.isSet(restartArgument)) {
        controller->restart();
    }
    else if(parser.isSet(stopArgument)) {
        controller->stop();
        QTimer::singleShot(0, app, SLOT(quit()));
    }
    else if(parser.isSet(statusArgument)) {
        qDebug() << "Status of servicemanager:" << controller->servicemanagerRunning();
        qDebug() << "Status of zygote:" << controller->surfaceflingerRunning();
        qDebug() << "Status of surfaceflinger:" << controller->zygoteRunning();
        qDebug() << "Status of adbd:" << controller->adbdRunning();
        qDebug() << "Status of installd:" << controller->installdRunning();
    }
    else {
        // no need to check for guiArgument - that is what we will have left, or no arguments, which is the same thing
        controller->setQuitOnError(false);
        new View(controller);
    }

    return app->exec();
}
