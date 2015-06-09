project(pixelflinger)


set(REPO_PATH ${ANDROID_CORE_PATH})
set(MOD_PATH ${REPO_PATH}/libpixelflinger)
set(INC_PATH ${REPO_PATH}/include/pixelflinger)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${REPO_PATH}/include   # FIXME: LIBPIXELFLINGER_INCLUDES
)

add_definitions(-D_GNU_SOURCE
                -DCORKSCREW_HAVE_ARCH
                -fpermissive  # FIXME: for pointer to int conversion in printf on x86_64
)

set(pixelflinger_SRCS
   ${MOD_PATH}/codeflinger/ARMAssemblerInterface.cpp
   ${MOD_PATH}/codeflinger/ARMAssemblerProxy.cpp
   ${MOD_PATH}/codeflinger/ARMAssembler.cpp
   ${MOD_PATH}/codeflinger/CodeCache.cpp
   ${MOD_PATH}/codeflinger/GGLAssembler.cpp
   ${MOD_PATH}/codeflinger/load_store.cpp
   ${MOD_PATH}/codeflinger/blending.cpp
   ${MOD_PATH}/codeflinger/texturing.cpp
   ${MOD_PATH}/codeflinger/disassem.c
   ${MOD_PATH}/codeflinger/tinyutils/SharedBuffer.cpp
   ${MOD_PATH}/codeflinger/tinyutils/VectorImpl.cpp
   ${MOD_PATH}/fixed.cpp
   ${MOD_PATH}/picker.cpp
   ${MOD_PATH}/pixelflinger.cpp
   ${MOD_PATH}/trap.cpp
   ${MOD_PATH}/scanline.cpp
   ${MOD_PATH}/format.cpp
   ${MOD_PATH}/clear.cpp
   ${MOD_PATH}/raster.cpp
   ${MOD_PATH}/buffer.cpp
)

set(pixelflinger_HEADERS
   ${INC_PATH}/format.h
   ${INC_PATH}/pixelflinger.h
)

add_library(pixelflinger SHARED ${pixelflinger_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(pixelflinger PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

install(TARGETS pixelflinger DESTINATION ${ANDROID_LIB_DIR})
install(FILES
        ${pixelflinger_HEADERS}
        DESTINATION include/pixelflinger)
