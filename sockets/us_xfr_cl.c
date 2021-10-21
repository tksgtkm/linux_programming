/*ソケットを作成する。
　サーバソケットのアドレス構造体を生成し、接続する。
　標準入力から読み取ったデータを接続済みソケットへ転送するループを実行する。
　標準入力のend-of-fileに到達すれば終了し、終了処理の一環としてソケットを自動的にクローズする。
　以降にサーバがソケットを読み取るとend-of-fileを得る。*/
#include "us_xfr.h"

int main(int argc, char *argv[]) {
  struct sockaddr_un addr;
  int sfd;
  ssize_t num_read;
  char buf[BUF_SIZE];

  sfd = socket(AF_UNIX, SOCK_STREAM, 0); // クライアントソケット作成
  if (sfd == -1)
    errExit("socket");

  // サーバアドレス生成、接続
  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

  if (connect(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
    errExit("connect");

  // stdinからの入力をソケットへ転送
  while ((num_read = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
    if (write(sfd, buf, num_read) != num_read)
      fatal("partial/failed write");
  }

  if (num_read == -1)
    errExit("read");

  // ソケットのクローズ。サーバーはEOFを受信する。
  exit(EXIT_SUCCESS);
}
