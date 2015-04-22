project(safe-iop)

set(REPO_PATH ${SAFE_IOP_PATH}
)

include_directories(${REPO_PATH}/include)

set(safe-iop_SRCS
    ${REPO_PATH}/src/safe_iop.c
)

set(safe-iop_HEADERS
    ${REPO_PATH}/include/safe_iop.h
)

add_library(safe-iop SHARED ${safe-iop_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(safe-iop PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
install(TARGETS safe-iop DESTINATION ${ANDROID_LIB_DIR})
#install(FILES
#        ${safe-iop_HEADERS}
#        DESTINATION include/safe-iop)

