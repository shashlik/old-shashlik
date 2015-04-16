// hacky hack time - api change means skia doesn't compile without a non-forced-ErrorCode close gif function
#ifndef GIF_LIB_HACK
#define GIF_LIB_HACK

#include <../include/gif_lib.h>

int DGifCloseFile(GifFileType * GifFile);

#endif
