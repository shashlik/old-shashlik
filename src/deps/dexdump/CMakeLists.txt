project(dexdump)

set(REPO_PATH ${DALVIK_PATH})
include_directories(${REPO_PATH}
                    ${LIBCUTILS_INCLUDES}
                    #${CMAKE_INSTALL_PREFIX}/include/android-libcore  # FIXME
                    ${CMAKE_INSTALL_PREFIX}/include/nativehelper     # FIXME
)
include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include)

add_definitions(-DANDROID_SMP
                -DDVM_SHOW_EXCEPTION=1
                -DWITH_JIT                 # FIXME: Really? Also when JIT_VM is false?
                -DWITH_JIT_TUNING
                -DARCH_IA32
                -DARCH_VARIANT="x86"
                -DDVM_JMP_TABLE_MTERP=1
                -DMTERP_STUB
                -fpermissive
                -w
)


set(dexdump_SRCS
   ${REPO_PATH}/dexdump/DexDump.cpp
)


link_directories(${CMAKE_INSTALL_PREFIX}/lib/)

add_executable(dexdump ${dexdump_SRCS})
target_link_libraries(dexdump dex
                              libcorkscrew.so liblog.so libnativehelper.so # WIll be transformed later to target names
			      libsafe-iop.so libutils.so cutils 
                              ${STANDARD_SYS_LIBS}
                      )

install(TARGETS dexdump DESTINATION bin)

