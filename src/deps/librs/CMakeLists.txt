project(renderscript)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/rs)
set(RS_INTERMEDIATES ${CMAKE_CURRENT_BINARY_DIR}/renderscript-intermediate-generated-files)
set(RSGEN_INTERMEDIATES ${CMAKE_CURRENT_BINARY_DIR}/rsg-generator-intermediate-generated-files)

set(rsg-generator_SRCS
    ${RSGEN_INTERMEDIATES}/spec.cpp
    ${REPO_PATH}/rsg_generator.c
)

add_custom_command(OUTPUT ${RSGEN_INTERMEDIATES}/spec.cpp
    COMMAND mkdir -p ${RSGEN_INTERMEDIATES}
    COMMAND flex -o${RSGEN_INTERMEDIATES}/spec.cpp ${REPO_PATH}/spec.l
)

# host C++: rsg-generator <= ${RSGEN_INTERMEDIATES}/spec.cpp
# prebuilts/tools/gcc-sdk/g++ -I ${REPO_PATH} -I ${RSGEN_INTERMEDIATES} -I libnativehelper/include/nativehelper  -isystem system/core/include -isystem hardware/libhardware/include -isystem hardware/libhardware_legacy/include -isystem hardware/ril/include -isystem libnativehelper/include -isystem frameworks/native/include -isystem frameworks/native/opengl/include -isystem frameworks/av/include -isystem frameworks/base/include -isystem external/skia/include -isystem tools/include -isystem out/host/linux-x86/obj/include -c  -fno-exceptions -Wno-multichar -mstackrealign -msse3 -mfpmath=sse -m32 -fPIC -include build/core/combo/include/arch/linux-x86/AndroidConfig.h -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 -DANDROID -fmessage-length=0 -W -Wall -Wno-unused -Winit-self -Wpointer-arith -O2 -g -fno-strict-aliasing -DNDEBUG -UDEBUG -DANDROID -fmessage-length=0 -W -Wall -Wno-unused -Winit-self -Wpointer-arith -Wsign-promo -DNDEBUG -UDEBUG       -MD -MF ${RSGEN_INTERMEDIATES}/spec.d -o ${RSGEN_INTERMEDIATES}/spec.o ${RSGEN_INTERMEDIATES}/spec.cpp
# cp ${RSGEN_INTERMEDIATES}/spec.d ${RSGEN_INTERMEDIATES}/spec.P; sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$//' -e '/^$/ d' -e 's/$/ :/' < ${RSGEN_INTERMEDIATES}/spec.d >> ${RSGEN_INTERMEDIATES}/spec.P; rm -f ${RSGEN_INTERMEDIATES}/spec.d
# Export includes file: ${REPO_PATH}/Android.mk -- ${RSGEN_INTERMEDIATES}/export_includes
# mkdir -p ${RSGEN_INTERMEDIATES}/ && rm -f ${RSGEN_INTERMEDIATES}/export_includes
# touch ${RSGEN_INTERMEDIATES}/export_includes
# host Executable: rsg-generator (${RSGEN_INTERMEDIATES}/rsg-generator)
# prebuilts/tools/gcc-sdk/g++         ${RSGEN_INTERMEDIATES}/rsg_generator.o    ${RSGEN_INTERMEDIATES}/spec.o    -Wl,--whole-archive   -Wl,--no-whole-archive       -Wl,-rpath-link=out/host/linux-x86/obj/lib -Wl,-rpath,\$ORIGIN/../lib -Lout/host/linux-x86/obj/lib   -Wl,--no-undefined   -m32  -o ${RSGEN_INTERMEDIATES}/rsg-generator 

set(RS_SRCS
    ${REPO_PATH}/rsAdapter.cpp
    ${REPO_PATH}/rsAllocation.cpp
    ${REPO_PATH}/rsAnimation.cpp
    ${REPO_PATH}/rsComponent.cpp
    ${REPO_PATH}/rsContext.cpp
    ${REPO_PATH}/rsCppUtils.cpp
    ${REPO_PATH}/rsDevice.cpp
    ${REPO_PATH}/rsElement.cpp
    ${REPO_PATH}/rsFBOCache.cpp
    ${REPO_PATH}/rsFifoSocket.cpp
    ${REPO_PATH}/rsFileA3D.cpp
    ${REPO_PATH}/rsFont.cpp
    ${REPO_PATH}/rsGrallocConsumer.cpp
    ${REPO_PATH}/rsObjectBase.cpp
    ${REPO_PATH}/rsMatrix2x2.cpp
    ${REPO_PATH}/rsMatrix3x3.cpp
    ${REPO_PATH}/rsMatrix4x4.cpp
    ${REPO_PATH}/rsMesh.cpp
    ${REPO_PATH}/rsMutex.cpp
    ${REPO_PATH}/rsPath.cpp
    ${REPO_PATH}/rsProgram.cpp
    ${REPO_PATH}/rsProgramFragment.cpp
    ${REPO_PATH}/rsProgramStore.cpp
    ${REPO_PATH}/rsProgramRaster.cpp
    ${REPO_PATH}/rsProgramVertex.cpp
    ${REPO_PATH}/rsSampler.cpp
    ${REPO_PATH}/rsScript.cpp
    ${REPO_PATH}/rsScriptC.cpp
    ${REPO_PATH}/rsScriptC_Lib.cpp
    ${REPO_PATH}/rsScriptC_LibGL.cpp
    ${REPO_PATH}/rsScriptGroup.cpp
    ${REPO_PATH}/rsScriptIntrinsic.cpp
    ${REPO_PATH}/rsSignal.cpp
    ${REPO_PATH}/rsStream.cpp
    ${REPO_PATH}/rsThreadIO.cpp
    ${REPO_PATH}/rsType.cpp
    ${RS_INTERMEDIATES}/rsgApiStructs.h
    ${RS_INTERMEDIATES}/rsgApiFuncDecl.h
    ${RS_INTERMEDIATES}/rsgApi.cpp
    ${RS_INTERMEDIATES}/rsgApiReplay.cpp
)

add_custom_command(OUTPUT ${RS_INTERMEDIATES}
    COMMAND mkdir -p ${RS_INTERMEDIATES}
)

add_custom_command(OUTPUT ${RS_INTERMEDIATES}/rsgApiStructs.h
    DEPENDS ${RS_INTERMEDIATES}
    DEPENDS rsg-generator
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND cat ${REPO_PATH}/rs.spec ${REPO_PATH}/rsg.spec ${REPO_PATH}/rs_native.spec | ./rsg-generator ${REPO_PATH}/rsgApiStructs.h.rsg ${RS_INTERMEDIATES}/rsgApiStructs.h
)

add_custom_command(OUTPUT ${RS_INTERMEDIATES}/rsgApiFuncDecl.h
    DEPENDS ${RS_INTERMEDIATES}
    DEPENDS rsg-generator
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND cat ${REPO_PATH}/rs.spec ${REPO_PATH}/rsg.spec ${REPO_PATH}/rs_native.spec | ./rsg-generator ${REPO_PATH}/rsgApiFuncDecl.h.rsg ${RS_INTERMEDIATES}/rsgApiFuncDecl.h
)

add_custom_command(OUTPUT ${RS_INTERMEDIATES}/rsgApi.cpp
    DEPENDS ${RS_INTERMEDIATES}
    DEPENDS rsg-generator
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND cat ${REPO_PATH}/rs.spec ${REPO_PATH}/rsg.spec ${REPO_PATH}/rs_native.spec | ./rsg-generator ${REPO_PATH}/rsgApi.cpp.rsg ${RS_INTERMEDIATES}/rsgApi.cpp
)

add_custom_command(OUTPUT ${RS_INTERMEDIATES}/rsgApiReplay.cpp
    DEPENDS ${RS_INTERMEDIATES}
    DEPENDS rsg-generator
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMAND cat ${REPO_PATH}/rs.spec ${REPO_PATH}/rsg.spec ${REPO_PATH}/rs_native.spec | ./rsg-generator ${REPO_PATH}/rsgApiReplay.cpp.rsg ${RS_INTERMEDIATES}/rsgApiReplay.cpp
)


set(RSDriver_SRCS
    ${REPO_PATH}/driver/rsdAllocation.cpp
    ${REPO_PATH}/driver/rsdBcc.cpp
    ${REPO_PATH}/driver/rsdCore.cpp
    ${REPO_PATH}/driver/rsdFrameBuffer.cpp
    ${REPO_PATH}/driver/rsdFrameBufferObj.cpp
    ${REPO_PATH}/driver/rsdGL.cpp
    ${REPO_PATH}/driver/rsdMesh.cpp
    ${REPO_PATH}/driver/rsdMeshObj.cpp
    ${REPO_PATH}/driver/rsdPath.cpp
    ${REPO_PATH}/driver/rsdProgram.cpp
    ${REPO_PATH}/driver/rsdProgramRaster.cpp
    ${REPO_PATH}/driver/rsdProgramStore.cpp
    ${REPO_PATH}/driver/rsdRuntimeStubs.cpp
    ${REPO_PATH}/driver/rsdSampler.cpp
    ${REPO_PATH}/driver/rsdScriptGroup.cpp
    ${REPO_PATH}/driver/rsdShader.cpp
    ${REPO_PATH}/driver/rsdShaderCache.cpp
    ${REPO_PATH}/driver/rsdVertexArray.cpp
)

set(RSCpuRef
    ${REPO_PATH}/rsCpuCore.cpp
    ${REPO_PATH}/rsCpuScript.cpp
    ${REPO_PATH}/rsCpuRuntimeMath.cpp
    ${REPO_PATH}/rsCpuRuntimeStubs.cpp
    ${REPO_PATH}/rsCpuScriptGroup.cpp
    ${REPO_PATH}/rsCpuIntrinsic.cpp
    ${REPO_PATH}/rsCpuIntrinsic3DLUT.cpp
    ${REPO_PATH}/rsCpuIntrinsicBlend.cpp
    ${REPO_PATH}/rsCpuIntrinsicBlur.cpp
    ${REPO_PATH}/rsCpuIntrinsicColorMatrix.cpp
    ${REPO_PATH}/rsCpuIntrinsicConvolve3x3.cpp
    ${REPO_PATH}/rsCpuIntrinsicConvolve5x5.cpp
    ${REPO_PATH}/rsCpuIntrinsicHistogram.cpp
    ${REPO_PATH}/rsCpuIntrinsicLUT.cpp
    ${REPO_PATH}/rsCpuIntrinsicYuvToRGB.cpp
)

set(rs_jni_SRCS
    ${ANDROID_FRAMEWORKS_BASE}/graphics/jni/android_renderscript_RenderScript.cpp
)

# add_definitions(-Werror -Wall -Wno-unused-parameter -Wno-unused-variable)

add_executable(rsg-generator ${rsg-generator_SRCS})
target_include_directories(rsg-generator
    PRIVATE
    ${REPO_PATH}
)

add_library(RS SHARED ${RS_SRCS})
target_link_libraries(RS
    log cutils utils EGL GLESv1_CM GLESv2 bcc
    ui bcinfo LLVM gui sync dl
    ft2 png z
)
target_include_directories(RS
    PRIVATE
    ${REPO_PATH}
    ${LIBUTILS_INCLUDES}
    ${LIBUI_INCLUDES}
    ${LIBHARDWARE_INCLUDES}
)

add_library(RSDriver SHARED ${RSDriver_SRCS})
target_link_libraries(RSDriver
    RS RSCpuRef
    log cutils utils EGL GLESv1_CM GLESv2
    bcc bcinfo LLVM ui gui sync
    pthread dl
)
target_include_directories(RSDriver
    PRIVATE
    # bcc
    ${REPO_PATH}/cpu_ref/linkloader/include
)

add_library(rs_jni SHARED ${rs_jni_SRCS})
target_link_libraries(rs_jni
        android_runtime androidfw nativehelper RS cutils log skia utils ui gui
)
target_include_directories(rs_jni
    PRIVATE
    ${RS_INTERMEDIATES}
    # rs itself
)

if(FORCE_32BIT_BUILD)
    set_target_properties(rsg-generator PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    set_target_properties(RS PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    set_target_properties(RSDriver PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    set_target_properties(rs_jni PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
