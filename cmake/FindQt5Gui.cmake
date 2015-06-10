# WARNING This is hack territory. The reason this exists at all is that the highly powerful and elaborate
# Qt5 cmake modules are incapable of providing 32bit libraries on a 64bit system. So, we do this. Not exactly
# an optimal situation, but oh well.

if (QT5GUI32_INCLUDE_DIRS AND QT5GUI32_LIBRARIES)
    # Already in cache, be silent
    set(QT5GUI32_FIND_QUIETLY TRUE)
endif (QT5GUI32_INCLUDE_DIRS AND QT5GUI32_LIBRARIES)

find_path(QT5GUI32_INCLUDE_DIR NAMES QtGuiVersion
    PATHS
    /usr/include/i386-linux-gnu/qt5/QtGui
    ${CMAKE_INSTALL_PREFIX}/include
    ${KDE4_INCLUDE_DIR}
    /usr/include
    /usr/include/QtGui
    /usr/include/qt5/QtGui
    )
find_path(QT5GUI32_BASE_INCLUDE_DIR NAMES QtGui/QtGuiVersion
    PATHS
    /usr/include/i386-linux-gnu/qt5
    ${CMAKE_INSTALL_PREFIX}/include
    ${KDE4_INCLUDE_DIR}
    /usr/include
    /usr/include/qt5
    )
find_library(QT5GUI32_LIBRARIES NAMES Qt5Gui libQt5Gui PATHS /usr/lib /usr/lib/i386-linux-gnu/)
SET(QT5GUI32_INCLUDE_DIRS "${QT5GUI32_INCLUDE_DIR};${QT5GUI32_BASE_INCLUDE_DIR}")


include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(QT5GUI DEFAULT_MSG QT5GUI32_INCLUDE_DIRS QT5GUI32_LIBRARIES)

mark_as_advanced(QT5GUI32_INCLUDE_DIRS QT5GUI32_LIBRARIES)
