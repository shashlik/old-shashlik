project(pixelflinger)

add_definitions(-D_GNU_SOURCE -DCORKSCREW_HAVE_ARCH -DHAVE_SYS_UIO_H -std=c99)
set(REPO_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../../android-core)
set(MOD_PATH ${REPO_PATH}/libpixelflinger)
set(INC_PATH ${REPO_PATH}/include/pixelflinger)

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

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${REPO_PATH}/include)
add_library(pixelflinger SHARED ${pixelflinger_SRCS})
install(TARGETS pixelflinger DESTINATION lib)
install(FILES
        ${pixelflinger_HEADERS}
        DESTINATION include/pixelflinger)
