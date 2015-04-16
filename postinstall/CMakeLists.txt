# Create a file containing the shashlik environment
file(WRITE ${PROJECT_BINARY_DIR}/shashlik_env_wrapper.sh
"export PATH=\"$PATH:${ANDROID_ROOT}/sbin:${ANDROID_ROOT}/vendor/bin:${ANDROID_ROOT}/system/sbin:${ANDROID_ROOT}/system/bin:${ANDROID_ROOT}/system/xbin\"
export LD_LIBRARY_PATH=\"${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}:${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}/egl:${ANDROID_ROOT}/vendor/lib:${ANDROID_ROOT}/system/lib\"
export ANDROID_BOOTLOGO=\"1\"
export ANDROID_ROOT=\"${ANDROID_ROOT}/system\"
export ANDROID_ASSETS=\"${ANDROID_ROOT}/system/app\"
export ANDROID_DATA=\"${ANDROID_ROOT}/data\"
export ANDROID_STORAGE=\"${ANDROID_ROOT}/storage\"
export ASEC_MOUNTPOINT=\"${ANDROID_ROOT}/mnt/asec\"
export LOOP_MOUNTPOINT=\"${ANDROID_ROOT}/mnt/obb\"
export EXTERNAL_STORAGE=\"/mnt\"
export BOOTCLASSPATH=\"${ANDROID_ROOT}/system/framework/core.jar:${ANDROID_ROOT}/system/framework/conscrypt.jar:${ANDROID_ROOT}/system/framework/bouncycastle.jar:${ANDROID_ROOT}/system/framework/okhttp.jar:${ANDROID_ROOT}/system/framework/ext.jar:${ANDROID_ROOT}/system/framework/framework.jar:${ANDROID_ROOT}/system/framework/telephony-common.jar:${ANDROID_ROOT}/system/framework/voip-common.jar:${ANDROID_ROOT}/system/framework/framework2.jar\"
exec $@
")
install(PROGRAMS ${PROJECT_BINARY_DIR}/shashlik_env_wrapper.sh DESTINATION ${CMAKE_INSTALL_PREFIX}/${BIN_INSTALL_DIR})

# Create the android directory structure locally, before installing it
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/android/sbin)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/android/dev)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/android/proc)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/android/sys)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/android/system)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/android/data)
file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/android/data/dalvik-cache)
install(DIRECTORY ${PROJECT_BINARY_DIR}/android DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR})

set(PostInstallCommands ${PROJECT_BINARY_DIR}/PostInstallCommands.cmake)
configure_file("PostInstallCommands.cmake.in" ${PostInstallCommands} @ONLY)
install(SCRIPT ${PostInstallCommands})
