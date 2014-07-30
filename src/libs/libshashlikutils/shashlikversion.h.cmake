/* This file is part of the Shashlik Simulated Android Environment
    Copyright (c) 2003 David Faure <faure@kde.org>
    Copyright (c) 2003 Lukas Tinkl <lukas@kde.org>
    Copyright (c) 2004 Nicolas Goutte <goutte@kde.org>
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
 * Boston, MA 02110-1301, USA.
*/

#ifndef _SHASHLIK_VERSION_H_
#define _SHASHLIK_VERSION_H_

#include "shashlikutils_export.h"

// -- WARNING: do not edit values below, instead edit SHASHLIK_VERSION_*, etc in /CMakeLists.txt --

/**
* @def SHASHLIK_VERSION_STRING
* @ingroup ShashlikMacros
* @brief Version of Shashlik as string, at compile time
*
* This macro contains the Shashlik version in string form. As it is a macro,
* it contains the version at compile time. See Shashlik::versionString() if you need
* the Shashlik version used at runtime.
*
* @note The version string might contain spaces and special characters,
* especially for development versions of Shashlik.
* If you use that macro directly for a file format (e.g. OASIS Open Document)
* or for a protocol (e.g. http) be careful that it is appropriate.
* (Fictional) example: "2.8 Pre-Alpha"
*/
#define SHASHLIK_VERSION_STRING "@SHASHLIK_VERSION_STRING@"

/**
 * @def SHASHLIK_VERSION_MAJOR
 * @ingroup ShashlikMacros
 * @brief Major version of Shashlik, at compile time
*/
#define SHASHLIK_VERSION_MAJOR @SHASHLIK_VERSION_MAJOR@

/**
 * @def SHASHLIK_VERSION_MINOR
 * @ingroup ShashlikMacros
 * @brief Minor version of Shashlik, at compile time
 * SHASHLIK_VERSION_MINOR is computed based on this value.
 * Unstable versions subtract 1 from this value, e.g. 2.5 Alpha has minor 4.
*/
#define SHASHLIK_VERSION_MINOR @SHASHLIK_VERSION_MINOR@

/**
 * @def SHASHLIK_VERSION_RELEASE
 * @ingroup ShashlikMacros
 * @brief Release version of Shashlik, at compile time.
 * 89 for Alpha.
 */
#define SHASHLIK_VERSION_RELEASE @SHASHLIK_VERSION_RELEASE@

/**
 * @ingroup ShashlikMacros
 * @brief Make a number from the major, minor and release number of a Shashlik version
 *
 * This function can be used for preprocessing when SHASHLIK_IS_VERSION is not
 * appropriate.
 */
#define SHASHLIK_MAKE_VERSION( a,b,c ) (((a) << 16) | ((b) << 8) | (c))

/**
 * @ingroup ShashlikMacros
 * @brief Version of Shashlik as number, at compile time
 *
 * This macro contains the Shashlik version in number form. As it is a macro,
 * it contains the version at compile time. See version() if you need
 * the Shashlik version used at runtime.
 */
#define SHASHLIK_VERSION \
    SHASHLIK_MAKE_VERSION(SHASHLIK_VERSION_MAJOR,SHASHLIK_VERSION_MINOR,SHASHLIK_VERSION_RELEASE)

/**
 * @ingroup ShashlikMacros
 * @brief Check if the Shashlik version matches a certain version or is higher
 *
 * This macro is typically used to compile conditionally a part of code:
 * @code
 * #if SHASHLIK_IS_VERSION(2,3,0)
 * // Code for Shashlik 2.3.0
 * #else
 * // Code for older Shashlik
 * #endif
 * @endcode
 *
 * @warning Especially during development phases of Shashlik, be careful
 * when choosing the version number that you are checking against.
 * Otherwise you might risk to break the next Shashlik release.
 * Therefore be careful that development version have a
 * version number lower than the released version, so do not check
 * e.g. for Shashlik 4.3 with SHASHLIK_IS_VERSION(4,3,0)
 * but with the actual version number at a time a needed feature was introduced, e.g. 4.3.2.
 */
#define SHASHLIK_IS_VERSION(a,b,c) ( SHASHLIK_VERSION >= SHASHLIK_MAKE_VERSION(a,b,c) )

/**
 * @def SHASHLIK_YEAR
 * @ingroup ShashlikMacros
 * @brief Year of the Shashlik release, set at compile time
 *
 * This macro is used in "About application" dialog for strings such as "© 2012-..., The Author Team".
*/
#define SHASHLIK_YEAR "@SHASHLIK_YEAR@"

/**
 * Namespace for general Shashlik functions.
 */
namespace shashlik
{
/**
 * Returns the encoded number of Shashlik's version, see the SHASHLIK_VERSION macro.
 * In contrary to that macro this function returns the number of the actually
 * installed Shashlik version, not the number of the Shashlik version that was
 * installed when the program was compiled.
 * @return the version number, encoded in a single uint
 */
SHASHLIKUTILS_EXPORT unsigned int version();

/**
 * Returns the major number of Shashlik's version, e.g.
 * 1 for Shashlik 1.2.3.
 * @return the major version number
 */
SHASHLIKUTILS_EXPORT unsigned int versionMajor();

/**
 * Returns the minor number of Shashlik's version, e.g.
 * 2 for Shashlik 1.2.3.
 * @return the minor version number
 */
SHASHLIKUTILS_EXPORT unsigned int versionMinor();

/**
 * Returns the release of Shashlik's version, e.g.
 * 3 for Shashlik 1.2.3.
 * @return the release number
 */
SHASHLIKUTILS_EXPORT unsigned int versionRelease();

/**
 * Returns the Shashlik version as string, e.g. "1.2.3".
 * @return the Shashlik version. You can keep the string forever.
 */
SHASHLIKUTILS_EXPORT const char *versionString();
}

#endif // _SHASHLIK_VERSION_H_
