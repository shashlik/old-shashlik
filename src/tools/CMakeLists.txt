# necessary to note that we have endian.h, which we do on all systems we target
# otherwise the android code goes and redefines it all on us. not so great
add_definitions(-DHAVE_ENDIAN_H)

# c++ tools
add_subdirectory(dexdump)
add_subdirectory(dexlist)
add_subdirectory(hprof-conv)

add_subdirectory(dexopt)

if (JIT_VM)
    set(JIT_DEFS -DWITH_JIT -DWITH_JIT_TUNING -DDVM_JMP_TABLE_MTERP=1 -DMTERP_STUB -DARCH_IA32 -DARCH_VARIANT="x86")
    add_subdirectory(gdbjithelper)
    add_subdirectory(dmtracedump)
endif(JIT_VM)
