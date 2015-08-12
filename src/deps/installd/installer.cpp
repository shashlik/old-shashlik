#include <unistd.h>
#include <sys/types.h>

#include <QStringList>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>

/* elements combined with a valid package name to form paths */

#define PRIMARY_USER_PREFIX    "data/"
#define SECONDARY_USER_PREFIX  "user/"

#define PKG_DIR_POSTFIX        ""

#define PKG_LIB_POSTFIX        "/lib"

#define CACHE_DIR_POSTFIX      "/cache"

#define APP_SUBDIR             "app/" // sub-directory under ANDROID_DATA

#define APP_LIB_SUBDIR         "app-lib/" // sub-directory under ANDROID_DATA

#define MEDIA_SUBDIR           "media/" // sub-directory under ANDROID_DATA

/* other handy constants */

#define PRIVATE_APP_SUBDIR     "app-private/" // sub-directory under ANDROID_DATA

#define DALVIK_CACHE_PREFIX    "/data/dalvik-cache/"
#define DALVIK_CACHE_POSTFIX   "/classes.dex"

#define UPDATE_COMMANDS_DIR_PREFIX  "/system/etc/updatecmds/"

#define PKG_NAME_MAX  128   /* largest allowed package name */
#define PKG_PATH_MAX  256   /* max size of any path we use */

/* data structures */

typedef struct {
    char* path;
    size_t len;
} dir_rec_t;

typedef struct {
    size_t count;
    dir_rec_t* dirs;
} dir_rec_array_t;

extern dir_rec_t android_app_dir;
extern dir_rec_t android_app_private_dir;
extern dir_rec_t android_app_lib_dir;
extern dir_rec_t android_data_dir;
extern dir_rec_t android_asec_dir;
extern dir_rec_t android_media_dir;
extern dir_rec_array_t android_system_dirs;

extern "C" {
int get_path_from_env(dir_rec_t* rec, const char* var);
int copy_and_append(dir_rec_t* dst, const dir_rec_t* src, const char* suffix);
char *build_string2(char *s1, char *s2);

int install(const char *pkgname, uid_t uid, gid_t gid, const char *seinfo);
}

/**
 * Initialize all the global variables that are used elsewhere. Returns 0 upon
 * success and -1 on error.
 */
void free_globals() {
    size_t i;

    for (i = 0; i < android_system_dirs.count; i++) {
        if (android_system_dirs.dirs[i].path != NULL) {
            free(android_system_dirs.dirs[i].path);
        }
    }

    free(android_system_dirs.dirs);
}

int initialize_globals() {
    // Get the android data directory.
    if (get_path_from_env(&android_data_dir, "ANDROID_DATA") < 0) {
        return -1;
    }

    // Get the android app directory.
    if (copy_and_append(&android_app_dir, &android_data_dir, APP_SUBDIR) < 0) {
        return -1;
    }

    // Get the android protected app directory.
    if (copy_and_append(&android_app_private_dir, &android_data_dir, PRIVATE_APP_SUBDIR) < 0) {
        return -1;
    }

    // Get the android app native library directory.
    if (copy_and_append(&android_app_lib_dir, &android_data_dir, APP_LIB_SUBDIR) < 0) {
        return -1;
    }

    // Get the sd-card ASEC mount point.
    if (get_path_from_env(&android_asec_dir, "ASEC_MOUNTPOINT") < 0) {
        return -1;
    }

    // Get the android media directory.
    if (copy_and_append(&android_media_dir, &android_data_dir, MEDIA_SUBDIR) < 0) {
        return -1;
    }

    // Take note of the system and vendor directories.
    android_system_dirs.count = 2;

    android_system_dirs.dirs = calloc(android_system_dirs.count, sizeof(dir_rec_t));
    if (android_system_dirs.dirs == NULL) {
        qDebug() << "Couldn't allocate array for dirs; aborting\n";
        return -1;
    }

    // system
    if (get_path_from_env(&android_system_dirs.dirs[0], "ANDROID_ROOT") < 0) {
        free_globals();
        return -1;
    }

    // append "app/" to dirs[0]
    char *system_app_path = build_string2(android_system_dirs.dirs[0].path, APP_SUBDIR);
    android_system_dirs.dirs[0].path = system_app_path;
    android_system_dirs.dirs[0].len = strlen(system_app_path);

    // vendor
    // TODO replace this with an environment variable (doesn't exist yet)
    android_system_dirs.dirs[1].path = "/vendor/app/";
    android_system_dirs.dirs[1].len = strlen(android_system_dirs.dirs[1].path);

    return 0;
}

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    app.setApplicationName("shashlik-installer");
    app.setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("Android application installer tool");
    QCommandLineOption helpArgument =  parser.addHelpOption();
    QCommandLineOption versionArgument = parser.addVersionOption();
    parser.addPositionalArgument("apkfile", "Install the passed apk file.");
    parser.process(app);

    QStringList apkfile = parser.positionalArguments();
    if(apkfile.length() > 0 && QFile::exists(apkfile.at(0))) {
        initialize_globals();
        install(apkfile.at(0).toLatin1(), getuid(), getuid(), "");
    }

    return app.exec();
}
