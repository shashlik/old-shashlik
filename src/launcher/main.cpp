/*
 * Main entry of app process.
 *
 * Starts the interpreted runtime, then starts up the application.
 *
 */

#define LOG_TAG "appproc"


// POSIX
//#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include <unistd.h>

//#include <cutils/properties.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
// #if 0 // See note in ProcessGlobals.cpp
// #else
// #include "ProcessGlobals.h"
// #endif
//#include <utils/Log.h>
#include <cutils/process_name.h>
//#include <cutils/memory.h>
//#include <cutils/trace.h>
//#include <android_runtime/AndroidRuntime.h>
//#include <sys/personality.h>

#include "shashlikversion.h"
#include "AppRuntime.h"
#include "appthread.h"

#include <QCoreApplication>

#define PROGRAM_NAME "shashlik-launcher"

void app_usage()
{
    fprintf(stderr, "%s %s\n", PROGRAM_NAME, SHASHLIK_VERSION_STRING);
    fprintf(stderr,
	    "Usage: %s [java-options] cmd-dir start-class-name [options]\n",
	    PROGRAM_NAME);
}


// using namespace shashlik;
using namespace android;


/*
 * sets argv0 to as much of newArgv0 as will fit
 */
static void setArgv0(const char *argv0, const char *newArgv0)
{
#if 0 // temp. disabled to make it build
    strlcpy(const_cast<char *>(argv0), newArgv0, strlen(argv0));
#else
    strncpy(const_cast<char *>(argv0), newArgv0, strlen(argv0));
#endif
}

int main(int argc, char* argv[])
{
//     InputArgs args = {argc, argv};
//     StartAppThread(args);
#ifdef __arm__
    /*
     * b/7188322 - Temporarily revert to the compat memory layout
     * to avoid breaking third party apps.
     *
     * THIS WILL GO AWAY IN A FUTURE ANDROID RELEASE.
     *
     * http://git.kernel.org/?p=linux/kernel/git/torvalds/linux-2.6.git;a=commitdiff;h=7dbaa466
     * changes the kernel mapping from bottom up to top-down.
     * This breaks some programs which improperly embed
     * an out of date copy of Android's linker.
     */
    char value[PROPERTY_VALUE_MAX];
    property_get("ro.kernel.qemu", value, "");
    bool is_qemu = (strcmp(value, "1") == 0);
    if ((getenv("NO_ADDR_COMPAT_LAYOUT_FIXUP") == NULL) && !is_qemu) {
        int current = personality(0xFFFFFFFF);
        if ((current & ADDR_COMPAT_LAYOUT) == 0) {
            personality(current | ADDR_COMPAT_LAYOUT);
            setenv("NO_ADDR_COMPAT_LAYOUT_FIXUP", "1", 1);
            execv("/system/bin/app_process", argv);
            return -1;
        }
    }
    unsetenv("NO_ADDR_COMPAT_LAYOUT_FIXUP");
#endif

    // These are global variables in ProcessState.cpp
//     mArgC = argc;
//     mArgV = argv;

//     mArgLen = 0;
//     for (int i=0; i<argc; i++) {
//         mArgLen += strlen(argv[i]) + 1;
//     }
//     mArgLen--;

//     while(!qApp) {
//         sleep(1);
//     }
    AppRuntime runtime;
    const char* argv0 = argv[0];

    // Process command line arguments
    // ignore argv[0]
    argc--;
    argv++;

    // Everything up to '--' or first non '-' arg goes to the vm

    int i = runtime.addVmArguments(argc, argv);

    // Parse runtime arguments.  Stop at first unrecognized option.
    bool zygote = false;
    bool startSystemServer = false;
    bool application = false;
    const char* parentDir = NULL;
    const char* niceName = NULL;
    const char* className = NULL;
    while (i < argc) {
        const char* arg = argv[i++];
        if (!parentDir) {
            parentDir = arg;
        } else if (strcmp(arg, "--zygote") == 0) {
            zygote = true;
            niceName = "zygote";
        } else if (strcmp(arg, "--start-system-server") == 0) {
            startSystemServer = true;
        } else if (strcmp(arg, "--application") == 0) {
            application = true;
        } else if (strncmp(arg, "--nice-name=", 12) == 0) {
            niceName = arg + 12;
        } else {
            className = arg;
            break;
        }
    }

    if (niceName && *niceName) {
        setArgv0(argv0, niceName);
        set_process_name(niceName);
    }

    runtime.setParentDir(parentDir);

    if (zygote) {
        runtime.start("com.android.internal.os.ZygoteInit",
                startSystemServer ? "start-system-server" : "");
    } else if (className) {
        // Remainder of args get passed to startup class main()
        runtime.setClassName(className);
        runtime.setArgcArgv(argc - i, argv + i);
        runtime.start("com.android.internal.os.RuntimeInit",
                application ? "application" : "tool");
    } else {
        fprintf(stderr, "%s %s error: no class name or --zygote supplied.\n",
        PROGRAM_NAME, SHASHLIK_VERSION_STRING);
        app_usage();
        LOG_ALWAYS_FATAL("app_process: no class name or --zygote supplied.");
        return 10;
    }
}
