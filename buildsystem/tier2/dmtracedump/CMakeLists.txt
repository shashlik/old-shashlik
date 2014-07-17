project(dmtracedump)

add_definitions(-DHAVE_SYS_UIO_H -DANDROID_SMP -DDVM_SHOW_EXCEPTION=1 -DWITH_JIT -DWITH_JIT_TUNING -DARCH_IA32 -DDVM_JMP_TABLE_MTERP=1 -DMTERP_STUB -DHAVE_BIG_ENDIAN -fpermissive -w -DARCH_VARIANT="x86")
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dalvik)
set(MOD_PATH ${REPO_PATH}/tools/dmtracedump)

include_directories(${REPO_PATH} ${REPO_PATH}/vm ${MOD_PATH} ${CMAKE_INSTALL_PREFIX}/include/android-libcore ${CMAKE_INSTALL_PREFIX}/include/nativehelper)
include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include)

set(dmtracedump_SRCS
   ${MOD_PATH}/TraceDump.c
)
add_executable(dmtracedump ${dmtracedump_SRCS})
target_link_libraries(dmtracedump ${STANDARD_SYS_LIBS} libcorkscrew.so libdex.so libcutils.so liblog.so libnativehelper.so libnativehelper.so libsafe-iop.so libutils.so dvm)
install(TARGETS dmtracedump DESTINATION bin)

set(create_test_dmtrace_SRCS
   ${MOD_PATH}/CreateTestTrace.c
)
add_executable(create_test_dmtrace ${create_test_dmtrace_SRCS})
target_link_libraries(create_test_dmtrace ${STANDARD_SYS_LIBS} libcorkscrew.so libdex.so libcutils.so liblog.so libnativehelper.so libnativehelper.so libsafe-iop.so libutils.so dvm)
install(TARGETS create_test_dmtrace DESTINATION bin)

