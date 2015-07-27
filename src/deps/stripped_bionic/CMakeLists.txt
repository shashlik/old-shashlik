project(stripped_bionic)

# This library provides a set of functions normally provided by the bionic libraries.
# The reason we have them split out here is that we explicitly want to use the libc
# and so on which is already on the system, rather than the mashup of bionic's.
# Some functionality is required (such as e.g. the bsd style strl* functions), so
# we have this to provide that.

set(BIONIC_LIBC_SRC_DIR ${GENERAL_SOURCE_PATH}/bionic/libc)

set(stripped_bionic_SRCS
    ${BIONIC_LIBC_SRC_DIR}/string/strlcat.c
    ${BIONIC_LIBC_SRC_DIR}/string/strlcpy.c
    ${BIONIC_LIBC_SRC_DIR}/tzcode/strftime.c
#     ${BIONIC_LIBC_SRC_DIR}/tzcode/localtime.c
    malloc_debug_common.c
    android_set_abort_message.cpp
    time64.c
    bionic_time.c
)

enable_language(ASM)
set(assembler_SRCS
#     ${BIONIC_LIBC_SRC_DIR}/arch-x86/syscalls/__mmap2.S
)
set_property(SOURCE ${assembler_SRCS} PROPERTY LANGUAGE ASM)

add_library(stripped_bionic SHARED ${stripped_bionic_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(stripped_bionic PROPERTIES COMPILE_FLAGS "-m32 -std=c99" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_include_directories(stripped_bionic
    PRIVATE
    ${BIONIC_LIBC_SRC_DIR}/arch-x86/include/
    ${LIBLOG_INCLUDES}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

install(TARGETS stripped_bionic DESTINATION ${ANDROID_LIB_DIR})

install(FILES ${BIONIC_LIBC_SRC_DIR}/zoneinfo/tzdata DESTINATION ${ANDROID_ROOT}/system/usr/share/zoneinfo)
