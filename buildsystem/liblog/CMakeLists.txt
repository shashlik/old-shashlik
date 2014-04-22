project(log)

add_definitions(-DHAVE_SYS_UIO_H)
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../android-core)

set(log_SRCS
    ${REPO_PATH}/liblog/event_tag_map.c
    ${REPO_PATH}/liblog/fake_log_device.c
    ${REPO_PATH}/liblog/logd_write.c
    ${REPO_PATH}/liblog/logprint.c
    ${REPO_PATH}/liblog/uio.c
)

set(log_HEADERS
    ${REPO_PATH}/include/logevent_tag_map.h
    ${REPO_PATH}/include/logd.h
    ${REPO_PATH}/include/logger.h
    ${REPO_PATH}/include/log.h
    ${REPO_PATH}/include/logprint.h
    ${REPO_PATH}/include/uio.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${REPO_PATH}/include)
add_library(log SHARED ${log_SRCS})
install(TARGETS log DESTINATION ${PROJ_PREFIX}/lib)
install(FILES
        ${log_HEADERS}
        DESTINATION ${PROJ_PREFIX}/include/log)

