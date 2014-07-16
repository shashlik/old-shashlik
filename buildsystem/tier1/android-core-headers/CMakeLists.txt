project(android-core-headers)

#add_definitions(-DHAVE_SYS_UIO_H)
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../android-core)

set(android_HEADERS
    ${REPO_PATH}/include/android/log.h
)

install(FILES
        ${android_HEADERS}
        DESTINATION include/android)

set(SYSTEM_INC ${REPO_PATH}/include/system)
set(system_HEADERS
    ${SYSTEM_INC}/audio.h
    ${SYSTEM_INC}/audio_policy.h
    ${SYSTEM_INC}/camera.h
    ${SYSTEM_INC}/graphics.h
    ${SYSTEM_INC}/thread_defs.h
    ${SYSTEM_INC}/window.h
)

install(FILES
        ${system_HEADERS}
        DESTINATION include/system)

