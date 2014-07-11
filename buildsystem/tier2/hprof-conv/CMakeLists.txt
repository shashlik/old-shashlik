project(hprof-conv)

add_definitions(-DHAVE_SYS_UIO_H -DANDROID_SMP -DDVM_SHOW_EXCEPTION=1 -DWITH_JIT -DWITH_JIT_TUNING -DARCH_IA32 -DDVM_JMP_TABLE_MTERP=1 -DMTERP_STUB -DHAVE_BIG_ENDIAN -fpermissive -w -DARCH_VARIANT="x86")
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dalvik)
set(MOD_PATH ${REPO_PATH}/tools/hprof-conv)

set(hprof-conv_SRCS
   ${MOD_PATH}/HprofConv.c
)

include_directories(${REPO_PATH} ${MOD_PATH} ${CMAKE_INSTALL_PREFIX}/include/android-libcore ${CMAKE_INSTALL_PREFIX}/include/nativehelper)
include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include)
add_executable(hprof-conv ${hprof-conv_SRCS})
target_link_libraries(hprof-conv ${STANDARD_SYS_LIBS} libcorkscrew.so libdex.so libcutils.so liblog.so libnativehelper.so libnativhelper.so libsafe-iop.so  libutils.so)
install(TARGETS hprof-conv DESTINATION bin)

