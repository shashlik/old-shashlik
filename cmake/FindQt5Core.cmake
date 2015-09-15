# WARNING This is hack territory. The reason this exists at all is that the highly powerful and elaborate
# Qt5 cmake modules are incapable of providing 32bit libraries on a 64bit system. So, we do this. Not exactly
# an optimal situation, but oh well.

if (QT5CORE32_INCLUDE_DIRS AND QT5CORE32_LIBRARIES)
    # Already in cache, be silent
    set(QT5CORE32_FIND_QUIETLY TRUE)
endif (QT5CORE32_INCLUDE_DIRS AND QT5CORE32_LIBRARIES)

find_path(QT5CORE32_INCLUDE_DIR NAMES QtCoreVersion
    PATHS
    /usr/include/i386-linux-gnu/qt5/QtCore
    ${CMAKE_INSTALL_PREFIX}/include/qt5/QtCore
    ${CMAKE_INSTALL_PREFIX}/include
    ${KDE4_INCLUDE_DIR}
    /usr/include/qt5/QtCore
    /usr/include
    /usr/include/QtCore
    )
find_path(QT5CORE32_BASE_INCLUDE_DIR NAMES QtCore/QtCoreVersion
    PATHS
    /usr/include/i386-linux-gnu/qt5
    ${CMAKE_INSTALL_PREFIX}/include/qt5
    ${CMAKE_INSTALL_PREFIX}/include
    ${KDE4_INCLUDE_DIR}
    /usr/include/qt5
    /usr/include
    )
find_library(QT5CORE32_LIBRARIES NAMES Qt5Core libQt5Core PATHS /usr/lib /usr/lib/i386-linux-gnu/)
SET(QT5CORE32_INCLUDE_DIRS "${QT5CORE32_INCLUDE_DIR};${QT5CORE32_BASE_INCLUDE_DIR}")


include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(QT5CORE DEFAULT_MSG QT5CORE32_INCLUDE_DIRS QT5CORE32_LIBRARIES)

mark_as_advanced(QT5CORE32_INCLUDE_DIRS QT5CORE32_LIBRARIES)
