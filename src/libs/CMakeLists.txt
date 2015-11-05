add_subdirectory(libapk)
# add_subdirectory(libshashlikutils)
# add_subdirectory(hwcomposer-shashlik)
add_subdirectory(gralloc-shashlik)

# generate shashlikversion.h
configure_file(shashlikversion.h.cmake ${CMAKE_BINARY_DIR}/shashlikversion.h)
