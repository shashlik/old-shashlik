project(libshashlikutils)

# generate shashlikversion.h
configure_file(shashlikversion.h.cmake ${CMAKE_BINARY_DIR}/shashlikversion.h)

find_package(Qt5 ${REQUIRED_QT_VERSION} CONFIG REQUIRED Core)
if(FORCE_32BIT_BUILD)
    STRING(REPLACE "lib64" "lib" Qt5Core_LIBRARIES ${Qt5Core_LIBRARIES})
endif(FORCE_32BIT_BUILD)
#find_package(KF5Archive NO_MODULE)

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
if(FORCE_32BIT_BUILD)
    set_target_properties(shashlikutils PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

target_link_libraries(shashlikutils
		      #KF5::Archive
                      Qt5::Core
)

install(TARGETS shashlikutils DESTINATION lib)
install(FILES
        ${libshashlikutils_HEADERS}
        DESTINATION include)
