
#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#define BUF_SIZE 256

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];

  ssize_t len = snprintf(buf, BUF_SIZE, format,
                         data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);

  if (len < 0) {
    perror("snprintf");
    exit(EXIT_FAILURE);
  }
  write(STDOUT_FILENO, buf, len);
}

int main() {
  void *addr = sbrk(256);

  if (addr == (void *)-1) {
    perror("sbrk");
    exit(EXIT_FAILURE);
  }

  struct header *block1 = (struct header *)addr;
  block1->size = 128;
  block1->next = NULL;

  struct header *block2 = (struct header *)((char *)addr + 128);
  block2->size = 128;
  block2->next = block1;

  memset(block1 + 1, 0, 128 - sizeof(struct header));
  memset(block2 + 1, 1, 128 - sizeof(struct header));

  // int waldo = 42;
  // print_out("Where is waldo? %p\n", &waldo, sizeof(&waldo));
  print_out("Block 1 address: %p\n", &block1, sizeof(void *));
  print_out("Block 2 address: %p\n", &block2, sizeof(void *));
  print_out("Block 1 size: %lu\n", &block1->size, sizeof(uint64_t));
  print_out("Block 2 size: %lu\n", &block2->size, sizeof(uint64_t));
  print_out("Block 1 next: %p\n", &block1->next, sizeof(void *));

  print_out("Block 2 next: %p\n", &block2->next, sizeof(void *));
  return 0;
}
