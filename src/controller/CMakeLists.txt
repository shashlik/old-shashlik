project(shashlik-controller)

include(KDECompilerSettings)

add_subdirectory(icons)

set(controller_SRCS
    main.cpp
    Controller.cpp
    ProcessTracker.cpp
    View.cpp
    init_util.c
)

add_executable(shashlik-controller ${controller_SRCS})
qt5_use_modules(shashlik-controller Core Gui Quick Widgets)
target_link_libraries(shashlik-controller
    KF5::I18n
    KF5::Service
    KF5::Declarative
    KF5::Package
    KF5::Plasma
    KF5::PlasmaQuick
    KF5::WindowSystem
)
target_include_directories(shashlik-controller
    PRIVATE
    ${LIBBINDER_INCLUDES}
)

install(PROGRAMS org.kde.shashlik-controller.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(TARGETS shashlik-controller DESTINATION ${BIN_INSTALL_DIR})
plasma_install_package(package org.kde.shashlik.controller packages package)
