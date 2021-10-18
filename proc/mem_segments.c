
#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>

char globBuf[65536]; /* 未初期化データセグメント */
int primes[] = {2, 3, 5, 7}; /* 初期化済みデータセグメント */

static int square(int x) { /* square()のフレーム上に割り当てられる */
  int result;

  result = x * x;
  return result; /* レジスタ経由で戻り地を返す */
}

static void doCalc(int val) { /* doCalc()のフレーム上に割り当てられる */
  printf("The square of %d is %d\n", val, square(val));

  if (val < 1000) {
    int t;
    t = val * val * val;
    printf("The cube of %d is %d\n", val, t);
  }
}

int main(int argc, char *argv[]) { /* main()のフレーム上に割り当てられる */
  static int key = 9973; /* 初期化済みデータセグメント */
  static char mbuf[10240000]; /* 未初期化データセグメント */
  char *p;

  p = malloc(1024); /* ヒープセグメント上の領域を指す */
  doCalc(key);
  exit(EXIT_SUCCESS);
}
