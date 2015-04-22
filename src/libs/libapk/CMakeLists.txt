project(libapk)

find_package(KF5Archive NO_MODULE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(libapk_SRCS
    ApkFile.cpp
)

set(libapk_HEADERS
    ApkFile.h
)

add_library(apk SHARED ${libapk_SRCS})

target_link_libraries(apk KF5::Archive Qt5::Core)

install(TARGETS apk DESTINATION ${ANDROID_LIB_DIR})
install(FILES
        ${libapk_HEADERS}
        DESTINATION include/libapk)
