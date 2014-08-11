# necessary to note that we have endian.h, which we do on all systems we target
# otherwise the android code goes and redefines it all on us. not so great
add_definitions(-DHAVE_ENDIAN_H)

add_subdirectory(deps)
add_subdirectory(libs)
add_subdirectory(propertiesd)
add_subdirectory(launcher)
