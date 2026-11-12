#include "darray.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


int slice_init(Slice *slice) {
  slice->length = 0;
  slice->capacity = 2;

  slice->data = malloc(sizeof(int)*slice->capacity);
  if (slice->data == NULL) {
    return -1;
  }

  return 0;
}

int slice_insert(Slice *slice, int num) {
  if (slice->length == slice->capacity) {
    size_t new_capacity = slice->capacity * 2;

    int *tmp = realloc(slice->data, sizeof(int)*new_capacity);
    if (tmp == NULL) {
      return -1;
    }

    slice->capacity = new_capacity;
    slice->data = tmp;
  }

  slice->data[slice->length++] = num;
  return 0;
}

void slice_print(Slice *slice) {
  for (size_t i = 0; i < slice->length; i++) {
    printf("%d ", slice->data[i]);
  }
  printf("\n");
}


void slice_destroy(Slice *slice) {
  free(slice->data);

  slice->capacity = 0;
  slice->length = 0;
  slice->data = NULL;
}
