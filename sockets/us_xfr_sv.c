#include "us_xfr.h"
#define BACKLOG 5

int main(int argc, char *argv[]) {

  struct sockaddr_un addr;
  int sfd, cfd;
  ssize_t num_read;
  char buf[BUF_SIZE];

  sfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sfd == -1)
    errExit("socket");

  if (strlen(SV_SOCK_PATH) > sizeof(addr.sun_path) - 1)
    fatal("Server socket path too: %s", SV_SOCK_PATH);

  if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT)
    errExit("remove-%s", SV_SOCK_PATH);

  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

  if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
    errExit("bind");

  if (listen(sfd, BACKLOG) == -1)
    errExit("listen");

  for (;;) {
    cfd = accept(sfd, NULL, NULL);
    if (cfd == -1)
      errExit("accept");

    while ((num_read = read(cfd, buf, BUF_SIZE)) > 0) {
      if (write(STDOUT_FILENO, buf, num_read) != num_read)
        fatal("partial/failed write");
    }

    if (num_read == -1)
      errExit("read");

    if (close(cfd) == -1)
      errMsg("close");
  }
}
