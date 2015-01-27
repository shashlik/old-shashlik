set(PostInstallCommands ${PROJECT_BINARY_DIR}/PostInstallCommands.cmake)
configure_file("PostInstallCommands.cmake.in" ${PostInstallCommands} @ONLY)
install(SCRIPT ${PostInstallCommands})

#install(CODE "message(STATUS \"Post processing core.jar - this might take a few minutes\")")
#install(CODE "execute_process(COMMAND ${CMAKE_INSTALL_PREFIX}/bin/dx --dex --core-library --statistics --verbose-dump --verbose --output=${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}/android/core-dxed.jar ${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}/android/core.jar)")
