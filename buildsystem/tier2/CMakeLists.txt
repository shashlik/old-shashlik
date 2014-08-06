cmake_minimum_required(VERSION 2.8)

link_directories(${CMAKE_INSTALL_PREFIX}/lib/
                 ${CMAKE_CURRENT_BINARY_DIR}/libdex/  # For linking dexdump, dexlist and dexgen
 		 )
set(STANDARD_SYS_LIBS dl pthread z resolv ffi)



#add_subdirectory(libbinder)


# ----------------------------------------------------------------
#                             Dalvik


# Set JIT_VM to:
#   false   if you want to run an interpreter (currently necessary on 64 bit systems)
#   true    if you want just in time compilation to assembler
#
# false is the default
set(JIT_VM false)

# vm support libs
add_subdirectory(libdex)

# dalvik vm
add_subdirectory(vm)

# c++ tools
add_subdirectory(dexdump)
add_subdirectory(dexlist)
add_subdirectory(hprof-conv)

if (JIT_VM)
    set(JIT_DEFS -DWITH_JIT -DWITH_JIT_TUNING -DDVM_JMP_TABLE_MTERP=1 -DMTERP_STUB -DARCH_IA32 -DARCH_VARIANT="x86")
    add_subdirectory(gdbjithelper)
    add_subdirectory(dexopt)
    add_subdirectory(dmtracedump)
endif(JIT_VM)

#java tools
#add_subdirectory(dexgen)
#add_subdirectory(dx)
#add_subdirectory(hit)
#add_subdirectory(tools/dexdeps)
