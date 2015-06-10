#include <unistd.h>
#include <sys/syscall.h>
#ifdef HAS_SPECIAL_INCLUDE_DIRS
#include <i386-linux-gnu/sys/types.h>
#else
#include <../include/sys/types.h>
#endif
#include <signal.h>

#define gettid() syscall(SYS_gettid)
