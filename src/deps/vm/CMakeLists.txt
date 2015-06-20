project(vm)

set(REPO_PATH ${DALVIK_PATH})
set(MODULE_PATH ${REPO_PATH}/vm)
set(LIBENC_PATH ${MODULE_PATH}/compiler/codegen/x86/libenc)

include_directories(${REPO_PATH}
                    ${MODULE_PATH}
                    ${LIBENC_PATH}
                    ${LIBCUTILS_INCLUDES}
                    ${CMAKE_INSTALL_PREFIX}/include/android-libcore #FIXME
                    ${LIBNATIVEHELPER_INCLUDEDIRS}
                    ${LIBANDROIDCORE_INCLUDEDIRS}
                    ${LIBANDROIDLIBCORE_INCLUDEDIRS}
)
include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include)

add_definitions(
    -DHAVE_ANDROID_PTHREAD_SETNAME_NP=1
    -DANDROID_SMP=1
    -fstrict-aliasing -Wstrict-aliasing=2
    -Wall -Wextra -Wno-unused-parameter
    -DARCH_IA32
    -DARCH_VARIANT="x86"
    -DDVM_SHOW_EXCEPTION=1
    -DWITH_JIT=1
    -DDVM_JMP_TABLE_MTERP=1
    -DMTERP_STUB
#     -UNDEBUG -DDEBUG=1 -DLOG_NDEBUG=1 -DWITH_DALVIK_ASSERT -DWITH_SELF_VERIFICATION
)

if(SystemIsBigEndian)
    add_definitions(-DHAVE_BIG_ENDIAN)
else()
    add_definitions(-DHAVE_LITTLE_ENDIAN)
endif()

if (JIT_VM)
   add_definitions(${JIT_DEFS})
else (JIT_VM)
    add_definitions(-DdvmAsmInstructionStart=0 -DdvmAsmInstructionEnd=0
                    -DdvmAsmSisterStart=0 -DdvmAsmSisterEnd=0 -DDVM_NO_ASM_INTERP=1)
endif (JIT_VM)

if (JIT_VM)
    set(libenc_SRCS
        ${LIBENC_PATH}/dec_base.cpp
        ${LIBENC_PATH}/enc_base.cpp
        ${LIBENC_PATH}/enc_wrapper.cpp
        ${LIBENC_PATH}/enc_tabl.cpp
    )

    enable_language(ASM)
    set(assembler_SRCS
        ${MODULE_PATH}/mterp/out/InterpAsm-x86.S
        ${MODULE_PATH}/arch/x86/Call386ABI.S
    )
    set_property(SOURCE ${assembler_SRCS} PROPERTY LANGUAGE ASM)

    set(vm_compiler_SRCS
        ${MODULE_PATH}/arch/x86/Hints386ABI.cpp
        ${MODULE_PATH}/mterp/out/InterpC-x86.cpp
        ${MODULE_PATH}/compiler/codegen/x86/LowerAlu.cpp
        ${MODULE_PATH}/compiler/codegen/x86/LowerConst.cpp
        ${MODULE_PATH}/compiler/codegen/x86/LowerMove.cpp
        ${MODULE_PATH}/compiler/codegen/x86/Lower.cpp
        ${MODULE_PATH}/compiler/codegen/x86/LowerHelper.cpp
        ${MODULE_PATH}/compiler/codegen/x86/LowerJump.cpp
        ${MODULE_PATH}/compiler/codegen/x86/LowerObject.cpp
        ${MODULE_PATH}/compiler/codegen/x86/AnalysisO1.cpp
        ${MODULE_PATH}/compiler/codegen/x86/BytecodeVisitor.cpp
        ${MODULE_PATH}/compiler/codegen/x86/NcgAot.cpp
        ${MODULE_PATH}/compiler/codegen/x86/CodegenInterface.cpp
        ${MODULE_PATH}/compiler/codegen/x86/LowerInvoke.cpp
        ${MODULE_PATH}/compiler/codegen/x86/LowerReturn.cpp
        ${MODULE_PATH}/compiler/codegen/x86/NcgHelper.cpp
        ${MODULE_PATH}/compiler/codegen/x86/LowerGetPut.cpp
        ${MODULE_PATH}/compiler/Compiler.cpp
        ${MODULE_PATH}/compiler/Frontend.cpp
        ${MODULE_PATH}/compiler/Utility.cpp
        ${MODULE_PATH}/compiler/InlineTransformation.cpp
        ${MODULE_PATH}/compiler/IntermediateRep.cpp
        ${MODULE_PATH}/compiler/Dataflow.cpp
        ${MODULE_PATH}/compiler/SSATransformation.cpp
        ${MODULE_PATH}/compiler/Loop.cpp
        ${MODULE_PATH}/compiler/Ralloc.cpp
        ${MODULE_PATH}/interp/Jit.cpp
     )
else (JIT_VM)
    set(vm_compiler_SRCS
        ${MODULE_PATH}/arch/generic/Call.cpp
        ${MODULE_PATH}/arch/generic/Hints.cpp
        ${MODULE_PATH}/mterp/out/InterpC-allstubs.cpp)
endif (JIT_VM)

set(vm_SRCS
    ${libenc_SRCS}
    ${vm_compiler_SRCS}
    ${MODULE_PATH}/mterp/out/InterpC-portable.cpp
    ${MODULE_PATH}/mterp/Mterp.cpp
    ${MODULE_PATH}/InlineNative.cpp
    ${MODULE_PATH}/AllocTracker.cpp
    ${MODULE_PATH}/Atomic.cpp
    ${MODULE_PATH}/AtomicCache.cpp
    ${MODULE_PATH}/BitVector.cpp
    ${MODULE_PATH}/CheckJni.cpp
    ${MODULE_PATH}/Ddm.cpp
    ${MODULE_PATH}/Debugger.cpp
    ${MODULE_PATH}/DvmDex.cpp
    ${MODULE_PATH}/Exception.cpp
    ${MODULE_PATH}/Hash.cpp
    ${MODULE_PATH}/IndirectRefTable.cpp
    ${MODULE_PATH}/Init.cpp
    ${MODULE_PATH}/InitRefs.cpp
    ${MODULE_PATH}/Inlines.cpp
    ${MODULE_PATH}/Intern.cpp
    ${MODULE_PATH}/Jni.cpp
    ${MODULE_PATH}/JarFile.cpp
    ${MODULE_PATH}/LinearAlloc.cpp
    ${MODULE_PATH}/Misc.cpp
    ${MODULE_PATH}/Native.cpp
    ${MODULE_PATH}/PointerSet.cpp
    ${MODULE_PATH}/Profile.cpp
    ${MODULE_PATH}/RawDexFile.cpp
    ${MODULE_PATH}/ReferenceTable.cpp
    ${MODULE_PATH}/SignalCatcher.cpp
    ${MODULE_PATH}/StdioConverter.cpp
    ${MODULE_PATH}/Sync.cpp
    ${MODULE_PATH}/Thread.cpp
    ${MODULE_PATH}/UtfString.cpp
    ${MODULE_PATH}/alloc/Alloc.cpp
    ${MODULE_PATH}/alloc/CardTable.cpp
    ${MODULE_PATH}/alloc/DlMalloc.cpp
    ${MODULE_PATH}/alloc/Heap.cpp
    ${MODULE_PATH}/alloc/HeapBitmap.cpp
    ${MODULE_PATH}/alloc/HeapSource.cpp
    ${MODULE_PATH}/alloc/HeapDebug.cpp
    ${MODULE_PATH}/alloc/DdmHeap.cpp
    ${MODULE_PATH}/alloc/Verify.cpp
    ${MODULE_PATH}/alloc/Visit.cpp
    ${MODULE_PATH}/alloc/MarkSweep.cpp
    ${MODULE_PATH}/analysis/CodeVerify.cpp
    ${MODULE_PATH}/analysis/DexPrepare.cpp
    ${MODULE_PATH}/analysis/DexVerify.cpp
    ${MODULE_PATH}/analysis/Liveness.cpp
    ${MODULE_PATH}/analysis/Optimize.cpp
    ${MODULE_PATH}/analysis/RegisterMap.cpp
    ${MODULE_PATH}/analysis/VerifySubs.cpp
    ${MODULE_PATH}/analysis/VfyBasicBlock.cpp
    ${MODULE_PATH}/hprof/Hprof.cpp
    ${MODULE_PATH}/hprof/HprofClass.cpp
    ${MODULE_PATH}/hprof/HprofHeap.cpp
    ${MODULE_PATH}/hprof/HprofOutput.cpp
    ${MODULE_PATH}/hprof/HprofString.cpp
    ${MODULE_PATH}/interp/Interp.cpp
    ${MODULE_PATH}/interp/Stack.cpp
    ${MODULE_PATH}/jdwp/ExpandBuf.cpp
    ${MODULE_PATH}/jdwp/JdwpAdb.cpp
    ${MODULE_PATH}/jdwp/JdwpConstants.cpp
    ${MODULE_PATH}/jdwp/JdwpEvent.cpp
    ${MODULE_PATH}/jdwp/JdwpHandler.cpp
    ${MODULE_PATH}/jdwp/JdwpMain.cpp
    ${MODULE_PATH}/jdwp/JdwpSocket.cpp
    ${MODULE_PATH}/native/InternalNative.cpp
    ${MODULE_PATH}/native/dalvik_bytecode_OpcodeInfo.cpp
    ${MODULE_PATH}/native/dalvik_system_DexFile.cpp
    ${MODULE_PATH}/native/dalvik_system_VMDebug.cpp
    ${MODULE_PATH}/native/dalvik_system_VMRuntime.cpp
    ${MODULE_PATH}/native/dalvik_system_VMStack.cpp
    ${MODULE_PATH}/native/dalvik_system_Zygote.cpp
    ${MODULE_PATH}/native/java_lang_Class.cpp
    ${MODULE_PATH}/native/java_lang_Double.cpp
    ${MODULE_PATH}/native/java_lang_Float.cpp
    ${MODULE_PATH}/native/java_lang_Math.cpp
    ${MODULE_PATH}/native/java_lang_Object.cpp
    ${MODULE_PATH}/native/java_lang_Runtime.cpp
    ${MODULE_PATH}/native/java_lang_String.cpp
    ${MODULE_PATH}/native/java_lang_System.cpp
    ${MODULE_PATH}/native/java_lang_Throwable.cpp
    ${MODULE_PATH}/native/java_lang_VMClassLoader.cpp
    ${MODULE_PATH}/native/java_lang_VMThread.cpp
    ${MODULE_PATH}/native/java_lang_reflect_AccessibleObject.cpp
    ${MODULE_PATH}/native/java_lang_reflect_Array.cpp
    ${MODULE_PATH}/native/java_lang_reflect_Constructor.cpp
    ${MODULE_PATH}/native/java_lang_reflect_Field.cpp
    ${MODULE_PATH}/native/java_lang_reflect_Method.cpp
    ${MODULE_PATH}/native/java_lang_reflect_Proxy.cpp
    ${MODULE_PATH}/native/java_util_concurrent_atomic_AtomicLong.cpp
    ${MODULE_PATH}/native/org_apache_harmony_dalvik_NativeTestTarget.cpp
    ${MODULE_PATH}/native/org_apache_harmony_dalvik_ddmc_DdmServer.cpp
    ${MODULE_PATH}/native/org_apache_harmony_dalvik_ddmc_DdmVmInternal.cpp
    ${MODULE_PATH}/native/sun_misc_Unsafe.cpp
    ${MODULE_PATH}/oo/AccessCheck.cpp
    ${MODULE_PATH}/oo/Array.cpp
    ${MODULE_PATH}/oo/Class.cpp
    ${MODULE_PATH}/oo/Object.cpp
    ${MODULE_PATH}/oo/Resolve.cpp
    ${MODULE_PATH}/oo/TypeCheck.cpp
    ${MODULE_PATH}/os/linux.cpp
    ${MODULE_PATH}/reflect/Annotation.cpp
    ${MODULE_PATH}/reflect/Proxy.cpp
    ${MODULE_PATH}/reflect/Reflect.cpp
    ${MODULE_PATH}/test/TestHash.cpp
    ${MODULE_PATH}/test/TestIndirectRefTable.cpp
)

set(vm_HEADERS
    ${REPO_PATH}/vm/Common.h
    ${REPO_PATH}/vm/DalvikVersion.h
)

add_library(dvm SHARED ${vm_SRCS} ${assembler_SRCS})
set_target_properties(dvm PROPERTIES COMPILE_FLAGS "-fstrict-aliasing -Wstrict-aliasing=2 -Wall -Wextra -Wno-unused-parameter")
if(FORCE_32BIT_BUILD)
    set_target_properties(dvm PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(dvm
    dex
    shashlik_jni
    javacore
    ${FFI_LIBRARIES})

install(TARGETS dvm DESTINATION ${ANDROID_LIB_DIR})
install(FILES
        ${vm_HEADERS}
        DESTINATION include/dex)

