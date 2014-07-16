project(hardware)

add_definitions(-DHAVE_SYS_UIO_H)
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../libhardware)
set(INC_PATH ${REPO_PATH}/include/hardware)
set(GRALLOC_PATH ${REPO_PATH}/modules/gralloc)


set(log_SRCS
    ${REPO_PATH}/hardware.c
    ${GRALLOC_PATH}/framebuffer.cpp
    ${GRALLOC_PATH}/gralloc.cpp
    ${GRALLOC_PATH}/mapper.cpp
)

set(log_HEADERS
    ${INC_PATH}/hardware.h
    ${INC_PATH}/gralloc.h
    ${INC_PATH}/fb.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${REPO_PATH}/include)
add_library(hardware SHARED ${log_SRCS})
install(TARGETS hardware DESTINATION lib)
install(FILES
        ${log_HEADERS}
        DESTINATION include/hardware)

