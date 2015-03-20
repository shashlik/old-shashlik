project(lzf)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/liblzf)

set(lzf_SRCS
    ${REPO_PATH}/lzf_c.c
    ${REPO_PATH}/lzf_d.c
)

add_library(lzf SHARED ${lzf_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(lzf PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
install(TARGETS lzf DESTINATION ${ANDROID_LIB_DIR})
