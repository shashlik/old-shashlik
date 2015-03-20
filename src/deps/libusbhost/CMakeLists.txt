project(libusbhost)

set(usbhost_SRCS
    ${ANDROID_CORE_PATH}/libusbhost/usbhost.c
)

add_library(usbhost SHARED ${usbhost_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(usbhost PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(usbhost cutils)
target_include_directories(usbhost
    PUBLIC
    ${ANDROID_CORE_PATH}/include
    )
install(TARGETS usbhost DESTINATION ${ANDROID_LIB_DIR})
