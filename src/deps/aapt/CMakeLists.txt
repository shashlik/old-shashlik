project(aapt)

set(REPO_PATH ${ANDROID_FRAMEWORKS_BASE}/tools/aapt)

include(FindEXPAT)
find_package(EXPAT REQUIRED)
find_package(PNG REQUIRED)

set(aapt_SRCS
    ${REPO_PATH}/AaptAssets.cpp
    ${REPO_PATH}/Command.cpp
    ${REPO_PATH}/CrunchCache.cpp
    ${REPO_PATH}/FileFinder.cpp
    ${REPO_PATH}/Main.cpp
    ${REPO_PATH}/Package.cpp
    ${REPO_PATH}/StringPool.cpp
    ${REPO_PATH}/XMLNode.cpp
    ${REPO_PATH}/ResourceFilter.cpp
    ${REPO_PATH}/ResourceIdCache.cpp
    ${REPO_PATH}/ResourceTable.cpp
    ${REPO_PATH}/Images.cpp
    ${REPO_PATH}/Resource.cpp
    ${REPO_PATH}/pseudolocalize.cpp
    ${REPO_PATH}/SourcePos.cpp
    ${REPO_PATH}/WorkQueue.cpp
    ${REPO_PATH}/ZipEntry.cpp
    ${REPO_PATH}/ZipFile.cpp
    ${REPO_PATH}/qsort_r_compat.c
)

add_executable(aapt ${aapt_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(aapt PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
add_definitions(-Wno-format-y2k -DSTATIC_ANDROIDFW_FOR_TOOLS -DOS_PATH_SEPARATOR='/')
target_include_directories(aapt
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${ANDROID_FRAMEWORKS_BASE}/include
    ${LIBUTILS_INCLUDES}
    ${LIBCUTILS_INCLUDES}
    ${LIBLOG_INCLUDES}
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/include
    ${EXPAT_INCLUDE_DIRS}
    ${PNG_INCLUDE_DIRS}
)
target_link_libraries(aapt 
    androidfw log
    # system libraries
    ${EXPAT_LIBRARIES} ${PNG_LIBRARIES} rt dl)
install(TARGETS aapt DESTINATION ${ANDROID_BIN_DIR})
