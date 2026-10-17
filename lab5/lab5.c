#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: Implement first fit

  struct header *ptr = free_list_ptr;

  while (ptr != NULL) {

    if (ptr->size >= size) {
      return ptr->id;
    }
    ptr = ptr->next;
  }
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  // TODO: Implement best fit
  struct header *ptr = free_list_ptr;
  struct header *curBest = NULL;

  while (ptr != NULL) {
    if (ptr->size >= size) {
      if (curBest == NULL) {
        curBest = ptr;
      }
      if (curBest->size > ptr->size) {
        curBest = ptr;
      }
    }
    ptr = ptr->next;
  }
  return curBest->id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *ptr = free_list_ptr;
  struct header *curBest = NULL;

  while (ptr != NULL) {
    if (ptr->size >= size) {
      if (curBest == NULL) {
        curBest = ptr;
      }
      if (curBest->size < ptr->size) {
        curBest = ptr;
      }
    }
    ptr = ptr->next;
  }
  return curBest->id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  // TODO: Print out the IDs
  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);

  printf("The ID for Best-Fit algorithm is: %d\n", best_fit_id);

  printf("The ID for Worst-Fit algorithm is: %d\n", worst_fit_id);
  return 0;
}

// Coalescing Alg
//
// When block is freed, store it's address and loop through all free blocks and find if any
// terminate 1 byte before the freed block's address. To check if free memory ends in correct place,
// do address
//+ size of block. If true, then change free memory's size to include the freed memory's size.
