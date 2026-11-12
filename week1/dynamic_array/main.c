#include "darray.h"

int main() {
  Slice arr = {
    .data = NULL,
    .length = 0,
    .capacity = 0
  };
  slice_init(&arr);

  slice_insert(&arr, 1);
  slice_insert(&arr, 2);
  slice_insert(&arr, 3);
  slice_insert(&arr, 4);
  slice_insert(&arr, 5);
  slice_insert(&arr, 6);
  slice_insert(&arr, 7);
  slice_insert(&arr, 8);

  slice_print(&arr);

  slice_destroy(&arr);
}
