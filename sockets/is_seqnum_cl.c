#define _POSIX_C_SOURCE 200112L

#include <netdb.h>
#include "is_seqnum.h"

int main(int argc, char *argv[]) {
  char *req_len_str;
  char seq_num_str[INT_LEN];
  int cfd;
  ssize_t num_read;
  struct addrinfo hints;
  struct addrinfo *result, *rp;

  if (argc < 2 || strcmp(argv[1], "--help") == 0)
    usageErr("%s server-host [sequence-len]\n", argv[0]);

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_NUMERICSERV;

  if (getaddrinfo(argv[1], PORT_NUM, &hints, &result) != 0)
    errExit("getaddrinfo");

  for (rp=result; rp!=NULL; rp=rp->ai_next) {
    cfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (cfd == -1)
      continue;

    if (connect(cfd, rp->ai_addr, rp->ai_addrlen) != -1)
      break;

    close(cfd);
  }

  if (rp == NULL)
    fatal("Could not connect socket to any address");

  freeaddrinfo(result);

  req_len_str = (argc > 2) ? argv[2] : "1";
  if (write(cfd, req_len_str, strlen(req_len_str)) != strlen(req_len_str))
    fatal("Partial/failed write (req_len_str)");
  if (write(cfd, "\n", 1) != 1)
    fatal("Partial/failed write (newline)");

  num_read = readLine(cfd, seq_num_str, INT_LEN);
  if (num_read == -1)
    errExit("readline");
  if (num_read == 0)
    fatal("Unexpected number: %s", seq_num_str);

  printf("Sequence number: %s", seq_num_str);

  exit(EXIT_SUCCESS);
}
