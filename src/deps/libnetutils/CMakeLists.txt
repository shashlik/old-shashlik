project(netutils)

set(REPO_PATH ${ANDROID_CORE_PATH}/libnetutils)

set(netutils_SRCS
    ${REPO_PATH}/dhcpclient.c
    ${REPO_PATH}/dhcpmsg.c
    ${REPO_PATH}/dhcp_utils.c
    ${REPO_PATH}/ifc_utils.c
    ${REPO_PATH}/packet.c
)

add_library(netutils SHARED ${netutils_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(netutils PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_compile_definitions(netutils
    PRIVATE
    -DANDROID
)
target_link_libraries(netutils
    cutils log
)
target_include_directories(netutils
    PRIVATE
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/include
    ${GENERAL_SOURCE_PATH}/android-core/include
)

install(TARGETS netutils DESTINATION ${ANDROID_LIB_DIR})
