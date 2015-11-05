project(libinputservice)

set(REPO_PATH ${ANDROID_FRAMEWORKS_BASE}/services/input)

set(inputservice_SRCS
    ${REPO_PATH}/EventHub.cpp
    ${REPO_PATH}/InputApplication.cpp
    ${REPO_PATH}/InputDispatcher.cpp
    ${REPO_PATH}/InputListener.cpp
    ${REPO_PATH}/InputManager.cpp
    ${REPO_PATH}/InputReader.cpp
    ${REPO_PATH}/InputWindow.cpp
    ${REPO_PATH}/PointerController.cpp
    ${REPO_PATH}/SpriteController.cpp

    ${ANDROID_CORE_PATH}/libcutils/sha1.c
)

add_library(inputservice SHARED ${inputservice_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(inputservice PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_include_directories(inputservice
    PRIVATE
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/include
    ${ANDROID_FRAMEWORKS_BASE}/include
    ${LIBHARDWARE_INCLUDES}
    ${LIBUTILS_INCLUDES}
    ${LIBBINDER_INCLUDES}
    ${ANDROID_CORE_PATH}/libcutils/ # for sha1.h
    ${SKIA_INCLUDES}
)
target_link_libraries(inputservice
    PRIVATE
    input
    hardware_legacy
)

install(TARGETS inputservice DESTINATION ${ANDROID_LIB_DIR})
