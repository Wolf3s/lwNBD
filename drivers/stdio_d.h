#ifndef STDIO_DRIVERS_NBD_H
#define STDIO_DRIVERS_NBD_H

#include "../nbd_server.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct file_driver
{
    nbd_context super;
    //TODO: char *pathname;
    FILE *fp;
} file_driver;

int file_ctor(file_driver *const me, const char *pathname);

#ifdef __cplusplus
}
#endif
#endif /* STDIO_DRIVERS_NBD_H */
