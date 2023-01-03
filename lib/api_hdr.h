/*
インクルードする共通ヘッダファイルをまとめたファイル
*/


#ifndef API_HDR_H 
#define API_HDR_H /*二重インクルード事故防止*/

#include <sys/types.h> /*型の定義*/
#include <stdio.h>     /*標準I/O関数*/
#include <stdlib.h>    /*一般ライブラリ関数のプロトタイプ宣言及びEXIT_SUCCESS, EXIT_FAILUREの定義*/

#include <unistd.h>    /*システムコールの全般のプロトタイプ宣言*/
#include <errno.h>     /*errno及びエラー定数の宣言*/
#include <string.h>    /*文字列処理ライブラリ関数の宣言*/

#include "get_num.h"   /*数値パラメータ処理関数の宣言(getInt()getLong())*/

#include "error_functions.h" /*エラー処理関数の宣言*/

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

typedef enum { FALSE, TRUE } Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

#if defined(__sgi)
typedef int socklen_t;
#endif

#if defined(__sun)
#include <sys/file.h>
#endif

#if ! defined(O_ASYNC) && defined(FASYNC)
#define O_ASYNC FASYNC
#endif

#if defined(MAP_ANON) && ! defined(MAP_ANONYMOUS)
#define MAP_ANONYMOUS MAP_ANON
#endif

#if ! defined(O_SYNC) && defined(O_FSYNC)
#define O_SYNC O_FSYNC
#endif

#if defined(__FreeBSD__)

#define sival_int sigval_int
#define sival_ptr sigval_ptr
#endif

#endif

