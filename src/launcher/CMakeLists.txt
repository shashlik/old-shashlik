project(shashlik_launcher)

#find_package(KF5CoreAddons NO_MODULE)
#find_package(KF5DBusAddons NO_MODULE)
#find_package(Qt5Network ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)

#add_definitions(-DHAVE_SYSTEM_PROPERTY_SERVER)

#include_directories(${SHASHLIK_INSTALL_PREFIX}/include)

set(shashlik_launcher_SRCS
    main.cpp

    AppRuntime.cpp
    )

add_executable(shashlik_launcher ${shashlik_launcher_SRCS})
set_target_properties(shashlik_launcher PROPERTIES
    OUTPUT_NAME shashlik-launcher
)

target_link_libraries(shashlik_launcher
    #KF5::CoreAddons
    #KF5::DBusAddons
    #Qt5::Network
)

install(TARGETS shashlik_launcher DESTINATION bin )
#install(FILES kded_shashlik_propertiesd.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/kded )

