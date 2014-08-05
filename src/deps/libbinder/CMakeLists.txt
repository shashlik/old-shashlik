project(binder)

set(REPO_PATH ${ANDROID_FRAMEWORKS_NATIVE_PATH})
include_directories(${LIBBINDER_INCLUDES})

add_definitions(-DHAVE_SYS_UIO_H
                -DHAVE_PTHREADS -pthread    # for IPCThreadState.cpp
                -fpermissive                # for redeclaration of  char32_t
)

set(binder_LIB_SRCS
    #    ${REPO_PATH}/libs/binder/AppOpsManager.cpp
    ${REPO_PATH}/libs/binder/Binder.cpp
    ${REPO_PATH}/libs/binder/BpBinder.cpp
    ${REPO_PATH}/libs/binder/BufferedTextOutput.cpp
    ${REPO_PATH}/libs/binder/Debug.cpp
    #    ${REPO_PATH}/libs/binder/IAppOpsCallback.cpp
    #    ${REPO_PATH}/libs/binder/IAppOpsService.cpp
    #    ${REPO_PATH}/libs/binder/IInterface.cpp
    #    ${REPO_PATH}/libs/binder/IMemory.cpp
    ${REPO_PATH}/libs/binder/IPCThreadState.cpp
    #    ${REPO_PATH}/libs/binder/IPermissionController.cpp
    #    ${REPO_PATH}/libs/binder/IServiceManager.cpp
    #    ${REPO_PATH}/libs/binder/MemoryBase.cpp
    #    ${REPO_PATH}/libs/binder/MemoryDealer.cpp
    #    ${REPO_PATH}/libs/binder/MemoryHeapBase.cpp
    ${REPO_PATH}/libs/binder/Parcel.cpp
    #    ${REPO_PATH}/libs/binder/PermissionCache.cpp
    ${REPO_PATH}/libs/binder/ProcessState.cpp
    ${REPO_PATH}/libs/binder/Static.cpp
    ${REPO_PATH}/libs/binder/TextOutput.cpp
)

set(binder_LIB_HEADERS
    #    ${REPO_PATH}/include/binder/AppOpsManager.h
    ${REPO_PATH}/include/binder/Binder.h
    #    ${REPO_PATH}/include/binder/BinderService.h
    ${REPO_PATH}/include/binder/BpBinder.h
    ${REPO_PATH}/include/binder/BufferedTextOutput.h
    ${REPO_PATH}/include/binder/Debug.h
    #    ${REPO_PATH}/include/binder/IAppOpsCallback.h
    #    ${REPO_PATH}/include/binder/IAppOpsService.h
    ${REPO_PATH}/include/binder/IBinder.h
    ${REPO_PATH}/include/binder/IInterface.h
    #    ${REPO_PATH}/include/binder/IMemory.h
    ${REPO_PATH}/include/binder/IPCThreadState.h
    #    ${REPO_PATH}/include/binder/IPermissionController.h
    #    ${REPO_PATH}/include/binder/IServiceManager.h
    #    ${REPO_PATH}/include/binder/MemoryBase.h
    #    ${REPO_PATH}/include/binder/MemoryDealer.h
    #    ${REPO_PATH}/include/binder/MemoryHeapBase.h
    ${REPO_PATH}/include/binder/Parcel.h
    #    ${REPO_PATH}/include/binder/PermissionCache.h
    ${REPO_PATH}/include/binder/ProcessState.h
    ${REPO_PATH}/include/binder/TextOutput.h

    #    ${REPO_PATH}/include/private/binder/binder_module.h
    ${REPO_PATH}/include/private/binder/Static.h
)

link_directories(${CMAKE_INSTALL_PREFIX}/lib/
                 #${CMAKE_CURRENT_BINARY_DIR}/libdex/  # For linking dexdump, dexlist and dexgen
                 )

add_library(binder SHARED ${binder_LIB_SRCS})
target_link_libraries(binder log utils cutils
			     ${STANDARD_SYS_LIBS}
                      )

install(TARGETS binder DESTINATION lib)
install(FILES
        ${binder_LIB_HEADERS}
        DESTINATION include/binder)

