project(shashlik-controller)

set(controller_SRCS
    main.cpp
    Controller.cpp
    init_util.c
)

add_executable(shashlik-controller ${controller_SRCS})
qt5_use_modules(shashlik-controller Core Gui Quick Widgets)
target_link_libraries(shashlik-controller KF5::I18n)

install(TARGETS shashlik-controller DESTINATION ${BIN_INSTALL_DIR})
