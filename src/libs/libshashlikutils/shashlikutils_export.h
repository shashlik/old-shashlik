/* This file is part of the Shashlik Simulated Android Environment
    Copyright (C) 2006 David Faure <faure@kde.org>
    Copyright (C) 2006 Thomas Zander <zander@kde.org>
    Copyright (c) 2014 Inge Wallin <inge@lysator.liu.se>

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
    Boston, MA 02110-1301, USA.
*/

#ifndef SHASHLIKUTILS_EXPORT_H
#define SHASHLIKUTILS_EXPORT_H

/* needed for KDE_EXPORT and KDE_IMPORT macros */
#include <qglobal.h>

/* We use _WIN32/_WIN64 instead of Q_OS_WIN so that this header can be used from C files too */
#if defined _WIN32 || defined _WIN64

#ifndef SHASHLIKUTILS_EXPORT
# if defined(MAKE_SHASHLIKUTILS_LIB)
/* We are building this library */
#  define SHASHLIKUTILS_EXPORT Q_DECL_EXPORT
# else
/* We are using this library */
#  define SHASHLIKUTILS_EXPORT Q_DECL_IMPORT
# endif
#endif

#else /* UNIX */

#define SHASHLIKUTILS_EXPORT Q_DECL_EXPORT

#endif

/* Now the same for SHASHLIKUTILS_TEST_EXPORT, if compiling with unit tests enabled */

#ifdef COMPILING_TESTS
#if defined _WIN32 || defined _WIN64
# if defined(MAKE_SHASHLIKUTILS_LIB)
#       define SHASHLIKUTILS_TEST_EXPORT Q_DECL_EXPORT
#   else
#       define SHASHLIKUTILS_TEST_EXPORT Q_DECL_IMPORT
#   endif
# else /* not windows */
#   define SHASHLIKUTILS_TEST_EXPORT Q_DECL_EXPORT
# endif
#else /* not compiling tests */
#   define SHASHLIKUTILS_TEST_EXPORT
#endif


#endif
