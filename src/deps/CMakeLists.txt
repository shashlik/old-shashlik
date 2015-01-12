set(STANDARD_SYS_LIBS dl pthread z resolv ffi)


# necessary to note that we have endian.h, which we do on all systems we target
# otherwise the android code goes and redefines it all on us. not so great
add_definitions(-DHAVE_ENDIAN_H)

add_subdirectory(android-core-headers)
add_subdirectory(android-libcore-headers)

# tier1 libraries
add_subdirectory(libcorkscrew)    # android-core
add_subdirectory(liblog)          # android-core
add_subdirectory(libutils)        # android-core
add_subdirectory(libcutils)       # android-core
add_subdirectory(libpixelflinger) # android-core

add_subdirectory(libnativehelper) # native-helper

add_subdirectory(safe-iop)        # safe-iop

# ----------------------------------------------------------------
#                             Dalvik


# Set JIT_VM to:
#   false   if you want to run an interpreter (currently necessary on 64 bit systems)
#   true    if you want just in time compilation to assembler
#
# false is the default
#
# FIXME: Should this move to the top CMakeList.txt?
#        Or should we perhaps have a test for 32/64 bit systems?
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
# FIXME: These can only be built on a 32 bit system.  Somebody with such a
#        system will have to move them from buildsystem/tier2.

##    add_subdirectory(gdbjithelper)
##    add_subdirectory(dexopt)
##    add_subdirectory(dmtracedump)
endif(JIT_VM)

#java tools
#add_subdirectory(dexgen)
#add_subdirectory(dx)
#add_subdirectory(hit)
#add_subdirectory(tools/dexdeps)


# ----------------------------------------------------------------
#                             Other stuff


add_subdirectory(libbinder)
