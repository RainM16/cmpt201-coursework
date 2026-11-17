#define _POSIX_SOURCE 200809
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int cnt = 0;

void *thread_func(void *arg) {
  printf("%lu: %p\n", strlen(arg), arg);

  return (void *)strlen(arg);
}

void *data_race() {
  for (int i = 0; i < 10000000; i++) {
    cnt++;
  }
  return NULL;
}

int main() {
  pthread_t id1;
  pthread_t id2;
  /*
    if (pthread_create(&id, NULL, thread_func, "Hello") != 0) {
      perror("thread");
      exit(EXIT_FAILURE);
    };
  */

  if (pthread_create(&id1, NULL, data_race, NULL) != 0) {
    perror("thread");
    exit(EXIT_FAILURE);
  }
  if (pthread_create(&id2, NULL, data_race, NULL) != 0) {
    perror("thread");
    exit(EXIT_FAILURE);
  }

  void *thread_ret1 = 0;
  void *thread_ret2 = 0;

  if (pthread_join(id1, &thread_ret1) != 0 && pthread_join(id2, &thread_ret2) != 0) {
    perror("Unable to join");
    exit(EXIT_FAILURE);
  };

  printf("Count: %d\n", cnt);
  return 0;
}
