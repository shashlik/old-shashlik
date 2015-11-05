project(libhardware)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/android-libhardware)

set(libhardware_SRCS
    hardware.c
)

set(MODULES_PATH ${REPO_PATH}/modules)

set(gralloc_SRCS
    ${MODULES_PATH}/gralloc/framebuffer.cpp
    ${MODULES_PATH}/gralloc/gralloc.cpp
    ${MODULES_PATH}/gralloc/mapper.cpp
)

set(hwcomposer_SRCS
    ${MODULES_PATH}/hwcomposer/hwcomposer.cpp
)

# set(INTEL_PATH ${GENERAL_SOURCE_PATH}/intel-hwcomposer)
# set(hwcomposerIntel_SRCS
#     ${INTEL_PATH}/common/base/Drm.cpp
#     ${INTEL_PATH}/common/base/HwcLayer.cpp
#     ${INTEL_PATH}/common/base/HwcLayerList.cpp
#     ${INTEL_PATH}/common/base/Hwcomposer.cpp
#     ${INTEL_PATH}/common/base/HwcModule.cpp
#     ${INTEL_PATH}/common/base/DisplayAnalyzer.cpp
#     ${INTEL_PATH}/common/buffers/BufferCache.cpp
#     ${INTEL_PATH}/common/buffers/GraphicBuffer.cpp
#     ${INTEL_PATH}/common/buffers/BufferManager.cpp
#     ${INTEL_PATH}/common/devices/DummyDevice.cpp
#     ${INTEL_PATH}/common/devices/PhysicalDevice.cpp
#     ${INTEL_PATH}/common/devices/PrimaryDevice.cpp
#     ${INTEL_PATH}/common/devices/ExternalDevice.cpp
#     ${INTEL_PATH}/common/observers/UeventObserver.cpp
#     ${INTEL_PATH}/common/observers/VsyncEventObserver.cpp
#     ${INTEL_PATH}/common/observers/SoftVsyncObserver.cpp
#     ${INTEL_PATH}/common/planes/DisplayPlane.cpp
#     ${INTEL_PATH}/common/planes/DisplayPlaneManager.cpp
#     ${INTEL_PATH}/common/utils/Dump.cpp
# 
#     ${INTEL_PATH}/ips/common/BlankControl.cpp
#     ${INTEL_PATH}/ips/common/HdcpControl.cpp
#     ${INTEL_PATH}/ips/common/DrmControl.cpp
#     ${INTEL_PATH}/ips/common/VsyncControl.cpp
#     ${INTEL_PATH}/ips/common/OverlayPlaneBase.cpp
#     ${INTEL_PATH}/ips/common/SpritePlaneBase.cpp
#     ${INTEL_PATH}/ips/common/PixelFormat.cpp
#     ${INTEL_PATH}/ips/common/GrallocBufferBase.cpp
#     ${INTEL_PATH}/ips/common/GrallocBufferMapperBase.cpp
#     ${INTEL_PATH}/ips/common/TTMBufferMapper.cpp
#     ${INTEL_PATH}/ips/common/DrmConfig.cpp
#     ${INTEL_PATH}/ips/common/Wsbm.cpp
#     ${INTEL_PATH}/ips/common/WsbmWrapper.c
#     ${INTEL_PATH}/ips/common/RotationBufferProvider.cpp
# 
#     ${INTEL_PATH}/ips/tangier/TngGrallocBuffer.cpp
#     ${INTEL_PATH}/ips/tangier/TngGrallocBufferMapper.cpp
#     ${INTEL_PATH}/ips/tangier/TngDisplayQuery.cpp
#     ${INTEL_PATH}/ips/tangier/TngDisplayContext.cpp
# 
#     ${INTEL_PATH}/ips/anniedale/AnnPlaneManager.cpp
#     ${INTEL_PATH}/ips/anniedale/AnnOverlayPlane.cpp
#     ${INTEL_PATH}/ips/anniedale/AnnRGBPlane.cpp
#     ${INTEL_PATH}/ips/anniedale/AnnCursorPlane.cpp
#     ${INTEL_PATH}/ips/anniedale/PlaneCapabilities.cpp
# 
#     ${INTEL_PATH}/platforms/merrifield_plus/PlatfBufferManager.cpp
#     ${INTEL_PATH}/platforms/merrifield_plus/PlatfPrimaryDevice.cpp
#     ${INTEL_PATH}/platforms/merrifield_plus/PlatfExternalDevice.cpp
#     ${INTEL_PATH}/platforms/merrifield_plus/PlatfHwcomposer.cpp
# )

include_directories(
                    ${REPO_PATH}/include
                    ${LIBCUTILS_INCLUDES}
                    ${LIBLOG_INCLUDES}
)

add_library(hardware SHARED ${libhardware_SRCS})
target_link_libraries(hardware cutils log dl)

add_library(gralloc.default SHARED ${gralloc_SRCS})
target_compile_definitions(gralloc.default PUBLIC -DLOG_TAG=\"gralloc\")
target_link_libraries(gralloc.default log cutils)

# add_library(hwcomposer.default SHARED ${hwcomposer_SRCS})
# target_compile_definitions(hwcomposer.default PUBLIC -DLOG_TAG=\"hwcomposer\")
# target_link_libraries(hwcomposer.default log EGL)
# target_include_directories(hwcomposer.default PRIVATE ${OPENGL_INCLUDES})

# add_library(hwcomposer.intel SHARED ${hwcomposerIntel_SRCS})
# target_compile_definitions(hwcomposer.intel PRIVATE -DINTEL_SUPPORT_HDMI_PRIMARY)
# target_link_libraries(hwcomposer.intel
#     log
#     cutils
#     drm
#     wsbm
#     utils
#     hardware
#     va
#     va-tpi
#     va-x11
# #     va-android
#     sync
# )
# target_include_directories(hwcomposer.intel
#     PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${INTEL_PATH}
#     ${INTEL_PATH}/include/pvr/hal
#     ${INTEL_PATH}/include
#     ${DRM_INCLUDE_DIRS}
#     ${GENERAL_SOURCE_PATH}/intel-libwsbm/src
#     ${CMAKE_SOURCE_DIR}/src/deps/libwsbm/drm
#     ${ANDROID_CORE_PATH}/include
# )

# because otherwise the module loader looks for the wrong file
set_target_properties(gralloc.default PROPERTIES PREFIX "")
# set_target_properties(hwcomposer.default PROPERTIES PREFIX "")
# set_target_properties(hwcomposer.intel PROPERTIES PREFIX "")

if(FORCE_32BIT_BUILD)
    set_target_properties(hardware PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    set_target_properties(gralloc.default PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
#     set_target_properties(hwcomposer.default PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
#     set_target_properties(hwcomposer.intel PROPERTIES COMPILE_FLAGS "-m32 -Werror" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

install(TARGETS hardware DESTINATION ${ANDROID_LIB_DIR})
install(TARGETS gralloc.default DESTINATION ${ANDROID_LIB_DIR}/hw)
# install(TARGETS hwcomposer.default DESTINATION ${ANDROID_LIB_DIR}/hw)
# install(TARGETS hwcomposer.intel DESTINATION ${ANDROID_LIB_DIR}/hw)
