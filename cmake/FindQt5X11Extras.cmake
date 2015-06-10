# WARNING This is hack territory. The reason this exists at all is that the highly powerful and elaborate
# Qt5 cmake modules are incapable of providing 32bit libraries on a 64bit system. So, we do this. Not exactly
# an optimal situation, but oh well.

if (QT5X11EXTRAS32_INCLUDE_DIRS AND QT5X11EXTRAS32_LIBRARIES)
    # Already in cache, be silent
    set(QT5X11EXTRAS32_FIND_QUIETLY TRUE)
endif (QT5X11EXTRAS32_INCLUDE_DIRS AND QT5X11EXTRAS32_LIBRARIES)

find_path(QT5X11EXTRAS32_INCLUDE_DIR NAMES QtX11ExtrasVersion
    PATHS
    /usr/include/i386-linux-gnu/qt5/QtX11Extras
    ${CMAKE_INSTALL_PREFIX}/include
    ${KDE4_INCLUDE_DIR}
    /usr/include
    /usr/include/QtX11Extras
    /usr/include/qt5/QtX11Extras
    )
find_path(QT5X11EXTRAS32_BASE_INCLUDE_DIR NAMES QtX11Extras/QtX11ExtrasVersion
    PATHS
    /usr/include/i386-linux-gnu/qt5
    ${CMAKE_INSTALL_PREFIX}/include
    ${KDE4_INCLUDE_DIR}
    /usr/include
    /usr/include/qt5
    )
find_library(QT5X11EXTRAS32_LIBRARIES NAMES Qt5X11Extras libQt5X11Extras libQt5X11Extras.so.5 PATHS /usr/lib /usr/lib/i386-linux-gnu/)
SET(QT5X11EXTRAS32_INCLUDE_DIRS "${QT5X11EXTRAS32_INCLUDE_DIR};${QT5X11EXTRAS32_BASE_INCLUDE_DIR}")


include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(QT5EXTRAS DEFAULT_MSG QT5X11EXTRAS32_INCLUDE_DIRS QT5X11EXTRAS32_LIBRARIES)

mark_as_advanced(QT5X11EXTRAS32_INCLUDE_DIRS QT5X11EXTRAS32_LIBRARIES)
