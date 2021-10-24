#include "id_echo.h"

int main(int argc, char *argv[]) {
  int sfd, j;
  size_t len;
  ssize_t numread;
  char buf[BUF_SIZE];

  if (argc < 2 || strcmp(argv[1], "--help") == 0)
    usageErr("%s host msg...\n", argv[0]);

  sfd = inetConnect(argv[1], SERVICE, SOCK_DGRAM);
  if (sfd == -1)
    fatal("Could not connect to server socket");

  for (j=2; j<argc; j++) {
    len = strlen(argv[j]);
    if (write(sfd, argv[j], len) != len)
      fatal("partial/failed write");

    numread = read(sfd, buf, BUF_SIZE);
    if (numread == -1)
      errExit("read");

    printf("[%ld bytes] %.*s\n", (long)numread, (int)numread, buf);
  }

  exit(EXIT_SUCCESS);
}
