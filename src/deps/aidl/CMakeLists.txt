project(aidl)

find_package(BISON)
find_package(FLEX)

set(AIDL_PATH ${ANDROID_FRAMEWORKS_BASE}/tools/aidl)

set(aidl_SRCS
    ${AIDL_PATH}/aidl.cpp
    ${AIDL_PATH}/aidl_language.cpp
    ${AIDL_PATH}/options.cpp
    ${AIDL_PATH}/search_path.cpp
    ${AIDL_PATH}/AST.cpp
    ${AIDL_PATH}/Type.cpp
    ${AIDL_PATH}/generate_java.cpp
    ${AIDL_PATH}/generate_java_binder.cpp
    ${AIDL_PATH}/generate_java_rpc.cpp
)

set(aidl_Y_SRCS
    ${AIDL_PATH}/aidl_language_y.y
)

set(aidl_L_SRCS
    ${AIDL_PATH}/aidl_language_l.l
)

# we explicitly ask for .h here, otherwise a .hpp is generated, and that's not what the aidl sources expect
BISON_TARGET(aidl_language_y ${aidl_Y_SRCS} ${CMAKE_CURRENT_BINARY_DIR}/aidl_language_y.cpp COMPILE_FLAGS "--defines=${CMAKE_CURRENT_BINARY_DIR}/aidl_language_y.h")
FLEX_TARGET(aidl_language_l ${aidl_L_SRCS} ${CMAKE_CURRENT_BINARY_DIR}/aidl_language_l.cpp)
ADD_FLEX_BISON_DEPENDENCY(aidl_language_l aidl_language_y)

add_definitions(
    -DOS_PATH_SEPARATOR='/'
)
include_directories(
    ${AIDL_PATH}
    ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(aidl ${aidl_SRCS} ${BISON_aidl_language_y_OUTPUTS} ${FLEX_aidl_language_l_OUTPUTS})
# no installation, this is only used for generating things later on
