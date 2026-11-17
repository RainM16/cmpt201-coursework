#include <stdio.h>
#include <unistd.h>

int main() {
  int pid = fork();

  if (pid == 0) {
    int childPID = getpid();
    int parentPID = getppid();
    printf("Is Child: %d, parent is: %d\n", childPID, parentPID);
  } else if (pid == 1) {
    int PID = getpid();
    printf("Is parent: %d\n", PID);
  }

  /*printf("%d\n", pid);
  for (int i = 0; i < 10; i++) {
    printf("Sleeping\n");
    sleep(1);
  }*/
  printf("done\n");
  return 0;
}
