project(libhardware)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/libhardware)

set(libhardware_SRCS
    ${REPO_PATH}/hardware.c
)

set(MODULES_PATH ${REPO_PATH}/modules)

set(gralloc_SRCS
    ${MODULES_PATH}/gralloc/framebuffer.cpp
    ${MODULES_PATH}/gralloc/gralloc.cpp
    ${MODULES_PATH}/gralloc/mapper.cpp
)

include_directories(
                    ${REPO_PATH}/include
                    ${LIBCUTILS_INCLUDES}
                    ${LIBLOG_INCLUDES}
)

add_library(hardware SHARED ${libhardware_SRCS})
target_link_libraries(hardware cutils log dl)

add_library(gralloc.default SHARED ${gralloc_SRCS})
target_compile_definitions(gralloc.default PUBLIC -DLOG_TAG=\"gralloc\")
target_link_libraries(gralloc.default log cutils)

if(FORCE_32BIT_BUILD)
    set_target_properties(hardware PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    set_target_properties(gralloc.default PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

install(TARGETS hardware DESTINATION ${ANDROID_LIB_DIR})
install(TARGETS gralloc.default DESTINATION ${ANDROID_LIB_DIR}/hw)
