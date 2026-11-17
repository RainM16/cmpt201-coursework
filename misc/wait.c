#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  int exitStatus = 0;

  if (pid == 0) {
    if (execlp("ls", "ls", "-a", "-l", NULL) == -1) {
      perror("execlp");
      exit(EXIT_FAILURE);
    }

  } else if (pid != -1) {
    // while (1) {
    if (waitpid(pid, &exitStatus, 0) != 0) {
      printf("Child done, exiting with status: %d\n", WIFEXITED(exitStatus));
      // printf("exit status %d\n", WIFEXITED(exitStatus));
      exit(EXIT_SUCCESS);
    } else if (waitpid(pid, &exitStatus, 0) == -1) {
      perror("waitpid");
      exit(EXIT_FAILURE);
    }
    //}
  }
}
