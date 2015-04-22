project(binder)

set(REPO_PATH ${ANDROID_FRAMEWORKS_NATIVE_PATH})
set(MODULE_PATH ${REPO_PATH}/libs/binder)
set(INCLUDE_PATH ${REPO_PATH}/include/binder)
include_directories(
                    ${CMAKE_CURRENT_SOURCE_DIR}
#                    ${REPO_PATH}/include
                    ${LIBBINDER_INCLUDES}
                    ${LIBUTILS_INCLUDES}
                    ${LIBCUTILS_INCLUDES}
)
#message("INC DIRS ARE ${LIBBINDER_INCLUDES}")

add_definitions(-fpermissive                # for redeclaration of  char32_t
)

set(binder_LIB_SRCS
    ${MODULE_PATH}/AppOpsManager.cpp
    ${MODULE_PATH}/Binder.cpp
    ${MODULE_PATH}/BpBinder.cpp
    ${MODULE_PATH}/BufferedTextOutput.cpp
    ${MODULE_PATH}/Debug.cpp
    ${MODULE_PATH}/IAppOpsCallback.cpp
    ${MODULE_PATH}/IAppOpsService.cpp
    ${MODULE_PATH}/IInterface.cpp
    ${MODULE_PATH}/IMemory.cpp
    ${MODULE_PATH}/IPCThreadState.cpp
    ${MODULE_PATH}/IPermissionController.cpp
    ${MODULE_PATH}/IServiceManager.cpp
    ${MODULE_PATH}/MemoryBase.cpp
    ${MODULE_PATH}/MemoryDealer.cpp
    ${MODULE_PATH}/MemoryHeapBase.cpp
    ${MODULE_PATH}/Parcel.cpp
    ${MODULE_PATH}/PermissionCache.cpp
    ${MODULE_PATH}/ProcessState.cpp
    ${MODULE_PATH}/Static.cpp
    ${MODULE_PATH}/TextOutput.cpp
)

set(binder_LIB_HEADERS
    #    ${INCLUDE_PATH}/AppOpsManager.h
    ${INCLUDE_PATH}/Binder.h
    #    ${INCLUDE_PATH}/BinderService.h
    ${INCLUDE_PATH}/BpBinder.h
    ${INCLUDE_PATH}/BufferedTextOutput.h
    ${INCLUDE_PATH}/Debug.h
    #    ${INCLUDE_PATH}/IAppOpsCallback.h
    #    ${INCLUDE_PATH}/IAppOpsService.h
    ${INCLUDE_PATH}/IBinder.h
    ${INCLUDE_PATH}/IInterface.h
    #    ${INCLUDE_PATH}/IMemory.h
    ${INCLUDE_PATH}/IPCThreadState.h
    #    ${INCLUDE_PATH}/IPermissionController.h
    #    ${INCLUDE_PATH}/IServiceManager.h
    #    ${INCLUDE_PATH}/MemoryBase.h
    #    ${INCLUDE_PATH}/MemoryDealer.h
    #    ${INCLUDE_PATH}/MemoryHeapBase.h
    ${INCLUDE_PATH}/Parcel.h
    #    ${INCLUDE_PATH}/PermissionCache.h
    ${INCLUDE_PATH}/ProcessState.h
    ${INCLUDE_PATH}/TextOutput.h

    #    ${REPO_PATH}/include/private/binder/binder_module.h
    ${REPO_PATH}/include/private/binder/Static.h
)

link_directories(${CMAKE_INSTALL_PREFIX}/lib/
                 #${CMAKE_CURRENT_BINARY_DIR}/libdex/  # For linking dexdump, dexlist and dexgen
                 )

add_library(binder SHARED ${binder_LIB_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(binder PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

target_compile_definitions(binder
    PUBLIC
#    -DBINDER_IPC_32BIT
    -DHAVE_ANDROID_OS
)
target_link_libraries(binder
                      log utils cutils
                      )

install(TARGETS binder DESTINATION ${ANDROID_LIB_DIR})
install(FILES
        ${binder_LIB_HEADERS}
        DESTINATION include/binder)

