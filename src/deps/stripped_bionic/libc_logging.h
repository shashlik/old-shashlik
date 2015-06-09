
#pragma once

#include <log/log.h>

#include <sys/cdefs.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

struct abort_msg_t {
  size_t size;
  char msg[0];
};
