project(sync)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/android-core/libsync)

set(sync_SRCS
    ${REPO_PATH}/sync.c
)

add_library(sync SHARED ${sync_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(sync PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(sync
    log
)
target_include_directories(sync
    PRIVATE
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/include
    ${GENERAL_SOURCE_PATH}/android-core/include
    ${GENERAL_SOURCE_PATH}/bionic/libc/kernel/common
    ${GENERAL_SOURCE_PATH}/android-libhardware/include
)

install(TARGETS sync DESTINATION ${ANDROID_LIB_DIR})
