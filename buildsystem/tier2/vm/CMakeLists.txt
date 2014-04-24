project(vm)

add_definitions(-DHAVE_SYS_UIO_H -DANDROID_SMP -DDVM_SHOW_EXCEPTION=1 -DWITH_JIT -DWITH_JIT_TUNING -DARCH_IA32 -DDVM_JMP_TABLE_MTERP=1 -DMTERP_STUB -DHAVE_BIG_ENDIAN -fpermissive -w -DARCH_VARIANT="x86")
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dalvik)
set(MOD_PATH ${REPO_PATH}/vm)
set(LIBENC_PATH ${MOD_PATH}/compiler/codegen/x86/libenc)
#     ${MOD_PATH}/Atomic.cpp.arm
#     ${MOD_PATH}/BitVector.cpp.arm
#     ${MOD_PATH}/IndirectRefTable.cpp.arm
#     ${MOD_PATH}/InlineNative.cpp.arm
#     ${MOD_PATH}/mterp/out/InterpC-portable.cpp.arm
#     ${MOD_PATH}/alloc/MarkSweep.cpp.arm
#     ${MOD_PATH}/alloc/HeapBitmap.cpp.arm
#     ${MOD_PATH}/interp/Interp.cpp.arm
#     ${MOD_PATH}/alloc/Heap.cpp.arm
#     ${MOD_PATH}/mterp/Mterp.cpp.arm
#     ${MOD_PATH}/test/AtomicTest.cpp.arm

set(libenc_SRCS
    ${LIBENC_PATH}/dec_base.cpp
    ${LIBENC_PATH}/enc_base.cpp
    ${LIBENC_PATH}/enc_wrapper.cpp
    ${LIBENC_PATH}/enc_tabl.cpp
)

set(vm_SRCS
    ${libenc_SRCS}
    ${MOD_PATH}/arch/x86/Call386ABI.S
    ${MOD_PATH}/arch/x86/Hints386ABI.cpp
    ${MOD_PATH}/mterp/out/InterpC-x86.cpp
    ${MOD_PATH}/mterp/out/InterpAsm-x86.S

    ${MOD_PATH}/AllocTracker.cpp
    ${MOD_PATH}/AtomicCache.cpp
    ${MOD_PATH}/CheckJni.cpp
    ${MOD_PATH}/Ddm.cpp
    ${MOD_PATH}/Debugger.cpp
    ${MOD_PATH}/DvmDex.cpp
    ${MOD_PATH}/Exception.cpp
    ${MOD_PATH}/Hash.cpp
    ${MOD_PATH}/Init.cpp
    ${MOD_PATH}/InitRefs.cpp
    ${MOD_PATH}/Inlines.cpp
    ${MOD_PATH}/Intern.cpp
    ${MOD_PATH}/Jni.cpp
    ${MOD_PATH}/JarFile.cpp
    ${MOD_PATH}/LinearAlloc.cpp
    ${MOD_PATH}/Misc.cpp
    ${MOD_PATH}/Native.cpp
    ${MOD_PATH}/PointerSet.cpp
    ${MOD_PATH}/Profile.cpp
    ${MOD_PATH}/RawDexFile.cpp
    ${MOD_PATH}/ReferenceTable.cpp
    ${MOD_PATH}/SignalCatcher.cpp
    ${MOD_PATH}/StdioConverter.cpp
    ${MOD_PATH}/Sync.cpp
    ${MOD_PATH}/Thread.cpp
    ${MOD_PATH}/UtfString.cpp
    ${MOD_PATH}/alloc/Alloc.cpp
    ${MOD_PATH}/alloc/CardTable.cpp
    ${MOD_PATH}/alloc/DlMalloc.cpp
    ${MOD_PATH}/alloc/HeapSource.cpp
    ${MOD_PATH}/alloc/HeapDebug.cpp
    ${MOD_PATH}/alloc/DdmHeap.cpp
    ${MOD_PATH}/alloc/Verify.cpp
    ${MOD_PATH}/alloc/Visit.cpp
    ${MOD_PATH}/analysis/CodeVerify.cpp
    ${MOD_PATH}/analysis/DexPrepare.cpp
    ${MOD_PATH}/analysis/DexVerify.cpp
    ${MOD_PATH}/analysis/Liveness.cpp
    ${MOD_PATH}/analysis/Optimize.cpp
    ${MOD_PATH}/analysis/RegisterMap.cpp
    ${MOD_PATH}/analysis/VerifySubs.cpp
    ${MOD_PATH}/analysis/VfyBasicBlock.cpp
    ${MOD_PATH}/compiler/codegen/x86/LowerAlu.cpp
    ${MOD_PATH}/compiler/codegen/x86/LowerConst.cpp
    ${MOD_PATH}/compiler/codegen/x86/LowerMove.cpp
    ${MOD_PATH}/compiler/codegen/x86/Lower.cpp
    ${MOD_PATH}/compiler/codegen/x86/LowerHelper.cpp
    ${MOD_PATH}/compiler/codegen/x86/LowerJump.cpp
    ${MOD_PATH}/compiler/codegen/x86/LowerObject.cpp
    ${MOD_PATH}/compiler/codegen/x86/AnalysisO1.cpp
    ${MOD_PATH}/compiler/codegen/x86/BytecodeVisitor.cpp
    ${MOD_PATH}/compiler/codegen/x86/NcgAot.cpp
    ${MOD_PATH}/compiler/codegen/x86/CodegenInterface.cpp
    ${MOD_PATH}/compiler/codegen/x86/LowerInvoke.cpp
    ${MOD_PATH}/compiler/codegen/x86/LowerReturn.cpp
    ${MOD_PATH}/compiler/codegen/x86/NcgHelper.cpp
    ${MOD_PATH}/compiler/codegen/x86/LowerGetPut.cpp
    ${MOD_PATH}/compiler/Compiler.cpp
    ${MOD_PATH}/compiler/Frontend.cpp
    ${MOD_PATH}/compiler/Utility.cpp
    ${MOD_PATH}/compiler/InlineTransformation.cpp
    ${MOD_PATH}/compiler/IntermediateRep.cpp
    ${MOD_PATH}/compiler/Dataflow.cpp
    ${MOD_PATH}/compiler/SSATransformation.cpp
    ${MOD_PATH}/compiler/Loop.cpp
    ${MOD_PATH}/compiler/Ralloc.cpp
    ${MOD_PATH}/hprof/Hprof.cpp
    ${MOD_PATH}/hprof/HprofClass.cpp
    ${MOD_PATH}/hprof/HprofHeap.cpp
    ${MOD_PATH}/hprof/HprofOutput.cpp
    ${MOD_PATH}/hprof/HprofString.cpp
    ${MOD_PATH}/interp/Jit.cpp
    ${MOD_PATH}/interp/Stack.cpp
    ${MOD_PATH}/jdwp/ExpandBuf.cpp
    ${MOD_PATH}/jdwp/JdwpAdb.cpp
    ${MOD_PATH}/jdwp/JdwpConstants.cpp
    ${MOD_PATH}/jdwp/JdwpEvent.cpp
    ${MOD_PATH}/jdwp/JdwpHandler.cpp
    ${MOD_PATH}/jdwp/JdwpMain.cpp
    ${MOD_PATH}/jdwp/JdwpSocket.cpp
    ${MOD_PATH}/native/InternalNative.cpp
    ${MOD_PATH}/native/dalvik_bytecode_OpcodeInfo.cpp
    ${MOD_PATH}/native/dalvik_system_DexFile.cpp
    ${MOD_PATH}/native/dalvik_system_VMDebug.cpp
    ${MOD_PATH}/native/dalvik_system_VMRuntime.cpp
    ${MOD_PATH}/native/dalvik_system_VMStack.cpp
    ${MOD_PATH}/native/dalvik_system_Zygote.cpp
    ${MOD_PATH}/native/java_lang_Class.cpp
    ${MOD_PATH}/native/java_lang_Double.cpp
    ${MOD_PATH}/native/java_lang_Float.cpp
    ${MOD_PATH}/native/java_lang_Math.cpp
    ${MOD_PATH}/native/java_lang_Object.cpp
    ${MOD_PATH}/native/java_lang_Runtime.cpp
    ${MOD_PATH}/native/java_lang_String.cpp
    ${MOD_PATH}/native/java_lang_System.cpp
    ${MOD_PATH}/native/java_lang_Throwable.cpp
    ${MOD_PATH}/native/java_lang_VMClassLoader.cpp
    ${MOD_PATH}/native/java_lang_VMThread.cpp
    ${MOD_PATH}/native/java_lang_reflect_AccessibleObject.cpp
    ${MOD_PATH}/native/java_lang_reflect_Array.cpp
    ${MOD_PATH}/native/java_lang_reflect_Constructor.cpp
    ${MOD_PATH}/native/java_lang_reflect_Field.cpp
    ${MOD_PATH}/native/java_lang_reflect_Method.cpp
    ${MOD_PATH}/native/java_lang_reflect_Proxy.cpp
    ${MOD_PATH}/native/java_util_concurrent_atomic_AtomicLong.cpp
    ${MOD_PATH}/native/org_apache_harmony_dalvik_NativeTestTarget.cpp
    ${MOD_PATH}/native/org_apache_harmony_dalvik_ddmc_DdmServer.cpp
    ${MOD_PATH}/native/org_apache_harmony_dalvik_ddmc_DdmVmInternal.cpp
    ${MOD_PATH}/native/sun_misc_Unsafe.cpp
    ${MOD_PATH}/oo/AccessCheck.cpp
    ${MOD_PATH}/oo/Array.cpp
    ${MOD_PATH}/oo/Class.cpp
    ${MOD_PATH}/oo/Object.cpp
    ${MOD_PATH}/oo/Resolve.cpp
    ${MOD_PATH}/oo/TypeCheck.cpp
    ${MOD_PATH}/os/linux.cpp
    ${MOD_PATH}/reflect/Annotation.cpp
    ${MOD_PATH}/reflect/Proxy.cpp
    ${MOD_PATH}/reflect/Reflect.cpp
    ${MOD_PATH}/test/TestHash.cpp
    ${MOD_PATH}/test/TestIndirectRefTable.cpp
)

set(vm_HEADERS
    ${REPO_PATH}/vm/Common.h
    ${REPO_PATH}/vm/DalvikVersion.h
)

include_directories(${REPO_PATH} ${MOD_PATH} ${LIBENC_PATH} ${CMAKE_INSTALL_PREFIX}/include/android-libcore ${CMAKE_INSTALL_PREFIX}/include/nativehelper)
include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include)
add_library(dvm SHARED ${vm_SRCS})
#install(TARGETS vm DESTINATION lib)
install(FILES
        ${vm_HEADERS}
        DESTINATION include/dex)

