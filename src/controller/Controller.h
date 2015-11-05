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
#include <QProcess>

class Controller : public QObject {
    Q_OBJECT
    Q_ENUMS(ErrorLevel)
    Q_PROPERTY(bool zygoteRunning READ zygoteRunning NOTIFY zygoteRunningChanged)
    Q_PROPERTY(bool installdRunning READ installdRunning NOTIFY installdRunningChanged)
    Q_PROPERTY(bool bootanimationRunning READ bootanimationRunning NOTIFY bootanimationRunningChanged)
    Q_PROPERTY(bool surfaceflingerRunning READ surfaceflingerRunning NOTIFY surfaceflingerRunningChanged)
    Q_PROPERTY(bool adbdRunning READ adbdRunning NOTIFY adbdRunningChanged)
    Q_PROPERTY(bool servicemanagerRunning READ servicemanagerRunning NOTIFY servicemanagerRunningChanged)

    Q_PROPERTY(bool quitOnError READ quitOnError WRITE setQuitOnError NOTIFY quitOnErrorChanged)
public:
    enum ErrorLevel {
        DebugLevel = 0,
        WarningLevel,
        CriticalLevel
    };

    Controller(QObject* parent = 0);
    virtual ~Controller();

    bool zygoteRunning() const;
    bool installdRunning() const;
    bool surfaceflingerRunning() const;
    bool servicemanagerRunning() const;
    bool adbdRunning() const;
    bool bootanimationRunning() const;

    bool quitOnError() const;
    void setQuitOnError(bool newValue);

Q_SIGNALS:
    void zygoteRunningChanged();
    void installdRunningChanged();
    void bootanimationRunningChanged();
    void surfaceflingerRunningChanged();
    void adbdRunningChanged();
    void servicemanagerRunningChanged();
    void quitOnErrorChanged();

    void error(QString description, Controller::ErrorLevel errorLevel);

public Q_SLOTS:
    void runApk(QString apkFile);
    void runAM(const QString& arguments);

    void startZygote();
    void startSurfaceflinger();
    void startServicemanager();
    void startInstalld();
    void startBootanimation();
    void startAdbd();

    void stop();
    void start() { startServicemanager(); startInstalld(); startSurfaceflinger(); /*startBootanimation();*/ startZygote(); startAdbd(); };
    void restart() { stop(); start(); }

    void logSomething();
    void processExited(int exitCode, QProcess::ExitStatus exitStatus);
    void processExited();

private:
    class Private;
    Private* d;
};

#endif // SHASHLIK_CONTROLLER_H
