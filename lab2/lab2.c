#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  while (1) {
    char *line = NULL;
    size_t n = 0;

    printf("Enter programs to run.\n");

    ssize_t charsRead = getline(&line, &n, stdin);

    if (charsRead == -1) {
      exit(EXIT_FAILURE);
    } else if (charsRead == 1) {
      free(line);
      exit(EXIT_SUCCESS);
    } else {
      line[strcspn(line, "\n")] = '\0';
      printf("%s", line);
    }

    char *savePtr = NULL;
    char *token = strtok_r(line, "/", &savePtr);

    char **charArr = NULL;
    size_t size = 0;

    while (token != NULL) {
      char **tempArr = realloc(charArr, (size + 1) * (sizeof(*charArr)));

      if (tempArr == NULL) {
        free(charArr);
        exit(EXIT_FAILURE);
      }
      charArr = tempArr;
      charArr[size] = token;
      size++;

      token = strtok_r(NULL, "/", &savePtr);
    }
    char *command = charArr[size - 1];
    printf("Command: %s\n", command);

    for (int i = 0; i < size; i++) {
      printf("tokens: %s\n", charArr[i]);
    }

    pid_t pid;
    pid = fork();
    switch (pid) {
    case -1:
      perror("fork");
      exit(EXIT_FAILURE);
    case 0:
      execlp(line, line, (char *)NULL);
      perror("execl");
      exit(EXIT_FAILURE);
    default:
      waitpid(pid, NULL, 0);
      break;
    }
  }
}
