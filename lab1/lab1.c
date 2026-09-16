#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  while (1) {

    char *line = NULL;
    size_t size = 0;

    printf("Please enter some text: ");

    ssize_t charsRead = getline(&line, &size, stdin);

    if (charsRead == -1) {
      perror("getline() failed");
      exit(EXIT_FAILURE);
    } else if (charsRead == 1) {
      exit(EXIT_SUCCESS);
    } else {
      printf("%zd chars read\n", charsRead);
    }

    char *saveptr;
    char *token = strtok_r(line, " ", &saveptr);
    printf("Tokens:\n");

    while (token != NULL) {
      printf("  %s\n", token);
      token = strtok_r(NULL, " ", &saveptr);
    }

    free(line);
  }
  return 0;
}
