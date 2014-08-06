project(dexdump)

set(REPO_PATH ${DALVIK_PATH})
include_directories(${REPO_PATH}
                    #${REPO_PATH}/dalvik
                    ${CMAKE_INSTALL_PREFIX}/include/android-libcore  # FIXME
                    ${CMAKE_INSTALL_PREFIX}/include/nativehelper     # FIXME
)
include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include)

add_definitions(-DHAVE_SYS_UIO_H
                -DANDROID_SMP
                -DDVM_SHOW_EXCEPTION=1
                -DWITH_JIT
                -DWITH_JIT_TUNING
                -DARCH_IA32
                -DARCH_VARIANT="x86"
                -DDVM_JMP_TABLE_MTERP=1
                -DMTERP_STUB
                -DHAVE_BIG_ENDIAN
                -fpermissive
                -w
)

set(MOD_PATH ${REPO_PATH}/dexdump)

set(dexdump_SRCS
   ${REPO_PATH}/dexdump/DexDump.cpp
)


link_directories(${CMAKE_INSTALL_PREFIX}/lib/)

add_executable(dexdump ${dexdump_SRCS})
target_link_libraries(dexdump libcorkscrew.so libdex.so
                              liblog.so libnativehelper.so libnativehelper.so
			      libsafe-iop.so libutils.so libcutils.so 
                              ${STANDARD_SYS_LIBS}
                      )

install(TARGETS dexdump DESTINATION bin)

