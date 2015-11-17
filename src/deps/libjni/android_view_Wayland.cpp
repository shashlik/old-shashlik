/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "Surface"

#include <stdio.h>
#include <wayland-client.h>
#include <wayland-util.h>
#include <wayland-egl.h>
#include <wayland-cursor.h>
#include <pthread.h>
// #include <GLES2/gl2.h>
// #include <EGL/egl.h>
// #include <EGL/eglext.h>
#include <epoxy/gl.h>
#include <epoxy/egl.h>

#include "jni.h"
#include "JNIHelp.h"
#include "android/graphics/GraphicsJNI.h"

#include <android_runtime/AndroidRuntime.h>
#include <android_runtime/Log.h>



#include <utils/misc.h>
#include <utils/Log.h>

#include "WaylandWindow.h"
#include "WaylandClient.h"

// ----------------------------------------------------------------------------

namespace android {

static struct {
    jclass clazz;
    jfieldID mNativeObject;
    jfieldID mLock;
    jmethodID ctor;
} gWaylandWindowClassInfo;


WaylandWindow* android_view_Wayland_getWindow(JNIEnv* env, jobject windowObj) {
    WaylandWindow* win;
    jobject lock = env->GetObjectField(windowObj,
            gWaylandWindowClassInfo.mLock);
    if (env->MonitorEnter(lock) == JNI_OK) {
        win = reinterpret_cast<WaylandWindow*>(
                env->GetLongField(windowObj, gWaylandWindowClassInfo.mNativeObject));
        env->MonitorExit(lock);
    }
    return win;
}

static jlong nativeCreateWindow(JNIEnv* env, jclass clazz, jint width, jint height)
{
    WaylandWindow *window = new WaylandWindow(width, height);
    window->init();
    return (jlong)window;
}

static void nativeClearInstance(JNIEnv* env, jclass clazz)
{
    ALOGE("Clearing WaylandClient instance %p in %d", &WaylandClient::getInstance(), getpid());
    WaylandClient::clearInstance();
}

static void nativeConnect(JNIEnv* env, jclass clazz)
{
    ALOGE("Connecting up the WaylandClient instance %p in %d", &WaylandClient::getInstance(), getpid());
//     WaylandClient *client = WaylandClient::getInstance();
    WaylandClient::getInstance().connect();
}

static jint nativeDispatch(JNIEnv* env, jclass clazz)
{
//     WaylandClient *client = WaylandClient::getInstance();
    return wl_display_dispatch(WaylandClient::getInstance().getDisplay());
}

static jlong nativeEGLDisplay(JNIEnv* env, jclass clazz)
{
    return (jlong)WaylandClient::getInstance().getDisplay();
}

// ----------------------------------------------------------------------------

static JNINativeMethod gWaylandMethods[] = {
        {"nativeCreateWindow", "(II)J", (void*)nativeCreateWindow },
        {"nativeClearInstance", "()V", (void*)nativeClearInstance },
        {"nativeConnect", "()V", (void*)nativeConnect },
        {"nativeDispatch", "()I", (void*)nativeDispatch },
        {"nativeEGLDisplay", "()J", (void*)nativeEGLDisplay }
    };



int register_android_view_Wayland(JNIEnv* env)
{
    int err = AndroidRuntime::registerNativeMethods(env, "android/view/WaylandClient",
            gWaylandMethods, NELEM(gWaylandMethods));

    jclass clazz = env->FindClass("android/view/WaylandWindow");
    gWaylandWindowClassInfo.clazz = jclass(env->NewGlobalRef(clazz));
    gWaylandWindowClassInfo.mNativeObject =
            env->GetFieldID(gWaylandWindowClassInfo.clazz, "mNativeObject", "J");
    gWaylandWindowClassInfo.mLock =
            env->GetFieldID(gWaylandWindowClassInfo.clazz, "mLock", "Ljava/lang/Object;");
    gWaylandWindowClassInfo.ctor = env->GetMethodID(gWaylandWindowClassInfo.clazz, "<init>", "(J)V");

    return err;
}

}
