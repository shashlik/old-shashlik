project(libshashlikutils)

find_package(Qt5Core) # Yes, this is a hack. We need the 32bit libraries
#find_package(KF5Archive NO_MODULE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_BINARY_DIR}
                    ${QT5CORE32_INCLUDE_DIRS}
)

set(libshashlikutils_SRCS
    shashlikversion.cpp
)

set(libshashlikutils_HEADERS
    shashlikutils_export.h

    ${CMAKE_BINARY_DIR}/shashlikversion.h
)

include_directories(${Qt5Core_INCLUDE_DIRS})
add_library(shashlikutils SHARED ${libshashlikutils_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(shashlikutils PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

target_link_libraries(shashlikutils
		      #KF5::Archive
                      ${QT5CORE32_LIBRARIES}
)

install(TARGETS shashlikutils DESTINATION ${ANDROID_LIB_DIR})
install(FILES
        ${libshashlikutils_HEADERS}
        DESTINATION include)
