/* This file is part of the Shashlik Simulated Android Environment
    Copyright (c) 2003 David Faure <faure@kde.org>
    Copyright (c) 2003 Inge Wallin <inge@lysator.liu.se>

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

#include "shashlikversion.h"

unsigned int shashlik::version()
{
    return SHASHLIK_VERSION;
}

unsigned int shashlik::versionMajor()
{
    return SHASHLIK_VERSION_MAJOR;
}

unsigned int shashlik::versionMinor()
{
    return SHASHLIK_VERSION_MINOR;
}

unsigned int shashlik::versionRelease()
{
    return SHASHLIK_VERSION_RELEASE;
}

const char *shashlik::versionString()
{
    return SHASHLIK_VERSION_STRING;
}
