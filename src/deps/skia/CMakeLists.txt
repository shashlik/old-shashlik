project(skia)

find_package(HarfBuzz REQUIRED)
find_package(Fontconfig REQUIRED)
find_package(Freetype REQUIRED)
find_package(JPEG REQUIRED)
find_package(GIF REQUIRED)
find_package(WebP REQUIRED)
find_package(PNG REQUIRED)

set(SKIA_SRC_PATH ${SKIA_PATH}/src)

#include_directories(${SKIA_PATH} ${SKIA_INCLUDES} ${SKIA_SRC_PATH} ${SKIA_SRC_PATH}/core ${SKIA_SRC_PATH}/image ${SKIA_SRC_PATH}/gpu ${SKIA_SRC_PATH}/opts ${SKIA_SRC_PATH}/sfnt ${SKIA_SRC_PATH}/utils)
include_directories(
    ${SKIA_PATH}/include/core
    ${SKIA_PATH}/include/config
    ${SKIA_PATH}/include/effects
    ${SKIA_PATH}/include/gpu
    ${SKIA_PATH}/include/images
    ${SKIA_PATH}/include/lazy
    ${SKIA_PATH}/include/pathops
    ${SKIA_PATH}/include/pdf
    ${SKIA_PATH}/include/pipe
    ${SKIA_PATH}/include/ports
    ${SKIA_PATH}/include/utils
    ${SKIA_PATH}/include/xml
    ${SKIA_SRC_PATH}/core
    ${SKIA_SRC_PATH}/gpu
    ${SKIA_SRC_PATH}/image
    ${SKIA_SRC_PATH}/images
    ${SKIA_SRC_PATH}/lazy
    ${SKIA_SRC_PATH}/opts
    ${SKIA_SRC_PATH}/pdf
    ${SKIA_SRC_PATH}/ports
    ${SKIA_SRC_PATH}/sfnt
    ${SKIA_SRC_PATH}/utils
    ${LIBLOG_INCLUDES}
    ${FONTCONFIG_INCLUDE_DIR}
    ${FREETYPE_INCLUDE_DIRS}
    ${GIF_INCLUDE_DIR}
    ${JPEG_INCLUDE_DIR}
    ${OPENGL_INCLUDES}
    )


add_definitions(
    # Android's -D_FORTIFY_SOURCE=2 extensions are incompatibile with SkString.
    # Revert to -D_FORTIFY_SOURCE=1
    -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=1
    # Skia does not enforce this usage pattern so we disable it here to avoid
    # unecessary log spew when building
    -Wno-unused-parameter
    # be less debuggy
    -DNDEBUG
    )

# This is not the best thing in the world. It does, however, ensure that we can compile
# certain bits of the code against system libraries, which lack android modifications,
# and still build...
set(skia_noworkey_SRCS
#     ${SKIA_SRC_PATH}/core/SkScalerContext.cpp
    ${SKIA_SRC_PATH}/images/SkImageDecoder_libjpeg.cpp
    ${SKIA_SRC_PATH}/images/SkImageDecoder_libpng.cpp
    ${SKIA_SRC_PATH}/images/SkJpegUtility.cpp
#     ${SKIA_SRC_PATH}/gpu/gl/unix/SkNativeGLContext_unix.cpp
    ${SKIA_SRC_PATH}/pdf/SkPDFDevice.cpp
)
set(skia_noworkey2_SRCS
    ${SKIA_SRC_PATH}/core/SkScalerContext.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/font_interface_workaround.cpp
)
add_library(skia_hack STATIC ${skia_noworkey_SRCS})
add_library(skia_hack2 STATIC ${skia_noworkey2_SRCS})
target_compile_definitions(skia_hack
    PUBLIC
    -DANDROID_LARGE_MEMORY_DEVICE
    -DDCT_IFAST_SUPPORTED
    # using freetype's embolden allows us to adjust fake bold settings at
    # draw-time, at which point we know which SkTypeface is being drawn
    -DSK_USE_FREETYPE_EMBOLDEN
#     -DSK_BUILD_FOR_ANDROID
#     -DSK_BUILD_FOR_ANDROID_FRAMEWORK
    #Android provides at least FreeType 2.4.0 at runtime.
    -DSK_FONTHOST_FREETYPE_RUNTIME_VERSION=0x020400
    #Skia should not use dlopen on Android.
    -DSK_CAN_USE_DLOPEN=0
    )
target_compile_definitions(skia_hack2
    PUBLIC
    -DANDROID_LARGE_MEMORY_DEVICE
    -DDCT_IFAST_SUPPORTED
    # using freetype's embolden allows us to adjust fake bold settings at
    # draw-time, at which point we know which SkTypeface is being drawn
    -DSK_USE_FREETYPE_EMBOLDEN
    -DSK_BUILD_FOR_ANDROID
#     -DSK_BUILD_FOR_ANDROID_FRAMEWORK
    #Android provides at least FreeType 2.4.0 at runtime.
    -DSK_FONTHOST_FREETYPE_RUNTIME_VERSION=0x020400
    #Skia should not use dlopen on Android.
    -DSK_CAN_USE_DLOPEN=0
    )
if(FORCE_32BIT_BUILD)
    set_target_properties(skia_hack PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    set_target_properties(skia_hack2 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)


# IMPORTANT: The build order of the SkImageDecoder_*.cpp files
# defines the order image decoders are tested when decoding a
# stream. The last decoder is the first one tested, so the .cpp
# files should be in listed in order from the least likely to be
# used, to the most likely (jpeg and png should be the last two
# for instance.)
set(skia_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/sk_thread_platform_workaround.cpp
    ${SKIA_SRC_PATH}/core/Sk64.cpp
    ${SKIA_SRC_PATH}/core/SkAnnotation.cpp
    ${SKIA_SRC_PATH}/core/SkAAClip.cpp
    ${SKIA_SRC_PATH}/core/SkAdvancedTypefaceMetrics.cpp
    ${SKIA_SRC_PATH}/core/SkAlphaRuns.cpp
    ${SKIA_SRC_PATH}/core/SkBBoxRecord.cpp
    ${SKIA_SRC_PATH}/core/SkBBoxHierarchyRecord.cpp
    ${SKIA_SRC_PATH}/core/SkBitmap.cpp
    ${SKIA_SRC_PATH}/core/SkBitmapDevice.cpp
    ${SKIA_SRC_PATH}/core/SkBitmapFilter.cpp
    ${SKIA_SRC_PATH}/core/SkBitmapHeap.cpp
    ${SKIA_SRC_PATH}/core/SkBitmapProcShader.cpp
    ${SKIA_SRC_PATH}/core/SkBitmapProcState.cpp
    ${SKIA_SRC_PATH}/core/SkBitmapProcState_matrixProcs.cpp
    ${SKIA_SRC_PATH}/core/SkBitmapScaler.cpp
    ${SKIA_SRC_PATH}/core/SkBitmap_scroll.cpp
    ${SKIA_SRC_PATH}/core/SkBlitMask_D32.cpp
    ${SKIA_SRC_PATH}/core/SkBlitRow_D16.cpp
    ${SKIA_SRC_PATH}/core/SkBlitRow_D32.cpp
    ${SKIA_SRC_PATH}/core/SkBlitter.cpp
    ${SKIA_SRC_PATH}/core/SkBlitter_A8.cpp
    ${SKIA_SRC_PATH}/core/SkBlitter_ARGB32.cpp
    ${SKIA_SRC_PATH}/core/SkBlitter_RGB16.cpp
    ${SKIA_SRC_PATH}/core/SkBlitter_Sprite.cpp
    ${SKIA_SRC_PATH}/core/SkBuffer.cpp
    ${SKIA_SRC_PATH}/core/SkCanvas.cpp
    ${SKIA_SRC_PATH}/core/SkChunkAlloc.cpp
    ${SKIA_SRC_PATH}/core/SkClipStack.cpp
    ${SKIA_SRC_PATH}/core/SkColor.cpp
    ${SKIA_SRC_PATH}/core/SkColorFilter.cpp
    ${SKIA_SRC_PATH}/core/SkColorTable.cpp
    ${SKIA_SRC_PATH}/core/SkComposeShader.cpp
    ${SKIA_SRC_PATH}/core/SkConfig8888.cpp
    ${SKIA_SRC_PATH}/core/SkConvolver.cpp
    ${SKIA_SRC_PATH}/core/SkCordic.cpp
    ${SKIA_SRC_PATH}/core/SkCubicClipper.cpp
    ${SKIA_SRC_PATH}/core/SkData.cpp
    ${SKIA_SRC_PATH}/core/SkDataTable.cpp
    ${SKIA_SRC_PATH}/core/SkDebug.cpp
    ${SKIA_SRC_PATH}/core/SkDeque.cpp
    ${SKIA_SRC_PATH}/core/SkDevice.cpp
    ${SKIA_SRC_PATH}/core/SkDeviceLooper.cpp
    ${SKIA_SRC_PATH}/core/SkDeviceProfile.cpp
    ${SKIA_SRC_PATH}/core/SkDither.cpp
    ${SKIA_SRC_PATH}/core/SkDraw.cpp
    ${SKIA_SRC_PATH}/core/SkDrawLooper.cpp
    ${SKIA_SRC_PATH}/core/SkEdgeBuilder.cpp
    ${SKIA_SRC_PATH}/core/SkEdgeClipper.cpp
    ${SKIA_SRC_PATH}/core/SkEdge.cpp
    ${SKIA_SRC_PATH}/core/SkError.cpp
    ${SKIA_SRC_PATH}/core/SkFilterProc.cpp
    ${SKIA_SRC_PATH}/core/SkFilterShader.cpp
    ${SKIA_SRC_PATH}/core/SkFlattenable.cpp
    ${SKIA_SRC_PATH}/core/SkFlattenableBuffers.cpp
    ${SKIA_SRC_PATH}/core/SkFlattenableSerialization.cpp
    ${SKIA_SRC_PATH}/core/SkFloat.cpp
    ${SKIA_SRC_PATH}/core/SkFloatBits.cpp
    ${SKIA_SRC_PATH}/core/SkFontDescriptor.cpp
    ${SKIA_SRC_PATH}/core/SkFontStream.cpp
    ${SKIA_SRC_PATH}/core/SkFontHost.cpp
    ${SKIA_SRC_PATH}/core/SkGeometry.cpp
    ${SKIA_SRC_PATH}/core/SkGlyphCache.cpp
    ${SKIA_SRC_PATH}/core/SkGraphics.cpp
    ${SKIA_SRC_PATH}/core/SkInstCnt.cpp
    ${SKIA_SRC_PATH}/core/SkImageFilter.cpp
    ${SKIA_SRC_PATH}/core/SkImageFilterUtils.cpp
    ${SKIA_SRC_PATH}/core/SkImageInfo.cpp
    ${SKIA_SRC_PATH}/core/SkLineClipper.cpp
    ${SKIA_SRC_PATH}/core/SkMallocPixelRef.cpp
    ${SKIA_SRC_PATH}/core/SkMask.cpp
    ${SKIA_SRC_PATH}/core/SkMaskFilter.cpp
    ${SKIA_SRC_PATH}/core/SkMaskGamma.cpp
    ${SKIA_SRC_PATH}/core/SkMath.cpp
    ${SKIA_SRC_PATH}/core/SkMatrix.cpp
    ${SKIA_SRC_PATH}/core/SkMetaData.cpp
    ${SKIA_SRC_PATH}/core/SkMipMap.cpp
    ${SKIA_SRC_PATH}/core/SkOrderedReadBuffer.cpp
    ${SKIA_SRC_PATH}/core/SkOrderedWriteBuffer.cpp
    ${SKIA_SRC_PATH}/core/SkPackBits.cpp
    ${SKIA_SRC_PATH}/core/SkPaint.cpp
    ${SKIA_SRC_PATH}/core/SkPaintOptionsAndroid.cpp
    ${SKIA_SRC_PATH}/core/SkPaintPriv.cpp
    ${SKIA_SRC_PATH}/core/SkPath.cpp
    ${SKIA_SRC_PATH}/core/SkPathEffect.cpp
    ${SKIA_SRC_PATH}/core/SkPathHeap.cpp
    ${SKIA_SRC_PATH}/core/SkPathMeasure.cpp
    ${SKIA_SRC_PATH}/core/SkPathRef.cpp
    ${SKIA_SRC_PATH}/core/SkPicture.cpp
    ${SKIA_SRC_PATH}/core/SkPictureFlat.cpp
    ${SKIA_SRC_PATH}/core/SkPicturePlayback.cpp
    ${SKIA_SRC_PATH}/core/SkPictureRecord.cpp
    ${SKIA_SRC_PATH}/core/SkPictureStateTree.cpp
    ${SKIA_SRC_PATH}/core/SkPixelRef.cpp
    ${SKIA_SRC_PATH}/core/SkPoint.cpp
    ${SKIA_SRC_PATH}/core/SkProcSpriteBlitter.cpp
    ${SKIA_SRC_PATH}/core/SkPtrRecorder.cpp
    ${SKIA_SRC_PATH}/core/SkQuadClipper.cpp
    ${SKIA_SRC_PATH}/core/SkRasterClip.cpp
    ${SKIA_SRC_PATH}/core/SkRasterizer.cpp
    ${SKIA_SRC_PATH}/core/SkRect.cpp
    ${SKIA_SRC_PATH}/core/SkRefDict.cpp
    ${SKIA_SRC_PATH}/core/SkRegion.cpp
    ${SKIA_SRC_PATH}/core/SkRegion_path.cpp
    ${SKIA_SRC_PATH}/core/SkRRect.cpp
    ${SKIA_SRC_PATH}/core/SkRTree.cpp
    ${SKIA_SRC_PATH}/core/SkScaledImageCache.cpp
    ${SKIA_SRC_PATH}/core/SkScalar.cpp
#     ${SKIA_SRC_PATH}/core/SkScalerContext.cpp
    ${SKIA_SRC_PATH}/core/SkScan.cpp
    ${SKIA_SRC_PATH}/core/SkScan_AntiPath.cpp
    ${SKIA_SRC_PATH}/core/SkScan_Antihair.cpp
    ${SKIA_SRC_PATH}/core/SkScan_Hairline.cpp
    ${SKIA_SRC_PATH}/core/SkScan_Path.cpp
    ${SKIA_SRC_PATH}/core/SkShader.cpp
    ${SKIA_SRC_PATH}/core/SkSpriteBlitter_ARGB32.cpp
    ${SKIA_SRC_PATH}/core/SkSpriteBlitter_RGB16.cpp
    ${SKIA_SRC_PATH}/core/SkStream.cpp
    ${SKIA_SRC_PATH}/core/SkString.cpp
    ${SKIA_SRC_PATH}/core/SkStringUtils.cpp
    ${SKIA_SRC_PATH}/core/SkStroke.cpp
    ${SKIA_SRC_PATH}/core/SkStrokeRec.cpp
    ${SKIA_SRC_PATH}/core/SkStrokerPriv.cpp
    ${SKIA_SRC_PATH}/core/SkTileGrid.cpp
    ${SKIA_SRC_PATH}/core/SkTileGridPicture.cpp
    ${SKIA_SRC_PATH}/core/SkTLS.cpp
    ${SKIA_SRC_PATH}/core/SkTSearch.cpp
    ${SKIA_SRC_PATH}/core/SkTypeface.cpp
    ${SKIA_SRC_PATH}/core/SkTypefaceCache.cpp
    ${SKIA_SRC_PATH}/core/SkUnPreMultiply.cpp
    ${SKIA_SRC_PATH}/core/SkUtils.cpp
    ${SKIA_SRC_PATH}/core/SkValidatingReadBuffer.cpp
    ${SKIA_SRC_PATH}/core/SkFlate.cpp
    ${SKIA_SRC_PATH}/core/SkWriter32.cpp
    ${SKIA_SRC_PATH}/core/SkXfermode.cpp
    ${SKIA_SRC_PATH}/doc/SkDocument.cpp
    ${SKIA_SRC_PATH}/doc/SkDocument_PDF.cpp
    ${SKIA_SRC_PATH}/effects/Sk1DPathEffect.cpp
    ${SKIA_SRC_PATH}/effects/Sk2DPathEffect.cpp
    ${SKIA_SRC_PATH}/effects/SkArithmeticMode.cpp
    ${SKIA_SRC_PATH}/effects/SkAvoidXfermode.cpp
    ${SKIA_SRC_PATH}/effects/SkBicubicImageFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkBitmapAlphaThresholdShader.cpp
    ${SKIA_SRC_PATH}/effects/SkBitmapSource.cpp
    ${SKIA_SRC_PATH}/effects/SkBlurDrawLooper.cpp
    ${SKIA_SRC_PATH}/effects/SkBlurImageFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkBlurMask.cpp
    ${SKIA_SRC_PATH}/effects/SkBlurMaskFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkColorFilterImageFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkColorFilters.cpp
    ${SKIA_SRC_PATH}/effects/SkColorMatrix.cpp
    ${SKIA_SRC_PATH}/effects/SkColorMatrixFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkComposeImageFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkCornerPathEffect.cpp
    ${SKIA_SRC_PATH}/effects/SkDashPathEffect.cpp
    ${SKIA_SRC_PATH}/effects/SkDiscretePathEffect.cpp
    ${SKIA_SRC_PATH}/effects/SkDisplacementMapEffect.cpp
    ${SKIA_SRC_PATH}/effects/SkDropShadowImageFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkEmbossMask.cpp
    ${SKIA_SRC_PATH}/effects/SkEmbossMaskFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkGpuBlurUtils.cpp
    ${SKIA_SRC_PATH}/effects/SkKernel33MaskFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkLayerDrawLooper.cpp
    ${SKIA_SRC_PATH}/effects/SkLayerRasterizer.cpp
    ${SKIA_SRC_PATH}/effects/SkLerpXfermode.cpp
    ${SKIA_SRC_PATH}/effects/SkLightingImageFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkLumaColorFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkMagnifierImageFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkMatrixConvolutionImageFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkMergeImageFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkMorphologyImageFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkOffsetImageFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkPaintFlagsDrawFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkPerlinNoiseShader.cpp
    ${SKIA_SRC_PATH}/effects/SkPictureImageFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkPixelXorXfermode.cpp
    ${SKIA_SRC_PATH}/effects/SkPorterDuff.cpp
    ${SKIA_SRC_PATH}/effects/SkRectShaderImageFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkStippleMaskFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkTableColorFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkTableMaskFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkTestImageFilters.cpp
    ${SKIA_SRC_PATH}/effects/SkTileImageFilter.cpp
    ${SKIA_SRC_PATH}/effects/SkTransparentShader.cpp
    ${SKIA_SRC_PATH}/effects/SkXfermodeImageFilter.cpp
    ${SKIA_SRC_PATH}/effects/gradients/SkBitmapCache.cpp
    ${SKIA_SRC_PATH}/effects/gradients/SkClampRange.cpp
    ${SKIA_SRC_PATH}/effects/gradients/SkGradientShader.cpp
    ${SKIA_SRC_PATH}/effects/gradients/SkLinearGradient.cpp
    ${SKIA_SRC_PATH}/effects/gradients/SkRadialGradient.cpp
    ${SKIA_SRC_PATH}/effects/gradients/SkTwoPointRadialGradient.cpp
    ${SKIA_SRC_PATH}/effects/gradients/SkTwoPointConicalGradient.cpp
    ${SKIA_SRC_PATH}/effects/gradients/SkSweepGradient.cpp
    ${SKIA_SRC_PATH}/image/SkDataPixelRef.cpp
    ${SKIA_SRC_PATH}/image/SkImage.cpp
    ${SKIA_SRC_PATH}/image/SkImagePriv.cpp
    ${SKIA_SRC_PATH}/image/SkImage_Codec.cpp
    ${SKIA_SRC_PATH}/image/SkImage_Gpu.cpp
    ${SKIA_SRC_PATH}/image/SkImage_Picture.cpp
    ${SKIA_SRC_PATH}/image/SkImage_Raster.cpp
    ${SKIA_SRC_PATH}/image/SkSurface.cpp
    ${SKIA_SRC_PATH}/image/SkSurface_Gpu.cpp
    ${SKIA_SRC_PATH}/image/SkSurface_Picture.cpp
    ${SKIA_SRC_PATH}/image/SkSurface_Raster.cpp
    ${SKIA_SRC_PATH}/images/bmpdecoderhelper.cpp
    ${SKIA_SRC_PATH}/images/SkDecodingImageGenerator.cpp
    ${SKIA_SRC_PATH}/images/SkImageDecoder_FactoryDefault.cpp
    ${SKIA_SRC_PATH}/images/SkImageDecoder_FactoryRegistrar.cpp
    ${SKIA_SRC_PATH}/images/SkImages.cpp
    ${SKIA_SRC_PATH}/images/SkForceLinking.cpp
    ${SKIA_SRC_PATH}/images/SkImageDecoder.cpp
    ${SKIA_SRC_PATH}/images/SkImageDecoder_libbmp.cpp
    ${SKIA_SRC_PATH}/images/SkImageDecoder_wbmp.cpp
    ${SKIA_SRC_PATH}/images/SkImageDecoder_libico.cpp
    ${SKIA_SRC_PATH}/images/SkImageDecoder_libwebp.cpp
    ${SKIA_SRC_PATH}/images/SkImageDecoder_libgif.cpp
#     ${SKIA_SRC_PATH}/images/SkImageDecoder_libjpeg.cpp
#     ${SKIA_SRC_PATH}/images/SkImageDecoder_libpng.cpp
    ${SKIA_SRC_PATH}/images/SkImageEncoder.cpp
    ${SKIA_SRC_PATH}/images/SkImageEncoder_Factory.cpp
    ${SKIA_SRC_PATH}/images/SkImageEncoder_argb.cpp
    ${SKIA_SRC_PATH}/images/SkImageRef.cpp
    ${SKIA_SRC_PATH}/images/SkImageRefPool.cpp
    ${SKIA_SRC_PATH}/images/SkImageRef_ashmem.cpp
    ${SKIA_SRC_PATH}/images/SkImageRef_GlobalPool.cpp
#     ${SKIA_SRC_PATH}/images/SkJpegUtility.cpp
    ${SKIA_SRC_PATH}/images/SkMovie.cpp
    ${SKIA_SRC_PATH}/images/SkMovie_gif.cpp
    ${SKIA_SRC_PATH}/images/SkPageFlipper.cpp
    ${SKIA_SRC_PATH}/images/SkScaledBitmapSampler.cpp
    ${SKIA_SRC_PATH}/images/SkStreamHelpers.cpp
    ${SKIA_SRC_PATH}/pathops/SkAddIntersections.cpp
    ${SKIA_SRC_PATH}/pathops/SkDCubicIntersection.cpp
    ${SKIA_SRC_PATH}/pathops/SkDCubicLineIntersection.cpp
    ${SKIA_SRC_PATH}/pathops/SkDCubicToQuads.cpp
    ${SKIA_SRC_PATH}/pathops/SkDLineIntersection.cpp
    ${SKIA_SRC_PATH}/pathops/SkDQuadImplicit.cpp
    ${SKIA_SRC_PATH}/pathops/SkDQuadIntersection.cpp
    ${SKIA_SRC_PATH}/pathops/SkDQuadLineIntersection.cpp
    ${SKIA_SRC_PATH}/pathops/SkIntersections.cpp
    ${SKIA_SRC_PATH}/pathops/SkOpAngle.cpp
    ${SKIA_SRC_PATH}/pathops/SkOpContour.cpp
    ${SKIA_SRC_PATH}/pathops/SkOpEdgeBuilder.cpp
    ${SKIA_SRC_PATH}/pathops/SkOpSegment.cpp
    ${SKIA_SRC_PATH}/pathops/SkPathOpsBounds.cpp
    ${SKIA_SRC_PATH}/pathops/SkPathOpsCommon.cpp
    ${SKIA_SRC_PATH}/pathops/SkPathOpsCubic.cpp
    ${SKIA_SRC_PATH}/pathops/SkPathOpsDebug.cpp
    ${SKIA_SRC_PATH}/pathops/SkPathOpsLine.cpp
    ${SKIA_SRC_PATH}/pathops/SkPathOpsOp.cpp
    ${SKIA_SRC_PATH}/pathops/SkPathOpsPoint.cpp
    ${SKIA_SRC_PATH}/pathops/SkPathOpsQuad.cpp
    ${SKIA_SRC_PATH}/pathops/SkPathOpsRect.cpp
    ${SKIA_SRC_PATH}/pathops/SkPathOpsSimplify.cpp
    ${SKIA_SRC_PATH}/pathops/SkPathOpsTriangle.cpp
    ${SKIA_SRC_PATH}/pathops/SkPathOpsTypes.cpp
    ${SKIA_SRC_PATH}/pathops/SkPathWriter.cpp
    ${SKIA_SRC_PATH}/pathops/SkQuarticRoot.cpp
    ${SKIA_SRC_PATH}/pathops/SkReduceOrder.cpp
    ${SKIA_SRC_PATH}/pipe/SkGPipeRead.cpp
    ${SKIA_SRC_PATH}/pipe/SkGPipeWrite.cpp
    ${SKIA_SRC_PATH}/ports/SkDebug_android.cpp
#     ${SKIA_SRC_PATH}/ports/SkDiscardableMemory_ashmem.cpp
    ${SKIA_SRC_PATH}/ports/SkDiscardableMemory_none.cpp
    ${SKIA_SRC_PATH}/ports/SkGlobalInitialization_default.cpp
#     ${SKIA_SRC_PATH}/ports/SkFontConfigInterface_android.cpp
#     ${SKIA_SRC_PATH}/ports/SkFontConfigParser_android.cpp
    ${SKIA_SRC_PATH}/ports/SkFontHost_FreeType.cpp
    ${SKIA_SRC_PATH}/ports/SkFontHost_FreeType_common.cpp
    ${SKIA_SRC_PATH}/ports/SkFontHost_fontconfig.cpp
    ${SKIA_SRC_PATH}/ports/SkMemory_malloc.cpp
    ${SKIA_SRC_PATH}/ports/SkOSFile_posix.cpp
    ${SKIA_SRC_PATH}/ports/SkOSFile_stdio.cpp
#     ${SKIA_SRC_PATH}/ports/SkPurgeableMemoryBlock_android.cpp
    ${SKIA_SRC_PATH}/ports/SkPurgeableMemoryBlock_none.cpp
    ${SKIA_SRC_PATH}/ports/SkThread_pthread.cpp
    ${SKIA_SRC_PATH}/ports/SkTime_Unix.cpp
    ${SKIA_SRC_PATH}/ports/SkTLS_pthread.cpp
    ${SKIA_SRC_PATH}/pdf/SkPDFCatalog.cpp
#     ${SKIA_SRC_PATH}/pdf/SkPDFDevice.cpp
    ${SKIA_SRC_PATH}/pdf/SkPDFDeviceFlattener.cpp
    ${SKIA_SRC_PATH}/pdf/SkPDFDocument.cpp
    ${SKIA_SRC_PATH}/pdf/SkPDFFont.cpp
    ${SKIA_SRC_PATH}/pdf/SkPDFFormXObject.cpp
    ${SKIA_SRC_PATH}/pdf/SkPDFGraphicState.cpp
    ${SKIA_SRC_PATH}/pdf/SkPDFImage.cpp
    ${SKIA_SRC_PATH}/pdf/SkPDFPage.cpp
    ${SKIA_SRC_PATH}/pdf/SkPDFResourceDict.cpp
    ${SKIA_SRC_PATH}/pdf/SkPDFShader.cpp
    ${SKIA_SRC_PATH}/pdf/SkPDFStream.cpp
    ${SKIA_SRC_PATH}/pdf/SkPDFTypes.cpp
    ${SKIA_SRC_PATH}/pdf/SkPDFUtils.cpp
    ${SKIA_SRC_PATH}/sfnt/SkOTTable_name.cpp
    ${SKIA_SRC_PATH}/sfnt/SkOTUtils.cpp
#     ${SKIA_SRC_PATH}/utils/android/ashmem.cpp
    ${SKIA_SRC_PATH}/utils/debugger/SkDebugCanvas.cpp
    ${SKIA_SRC_PATH}/utils/debugger/SkDrawCommand.cpp
    ${SKIA_SRC_PATH}/utils/debugger/SkObjectParser.cpp
    ${SKIA_SRC_PATH}/utils/SkBase64.cpp
    ${SKIA_SRC_PATH}/utils/SkBitSet.cpp
    ${SKIA_SRC_PATH}/utils/SkBoundaryPatch.cpp
    ${SKIA_SRC_PATH}/utils/SkCamera.cpp
    ${SKIA_SRC_PATH}/utils/SkCanvasStack.cpp
    ${SKIA_SRC_PATH}/utils/SkCanvasStateUtils.cpp
    ${SKIA_SRC_PATH}/utils/SkCubicInterval.cpp
    ${SKIA_SRC_PATH}/utils/SkCullPoints.cpp
    ${SKIA_SRC_PATH}/utils/SkDeferredCanvas.cpp
    ${SKIA_SRC_PATH}/utils/SkDumpCanvas.cpp
    ${SKIA_SRC_PATH}/utils/SkFrontBufferedStream.cpp
    ${SKIA_SRC_PATH}/utils/SkInterpolator.cpp
    ${SKIA_SRC_PATH}/utils/SkLayer.cpp
    ${SKIA_SRC_PATH}/utils/SkMatrix44.cpp
    ${SKIA_SRC_PATH}/utils/SkMD5.cpp
    ${SKIA_SRC_PATH}/utils/SkMeshUtils.cpp
    ${SKIA_SRC_PATH}/utils/SkNinePatch.cpp
    ${SKIA_SRC_PATH}/utils/SkNWayCanvas.cpp
    ${SKIA_SRC_PATH}/utils/SkNullCanvas.cpp
    ${SKIA_SRC_PATH}/utils/SkOSFile.cpp
    ${SKIA_SRC_PATH}/utils/SkParse.cpp
    ${SKIA_SRC_PATH}/utils/SkParseColor.cpp
    ${SKIA_SRC_PATH}/utils/SkParsePath.cpp
    ${SKIA_SRC_PATH}/utils/SkPictureUtils.cpp
    ${SKIA_SRC_PATH}/utils/SkPathUtils.cpp
    ${SKIA_SRC_PATH}/utils/SkProxyCanvas.cpp
    ${SKIA_SRC_PATH}/utils/SkSHA1.cpp
    ${SKIA_SRC_PATH}/utils/SkRTConf.cpp
    ${SKIA_SRC_PATH}/utils/SkThreadUtils_pthread.cpp
    ${SKIA_SRC_PATH}/utils/SkThreadUtils_pthread_other.cpp
    ${SKIA_SRC_PATH}/utils/SkUnitMappers.cpp
    ${SKIA_SRC_PATH}/lazy/SkDiscardableMemoryPool.cpp
    ${SKIA_SRC_PATH}/lazy/SkDiscardablePixelRef.cpp
    ${SKIA_SRC_PATH}/lazy/SkCachingPixelRef.cpp 

    ${SKIA_SRC_PATH}/fonts/SkFontMgr_fontconfig.cpp
    ${SKIA_SRC_PATH}/ports/SkFontConfigInterface_direct.cpp

    ${SKIA_SRC_PATH}/opts/SkUtils_opts_none.cpp
    ${SKIA_SRC_PATH}/opts/SkBitmapProcState_opts_none.cpp
    ${SKIA_SRC_PATH}/opts/SkBlitRow_opts_none.cpp
    ${SKIA_SRC_PATH}/opts/SkBlitMask_opts_none.cpp
    ${SKIA_SRC_PATH}/opts/SkBlurImage_opts_none.cpp
    ${SKIA_SRC_PATH}/opts/SkMorphology_opts_none.cpp
    ${SKIA_SRC_PATH}/opts/SkXfermode_opts_none.cpp
)

# maps to the 'skgr' gyp target
set(skia_skgr_SRCS
    ${SKIA_SRC_PATH}/gpu/SkGpuDevice.cpp
    ${SKIA_SRC_PATH}/gpu/SkGr.cpp
    ${SKIA_SRC_PATH}/gpu/SkGrFontScaler.cpp
    ${SKIA_SRC_PATH}/gpu/SkGrPixelRef.cpp
    ${SKIA_SRC_PATH}/gpu/SkGrTexturePixelRef.cpp
    ${SKIA_SRC_PATH}/gpu/gl/SkGLContextHelper.cpp
    ${SKIA_SRC_PATH}/gpu/gl/android/SkNativeGLContext_android.cpp
    )

# null and debug gpu interfaces
set(skia_nulldbg_gpu_SRCS
    ${SKIA_SRC_PATH}/gpu/gl/SkNullGLContext.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLCreateNullInterface.cpp
    ${SKIA_SRC_PATH}/gpu/gl/debug/SkDebugGLContext.cpp
    ${SKIA_SRC_PATH}/gpu/gl/debug/GrGLCreateDebugInterface.cpp
    ${SKIA_SRC_PATH}/gpu/gl/debug/GrBufferObj.cpp
    ${SKIA_SRC_PATH}/gpu/gl/debug/GrTextureObj.cpp
    ${SKIA_SRC_PATH}/gpu/gl/debug/GrTextureUnitObj.cpp
    ${SKIA_SRC_PATH}/gpu/gl/debug/GrFrameBufferObj.cpp
    ${SKIA_SRC_PATH}/gpu/gl/debug/GrShaderObj.cpp
    ${SKIA_SRC_PATH}/gpu/gl/debug/GrProgramObj.cpp
    ${SKIA_SRC_PATH}/gpu/gl/debug/GrDebugGL.cpp
    )

# maps to the 'gr' gyp target
set(skia_gr_SRCS
    ${SKIA_SRC_PATH}/gpu/GrAAHairLinePathRenderer.cpp
    ${SKIA_SRC_PATH}/gpu/GrAAConvexPathRenderer.cpp
    ${SKIA_SRC_PATH}/gpu/GrAARectRenderer.cpp
    ${SKIA_SRC_PATH}/gpu/GrAddPathRenderers_default.cpp
    ${SKIA_SRC_PATH}/gpu/GrAllocPool.cpp
    ${SKIA_SRC_PATH}/gpu/GrAtlas.cpp
    ${SKIA_SRC_PATH}/gpu/GrBitmapTextContext.cpp
    ${SKIA_SRC_PATH}/gpu/GrBufferAllocPool.cpp
    ${SKIA_SRC_PATH}/gpu/GrBlend.cpp
    ${SKIA_SRC_PATH}/gpu/GrCacheID.cpp
    ${SKIA_SRC_PATH}/gpu/GrClipData.cpp
    ${SKIA_SRC_PATH}/gpu/GrContext.cpp
    ${SKIA_SRC_PATH}/gpu/GrDefaultPathRenderer.cpp
    ${SKIA_SRC_PATH}/gpu/GrDrawState.cpp
    ${SKIA_SRC_PATH}/gpu/GrDrawTarget.cpp
    ${SKIA_SRC_PATH}/gpu/GrEffect.cpp
    ${SKIA_SRC_PATH}/gpu/GrClipMaskCache.cpp
    ${SKIA_SRC_PATH}/gpu/GrClipMaskManager.cpp
    ${SKIA_SRC_PATH}/gpu/GrGpu.cpp
    ${SKIA_SRC_PATH}/gpu/GrGpuFactory.cpp
    ${SKIA_SRC_PATH}/gpu/GrInOrderDrawBuffer.cpp
    ${SKIA_SRC_PATH}/gpu/GrMemoryPool.cpp
    ${SKIA_SRC_PATH}/gpu/GrOvalRenderer.cpp
    ${SKIA_SRC_PATH}/gpu/GrPaint.cpp
    ${SKIA_SRC_PATH}/gpu/GrPath.cpp
    ${SKIA_SRC_PATH}/gpu/GrPathRendererChain.cpp
    ${SKIA_SRC_PATH}/gpu/GrPathRenderer.cpp
    ${SKIA_SRC_PATH}/gpu/GrPathUtils.cpp
    ${SKIA_SRC_PATH}/gpu/GrRectanizer.cpp
    ${SKIA_SRC_PATH}/gpu/GrRectanizer_skyline.cpp
    ${SKIA_SRC_PATH}/gpu/GrReducedClip.cpp
    ${SKIA_SRC_PATH}/gpu/GrRenderTarget.cpp
    ${SKIA_SRC_PATH}/gpu/GrResource.cpp
    ${SKIA_SRC_PATH}/gpu/GrResourceCache.cpp
    ${SKIA_SRC_PATH}/gpu/GrStencil.cpp
    ${SKIA_SRC_PATH}/gpu/GrStencilAndCoverPathRenderer.cpp
    ${SKIA_SRC_PATH}/gpu/GrStencilBuffer.cpp
    ${SKIA_SRC_PATH}/gpu/GrSWMaskHelper.cpp
    ${SKIA_SRC_PATH}/gpu/GrSoftwarePathRenderer.cpp
    ${SKIA_SRC_PATH}/gpu/GrSurface.cpp
    ${SKIA_SRC_PATH}/gpu/GrTextContext.cpp
    ${SKIA_SRC_PATH}/gpu/GrTextStrike.cpp
    ${SKIA_SRC_PATH}/gpu/GrTexture.cpp
    ${SKIA_SRC_PATH}/gpu/GrTextureAccess.cpp
    ${SKIA_SRC_PATH}/gpu/effects/GrConfigConversionEffect.cpp
    ${SKIA_SRC_PATH}/gpu/effects/GrBezierEffect.cpp
    ${SKIA_SRC_PATH}/gpu/effects/GrConvolutionEffect.cpp
    ${SKIA_SRC_PATH}/gpu/effects/GrBicubicEffect.cpp
    ${SKIA_SRC_PATH}/gpu/effects/GrCustomCoordsTextureEffect.cpp
    ${SKIA_SRC_PATH}/gpu/effects/GrSimpleTextureEffect.cpp
    ${SKIA_SRC_PATH}/gpu/effects/GrSingleTextureEffect.cpp
    ${SKIA_SRC_PATH}/gpu/effects/GrTextureDomain.cpp
    ${SKIA_SRC_PATH}/gpu/effects/GrTextureStripAtlas.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLBufferImpl.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLCaps.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLContext.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLDefaultInterface_native.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLExtensions.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLIndexBuffer.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLInterface.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLNoOpInterface.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLPath.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLProgram.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLProgramDesc.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLProgramEffects.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLRenderTarget.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLShaderBuilder.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLSL.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLStencilBuffer.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLTexture.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLUtil.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLUniformManager.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLVertexArray.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGLVertexBuffer.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGpuGL.cpp
    ${SKIA_SRC_PATH}/gpu/gl/GrGpuGL_program.cpp
#     ${SKIA_SRC_PATH}/gpu/gl/mesa/GrGLCreateMesaInterface.cpp
#     ${SKIA_SRC_PATH}/gpu/gl/mesa/SkMesaGLContext.cpp
#     ${SKIA_SRC_PATH}/gpu/gl/GrGLDefaultInterface_none.cpp
#     ${SKIA_SRC_PATH}/gpu/gl/GrGLCreateNativeInterface_none.cpp
    ${SKIA_SRC_PATH}/gpu/gl/android/GrGLCreateNativeInterface_android.cpp
#     ${SKIA_SRC_PATH}/gpu/gl/unix/GrGLCreateNativeInterface_unix.cpp
#     ${SKIA_SRC_PATH}/gpu/gl/unix/SkNativeGLContext_unix.cpp
    )

add_library(skia SHARED ${skia_SRCS} ${skia_skgr_SRCS} ${skia_nulldbg_gpu_SRCS} ${skia_gr_SRCS} gif-hacks.cpp)
target_compile_definitions(skia
    PUBLIC
    -DANDROID_LARGE_MEMORY_DEVICE
    -DDCT_IFAST_SUPPORTED
    # using freetype's embolden allows us to adjust fake bold settings at
    # draw-time, at which point we know which SkTypeface is being drawn
    -DSK_USE_FREETYPE_EMBOLDEN
    -DSK_BUILD_FOR_ANDROID
    -DSK_BUILD_FOR_ANDROID_FRAMEWORK
    #Android provides at least FreeType 2.4.0 at runtime.
    -DSK_FONTHOST_FREETYPE_RUNTIME_VERSION=0x020400
    #Skia should not use dlopen on Android.
    -DSK_CAN_USE_DLOPEN=0
    )
if(FORCE_32BIT_BUILD)
    set_target_properties(skia PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(skia
    skia_hack
    skia_hack2

    z
    ${HARFBUZZ_LIBRARIES}
    ${HARFBUZZ_ICU_LIBRARIES}
    ${FONTCONFIG_LIBRARIES}
    ${FREETYPE_LIBRARIES}
    ${JPEG_LIBRARIES}
    ${GIF_LIBRARIES}
    ${WEBP_LIBRARIES}
    ${OPENGL_LIBS}
    OSMesa
    epoxy
    ${PNG_LIBRARIES}
    )
install(TARGETS skia DESTINATION ${ANDROID_LIB_DIR})
