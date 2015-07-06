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

#include "ProcessTracker.h"

#include <QFile>
#include <QDirIterator>
#include <QDebug>
#include <QTimer>

#include <stdio.h>
#include <signal.h>

class ProcessTracker::Private
{
public:
    Private(int processId)
        : processId(processId)
        , watchTimer(0)
    {}

    int processId;
    QString commandLine;
    QStringList arguments;
    QFile logFile;
    // This should be qfilesystemwatcher. QFSW fails to work for me when watching something in /proc
    // Guess it would likely also fail for others. Long timer to keep track, then.
    QTimer* watchTimer;
    QFile watchFile;
};

ProcessTracker::ProcessTracker(int processId, QObject* parent)
    : QObject(parent)
    , d(new Private(processId))
{
    d->watchFile.setFileName(QString("/proc/%1").arg(QString::number(processId)));
    d->watchTimer = new QTimer(this);
    d->watchTimer->start(500);
    connect(d->watchTimer, SIGNAL(timeout()), SLOT(fileWatch()));
    QFile f(QString("/proc/%1/cmdline").arg(QString::number(processId)));
    if(f.open(QIODevice::ReadOnly | QFile::Text)) {
        QTextStream in(&f);
        QString arg;
        while(true) {
            while(true) {
                QChar chr = in.read(1).at(0);
                if(chr.isNull()) {
                    break;
                }
                arg.append(chr);
            }
            d->arguments.append(arg);
            if(in.atEnd())
                break;
            arg.clear();
        }
        f.close();
    }
}

ProcessTracker::~ProcessTracker()
{
    delete d;
}

int ProcessTracker::processId() const
{
    return d->processId;
}

QStringList ProcessTracker::arguments() const
{
    return d->arguments;
}

bool ProcessTracker::killProcess()
{
    int result = kill(d->processId, SIGTERM);
    if(result == 0) {
        return true;
    }
    return false;
}

void ProcessTracker::fileWatch()
{
    // something changed, but the file is still there. Never mind we don't care right now.
    if(d->watchFile.exists())
        return;
    d->watchTimer->stop();
    emit processExited();
}

QList< ProcessTracker* > ProcessTracker::getTrackers(QString executableFilePath, QObject* parent)
{
    QList<ProcessTracker*> trackers;

    QDirIterator it("/proc", QDirIterator::NoIteratorFlags);
    while (it.hasNext()) {
        it.next();
        if(it.fileName() == QString::number(it.fileName().toInt())) {
            QFileInfo file(QString("%1/exe").arg(it.filePath()));
            if(file.canonicalFilePath() == executableFilePath) {
                trackers.append(new ProcessTracker(it.fileName().toInt(), parent));
            }
        }
    }

    return trackers;
}
