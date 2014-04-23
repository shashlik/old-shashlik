project(dex)

#add_definitions(-D_GNU_SOURCE -DHAVE_LINUX_LOCAL_SOCKET_NAMESPACE -DHAVE_SYS_UIO_H -DHAVE_SYS_SOCKET_H -DHAVE_PTHREADS -DANDROID_SMP=1)
add_definitions(-DHAVE_SYS_UIO_H -DHAVE_OFF64_T)
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../dalvik)

set(dex_SRCS
    ${REPO_PATH}/libdex/CmdUtils.cpp
    ${REPO_PATH}/libdex/DexCatch.cpp
    ${REPO_PATH}/libdex/DexClass.cpp
    ${REPO_PATH}/libdex/DexDataMap.cpp
    ${REPO_PATH}/libdex/DexDebugInfo.cpp
    ${REPO_PATH}/libdex/DexFile.cpp
    ${REPO_PATH}/libdex/DexInlines.cpp
    ${REPO_PATH}/libdex/DexOpcodes.cpp
    ${REPO_PATH}/libdex/DexOptData.cpp
    ${REPO_PATH}/libdex/DexProto.cpp
    ${REPO_PATH}/libdex/DexSwapVerify.cpp
    ${REPO_PATH}/libdex/DexUtf.cpp
    ${REPO_PATH}/libdex/InstrUtils.cpp
    ${REPO_PATH}/libdex/Leb128.cpp
    ${REPO_PATH}/libdex/OptInvocation.cpp
    ${REPO_PATH}/libdex/sha1.cpp
    ${REPO_PATH}/libdex/SysUtil.cpp
    ${REPO_PATH}/libdex/ZipArchive.cpp
)

set(dex_HEADERS
    ${REPO_PATH}/libdex/CmdUtils.h
    ${REPO_PATH}/libdex/DexCatch.h
    ${REPO_PATH}/libdex/DexClass.h
    ${REPO_PATH}/libdex/DexDataMap.h
    ${REPO_PATH}/libdex/DexDebugInfo.h
    ${REPO_PATH}/libdex/DexFile.h
    ${REPO_PATH}/libdex/DexOpcodes.h
    ${REPO_PATH}/libdex/DexOptData.h
    ${REPO_PATH}/libdex/DexProto.h
    ${REPO_PATH}/libdex/DexUtf.h
    ${REPO_PATH}/libdex/InstrUtils.h
    ${REPO_PATH}/libdex/Leb128.h
    ${REPO_PATH}/libdex/OptInvocation.h
    ${REPO_PATH}/libdex/SysUtil.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${REPO_PATH})
include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include ${CMAKE_INSTALL_PREFIX}/include/safe-iop)
add_library(dex SHARED ${dex_SRCS})
install(TARGETS dex DESTINATION lib)
install(FILES
        ${dex_HEADERS}
        DESTINATION include/dex)

