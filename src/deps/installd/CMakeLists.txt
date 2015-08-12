project(installd)

add_definitions(-fpermissive)

find_package(Qt5Core) # Yes, this is a hack. We need the 32bit libraries

set(REPO_PATH ${ANDROID_FRAMEWORKS_NATIVE_PATH}/cmds/installd)

set(installer_SRCS
    installer.cpp

    ${REPO_PATH}/commands.c
    ${REPO_PATH}/utils.c
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/libs/diskusage/dirsize.c
)

set(installd_SRCS
    ${REPO_PATH}/commands.c
    ${REPO_PATH}/utils.c
    ${REPO_PATH}/installd.c

    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/libs/diskusage/dirsize.c
)

add_executable(installer ${installer_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(installer PROPERTIES COMPILE_FLAGS "-m32 -fPIC" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(installer
    cutils
    log
    ${QT5CORE32_LIBRARIES}
)
target_include_directories(installer
    PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
    ${LIBCUTILS_INCLUDES}
    ${LIBLOG_INCLUDES}
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/include
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/cmds/installd
    ${ANDROID_CORE_PATH}/include
    ${QT5CORE32_INCLUDE_DIRS}
)

add_executable(installd ${installd_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(installd PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(installd
    cutils
    log
)
target_include_directories(installd
    PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
    ${LIBCUTILS_INCLUDES}
    ${LIBLOG_INCLUDES}
    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/include
    ${ANDROID_CORE_PATH}/include
)
install(TARGETS installd installer DESTINATION ${ANDROID_BIN_DIR})
