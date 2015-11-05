project(ui)

set(REPO_PATH ${ANDROID_FRAMEWORKS_NATIVE_PATH}/libs/ui)

set(ui_SRCS
    ${REPO_PATH}/Fence.cpp
    ${REPO_PATH}/FramebufferNativeWindow.cpp
    ${REPO_PATH}/GraphicBuffer.cpp
    ${REPO_PATH}/GraphicBufferAllocator.cpp
    ${REPO_PATH}/GraphicBufferMapper.cpp
    ${REPO_PATH}/PixelFormat.cpp
    ${REPO_PATH}/Rect.cpp
    ${REPO_PATH}/Region.cpp
    ${REPO_PATH}/UiConfig.cpp
)

add_library(ui SHARED ${ui_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(ui PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(ui
    hardware utils sync
)
target_include_directories(ui
    PUBLIC
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/include
    PRIVATE
    ${GENERAL_SOURCE_PATH}/android-core/include
#     ${GENERAL_SOURCE_PATH}/bionic/libc/kernel/common
    ${GENERAL_SOURCE_PATH}/android-libhardware/include
)

install(TARGETS ui DESTINATION ${ANDROID_LIB_DIR})
