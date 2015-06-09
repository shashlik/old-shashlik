project(protobuf)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/protobuf)

set(protobuf_cpp_SRCS
    ${REPO_PATH}/src/google/protobuf/stubs/common.cc
    ${REPO_PATH}/src/google/protobuf/stubs/once.cc
    ${REPO_PATH}/src/google/protobuf/stubs/hash.cc
    ${REPO_PATH}/src/google/protobuf/extension_set.cc
    ${REPO_PATH}/src/google/protobuf/generated_message_util.cc
    ${REPO_PATH}/src/google/protobuf/message_lite.cc
    ${REPO_PATH}/src/google/protobuf/repeated_field.cc
    ${REPO_PATH}/src/google/protobuf/wire_format_lite.cc
    ${REPO_PATH}/src/google/protobuf/io/coded_stream.cc
    ${REPO_PATH}/src/google/protobuf/io/zero_copy_stream.cc
    ${REPO_PATH}/src/google/protobuf/io/zero_copy_stream_impl_lite.cc
)

add_library(protobuf-cpp-2.3.0-lite SHARED ${protobuf_cpp_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(protobuf-cpp-2.3.0-lite PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_compile_definitions(protobuf-cpp-2.3.0-lite
    PUBLIC
    -DGOOGLE_PROTOBUF_NO_RTTI
)
target_include_directories(protobuf-cpp-2.3.0-lite
    PUBLIC
    ${REPO_PATH}/android
    ${REPO_PATH}/src

)
install(TARGETS protobuf-cpp-2.3.0-lite DESTINATION ${ANDROID_LIB_DIR})
