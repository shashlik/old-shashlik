project(gralloc-shashlik)

set(gralloc_shashlik_SRCS
    bufferhandler.c
    framebuffer.cpp
    gralloc.cpp
    mapper.cpp
)

add_library(gralloc.shashlik SHARED ${gralloc_shashlik_SRCS})
target_compile_definitions(gralloc.shashlik
    PUBLIC
    -DLOG_TAG=\"shashlik\"
)
target_link_libraries(gralloc.shashlik
    log
    cutils
    waylandthings
    ${QT5CORE32_LIBRARIES}
    ${QT5GUI32_LIBRARIES}
)
target_include_directories(gralloc.shashlik
    PRIVATE
    ${OPENGL_INCLUDES}
    ${LIBUTILS_INCLUDES}
    ${LIBHARDWARE_INCLUDES}
    ${QT5CORE32_INCLUDE_DIRS}
    ${QT5GUI32_INCLUDE_DIRS}
)

# because otherwise the module loader looks for the wrong file
set_target_properties(gralloc.shashlik PROPERTIES PREFIX "")

if(FORCE_32BIT_BUILD)
    set_target_properties(gralloc.shashlik PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

# install(TARGETS gralloc.shashlik DESTINATION ${ANDROID_LIB_DIR}/hw)
