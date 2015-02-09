add_subdirectory(android-core-headers)
add_subdirectory(android-libcore-headers)

# used for certain minor bits provided by bionic's bsd style imports
add_subdirectory(stripped_bionic)

# tier1 libraries
add_subdirectory(libcorkscrew)    # android-core
add_subdirectory(liblog)          # android-core
add_subdirectory(libutils)        # android-core
add_subdirectory(libcutils)       # android-core
add_subdirectory(libpixelflinger) # android-core

add_subdirectory(libnativehelper) # native-helper

add_subdirectory(safe-iop)        # safe-iop

add_subdirectory(skia)            # skia graphics library

add_subdirectory(libandroidfw)    # frameworks-base

# ----------------------------------------------------------------
#                             Dalvik

# vm support libraries and tools
add_subdirectory(libdex)
add_subdirectory(dx)

# dalvik vm
add_subdirectory(vm)
add_subdirectory(javalibrary)

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
