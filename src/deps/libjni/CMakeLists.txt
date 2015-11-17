project(libjni)

set(JNI_SOURCE_DIR ${ANDROID_FRAMEWORKS_BASE}/core/jni)

#find_package(KF5Archive NO_MODULE)
find_package(LibCAP REQUIRED) # required for zygote init, that is, sys/capability.h
find_package (Wayland COMPONENTS Client Egl Cursor REQUIRED)
find_package(KF5Wayland REQUIRED)

add_definitions(-DHAVE_ANDROID_OS   # To make cutils/trace work.  FIXME: Check what other consequences this has.
                -fpermissive  # FIXME: for pointer to int conversion in printf on x86_64

                -DHAVE_CONFIG_H -DKHTML_NO_EXCEPTIONS -DGKWQ_NO_JAVA -DUSE_OPENGL_RENDERER
                -DHAVE_OOM_ADJ # Well... we do!
                -DNO_SUPPORT_JS_BINDING -DQT_NO_WHEELEVENT -DKHTML_NO_XBL
#                 -U__APPLE__
                -DPACKED=""
                -DEGL_TRACE=1
                -DGL_GLEXT_PROTOTYPES -DEGL_EGLEXT_PROTOTYPES
                -DSK_BUILD_FOR_ANDROID # lololo skia internals
                ${Wayland_DEFINITIONS}
)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    ${JNI_SOURCE_DIR}
                    ${JNI_SOURCE_DIR}/android/graphics
                    ${ANDROID_FRAMEWORKS_BASE}/libs/hwui
                    ${OPENGL_INCLUDES}
                    ${ANDROID_FRAMEWORKS_NATIVE_PATH}/opengl/libs
                    ${GENERAL_SOURCE_PATH}/android-libhardware/include
                    ${GENERAL_SOURCE_PATH}/android-libhardware/modules
                    ${HARFBUZZ_INCLUDE_DIRS}
                    ${SQLITE3_INCLUDES}
                    ${SKIA_INCLUDES}
                    ${SKIA_PATH}/include ${SKIA_PATH}/src/core ${SKIA_PATH}/src/images
                    ${LIBCUTILS_INCLUDES}
                    ${LIBNATIVEHELPER_INCLUDEDIRS}
                    ${LIBBINDER_INCLUDES}
                    ${ANDROID_FRAMEWORKS_BASE}/include
#                     ${GENERAL_SOURCE_PATH}/bionic/libc/private
                    ${CMAKE_SOURCE_DIR}/src/deps/stripped_bionic # for the hackified string.h
                    ${LibCAP_INCLUDE_DIRS}
                    ${Wayland_INCLUDE_DIRS}
)

set(GENTROID_DIR ${GENERAL_SOURCE_PATH}/gentroid-frameworks-base)

set(libjni_SRCS
#     ${GENTROID_DIR}/core/jni/WaylandClient.cpp
#     ${GENTROID_DIR}/core/jni/com_google_android_gles_jni_EGLImpl.cpp
#     ${GENTROID_DIR}/core/jni/com_google_android_gles_jni_GLImpl.cpp
#     ${GENTROID_DIR}/core/jni/android_app_NativeActivity.cpp
#     ${GENTROID_DIR}/core/jni/android_opengl_EGL14.cpp
#     ${GENTROID_DIR}/core/jni/android_opengl_EGLExt.cpp
#     ${GENTROID_DIR}/core/jni/android_opengl_GLES20.cpp
#     ${GENTROID_DIR}/core/jni/android_opengl_GLES30.cpp
#     ${GENTROID_DIR}/core/jni/android_view_Wayland.cpp
#     ${GENTROID_DIR}/core/jni/android_view_DisplayEventReceiver.cpp
#     ${GENTROID_DIR}/core/jni/android_view_HardwareRenderer.cpp
#     ${GENTROID_DIR}/core/jni/android_view_GLES20DisplayList.cpp
#     ${GENTROID_DIR}/core/jni/android_view_GLES20Canvas.cpp
#     ${GENTROID_DIR}/core/jni/android/opengl/poly_clip.cpp
#     ${GENTROID_DIR}/core/jni/android/opengl/util.cpp


    ${CMAKE_CURRENT_SOURCE_DIR}/android_view_Wayland.cpp
    ${JNI_SOURCE_DIR}/AndroidRuntime.cpp
    ${JNI_SOURCE_DIR}/Time.cpp
    ${JNI_SOURCE_DIR}/com_android_internal_content_NativeLibraryHelper.cpp
    ${JNI_SOURCE_DIR}/com_google_android_gles_jni_EGLImpl.cpp
    ${JNI_SOURCE_DIR}/com_google_android_gles_jni_GLImpl.cpp
    ${JNI_SOURCE_DIR}/android_app_NativeActivity.cpp
    ${JNI_SOURCE_DIR}/android_opengl_EGL14.cpp
    ${JNI_SOURCE_DIR}/android_opengl_EGLExt.cpp
    ${JNI_SOURCE_DIR}/android_opengl_GLES10.cpp
    ${JNI_SOURCE_DIR}/android_opengl_GLES10Ext.cpp
    ${JNI_SOURCE_DIR}/android_opengl_GLES11.cpp
    ${JNI_SOURCE_DIR}/android_opengl_GLES11Ext.cpp
    ${JNI_SOURCE_DIR}/android_opengl_GLES20.cpp
    ${JNI_SOURCE_DIR}/android_opengl_GLES30.cpp
    ${JNI_SOURCE_DIR}/android_database_CursorWindow.cpp
    ${JNI_SOURCE_DIR}/android_database_SQLiteCommon.cpp
    ${JNI_SOURCE_DIR}/android_database_SQLiteConnection.cpp
    ${JNI_SOURCE_DIR}/android_database_SQLiteGlobal.cpp
    ${JNI_SOURCE_DIR}/android_database_SQLiteDebug.cpp
    ${JNI_SOURCE_DIR}/android_emoji_EmojiFactory.cpp
    ${JNI_SOURCE_DIR}/android_view_DisplayEventReceiver.cpp
    ${JNI_SOURCE_DIR}/android_view_Surface.cpp
    ${JNI_SOURCE_DIR}/android_view_SurfaceControl.cpp
    ${JNI_SOURCE_DIR}/android_view_SurfaceSession.cpp
    ${JNI_SOURCE_DIR}/android_view_TextureView.cpp
    ${JNI_SOURCE_DIR}/android_view_InputChannel.cpp
    ${JNI_SOURCE_DIR}/android_view_InputDevice.cpp
    ${JNI_SOURCE_DIR}/android_view_InputEventReceiver.cpp
    ${JNI_SOURCE_DIR}/android_view_InputEventSender.cpp
    ${JNI_SOURCE_DIR}/android_view_InputQueue.cpp
    ${JNI_SOURCE_DIR}/android_view_KeyEvent.cpp
    ${JNI_SOURCE_DIR}/android_view_KeyCharacterMap.cpp
    ${JNI_SOURCE_DIR}/android_view_HardwareRenderer.cpp
    ${JNI_SOURCE_DIR}/android_view_GraphicBuffer.cpp
    ${JNI_SOURCE_DIR}/android_view_GLES20DisplayList.cpp
    ${JNI_SOURCE_DIR}/android_view_GLES20Canvas.cpp
    ${JNI_SOURCE_DIR}/android_view_MotionEvent.cpp
    ${JNI_SOURCE_DIR}/android_view_PointerIcon.cpp
    ${JNI_SOURCE_DIR}/android_view_VelocityTracker.cpp
    ${JNI_SOURCE_DIR}/android_text_AndroidCharacter.cpp
    ${JNI_SOURCE_DIR}/android_text_AndroidBidi.cpp
    ${JNI_SOURCE_DIR}/android_os_Debug.cpp
    ${JNI_SOURCE_DIR}/android_os_MemoryFile.cpp
    ${JNI_SOURCE_DIR}/android_os_MessageQueue.cpp
    ${JNI_SOURCE_DIR}/android_os_Parcel.cpp
    ${JNI_SOURCE_DIR}/android_os_SELinux.cpp
    ${JNI_SOURCE_DIR}/android_os_SystemClock.cpp
    ${JNI_SOURCE_DIR}/android_os_SystemProperties.cpp
    ${JNI_SOURCE_DIR}/android_os_Trace.cpp
    ${JNI_SOURCE_DIR}/android_os_UEventObserver.cpp
    ${JNI_SOURCE_DIR}/android_net_LocalSocketImpl.cpp
    ${JNI_SOURCE_DIR}/android_net_NetUtils.cpp
    ${JNI_SOURCE_DIR}/android_net_TrafficStats.cpp
#     ${JNI_SOURCE_DIR}/android_net_wifi_WifiNative.cpp
    ${JNI_SOURCE_DIR}/android_nio_utils.cpp
    ${JNI_SOURCE_DIR}/android_text_format_Time.cpp
    ${JNI_SOURCE_DIR}/android_util_AssetManager.cpp
    ${JNI_SOURCE_DIR}/android_util_Binder.cpp
    ${JNI_SOURCE_DIR}/android_util_EventLog.cpp
    ${JNI_SOURCE_DIR}/android_util_Log.cpp
    ${JNI_SOURCE_DIR}/android_util_FloatMath.cpp
    ${JNI_SOURCE_DIR}/android_util_Process.cpp
    ${JNI_SOURCE_DIR}/android_util_StringBlock.cpp
    ${JNI_SOURCE_DIR}/android_util_XmlBlock.cpp
    ${JNI_SOURCE_DIR}/android/graphics/AutoDecodeCancel.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Bitmap.cpp
    ${JNI_SOURCE_DIR}/android/graphics/BitmapFactory.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Camera.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Canvas.cpp
    ${JNI_SOURCE_DIR}/android/graphics/ColorFilter.cpp
    ${JNI_SOURCE_DIR}/android/graphics/DrawFilter.cpp
    ${JNI_SOURCE_DIR}/android/graphics/CreateJavaOutputStreamAdaptor.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Graphics.cpp
    ${JNI_SOURCE_DIR}/android/graphics/HarfBuzzNGFaceSkia.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Interpolator.cpp
    ${JNI_SOURCE_DIR}/android/graphics/LayerRasterizer.cpp
    ${JNI_SOURCE_DIR}/android/graphics/MaskFilter.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Matrix.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Movie.cpp
    ${JNI_SOURCE_DIR}/android/graphics/NinePatch.cpp
    ${JNI_SOURCE_DIR}/android/graphics/NinePatchImpl.cpp
    ${JNI_SOURCE_DIR}/android/graphics/NinePatchPeeker.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Paint.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Path.cpp
    ${JNI_SOURCE_DIR}/android/graphics/PathMeasure.cpp
    ${JNI_SOURCE_DIR}/android/graphics/PathEffect.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Picture.cpp
    ${JNI_SOURCE_DIR}/android/graphics/PorterDuff.cpp
    ${JNI_SOURCE_DIR}/android/graphics/BitmapRegionDecoder.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Rasterizer.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Region.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Shader.cpp
    ${JNI_SOURCE_DIR}/android/graphics/SurfaceTexture.cpp
    ${JNI_SOURCE_DIR}/android/graphics/TextLayout.cpp
    ${JNI_SOURCE_DIR}/android/graphics/TextLayoutCache.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Typeface.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Utils.cpp
    ${JNI_SOURCE_DIR}/android/graphics/Xfermode.cpp
    ${JNI_SOURCE_DIR}/android/graphics/YuvToJpegEncoder.cpp
#     ${JNI_SOURCE_DIR}/android/graphics/pdf/PdfDocument.cpp
#     ${JNI_SOURCE_DIR}/android_media_AudioRecord.cpp
#     ${JNI_SOURCE_DIR}/android_media_AudioSystem.cpp
#     ${JNI_SOURCE_DIR}/android_media_AudioTrack.cpp
#     ${JNI_SOURCE_DIR}/android_media_JetPlayer.cpp
#     ${JNI_SOURCE_DIR}/android_media_RemoteDisplay.cpp
#     ${JNI_SOURCE_DIR}/android_media_ToneGenerator.cpp
#     ${JNI_SOURCE_DIR}/android_hardware_Camera.cpp
#     ${JNI_SOURCE_DIR}/android_hardware_camera2_CameraMetadata.cpp
    ${JNI_SOURCE_DIR}/android_hardware_SensorManager.cpp
    ${JNI_SOURCE_DIR}/android_hardware_SerialPort.cpp
    ${JNI_SOURCE_DIR}/android_hardware_UsbDevice.cpp
    ${JNI_SOURCE_DIR}/android_hardware_UsbDeviceConnection.cpp
    ${JNI_SOURCE_DIR}/android_hardware_UsbRequest.cpp
    ${JNI_SOURCE_DIR}/android_debug_JNITest.cpp
    ${JNI_SOURCE_DIR}/android_util_FileObserver.cpp
    ${JNI_SOURCE_DIR}/android/opengl/poly_clip.cpp
    ${JNI_SOURCE_DIR}/android/opengl/util.cpp
    ${JNI_SOURCE_DIR}/android_server_NetworkManagementSocketTagger.cpp
    ${JNI_SOURCE_DIR}/android_server_Watchdog.cpp
    ${JNI_SOURCE_DIR}/android_ddm_DdmHandleNativeHeap.cpp
    ${JNI_SOURCE_DIR}/com_android_internal_os_ZygoteInit.cpp
    ${JNI_SOURCE_DIR}/android_backup_BackupDataInput.cpp
    ${JNI_SOURCE_DIR}/android_backup_BackupDataOutput.cpp
    ${JNI_SOURCE_DIR}/android_backup_FileBackupHelperBase.cpp
    ${JNI_SOURCE_DIR}/android_backup_BackupHelperDispatcher.cpp
    ${JNI_SOURCE_DIR}/android_app_backup_FullBackup.cpp
    ${JNI_SOURCE_DIR}/android_content_res_ObbScanner.cpp
    ${JNI_SOURCE_DIR}/android_content_res_Configuration.cpp
    ${JNI_SOURCE_DIR}/android_animation_PropertyValuesHolder.cpp
    ${JNI_SOURCE_DIR}/com_android_internal_net_NetworkStatsFactory.cpp
)

set(libjni_HEADERS
#    ApkFile.h
)

add_library(jni SHARED ${libjni_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(jni PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

target_link_libraries(jni
ffi
skia
safe-iop
androidfw
nativehelper
sqlite3
stripped_bionic
usbhost
memtrack
netutils
gui
input
shashlik_jni
hwui
emoji
selinux
#KF5::Archive
    GLESv1_CM
    EGL
    GLESv2
    epoxy
#     icuuc icui18n - these two included via sqlite3
#    ${OPENGL_LIBRARIES} - included by skia
			  #Qt5::Core
			  ${Wayland_LIBRARIES}
			  KF5WaylandClient
			  waylandthings
)

install(TARGETS jni DESTINATION ${ANDROID_LIB_DIR})
install(FILES
        ${libjni_HEADERS}
        DESTINATION include/libjni)
