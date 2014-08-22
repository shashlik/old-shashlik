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
install(TARGETS safe-iop DESTINATION lib)
#install(FILES
#        ${safe-iop_HEADERS}
#        DESTINATION include/safe-iop)

