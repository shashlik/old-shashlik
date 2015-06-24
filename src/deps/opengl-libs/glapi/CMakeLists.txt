project(glapi)

include(FindPythonInterp)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/mesa/src/mapi)

set(abi_header "shared-glapi/glapi_mapi_tmp.h")

set(glapi_SRCS
    ${REPO_PATH}/entry.c
    ${REPO_PATH}/mapi_glapi.c
    ${REPO_PATH}/stub.c
    ${REPO_PATH}/table.c
    ${REPO_PATH}/u_current.c
    ${REPO_PATH}/u_execmem.c
    ${CMAKE_CURRENT_BINARY_DIR}/${abi_header}
)

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${abi_header}
    COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/shared-glapi
    COMMAND ${PYTHON_EXECUTABLE} ${REPO_PATH}/mapi_abi.py --printer shared-glapi --mode lib ${REPO_PATH}/glapi/gen/gl_and_es_API.xml > ${CMAKE_CURRENT_BINARY_DIR}/${abi_header}
)

add_library(glapi SHARED ${glapi_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(glapi PROPERTIES COMPILE_FLAGS "-m32 -std=gnu99" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_compile_definitions(glapi
    PRIVATE
    -DMAPI_MODE_GLAPI
    -DMAPI_ABI_HEADER="${abi_header}"
    -DHAVE_PTHREAD
)
target_include_directories(glapi
    PRIVATE
    ${REPO_PATH}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${GENERAL_SOURCE_PATH}/mesa/include
    ${GENERAL_SOURCE_PATH}/mesa/src
)

install(TARGETS glapi DESTINATION ${ANDROID_LIB_DIR})
