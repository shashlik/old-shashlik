project(android-core-headers)

#add_definitions(-DHAVE_SYS_UIO_H)
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../android-core)

set(android_HEADERS
    ${REPO_PATH}/include/android/log.h
)

install(FILES
        ${android_HEADERS}
        DESTINATION include/android)

