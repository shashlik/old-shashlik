project(libapk)

# Copied from buildsystems/tier1/liblog/CMakeLists.txt.  Remove when this builds correctly
#add_definitions(-DHAVE_SYS_UIO_H)
#set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../android-core)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    # Add more here, e.g. from the KArchive framework
                    )

set(libapk_SRCS
    ApkFile.cpp
)

set(libapk_HEADERS
    ApkFile.h
)

add_library(libapk SHARED ${libapk_SRCS})
install(TARGETS libapk DESTINATION lib)
install(FILES
        ${log_HEADERS}
        DESTINATION include/libapk)
