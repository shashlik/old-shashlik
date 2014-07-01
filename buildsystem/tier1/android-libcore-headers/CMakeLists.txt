project(android-libcore-headers)

#add_definitions(-DHAVE_SYS_UIO_H)
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../android-libcore)

set(android_HEADERS
   ${REPO_PATH}/include/LocalArray.h
   ${REPO_PATH}/include/ScopedJavaUnicodeString.h
   ${REPO_PATH}/include/ScopedPthreadMutexLock.h
   ${REPO_PATH}/include/StaticAssert.h
)

install(FILES
        ${android_HEADERS}
        DESTINATION include/android-libcore)

