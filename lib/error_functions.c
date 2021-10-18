#include <stdarg.h>
#include "error_functions.h"
#include "api_hdr.h"
#include "ename.c.inc" /* ename及びMAX_ENAMEの定義 */

#ifdef __GNUC__
__attribute__ ((__noreturn__))
#endif

static void terminate(Boolean useExit3) {

  char *s;

  /* 環境変数EF_DUMPCOREを空文字以外に設定した場合はコアダンプファイルを生成する。
  　　それ以外の場合はexit(3)または_exit(2)により終了する。
  　　どちらを実行するかはuseExit3により決定する。 */

  s = getenv("EF_DUMPCORE");

  if (s != NULL && *s != '\0')
    abort();
  else if (useExit3)
    exit(EXIT_FAILURE);
  else
    _exit(EXIT_FAILURE);
}

static void outputError(Boolean useErr, int err, Boolean flushStdout, const char *format, va_list ap) {

#define BUF_SIZE 500

  char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];

  vsnprintf(userMsg, BUF_SIZE, format, ap);

  if (useErr)
    snprintf(errText, BUF_SIZE, " [%s %s] ",
             (err > 0 && err <= MAX_ENAME) ?
             ename[err] : "?UNKNOWN" , strerror(err));
  else
    snprintf(errText, BUF_SIZE, ":");

  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wformat-truncation"
    snprintf(buf, BUF_SIZE, "ERROR%s %s\n", errText, userMsg);
  #pragma GCC diagnostic pop

    if (flushStdout)
      fflush(stdout); /* stdoutのフラッシュ */
    fputs(buf, stderr); /* stderrが行バッファリング出ない場合に備える。 */
    fflush(stderr);
}

void errMsg(const char *format, ...) {
  va_list argList;
  int savedErrno;

  savedErrno = errno; /* 本関数がerrnoを上書きする恐れがあるため */

  va_start(argList, format);
  outputError(TRUE, errno, TRUE, format, argList);
  va_end(argList);

  errno = savedErrno;
}

void errExit(const char *format, ...) {
  va_list argList;

  va_start(argList, format);
  outputError(TRUE, errno, TRUE, format, argList);
  va_end(argList);

  terminate(TRUE);
}

void err_exit(const char *format, ...) {
  va_list argList;

  va_start(argList, format);
  outputError(TRUE, errno, FALSE, format, argList);
  va_end(argList);

  terminate(FALSE);
}

void errExitEN(int errnum, const char *format, ...) {
  va_list argList;

  va_start(argList, format);
  outputError(TRUE, errnum, TRUE, format, argList);
  va_end(argList);

  terminate(TRUE);
}

void fatal(const char *format, ...) {
  va_list argList;

  va_start(argList, format);
  outputError(FALSE, 0, TRUE, format, argList);
  va_end(argList);

  terminate(TRUE);
}

void usageErr(const char *format, ...) {
  va_list argList;

  fflush(stdout);

  fprintf(stderr, "Usage: ");
  va_start(argList, format);
  vfprintf(stderr, format, argList);
  va_end(argList);

  fflush(stderr); /* stderrが行バッファリング出ない場合に備える */
  exit(EXIT_FAILURE);
}

void cmdLineErr(const char *format, ...) {
  va_list argList;

  fflush(stdout);

  fprintf(stderr, "Command^line usage error: ");
  va_start(argList, format);
  vfprintf(stderr, format, argList);
  va_end(argList);

  fflush(stderr); /* stderrが行バッファリング出ない場合に備える */
  exit(EXIT_FAILURE);
}
