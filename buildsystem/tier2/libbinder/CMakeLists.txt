project(binder)

add_definitions(-DHAVE_SYS_UIO_H -fpermissive)
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../android-frameworks-native)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${REPO_PATH}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${REPO_PATH}/include
	            ${CMAKE_INSTALL_PREFIX}/include
)

set(binder_SRCS
    #    ${REPO_PATH}/libs/binder/AppOpsManager.cpp
    ${REPO_PATH}/libs/binder/Binder.cpp
    #    ${REPO_PATH}/libs/binder/BpBinder.cpp
    #    ${REPO_PATH}/libs/binder/BufferedTextOutput.cpp
    #    ${REPO_PATH}/libs/binder/Debug.cpp
    #    ${REPO_PATH}/libs/binder/IAppOpsCallback.cpp
    #    ${REPO_PATH}/libs/binder/IAppOpsService.cpp
    #    ${REPO_PATH}/libs/binder/IInterface.cpp
    #    ${REPO_PATH}/libs/binder/IMemory.cpp
    #    ${REPO_PATH}/libs/binder/IPCThreadState.cpp
    #    ${REPO_PATH}/libs/binder/IPermissionController.cpp
    #    ${REPO_PATH}/libs/binder/IServiceManager.cpp
    #    ${REPO_PATH}/libs/binder/MemoryBase.cpp
    #    ${REPO_PATH}/libs/binder/MemoryDealer.cpp
    #    ${REPO_PATH}/libs/binder/MemoryHeapBase.cpp
    #    ${REPO_PATH}/libs/binder/Parcel.cpp
    #    ${REPO_PATH}/libs/binder/PermissionCache.cpp
    #    ${REPO_PATH}/libs/binder/ProcessState.cpp
    #    ${REPO_PATH}/libs/binder/Static.cpp
    #    ${REPO_PATH}/libs/binder/TextOutput.cpp
)

set(binder_HEADERS
    #    ${REPO_PATH}/include/binder/AppOpsManager.h
    ${REPO_PATH}/include/binder/Binder.h
    #    ${REPO_PATH}/include/binder/BinderService.h
    ${REPO_PATH}/include/binder/BpBinder.h
    #    ${REPO_PATH}/include/binder/BufferedTextOutput.h
    #    ${REPO_PATH}/include/binder/Debug.h
    #    ${REPO_PATH}/include/binder/IAppOpsCallback.h
    #    ${REPO_PATH}/include/binder/IAppOpsService.h
    ${REPO_PATH}/include/binder/IBinder.h
    ${REPO_PATH}/include/binder/IInterface.h
    #    ${REPO_PATH}/include/binder/IMemory.h
    #    ${REPO_PATH}/include/binder/IPCThreadState.h
    #    ${REPO_PATH}/include/binder/IPermissionController.h
    #    ${REPO_PATH}/include/binder/IServiceManager.h
    #    ${REPO_PATH}/include/binder/MemoryBase.h
    #    ${REPO_PATH}/include/binder/MemoryDealer.h
    #    ${REPO_PATH}/include/binder/MemoryHeapBase.h
    ${REPO_PATH}/include/binder/Parcel.h
    #    ${REPO_PATH}/include/binder/PermissionCache.h
    #    ${REPO_PATH}/include/binder/ProcessState.h
    #    ${REPO_PATH}/include/binder/TextOutput.h

    #    ${REPO_PATH}/include/private/binder/binder_module.h
    #    ${REPO_PATH}/include/private/binder/Static.h
)

add_library(binder SHARED ${binder_SRCS})
install(TARGETS binder DESTINATION lib)
install(FILES
        ${binder_HEADERS}
        DESTINATION include/binder)

