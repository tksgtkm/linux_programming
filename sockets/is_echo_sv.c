#include <signal.h>
#include <syslog.h>
#include <sys/wait.h>
#include "become_daemon.h"
#include "inet_sockets.h"
#include "api_hdr.h"

#define SERVICE "echo"
#define BUF_SIZE 4096

static void grimReaper(int sig) {
  int savedErrno;

  savedErrno = errno;
  while (waitpid(-1, NULL, WNOHANG) > 0)
    continue;
  errno = savedErrno;
}

static void handleRequest(int cfd) {
  char buf[BUF_SIZE];
  ssize_t numread;

  while ((numread = read(cfd, buf, BUF_SIZE)) > 0) {
    if (write(cfd, buf, numread) != numread) {
      syslog(LOG_ERR, "write() failed: %s", strerror(errno));
      exit(EXIT_FAILURE);
    }
  }

  if (numread == -1) {
    syslog(LOG_ERR, "Error from read(): %s", strerror(errno));
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]) {
  int lfd, cfd;
  struct sigaction sa;

  if (becomeDaemon(0) == -1)
    errExit("becomeDaemon");

  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = grimReaper;
  if (sigaction(SIGCHLD, &sa, NULL) == -1) {
    syslog(LOG_ERR, "Error from sigaction(): %s", strerror(errno));
    exit(EXIT_FAILURE);
  }

  lfd = inetListen(SERVICE, 10, NULL);
  if (lfd == -1) {
    syslog(LOG_ERR, "Could not create server socket (%s)", strerror(errno));
    exit(EXIT_FAILURE);
  }

  for (;;) {
    cfd = accept(lfd, NULL, NULL);
    if (cfd == -1) {
      syslog(LOG_ERR, "Failure in accept(): %s", strerror(errno));
      exit(EXIT_FAILURE);
    }

    switch(fork()) {
      case -1:
        syslog(LOG_ERR, "Can't create child (%s)", strerror(errno));
        close(cfd);
        break;
      case 0:
        close(lfd);
        handleRequest(cfd);
        _exit(EXIT_SUCCESS);
      default:
        close(cfd);
        break;
    }
  }
}