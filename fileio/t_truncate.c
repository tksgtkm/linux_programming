#include "api_hdr.h"

int main(int argc, char *argv[]) {
  if (argc != 3 || strcmp(argv[1], "--help") == 0)
    usageErr("%s file length\n", argv[0]);

  if (truncate(argv[1], getLong(argv[2], GN_ANY_BASE, "length")) == -1)
    errExit("truncate");

  exit(EXIT_SUCCESS);
}
