
#include "WaylandWindow.h"

#define LOG_TAG "shashlik/WaylandWindow"

#include "WaylandClient.h"
// #include <android_runtime/AndroidRuntime.h>
#include <log/log.h>

namespace android {

wl_callback_listener WaylandWindow::mFrameListener = {
    WaylandWindow::sRedraw
};

wl_shell_surface_listener WaylandWindow::mShellSurfaceListener = {
    WaylandWindow::sShellHandlePing,
    WaylandWindow::sShellHandleConfigure,
    WaylandWindow::sShellHandlePopup
};

void WaylandWindow::init()
{
//     mClient = WaylandClient::getInstance();
//     mSurface = AndroidRuntime::getWaylandClient()->surface();//wl_compositor_create_surface(mClient->getCompositor());
    mSurface = wl_compositor_create_surface(WaylandClient::getInstance().getCompositor());
//     mShellSurface = AndroidRuntime::getWaylandClient()->shellSurface();// wl_shell_get_shell_surface(mClient->getShell(), mSurface);
    mShellSurface = wl_shell_get_shell_surface(WaylandClient::getInstance().getShell(), mSurface);

    if (mShellSurface) {
        wl_shell_surface_add_listener(mShellSurface, &mShellSurfaceListener, this);
        wl_shell_surface_set_toplevel(mShellSurface);
    } else {
       ALOGW("wl_shell_get_shell_surface FAILED \n");
       return;
    }

    wl_surface_set_user_data(mSurface, this);
    wl_shell_surface_set_title(mShellSurface, "android");
    wl_surface_commit(mSurface);
    mNative = wl_egl_window_create(mSurface, mWidth, mHeight);
    if (mNative == NULL) {
        ALOGW("wl_egl_window_create FAILED \n");
        return;
    } else {
        ALOGW("wl_egl_window_create succeded, resulting in %p \n", mNative);
    }
}

void WaylandWindow::sShellHandlePing(void *data, wl_shell_surface *surface,
	    uint32_t serial)
{
	wl_shell_surface_pong(surface, serial);
}

void WaylandWindow::sShellHandleConfigure(void *data, wl_shell_surface *surface,
		 uint32_t edges, int32_t width, int32_t height)
{
}

void WaylandWindow::sShellHandlePopup(void *data, wl_shell_surface *surface)
{
}

void WaylandWindow::sRedraw(void *data, wl_callback *callback, uint32_t time)
{
    ALOGW("Redrawing WaylandWindow");
    WaylandWindow *window = reinterpret_cast<WaylandWindow*>(data);
    window->redraw(callback, time);
}

void WaylandWindow::redraw(wl_callback *callback, uint32_t time)
{
    ALOGW("Actually redrawing WaylandWindow");

}


}
