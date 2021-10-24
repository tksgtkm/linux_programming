#include <syslog.h>
#include "id_echo.h"
#include "become_daemon.h"

int main(int argc, char *argv[]) {
  int sfd;
  ssize_t numread;
  socklen_t len;
  struct sockaddr_storage claddr;
  char buf[BUF_SIZE];
  char addrstr[IS_ADDR_STR_LEN];

  if (becomeDaemon(0) == -1)
    errExit("becomeDaemon");

  sfd = inetBind(SERVICE, SOCK_DGRAM, NULL);
  if (sfd == -1) {
    syslog(LOG_ERR, "Could not create server socket (%s)", strerror(errno));
    exit(EXIT_FAILURE);
  }

  for (;;) {
    len = sizeof(struct sockaddr_storage);
    numread = recvfrom(sfd, buf, BUF_SIZE, 0, (struct sockaddr *) &claddr, &len);

    if (numread == -1)
      errExit("recvfrom");

    if (sendto(sfd, buf, numread, 0, (struct sockaddr *) &claddr, len) != numread)
      syslog(LOG_WARNING, "Error echoing response to %s (%s)",
             inetAddressStr((struct sockaddr *) &claddr, len, addrstr, IS_ADDR_STR_LEN),
             strerror(errno));
  }
}
