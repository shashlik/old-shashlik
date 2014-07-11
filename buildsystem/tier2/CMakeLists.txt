cmake_minimum_required(VERSION 2.8)

link_directories(${CMAKE_INSTALL_PREFIX}/lib/)

add_subdirectory(vm)
add_subdirectory(libdex)
add_subdirectory(dexdump)
