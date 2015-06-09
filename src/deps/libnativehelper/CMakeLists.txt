project(nativehelper)

#add_definitions(-DHAVE_SYS_UIO_H)
add_definitions(-fpermissive) # To allow cast from char* to int

set(nativehelper_SRCS
   ${NATIVEHELPER_PATH}/JniConstants.cpp
   ${NATIVEHELPER_PATH}/JNIHelp.cpp
   ${NATIVEHELPER_PATH}/JniInvocation.cpp
   ${NATIVEHELPER_PATH}/toStringArray.cpp
)

set(nativehelper_HEADERS
   ${LIBNATIVEHELPER_INCLUDES}/JniConstants.h
   ${LIBNATIVEHELPER_INCLUDES}/jni.h
   ${LIBNATIVEHELPER_INCLUDES}/JNIHelp.h
   ${LIBNATIVEHELPER_INCLUDES}/JniInvocation.h
   ${LIBNATIVEHELPER_INCLUDES}/ScopedBytes.h
   ${LIBNATIVEHELPER_INCLUDES}/ScopedFd.h
   ${LIBNATIVEHELPER_INCLUDES}/ScopedLocalFrame.h
   ${LIBNATIVEHELPER_INCLUDES}/ScopedLocalRef.h
   ${LIBNATIVEHELPER_INCLUDES}/ScopedPrimitiveArray.h
   ${LIBNATIVEHELPER_INCLUDES}/ScopedStringChars.h
   ${LIBNATIVEHELPER_INCLUDES}/ScopedUtfChars.h
   ${LIBNATIVEHELPER_INCLUDES}/toStringArray.h
   ${LIBNATIVEHELPER_INCLUDES}/UniquePtr.h
)

include_directories(${LIBNATIVEHELPER_INCLUDES})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../../android-core/include) # for android/log.h
include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include)

add_library(nativehelper SHARED ${nativehelper_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(nativehelper PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(nativehelper dl)

install(TARGETS nativehelper DESTINATION ${ANDROID_LIB_DIR})
install(FILES
        ${nativehelper_HEADERS}
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/nativehelper)
