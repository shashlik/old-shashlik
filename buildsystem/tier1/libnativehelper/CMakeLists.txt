project(nativhelper)

#add_definitions(-DHAVE_SYS_UIO_H)
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../libnativehelper)
set(INCS_PATH ${REPO_PATH}/include/nativehelper)

set(nativhelper_SRCS
   ${REPO_PATH}/JniConstants.cpp
   ${REPO_PATH}/JNIHelp.cpp
   ${REPO_PATH}/JniInvocation.cpp
   ${REPO_PATH}/toStringArray.cpp
)

set(nativhelper_HEADERS
   ${INCS_PATH}/JniConstants.h
   ${INCS_PATH}/jni.h
   ${INCS_PATH}/JNIHelp.h
   ${INCS_PATH}/JniInvocation.h
   ${INCS_PATH}/ScopedBytes.h
   ${INCS_PATH}/ScopedFd.h
   ${INCS_PATH}/ScopedLocalFrame.h
   ${INCS_PATH}/ScopedLocalRef.h
   ${INCS_PATH}/ScopedPrimitiveArray.h
   ${INCS_PATH}/ScopedStringChars.h
   ${INCS_PATH}/ScopedUtfChars.h
   ${INCS_PATH}/toStringArray.h
   ${INCS_PATH}/UniquePtr.h
)

include_directories(${REPO_PATH} ${INCS_PATH})
include_directories(SYSTEM ${CMAKE_INSTALL_PREFIX}/include)
add_library(nativhelper SHARED ${nativhelper_SRCS})
install(TARGETS nativhelper DESTINATION lib)
install(FILES
        ${nativhelper_HEADERS}
        DESTINATION include/nativhelper)

