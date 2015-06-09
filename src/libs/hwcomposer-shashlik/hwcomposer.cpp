
#include <QCoreApplication>

#include "hwcomposer.h"

namespace android {
namespace shashlik {

Hwcomposer* Hwcomposer::sInstance(0);

Hwcomposer::Hwcomposer()
    : mProcs(0)
    , mInitialized(false)
    , mWindow(0)
{
    CTRACE();

    // create display device
    // that is, just create the window we'll be painting on...
    mWindow = new QWindow();
    mWindow->setSurfaceType(QSurface::OpenGLSurface);
    mWindow->resize(640, 480);
    mWindow->show();
    QCoreApplication::processEvents();
}

Hwcomposer::~Hwcomposer()
{
    CTRACE();
    deinitialize();
}

bool Hwcomposer::initCheck() const
{
    return mInitialized;
}

bool Hwcomposer::prepare(size_t numDisplays,
                          hwc_display_contents_1_t** displays)
{
    bool ret = true;

    RETURN_FALSE_IF_NOT_INIT();
    ALOGTRACE("display count = %d", numDisplays);

    if (!numDisplays || !displays) {
        ELOGTRACE("invalid parameters");
//         return false;
    }

//     ret = device->prepare(displays[i]);
    if (ret == false) {
        ELOGTRACE("failed to do prepare for device %d", 0);
    }

    return ret;
}

bool Hwcomposer::commit(size_t numDisplays,
                         hwc_display_contents_1_t **displays)
{
    bool ret = true;

    RETURN_FALSE_IF_NOT_INIT();
    ALOGTRACE("display count = %d", numDisplays);

    if (!numDisplays || !displays) {
        ELOGTRACE("invalid parameters");
//         return false;
    }

//     mDisplayContext->commitBegin(numDisplays, displays);

//     ret = device->commit(displays[i], mDisplayContext);
//     if (ret == false) {
//         ELOGTRACE("failed to do commit for device %d", i);
//         continue;
//     }

//     mDisplayContext->commitEnd(numDisplays, displays);
    // return true always
    return true;
}

bool Hwcomposer::vsyncControl(int disp, int enabled)
{
    RETURN_FALSE_IF_NOT_INIT();
    ALOGTRACE("disp = %d, enabled = %d", disp, enabled);

    if (disp != 0) {
        ELOGTRACE("invalid disp %d", disp);
//         return false;
    }

//     return device->vsyncControl(enabled ? true : false);
    return true;
}

bool Hwcomposer::blank(int disp, int blank)
{
    RETURN_FALSE_IF_NOT_INIT();
    ALOGTRACE("disp = %d, blank = %d", disp, blank);

    // handle one display, lol...
    if (disp != 0) {
        ELOGTRACE("invalid disp %d", disp);
//         return false;
    }

    // if the device isn't created yet, create it
    if(!mInitialized) {
        initialize();
    }

    // blank the device...
    //return device->blank(blank ? true : false);
    return true;
}

bool Hwcomposer::getDisplayConfigs(int disp,
                                      uint32_t *configs,
                                      size_t *numConfigs)
{
    RETURN_FALSE_IF_NOT_INIT();

    if (disp != 0) {
        ELOGTRACE("invalid disp %d", disp);
//         return false;
    }

//     return device->getDisplayConfigs(configs, numConfigs);
    return true;
}

bool Hwcomposer::getDisplayAttributes(int disp,
                                         uint32_t config,
                                         const uint32_t *attributes,
                                         int32_t *values)
{
    RETURN_FALSE_IF_NOT_INIT();

    if (disp != 0) {
        ELOGTRACE("invalid disp %d", disp);
//         return false;
    }

//     return device->getDisplayAttributes(config, attributes, values);
    return true;
}

bool Hwcomposer::compositionComplete(int disp)
{
    RETURN_FALSE_IF_NOT_INIT();

    if (disp != 0) {
        ELOGTRACE("invalid disp %d", disp);
//         return false;
    }

//     mDisplayContext->compositionComplete();

//     return device->compositionComplete();
    return true;
}

bool Hwcomposer::setPowerMode(int disp, int mode)
{
    RETURN_FALSE_IF_NOT_INIT();

    if (disp != 0) {
        ELOGTRACE("invalid disp %d", disp);
//         return false;
    }

//     return device->setPowerMode(mode);
    return true;
}

int Hwcomposer::getActiveConfig(int disp)
{
    RETURN_NULL_IF_NOT_INIT();

    if (disp != 0) {
        ELOGTRACE("invalid disp %d", disp);
        return -1;
    }

//     return device->getActiveConfig();
    return 0;
}

bool Hwcomposer::setActiveConfig(int disp, int index)
{
    RETURN_FALSE_IF_NOT_INIT();

    if (disp != 0) {
        ELOGTRACE("invalid disp %d", disp);
//         return false;
    }

//     return device->setActiveConfig(index);
    return true;
}

bool Hwcomposer::setCursorPositionAsync(int disp, int x, int y)
{
    RETURN_FALSE_IF_NOT_INIT();

    if (disp != HWC_DISPLAY_PRIMARY && disp != HWC_DISPLAY_EXTERNAL) {
        ELOGTRACE("invalid disp %d", disp);
//         return false;
    }

//     return mDisplayContext->setCursorPosition(disp, x, y);
    return true;
}

void Hwcomposer::vsync(int disp, int64_t timestamp)
{
    RETURN_VOID_IF_NOT_INIT();

//     if (mProcs && mProcs->vsync) {
//         VLOGTRACE("report vsync on disp %d, timestamp %llu", disp, timestamp);
//         // workaround to pretend vsync is from primary display
//         // Display will freeze if vsync is from external display.
//         mProcs->vsync(const_cast<hwc_procs_t*>(mProcs), IDisplayDevice::DEVICE_PRIMARY, timestamp);
//     }
}

void Hwcomposer::hotplug(__attribute__((unused))int disp, bool connected)
{
    RETURN_VOID_IF_NOT_INIT();
    // this is not really a thing in shashlik, as we don't have anything that isn't just a window...
}

void Hwcomposer::invalidate()
{
    RETURN_VOID_IF_NOT_INIT();

//     if (mProcs && mProcs->invalidate) {
//         DLOGTRACE("invalidating screen...");
//         mProcs->invalidate(const_cast<hwc_procs_t*>(mProcs));
//     }
}

bool Hwcomposer::release()
{
    RETURN_FALSE_IF_NOT_INIT();

    return true;
}

bool Hwcomposer::dump(char *buff, int buff_len, int * /* cur_len */)
{
    RETURN_FALSE_IF_NOT_INIT();

//     Dump d(buff, buff_len);
// 
//     // dump composer status
//     d.append("Hardware Composer state:");
//     // dump device status
//     for (size_t i= 0; i < mDisplayDevices.size(); i++) {
//         IDisplayDevice *device = mDisplayDevices.itemAt(i);
//         if (device)
//             device->dump(d);
//     }
// 
//     // dump plane manager status
//     if (mPlaneManager)
//         mPlaneManager->dump(d);
// 
//     // dump buffer manager status
//     if (mBufferManager)
//         mBufferManager->dump(d);

    return true;
}

void Hwcomposer::registerProcs(hwc_procs_t const *procs)
{
    CTRACE();

    if (!procs) {
        WLOGTRACE("procs is NULL");
    }
    mProcs = procs;
}

bool Hwcomposer::initialize()
{
    CTRACE();

    // create drm
//     mDrm = new Drm();
//     if (!mDrm || !mDrm->initialize()) {
//         DEINIT_AND_RETURN_FALSE("failed to create DRM");
//     }

    // create buffer manager
//     mBufferManager = createBufferManager();
//     if (!mBufferManager || !mBufferManager->initialize()) {
//         DEINIT_AND_RETURN_FALSE("failed to create buffer manager");
//     }

    // create display plane manager
//     mPlaneManager = createDisplayPlaneManager();
//     if (!mPlaneManager || !mPlaneManager->initialize()) {
//         DEINIT_AND_RETURN_FALSE("failed to create display plane manager");
//     }

//     mDisplayContext = createDisplayContext();
//     if (!mDisplayContext || !mDisplayContext->initialize()) {
//         DEINIT_AND_RETURN_FALSE("failed to create display context");
//     }

//     mUeventObserver = new UeventObserver();
//     if (!mUeventObserver || !mUeventObserver->initialize()) {
//         DEINIT_AND_RETURN_FALSE("failed to initialize uevent observer");
//     }

    // all initialized, starting uevent observer
//     mUeventObserver->start();

    mInitialized = true;
    return true;
}

void Hwcomposer::deinitialize()
{
//     DEINIT_AND_DELETE_OBJ(mDisplayAnalyzer);

//     DEINIT_AND_DELETE_OBJ(mUeventObserver);
    // destroy display devices
    // that is, get rid of the window...

//     DEINIT_AND_DELETE_OBJ(mDisplayContext);
//     DEINIT_AND_DELETE_OBJ(mPlaneManager);
//     DEINIT_AND_DELETE_OBJ(mBufferManager);
//     DEINIT_AND_DELETE_OBJ(mDrm);
    mWindow->deleteLater();
    mWindow = 0;
    mInitialized = false;
}


Hwcomposer* Hwcomposer::createHwcomposer()
{
    CTRACE();
    return new Hwcomposer();
}

} // shashlik
} // android
