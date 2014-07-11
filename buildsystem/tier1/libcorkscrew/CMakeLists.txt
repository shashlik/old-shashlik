project(corkscrew)

add_definitions(-D_GNU_SOURCE -DCORKSCREW_HAVE_ARCH -DHAVE_SYS_UIO_H -std=c99)
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../android-core)
set(MOD_PATH ${REPO_PATH}/libcorkscrew)
set(INC_PATH ${REPO_PATH}/include/corkscrew)

set(corkscrew_SRCS
   ${MOD_PATH}/backtrace.c
   ${MOD_PATH}/backtrace-helper.c
   ${MOD_PATH}/demangle.c
   ${MOD_PATH}/map_info.c
   ${MOD_PATH}/ptrace.c
   ${MOD_PATH}/symbol_table.c
   ${MOD_PATH}/arch-x86/backtrace-x86.c
   ${MOD_PATH}/arch-x86/ptrace-x86.c
)

set(corkscrew_HEADERS
   ${INC_PATH}/backtrace.h
   ${INC_PATH}/demangle.h
   ${INC_PATH}/map_info.h
   ${INC_PATH}/ptrace.h
   ${INC_PATH}/symbol_table.h
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${REPO_PATH}/include)
add_library(corkscrew SHARED ${corkscrew_SRCS})
install(TARGETS corkscrew DESTINATION lib)
install(FILES
        ${corkscrew_HEADERS}
        DESTINATION include/corkscrew)
