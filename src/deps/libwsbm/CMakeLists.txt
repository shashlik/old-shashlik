project(libwsbm)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/intel-libwsbm/src)

set(wsbm_SRCS
    ${REPO_PATH}/wsbm_driver.c
    ${REPO_PATH}/wsbm_fencemgr.c
    ${REPO_PATH}/wsbm_mallocpool.c
    ${REPO_PATH}/wsbm_manager.c
    ${REPO_PATH}/wsbm_mm.c
    ${REPO_PATH}/wsbm_slabpool.c
    ${REPO_PATH}/wsbm_ttmpool.c
    ${REPO_PATH}/wsbm_userpool.c
)

add_library(wsbm SHARED ${wsbm_SRCS})
target_compile_definitions(wsbm PRIVATE -DHAVE_CONFIG_H -DANDROID)
target_link_libraries(wsbm ${DRM_LIBRARIES} stripped_bionic)
target_include_directories(wsbm
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/drm
    ${DRM_INCLUDE_DIRS}
)

if(FORCE_32BIT_BUILD)
    set_target_properties(wsbm PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

install(TARGETS wsbm DESTINATION ${ANDROID_LIB_DIR})
