/* This file is part of Shashlik

   Copyright (C) 2014 Inge Wallin <inge@lysator.liu.se>

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

#ifndef APKFILE_H
#define APKFILE_H


// Qt
#include <QHash>

// KDE Frameworks
//#include <KArchive>
#include <KZip>

//
//#include "FileCollector.h"


class QString;
class QByteArray;

class ApkFile : public KZip
{
public:
    ApkFile(const QString &filename);
    ApkFile(QIODevice *dev);
    virtual ~ApkFile();

    /** Unpack the APK file into the directory dest
     *
     * Unpack the contents of the APK file into a directory. The directory is created 
     *
     * @param dest path to a directory which is created if needed and where the unpacked files are placed
     */
    bool unpack(const QString &dest) const;

    // When you have created all the content and added it using
    // addContentFile(), call this function once and it will write the
    // apk to the disk.
    bool writeApk(const QString &fileName,
                  const QByteArray &appIdentification,
                  QHash<QString, QString> metadata);

private:
// Private functions here

private:
// Private data members here
};

#endif // APKFILE_H
