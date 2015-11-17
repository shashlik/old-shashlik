#include "WaylandClient.h"

#define LOG_TAG "shashlik/WaylandClient"

#include <string.h>
#include <signal.h>
#include <utils/Log.h>


namespace android {

ANDROID_SINGLETON_STATIC_INSTANCE(WaylandClient);
// WaylandClient *WaylandClient::sInstance = NULL;

wl_registry_listener WaylandClient::mRegistryListener = {
    WaylandClient::sHandleRegistry,
    WaylandClient::sHandleRegistryRemove };

wl_seat_listener WaylandClient::mSeatListener = {
    WaylandClient::sSeatHandleCapabilities };

wl_pointer_listener WaylandClient::mPointerListener = {
    WaylandClient::sPointerHandleEnter,
    WaylandClient::sPointerHandleLeave,
    WaylandClient::sPointerHandleMotion,
    WaylandClient::sPointerHandleButton,
    WaylandClient::sPointerHandleAxis };

wl_keyboard_listener WaylandClient::mKeyboardListener = {
    WaylandClient::sKeyboardHandleKeymap,
    WaylandClient::sKeyboardHandleEnter,
    WaylandClient::sKeyboardHandleLeave,
    WaylandClient::sKeyboardHandleKey,
    WaylandClient::sKeyboardHandleModifiers };

wl_touch_listener WaylandClient::mTouchListener = {
	WaylandClient::sTouchHandleDown,
	WaylandClient::sTouchHandleUp,
	WaylandClient::sTouchHandleMotion,
	WaylandClient::sTouchHandleFrame,
	WaylandClient::sTouchHandleCancel,
};


WaylandClient::WaylandClient() : mDisplay(NULL), mRegistry(NULL),
        mCompositor(NULL), mSeat(NULL), mPointer(NULL), mTouch(NULL),
        mKeyboard(NULL), mShell(NULL), mShm(NULL), mCursorTheme(NULL),
        mDefaultCursor(NULL)
{
}


// WaylandClient *WaylandClient::getInstance()
// {
//     if (sInstance == NULL ) {
//         sInstance = new WaylandClient();
//     }
// 
//     return sInstance;
// }

wl_compositor* WaylandClient::getCompositor()
{
    if (mDisplay == NULL)
        ALOGW("WaylandClient not connected\n");

    return mCompositor;
}

wl_shell* WaylandClient::getShell()
{
    if (mDisplay == NULL)
        ALOGW("WaylandClient not connected\n");

    return mShell;
}

wl_display* WaylandClient::getDisplay()
{
    if (mDisplay == NULL)
        ALOGW("WaylandClient not connected\n");

    return mDisplay;
}

wl_event_queue* WaylandClient::getEventQueue()
{
    if (mDisplay == NULL)
        ALOGW("WaylandClient not connected\n");

    return mEventQueue;
}

wl_shm* WaylandClient::getShm()
{
    if (mDisplay == NULL)
        ALOGW("WaylandClient not connected\n");

    return mShm;
}

void WaylandClient::connect()
{
    struct sigaction sigint;
    assert(mDisplay == NULL);
	mDisplay = wl_display_connect(NULL);
	if (mDisplay == NULL) {
	    ALOGW("wl_display_connect FAILED\n");
	    return;
	}

	mRegistry = wl_display_get_registry(mDisplay);

	wl_registry_add_listener(mRegistry,
				 &mRegistryListener, this);
	wl_display_dispatch(mDisplay);
	mEventQueue = wl_display_create_queue(mDisplay);
}

void WaylandClient::disconnect()
{
	if (mCursorTheme)
		wl_cursor_theme_destroy(mCursorTheme);

	if (mCompositor)
		wl_compositor_destroy(mCompositor);

	wl_registry_destroy(mRegistry);
	wl_display_flush(mDisplay);
	wl_display_disconnect(mDisplay);
	wl_event_queue_destroy(mEventQueue);
	mDisplay = NULL;
}

void WaylandClient::sTouchHandleDown(void *data, wl_touch *touch,
		  uint32_t serial, uint32_t time, wl_surface *surface,
		  int32_t id, wl_fixed_t x_w, wl_fixed_t y_w)
{
}

void WaylandClient::sTouchHandleUp(void *data, wl_touch *touch,
		uint32_t serial, uint32_t time, int32_t id)
{
}

void WaylandClient::sTouchHandleMotion(void *data, wl_touch *touch,
		    uint32_t time, int32_t id, wl_fixed_t x_w, wl_fixed_t y_w)
{
}

void WaylandClient::sTouchHandleFrame(void *data, wl_touch *touch)
{
}

void WaylandClient::sTouchHandleCancel(void *data, wl_touch *touch)
{
}


void WaylandClient::sKeyboardHandleKeymap(void *data, wl_keyboard *keyboard,
		       uint32_t format, int fd, uint32_t size)
{
}


void WaylandClient::sKeyboardHandleEnter(void *data, wl_keyboard *keyboard,
		      uint32_t serial, wl_surface *surface, wl_array *keys)
{
}

void WaylandClient::sKeyboardHandleLeave(void *data, wl_keyboard *keyboard,
		      uint32_t serial, wl_surface *surface)
{
}

void WaylandClient::sKeyboardHandleKey(void *data, wl_keyboard *keyboard,
		    uint32_t serial, uint32_t time, uint32_t key,
		    uint32_t state)
{
}

void WaylandClient::sKeyboardHandleModifiers(void *data, wl_keyboard *keyboard,
			  uint32_t serial, uint32_t mods_depressed,
			  uint32_t mods_latched, uint32_t mods_locked,
			  uint32_t group)
{
}


void WaylandClient::sHandleRegistry(void * data, wl_registry *registry,
		       uint32_t name, const char *interface, uint32_t version)
{
    WaylandClient *client = reinterpret_cast<WaylandClient*>(data);
    client->handleRegistry(registry, name, interface, version);
}



void WaylandClient::sSeatHandleCapabilities(void *data, wl_seat *seat,
			 uint32_t caps)
{
    WaylandClient *client = reinterpret_cast<WaylandClient*>(data);
    client->seatHandleCapabilities(seat, (wl_seat_capability)caps);
}

void WaylandClient::seatHandleCapabilities(wl_seat *seat,
			 enum wl_seat_capability caps)
{
	if ((caps & WL_SEAT_CAPABILITY_POINTER) && !mPointer) {
		mPointer = wl_seat_get_pointer(mSeat);
		wl_pointer_add_listener(mPointer, &mPointerListener, this);
	} else if (!(caps & WL_SEAT_CAPABILITY_POINTER) && mPointer) {
		wl_pointer_destroy(mPointer);
		mPointer = NULL;
	}

	if ((caps & WL_SEAT_CAPABILITY_KEYBOARD) && !mKeyboard) {
		mKeyboard = wl_seat_get_keyboard(mSeat);
		wl_keyboard_add_listener(mKeyboard, &mKeyboardListener, this);
	} else if (!(caps & WL_SEAT_CAPABILITY_KEYBOARD) && mKeyboard) {
		wl_keyboard_destroy(mKeyboard);
		mKeyboard = NULL;
	}

	if ((caps & WL_SEAT_CAPABILITY_TOUCH) && !mTouch) {
		mTouch = wl_seat_get_touch(mSeat);
		wl_touch_set_user_data(mTouch, this);
		wl_touch_add_listener(mTouch, &mTouchListener, this);
	} else if (!(caps & WL_SEAT_CAPABILITY_TOUCH) && mTouch) {
		wl_touch_destroy(mTouch);
		mTouch = NULL;
	}
}

void WaylandClient::sHandleRegistryRemove(void * data, wl_registry *registry,
		       uint32_t name)
{
    WaylandClient *client = reinterpret_cast<WaylandClient*>(data);
    client->handleRegistryRemove(registry, name);
}

void WaylandClient::handleRegistry(wl_registry *registry,
		       uint32_t name, const char *interface, uint32_t version)
{

	if (strcmp(interface, "wl_compositor") == 0) {
		mCompositor = (wl_compositor*)wl_registry_bind(registry, name,
					 &wl_compositor_interface, 1);
	} else if (strcmp(interface, "wl_seat") == 0) {
		mSeat = (wl_seat*)wl_registry_bind(registry, name,
					   &wl_seat_interface, 1);
		wl_seat_add_listener(mSeat, &mSeatListener, this);
	} else if (strcmp(interface, "wl_shell") == 0) {
      	mShell = (wl_shell*)wl_registry_bind(registry, name,
      					 &wl_shell_interface, 1);
    } else if (strcmp(interface, "wl_shm") == 0) {
		mShm = (wl_shm*)wl_registry_bind(registry, name,
					  &wl_shm_interface, 1);
		mCursorTheme = wl_cursor_theme_load(NULL, 32, mShm);
		if (!mCursorTheme) {
			fprintf(stderr, "unable to load default theme\n");
			return;
		}
		mDefaultCursor =
			wl_cursor_theme_get_cursor(mCursorTheme, "left_ptr");
		if (!mDefaultCursor) {
			fprintf(stderr, "unable to load default left pointer\n");
			// TODO: abort ?
		}
	}

}

void WaylandClient::handleRegistryRemove(wl_registry *registry,
			      uint32_t name)
{
}

void WaylandClient::sPointerHandleEnter(void *data, wl_pointer *pointer,
		     uint32_t serial, wl_surface *surface,
		     wl_fixed_t sx, wl_fixed_t sy)
{
}

void WaylandClient::sPointerHandleLeave(void *data, wl_pointer *pointer,
		     uint32_t serial, wl_surface *surface)
{
}

void WaylandClient::sPointerHandleMotion(void *data, wl_pointer *pointer,
		      uint32_t time, wl_fixed_t sx, wl_fixed_t sy)
{
}

void WaylandClient::sPointerHandleButton(void *data, wl_pointer *wl_pointer,
		      uint32_t serial, uint32_t time, uint32_t button,
		      uint32_t state)
{
}

void WaylandClient::sPointerHandleAxis(void *data, wl_pointer *wl_pointer,
		    uint32_t time, uint32_t axis, wl_fixed_t value)
{
}

const char* WaylandClient::EGLErrorString(EGLint nErr) const {
    switch(nErr){
        case EGL_SUCCESS:               return "EGL_SUCCESS";
        case EGL_BAD_DISPLAY:           return "EGL_BAD_DISPLAY";
        case EGL_NOT_INITIALIZED:       return "EGL_NOT_INITIALIZED";
        case EGL_BAD_ACCESS:            return "EGL_BAD_ACCESS";
        case EGL_BAD_ALLOC:             return "EGL_BAD_ALLOC";
        case EGL_BAD_ATTRIBUTE:         return "EGL_BAD_ATTRIBUTE";
        case EGL_BAD_CONFIG:            return "EGL_BAD_CONFIG";
        case EGL_BAD_CONTEXT:           return "EGL_BAD_CONTEXT";
        case EGL_BAD_CURRENT_SURFACE:   return "EGL_BAD_CURRENT_SURFACE";
        case EGL_BAD_MATCH:             return "EGL_BAD_MATCH";
        case EGL_BAD_NATIVE_PIXMAP:     return "EGL_BAD_NATIVE_PIXMAP";
        case EGL_BAD_NATIVE_WINDOW:     return "EGL_BAD_NATIVE_WINDOW";
        case EGL_BAD_PARAMETER:         return "EGL_BAD_PARAMETER";
        case EGL_BAD_SURFACE:           return "EGL_BAD_SURFACE";
        default:                        return "unknown";
    }
}
}

// 
// #include <wayland-egl.h>
// 
// // Qt
// #include <QCoreApplication>
// #include <QImage>
// #include <QThread>
// #include <QTimer>
// #include <QRegion>
// #include <QDebug>
// // KWin::Wayland
// #include <Client/compositor.h>
// #include <Client/connection_thread.h>
// #include <Client/event_queue.h>
// #include <Client/registry.h>
// #include <Client/seat.h>
// #include <Client/shell.h>
// #include <Client/shm_pool.h>
// #include <Client/surface.h>
// 
// using namespace KWayland::Client;
// 
// WaylandClient::WaylandClient(QObject *parent)
//     : QObject(parent)
//     , m_width(0)
//     , m_height(0)
//     , m_displayConnected(false)
//     , m_connectionThread(nullptr)
//     , m_connectionThreadObject(new ConnectionThread(nullptr))
//     , m_eventQueue(nullptr)
//     , m_compositor(nullptr)
//     , m_output(nullptr)
//     , m_surface(nullptr)
//     , m_shm(nullptr)
//     , m_shellSurface(nullptr)
//     , m_derpySurface(EGL_NO_SURFACE)
//     , m_derpyWindow(nullptr)
// {
//     qDebug() << Q_FUNC_INFO << "in application" << qApp;
//     m_connectionThread = new QThread(this);
//     moveToThread(qApp->thread());
//     m_connectionThread->moveToThread(qApp->thread());
//     QTimer* timer = new QTimer(this);
//     timer->moveToThread(qApp->thread());
//     timer->setInterval(100);
//     timer->setSingleShot(false);
//     connect(timer, SIGNAL(timeout()), this, SLOT(processEvents()));
//     QTimer::singleShot(0, timer, SLOT(start()));
//     connect(m_connectionThreadObject, SIGNAL(connected()), this, SLOT(displayConnected()));
//     init();
// }
// 
// void WaylandClient::processEvents()
// {
//     qApp->processEvents();
// }
// 
// WaylandClient::~WaylandClient()
// {
//     m_connectionThread->quit();
//     m_connectionThread->wait();
//     m_connectionThreadObject->deleteLater();
// }
// 
// 
// void WaylandClient::displayConnected()
// {
//     qDebug() << "WaylandClient connected to display";
//     m_displayConnected = true;
// }
// 
// void WaylandClient::waitForReady()
// {
//     qDebug() << Q_FUNC_INFO;
//     int i = 0;
//     while(!m_displayConnected && !hasShellSurface() && !m_shm && !m_surface) {
//         qApp->processEvents(QEventLoop::WaitForMoreEvents);
// //         qApp->processEvents();
//         if(i++ == 100000) {
//             qDebug() << "Waiting for even more events to be processed so we can get displays connected, find a shell surface and acquire a shared memory manager...";
//             i = 0;
//         }
//     }
// }
// 
// wl_display* WaylandClient::display()
// {
//     qDebug() << "Getting wayland client display";
//     waitForReady();
//     return m_connectionThreadObject->display();
// }
// 
// wl_surface* WaylandClient::surface()
// {
//     qDebug() << "Getting wayland surface";
//     waitForReady();
//     return m_surface->operator wl_surface*();
// }
// 
// wl_shell_surface* WaylandClient::shellSurface()
// {
//     qDebug() << "Getting wayland shell surface";
//     waitForReady();
//     return m_shellSurface->operator wl_shell_surface*();
// }
// 
// bool WaylandClient::hasShellSurface() const
// {
//     return m_shellSurface != nullptr;
// }
// 
// EGLSurface WaylandClient::getSurface(EGLDisplay display, EGLConfig config, int w, int h)
// {
//     qDebug() << Q_FUNC_INFO;
//     waitForReady();
//     m_width = w, m_height = h;
//     if(m_derpySurface == EGL_NO_SURFACE) {
//         qDebug() << "No surface yet, let's create one";
//         m_derpyWindow = wl_egl_window_create(*m_surface, w, h);
//         m_derpySurface = eglCreateWindowSurface(display, config, m_derpyWindow, nullptr);
//         EGLint error = eglGetError();
//         if(m_derpySurface == EGL_NO_SURFACE) {
//             qDebug() << "Error creating surface, oh no! The error was" << EGLErrorString(error);
//         }
//     } else {
//         wl_egl_window_resize(m_derpyWindow, w, h, 0, 0);
//         eglSurfaceAttrib(display, m_derpySurface, EGL_WIDTH, w);
//         eglSurfaceAttrib(display, m_derpySurface, EGL_HEIGHT, h);
//     }
//     qDebug() << "Returning a window surface of size w*h:" << w << h;
//     return m_derpySurface;
// }
// 
// wl_shm* WaylandClient::getShm()
// {
//     qDebug() << Q_FUNC_INFO;
//     waitForReady();
//     return m_shm->shm();
// }
// 
// QSharedPointer<KWayland::Client::Buffer> WaylandClient::getBuffer(const QImage &image)
// {
//     qDebug() << Q_FUNC_INFO;
//     waitForReady();
//     if(m_shm) {
//         QSharedPointer<KWayland::Client::Buffer> buffer = m_shm->createBuffer(image).toStrongRef();
//         if(buffer) {
//             buffer->setUsed(true);
//             qDebug() << "Returning a buffer, wooh!" << buffer;
//             return buffer;
//         }
//     }
//     qDebug() << "Failed to create a buffer, sadface...";
//     return QSharedPointer<KWayland::Client::Buffer>();
// }
// 
// void WaylandClient::init()
// {
//     connect(m_connectionThreadObject, &ConnectionThread::connected, this,
//         [this]() {
//             // create the event queue for the main gui thread
//             m_eventQueue = new EventQueue(this);
//             m_eventQueue->setup(m_connectionThreadObject);
//             // setup registry
//             Registry *registry = new Registry(this);
//             setupRegistry(registry);
//         },
//         Qt::QueuedConnection);
// 
//     m_connectionThreadObject->moveToThread(m_connectionThread);
//     m_connectionThread->start();
// 
//     m_connectionThreadObject->initConnection();
//     m_connectionThreadObject->flush();
//     qDebug() << "Waiting for events";
//     for(int i = 0; i < 1000; ++i) {
//         qApp->processEvents();
//     }
//     qDebug() << "init completed";
// }
// 
// void WaylandClient::setupRegistry(Registry *registry)
// {
//     qDebug() << Q_FUNC_INFO;
//     connect(registry, &Registry::compositorAnnounced, this,
//         [this, registry](quint32 name) {
//             qDebug() << "compositor announced...";
//             m_compositor = registry->createCompositor(name, 1, this);
//             m_surface = m_compositor->createSurface(this);
//         },
//         Qt::QueuedConnection
//     );
//     connect(registry, &Registry::shellAnnounced, this,
//         [this, registry](quint32 name) {
//             qDebug() << "shell announced...";
//             Shell *shell = registry->createShell(name, 1, this);
//             m_shellSurface = shell->createSurface(m_surface, m_surface);
//             m_shellSurface->setToplevel();
//         },
//         Qt::QueuedConnection
//     );
//     connect(registry, &Registry::shmAnnounced, this,
//         [this, registry](quint32 name) {
//             qDebug() << "shared memory pool announced, we can make buffers now!";
//             m_shm = registry->createShmPool(name, 1, this);
//         },
//         Qt::QueuedConnection
//     );
//     registry->create(m_connectionThreadObject->display());
//     registry->setEventQueue(m_eventQueue);
//     registry->setup();
//     m_connectionThreadObject->flush();
//     qDebug() << "Waiting for events";
//     for(int i = 0; i < 1000; ++i) {
//         qApp->processEvents();
//     }
//     qDebug() << "Registry setup completed";
// }
// 
// void WaylandClient::render()
// {
//     if(m_surface) {
// //     m_surface->attachBuffer(*buffer);
//         m_surface->damage(QRect(QPoint(0, 0), QSize(m_width, m_height)));
//         m_surface->commit(Surface::CommitFlag::None);
//     }
// }
