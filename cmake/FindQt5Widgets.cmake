# WARNING This is hack territory. The reason this exists at all is that the highly powerful and elaborate
# Qt5 cmake modules are incapable of providing 32bit libraries on a 64bit system. So, we do this. Not exactly
# an optimal situation, but oh well.

if (QT5WIDGETS32_INCLUDE_DIRS AND QT5WIDGETS32_LIBRARIES)
    # Already in cache, be silent
    set(QT5WIDGETS32_FIND_QUIETLY TRUE)
endif (QT5WIDGETS32_INCLUDE_DIRS AND QT5WIDGETS32_LIBRARIES)

find_path(QT5WIDGETS32_INCLUDE_DIR NAMES QtWidgetsVersion
    PATHS
    /usr/include/i386-linux-gnu/qt5/QtWidgets
    ${CMAKE_INSTALL_PREFIX}/include
    ${KDE4_INCLUDE_DIR}
    /usr/include
    /usr/include/QtWidgets
    /usr/include/qt5/QtWidgets
    )
find_path(QT5WIDGETS32_BASE_INCLUDE_DIR NAMES QtWidgets/QtWidgetsVersion
    PATHS
    /usr/include/i386-linux-gnu/qt5
    ${CMAKE_INSTALL_PREFIX}/include
    ${KDE4_INCLUDE_DIR}
    /usr/include
    /usr/include/qt5
    )
find_library(QT5WIDGETS32_LIBRARIES NAMES Qt5Widgets libQt5Widgets PATHS /usr/lib /usr/lib/i386-linux-gnu/)
SET(QT5WIDGETS32_INCLUDE_DIRS "${QT5WIDGETS32_INCLUDE_DIR};${QT5WIDGETS32_BASE_INCLUDE_DIR}")


include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(QT5WIDGETS DEFAULT_MSG QT5WIDGETS32_INCLUDE_DIRS QT5WIDGETS32_LIBRARIES)

mark_as_advanced(QT5WIDGETS32_INCLUDE_DIRS QT5WIDGETS32_LIBRARIES)
