#include <unistd.h>
#include <errno.h>
#include "rdwrn.h"

ssize_t readn(int fd, void *buffer, size_t n) {
  ssize_t numread;
  size_t toread;
  char *buf;

  buf = buffer;
  for (toread=0; toread<n;) {
    numread = read(fd, buf, n-toread);

    if (numread == 0)
      return toread;

    if (numread == -1) {
      if (errno == EINTR)
        continue;
      else
        return -1;
    }

    toread += numread;
    buf += numread;
  }

  return toread;
}

ssize_t writen(int fd, const void *buffer, size_t n) {
  ssize_t numwritten;
  size_t towritten;
  const char *buf;

  buf = buffer;
  for (towritten=0; towritten<n;) {
    numwritten = write(fd, buf, n-towritten);

    if (numwritten <= 0) {
      if (numwritten == -1 && errno == EINTR)
        continue;
      else
        return -1;
    }
    towritten += numwritten;
    buf += numwritten;
  }

  return towritten;
}
