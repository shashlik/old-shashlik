/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright 2015  Dan Leinir Turthra Jensen <admin@leinir.dk>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License or (at your option) version 3 or any later version
 * accepted by the membership of KDE e.V. (or its successor approved
 * by the membership of KDE e.V.), which shall act as a proxy
 * defined in Section 14 of version 3 of the license.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef PROCESSTRACKER_H
#define PROCESSTRACKER_H

#include <QObject>
#include <QStringList>

class ProcessTracker : public QObject
{
    Q_OBJECT
public:
    ProcessTracker(int processId, QObject* parent = 0);
    virtual ~ProcessTracker();

    int processId() const;
    QStringList arguments() const;

    /**
     * Kill the process being tracked, and clean up logs for it.
     *
     * This function can also be used to clean up stale log entries by manually
     * constructing a ProcessTracker for the PID in question and then calling
     * this function.
     * 
     * @return Whether the cleanup operation was successful
     */
    bool killProcess();

    /**
     * Get an instance for each process which has a binary which matches
     * the passed process name
     * 
     * @executableFilePath The name of the binary for which you want to track processes
     * @parent       The QObject instance to parent the trackers to
     * @return       A list of process trackers for the given process name. Can be empty.
     */
    static QList<ProcessTracker*> getTrackers(QString executableFilePath, QObject* parent);

    Q_SIGNAL void processExited();

private:
    class Private;
    Private *d;

private slots:
    void fileWatch();
};

#endif // PROCESSTRACKER_H
