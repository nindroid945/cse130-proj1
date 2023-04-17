#include <err.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void read_from_stdin() {
  char buffer[5000];
  while (read(STDIN_FILENO, buffer, 1) > 0) {
    printf("%s", buffer);
  }
}

// void read_from_file(str filename) {
//   char buffer[5000];
//   while (read(filename, buffer, 1) > 0) {
//     printf("%s", buffer);
//   }
// }

int main(int argc, char *argv[]) {
  if (argc == 1 ||
      strcmp(argv[1], "-") == 0) {  // no args, should read from stdin
    read_from_stdin();
  } else {
    if (strcmp(argv[1], "-") == 0) {
      // do nothing
    }

    printf("second arg is %s.\n", argv[2]);
  }

  return EXIT_SUCCESS;
}
