project(surfaceflinger)

find_package(Qt5Core) # Yes, this is a hack. We need the 32bit libraries
find_package(Qt5Gui) # Yes, this is a hack. We need the 32bit libraries
find_package(Qt5Widgets) # Yes, this is a hack. We need the 32bit libraries
find_package(Qt5X11Extras) # Yes, this is a hack. We need the 32bit libraries

set(REPO_PATH ${ANDROID_FRAMEWORKS_NATIVE_PATH}/services/surfaceflinger)

add_definitions(-fvisibility=hidden -fpermissive -fPIC)

set(libsurfaceflinger_SRCS
    ${REPO_PATH}/Client.cpp
    ${REPO_PATH}/DisplayDevice.cpp
    ${REPO_PATH}/DispSync.cpp
    ${REPO_PATH}/EventControlThread.cpp
    ${REPO_PATH}/EventThread.cpp
    ${REPO_PATH}/FrameTracker.cpp
    ${REPO_PATH}/Layer.cpp
    ${REPO_PATH}/LayerDim.cpp
    ${REPO_PATH}/MessageQueue.cpp
    ${REPO_PATH}/SurfaceFlinger.cpp
    ${REPO_PATH}/SurfaceFlingerConsumer.cpp
    ${REPO_PATH}/SurfaceTextureLayer.cpp
    ${REPO_PATH}/Transform.cpp
    ${REPO_PATH}/DisplayHardware/FramebufferSurface.cpp
    ${REPO_PATH}/DisplayHardware/HWComposer.cpp
    ${REPO_PATH}/DisplayHardware/PowerHAL.cpp
    ${REPO_PATH}/DisplayHardware/VirtualDisplaySurface.cpp
    ${REPO_PATH}/Effects/Daltonizer.cpp
    ${REPO_PATH}/EventLog/EventLogTags.logtags
    ${REPO_PATH}/EventLog/EventLog.cpp
    ${REPO_PATH}/RenderEngine/Description.cpp
    ${REPO_PATH}/RenderEngine/Mesh.cpp
    ${REPO_PATH}/RenderEngine/Program.cpp
    ${REPO_PATH}/RenderEngine/ProgramCache.cpp
    ${REPO_PATH}/RenderEngine/GLExtensions.cpp
    ${REPO_PATH}/RenderEngine/RenderEngine.cpp
    ${REPO_PATH}/RenderEngine/Texture.cpp
    ${REPO_PATH}/RenderEngine/GLES10RenderEngine.cpp
    ${REPO_PATH}/RenderEngine/GLES11RenderEngine.cpp
    ${REPO_PATH}/RenderEngine/GLES20RenderEngine.cpp
)

set(surfaceflinger_SRCS
    ${REPO_PATH}/main_surfaceflinger.cpp
)

add_library(libsurfaceflinger SHARED ${libsurfaceflinger_SRCS})
set_target_properties(libsurfaceflinger PROPERTIES PREFIX "") # this because we've got both a lib and an executable named surfaceflinger...
target_compile_definitions(libsurfaceflinger
    PRIVATE
    -DANDROID
    -DANDROID_OS
    -DLOG_TAG="SurfaceFlinger"
    -DGL_GLEXT_PROTOTYPES -DEGL_EGLEXT_PROTOTYPES
    -DRUNNING_WITHOUT_SYNC_FRAMEWORK
    -DVSYNC_EVENT_PHASE_OFFSET_NS=0
    -DSF_VSYNC_EVENT_PHASE_OFFSET_NS=0
    -DPRESENT_TIME_OFFSET_FROM_VSYNC_NS=0
)
target_link_libraries(libsurfaceflinger
#     cutils
#     log
#     dl
#     hardware
#     utils
#     EGL
    GLESv1_CM
#     GLESv2
#     binder
#     ui
    gui
    ${QT5CORE32_LIBRARIES}
    ${QT5WIDGETS32_LIBRARIES}
    ${QT5X11EXTRAS32_LIBRARIES}
)
target_include_directories(libsurfaceflinger
    PRIVATE
    ${LIBBINDER_INCLUDES}
    ${LIBLOG_INCLUDES}
    ${LIBHARDWARE_INCLUDES}
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/include
    ${OPENGL_INCLUDES}
    ${QT5CORE32_INCLUDE_DIRS}
    ${QT5WIDGETS32_INCLUDE_DIRS}
    ${QT5X11EXTRAS32_INCLUDE_DIRS}
)

add_executable(surfaceflinger ${surfaceflinger_SRCS})
target_compile_definitions(surfaceflinger
    PRIVATE
    -DLOG_TAG="SurfaceFlinger"
)
target_link_libraries(surfaceflinger
    libsurfaceflinger
#     cutils
#     log
#     binder
#     utils
    ${QT5GUI32_LIBRARIES}
)
target_include_directories(surfaceflinger
    PRIVATE
    ${LIBCUTILS_INCLUDES}
    ${LIBBINDER_INCLUDES}
    ${LIBHARDWARE_INCLUDES}
    ${QT5GUI32_INCLUDE_DIRS}
)


#TESTS

add_executable(surfaceflinger_vsync_test ${REPO_PATH}/tests/vsync/vsync.cpp)
target_link_libraries(surfaceflinger_vsync_test
    libsurfaceflinger
)

target_include_directories(surfaceflinger_vsync_test
    PRIVATE
    ${LIBBINDER_INCLUDES}
    ${LIBLOG_INCLUDES}
    ${LIBHARDWARE_INCLUDES}
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/include
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/opengl/include
)




if(FORCE_32BIT_BUILD)
    set_target_properties(libsurfaceflinger PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    set_target_properties(surfaceflinger PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

install(TARGETS libsurfaceflinger DESTINATION ${ANDROID_LIB_DIR})
install(TARGETS surfaceflinger DESTINATION ${ANDROID_BIN_DIR})
