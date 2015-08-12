project(zipfile)

set(REPO_PATH ${ANDROID_CORE_PATH}/libzipfile)

set(zipfile_SRCS
    ${REPO_PATH}/centraldir.c
    ${REPO_PATH}/zipfile.c
)

add_library(zipfile STATIC ${zipfile_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(zipfile PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(zipfile
    z
)
target_include_directories(zipfile
    PUBLIC
    ${ANDROID_CORE_PATH}/include
)
