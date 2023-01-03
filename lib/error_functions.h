#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

/*
メッセージを標準エラーへ出力する。
引数はprintf()と同様だた、末尾へ自動的に改行文字を付加する。
errMsg()は現在のerrnoに応じたEPERMなどのエラー名、
stderror()が返すエラーメッセージを文字列に続けて、引数に指定された
文字列をフォーマットして出力する
*/
void errMsg(const char *format, ...);

#ifdef __GNUC__

/*以下の関数によりmain()など非void関数を終了する場合
  'gcc -Wall'が無用の警告を発するのを抑制するマクロ*/

#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

/*
errMsg()と同様、出力後にexit()を実行するか、
または環境変数EF_DUMPCOREに空文字列以外が設定されていた場合は
abort()を実行し、デバッガが使用するコアダンプファイルを生成し、
その後プログラムを終了させる。
*/
void errExit(const char *format, ...) NORETURN ;

/*
errExit()と同様の関数であるが下記二点で異なる
・エラーメッセージを出力前に標準出力をフラッシュしない
・exit()ではなく、_exit()により終了する。
　すなわち、stdioバッファをフラッシュせず、またexitハンドラも実行しない。
*/
void err_exit(const char *format, ...) NORETURN ;

/*
errExit()と同様の関数であるが、
errnoの現在値に対応するエラーメッセージの代わりに
引数のerrnumに対応するエラーメッセージを出力する。
POSIXスレッドAPIを使用する場合に主に使用する。
エラー時に-1を返す従来のUNIXシステムコールとは異なり
POSIXスレッドAPIはエラー番号を戻り値とする。
*/
void errExitEN(int errnum, const char *format, ...) NORETURN ;

/*
汎用のエラー処理関数
errnoを出力しないライブラリ関数での異常終了時にも用いる
出力する文字列の末尾に自動的に改行文字も追加する
*/
void fatal(const char *format, ...) NORETURN ;

/*
コマンドラインパラメータに関するエラーを処理する。
Usage: に続く文字列で標準エラーを出力する。
そしてexit()で終了する。
*/
void usageErr(const char *format, ...) NORETURN ;

// プログラムが指定したコマンドラインパラメータに特化した関数
void cmdLineErr(const char *format, ...) NORETURN ;

#endif

