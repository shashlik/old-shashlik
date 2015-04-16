project(libbcc)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/libbcc)

set(bccCore_SRCS
    ${REPO_PATH}/lib/Core/BCCContext.cpp
    ${REPO_PATH}/lib/Core/BCCContextImpl.cpp
    ${REPO_PATH}/lib/Core/Compiler.cpp
    ${REPO_PATH}/lib/Core/Script.cpp
    ${REPO_PATH}/lib/Core/Source.cpp
)

set(bccExecutionEngine_SRCS
    ${REPO_PATH}/lib/ExecutionEngine/ELFObjectLoaderImpl.cpp
    ${REPO_PATH}/lib/ExecutionEngine/GDBJIT.cpp
    ${REPO_PATH}/lib/ExecutionEngine/GDBJITRegistrar.cpp
    ${REPO_PATH}/lib/ExecutionEngine/ObjectLoader.cpp
    ${REPO_PATH}/lib/ExecutionEngine/SymbolResolverProxy.cpp
    ${REPO_PATH}/lib/ExecutionEngine/SymbolResolvers.cpp
)

set(bccRenderscript_SRCS
    ${REPO_PATH}/lib/Renderscript/RSCompiler.cpp
    ${REPO_PATH}/lib/Renderscript/RSCompilerDriver.cpp
    ${REPO_PATH}/lib/Renderscript/RSEmbedInfo.cpp
    ${REPO_PATH}/lib/Renderscript/RSExecutable.cpp
    ${REPO_PATH}/lib/Renderscript/RSForEachExpand.cpp
    ${REPO_PATH}/lib/Renderscript/RSInfo.cpp
    ${REPO_PATH}/lib/Renderscript/RSInfoExtractor.cpp
    ${REPO_PATH}/lib/Renderscript/RSInfoReader.cpp
    ${REPO_PATH}/lib/Renderscript/RSInfoWriter.cpp
    ${REPO_PATH}/lib/Renderscript/RSScript.cpp
)

set(bccSupport_SRCS
    ${REPO_PATH}/lib/Support/CompilerConfig.cpp
    ${REPO_PATH}/lib/Support/Disassembler.cpp
    ${REPO_PATH}/lib/Support/FileBase.cpp
    ${REPO_PATH}/lib/Support/Initialization.cpp
    ${REPO_PATH}/lib/Support/InputFile.cpp
    ${REPO_PATH}/lib/Support/OutputFile.cpp
    ${REPO_PATH}/lib/Support/Sha1Util.cpp
    ${REPO_PATH}/lib/Support/TargetCompilerConfigs.cpp
)

set(bcinfo_SRCS
    ${REPO_PATH}/bcinfo/BitcodeTranslator.cpp
    ${REPO_PATH}/bcinfo/BitcodeWrapper.cpp
    ${REPO_PATH}/bcinfo/MetadataExtractor.cpp
)

set(LLVMWrap_SRCS
    ${REPO_PATH}/bcinfo/Wrap/bitcode_wrapperer.cpp
    ${REPO_PATH}/bcinfo/Wrap/file_wrapper_input.cpp
    ${REPO_PATH}/bcinfo/Wrap/file_wrapper_output.cpp
    ${REPO_PATH}/bcinfo/Wrap/in_memory_wrapper_input.cpp
    ${REPO_PATH}/bcinfo/Wrap/wrapper_output.cpp
)

add_llvm_library(LLVMBitReader_2_7
  ${REPO_PATH}/bcinfo/BitReader_2_7/BitReader.cpp
  ${REPO_PATH}/bcinfo/BitReader_2_7/BitcodeReader.cpp
)
target_include_directories(LLVMBitReader_2_7
    PRIVATE
    ${LLVM_INCLUDE_DIRS}
)

add_llvm_library(LLVMBitReader_3_0
  ${REPO_PATH}/bcinfo/BitReader_3_0/BitReader.cpp
  ${REPO_PATH}/bcinfo/BitReader_3_0/BitcodeReader.cpp
)
target_include_directories(LLVMBitReader_3_0
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LLVM_INCLUDE_DIRS}
)

# add_llvm_library_dependencies(LLVMBitReader_3_0
#   LLVMCore
#   LLVMSupport
# )

add_library(LLVMWrap SHARED ${LLVMWrap_SRCS})
target_include_directories(LLVMWrap
    PRIVATE
    ${REPO_PATH}/include
)

add_library(bcinfo SHARED ${bcinfo_SRCS})
target_link_libraries(bcinfo
    LLVMWrap LLVMBitReader_2_7 LLVMBitReader_3_0
)

add_library(bccRenderscript STATIC ${bccRenderscript_SRCS})
add_library(bccExecutionEngine STATIC ${bccExecutionEngine_SRCS})
add_library(bccCore STATIC ${bccCore_SRCS})
add_library(bccSupport STATIC ${bccSupport_SRCS})
# this is a derpy little thing that we do because otherwise cmake complains a great deal...
file(WRITE ${CMAKE_BINARY_DIR}/dummy.c "")
add_library(bcc SHARED ${CMAKE_BINARY_DIR}/dummy.c)
target_link_libraries(bcc
    bccRenderscript bccExecutionEngine bccCore bccSupport
    bcinfo LLVM
)

if(FORCE_32BIT_BUILD)
    set_target_properties(LLVMWrap PROPERTIES COMPILE_FLAGS "-m32 -std=c++11" LINK_FLAGS "-m32")
    set_target_properties(LLVMBitReader_3_0 PROPERTIES COMPILE_FLAGS "-m32 -std=c++11" LINK_FLAGS "-m32")
    set_target_properties(LLVMBitReader_2_7 PROPERTIES COMPILE_FLAGS "-m32 -std=c++11" LINK_FLAGS "-m32")
    set_target_properties(bcinfo PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    set_target_properties(bcc PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    set_target_properties(bccRenderscript PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    set_target_properties(bccExecutionEngine PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    set_target_properties(bccCore PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    set_target_properties(bccSupport PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
