project(shashlik-controller)

add_subdirectory(icons)

set(controller_SRCS
    main.cpp
    Controller.cpp
    init_util.c
)

add_executable(shashlik-controller ${controller_SRCS})
qt5_use_modules(shashlik-controller Core Gui Quick Widgets)
target_link_libraries(shashlik-controller KF5::I18n)
target_include_directories(shashlik-controller
    PRIVATE
    ${LIBBINDER_INCLUDES}
)

install(PROGRAMS org.kde.shashlik-controller.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})
install(TARGETS shashlik-controller DESTINATION ${BIN_INSTALL_DIR})
