project(dex)

#add_definitions(-DHAVE_SYS_UIO_H)
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../dalvik)

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
    ${REPO_PATH}/include/dex/CmdUtils.h
    ${REPO_PATH}/include/dex/DexCatch.h
    ${REPO_PATH}/include/dex/DexClass.h
    ${REPO_PATH}/include/dex/DexDataMap.h
    ${REPO_PATH}/include/dex/DexDebugInfo.h
    ${REPO_PATH}/include/dex/DexFile.h
    ${REPO_PATH}/include/dex/DexOpcodes.h
    ${REPO_PATH}/include/dex/DexOptData.h
    ${REPO_PATH}/include/dex/DexProto.h
    ${REPO_PATH}/include/dex/DexUtf.h
    ${REPO_PATH}/include/dex/InstrUtils.h
    ${REPO_PATH}/include/dex/Leb128.h
    ${REPO_PATH}/include/dex/OptInvocation.h
    ${REPO_PATH}/include/dex/SysUtil.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${REPO_PATH})
include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include)
add_library(dex SHARED ${dex_SRCS})
install(TARGETS dex DESTINATION lib)
install(FILES
        ${dex_HEADERS}
        DESTINATION include/dex)

