#ifndef __US_XFR_H
#define __US_XFR_H

#include <sys/un.h>
#include <sys/socket.h>
#include "api_hdr.h"

// tmpは書き込み可能なディリクトリなので、実際は変えたほうがいい
#define SV_SOCK_PATH "/tmp/us_xfr"

#define BUF_SIZE 100

#endif
