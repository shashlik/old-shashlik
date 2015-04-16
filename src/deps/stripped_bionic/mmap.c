// Taken from bionic/libc/bionic/mmap.cpp and __set_errno.cpp

#include <errno.h>
#include <unistd.h>

// This function is called from our assembler syscall stubs.
// C/C++ code should just assign 'errno' instead.

// TODO: this should be __LIBC_HIDDEN__ but was exposed in <errno.h> in the NDK.
int __set_errno(int n) {
  errno = n;
  return -1;
}

// mmap2(2) is like mmap(2), but the offset is in 4096-byte blocks, not bytes.
void*  __mmap2(void*, size_t, int, int, int, size_t);

#define MMAP2_SHIFT 12 // 2**12 == 4096
