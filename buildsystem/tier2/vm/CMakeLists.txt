project(vm)

#add_definitions(-DHAVE_SYS_UIO_H)
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../dalvik)

#set(vm_SRCS
#    ${REPO_PATH}/vm/
#)

set(vm_HEADERS
    ${REPO_PATH}/vm/Common.h
    ${REPO_PATH}/vm/DalvikVersion.h
)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${REPO_PATH}/include)
#add_library(vm SHARED ${vm_SRCS})
#install(TARGETS vm DESTINATION lib)
install(FILES
        ${vm_HEADERS}
        DESTINATION include/dex)

