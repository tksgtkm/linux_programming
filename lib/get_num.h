#ifndef GET_NUM_H
#define GET_NUM_H

#define GN_NONNEG    01 /*自然数に制限する*/
#define GN_GT_0      02 /*正数に制限する*/

                          /*デフォルトでは10進数表記*/
#define GN_ANY_BASE  0100 /*strtol(3)同様に任意の基数に対応*/
#define GN_BASE_8    0200 /*8進数表記*/
#define GN_BASE_16   0400 /*16進数表記*/

/*
標準関数のatoi(), atol(), strtol()の代替として用いる
argに指定された文字列をそれぞれint, longへ変換する。
argが無効な場合は(数字、+、-以外の文字を含む)
エラーメッセージを表示してプログラムを終了させる。
*/
long getLong(const char *arg, int flags, const char *name);

int getInt(const char *arg, int flags, const char *name);

#endif
