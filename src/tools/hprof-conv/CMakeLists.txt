project(hprof-conv)

set(REPO_PATH ${DALVIK_PATH})
set(MODULE_PATH ${REPO_PATH}/tools/hprof-conv)
include_directories(${REPO_PATH}
                    ${LIBUTILS_INCLUDES}
                    ${LIBCUTILS_INCLUDES}
                    ${CMAKE_INSTALL_PREFIX}/include/android-libcore #FIXME
                    ${CMAKE_INSTALL_PREFIX}/include/nativehelper    #FIXME
)
include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include)


add_definitions(-DANDROID_SMP
                -DDVM_SHOW_EXCEPTION=1
                -DWITH_JIT
                -DWITH_JIT_TUNING
                -DARCH_IA32
                -DARCH_VARIANT="x86"
                -DDVM_JMP_TABLE_MTERP=1
                -DMTERP_STUB
                -fpermissive
                -w
)

set(hprof-conv_SRCS
   ${MODULE_PATH}/HprofConv.c
)

link_directories(${CMAKE_INSTALL_PREFIX}/lib/)

add_executable(hprof-conv ${hprof-conv_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(hprof-conv PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

target_link_libraries(hprof-conv dex
                                 nativehelper
                                 safe-iop
                                 corkscrew log utils cutils  # android-core
                                 z
                      )

install(TARGETS hprof-conv DESTINATION ${ANDROID_BIN_DIR})

