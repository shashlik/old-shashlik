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

#include <QObject>
#include <EGL/egl.h>

struct wl_display;
struct wl_egl_window;

namespace KWayland
{
namespace Client
{
class Compositor;
class ConnectionThread;
class EventQueue;
class Output;
class Registry;
class ShmPool;
class Surface;
class ShellSurface;
}
}

class QThread;

class WaylandClient : public QObject
{
    Q_OBJECT
public:
    explicit WaylandClient(QObject *parent = 0);
    virtual ~WaylandClient();

    wl_display* display();
    bool hasShellSurface() const;
    EGLSurface getSurface(EGLDisplay display, EGLConfig config, int w, int h);

private:
    void init();
    void setupRegistry(KWayland::Client::Registry *registry);
    QThread *m_connectionThread;
    KWayland::Client::ConnectionThread *m_connectionThreadObject;
    KWayland::Client::EventQueue *m_eventQueue;
    KWayland::Client::Compositor *m_compositor;
    KWayland::Client::Output *m_output;
    KWayland::Client::Surface *m_surface;
    KWayland::Client::ShmPool *m_shm;
    KWayland::Client::ShellSurface *m_shellSurface;
    EGLSurface m_derpySurface;
    wl_egl_window* m_derpyWindow;
};

#endif
