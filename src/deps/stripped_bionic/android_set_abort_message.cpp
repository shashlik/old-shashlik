#include "android/set_abort_message.h"
#include "libc_logging.h"
#include "ScopedPthreadMutexLocker.h"

#include <string.h>
#include <sys/mman.h>
#include <pthread.h>

static pthread_mutex_t g_abort_msg_lock = PTHREAD_MUTEX_INITIALIZER;

abort_msg_t** __abort_message_ptr; // Accessible to __libc_init_common.

void android_set_abort_message(const char* msg) {
  ScopedPthreadMutexLocker locker(&g_abort_msg_lock);
  if (__abort_message_ptr == NULL) {
    // We must have crashed _very_ early.
    return;
  }
  if (*__abort_message_ptr != NULL) {
    // We already have an abort message.
    // Assume that the first crash is the one most worth reporting.
    return;
  }
  size_t size = sizeof(abort_msg_t) + strlen(msg) + 1;
  void* map = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
  if (map == MAP_FAILED) {
    return;
  }
  // TODO: if we stick to the current "one-shot" scheme, we can remove this code and
  // stop storing the size.
  if (*__abort_message_ptr != NULL) {
    munmap(*__abort_message_ptr, (*__abort_message_ptr)->size);
  }
  abort_msg_t* new_abort_message = reinterpret_cast<abort_msg_t*>(map);
  new_abort_message->size = size;
  strcpy(new_abort_message->msg, msg);
  *__abort_message_ptr = new_abort_message;
}
