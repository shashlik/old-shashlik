
#include <hardware/hardware.h>
#include <utils/Trace.h>

#include "HwcTrace.h"

#include "hwcomposer.h"

#define GET_HWC_RETURN_X_IF_NULL(X) \
    CTRACE(); \
    Hwcomposer *hwc = static_cast<Hwcomposer*>(dev); \
    do {\
        if (!hwc) { \
            ELOGTRACE("invalid HWC device."); \
            return X; \
        } \
    } while (0)


#define GET_HWC_RETURN_ERROR_IF_NULL()        GET_HWC_RETURN_X_IF_NULL(-EINVAL)
#define GET_HWC_RETURN_VOID_IF_NULL()         GET_HWC_RETURN_X_IF_NULL()

namespace android {
namespace shashlik {


static int hwc_prepare(struct hwc_composer_device_1 *dev,
                          size_t numDisplays,
                          hwc_display_contents_1_t** displays)
{
    ATRACE_CALL();
    GET_HWC_RETURN_ERROR_IF_NULL();
    if (!hwc->prepare(numDisplays, displays)) {
        ELOGTRACE("failed to prepare");
        return -EINVAL;
    }
    return 0;
}

static int hwc_set(struct hwc_composer_device_1 *dev,
                     size_t numDisplays,
                     hwc_display_contents_1_t **displays)
{
    ATRACE_CALL();
    GET_HWC_RETURN_ERROR_IF_NULL();
    if (!hwc->commit(numDisplays, displays)) {
        ELOGTRACE("failed to commit");
        return -EINVAL;
    }
    return 0;
}

static void hwc_dump(struct hwc_composer_device_1 *dev,
                       char *buff,
                       int buff_len)
{
    GET_HWC_RETURN_VOID_IF_NULL();
    hwc->dump(buff, buff_len, 0);
}

void hwc_registerProcs(struct hwc_composer_device_1 *dev,
                          hwc_procs_t const *procs)
{
    GET_HWC_RETURN_VOID_IF_NULL();
    hwc->registerProcs(procs);
}

static int hwc_device_close(struct hw_device_t * /* dev */)
{
    CTRACE();
    Hwcomposer::releaseInstance();
    return 0;
}

static int hwc_query(struct hwc_composer_device_1 * /* dev */,
        int what, int* /* value */)
{
    (void) what;
    ALOGTRACE("what = %d", what);
    return -EINVAL;
}

static int hwc_eventControl(struct hwc_composer_device_1 *dev,
                                int disp,
                                int event,
                                int enabled)
{
    bool ret;
    ATRACE_CALL();
    GET_HWC_RETURN_ERROR_IF_NULL();

    switch (event) {
    case HWC_EVENT_VSYNC:
        ret = hwc->vsyncControl(disp, enabled);
        if (ret == false) {
            ELOGTRACE("failed to control vsync");
            return -EINVAL;
        }
        break;
    default:
        WLOGTRACE("unsupported event %d", event);
        break;
    }

    return 0;
}

static int hwc_getDisplayConfigs(hwc_composer_device_1_t *dev,
                                     int disp,
                                     uint32_t *configs,
                                     size_t *numConfigs)
{
    ATRACE_CALL();
    GET_HWC_RETURN_ERROR_IF_NULL();
    bool ret = hwc->getDisplayConfigs(disp, configs, numConfigs);
    if (ret == false) {
        WLOGTRACE("failed to get configs of disp %d", disp);
        return -EINVAL;
    }

    return 0;
}

static int hwc_getDisplayAttributes(hwc_composer_device_1_t *dev,
                                        int disp,
                                        uint32_t config,
                                        const uint32_t *attributes,
                                        int32_t *values)
{
    ATRACE_CALL();
    GET_HWC_RETURN_ERROR_IF_NULL();
    bool ret = hwc->getDisplayAttributes(disp, config, attributes, values);
    if (ret == false) {
        WLOGTRACE("failed to get attributes of disp %d", disp);
        return -EINVAL;
    }

    return 0;
}

static int hwc_compositionComplete(hwc_composer_device_1_t *dev, int disp)
{
    ATRACE_CALL();
    GET_HWC_RETURN_ERROR_IF_NULL();
    bool ret = hwc->compositionComplete(disp);
    if (ret == false) {
        ELOGTRACE("failed for disp %d", disp);
        return -EINVAL;
    }

    return 0;
}

static int hwc_setPowerMode(hwc_composer_device_1_t *dev, int disp, int mode)
{
    ATRACE_CALL();
    GET_HWC_RETURN_ERROR_IF_NULL();
    bool ret = hwc->setPowerMode(disp, mode);
    if (ret == false) {
        WLOGTRACE("failed to set power mode of disp %d", disp);
        return -EINVAL;
    }

    return 0;
}

static int hwc_getActiveConfig(hwc_composer_device_1_t *dev, int disp)
{
    ATRACE_CALL();
    GET_HWC_RETURN_ERROR_IF_NULL();
    int ret = hwc->getActiveConfig(disp);
    if (ret == -1) {
        WLOGTRACE("failed to get active config of disp %d", disp);
        return -EINVAL;
    }

    return ret;
}

static int hwc_setActiveConfig(hwc_composer_device_1_t *dev, int disp, int index)
{
    ATRACE_CALL();
    GET_HWC_RETURN_ERROR_IF_NULL();
    bool ret = hwc->setActiveConfig(disp, index);
    if (ret == false) {
        WLOGTRACE("failed to set active config of disp %d", disp);
        return -EINVAL;
    }

    return 0;
}


static int hwc_device_open(const struct hw_module_t* module,
                              const char* name,
                              struct hw_device_t** device)
{
    if (!name) {
        ELOGTRACE("invalid name.");
        return -EINVAL;
    }

    ALOGTRACE("open device %s", name);

    if (strcmp(name, HWC_HARDWARE_COMPOSER) != 0) {
        ELOGTRACE("try to open unknown HWComposer %s", name);
        return -EINVAL;
    }

    Hwcomposer& hwc = Hwcomposer::getInstance();
    // initialize our state here
    if (hwc.initialize() == false) {
        ELOGTRACE("failed to intialize HWComposer");
        Hwcomposer::releaseInstance();
        return -EINVAL;
    }

    // initialize the procs
    hwc.hwc_composer_device_1_t::common.tag = HARDWARE_DEVICE_TAG;
    hwc.hwc_composer_device_1_t::common.module =
        const_cast<hw_module_t*>(module);
    hwc.hwc_composer_device_1_t::common.close = hwc_device_close;

    hwc.hwc_composer_device_1_t::prepare = hwc_prepare;
    hwc.hwc_composer_device_1_t::set = hwc_set;
    hwc.hwc_composer_device_1_t::dump = hwc_dump;
    hwc.hwc_composer_device_1_t::registerProcs = hwc_registerProcs;
    hwc.hwc_composer_device_1_t::query = hwc_query;

    hwc.hwc_composer_device_1_t::eventControl = hwc_eventControl;
    hwc.hwc_composer_device_1_t::getDisplayConfigs = hwc_getDisplayConfigs;
    hwc.hwc_composer_device_1_t::getDisplayAttributes = hwc_getDisplayAttributes;

    // This is used to hack FBO switch flush issue in SurfaceFlinger.
    hwc.hwc_composer_device_1_t::reserved_proc[0] = (void*)hwc_compositionComplete;
    hwc.hwc_composer_device_1_t::common.version = HWC_DEVICE_API_VERSION_1_4;
    hwc.hwc_composer_device_1_t::setPowerMode = hwc_setPowerMode;
    hwc.hwc_composer_device_1_t::getActiveConfig = hwc_getActiveConfig;
    hwc.hwc_composer_device_1_t::setActiveConfig = hwc_setActiveConfig;
    // Todo: add hwc_setCursorPositionAsync after supporting patches
    hwc.hwc_composer_device_1_t::setCursorPositionAsync = NULL;

    *device = &hwc.hwc_composer_device_1_t::common;

    return 0;
}

} // shashlik
} // android

static struct hw_module_methods_t hwc_module_methods = {
    open: android::shashlik::hwc_device_open
};

hwc_module_t HAL_MODULE_INFO_SYM = {
    common: {
        tag: HARDWARE_MODULE_TAG,
        version_major: 1,
        version_minor: 4,
        id: HWC_HARDWARE_MODULE_ID,
        name: "Shashlik Hardware Composer",
        author: "KDE e.V.",
        methods: &hwc_module_methods,
        dso: 0,
        reserved: { 0 },
    }
};
