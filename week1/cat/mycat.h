#ifndef MY_CAT_H

#define MY_CAT_H

#include <stddef.h>

int write_all(int fd, void *buffer, size_t length);
int read_and_write(int fd, void *buffer, size_t length);

#endif
