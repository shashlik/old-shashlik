#include "SkTypeface.h"
#include "SkPaintOptionsAndroid.h"

// HACK alert
// returning NULL here is apparently sort of ok, as this is done if there is no font
// fall back implemented. SkAndroidNextLogicalTypeface ends up simply not supporting
// font fallbacks. This can be sorted at some later point.
SkTypeface* SkAndroidNextLogicalTypeface(SkFontID currFontID, SkFontID origFontID,
                                         const SkPaintOptionsAndroid& options) {
    return NULL;
}
