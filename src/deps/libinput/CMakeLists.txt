project(input)

set(REPO_PATH ${ANDROID_FRAMEWORKS_NATIVE_PATH}/libs/input)

set(input_SRCS
    ${REPO_PATH}/Input.cpp
    ${REPO_PATH}/InputDevice.cpp
    ${REPO_PATH}/Keyboard.cpp
    ${REPO_PATH}/KeyCharacterMap.cpp
    ${REPO_PATH}/KeyLayoutMap.cpp
    ${REPO_PATH}/VirtualKeyMap.cpp
    # device sources
    ${REPO_PATH}/InputTransport.cpp
    ${REPO_PATH}/VelocityControl.cpp
    ${REPO_PATH}/VelocityTracker.cpp
)

add_library(input SHARED ${input_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(input PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(input
#     log
#     cutils
#     utils
    binder
)
target_include_directories(input
    PRIVATE
    ${LIBBINDER_INCLUDES}
    ${LIBUTILS_INCLUDES}
    ${LIBCUTILS_INCLUDES}
)
target_compile_definitions(input
    PRIVATE
    -DHAVE_ANDROID_OS
)

install(TARGETS input DESTINATION ${ANDROID_LIB_DIR})
