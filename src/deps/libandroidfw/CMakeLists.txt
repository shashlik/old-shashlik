project(androidfw)

set(ANDROIDFW_SRC_DIR ${ANDROID_FRAMEWORKS_BASE}/libs/androidfw)

set(androidfw_SRCS
    ${ANDROIDFW_SRC_DIR}/Asset.cpp
    ${ANDROIDFW_SRC_DIR}/AssetDir.cpp
    ${ANDROIDFW_SRC_DIR}/AssetManager.cpp
    ${ANDROIDFW_SRC_DIR}/misc.cpp
    ${ANDROIDFW_SRC_DIR}/ObbFile.cpp
    ${ANDROIDFW_SRC_DIR}/ResourceTypes.cpp
    ${ANDROIDFW_SRC_DIR}/StreamingZipInflater.cpp
    ${ANDROIDFW_SRC_DIR}/ZipFileRO.cpp
    ${ANDROIDFW_SRC_DIR}/ZipUtils.cpp

# the device specific sources, because we are creating a target
    ${ANDROIDFW_SRC_DIR}/BackupData.cpp
    ${ANDROIDFW_SRC_DIR}/BackupHelpers.cpp
    ${ANDROIDFW_SRC_DIR}/CursorWindow.cpp
)

add_library(androidfw SHARED ${androidfw_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(androidfw PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
#target_include_directories(icu4c zlib)
target_include_directories(androidfw
    PUBLIC
    ${ANDROID_FRAMEWORKS_BASE}/include
    PRIVATE
    ${LIBUTILS_INCLUDES}
    ${LIBCUTILS_INCLUDES}
    ${LIBLOG_INCLUDES}
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/include
)
target_link_libraries(androidfw
    binder
#     cutils
#     utils
    z
)
install(TARGETS androidfw DESTINATION ${ANDROID_LIB_DIR})
