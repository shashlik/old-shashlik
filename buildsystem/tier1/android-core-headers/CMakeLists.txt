project(android-core-headers)

set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../android-core)

set(android_HEADERS
    ${REPO_PATH}/include/android/log.h
)
set(system_HEADERS
    ${REPO_PATH}/include/system/graphics.h
    ${REPO_PATH}/include/system/thread_defs.h
)

install(FILES
        ${android_HEADERS}
        DESTINATION include/android)
install(FILES
        ${system_HEADERS}
        DESTINATION include/system)

