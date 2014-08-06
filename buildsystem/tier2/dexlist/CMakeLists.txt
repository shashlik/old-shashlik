project(dexlist)

add_definitions(-DHAVE_SYS_UIO_H -DANDROID_SMP -DDVM_SHOW_EXCEPTION=1 -DHAVE_BIG_ENDIAN -fpermissive -w ${JIT_DEFS})

set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dalvik)
set(MOD_PATH ${REPO_PATH}/dexlist)

set(dexlist_SRCS
   ${MOD_PATH}/DexList.cpp
)

include_directories(${REPO_PATH} ${MOD_PATH} ${CMAKE_INSTALL_PREFIX}/include/android-libcore ${CMAKE_INSTALL_PREFIX}/include/nativehelper)
include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include)
add_executable(dexlist ${dexlist_SRCS})
target_link_libraries(dexlist ${STANDARD_SYS_LIBS} libcorkscrew.so libdex.so libcutils.so liblog.so libnativehelper.so libnativehelper.so libsafe-iop.so  libutils.so)
install(TARGETS dexlist DESTINATION bin)

