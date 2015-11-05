project(shashlik_launcher)

#find_package(KF5CoreAddons NO_MODULE)
#find_package(KF5DBusAddons NO_MODULE)
#find_package(Qt5Network ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)
find_package(Qt5Core)
find_package(Qt5Gui)

add_definitions(-fPIC
                -fpermissive    # For redeclaration of char32_t (among other things?)
		-DHAVE_ANDROID_OS # For atrace_*. FIXME: This one needs some deeper considerations.
                )

# FIXME: Introduce ${<library>_INCLUDES} variables for all our libraries.
include_directories(${LIBBINDER_INCLUDES}
                    ${LIBUTILS_INCLUDES}
                    ${LIBCUTILS_INCLUDES}
                    ${LIBNATIVEHELPER_INCLUDEDIRS}
                    ${SKIA_INCLUDES}
                    ${CMAKE_INSTALL_PREFIX}/include
                    ${CMAKE_SOURCE_DIR}/src/libs/libshashlikutils
                    ${CMAKE_BINARY_DIR}     # for shashlikversion.h
                    ${ANDROID_FRAMEWORKS_BASE}/include
                    ${QT5CORE32_INCLUDE_DIRS}
                    )

set(shashlik_launcher_SRCS
    main.cpp
    AppRuntime.cpp
    appthread.cpp
#     ProcessGlobals.cpp
)

set(shashlik_jni_SRCS
    runtime/Stubs.cpp
)

set(launch_SRCS
    Launch.java
)

set(CMAKE_JAVA_COMPILE_FLAGS -J-Xmx2048M -target 1.5 -source 1.5 -encoding UTF-8 -Xmaxwarns 9999999 -g -bootclasspath ${CMAKE_BINARY_DIR}/src/deps/javalibrary-core/core.jar -extdirs \"\")
add_jar(launch SOURCES ${launch_SRCS} INCLUDE_JARS core framework)
# install_jar(launch ${ANDROID_JAR_DIR})

link_directories(${CMAKE_INSTALL_PREFIX}/lib)   # NOTE: This must be before add_executable :/

add_library(shashlik_jni SHARED ${shashlik_jni_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(shashlik_jni PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

target_link_libraries(shashlik_jni
#                       shashlikutils
                      javacrypto
)

add_executable(shashlik_launcher ${shashlik_launcher_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(shashlik_launcher PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

target_link_libraries(shashlik_launcher
                      dvm
                      pthread
                      ${QT5CORE32_LIBRARIES}
)

install(TARGETS shashlik_jni DESTINATION ${ANDROID_LIB_DIR})
install(TARGETS shashlik_launcher DESTINATION ${ANDROID_BIN_DIR})
