project(libandroid_servers)

set(REPO_PATH ${ANDROID_FRAMEWORKS_BASE}/services/jni)

set(android_servers_SRCS
    ${REPO_PATH}/com_android_server_AlarmManagerService.cpp
    ${REPO_PATH}/com_android_server_AssetAtlasService.cpp
    ${REPO_PATH}/com_android_server_ConsumerIrService.cpp
    ${REPO_PATH}/com_android_server_input_InputApplicationHandle.cpp
    ${REPO_PATH}/com_android_server_input_InputManagerService.cpp
    ${REPO_PATH}/com_android_server_input_InputWindowHandle.cpp
    ${REPO_PATH}/com_android_server_LightsService.cpp
    ${REPO_PATH}/com_android_server_power_PowerManagerService.cpp
#     ${REPO_PATH}/com_android_server_SerialService.cpp
    ${REPO_PATH}/com_android_server_SystemServer.cpp
#     ${REPO_PATH}/com_android_server_UsbDeviceManager.cpp
#     ${REPO_PATH}/com_android_server_UsbHostManager.cpp
    ${REPO_PATH}/com_android_server_VibratorService.cpp
#     ${REPO_PATH}/com_android_server_location_GpsLocationProvider.cpp
#     ${REPO_PATH}/com_android_server_location_FlpHardwareProvider.cpp
#     ${REPO_PATH}/com_android_server_connectivity_Vpn.cpp
    ${REPO_PATH}/onload.cpp
)

add_library(android_servers SHARED ${android_servers_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(android_servers PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_compile_definitions(android_servers
    PRIVATE
    -DGL_GLEXT_PROTOTYPES -DEGL_EGLEXT_PROTOTYPES
)
target_include_directories(android_servers
    PRIVATE
    ${LIBNATIVEHELPER_INCLUDEDIRS}
    ${OPENGL_INCLUDES}
    ${ANDROID_FRAMEWORKS_BASE}/include
    ${ANDROID_FRAMEWORKS_BASE}/services
    ${ANDROID_FRAMEWORKS_BASE}/core/jni
    ${LIBUI_INCLUDES}
    ${LIBHARDWARE_INCLUDES}
    ${SKIA_INCLUDES}
)
target_link_libraries(android_servers
#     android_runtime
    androidfw
#     binder
#     cutils
#     log
#     hardware
#     hardware_legacy
    nativehelper
#     utils
#     ui
    input
    inputservice
#     sensorservice
    skia
    gui
    usbhost
#     suspend
#     EGL
    GLESv2
    waylandthings
)
install(TARGETS android_servers DESTINATION ${ANDROID_LIB_DIR})
