/* This file is part of Shashlik

   Copyright (C) 2014 Inge Wallin            <inge@lysator.liu.se>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
*/


// Own
#include "ApkFile.h"

// Qt
#include <QString>
#include <QByteArray>
#include <QList>

// KDE Frameworks
//#include <KArchive>

// This library
//...


// ================================================================
//                         class ApkFile


ApkFile::ApkFile(const QString &filename)
    : KZip(filename)
{
}

ApkFile::ApkFile(QIODevice *dev)
    : KZip(dev)
{
}

ApkFile::~ApkFile()
{
}


bool ApkFile::unpack(const QString &dest) const
{
    const KArchiveDirectory *dir = directory();

    // This was simpler than I thought...
    return dir->copyTo(dest, true);
}


bool ApkFile::writeApk(const QString &fileName,
                       const QByteArray &appIdentification,
                       QHash<QString, QString> metadata)
{
    Q_UNUSED(fileName);
    Q_UNUSED(appIdentification);
    Q_UNUSED(metadata);

    return false;
}


// ----------------------------------------------------------------
//                         Private functions


