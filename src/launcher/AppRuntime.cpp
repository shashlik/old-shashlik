/*
 * Main entry of app process.
 *
 * Starts the interpreted runtime, then starts up the application.
 *
 */

#define LOG_TAG "appproc"

#include "AppRuntime.h"

//#include <stdlib.h>
//#include <stdio.h>
//#include <unistd.h>

//#include <cutils/properties.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
//#include <utils/Log.h>
//#include <cutils/process_name.h>
//#include <cutils/memory.h>
#include <cutils/trace.h>
//#include <android_runtime/AndroidRuntime.h>
//#include <sys/personality.h>


namespace android {


AppRuntime::AppRuntime()
    : m_parentDir(0)
    , m_className(0)
    , m_class(0)
    , m_argC(0)
    , m_argV(0)
{
}

AppRuntime::~AppRuntime()
{
}


void AppRuntime::setParentDir(const char* parentDir)
{
    m_parentDir = parentDir;
}

#if 0
const char* AppRuntime::getParentDir() const
{
    return m_parentDir;
}
#endif

void AppRuntime::setClassName(const char *className)
{
    m_className = className;
}

const char* AppRuntime::getClassName() const
{
    return m_className;
}

void AppRuntime::setArgcArgv(int argc, const char *const *argv)
{
    m_argC = argc;
    m_argV = argv;
}



// ----------------------------------------------------------------
//                 Reimplemented virtual functions


void AppRuntime::onVmCreated(JNIEnv* env)
{
    if (m_className == NULL) {
	return; // Zygote. Nothing to do here.
    }

    /*
     * This is a little awkward because the JNI FindClass call uses the
     * class loader associated with the native method we're executing in.
     * If called in onStarted (from RuntimeInit.finishInit because we're
     * launching "am", for example), FindClass would see that we're calling
     * from a boot class' native method, and so wouldn't look for the class
     * we're trying to look up in CLASSPATH. Unfortunately it needs to,
     * because the "am" classes are not boot classes.
     *
     * The easiest fix is to call FindClass here, early on before we start
     * executing boot class Java code and thereby deny ourselves access to
     * non-boot classes.
     */
    char* slashClassName = toSlashClassName(m_className);
    m_class = env->FindClass(slashClassName);
    if (m_class == NULL) {
	ALOGE("ERROR: could not find class '%s'\n", m_className);
    }
    free(slashClassName);

    m_class = reinterpret_cast<jclass>(env->NewGlobalRef(m_class));
}

void AppRuntime::onStarted()
{
    sp<ProcessState> proc = ProcessState::self();
    ALOGV("App process: starting thread pool.\n");
    proc->startThreadPool();

    AndroidRuntime* ar = AndroidRuntime::getRuntime();
    ar->callMain(m_className, m_class, m_argC, m_argV);

    IPCThreadState::self()->stopProcess();
}

void AppRuntime::onZygoteInit()
{
    // Re-enable tracing now that we're no longer in Zygote.
    atrace_set_tracing_enabled(true);

    sp<ProcessState> proc = ProcessState::self();
    ALOGV("App process: starting thread pool.\n");
    proc->startThreadPool();
}

void AppRuntime::onExit(int code)
{
    if (m_className == NULL) {
	// if zygote
	IPCThreadState::self()->stopProcess();
    }

    AndroidRuntime::onExit(code);
}


}
