find_package(KF5CoreAddons NO_MODULE)
find_package(KF5DBusAddons NO_MODULE)
find_package(Qt5Network ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)

include_directories(${CMAKE_INSTALL_PREFIX}/include 
                    ${LIBCUTILS_INCLUDES}
)

set(kded_shashlik_propertiesd_SRCS
    propertiesd.cpp
)

add_library(kded_shashlik_propertiesd MODULE ${kded_shashlik_propertiesd_SRCS} )
kcoreaddons_desktop_to_json(kded_shashlik_propertiesd kded_shashlik_propertiesd.desktop)
set_target_properties(kded_shashlik_propertiesd PROPERTIES
    OUTPUT_NAME shashlik_propertiesd
)

target_link_libraries(
   kded_shashlik_propertiesd
   KF5::CoreAddons
   KF5::DBusAddons
   Qt5::Network
)

# FIXME: We need to find out which CMake variables we can use to create proper
#        destinations for these files in the kf5/kde5 install tree.
#        But until then, let's install them in the shashlik install tree.
install( TARGETS kded_shashlik_propertiesd        DESTINATION ${LIB_INSTALL_DIR}/qt5/plugins/kf5/kded )
# install( TARGETS kded_shashlik_propertiesd        DESTINATION /usr/lib64/qt5/plugins/kf5/kded )
