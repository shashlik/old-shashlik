project(hwcomposer-shashlik)

find_package(Qt5Core) # Yes, this is a hack. We need the 32bit libraries
find_package(Qt5Gui) # Yes, this is a hack. We need the 32bit libraries

set(hwcomposer_SRCS
    hwcmodule.cpp
    hwcomposer.cpp
)

add_library(hwcomposer.shashlik SHARED ${hwcomposer_SRCS})
target_compile_definitions(hwcomposer.shashlik
    PUBLIC
    -DLOG_TAG=\"shashlik\"
)
target_link_libraries(hwcomposer.shashlik
    log
    EGL
    utils
    hardware
    ${QT5CORE32_LIBRARIES}
    ${QT5GUI32_LIBRARIES}
)
target_include_directories(hwcomposer.shashlik
    PRIVATE
    ${OPENGL_INCLUDES}
    ${LIBUTILS_INCLUDES}
    ${LIBHARDWARE_INCLUDES}
    ${QT5CORE32_INCLUDE_DIRS}
    ${QT5GUI32_INCLUDE_DIRS}
)

# because otherwise the module loader looks for the wrong file
set_target_properties(hwcomposer.shashlik PROPERTIES PREFIX "")

if(FORCE_32BIT_BUILD)
    set_target_properties(hwcomposer.shashlik PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

install(TARGETS hwcomposer.shashlik DESTINATION ${ANDROID_LIB_DIR}/hw)
