project(installd)

set(REPO_PATH ${ANDROID_FRAMEWORKS_NATIVE_PATH}/cmds/installd)

set(installd_SRCS
    ${REPO_PATH}/commands.c
    ${REPO_PATH}/utils.c
    ${REPO_PATH}/installd.c

    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/libs/diskusage/dirsize.c
)

add_executable(installd ${installd_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(installd PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(installd
    cutils
    log
)
target_include_directories(installd
    PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
    ${LIBCUTILS_INCLUDES}
    ${LIBLOG_INCLUDES}
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/include
    ${ANDROID_CORE_PATH}/include
)
install(TARGETS installd DESTINATION ${ANDROID_BIN_DIR})
