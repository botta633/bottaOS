#ifndef HEAP_H
#define HEAP_H
#include "config.h"

#include <stdint.h>
#include <stddef.h>

// Coding the buddy allocator
#define MAX_ORDER 20 
#define KERNEL_HEAP_START 0xC0000000



struct zone{
  unsigned short isfree;
  void *start_addr;
  struct zone *nextFree;
};

// heap is full- it is devide to two power of2 
// we will have 2
struct heap{
  struct zone zones[MAX_ORDER];
  unsigned short idx_of_largest_free;


};  

int heap_Create

int allocate_page(unsigned int size, char *data);



  











#endif
