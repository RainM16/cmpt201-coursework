#include <stdio.h>
#include <unistd.h>

int main() {
  fork();

  for (int i = 0; i < 10; i++) {
    printf("Sleeping\n");
    sleep(1);
  }
  printf("done\n");
  return 0;
}
