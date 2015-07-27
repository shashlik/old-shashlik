project(libhwui)

set(REPO_PATH ${ANDROID_FRAMEWORKS_BASE}/libs/hwui)

set(hwui_SRCS
    ${REPO_PATH}/utils/Blur.cpp
    ${REPO_PATH}/utils/SortedListImpl.cpp
    ${REPO_PATH}/thread/TaskManager.cpp
    ${REPO_PATH}/font/CacheTexture.cpp
    ${REPO_PATH}/font/Font.cpp
    ${REPO_PATH}/AssetAtlas.cpp
    ${REPO_PATH}/FontRenderer.cpp
    ${REPO_PATH}/GammaFontRenderer.cpp
    ${REPO_PATH}/Caches.cpp
    ${REPO_PATH}/DisplayList.cpp
    ${REPO_PATH}/DeferredDisplayList.cpp
    ${REPO_PATH}/DisplayListLogBuffer.cpp
    ${REPO_PATH}/DisplayListRenderer.cpp
    ${REPO_PATH}/Dither.cpp
    ${REPO_PATH}/Extensions.cpp
    ${REPO_PATH}/FboCache.cpp
    ${REPO_PATH}/GradientCache.cpp
    ${REPO_PATH}/Image.cpp
    ${REPO_PATH}/Layer.cpp
    ${REPO_PATH}/LayerCache.cpp
    ${REPO_PATH}/LayerRenderer.cpp
    ${REPO_PATH}/Matrix.cpp
    ${REPO_PATH}/OpenGLRenderer.cpp
    ${REPO_PATH}/Patch.cpp
    ${REPO_PATH}/PatchCache.cpp
    ${REPO_PATH}/PathCache.cpp
    ${REPO_PATH}/PathTessellator.cpp
    ${REPO_PATH}/PixelBuffer.cpp
    ${REPO_PATH}/Program.cpp
    ${REPO_PATH}/ProgramCache.cpp
    ${REPO_PATH}/RenderBufferCache.cpp
    ${REPO_PATH}/ResourceCache.cpp
    ${REPO_PATH}/SkiaColorFilter.cpp
    ${REPO_PATH}/SkiaShader.cpp
    ${REPO_PATH}/Snapshot.cpp
    ${REPO_PATH}/Stencil.cpp
    ${REPO_PATH}/Texture.cpp
    ${REPO_PATH}/TextureCache.cpp
    ${REPO_PATH}/TextDropShadowCache.cpp
)

add_definitions(-fpermissive)
add_library(hwui SHARED ${hwui_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(hwui PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_compile_definitions(hwui
    PRIVATE
    -DSK_BUILD_FOR_ANDROID # lololo skia internals
    -DNDEBUG
    PUBLIC
    -DUSE_OPENGL_RENDERER -DEGL_EGLEXT_PROTOTYPES -DGL_GLEXT_PROTOTYPES
)
target_include_directories(hwui
    PUBLIC
    ${ANDROID_FRAMEWORKS_BASE}/include/private
    PRIVATE
    ${LIBLOG_INCLUDES}
    ${SKIA_INCLUDES}
    ${SKIA_PATH}/src/core
    ${REPO_PATH}
    ${LIBHARDWARE_INCLUDES}
)
target_link_libraries(hwui
    log
    cutils
    utils
    EGL
    GL
    GLESv2
    epoxy
    skia
    ui
    androidfw
)
install(TARGETS hwui DESTINATION ${ANDROID_LIB_DIR})
