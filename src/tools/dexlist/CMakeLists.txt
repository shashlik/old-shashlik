project(dexlist)

set(REPO_PATH ${DALVIK_PATH})
include_directories(${REPO_PATH}
                    #${MOD_PATH}
                    ${LIBUTILS_INCLUDES}
                    ${LIBCUTILS_INCLUDES}
                    #${CMAKE_INSTALL_PREFIX}/include/android-libcore #FIXME
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

set(dexlist_SRCS
   ${REPO_PATH}/dexlist/DexList.cpp
)

link_directories(${CMAKE_INSTALL_PREFIX}/lib/)

add_executable(dexlist ${dexlist_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(dexlist PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

target_link_libraries(dexlist  dex
                               nativehelper
                               safe-iop
                               corkscrew log utils cutils  # Targets in this tree
                               z
                      )

install(TARGETS dexlist DESTINATION ${ANDROID_BIN_DIR})

