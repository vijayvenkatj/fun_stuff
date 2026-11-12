#ifndef INT_ARRAY_H
#define INT_ARRAY_H

#include <stddef.h>

typedef struct {
  int *data;
  size_t length;
  size_t capacity;
} Slice;


int slice_init(Slice *slice);
int slice_insert(Slice *slice, int num);
void slice_print(Slice *slice);
void slice_destroy(Slice *slice);

#endif
