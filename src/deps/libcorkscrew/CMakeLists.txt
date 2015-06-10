project(corkscrew)

set(REPO_PATH ${ANDROID_CORE_PATH})
set(MOD_PATH ${REPO_PATH}/libcorkscrew)
set(INC_PATH ${REPO_PATH}/include/corkscrew)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${LIBCORKSCREW_INCLUDES}
)

add_definitions(-D_GNU_SOURCE
                -DCORKSCREW_HAVE_ARCH
                -std=c99
)

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

add_library(corkscrew SHARED ${corkscrew_SRCS})
target_link_libraries(corkscrew
    dl
)
if(FORCE_32BIT_BUILD)
    set_target_properties(corkscrew PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

install(TARGETS corkscrew DESTINATION ${ANDROID_LIB_DIR})
#install(FILES
#        ${corkscrew_HEADERS}
#        DESTINATION include/corkscrew)
