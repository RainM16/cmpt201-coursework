#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printRecent(char **inputs, int currentIndex) {
  for (int i = 0; i < 5; i++) {
    int index = (currentIndex - i + 5) % 5;
    if (inputs[index] != NULL) {
      printf("%s", inputs[index]);
    }
  }
}

int main() {
  char *recentInputs[5] = {NULL};

  char *linePtr = NULL;
  size_t size = 0;

  int inputIndex = 4;

  while (1) {
    ssize_t linesRead = getline(&linePtr, &size, stdin);

    if (linesRead == -1) {
      perror("getline()");
      exit(EXIT_FAILURE);
    }

    if (strcmp(linePtr, "print\n") == 0) {
      printRecent(recentInputs, inputIndex);
      break;
    }

    char *input = malloc((linesRead + 1) * sizeof(char));

    if (input == NULL) {
      perror("malloc");
      exit(EXIT_FAILURE);
    }

    strcpy(input, linePtr);

    if (recentInputs[inputIndex] != NULL) {
      free(recentInputs[inputIndex]);
    }
    recentInputs[inputIndex] = input;

    if (inputIndex == 0) {
      inputIndex = 4;
    } else {
      inputIndex--;
    }
  }

  for (int i = 0; i < 5; i++) {
    if (recentInputs[i] != NULL) {
      free(recentInputs[i]);
      recentInputs[i] = NULL;
    }
  }

  free(linePtr);
  linePtr = NULL;

  return 0;
}
