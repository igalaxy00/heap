
#ifndef HEAP_LIBHEAP_H
#define HEAP_LIBHEAP_H

#include <stddef.h>
#include <stdbool.h>

typedef int key_heap;
typedef unsigned int value_heap;

typedef struct {// чтобы каждый раз не вызывать   struct
    key_heap key;
    value_heap value;
} pair_heap;// создание новую структуру pair_heap

typedef struct { // чтобы каждый раз не вызывать   struct
    pair_heap *array;
    size_t size;
    unsigned int data;
    bool max;
} heap; // создание новую структуру heap

//ниже идут экземпляры функций
extern heap *maxHeap(unsigned int start_data);

extern heap *minHeap(unsigned int start_data);

extern void heapAdd(heap *h, pair_heap p);

extern pair_heap heapRoot(heap *h);

extern void heapRemove(heap *h);

extern void heapSort(key_heap *array, size_t size);

extern heap *minHeapArray(pair_heap *p, size_t size);

extern heap *maxHeapArray(pair_heap *p, size_t size);

extern void printHeap(heap *h);

#endif