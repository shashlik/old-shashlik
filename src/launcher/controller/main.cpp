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
#include <QStringList>
#include <qcommandlineparser.h>
#include <qtimer.h>

#include <klocalizedstring.h>

#include "Controller.h"
#include "init_util.h"

int main(int argc, char *argv[])
{
    {
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
    }

    QApplication app(argc, argv);
    app.setApplicationName("shashlik-launcher");
    app.setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Controller interface for the Shashlik Android application launcher");
    QCommandLineOption helpArgument =  parser.addHelpOption();
    QCommandLineOption versionArgument = parser.addVersionOption();

    QCommandLineOption apkArgument("launchapk", i18n("Run the apk passed as an argument. This will install and run the apk, and launch any services required to do so."), "apkfile");
    parser.addOption(apkArgument);

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

    QCommandLineOption startArgument("start", i18n("Start everything needed to launch applications (equivalent to running with --servicemanager, surfaceflinger and --zygote separately and in that order)"));
    parser.addOption(startArgument);
    QCommandLineOption stopArgument("stop", i18n("Stop everything needed to launch applications"));
    parser.addOption(stopArgument);
    QCommandLineOption restartArgument("restart", i18n("Stop and start all services (equivalent to running shashlik-controller first with --stop and then with --start)"));
    parser.addOption(restartArgument);

    parser.process(app);

    Controller* controller = new Controller(&app);
    if(parser.isSet(apkArgument)) {
        // do a thing with this thing...
        if(!controller->zygoteRunning() || !controller->servicemanagerRunning() || !controller->surfaceflingerRunning()) {
            // if any one of the services above isn't running, restart everything - we must assume something's broken
//             controller->start();
        }
        if(!controller->zygoteRunning() || !controller->servicemanagerRunning() || !controller->surfaceflingerRunning()) {
            // never mind for now, as these always return false...
            // If this happens when the check is actually functional, we should be quitting with a useful error
        }
        controller->runJar(parser.value(apkArgument));
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
    else if(parser.isSet(restartArgument)) {
        controller->restart();
    }
    else if(parser.isSet(stopArgument)) {
        controller->stop();
        QTimer::singleShot(0, &app, SLOT(quit()));
    }
    else {
        // no need to check for guiArgument - that is what we will have left, or no arguments, which is the same thing
        printf("Do the thing!\n");
    }

    return app.exec();
}