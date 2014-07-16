cmake_minimum_required(VERSION 2.8)

link_directories(${CMAKE_INSTALL_PREFIX}/lib/)
set(STANDARD_SYS_LIBS dl pthread z resolv)
include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include)

# vm support libs
add_subdirectory(libdex)
add_subdirectory(libhardware)

# dalvik vm
add_subdirectory(vm)

# c++ tools
add_subdirectory(dexdump)
add_subdirectory(dexlist)
add_subdirectory(dexopt)
add_subdirectory(dmtracedump)
add_subdirectory(gdbjithelper)
add_subdirectory(hprof-conv)

#java tools
#add_subdirectory(dexgen)
#add_subdirectory(dx)
#add_subdirectory(hit)
#add_subdirectory(tools/dexdeps)
