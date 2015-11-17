#ifndef _ANDROID_WAYLANDWINDOW_H
#define _ANDROID_WAYLANDWINDOW_H

#include <epoxy/egl.h>
// #include <EGL/eglplatform.h>
#include <wayland-client.h>
#include <wayland-egl.h>
// #include <wayland-cursor.h>

namespace android {
class WaylandClient;
class WaylandWindow
{
public:
    WaylandWindow(int width, int height) : mWidth(width), mHeight(height) {}
    void init();
    static void sRedraw(void *data, wl_callback *callback, uint32_t time);
    void redraw(wl_callback *callback, uint32_t time);
    wl_egl_window* getNative() { return mNative; }
private:
    WaylandClient* mClient;
    static wl_shell_surface_listener mShellSurfaceListener;
    static wl_callback_listener mFrameListener;
    wl_surface *mSurface;
    wl_shell_surface *mShellSurface;
    wl_egl_window *mNative;
    int mWidth;
    int mHeight;
    wl_callback *mCallback;


    static void sShellHandlePing(void *data, wl_shell_surface *surface,
        	    uint32_t serial);
    static void sShellHandleConfigure(void *data, wl_shell_surface *surface,
        		 uint32_t edges, int32_t width, int32_t height);
    static void sShellHandlePopup(void *data, wl_shell_surface *surface);

};
}

#endif // _ANDROID_WAYLANDWINDOW_H
