project(libshashlikutils)

# generate shashlikversion.h
configure_file(shashlikversion.h.cmake ${CMAKE_BINARY_DIR}/shashlikversion.h)

#find_package(KF5Archive NO_MODULE)

#add_definitions(-DHAVE_SYS_UIO_H)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_BINARY_DIR}
)

set(libshashlikutils_SRCS
    shashlikversion.cpp
)

set(libshashlikutils_HEADERS
    shashlikutils_export.h

    ${CMAKE_BINARY_DIR}/shashlikversion.h
)

add_library(shashlikutils SHARED ${libshashlikutils_SRCS})

target_link_libraries(shashlikutils
		     # KF5::Archive Qt5::Core
)

install(TARGETS shashlikutils DESTINATION lib)
install(FILES
        ${libshashlikutils_HEADERS}
        DESTINATION include)
