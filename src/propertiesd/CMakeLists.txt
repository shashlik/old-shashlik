find_package(KF5CoreAddons NO_MODULE)
find_package(KF5DBusAddons NO_MODULE)
find_package(Qt5Network ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)

add_definitions(-DHAVE_SYSTEM_PROPERTY_SERVER)

include_directories(${SHAHSKLIK_INSTALL_PREFIX}/include)

set(
   kded_shashlik_propertiesd_SRCS
   propertiesd.cpp
   )

add_library(kded_shashlik_propertiesd MODULE ${kded_shashlik_propertiesd_SRCS} )
set_target_properties(kded_shashlik_propertiesd PROPERTIES
    OUTPUT_NAME shashlik_propertiesd
)

target_link_libraries(
   kded_shashlik_propertiesd
   KF5::CoreAddons
   KF5::DBusAddons
   Qt5::Network
)

install( TARGETS kded_shashlik_propertiesd        DESTINATION ${PLUGIN_INSTALL_DIR}/kf5/kded )
install( FILES kded_shashlik_propertiesd.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/kded )

