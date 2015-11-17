project(gui)

set(REPO_PATH ${ANDROID_FRAMEWORKS_NATIVE_PATH}/libs/gui)

set(gui_SRCS
    ${REPO_PATH}/IGraphicBufferConsumer.cpp
    ${REPO_PATH}/IConsumerListener.cpp
    ${REPO_PATH}/BitTube.cpp
    ${REPO_PATH}/BufferItemConsumer.cpp
    ${REPO_PATH}/BufferQueue.cpp
    ${REPO_PATH}/ConsumerBase.cpp
    ${REPO_PATH}/CpuConsumer.cpp
    ${REPO_PATH}/DisplayEventReceiver.cpp
    ${REPO_PATH}/GLConsumer.cpp
    ${REPO_PATH}/GraphicBufferAlloc.cpp
    ${REPO_PATH}/GuiConfig.cpp
    ${REPO_PATH}/IDisplayEventConnection.cpp
    ${REPO_PATH}/IGraphicBufferAlloc.cpp
    ${REPO_PATH}/IGraphicBufferProducer.cpp
    ${REPO_PATH}/ISensorEventConnection.cpp
    ${REPO_PATH}/ISensorServer.cpp
    ${REPO_PATH}/ISurfaceComposer.cpp
    ${REPO_PATH}/ISurfaceComposerClient.cpp
    ${REPO_PATH}/LayerState.cpp
    ${REPO_PATH}/Sensor.cpp
    ${REPO_PATH}/SensorEventQueue.cpp
    ${REPO_PATH}/SensorManager.cpp
    ${REPO_PATH}/Surface.cpp
    ${REPO_PATH}/SurfaceControl.cpp
    ${REPO_PATH}/SurfaceComposerClient.cpp
    ${REPO_PATH}/SyncFeatures.cpp
)

add_library(gui SHARED ${gui_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(gui PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(gui
    GLESv2 EGL GLESv1_CM ${DRM_LIBRARIES} ui binder  hwui epoxy
)
target_compile_definitions(gui
    PRIVATE
    -DHAVE_ANDROID_OS
    -DGL_GLEXT_PROTOTYPES -DEGL_EGLEXT_PROTOTYPES
)
target_include_directories(gui
    PRIVATE
    ${LIBUTILS_INCLUDES}
    ${LIBBINDER_INCLUDES}
    ${GENERAL_SOURCE_PATH}/android-libhardware/include
    ${OPENGL_INCLUDES}
)
install(TARGETS gui DESTINATION ${ANDROID_LIB_DIR})
