project(bootanimation)

set(REPO_PATH ${ANDROID_FRAMEWORKS_BASE}/cmds/bootanimation)

set(bootanimation_SRCS
    ${REPO_PATH}/bootanimation_main.cpp
    ${REPO_PATH}/BootAnimation.cpp
)

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
)
target_compile_definitions(bootanimation
    PRIVATE
    -DANDROID
    -DHAVE_ANDROID_OS
    -DSK_RELEASE
)

install(TARGETS bootanimation DESTINATION ${ANDROID_BIN_DIR})
