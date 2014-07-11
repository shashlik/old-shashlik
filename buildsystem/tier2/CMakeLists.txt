cmake_minimum_required(VERSION 2.8)

link_directories(${CMAKE_INSTALL_PREFIX}/lib/)
set(STANDARD_SYS_LIBS dl pthread z resolv)

add_subdirectory(vm)
add_subdirectory(libdex)
add_subdirectory(dexdump)
