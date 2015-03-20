project(opengl-libraries)

set(REPO_PATH ${ANDROID_FRAMEWORKS_NATIVE_PATH}/opengl)

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

add_library(EGL SHARED ${EGL_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(EGL PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(EGL
    cutils utils log GLES_trace GLES_android
    pthread dl
)
target_include_directories(EGL
    PRIVATE
    ${REPO_PATH}/include
    ${REPO_PATH}/libs
    ${REPO_PATH}/libs/GLES_trace
    ${LIBUTILS_INCLUDES}
    ${CMAKE_SOURCE_DIR}/src/deps/stripped_bionic # for the hackified bionic_tls.h
    ${GENERAL_SOURCE_PATH}/libhardware/include
)
target_compile_definitions(EGL
    PRIVATE
    -DLOG_TAG="libEGL"
    -DHAVE_ANDROID_OS
    PUBLIC
    -DEGL_TRACE=1
    -DGL_GLEXT_PROTOTYPES -DEGL_EGLEXT_PROTOTYPES
)

add_library(GLES_trace SHARED ${GLES_trace_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(GLES_trace PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(GLES_trace
    cutils utils log protobuf-cpp-2.3.0-lite lzf
    #stlport 
)
target_compile_definitions(GLES_trace
    PRIVATE
    -DLOG_TAG="libGLES_trace"
    -DGOOGLE_PROTOBUF_NO_RTTI
    -DGL_GLEXT_PROTOTYPES -DEGL_EGLEXT_PROTOTYPES
)
target_include_directories(GLES_trace
    PRIVATE
    ${REPO_PATH}/include
    ${REPO_PATH}/libs
    ${REPO_PATH}/libs/GLES_trace
    ${LIBCUTILS_INCLUDES}
    ${GENERAL_SOURCE_PATH}/protobuf/src
    ${GENERAL_SOURCE_PATH} # for liblzf/lzf.h
    ${CMAKE_SOURCE_DIR}/src/deps/stripped_bionic # for the hackified bionic_tls.h
)

add_library(GLES_android SHARED ${agl_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(GLES_android PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(GLES_android
    cutils hardware utils log pixelflinger ETC1 ui
    pthread dl
)
target_compile_definitions(GLES_android
    PRIVATE
    -DLOG_TAG="libagl"
    -DGL_GLEXT_PROTOTYPES -DEGL_EGLEXT_PROTOTYPES
    -DANDROID
)
target_include_directories(GLES_android
    PRIVATE
    ${REPO_PATH}/include
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/include
    ${LIBCUTILS_INCLUDES}
    ${CMAKE_SOURCE_DIR}/src/deps/stripped_bionic # for the hackified bionic_tls.h
    ${GENERAL_SOURCE_PATH}/libhardware/include
)

add_library(ETC1 STATIC ${ETC1_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(ETC1 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(ETC1
    pthread dl
)
target_include_directories(ETC1
    PRIVATE
    ${REPO_PATH}/include
)

add_library(GLESv1_CM SHARED ${GLESv1_CM_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(GLESv1_CM PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(GLESv1_CM
    cutils log EGL
    pthread dl
)
target_compile_definitions(GLESv1_CM
    PRIVATE
    -DLOG_TAG="libGLESv1_CM"
    -DGL_GLEXT_PROTOTYPES -DEGL_EGLEXT_PROTOTYPES
    -DANDROID
)
target_include_directories(GLESv1_CM
    PRIVATE
    ${REPO_PATH}/include
    ${LIBCUTILS_INCLUDES}
    ${CMAKE_SOURCE_DIR}/src/deps/stripped_bionic # for the hackified bionic_tls.h
)

add_library(GLESv2 SHARED ${GLESv2_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(GLESv2 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(GLESv2
    cutils utils log EGL
    pthread dl
)
target_compile_definitions(GLESv2
    PRIVATE
    -DLOG_TAG="libGLESv1_CM"
    -DGL_GLEXT_PROTOTYPES -DEGL_EGLEXT_PROTOTYPES
    -DANDROID
)
target_include_directories(GLESv2
    PRIVATE
    ${REPO_PATH}/include
    ${LIBCUTILS_INCLUDES}
    ${CMAKE_SOURCE_DIR}/src/deps/stripped_bionic # for the hackified bionic_tls.h
)

add_definitions(
    -fpermissive
)

install(TARGETS GLESv2 GLESv1_CM ETC1 GLES_trace EGL DESTINATION ${ANDROID_LIB_DIR})
install(TARGETS GLES_android DESTINATION ${ANDROID_LIB_DIR}/egl)
