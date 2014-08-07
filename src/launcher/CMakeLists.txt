project(shashlik_launcher)

# Definitions.  Some of these might move to the top CMakeLists.txt
set(STANDARD_SYS_LIBS  dl pthread z resolv ffi)


#find_package(KF5CoreAddons NO_MODULE)
#find_package(KF5DBusAddons NO_MODULE)
#find_package(Qt5Network ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)

add_definitions(-fPIC
                -fpermissive    # For redeclaration of char32_t (among other things?)
                )

# FIXME: Introduce ${<library>_INCLUDES} variables for all our libraries.
include_directories(${CMAKE_INSTALL_PREFIX}/include
                    ${CMAKE_INSTALL_PREFIX}/include/nativehelper
                    ${CMAKE_SOURCE_DIR}/src/libs/libshashlikutils
                    ${CMAKE_BINARY_DIR}     # for shashlikversion.h
                    ${ANDROID_FRAMEWORKS_BASE}/include
                    )

set(shashlik_launcher_SRCS
    main.cpp
    AppRuntime.cpp
    ProcessGlobals.cpp

    runtime/ShashlikRuntime.cpp
    runtime/Stubs.cpp

    # Old stuff that we may have to bring back in later.
    #${ANDROID_FRAMEWORKS_BASE}/core/jni/AndroidRuntime.cpp
)

link_directories(${CMAKE_INSTALL_PREFIX}/lib)   # NOTE: This must be before add_executable :/
add_executable(shashlik_launcher ${shashlik_launcher_SRCS})
set_target_properties(shashlik_launcher PROPERTIES
    OUTPUT_NAME shashlik-launcher
)

target_link_libraries(shashlik_launcher
    libnativehelper.so
    libutils.so
    libcutils.so
    libcorkscrew.so
    liblog.so
    #KF5::CoreAddons
    #KF5::DBusAddons
    #Qt5::Network
    shashlikutils
    ${STANDARD_SYS_LIBS}
)

install(TARGETS shashlik_launcher DESTINATION bin )

