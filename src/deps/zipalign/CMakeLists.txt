project(zipalign)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/android-build/tools/zipalign)

set(zipalign_SRCS
    ${REPO_PATH}/ZipAlign.cpp
    ${REPO_PATH}/ZipEntry.cpp
    ${REPO_PATH}/ZipFile.cpp
)

add_executable(zipalign ${zipalign_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(zipalign PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_include_directories(zipalign
    PRIVATE
    ${LIBLOG_INCLUDES}
)
target_link_libraries(zipalign
    rt z pthread
    androidfw
    utils
    cutils
    log
)
