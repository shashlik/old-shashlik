// hackety-hack
#include "gif_lib.h"

int DGifCloseFile(GifFileType * GifFile) {
    int ErrorCode = 0;
    return DGifCloseFile(GifFile, &ErrorCode);
}
