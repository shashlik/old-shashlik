
project(libjni)

#find_package(KF5Archive NO_MODULE)

add_definitions(-DHAVE_ANDROID_OS   # To make cutils/trace work.  FIXME: Check what other consequences this has.
                -fpermissive  # FIXME: for pointer to int conversion in printf on x86_64
)


#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${CMAKE_CURRENT_SOURCE_DIR}/..   # For runtime/ . Reorganize this better once it works
                    ${LIBCUTILS_INCLUDES}
                    ${LIBNATIVEHELPER_INCLUDEDIRS}
                    ${CMAKE_INSTALL_PREFIX}/include
                    ${LIBBINDER_INCLUDES}
                    #${CMAKE_BINARY_DIR}     # for shashlikversion.h
                    #${ANDROID_FRAMEWORKS_BASE}/include
                    )


set(libjni_SRCS
    #android_animation_PropertyValuesHolder.cpp
    #android_app_backup_FullBackup.cpp
    #android_app_NativeActivity.cpp
    #android_backup_BackupDataInput.cpp
    #android_backup_BackupDataOutput.cpp
    #android_backup_BackupHelperDispatcher.cpp
    #android_backup_FileBackupHelperBase.cpp
    #android_content_res_Configuration.cpp
    #android_content_res_ObbScanner.cpp
    #android_database_CursorWindow.cpp
    #android_database_SQLiteCommon.cpp
    #android_database_SQLiteConnection.cpp
    #android_database_SQLiteDebug.cpp
    #android_database_SQLiteGlobal.cpp
    #android_ddm_DdmHandleNativeHeap.cpp
    #android_debug_JNITest.cpp
    #android_emoji_EmojiFactory.cpp
    #android_hardware_camera2_CameraMetadata.cpp
    #android_hardware_Camera.cpp
    #android_hardware_SensorManager.cpp
    #android_hardware_SerialPort.cpp
    #android_hardware_UsbDeviceConnection.cpp
    #android_hardware_UsbDevice.cpp
    #android_hardware_UsbRequest.cpp
    #android_media_AudioRecord.cpp
    #android_media_AudioSystem.cpp
    #android_media_AudioTrack.cpp
    #android_media_JetPlayer.cpp
    #android_media_RemoteDisplay.cpp
    #android_media_ToneGenerator.cpp
    #android_net_LocalSocketImpl.cpp
    #android_net_NetUtils.cpp
    #android_net_TrafficStats.cpp
    #android_net_wifi_WifiNative.cpp
    #android_nio_utils.cpp
    #android_opengl_EGL14.cpp
    #android_opengl_EGLExt.cpp
    #android_opengl_GLES10.cpp
    #android_opengl_GLES10Ext.cpp
    #android_opengl_GLES11.cpp
    #android_opengl_GLES11Ext.cpp
    #android_opengl_GLES20.cpp
    #android_opengl_GLES30.cpp
#    android_os_Debug.cpp              # Problems: includes memtrack.h
    android_os_FileUtils.cpp          # Builds
#    android_os_MemoryFile.cpp         # Problems: cast 64 bit / jint
#    android_os_MessageQueue.cpp       # Problems: include utils/Looper.h
    android_os_Parcel.cpp             # Problems: cast 64 bit / jint
    #android_os_SELinux.cpp
#    android_os_SystemClock.cpp       # Problems: ioctl(...ANDROID_ALARM_SET_RTC ...)
    android_os_SystemProperties.cpp   # Builds
    android_os_Trace.cpp              # Builds
    #android_os_UEventObserver.cpp
    #AndroidRuntime.cpp
    #android_server_NetworkManagementSocketTagger.cpp
    #android_server_Watchdog.cpp
    android_text_AndroidBidi.cpp      # Builds
    android_text_AndroidCharacter.cpp # Builds
#    android_text_format_Time.cpp     # Problems: includes bionic_time.h
#    android_util_AssetManager.cpp     # Problems: includes android_runtime/android_util_AssetManager.h>
    android_util_Binder.cpp           # Problems: cast 64 bit / int32_t
    android_util_EventLog.cpp	      # Builds
    android_util_FileObserver.cpp     # Builds
#    android_util_FloatMath.cpp	      # Problems: Uses SK_ARRAY_COUNT from SkTypes.h (Skia)
    android_util_Log.cpp	      # Builds
    android_util_Process.cpp	      # Builds
#    android_util_StringBlock.cpp      # Problems: includes androidfw/ResourceTypes.h
#    android_util_XmlBlock.cpp          # Problems: includes androidfw/AssetManager.h
    #android_view_DisplayEventReceiver.cpp
    #android_view_GLES20Canvas.cpp
    #android_view_GLES20DisplayList.cpp
    #android_view_GraphicBuffer.cpp
    #android_view_HardwareRenderer.cpp
    #android_view_InputChannel.cpp
    #android_view_InputDevice.cpp
    #android_view_InputEventReceiver.cpp
    #android_view_InputEventSender.cpp
    #android_view_InputQueue.cpp
    #android_view_KeyCharacterMap.cpp
    #android_view_KeyEvent.cpp
    #android_view_MotionEvent.cpp
    #android_view_PointerIcon.cpp
    #android_view_SurfaceControl.cpp
    #android_view_Surface.cpp
    #android_view_SurfaceSession.cpp
    #android_view_TextureView.cpp
    #android_view_VelocityTracker.cpp
    #BindTest.cpp
    #com_android_internal_content_NativeLibraryHelper.cpp
    #com_android_internal_net_NetworkStatsFactory.cpp
    #com_android_internal_os_ZygoteInit.cpp
    #com_google_android_gles_jni_EGLImpl.cpp
    #com_google_android_gles_jni_GLImpl.cpp
    #GraphicsExternGlue.h
    #GraphicsRegisterGlue.h
    #Time.cpp

    #graphics/AutoDecodeCancel.cpp
    #graphics/Bitmap.cpp
    #graphics/BitmapFactory.cpp
    #graphics/BitmapRegionDecoder.cpp
    #graphics/Camera.cpp
    #graphics/Canvas.cpp
    #graphics/ColorFilter.cpp
    #graphics/CreateJavaOutputStreamAdaptor.cpp
    #graphics/DrawFilter.cpp
    #graphics/Graphics.cpp
    #graphics/HarfBuzzNGFaceSkia.cpp
    #graphics/Interpolator.cpp
    #graphics/LayerRasterizer.cpp
    #graphics/MaskFilter.cpp
    #graphics/Matrix.cpp
    #graphics/Movie.cpp
    #graphics/NinePatch.cpp
    #graphics/NinePatchImpl.cpp
    #graphics/NinePatchPeeker.cpp
    #graphics/Paint.cpp
    #graphics/Path.cpp
    #graphics/PathEffect.cpp
    #graphics/PathMeasure.cpp
    #graphics/Picture.cpp
    #graphics/PorterDuff.cpp
    #graphics/Rasterizer.cpp
    #graphics/Region.cpp
    #graphics/Shader.cpp
    #graphics/SurfaceTexture.cpp
    #graphics/TextLayoutCache.cpp
    #graphics/TextLayout.cpp
    #graphics/Typeface.cpp
    #graphics/Utils.cpp
    #graphics/Xfermode.cpp
    #graphics/YuvToJpegEncoder.cpp
    #graphics/pdf/PdfDocument.cpp

    #opengl/poly_clip.cpp
    #opengl/util.cpp
)

set(libjni_HEADERS
#    ApkFile.h
)

add_library(jni SHARED ${libjni_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(jni PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

target_link_libraries(jni utils nativehelper #KF5::Archive
			  #Qt5::Core
)

install(TARGETS jni DESTINATION ${LIB_INSTALL_DIR})
install(FILES
        ${libjni_HEADERS}
        DESTINATION include/libjni)
