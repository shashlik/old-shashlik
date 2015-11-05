project(opengl-libraries)

set(REPO_PATH ${ANDROID_FRAMEWORKS_NATIVE_PATH}/opengl)

add_definitions(
    -DHAVE_ANDROID_OS
    -DANDROID
)

# add_subdirectory(glapi)

set(GLES_trace_SRCS
    ${REPO_PATH}/libs/GLES_trace/src/gltrace_api.cpp
    ${REPO_PATH}/libs/GLES_trace/src/gltrace_context.cpp
    ${REPO_PATH}/libs/GLES_trace/src/gltrace_egl.cpp
    ${REPO_PATH}/libs/GLES_trace/src/gltrace_eglapi.cpp
    ${REPO_PATH}/libs/GLES_trace/src/gltrace_fixup.cpp
    ${REPO_PATH}/libs/GLES_trace/src/gltrace_hooks.cpp
    ${REPO_PATH}/libs/GLES_trace/src/gltrace.pb.cpp
    ${REPO_PATH}/libs/GLES_trace/src/gltrace_transport.cpp
)

set(EGL_SRCS
    ${REPO_PATH}/libs/EGL/egl_tls.cpp
    ${REPO_PATH}/libs/EGL/egl_cache.cpp
    ${REPO_PATH}/libs/EGL/egl_display.cpp
    ${REPO_PATH}/libs/EGL/egl_object.cpp
    ${REPO_PATH}/libs/EGL/egl.cpp
    ${REPO_PATH}/libs/EGL/eglApi.cpp
    ${REPO_PATH}/libs/EGL/trace.cpp
    ${REPO_PATH}/libs/EGL/getProcAddress.cpp
    ${REPO_PATH}/libs/EGL/Loader.cpp
)

set(agl_SRCS
    ${REPO_PATH}/libagl/egl.cpp
    ${REPO_PATH}/libagl/state.cpp
    ${REPO_PATH}/libagl/texture.cpp
    ${REPO_PATH}/libagl/Tokenizer.cpp
    ${REPO_PATH}/libagl/TokenManager.cpp
    ${REPO_PATH}/libagl/TextureObjectManager.cpp
    ${REPO_PATH}/libagl/BufferObjectManager.cpp
    ${REPO_PATH}/libagl/array.cpp
    ${REPO_PATH}/libagl/fp.cpp
    ${REPO_PATH}/libagl/light.cpp
    ${REPO_PATH}/libagl/matrix.cpp
    ${REPO_PATH}/libagl/mipmap.cpp
    ${REPO_PATH}/libagl/primitives.cpp
    ${REPO_PATH}/libagl/vertex.cpp
)

set(ETC1_SRCS
    ${REPO_PATH}/libs/ETC1/etc1.cpp
)

set(GLESv1_CM_SRCS
    ${REPO_PATH}/libs/GLES_CM/gl.cpp
)

set(GLESv2_SRCS
    ${REPO_PATH}/libs/GLES2/gl2.cpp
)

set(mesa_egl_dri2_SRCS
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/drivers/dri2/egl_dri2.c
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/drivers/dri2/platform_android.c
)

set(mesa_loader_SRCS
    ${GENERAL_SOURCE_PATH}/mesa/src/loader/loader.c
    ${GENERAL_SOURCE_PATH}/mesa/src/loader/pci_id_driver_map.c
)

set(mesa_SRCS
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglapi.c
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglapi.h
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglarray.c
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglarray.h
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglcompiler.h
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglconfig.c
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglconfig.h
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglcontext.c
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglcontext.h
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglcurrent.c
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglcurrent.h
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/egldefines.h
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/egldisplay.c
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/egldisplay.h
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/egldriver.c
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/egldriver.h
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglfallbacks.c
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglglobals.c
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglglobals.h
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglimage.c
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglimage.h
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/egllog.c
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/egllog.h
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglstring.c
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglstring.h
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglsurface.c
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglsurface.h
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglsync.c
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/eglsync.h
    ${GENERAL_SOURCE_PATH}/mesa/src/egl/main/egltypedefs.h
)

set(gralloc.shashlik_SRCS
    ${GENERAL_SOURCE_PATH}/drm_gralloc/gralloc.c
    ${GENERAL_SOURCE_PATH}/drm_gralloc/gralloc_drm.c
    ${GENERAL_SOURCE_PATH}/drm_gralloc/gralloc_drm_kms.c
    ${GENERAL_SOURCE_PATH}/drm_gralloc/gralloc_drm_intel.c
#     ${GENERAL_SOURCE_PATH}/drm_gralloc/gralloc_drm_radeon.c
#     ${GENERAL_SOURCE_PATH}/drm_gralloc/gralloc_drm_nouveau.c
)

set(grallocdrm_module_SRCS
    ${GENERAL_SOURCE_PATH}/gralloc/alloc_device.cpp
    ${GENERAL_SOURCE_PATH}/gralloc/gralloc_module.cpp
)

set(hwcomposer_drm_SRCS
    ${GENERAL_SOURCE_PATH}/hwcomposer/hwcomposer.cpp
)
# 
# add_library(EGL SHARED ${EGL_SRCS})
# if(FORCE_32BIT_BUILD)
#     set_target_properties(EGL PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
# endif(FORCE_32BIT_BUILD)
# target_link_libraries(EGL
#     GLES_trace
# #     GLES_android
# )
# target_include_directories(EGL
#     PRIVATE
#     ${REPO_PATH}/include
#     ${REPO_PATH}/libs
#     ${REPO_PATH}/libs/GLES_trace
#     ${LIBUTILS_INCLUDES}
#     ${CMAKE_SOURCE_DIR}/src/deps/stripped_bionic # for the hackified bionic_tls.h
#     ${GENERAL_SOURCE_PATH}/android-libhardware/include
# )
# target_compile_definitions(EGL
#     PRIVATE
#     -DLOG_TAG="libEGL"
#     PUBLIC
#     -DEGL_TRACE=1
#     -DGL_GLEXT_PROTOTYPES -DEGL_EGLEXT_PROTOTYPES
# )
# 
# add_library(GLES_trace SHARED ${GLES_trace_SRCS})
# if(FORCE_32BIT_BUILD)
#     set_target_properties(GLES_trace PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
# endif(FORCE_32BIT_BUILD)
# target_link_libraries(GLES_trace
#     cutils utils protobuf-cpp-2.3.0-lite lzf
#     #stlport 
# )
# target_compile_definitions(GLES_trace
#     PRIVATE
#     -DLOG_TAG="libGLES_trace"
#     -DGOOGLE_PROTOBUF_NO_RTTI
#     -DEGL_TRACE=1
#     -DGL_GLEXT_PROTOTYPES -DEGL_EGLEXT_PROTOTYPES
# )
# target_include_directories(GLES_trace
#     PRIVATE
#     ${REPO_PATH}/include
#     ${REPO_PATH}/libs
#     ${REPO_PATH}/libs/GLES_trace
#     ${LIBCUTILS_INCLUDES}
#     ${GENERAL_SOURCE_PATH}/protobuf/src
#     ${GENERAL_SOURCE_PATH} # for liblzf/lzf.h
#     ${CMAKE_SOURCE_DIR}/src/deps/stripped_bionic # for the hackified bionic_tls.h
# )
# 
# add_library(GLES_android SHARED ${agl_SRCS})
# if(FORCE_32BIT_BUILD)
#     set_target_properties(GLES_android PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
# endif(FORCE_32BIT_BUILD)
# target_link_libraries(GLES_android
#     pixelflinger ETC1 ui
# )
# target_compile_definitions(GLES_android
#     PRIVATE
#     -DLOG_TAG="libagl"
#     -DGL_GLEXT_PROTOTYPES -DEGL_EGLEXT_PROTOTYPES
# )
# target_include_directories(GLES_android
#     PRIVATE
#     ${REPO_PATH}/include
#     ${ANDROID_FRAMEWORKS_NATIVE_PATH}/include
#     ${LIBCUTILS_INCLUDES}
#     ${CMAKE_SOURCE_DIR}/src/deps/stripped_bionic # for the hackified bionic_tls.h
#     ${GENERAL_SOURCE_PATH}/android-libhardware/include
# )

add_library(gralloc.shashlik SHARED ${gralloc.shashlik_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(gralloc.shashlik PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32" )
    #OUTPUT_NAME gralloc.default PREFIX ""
endif(FORCE_32BIT_BUILD)
# because otherwise the module loader looks for the wrong file
set_target_properties(gralloc.shashlik PROPERTIES PREFIX "")
target_compile_definitions(gralloc.shashlik
    PRIVATE
    -DENABLE_INTEL
#     -DENABLE_RADEON
#     -DENABLE_NOUVEAU
    -DANDROID_VERSION=0x442
)
target_include_directories(gralloc.shashlik
    PRIVATE
#     /usr/src/linux-4.0.4/include/drivers/gpu/drm/i915
    ${LIBLOG_INCLUDES}
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/opengl/include

    ${LIBHARDWARE_INCLUDES}
    ${DRM_INCLUDE_DIRS}
#     /usr/src/linux-4.0.4/drivers/gpu/drm/i915
#     /usr/src/linux-4.0.4/include/uapi
#     /usr/src/linux-4.0.4/include
#     ${GENERAL_SOURCE_PATH}/mesa/src/mesa/drivers/dri/i915
    ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(gralloc.shashlik
    log
    cutils
    hardware_legacy
    hardware
    ${DRM_LIBRARIES}
    drm_intel
#     /usr/lib/dri/i915_dri.so
#     drm_radeon
#     drm_nouveau
)

add_library(hwcomposer.shashlik SHARED ${hwcomposer_drm_SRCS})
set_target_properties(hwcomposer.shashlik PROPERTIES PREFIX "")
if(FORCE_32BIT_BUILD)
    set_target_properties(hwcomposer.shashlik PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
# because otherwise the module loader looks for the wrong file
set_target_properties(hwcomposer.shashlik PROPERTIES PREFIX "")
target_compile_definitions(hwcomposer.shashlik
    PRIVATE
    -DHAVE_PTHREAD
    -DANDROID_VERSION=0x442
    -DLOG_TAG="hwcomposer-drm"
)
target_include_directories(hwcomposer.shashlik
    PRIVATE
    ${DRM_INCLUDE_DIRS}
    ${LIBHARDWARE_INCLUDES}
#     ${GENERAL_SOURCE_PATH}/gralloc #new

    ${GENERAL_SOURCE_PATH}/drm_gralloc


    ${LIBLOG_INCLUDES}
    ${ANDROID_CORE_PATH}/include/sync
    ${GENERAL_SOURCE_PATH}/hwcomposer
)
target_link_libraries(hwcomposer.shashlik
    ${DRM_LIBRARIES}
    log
    hardware
    sync
    gralloc.shashlik
)
# 
# add_library(ETC1 STATIC ${ETC1_SRCS})
# if(FORCE_32BIT_BUILD)
#     set_target_properties(ETC1 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
# endif(FORCE_32BIT_BUILD)
# target_link_libraries(ETC1
#     pthread dl
# )
# target_include_directories(ETC1
#     PRIVATE
#     ${REPO_PATH}/include
# )
# 
# add_library(GLESv1_CM SHARED ${GLESv1_CM_SRCS})
# if(FORCE_32BIT_BUILD)
#     set_target_properties(GLESv1_CM PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
# endif(FORCE_32BIT_BUILD)
# target_link_libraries(GLESv1_CM
#     EGL
# )
# target_compile_definitions(GLESv1_CM
#     PRIVATE
#     -DLOG_TAG="libGLESv1_CM"
#     -DGL_GLEXT_PROTOTYPES -DEGL_EGLEXT_PROTOTYPES
# )
# target_include_directories(GLESv1_CM
#     PRIVATE
#     ${REPO_PATH}/include
#     ${LIBCUTILS_INCLUDES}
#     ${CMAKE_SOURCE_DIR}/src/deps/stripped_bionic # for the hackified bionic_tls.h
# )
# 
# add_library(GLESv2 SHARED ${GLESv2_SRCS})
# if(FORCE_32BIT_BUILD)
#     set_target_properties(GLESv2 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
# endif(FORCE_32BIT_BUILD)
# target_link_libraries(GLESv2
#     EGL
# )
# target_compile_definitions(GLESv2
#     PRIVATE
#     -DLOG_TAG="libGLESv1_CM"
#     -DGL_GLEXT_PROTOTYPES -DEGL_EGLEXT_PROTOTYPES
# )
# target_include_directories(GLESv2
#     PRIVATE
#     ${REPO_PATH}/include
#     ${LIBCUTILS_INCLUDES}
#     ${CMAKE_SOURCE_DIR}/src/deps/stripped_bionic # for the hackified bionic_tls.h
# )

add_definitions(
    -fpermissive
)


# install(TARGETS GLESv2 GLESv1_CM ETC1 GLES_trace EGL gralloc.shashlik DESTINATION ${ANDROID_LIB_DIR})
# install(TARGETS GLES_android DESTINATION ${ANDROID_LIB_DIR}/egl)
install(TARGETS hwcomposer.shashlik DESTINATION ${ANDROID_LIB_DIR}/hw)
install(TARGETS gralloc.shashlik DESTINATION ${ANDROID_LIB_DIR})
install(TARGETS gralloc.shashlik DESTINATION ${ANDROID_LIB_DIR}/hw)
