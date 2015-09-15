project(adb)

add_definitions(
    -O2
    -g
    -Wall
    -Wno-unused-parameter
)

set(REPO_PATH ${ANDROID_CORE_PATH}/adb)

set(adbd_SRCS
    ${REPO_PATH}/adb.c
    ${REPO_PATH}/backup_service.c
    ${REPO_PATH}/fdevent.c
    ${REPO_PATH}/transport.c
    ${REPO_PATH}/transport_local.c
    ${REPO_PATH}/transport_usb.c
    ${REPO_PATH}/adb_auth_client.c
    ${REPO_PATH}/sockets.c
    ${REPO_PATH}/services.c
    ${REPO_PATH}/file_sync_service.c
    ${REPO_PATH}/jdwp_service.c
    ${REPO_PATH}/framebuffer_service.c
    ${REPO_PATH}/remount_service.c
    ${REPO_PATH}/usb_linux_client.c
    ${REPO_PATH}/log_service.c
)

set(adb_SRCS
    ${REPO_PATH}/adb.c
    ${REPO_PATH}/console.c
    ${REPO_PATH}/transport.c
    ${REPO_PATH}/transport_local.c
    ${REPO_PATH}/transport_usb.c
    ${REPO_PATH}/commandline.c
    ${REPO_PATH}/adb_client.c
    ${REPO_PATH}/adb_auth_host.c
    ${REPO_PATH}/sockets.c
    ${REPO_PATH}/services.c
    ${REPO_PATH}/file_sync_client.c
    ${REPO_PATH}/get_my_path_linux.c
    ${REPO_PATH}/usb_linux.c
    ${REPO_PATH}/usb_vendors.c
    ${REPO_PATH}/fdevent.c
)

add_executable(adbd ${adbd_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(adbd PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_compile_definitions(adbd
    PRIVATE
    -DHAVE_FORKEXEC
    -DADB_HOST=0
    -D_XOPEN_SOURCE -D_GNU_SOURCE
)
target_include_directories(adbd
    PRIVATE
    ${REPO_PATH}
    ${ANDROID_CORE_PATH}/include
    ${LIBHARDWARE_INCLUDES}
)
target_link_libraries(adbd
    dl
    log
    cutils
    crypto
)

add_executable(adb ${adb_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(adb PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_compile_definitions(adb
    PRIVATE
    -DHAVE_FORKEXEC
    -DADB_HOST=1
    -DADB_HOST_ON_TARGET=1
    -D_XOPEN_SOURCE
    -D_GNU_SOURCE
)
target_include_directories(adb
    PRIVATE
    ${REPO_PATH}
    ${ANDROID_CORE_PATH}/include
    ${LIBHARDWARE_INCLUDES}
)
target_link_libraries(adb
    rt dl pthread z
    zipfile cutils log
    crypto
)

install(TARGETS adb adbd DESTINATION ${ANDROID_BIN_DIR})
