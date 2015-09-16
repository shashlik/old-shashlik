project(cutils)

set(REPO_PATH ${ANDROID_CORE_PATH})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${LIBCUTILS_INCLUDES}
)

add_definitions(-D_GNU_SOURCE
                -DHAVE_LINUX_LOCAL_SOCKET_NAMESPACE
                -DANDROID_SMP=1
                -DHAVE_SYSTEM_PROPERTY_SERVER
)
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../android-core)

set(cutils_SRCS
    ${REPO_PATH}/libcutils/android_reboot.c
    #${REPO_PATH}/libcutils/ashmem-dev.c
    ${REPO_PATH}/libcutils/ashmem-host.c
#     ${REPO_PATH}/libcutils/atomic.c # ARM only sources, apparently...
    ${REPO_PATH}/libcutils/config_utils.c
    ${REPO_PATH}/libcutils/cpu_info.c
    ${REPO_PATH}/libcutils/debugger.c
    ${REPO_PATH}/libcutils/dir_hash.c
    #    ${REPO_PATH}/libcutils/dlmalloc_stubs.c
    ${REPO_PATH}/libcutils/fs.c
    ${REPO_PATH}/libcutils/hashmap.c
    ${REPO_PATH}/libcutils/iosched_policy.c
    ${REPO_PATH}/libcutils/klog.c
    ${REPO_PATH}/libcutils/list.c
    ${REPO_PATH}/libcutils/load_file.c
    ${REPO_PATH}/libcutils/memory.c
    ${REPO_PATH}/libcutils/multiuser.c
    ${REPO_PATH}/libcutils/native_handle.c
    ${REPO_PATH}/libcutils/open_memstream.c
    #    ${REPO_PATH}/libcutils/partition_utils.c
    ${REPO_PATH}/libcutils/process_name.c
    ${REPO_PATH}/libcutils/properties.c
    ${REPO_PATH}/libcutils/qtaguid.c
    ${REPO_PATH}/libcutils/record_stream.c
    ${REPO_PATH}/libcutils/sched_policy.c
    ${REPO_PATH}/libcutils/sha1.c
    ${REPO_PATH}/libcutils/socket_inaddr_any_server.c
    ${REPO_PATH}/libcutils/socket_local_client.c
    ${REPO_PATH}/libcutils/socket_local_server.c
    ${REPO_PATH}/libcutils/socket_loopback_client.c
    ${REPO_PATH}/libcutils/socket_loopback_server.c
    ${REPO_PATH}/libcutils/socket_network_client.c
    ${REPO_PATH}/libcutils/sockets.c
    ${REPO_PATH}/libcutils/strdup16to8.c
    ${REPO_PATH}/libcutils/strdup8to16.c
    ${REPO_PATH}/libcutils/str_parms.c
    ${REPO_PATH}/libcutils/threads.c
    ${REPO_PATH}/libcutils/trace.c
    ${REPO_PATH}/libcutils/uevent.c
)

set(cutils_HEADERS
    ${REPO_PATH}/include/cutils/android_reboot.h
    ${REPO_PATH}/include/cutils/aref.h
    ${REPO_PATH}/include/cutils/ashmem.h
    ${REPO_PATH}/include/cutils/atomic-arm.h
    ${REPO_PATH}/include/cutils/atomic.h
    ${REPO_PATH}/include/cutils/atomic-inline.h
    ${REPO_PATH}/include/cutils/atomic-mips.h
    ${REPO_PATH}/include/cutils/atomic-x86.h
    ${REPO_PATH}/include/cutils/bitops.h
    ${REPO_PATH}/include/cutils/compiler.h
    ${REPO_PATH}/include/cutils/config_utils.h
    ${REPO_PATH}/include/cutils/cpu_info.h
    ${REPO_PATH}/include/cutils/debugger.h
    ${REPO_PATH}/include/cutils/dir_hash.h
    ${REPO_PATH}/include/cutils/fs.h
    ${REPO_PATH}/include/cutils/hashmap.h
    ${REPO_PATH}/include/cutils/iosched_policy.h
    ${REPO_PATH}/include/cutils/jstring.h
    ${REPO_PATH}/include/cutils/klog.h
    ${REPO_PATH}/include/cutils/list.h
    ${REPO_PATH}/include/cutils/log.h
    ${REPO_PATH}/include/cutils/memory.h
    ${REPO_PATH}/include/cutils/misc.h
    ${REPO_PATH}/include/cutils/multiuser.h
    ${REPO_PATH}/include/cutils/native_handle.h
    ${REPO_PATH}/include/cutils/open_memstream.h
    #    ${REPO_PATH}/include/cutils/partition_utils.h
    ${REPO_PATH}/include/cutils/process_name.h
    ${REPO_PATH}/include/cutils/properties.h
    ${REPO_PATH}/include/cutils/qtaguid.h
    ${REPO_PATH}/include/cutils/record_stream.h
    ${REPO_PATH}/include/cutils/sched_policy.h
    ${REPO_PATH}/include/cutils/sockets.h
    ${REPO_PATH}/include/cutils/str_parms.h
    ${REPO_PATH}/include/cutils/threads.h
    ${REPO_PATH}/include/cutils/trace.h
    ${REPO_PATH}/include/cutils/tztime.h
    ${REPO_PATH}/include/cutils/uevent.h
)

add_library(cutils SHARED ${cutils_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(cutils PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(cutils pthread resolv log)

install(TARGETS cutils DESTINATION ${ANDROID_LIB_DIR})
install(FILES
        ${cutils_HEADERS}
        DESTINATION include/cutils)
#install(FILES ${REPO_PATH}/include/sys/system_properties.h DESTINATION include/sys)
