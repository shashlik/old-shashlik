/********************************************************************
Copyright 2014, 2015  Martin Gräßlin <mgraesslin@kde.org>

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) version 3, or any
later version accepted by the membership of KDE e.V. (or its
successor approved by the membership of KDE e.V.), which shall
act as a proxy defined in Section 6 of version 3 of the license.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/
#ifndef WAYLANDCLIENT_H
#define WAYLANDCLIENT_H

#define QT_NO_KEYWORDS

// #include <QObject>
#include <stdio.h>
#include <assert.h>

#include <utils/Singleton.h>

// #include <EGL/egl.h>
// #include <EGL/eglplatform.h>
#include <epoxy/egl.h>
#include <wayland-client.h>
#include <wayland-egl.h>
#include <wayland-cursor.h>

namespace android {

class WaylandClient : public Singleton<WaylandClient>
{
public:
    WaylandClient (WaylandClient &) { assert(0); }
    WaylandClient & operator = (const WaylandClient &) { assert(0); }
    WaylandClient();
//     static WaylandClient *getInstance();
    void connect();
    void disconnect();
//     WaylandWindow* createWindow(int width, int height);
    wl_compositor* getCompositor();
    wl_shell* getShell();
    wl_display* getDisplay();
    wl_event_queue* getEventQueue();
    const char* EGLErrorString(EGLint nErr) const;
    wl_shm* getShm();
private:
    wl_event_queue *mEventQueue;
//     static WaylandClient *sInstance;
	wl_display *mDisplay;
	wl_registry *mRegistry;
	wl_compositor *mCompositor;
	wl_seat *mSeat;
	wl_pointer *mPointer;
	wl_touch *mTouch;
	wl_keyboard *mKeyboard;
    wl_shell *mShell;
	wl_shm *mShm;
	wl_cursor_theme *mCursorTheme;
	wl_cursor *mDefaultCursor;

    static wl_registry_listener mRegistryListener;
    static wl_seat_listener mSeatListener;
    static wl_pointer_listener mPointerListener;
    static wl_keyboard_listener mKeyboardListener;
    static wl_touch_listener mTouchListener;




	static void sHandleRegistry(void * data, wl_registry *registry,
		       uint32_t name, const char *interface, uint32_t version);
	static void sHandleRegistryRemove(void * data, wl_registry *registry,
		       uint32_t name);

    static void sSeatHandleCapabilities(void *data, wl_seat *seat, uint32_t caps);

    static void sPointerHandleEnter(void *data, wl_pointer *pointer,
    		     uint32_t serial, wl_surface *surface,
    		     wl_fixed_t sx, wl_fixed_t sy);
    static void sPointerHandleLeave(void *data, wl_pointer *pointer,
    		     uint32_t serial, wl_surface *surface);
    static void sPointerHandleMotion(void *data, wl_pointer *pointer,
    		      uint32_t time, wl_fixed_t sx, wl_fixed_t sy);
    static void sPointerHandleButton(void *data, wl_pointer *pointer,
    		      uint32_t serial, uint32_t time, uint32_t button,
    		      uint32_t state);
    static void sPointerHandleAxis(void *data, wl_pointer *pointer,
    		    uint32_t time, uint32_t axis, wl_fixed_t value);

    static void sKeyboardHandleKeymap(void *data, wl_keyboard *keyboard,
                                     		       uint32_t format, int fd, uint32_t size);
    static void sKeyboardHandleEnter(void *data, wl_keyboard *keyboard,
    		      uint32_t serial, wl_surface *surface, wl_array *keys);
    static void sKeyboardHandleLeave(void *data, wl_keyboard *keyboard,
    		      uint32_t serial, wl_surface *surface);
    static void sKeyboardHandleKey(void *data, wl_keyboard *keyboard,
    		    uint32_t serial, uint32_t time, uint32_t key,
    		    uint32_t state);
    static void sKeyboardHandleModifiers(void *data, wl_keyboard *keyboard,
    			  uint32_t serial, uint32_t mods_depressed,
    			  uint32_t mods_latched, uint32_t mods_locked,
    			  uint32_t group);

    static void sTouchHandleDown(void *data, wl_touch *touch,
    		  uint32_t serial, uint32_t time, wl_surface *surface,
    		  int32_t id, wl_fixed_t x_w, wl_fixed_t y_w);
    static void sTouchHandleUp(void *data, wl_touch *touch,
    		uint32_t serial, uint32_t time, int32_t id);
    static void sTouchHandleMotion(void *data, wl_touch *touch,
    		    uint32_t time, int32_t id, wl_fixed_t x_w, wl_fixed_t y_w);
    static void sTouchHandleFrame(void *data, wl_touch *touch);
    static void sTouchHandleCancel(void *data, wl_touch *touch);

    void handleRegistry(wl_registry *registry,
    		       uint32_t name, const char *interface, uint32_t version);
    void handleRegistryRemove(wl_registry *registry, uint32_t name);
    void seatHandleCapabilities(wl_seat *seat, enum wl_seat_capability caps);
};

}

// #include <Client/buffer.h>

// struct wl_display;
// struct wl_egl_window;
// struct wl_shm;
// struct wl_surface;
// struct wl_shell_surface;
// class QImage;

// namespace KWayland
// {
// namespace Client
// {
// class Compositor;
// class ConnectionThread;
// class EventQueue;
// class Output;
// class Registry;
// class ShmPool;
// class Surface;
// class ShellSurface;
// }
// }

// class QThread;
// 
// class WaylandClient : public QObject
// {
//     Q_OBJECT
// public:
//     explicit WaylandClient(QObject *parent = 0);
//     virtual ~WaylandClient();
// 
//     const char* EGLErrorString(EGLint nErr) const;
// 
//     // Wait for a display to be connected, and for us to have gotten a shell surface
//     // You don't need to explicitly call this function, as it is called elsewhere,
//     // but even then, i like the verbosity of it, so... public :)
//     void waitForReady();
//     wl_display* display();
//     wl_surface* surface();
//     wl_shell_surface* shellSurface();
//     bool hasShellSurface() const;
//     EGLSurface getSurface(EGLDisplay display, EGLConfig config, int w, int h);
//     wl_shm* getShm();
//     QSharedPointer<KWayland::Client::Buffer> getBuffer(const QImage &image);
// 
// private:
//     Q_SLOT void displayConnected();
//     Q_SLOT void processEvents();
//     Q_SLOT void render();
//     int m_width; int m_height;
//     bool m_displayConnected;
//     void init();
//     void setupRegistry(KWayland::Client::Registry *registry);
//     QThread *m_connectionThread;
//     KWayland::Client::ConnectionThread *m_connectionThreadObject;
//     KWayland::Client::EventQueue *m_eventQueue;
//     KWayland::Client::Compositor *m_compositor;
//     KWayland::Client::Output *m_output;
//     KWayland::Client::Surface *m_surface;
//     KWayland::Client::ShmPool *m_shm;
//     KWayland::Client::ShellSurface *m_shellSurface;
//     EGLSurface m_derpySurface;
//     wl_egl_window* m_derpyWindow;
// };

#endif
