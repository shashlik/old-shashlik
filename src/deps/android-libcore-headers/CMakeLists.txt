project(android-libcore-headers)

#add_definitions(-DHAVE_SYS_UIO_H)

set(android_HEADERS
   ${ANDROID_LIBCORE_PATH}/include/LocalArray.h
   ${ANDROID_LIBCORE_PATH}/include/ScopedJavaUnicodeString.h
   ${ANDROID_LIBCORE_PATH}/include/ScopedPthreadMutexLock.h
   ${ANDROID_LIBCORE_PATH}/include/StaticAssert.h
)

install(FILES
        ${android_HEADERS}
        DESTINATION include/android-libcore)

