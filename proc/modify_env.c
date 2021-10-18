
#define _GNU_SOURCE /* <stdlib.h>内の宣言を有効にする */
#include <stdlib.h>
#include "api_hdr.h"

extern char **environ;

int main(int argc, char *argv[]) {
  int j;
  char **ep;

  clearenv(); /* 環境の全削除 */

  for (j = 1; j < argc; j++)
    if (putenv(argv[j]) != 0)
      errExit("putenv: %s", argv[j]);

  if (setenv("GREET", "Hello world", 0) == -1)
    errExit("setenv");

  unsetenv("BYE");

  for (ep = environ; *ep != NULL; ep++)
    puts(*ep);

  exit(EXIT_SUCCESS);
}
