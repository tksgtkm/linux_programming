/*ソケットを作成する。
　ソケットへバインドするパス名があれば削除する。
　サーバーソケットのアドレス構造体を生成し、ソケットをバインドし、
　リスニングソケットとする。
　クライアントからの接続要求を処理する無限ループを実行する。
　繰り返しのたびに次の内容を実行する。
　ー接続要求を受付け、接続に対応する新規ソケット(コネクション)cfdを得る。
　ー接続済みソケットからのデータをすべて受信し、標準出力へ出力する。
　ー接続済みソケットcfdをクローズする。*/
#include "us_xfr.h"
#define BACKLOG 5

int main(int argc, char *argv[]) {

  struct sockaddr_un addr;
  int sfd, cfd;
  ssize_t num_read;
  char buf[BUF_SIZE];

  sfd = socket(AF_UNIX, SOCK_STREAM, 0); // ソケット作成
  if (sfd == -1)
    errExit("socket");

　// サーバーソケットアドレスの作成、バインド、listen開始

  if (strlen(SV_SOCK_PATH) > sizeof(addr.sun_path) - 1)
    fatal("Server socket path too: %s", SV_SOCK_PATH);

  if (remove(SV_SOCK_PATH) == -1 && errno != ENOENT)
    errExit("remove-%s", SV_SOCK_PATH);

  memset(&addr, 0, sizeof(struct sockaddr_un)); // 構造体をゼロクリア
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1); // UNIXドメインのアドレス

  if (bind(sfd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un)) == -1)
    errExit("bind");

  if (listen(sfd, BACKLOG) == -1)
    errExit("listen");

  for (;;) {
    // クライアントからの接続を逐次処理
    /*接続を受け付ける。
    　コネクションは新規ソケット'cfd'であるリスニングソケット
    　('sfd')はオープンしたまま以降の接続を受け付ける*/
    cfd = accept(sfd, NULL, NULL);
    if (cfd == -1)
      errExit("accept");

    // 接続済みソケットから受信したデータをEOFに到達するまでstdoutへ転送する
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
