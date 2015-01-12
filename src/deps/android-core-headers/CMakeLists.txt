project(android-core-headers)

set(android_HEADERS
    ${ANDROID_CORE_PATH}/include/android/log.h
)
set(system_HEADERS
    ${ANDROID_CORE_PATH}/include/system/graphics.h
    ${ANDROID_CORE_PATH}/include/system/thread_defs.h
)

install(FILES
        ${android_HEADERS}
        DESTINATION include/android)
install(FILES
        ${system_HEADERS}
        DESTINATION include/system)
