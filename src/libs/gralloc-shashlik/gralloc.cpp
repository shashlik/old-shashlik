
/*
 * Copyright (C) 2008 The Android Open Source Project
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

#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include <cutils/ashmem.h>
#include <cutils/log.h>
#include <cutils/atomic.h>

#include <hardware/hardware.h>
#include <hardware/gralloc.h>

#include <QImage>

#include <wayland-client-protocol.h>

#include "gralloc_priv.h"
#include "gr.h"

#include "WaylandClient.h"

/*****************************************************************************/

struct gralloc_context_t {
    alloc_device_t  device;
    /* our private data here */
};

static int gralloc_alloc_buffer(alloc_device_t* dev,
        size_t size, int usage, buffer_handle_t* pHandle);

/*****************************************************************************/

// SHASHLIK
static int gralloc_setWaylandClient(struct alloc_device_t* dev,
        android::WaylandClient* waylandClient);

// SHASHLIK
static void* gralloc_getWaylandBuffer(struct alloc_device_t* dev,
        buffer_handle_t handle);

extern "C" int os_create_anonymous_file(off_t size);

int fb_device_open(const hw_module_t* module, const char* name,
        hw_device_t** device);

static int gralloc_device_open(const hw_module_t* module, const char* name,
        hw_device_t** device);

extern int gralloc_lock(gralloc_module_t const* module,
        buffer_handle_t handle, int usage,
        int l, int t, int w, int h,
        void** vaddr);

extern int gralloc_unlock(gralloc_module_t const* module, 
        buffer_handle_t handle);

extern int gralloc_register_buffer(gralloc_module_t const* module,
        buffer_handle_t handle);

extern int gralloc_unregister_buffer(gralloc_module_t const* module,
        buffer_handle_t handle);

/*****************************************************************************/

static struct hw_module_methods_t gralloc_module_methods = {
        .open = gralloc_device_open
};

struct private_module_t HAL_MODULE_INFO_SYM = {
    .base = {
        .common = {
            .tag = HARDWARE_MODULE_TAG,
            .version_major = 1,
            .version_minor = 0,
            .id = GRALLOC_HARDWARE_MODULE_ID,
            .name = "Shashlik Graphics Memory Allocator Module for Wayland",
            .author = "The Shashlik Project",
            .methods = &gralloc_module_methods
        },
        .registerBuffer = gralloc_register_buffer,
        .unregisterBuffer = gralloc_unregister_buffer,
        .lock = gralloc_lock,
        .unlock = gralloc_unlock,
    },
    .framebuffer = 0,
    .flags = 0,
    .numBuffers = 0,
    .bufferMask = 0,
    .lock = PTHREAD_MUTEX_INITIALIZER,
    .currentBuffer = 0,
    .waylandClient = 0,
};

// SHASHLIK
static int gralloc_setWaylandClient(struct alloc_device_t* dev, android::WaylandClient* waylandClient) {
    private_module_t* m = reinterpret_cast<private_module_t*>(dev->common.module);
    if (m) {
        m->waylandClient = waylandClient;
    }
    return 0;
}

// SHASHLIK
static void* gralloc_getWaylandBuffer(struct alloc_device_t* dev, buffer_handle_t handle) {
    const private_handle_t* hnd = reinterpret_cast<const private_handle_t*>(handle);
    if (hnd) {
        return hnd->wlBuffer;
    }
    return 0;
}

/*****************************************************************************/

static int gralloc_alloc_framebuffer_locked(alloc_device_t* dev,
        size_t size, int usage, buffer_handle_t* pHandle)
{
    private_module_t* m = reinterpret_cast<private_module_t*>(
            dev->common.module);

    // allocate the framebuffer
    if (m->framebuffer == NULL) {
        // initialize the framebuffer, the framebuffer is mapped once
        // and forever.
        int err = mapFrameBufferLocked(m);
        if (err < 0) {
            return err;
        }
    }

    const uint32_t bufferMask = m->bufferMask;
    const uint32_t numBuffers = m->numBuffers;
    const size_t bufferSize = m->finfo.line_length * m->info.yres;
    if (numBuffers == 1) {
        // If we have only one buffer, we never use page-flipping. Instead,
        // we return a regular buffer which will be memcpy'ed to the main
        // screen when post is called.
        int newUsage = (usage & ~GRALLOC_USAGE_HW_FB) | GRALLOC_USAGE_HW_2D;
        return gralloc_alloc_buffer(dev, bufferSize, newUsage, pHandle);
    }

    if (bufferMask >= ((1LU<<numBuffers)-1)) {
        // We ran out of buffers.
        return -ENOMEM;
    }

    // create a "fake" handles for it
    intptr_t vaddr = intptr_t(m->framebuffer->base);
    private_handle_t* hnd = new private_handle_t(dup(m->framebuffer->fd), size,
            private_handle_t::PRIV_FLAGS_FRAMEBUFFER, 0, 0);

    // find a free slot
    for (uint32_t i=0 ; i<numBuffers ; i++) {
        if ((bufferMask & (1LU<<i)) == 0) {
            m->bufferMask |= (1LU<<i);
            break;
        }
        vaddr += bufferSize;
    }
    
    hnd->base = vaddr;
    hnd->offset = vaddr - intptr_t(m->framebuffer->base);
    *pHandle = hnd;

    return 0;
}

static int gralloc_alloc_framebuffer(alloc_device_t* dev,
        size_t size, int usage, buffer_handle_t* pHandle)
{
    private_module_t* m = reinterpret_cast<private_module_t*>(
            dev->common.module);
    pthread_mutex_lock(&m->lock);
    int err = gralloc_alloc_framebuffer_locked(dev, size, usage, pHandle);
    pthread_mutex_unlock(&m->lock);
    return err;
}

static int gralloc_alloc_buffer(alloc_device_t* dev,
        size_t size, int /*usage*/, buffer_handle_t* pHandle)
{
    int err = 0;
    int fd = -1;

    size = roundUpToPageSize(size);
    
    fd = ashmem_create_region("gralloc-buffer", size);
    if (fd < 0) {
        ALOGE("couldn't create ashmem (%s)", strerror(-errno));
        err = -errno;
    }

    if (err == 0) {
        private_handle_t* hnd = new private_handle_t(fd, size, 0, 0, 0);
        gralloc_module_t* module = reinterpret_cast<gralloc_module_t*>(
                dev->common.module);
        err = mapBuffer(module, hnd);
        if (err == 0) {
            *pHandle = hnd;
        }
    }
    
    ALOGE_IF(err, "gralloc failed err=%s", strerror(-err));
    
    return err;
}

/*****************************************************************************/

static int gralloc_alloc(alloc_device_t* dev,
        int w, int h, int format, int usage,
        buffer_handle_t* pHandle, int* pStride)
{
    ALOGI("Attempting to allocate a buffer");
    if (!pHandle || !pStride)
        return -EINVAL;

    size_t size, stride;

    int align = 4;
    int bpp = 0;
//     QImage::Format bufferFormat;
    int wlBufferFormat = 0;
    switch (format) {
        case HAL_PIXEL_FORMAT_RGBA_8888:
        case HAL_PIXEL_FORMAT_RGBX_8888:
        case HAL_PIXEL_FORMAT_BGRA_8888:
//             bufferFormat = QImage::Format_ARGB32;
            wlBufferFormat = WL_SHM_FORMAT_ARGB8888;
            bpp = 4;
            break;
        case HAL_PIXEL_FORMAT_RGB_888:
//             bufferFormat = QImage::Format_RGB32;
            wlBufferFormat = WL_SHM_FORMAT_XRGB8888;
            bpp = 3;
            break;
        case HAL_PIXEL_FORMAT_RGB_565:
        case HAL_PIXEL_FORMAT_RAW_SENSOR:
            bpp = 2;
            break;
        default:
            return -EINVAL;
    }
    size_t bpr = (w*bpp + (align-1)) & ~(align-1);
    size = bpr * h;
    stride = bpr / bpp;

    int err = 0;
    if (usage & GRALLOC_USAGE_HW_FB) {
        err = gralloc_alloc_framebuffer(dev, size, usage, pHandle);
        if (err < 0) {
            return err;
        }
        *pStride = stride;
        return 0;
    }
//     else {
//         err = gralloc_alloc_buffer(dev, size, usage, pHandle);
//     }
    
    int fd, size_map;
    uchar *data_map;
 
    size_map = h * stride;
 
    /* Create a sharable buffer */
    fd = os_create_anonymous_file(size_map);
    if (fd < 0) {
        ALOGE("Failed to create shareable buffer with error %d (%s)", -fd, strerror(-fd));
        return 0;
    }
 
    data_map = (uchar*)mmap(NULL, size_map, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data_map == MAP_FAILED) {
        ALOGE("Failed to memory map the buffer");
        close(fd);
        return 0;
    }

    private_module_t* m = reinterpret_cast<private_module_t*>(dev->common.module);
    /* Share it in a wl_buffer */
    struct wl_shm_pool *pool = wl_shm_create_pool(m->waylandClient->getShm(), fd, size_map);
    wl_buffer *buffer = wl_shm_pool_create_buffer(pool, 0, w, h, stride, wlBufferFormat);
//     wl_shm_pool_destroy(pool);
//     close(fd);

//     *data = data_map;
//     *size = size_map;
//     return EGL_TRUE;

//     QImage* image = new QImage(data_map, w, h, stride, bufferFormat);
//     QSharedPointer<KWayland::Client::Buffer> buffer = m->waylandClient->getBuffer(*image);
    if(buffer) {
        ALOGI("Successfully created a buffer at address %p", buffer);
//         buffer->setUsed(true);
        private_handle_t* hnd = new private_handle_t(fd, size, 0, pool, buffer);
        gralloc_module_t* module = reinterpret_cast<gralloc_module_t*>(dev->common.module);
        err = mapBuffer(module, hnd);
        if (err == 0) {
            ALOGI("Successfully mapped the buffer");
            *pHandle = hnd;
        }
    } else {
        ALOGE("Could not create wayland buffer");
    }

    if (err < 0) {
//         buffer->setUsed(false);
        return err;
    }

    *pStride = stride;
    return 0;
}

static int gralloc_free(alloc_device_t* dev,
        buffer_handle_t handle)
{
    if (private_handle_t::validate(handle) < 0)
        return -EINVAL;

    private_handle_t const* hnd = reinterpret_cast<private_handle_t const*>(handle);
    if (hnd->flags & private_handle_t::PRIV_FLAGS_FRAMEBUFFER) {
        // free this buffer
        private_module_t* m = reinterpret_cast<private_module_t*>(
                dev->common.module);
        const size_t bufferSize = m->finfo.line_length * m->info.yres;
        int index = (hnd->base - m->framebuffer->base) / bufferSize;
        m->bufferMask &= ~(1<<index); 
    } else { 
        gralloc_module_t* module = reinterpret_cast<gralloc_module_t*>(
                dev->common.module);
        terminateBuffer(module, const_cast<private_handle_t*>(hnd));
    }

    wl_shm_pool_destroy(hnd->pool);
    close(hnd->fd);
    delete hnd;
    return 0;
}

/*****************************************************************************/

static int gralloc_close(struct hw_device_t *dev)
{
    gralloc_context_t* ctx = reinterpret_cast<gralloc_context_t*>(dev);
    if (ctx) {
        /* TODO: keep a list of all buffer_handle_t created, and free them
         * all here.
         */
        free(ctx);
    }
    return 0;
}

int gralloc_device_open(const hw_module_t* module, const char* name,
        hw_device_t** device)
{
    ALOGE("Opening Shashlik gralloc device");
    int status = -EINVAL;
    if (!strcmp(name, GRALLOC_HARDWARE_GPU0)) {
        gralloc_context_t *dev;
        dev = (gralloc_context_t*)malloc(sizeof(*dev));

        /* initialize our state here */
        memset(dev, 0, sizeof(*dev));

        /* initialize the procs */
        dev->device.common.tag = HARDWARE_DEVICE_TAG;
        dev->device.common.version = 0;
        dev->device.common.module = const_cast<hw_module_t*>(module);
        dev->device.common.close = gralloc_close;

        dev->device.alloc   = gralloc_alloc;
        dev->device.free    = gralloc_free;
        dev->device.setWaylandClient = gralloc_setWaylandClient;
        dev->device.getWaylandBuffer = gralloc_getWaylandBuffer;

        *device = &dev->device.common;
        status = 0;
    } else {
        status = fb_device_open(module, name, device);
    }
    return status;
}
