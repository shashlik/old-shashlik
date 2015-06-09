project(libziparchive)

set(ziparchive_SRCS
    zip_archive.cc
)

add_library(ziparchive SHARED ${ziparchive_SRCS})
target_include_directories(ziparchive
    PRIVATE
    ${LIBLOG_INCLUDES}
)
target_link_libraries(ziparchive
    base
)
if(FORCE_32BIT_BUILD)
    set_target_properties(ziparchive PROPERTIES COMPILE_FLAGS "-m32 -std=c++11" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
install(TARGETS ziparchive DESTINATION ${ANDROID_LIB_DIR})
