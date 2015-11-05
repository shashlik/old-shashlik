project(memtrack)

set(REPO_PATH ${ANDROID_CORE_PATH}/libmemtrack)

set(memtrack_SRCS
    ${REPO_PATH}/memtrack.c
)

add_library(memtrack SHARED ${memtrack_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(memtrack PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(memtrack
    hardware
)
target_include_directories(memtrack
    PRIVATE
    ${LIBLOG_INCLUDES}
    ${GENERAL_SOURCE_PATH}/bionic/libc/kernel/common
    ${GENERAL_SOURCE_PATH}/android-core/include
    ${GENERAL_SOURCE_PATH}/android-libhardware/include
)
add_definitions(-Wall -Werror)
install(TARGETS memtrack DESTINATION ${ANDROID_LIB_DIR})
