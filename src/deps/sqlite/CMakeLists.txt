project(sqlite)

set(REPO_PATH ${GENERAL_SOURCE_PATH}/sqlite)

set(sqlite_android_SRCS
    ${REPO_PATH}/android/PhoneNumberUtils.cpp
    ${REPO_PATH}/android/OldPhoneNumberUtils.cpp
    ${REPO_PATH}/android/sqlite3_android.cpp
)

set(sqlite_SRCS
    ${REPO_PATH}/dist/sqlite3.c
)

include_directories(
    ${LIBCUTILS_INCLUDES}
    ${REPO_PATH}/dist
)

add_library(sqlite3_android STATIC ${sqlite_android_SRCS})
target_link_libraries(sqlite3_android log)

add_library(sqlite3 SHARED ${sqlite_SRCS})
target_compile_definitions(sqlite3
    PUBLIC
    -DNDEBUG=1
    -DHAVE_USLEEP=1
    -DSQLITE_HAVE_ISNAN
    -DSQLITE_DEFAULT_JOURNAL_SIZE_LIMIT=1048576
    -DSQLITE_THREADSAFE=2
    -DSQLITE_TEMP_STORE=3
    -DSQLITE_POWERSAFE_OVERWRITE=1
    -DSQLITE_DEFAULT_FILE_FORMAT=4
    -DSQLITE_DEFAULT_AUTOVACUUM=1
    -DSQLITE_ENABLE_MEMORY_MANAGEMENT=1
    -DSQLITE_ENABLE_FTS3
    -DSQLITE_ENABLE_FTS3_BACKWARDS
    -DSQLITE_ENABLE_FTS4
    -DSQLITE_OMIT_BUILTIN_TEST
    -DSQLITE_OMIT_COMPILEOPTION_DIAGS
    -DSQLITE_OMIT_LOAD_EXTENSION
    -DSQLITE_DEFAULT_FILE_PERMISSIONS=0600

    -DUSE_PREAD64
    -Dfdatasync=fdatasync
    -DHAVE_MALLOC_USABLE_SIZE
)
target_link_libraries(sqlite3
    sqlite3_android
    icuuc icui18n utils
    dl
    )

if(FORCE_32BIT_BUILD)
    set_target_properties(sqlite3 PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
    set_target_properties(sqlite3_android PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
endif(FORCE_32BIT_BUILD)

install(TARGETS sqlite3 DESTINATION ${ANDROID_LIB_DIR})
