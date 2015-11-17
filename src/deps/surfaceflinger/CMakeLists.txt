project(surfaceflinger)

find_package(Qt5Core) # Yes, this is a hack. We need the 32bit libraries
find_package(Qt5Gui) # Yes, this is a hack. We need the 32bit libraries
find_package(Qt5Widgets) # Yes, this is a hack. We need the 32bit libraries
find_package(Qt5X11Extras) # Yes, this is a hack. We need the 32bit libraries
find_package(KF5Wayland REQUIRED)
find_package(Wayland COMPONENTS Client Egl Cursor REQUIRED)

set(REPO_PATH ${ANDROID_FRAMEWORKS_NATIVE_PATH}/services/surfaceflinger)

add_definitions(-fvisibility=hidden -fpermissive -fPIC)

set(waylandthings_SRCS
    WaylandClient.cpp
    WaylandWindow.cpp
)

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

add_library(waylandthings STATIC ${waylandthings_SRCS})

target_link_libraries(waylandthings
    log
    KF5WaylandClient
    ${Wayland_LIBRARIES}
)

target_compile_definitions(waylandthings
    PUBLIC
    -DWL_EGL_PLATFORM
    ${Wayland_DEFINITIONS}
)
target_include_directories(waylandthings
    PRIVATE
    ${CMAKE_CURRENT_SRC_DIR}
    ${LIBLOG_INCLUDES}
    PUBLIC
    ${OPENGL_INCLUDES}
    /usr/include/KF5
    /usr/include/KF5/KWayland
    ${Wayland_INCLUDE_DIRS}
    ${QT5GUI32_INCLUDE_DIRS}
    ${QT5CORE32_INCLUDE_DIRS}
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
    PUBLIC
    -DWL_EGL_PLATFORM
    ${Wayland_DEFINITIONS}
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
    hwui
    epoxy
    ${Wayland_LIBRARIES}
    KF5WaylandClient
    ${QT5CORE32_LIBRARIES}
    ${QT5GUI32_LIBRARIES}
    waylandthings
)
target_include_directories(libsurfaceflinger
    PRIVATE
    ${CMAKE_CURRENT_SRC_DIR}
    ${LIBBINDER_INCLUDES}
    ${LIBLOG_INCLUDES}
    ${LIBHARDWARE_INCLUDES}
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/include
    ${OPENGL_INCLUDES}
    ${Wayland_INCLUDE_DIRS}
    /usr/include/KF5/KWayland
    /usr/include/KF5
    ${QT5CORE32_INCLUDE_DIRS}
    ${QT5GUI32_INCLUDE_DIRS}
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
#     ${QT5GUI32_LIBRARIES}
    ${QT5CORE32_LIBRARIES}
)
target_include_directories(surfaceflinger
    PRIVATE
    ${LIBCUTILS_INCLUDES}
    ${LIBBINDER_INCLUDES}
    ${LIBHARDWARE_INCLUDES}
#     ${QT5GUI32_INCLUDE_DIRS}
    ${QT5CORE32_INCLUDE_DIRS}
)

if(FORCE_32BIT_BUILD)
    set_target_properties(waylandthings PROPERTIES COMPILE_FLAGS "-m32 -std=c++11" LINK_FLAGS "-m32")
    set_target_properties(libsurfaceflinger PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    set_target_properties(surfaceflinger PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

install(TARGETS libsurfaceflinger DESTINATION ${ANDROID_LIB_DIR})
install(TARGETS surfaceflinger DESTINATION ${ANDROID_BIN_DIR})
