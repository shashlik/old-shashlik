#include <unistd.h>
#include <sys/syscall.h>
#include <../include/sys/types.h>
#include <signal.h>

#define gettid() syscall(SYS_gettid)
