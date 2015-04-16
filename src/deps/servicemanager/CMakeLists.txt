project(servicemanager)

set(REPO_PATH ${ANDROID_FRAMEWORKS_NATIVE_PATH}/cmds/servicemanager)

set(servicemanager_SRCS
    ${REPO_PATH}/service_manager.c
    ${REPO_PATH}/binder.c
)

add_executable(servicemanager ${servicemanager_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(servicemanager PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

target_include_directories(servicemanager
    PRIVATE
    ${LIBLOG_INCLUDES}
    ${LIBBINDER_INCLUDES}
)
target_link_libraries(servicemanager log)

install(TARGETS servicemanager DESTINATION ${ANDROID_BIN_DIR})
