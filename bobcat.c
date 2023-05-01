#include <err.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFSIZE 5000

void read_from_stdin() {
  char buffer[BUFSIZE];
  while (read(STDIN_FILENO, buffer, BUFSIZE) > 0) {
    printf("%s", buffer);
  }
  if (read(STDIN_FILENO, buffer, BUFSIZE) < 0) {
    warn("%s", buffer);
  }
}

int read_from_file(char *filename, bool check) {
  int fd, sz;
  char c[BUFSIZE] = "";

  fd = open(filename, O_RDONLY);
  if (fd < 0) {
    warn("%s", filename);
    return 0;
  }
  sz = read(fd, c, BUFSIZE);
  if (sz < 0) {
    warn("%s", filename);
    return 0;
  }
  c[sz] = '\0';
  int wr = write(STDOUT_FILENO, c, sizeof(c));
  if (wr < 0) {
    warn("%s", filename);
    return 0;
  }
  if (!check) {
    return 0;
  } else {
    return 1;
  }
}

int main(int argc, char *argv[]) {
  bool success = 1;
  if (argc == 1 ||
      (strcmp(argv[1], "-") == 0)) {  // no args, should read from stdin
    read_from_stdin();
    return 0;
  } else {  // one or more args
    int i;
    for (i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-") == 0) {  // wait for eof
        char buffer[BUFSIZE];
        int rd = read(STDIN_FILENO, buffer, BUFSIZE);
        if (rd < 0) {
          warn("%s", argv[i]);
          return 0;
        }
        while (rd <= 0) {
          i++;
          break;
        }
        printf("%s", buffer);
      } else {
        success = read_from_file(argv[i], success);
      }
    }
  }
  if (success == 1) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}
