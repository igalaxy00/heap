#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

#include <stddef.h>
#include <stdbool.h>
#include "libHeap.h"

//ниже идут экземпляры функций
extern heap *heapInit(unsigned int start_data);

extern void heapShiftUp(heap *h, size_t i);

extern void heapShiftDown(heap *h, size_t i);


#endif