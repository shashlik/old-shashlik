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
add_subdirectory(libjni)
add_subdirectory(libdex)
add_subdirectory(dx)
add_subdirectory(aidl) # must be before the java libraries, as it is used to create the interfaces

# dalvik vm
add_subdirectory(vm)
add_subdirectory(javalibrary-core)
add_subdirectory(javalibrary-frameworks)
add_subdirectory(libjavacore)

#java tools
#add_subdirectory(dexgen)
#add_subdirectory(hit)
#add_subdirectory(tools/dexdeps)


# ----------------------------------------------------------------
#                             Other stuff


add_subdirectory(libbinder)
