project(shashlik_launcher)


add_subdirectory(libjni)


#find_package(KF5CoreAddons NO_MODULE)
#find_package(KF5DBusAddons NO_MODULE)
#find_package(Qt5Network ${REQUIRED_QT_VERSION} REQUIRED NO_MODULE)

add_definitions(-fPIC
                -fpermissive    # For redeclaration of char32_t (among other things?)
		-DHAVE_ANDROID_OS # For atrace_*. FIXME: This one needs some deeper considerations.
                )

# FIXME: Introduce ${<library>_INCLUDES} variables for all our libraries.
include_directories(${LIBBINDER_INCLUDES}
                    ${LIBUTILS_INCLUDES}
                    ${LIBCUTILS_INCLUDES}
                    ${LIBNATIVEHELPER_INCLUDEDIRS}
                    ${CMAKE_INSTALL_PREFIX}/include
                    ${CMAKE_SOURCE_DIR}/src/libs/libshashlikutils
                    ${CMAKE_BINARY_DIR}     # for shashlikversion.h
                    ${ANDROID_FRAMEWORKS_BASE}/include
                    )

set(shashlik_launcher_SRCS
    main.cpp
    AppRuntime.cpp
    ProcessGlobals.cpp
)

set(shashlik_launcher_helper_SRCS
    runtime/ShashlikRuntime.cpp
    runtime/Stubs.cpp

    # Old stuff that we may have to bring back in later.
    #${ANDROID_FRAMEWORKS_BASE}/core/jni/AndroidRuntime.cpp
)

link_directories(${CMAKE_INSTALL_PREFIX}/lib)   # NOTE: This must be before add_executable :/

add_library(shashlik_launcher_helper SHARED ${shashlik_launcher_helper_SRCS})

target_link_libraries(shashlik_launcher_helper
                      shashlikutils
                      binder
                      nativehelper
                      corkscrew log utils cutils  # android-core

                      ${STANDARD_SYS_LIBS}
)

add_executable(shashlik_launcher ${shashlik_launcher_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(shashlik_launcher PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

set_target_properties(shashlik_launcher PROPERTIES
    OUTPUT_NAME shashlik-launcher
)

target_link_libraries(shashlik_launcher
                      shashlik_launcher_helper
                      shashlikutils
                      binder
                      nativehelper
                      corkscrew log utils cutils  # android-core

                      ${STANDARD_SYS_LIBS}
)

install(TARGETS shashlik_launcher_helper DESTINATION ${LIB_INSTALL_DIR})
install(TARGETS shashlik_launcher DESTINATION ${BIN_INSTALL_DIR} )
