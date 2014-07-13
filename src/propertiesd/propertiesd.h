/* This file is part of Shashlik

   Copyright (C) 2014 Aaron Seigo <aseigo@kde.org>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
*/

#ifndef PROPERTIESD_H
#define PROPERTIESD_H

#include <kdedmodule.h>

#include <QLocalServer>
#include <QSettings>

class Propertiesd : public KDEDModule
{
    Q_OBJECT

public:
    Propertiesd(QObject *parent, const QVariantList &);
    ~Propertiesd();

private Q_SLOTS:
    void newConnection();
    void readRequest();

private:
    void initProperties();
    void writeProperty(const QString &key, const QString &values);
    QString readProperty(const QString &key);

    QLocalServer m_server;
    QSettings m_properties;
};

#endif

