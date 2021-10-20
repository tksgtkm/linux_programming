#include <unistd.h>
#include <errno.h>

#include "read_line.h"

ssize_t readLine(int fd, void *buffer, size_t n) {
  ssize_t num_read;
  size_t tot_read;
  char *buf;
  char ch;

  if (n <= 0 || buffer == NULL) {
    errno = EINVAL;
    return -1;
  }

  buf = buffer;

  tot_read = 0;
  for (;;) {
    num_read = read(fd, &ch, 1);

    if (num_read == -1) {
      if (errno == EINTR)
        continue;
      else
        return -1;
    } else if (num_read == 0) {
        if (tot_read == 0)
          return 0;
        else
          break;
    } else {
        if (tot_read < n - 1) {
          tot_read++;
          *buf++ = ch;
        }

        if (ch == '\n')
          break;
    }
  }

  *buf = '\0';

  return tot_read;
}
