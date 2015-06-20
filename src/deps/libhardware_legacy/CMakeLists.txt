project(libhardware_legacy)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/libhardware_legacy)

set(hardware_legacy_SRCS
    ${REPO_PATH}/power/power.c
    ${REPO_PATH}/uevent/uevent.c
#     ${REPO_PATH}/vibrator/vibrator.c
#     ${REPO_PATH}/wifi/wifi.c
#     ${REPO_PATH}/qemu/qemu.c
#     ${REPO_PATH}/qemu_tracing/qemu_tracing.c
)

add_library(hardware_legacy SHARED ${hardware_legacy_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(hardware_legacy PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
# target_compile_definitions(hardware_legacy
#     PUBLIC
#     -DQEMU_HARDWARE
# )
target_include_directories(hardware_legacy
    PUBLIC
    ${REPO_PATH}/include
    ${LIBLOG_INCLUDES}
    ${LIBCUTILS_INCLUDES}
)
target_link_libraries(hardware_legacy
    cutils
    log
    dl
)

install(TARGETS hardware_legacy DESTINATION ${ANDROID_LIB_DIR})
