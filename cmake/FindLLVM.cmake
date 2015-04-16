# This module simply looks for the LLVM directory and includes the appropriate files from there

find_path(LLVM_CMAKE_DIR NAMES LLVMConfig.cmake
    HINTS ${CMAKE_PREFIX_PATH}/share/llvm/cmake
    PATHS /usr/share/llvm/cmake
)
if(NOT LLVM_CMAKE_DIR)
    message(FATAL_ERROR "Could not find the LLVM cmake includes directory. Please install the package containing LLVMConfig.cmake and try again")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${LLVM_CMAKE_DIR})
include(LLVMConfig)
