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

void read_from_file(char *filename) {
    int fd, sz;
    char c[5000] = "";

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
    warn("%s", filename);
    //exit(1);
    }
    sz = read(fd, c, 5000);
    c[sz] = '\0';
    write(STDOUT_FILENO, c, 5000);
}

int main(int argc, char *argv[]) {
    if (argc == 1 ||
        strcmp(argv[1], "-") == 0) {  // no args, should read from stdin
    read_from_stdin();
    return 0;
    } else { //one or more args
        int i;
        for(i = 1; i < argc; i++){
            read_from_file(argv[i]);
        }
    }
  return EXIT_SUCCESS;
}
