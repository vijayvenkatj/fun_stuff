#include "mycat.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {

  void *buffer = malloc(BUFFER_SIZE);
  if (buffer == NULL) {
    perror("malloc");
    return -1;
  }

  int input_fd = STDIN_FILENO;

  if (argc == 2) {
      input_fd = open(argv[1], O_RDONLY);
      if (input_fd == -1) {
        perror("open");
        free(buffer);
        return 1;
      }
  } else if (argc > 2) {
      for (int i = 1; i < argc; i++) {
          int input_fd = open(argv[i], O_RDONLY);
          if (input_fd == -1) {
              perror(argv[i]);
              continue;
          }

          int n = read_and_write(input_fd, buffer, BUFFER_SIZE);
          if (n != 0) {
            perror("read_and_write");
            close(input_fd);
            free(buffer);
            return -1;
          }

          close(input_fd);
      }
      free(buffer);
      return 0;
  }

  int n = read_and_write(input_fd, buffer, BUFFER_SIZE);
  if (n != 0) {
    perror("read_and_write");
    close(input_fd);
    free(buffer);
    return -1;
  }

  close(input_fd);
  free(buffer);

  return 0;
}
