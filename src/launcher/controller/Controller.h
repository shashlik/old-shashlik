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

#ifndef SHASHLIK_CONTROLLER_H
#define SHASHLIK_CONTROLLER_H

#include <QObject>
#include <qprocess.h>

class Controller : public QObject {
    Q_OBJECT
public:
    Controller(QObject* parent = 0);
    virtual ~Controller();

    /// TODO this should do real things, like check PIDs and report back.
    bool zygoteRunning() { return false; }
    bool surfaceflingerRunning() { return false; }
    bool servicemanagerRunning() { return false; }

Q_SIGNALS:
    void onError(QString description);

public Q_SLOTS:
    void runJar(const QString& jarFile);
    void runAM(const QString& arguments);

    void startZygote();
    void startSurfaceflinger();
    void startServicemanager();
    void startInstalld();

    void stop();
    void start() { startServicemanager(); startInstalld(); startSurfaceflinger(); startZygote(); };
    void restart() { stop(); start(); }

    void logSomething();
    void processExited(int exitCode, QProcess::ExitStatus exitStatus);

private:
    class Private;
    Private* d;
};

#endif // SHASHLIK_CONTROLLER_H
