project(shashlik_launcher)

# Definitions.  Some of these might move to the top CMakeLists.txt
set(ANDROID_FRAMEWORKS_BASE "${CMAKE_SOURCE_DIR}/../frameworks-base")
set(ANDROID_CORE            "${CMAKE_SOURCE_DIR}/../android-core")
set(LIBNATIVEHELPER         "${CMAKE_SOURCE_DIR}/../libnativehelper")


#find_package(KF5CoreAddons NO_MODULE)
#find_package(KF5DBusAddons NO_MODULE)
#find_package(Qt5Network ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)

#add_definitions(-DHAVE_SYSTEM_PROPERTY_SERVER)
add_definitions(-fpermissive    # For redeclaration of char32_t (among other things?)
                )

include_directories(${CMAKE_INSTALL_PREFIX}/include
                    ${CMAKE_INSTALL_PREFIX}/include/nativehelper
                    #${CMAKE_CURRENT_SOURCE_DIR}/runtime
                    ${ANDROID_FRAMEWORKS_BASE}/include
                    #${ANDROID_CORE}/include
                    #${LIBNATIVEHELPER}/include
		    #fakeinclude
	            )

set(shashlik_launcher_SRCS
    main.cpp
    AppRuntime.cpp

    runtime/ShashlikRuntime.cpp

    #${ANDROID_FRAMEWORKS_BASE}/core/jni/AndroidRuntime.cpp
)

add_executable(shashlik_launcher ${shashlik_launcher_SRCS})
set_target_properties(shashlik_launcher PROPERTIES
    OUTPUT_NAME shashlik-launcher
)

link_directories(${CMAKE_INSTALL_PREFIX}/lib
                 /local/SHASHLIK/install/lib
)
#set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH}   /local/SHASHLIK/install/lib)
target_link_libraries(shashlik_launcher
    #${STANDARD_SYS_LIBS}
    libnativehelper.so
    libutils.so
    #KF5::CoreAddons
    #KF5::DBusAddons
    #Qt5::Network
)

install(TARGETS shashlik_launcher DESTINATION bin )
#install(FILES kded_shashlik_propertiesd.desktop  DESTINATION ${SERVICES_INSTALL_DIR}/kded )

