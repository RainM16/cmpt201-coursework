#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid == 0) {
    printf("Is Child: %d, parent is: %d\n", getpid(), getppid());
    execlp("ls", "ls", "-a" NULL);
  } else if (pid != -1) {
    printf("Is parent: %d, child is: %d\n", getpid(), pid);
    execlp("ls", "ls", "-a", "-l", "-h", NULL);
  }

  /*printf("%d\n", pid);
  for (int i = 0; i < 10; i++) {
    printf("Sleeping\n");
    sleep(1);
  }*/
  printf("done\n");
  return 0;
}
