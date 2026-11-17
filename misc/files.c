#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  int s = open("tmp", O_RDWR | O_CREAT, S_IRWXU);

  int x = 6;

  char buf[12];

  ssize_t w = write(s, "HELLO", x);

  lseek(s, x / 2, SEEK_CUR);
  read(s, buf, x);

  write(STDOUT_FILENO, buf, s);
  close(s);

  printf("%s\n", buf);

  return 0;
}
