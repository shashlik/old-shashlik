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
