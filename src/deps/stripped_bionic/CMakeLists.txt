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
)

add_library(stripped_bionic SHARED ${stripped_bionic_SRCS})
install(TARGETS stripped_bionic DESTINATION ${ANDROID_LIB_DIR})
