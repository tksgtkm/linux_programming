#include <syslog.h>
#include "api_hdr.h"

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {
  char buf[BUF_SIZE];
  ssize_t numread;

  while ((numread == read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
    if (write(STDOUT_FILENO, buf, numread) != numread) {
      syslog(LOG_ERR, "write() failed: %s", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  if (numread == -1) {
    syslog(LOG_ERR, "Error from read(): %s", strerror(errno));
    exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
