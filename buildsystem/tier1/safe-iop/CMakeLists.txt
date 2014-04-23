project(safe-iop)

add_definitions(-DHAVE_SYS_UIO_H)
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../safe-iop)

set(safe-iop_SRCS
    ${REPO_PATH}/src/safe_iop.c
)

set(safe-iop_HEADERS
    ${REPO_PATH}/include/safe_iop.h
)

include_directories(${REPO_PATH}/include)
add_library(safe-iop SHARED ${safe-iop_SRCS})
install(TARGETS safe-iop DESTINATION lib)
install(FILES
        ${safe-iop_HEADERS}
        DESTINATION include/safe-iop)

