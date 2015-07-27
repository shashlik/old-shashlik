project(bootanimation)

find_package(Qt5Core) # Yes, this is a hack. We need the 32bit libraries
find_package(Qt5Gui) # Yes, this is a hack. We need the 32bit libraries
find_package(KF5Wayland REQUIRED)
find_package(Wayland COMPONENTS Client Egl Cursor REQUIRED)

set(REPO_PATH ${ANDROID_FRAMEWORKS_BASE}/cmds/bootanimation)

set(bootanimation_SRCS
    ${REPO_PATH}/bootanimation_main.cpp
    ${REPO_PATH}/BootAnimation.cpp
)

add_definitions(-fPIC)
add_executable(bootanimation ${bootanimation_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(bootanimation PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(bootanimation
    cutils
    log
    androidfw
    utils
    binder
    ui
    skia
    EGL
    GLESv1_CM
    gui
    epoxy
    ${Wayland_LIBRARIES}
    KF5WaylandClient
    ${QT5CORE32_LIBRARIES}
    ${QT5GUI32_LIBRARIES}
    waylandthings
)
target_include_directories(bootanimation
    PRIVATE
    ${LIBCUTILS_INCLUDES}
    ${LIBLOG_INCLUDES}
    ${LIBANDROIDCORE_INCLUDEDIRS}
    ${LIBANDROIDLIBCORE_INCLUDEDIRS}
    ${OPENGL_INCLUDES}
    ${LIBBINDER_INCLUDES}
    ${ANDROID_FRAMEWORKS_BASE}/include
    ${LIBHARDWARE_INCLUDES}
    ${SKIA_INCLUDES}
    ${GENERAL_SOURCE_PATH}/shashlik/src/deps/surfaceflinger
    ${Wayland_INCLUDE_DIRS}
    /usr/include/KF5/KWayland
    /usr/include/KF5
    ${QT5CORE32_INCLUDE_DIRS}
    ${QT5GUI32_INCLUDE_DIRS}
)
target_compile_definitions(bootanimation
    PRIVATE
    -DANDROID
    -DHAVE_ANDROID_OS
    -DSK_RELEASE
    -DWL_EGL_PLATFORM
    ${Wayland_DEFINITIONS}
)

install(TARGETS bootanimation DESTINATION ${ANDROID_BIN_DIR})
