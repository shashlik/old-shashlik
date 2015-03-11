project(gdbjithelper)

add_definitions(-DHAVE_SYS_UIO_H -DANDROID_SMP -DDVM_SHOW_EXCEPTION=1 -DWITH_JIT -DWITH_JIT_TUNING -DARCH_IA32 -DDVM_JMP_TABLE_MTERP=1 -DMTERP_STUB -fpermissive -w -DARCH_VARIANT="x86")
if(SystemIsBigEndian)
    add_definitions(-DHAVE_BIG_ENDIAN)
else()
    add_definitions(-DHAVE_LITTLE_ENDIAN)
endif()
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dalvik)
set(MOD_PATH ${REPO_PATH}/tools/gdbjithelper)

set(gdbjithelper_SRCS
   ${MOD_PATH}/gdbjithelper.c
)

include_directories(${REPO_PATH} ${MOD_PATH} ${CMAKE_INSTALL_PREFIX}/include/android-libcore ${CMAKE_INSTALL_PREFIX}/include/nativehelper)
include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include)
add_executable(gdbjithelper ${gdbjithelper_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(gdbjithelper PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(gdbjithelper z corkscrew dex cutils log nativehelper safe-iop utils)
install(TARGETS gdbjithelper DESTINATION ${ANDROID_BIN_DIR})
