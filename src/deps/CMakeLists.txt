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
add_subdirectory(libusbhost)      # android-core
add_subdirectory(libzipfile)      # android-core

add_subdirectory(libnativehelper) # native-helper

add_subdirectory(safe-iop)        # safe-iop

add_subdirectory(skia)            # skia graphics library
add_subdirectory(openssl)         # openssl secure socket layer library
add_subdirectory(sqlite)          # single file embedded database library
add_subdirectory(libhardware)     # hardware abstraction layer
add_subdirectory(libhardware_legacy) # older hardware layer stuff
add_subdirectory(liblzf)          # very fast compression library
add_subdirectory(libmemtrack)     # memory tracker
add_subdirectory(libnetutils)     # networking utility functions
add_subdirectory(libprotobuf)     # Google's protocol buffers library
# add_subdirectory(libbcc)          # LLVM bitcode execution engine
# add_subdirectory(librs)           # renderscript

add_subdirectory(libandroidfw)    # frameworks-base

add_subdirectory(libgui)
add_subdirectory(libsync)
add_subdirectory(libui)
add_subdirectory(libhwui)
add_subdirectory(libinput)
# add_subdirectory(opengl-libs)     # frameworks-native
add_subdirectory(installd)
add_subdirectory(adb)

add_subdirectory(libbase)
add_subdirectory(libziparchive)
add_subdirectory(libemoji)

# ----------------------------------------------------------------
#                             Dalvik

# vm support libraries and tools
add_subdirectory(libjni)
add_subdirectory(libdex)
add_subdirectory(aidl) # must be before the java libraries, as it is used to create the interfaces
add_subdirectory(aapt)
add_subdirectory(zipalign) # used to align the APK files (which are zip archives), allowing for mmapping them

# dalvik vm
add_subdirectory(vm)
add_subdirectory(javalibrary-core)
add_subdirectory(javalibrary-conscrypt)
add_subdirectory(javalibrary-bouncycastle)
add_subdirectory(signapk) # used to sign APK files, in particular the frameworks resource bundle
add_subdirectory(javalibrary-ext)
add_subdirectory(javalibrary-okhttp)
add_subdirectory(javalibrary-frameworks)
add_subdirectory(javalibrary-voip)
add_subdirectory(javalibrary-telephony)
add_subdirectory(javalibrary-settingsprovider)
add_subdirectory(javalibrary-systemui)
add_subdirectory(libjavacore)
# add_subdirectory(javalibrary-packageinstaller)

add_subdirectory(javalibrary-shashlik)

#java tools
add_subdirectory(dx)
add_subdirectory(javalibrary-am)
#add_subdirectory(dexgen)
#add_subdirectory(hit)
#add_subdirectory(tools/dexdeps)


# ----------------------------------------------------------------
#                             Other stuff


add_subdirectory(libbinder)
add_subdirectory(libinputservice)
add_subdirectory(libandroid_servers)
add_subdirectory(servicemanager) # The application which takes care of starting and stopping services
# TODO hook into KDE's service management infrastructure for this
add_subdirectory(surfaceflinger)
add_subdirectory(bootanimation)

# Intel hardware libraries
# add_subdirectory(libwsbm)
