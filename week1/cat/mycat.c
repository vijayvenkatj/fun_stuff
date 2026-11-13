#include "mycat.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

int write_all(int fd, void *buffer, size_t length) {
  size_t written = 0;

  while (written < length) {
    ssize_t n = write(fd, buffer+written, length-written);
    if (n == -1) {
      if (errno == EINTR) {
        continue;
      }
      perror("write");
      return -1; 
    }
    written += n;
  }

  return 0;
}


int read_and_write(int fd, void *buffer, size_t length) {
  ssize_t n;

  while ((n = read(fd, buffer, length)) > 0) {
    int out = write_all(STDOUT_FILENO, buffer, n);
    if (out == -1) {
      return -1;
    }
  }

  if (n == -1) {
    perror("read");
    return -1;
  }

  return 0;
}
