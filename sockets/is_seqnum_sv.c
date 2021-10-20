#define _BSD_SOURCE

#include <netdb.h>

#include "is_seqnum.h"

#define BACKLOG 50

int main(int argc, char *argv[]) {
  uint32_t seqnum;
  char req_len_str[INT_LEN];
  char seq_num_str[INT_LEN];
  struct sockaddr_storage claddr;
  int lfd, cfd, optval, reqlen;
  socklen_t addrlen;
  struct addrinfo hints;
  struct addrinfo *result, *rp;

  #define ADDRSTRLEN (NI_MAXHOST + NI_MAXSERV + 10)
  char addrstr[ADDRSTRLEN];
  char host[NI_MAXHOST];
  char service[NI_MAXSERV];

  if (argc > 1 && strcmp(argv[1], "--help") == 0)
    usageErr("%s [init-swq-num]\n", argv[0]);

  seqnum = (argc > 1) ? getInt(argv[1], 0, "init-seq-num") : 0;

  if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
    errExit("signal");

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_family = AF_UNSPEC;
  hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;

  if (getaddrinfo(NULL, PORT_NUM, &hints, &result) != 0)
    errExit("getaddrinfo");

  optval = 1;
  for (rp=result; rp!=NULL; rp=rp->ai_next) {
    lfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (lfd == -1)
      continue;

    if (setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
      errExit("setsockopt");

    if (bind(lfd, rp->ai_addr, rp->ai_addrlen) == 0)
      break;

    close(lfd);
  }

  if (rp == NULL)
    fatal("Could not bind socket to any address");

  if (listen(lfd, BACKLOG) == -1)
    errExit("listen");

  freeaddrinfo(result);

  for (;;) {
    addrlen = sizeof(struct sockaddr_storage);
    cfd = accept(lfd, (struct sockaddr *) &claddr, &addrlen);
    if (cfd == -1) {
      errMsg("listen");
      continue;
    }

    if (getnameinfo((struct sockaddr *) &claddr, addrlen, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
      snprintf(addrstr, ADDRSTRLEN, "(%s, %s)", host, service);
    else
      snprintf(addrstr, ADDRSTRLEN, "(?UNKNOWN?)");
    printf("Connection from %s\n", addrstr);

    if (readLine(cfd, req_len_str, INT_LEN) <= 0) {
      close(cfd);
      continue;
    }

    reqlen = atoi(req_len_str);
    if (reqlen <= 0) {
      close(cfd);
      continue;
    }

    snprintf(seq_num_str, INT_LEN, "%d\n", seqnum);
    if (write(cfd, seq_num_str, strlen(seq_num_str)) != strlen(seq_num_str))
      fprintf(stderr, "Error on write");

    seqnum += reqlen;

    if (close(cfd) == -1)
      errMsg("close");
  }
}
