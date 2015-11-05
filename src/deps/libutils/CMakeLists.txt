project(utils)

find_package(Qt5Core) # Yes, this is a hack. We need the 32bit libraries

set(REPO_PATH ${ANDROID_CORE_PATH})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${LIBCUTILS_INCLUDES}
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/include
    ${QT5CORE32_INCLUDE_DIRS}
)

add_definitions(-DHAVE_POSIX_FILEMAP
                -DHAVE_OFF64_T
                -DHAVE_SYS_UIO_H
                -DHAVE_PTHREADS
                -DOS_PATH_SEPARATOR='/'
                -DANDROID_SMP=1
                -DHAVE_ANDROID_OS   # To make android threads work.  FIXME: Check what other consequences this has.
)

set(utils_SRCS
   ${REPO_PATH}/libutils/BasicHashtable.cpp
   ${REPO_PATH}/libutils/BlobCache.cpp
   ${REPO_PATH}/libutils/CallStack.cpp
   ${REPO_PATH}/libutils/FileMap.cpp
   ${REPO_PATH}/libutils/JenkinsHash.cpp
   ${REPO_PATH}/libutils/LinearAllocator.cpp
   ${REPO_PATH}/libutils/LinearTransform.cpp
   ${REPO_PATH}/libutils/Log.cpp
   ${REPO_PATH}/libutils/Looper.cpp
   ${REPO_PATH}/libutils/misc.cpp
   ${REPO_PATH}/libutils/PropertyMap.cpp
   ${REPO_PATH}/libutils/RefBase.cpp
   ${REPO_PATH}/libutils/SharedBuffer.cpp
   ${REPO_PATH}/libutils/Static.cpp
   ${REPO_PATH}/libutils/StopWatch.cpp
   ${REPO_PATH}/libutils/String16.cpp
   ${REPO_PATH}/libutils/String8.cpp
   ${REPO_PATH}/libutils/SystemClock.cpp
   ${REPO_PATH}/libutils/Threads.cpp
   ${REPO_PATH}/libutils/Timers.cpp
   ${REPO_PATH}/libutils/Tokenizer.cpp
   ${REPO_PATH}/libutils/Trace.cpp
   ${REPO_PATH}/libutils/Unicode.cpp
   ${REPO_PATH}/libutils/VectorImpl.cpp
)

set(utils_HEADERS
   ${REPO_PATH}/include/utils/AndroidThreads.h
   #    ${REPO_PATH}/include/utils/ashmem.h
   ${REPO_PATH}/include/utils/Atomic.h
   ${REPO_PATH}/include/utils/BasicHashtable.h
   ${REPO_PATH}/include/utils/BitSet.h
   ${REPO_PATH}/include/utils/BlobCache.h
   ${REPO_PATH}/include/utils/ByteOrder.h
   ${REPO_PATH}/include/utils/CallStack.h
   ${REPO_PATH}/include/utils/Compat.h
   ${REPO_PATH}/include/utils/Condition.h
   ${REPO_PATH}/include/utils/Debug.h
   ${REPO_PATH}/include/utils/Endian.h
   ${REPO_PATH}/include/utils/Errors.h
   ${REPO_PATH}/include/utils/FileMap.h
   ${REPO_PATH}/include/utils/Flattenable.h
   ${REPO_PATH}/include/utils/Functor.h
   ${REPO_PATH}/include/utils/JenkinsHash.h
   ${REPO_PATH}/include/utils/KeyedVector.h
   ${REPO_PATH}/include/utils/LinearAllocator.h
   ${REPO_PATH}/include/utils/LinearTransform.h
   ${REPO_PATH}/include/utils/List.h
   ${REPO_PATH}/include/utils/Log.h
   ${REPO_PATH}/include/utils/Looper.h
   ${REPO_PATH}/include/utils/LruCache.h
   ${REPO_PATH}/include/utils/misc.h
   ${REPO_PATH}/include/utils/Mutex.h
   ${REPO_PATH}/include/utils/PropertyMap.h
   ${REPO_PATH}/include/utils/RefBase.h
   ${REPO_PATH}/include/utils/RWLock.h
   ${REPO_PATH}/include/utils/SharedBuffer.h
   ${REPO_PATH}/include/utils/Singleton.h
   ${REPO_PATH}/include/utils/SortedVector.h
   ${REPO_PATH}/include/utils/StopWatch.h
   ${REPO_PATH}/include/utils/String16.h
   ${REPO_PATH}/include/utils/String8.h
   ${REPO_PATH}/include/utils/StrongPointer.h
   ${REPO_PATH}/include/utils/SystemClock.h
   ${REPO_PATH}/include/utils/ThreadDefs.h
   ${REPO_PATH}/include/utils/Thread.h
   ${REPO_PATH}/include/utils/threads.h
   ${REPO_PATH}/include/utils/Timers.h
   ${REPO_PATH}/include/utils/Tokenizer.h
   ${REPO_PATH}/include/utils/Trace.h
   ${REPO_PATH}/include/utils/TypeHelpers.h
   ${REPO_PATH}/include/utils/Unicode.h
   ${REPO_PATH}/include/utils/UniquePtr.h
   ${REPO_PATH}/include/utils/Vector.h
   ${REPO_PATH}/include/utils/VectorImpl.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${REPO_PATH}/include)
add_library(utils SHARED ${utils_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(utils PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(utils
    pthread
    corkscrew
    ${QT5CORE32_LIBRARIES}
)

install(TARGETS utils DESTINATION ${ANDROID_LIB_DIR})
install(FILES
        ${utils_HEADERS}
        DESTINATION include/utils)

