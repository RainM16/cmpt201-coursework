#define _POSIX_C_SOURCES 200809
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *message = "CTRL-Q pressed\n";
void handle_sigint(int signum) { write(STDOUT_FILENO, message, strlen(message)); }

int main() {

  pid_t status = fork();
  if (status == 0) {
    while (1) {
      sleep(1);
      printf("hey parent\n");
      if (kill(getppid(), SIGINT) == -1) {
        perror("kill()");
        exit(EXIT_FAILURE);
      }
    }
  } else {
    struct sigaction act;
    act.sa_handler = handle_sigint;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);

    if (sigaction(SIGINT, &act, NULL) == -1) {
      perror("Sigaction() failed");
      exit(EXIT_FAILURE);
    }

    printf("parent sleeping\n");
    while (1) {
      sleep(1);
    }
  }
}
