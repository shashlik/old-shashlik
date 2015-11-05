#include "WaylandClient.h"

#include <wayland-egl.h>

// Qt
#include <QCoreApplication>
#include <QImage>
#include <QThread>
#include <QTimer>
#include <QRegion>
#include <QDebug>
// KWin::Wayland
#include <Client/compositor.h>
#include <Client/connection_thread.h>
#include <Client/event_queue.h>
#include <Client/registry.h>
#include <Client/seat.h>
#include <Client/shell.h>
#include <Client/shm_pool.h>
#include <Client/surface.h>

using namespace KWayland::Client;

WaylandClient::WaylandClient(QObject *parent)
    : QObject(parent)
    , m_displayConnected(false)
    , m_connectionThread(new QThread(this))
    , m_connectionThreadObject(new ConnectionThread(nullptr))
    , m_eventQueue(nullptr)
    , m_compositor(nullptr)
    , m_output(nullptr)
    , m_surface(nullptr)
    , m_shm(nullptr)
    , m_shellSurface(nullptr)
    , m_derpySurface(EGL_NO_SURFACE)
    , m_derpyWindow(nullptr)
{
    qDebug() << Q_FUNC_INFO << "in application" << qApp;
    moveToThread(qApp->thread());
    m_connectionThread->moveToThread(qApp->thread());
    QTimer* timer = new QTimer(this);
    timer->moveToThread(qApp->thread());
    timer->setInterval(100);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(processEvents()));
    QTimer::singleShot(0, timer, SLOT(start()));
    connect(m_connectionThreadObject, SIGNAL(connected()), this, SLOT(displayConnected()));
    init();
}

void WaylandClient::processEvents()
{
    qApp->processEvents();
}

WaylandClient::~WaylandClient()
{
    m_connectionThread->quit();
    m_connectionThread->wait();
    m_connectionThreadObject->deleteLater();
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

void WaylandClient::displayConnected()
{
    qDebug() << "WaylandClient connected to display";
    m_displayConnected = true;
}

void WaylandClient::waitForReady()
{
    qDebug() << Q_FUNC_INFO;
    while(!m_displayConnected && !hasShellSurface() && !m_shm) {
        qDebug() << "Waiting for events to be processed so we can get displays connected, find a shell surface and acquire a shared memory manager...";
        qApp->processEvents(QEventLoop::WaitForMoreEvents);
    }
}

wl_display* WaylandClient::display()
{
    qDebug() << "Getting wayland client display";
    waitForReady();
    return m_connectionThreadObject->display();
}

bool WaylandClient::hasShellSurface() const
{
    return m_shellSurface != nullptr;
}

EGLSurface WaylandClient::getSurface(EGLDisplay display, EGLConfig config, int w, int h)
{
    qDebug() << Q_FUNC_INFO;
    waitForReady();
    if(m_derpySurface == EGL_NO_SURFACE) {
        qDebug() << "No surface yet, let's create one";
        m_derpyWindow = wl_egl_window_create(*m_surface, w, h);
        m_derpySurface = eglCreateWindowSurface(display, config, m_derpyWindow, nullptr);
        EGLint error = eglGetError();
        if(m_derpySurface == EGL_NO_SURFACE) {
            qDebug() << "Error creating surface, oh no! The error was" << EGLErrorString(error);
        }
    }
    wl_egl_window_resize(m_derpyWindow, w, h, 0, 0);
    qDebug() << "Returning a window surface of size w*h:" << w << h;
    return m_derpySurface;
}

wl_shm* WaylandClient::getShm()
{
    qDebug() << Q_FUNC_INFO;
    waitForReady();
    return m_shm->shm();
}

QSharedPointer<KWayland::Client::Buffer> WaylandClient::getBuffer(const QImage &image)
{
    qDebug() << Q_FUNC_INFO;
    waitForReady();
    if(m_shm) {
        QSharedPointer<KWayland::Client::Buffer> buffer = m_shm->createBuffer(image).toStrongRef();
        if(buffer) {
            buffer->setUsed(true);
            qDebug() << "Returning a buffer, wooh!" << buffer;
            return buffer;
        }
    }
    qDebug() << "Failed to create a buffer, sadface...";
    return QSharedPointer<KWayland::Client::Buffer>();
}

void WaylandClient::init()
{
    connect(m_connectionThreadObject, &ConnectionThread::connected, this,
        [this]() {
            // create the event queue for the main gui thread
            m_eventQueue = new EventQueue(this);
            m_eventQueue->setup(m_connectionThreadObject);
            // setup registry
            Registry *registry = new Registry(this);
            setupRegistry(registry);
        },
        Qt::QueuedConnection);

    m_connectionThreadObject->moveToThread(m_connectionThread);
    m_connectionThread->start();

    m_connectionThreadObject->initConnection();
    m_connectionThreadObject->flush();
}

void WaylandClient::setupRegistry(Registry *registry)
{
    qDebug() << Q_FUNC_INFO;
    connect(registry, &Registry::compositorAnnounced, this,
        [this, registry](quint32 name) {
            qDebug() << "compositor announced...";
            m_compositor = registry->createCompositor(name, 1, this);
            m_surface = m_compositor->createSurface(this);
        },
        Qt::QueuedConnection
    );
    connect(registry, &Registry::shellAnnounced, this,
        [this, registry](quint32 name) {
            qDebug() << "shell announced...";
            Shell *shell = registry->createShell(name, 1, this);
            m_shellSurface = shell->createSurface(m_surface, m_surface);
            m_shellSurface->setToplevel();
        },
        Qt::QueuedConnection
    );
    connect(registry, &Registry::shmAnnounced, this,
        [this, registry](quint32 name) {
            qDebug() << "shared memory pool announced, we can make buffers now!";
            m_shm = registry->createShmPool(name, 1, this);
        },
        Qt::QueuedConnection
    );
    registry->create(m_connectionThreadObject->display());
    registry->setEventQueue(m_eventQueue);
    registry->setup();
    m_connectionThreadObject->flush();
    qDebug() << "Waiting for events";
    for(int i = 0; i < 1000; ++i) {
        qApp->processEvents();
    }
    qDebug() << "Registry setup completed";
}
