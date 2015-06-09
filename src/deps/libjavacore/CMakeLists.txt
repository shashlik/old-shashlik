project(libjavacore)

find_package(ICU REQUIRED)
find_package(EXPAT REQUIRED)

set(libjavacore_dalvik_SRCS
    ${ANDROID_LIBCORE_PATH}/dalvik/src/main/native/org_apache_harmony_dalvik_NativeTestTarget.cpp
)

set(LUNI_SRC_PATH "${ANDROID_LIBCORE_PATH}/luni/src/main/native/")

set(libjavacore_luni_SRCS
    ${LUNI_SRC_PATH}/AsynchronousSocketCloseMonitor.cpp
    ${LUNI_SRC_PATH}/ExecStrings.cpp
    ${LUNI_SRC_PATH}/IcuUtilities.cpp
    ${LUNI_SRC_PATH}/JniException.cpp
    ${LUNI_SRC_PATH}/NetworkUtilities.cpp
    ${LUNI_SRC_PATH}/Register.cpp
    ${LUNI_SRC_PATH}/ZipUtilities.cpp
    ${LUNI_SRC_PATH}/cbigint.cpp
    ${LUNI_SRC_PATH}/java_io_Console.cpp
    ${LUNI_SRC_PATH}/java_io_File.cpp
    ${LUNI_SRC_PATH}/java_io_ObjectStreamClass.cpp
    ${LUNI_SRC_PATH}/java_lang_Character.cpp
    ${LUNI_SRC_PATH}/java_lang_Double.cpp
    ${LUNI_SRC_PATH}/java_lang_Float.cpp
    ${LUNI_SRC_PATH}/java_lang_Math.cpp
    ${LUNI_SRC_PATH}/java_lang_ProcessManager.cpp
    ${LUNI_SRC_PATH}/java_lang_RealToString.cpp
    ${LUNI_SRC_PATH}/java_lang_StrictMath.cpp # requires fdlibm - let's run without it for now
    ${LUNI_SRC_PATH}/java_lang_StringToReal.cpp
    ${LUNI_SRC_PATH}/java_lang_System.cpp
    ${LUNI_SRC_PATH}/java_math_NativeBN.cpp
    ${LUNI_SRC_PATH}/java_nio_ByteOrder.cpp
    ${LUNI_SRC_PATH}/java_nio_charset_Charsets.cpp
    ${LUNI_SRC_PATH}/java_text_Bidi.cpp
    ${LUNI_SRC_PATH}/java_util_regex_Matcher.cpp
    ${LUNI_SRC_PATH}/java_util_regex_Pattern.cpp
    ${LUNI_SRC_PATH}/java_util_zip_Adler32.cpp
    ${LUNI_SRC_PATH}/java_util_zip_CRC32.cpp
    ${LUNI_SRC_PATH}/java_util_zip_Deflater.cpp
    ${LUNI_SRC_PATH}/java_util_zip_Inflater.cpp
    ${LUNI_SRC_PATH}/libcore_icu_AlphabeticIndex.cpp
    ${LUNI_SRC_PATH}/libcore_icu_DateIntervalFormat.cpp
    ${LUNI_SRC_PATH}/libcore_icu_ICU.cpp
    ${LUNI_SRC_PATH}/libcore_icu_NativeBreakIterator.cpp
    ${LUNI_SRC_PATH}/libcore_icu_NativeCollation.cpp
    ${LUNI_SRC_PATH}/libcore_icu_NativeConverter.cpp
    ${LUNI_SRC_PATH}/libcore_icu_NativeDecimalFormat.cpp
    ${LUNI_SRC_PATH}/libcore_icu_NativeIDN.cpp
    ${LUNI_SRC_PATH}/libcore_icu_NativeNormalizer.cpp
    ${LUNI_SRC_PATH}/libcore_icu_NativePluralRules.cpp
    ${LUNI_SRC_PATH}/libcore_icu_TimeZoneNames.cpp
    ${LUNI_SRC_PATH}/libcore_icu_Transliterator.cpp
    ${LUNI_SRC_PATH}/libcore_io_AsynchronousCloseMonitor.cpp
    ${LUNI_SRC_PATH}/libcore_io_Memory.cpp
    ${LUNI_SRC_PATH}/libcore_io_OsConstants.cpp
    ${LUNI_SRC_PATH}/libcore_io_Posix.cpp
    ${LUNI_SRC_PATH}/libcore_net_RawSocket.cpp
    ${LUNI_SRC_PATH}/org_apache_harmony_xml_ExpatParser.cpp
    ${LUNI_SRC_PATH}/readlink.cpp
    ${LUNI_SRC_PATH}/realpath.cpp
    ${LUNI_SRC_PATH}/sun_misc_Unsafe.cpp
    ${LUNI_SRC_PATH}/valueOf.cpp
)

include_directories(
                    ${CMAKE_CURRENT_SOURCE_DIR}
                    ${EXPAT_INCLUDE_DIRS}
                    ${OPENSSL_INCLUDE_DIR}
                    ${ICU_INCLUDE_DIRS}
                    ${LIBANDROIDLIBCORE_INCLUDEDIRS}
                    ${LIBCUTILS_INCLUDES}
                    ${LIBNATIVEHELPER_INCLUDEDIRS}
                    ${ANDROID_FRAMEWORKS_BASE}/include
                    ${DALVIK_PATH}/vm
)

# From AndroidConfig.h
add_definitions(
    -DOS_SHARED_LIB_FORMAT_STR="lib%s.so"
    -D__ANDROID__
)

add_library(javacore SHARED ${libjavacore_dalvik_SRCS} ${libjavacore_luni_SRCS})
if(FORCE_32BIT_BUILD)
    set_target_properties(javacore PROPERTIES COMPILE_FLAGS "-m32 -std=c++11" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)
target_link_libraries(javacore jni ${ICU_LIBRARIES} ${OPENSSL_LIBRARIES} ${EXPAT_LIBRARIES})
install(TARGETS javacore DESTINATION ${ANDROID_LIB_DIR})
