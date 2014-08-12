cmake_minimum_required(VERSION 2.8)

# necessary to note that we have endian.h, which we do on all systems we target
# otherwise the android code goes and redefines it all on us. not so great
add_definitions(-DHAVE_ENDIAN_H)

add_subdirectory(android-core-headers)
add_subdirectory(android-libcore-headers)
add_subdirectory(libcorkscrew)
add_subdirectory(libcutils)
add_subdirectory(liblog)
add_subdirectory(libutils)
add_subdirectory(safe-iop)
add_subdirectory(libnativehelper)
add_subdirectory(libpixelflinger)
