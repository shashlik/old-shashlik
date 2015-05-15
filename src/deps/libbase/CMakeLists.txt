project(libbase)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/core-head/base)

set(base_SRCS
    ${REPO_PATH}/file.cpp
    ${REPO_PATH}/logging.cpp
    ${REPO_PATH}/stringprintf.cpp
    ${REPO_PATH}/strings.cpp
)

add_library(base SHARED ${base_SRCS})
target_include_directories(base
    PRIVATE
    ${LIBCUTILS_INCLUDES}
    ${LIBLOG_INCLUDES}
    PUBLIC
    ${REPO_PATH}/include
)
target_link_libraries(base
    PRIVATE
    stripped_bionic
)
target_compile_definitions(base
    PRIVATE
    -D__ANDROID__
)
if(FORCE_32BIT_BUILD)
    set_target_properties(base PROPERTIES COMPILE_FLAGS "-m32 -std=c++11" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
install(TARGETS base DESTINATION ${ANDROID_LIB_DIR})
