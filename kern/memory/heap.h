#ifndef HEAP_H
#define HEAP_H

#include <stdint.h>
#include "config.h"
#include "buddy.h"
#include "stddef.h"

#include "../utils/math.h"
#include "mem.h"

// heap is full- it is devide to two power of 2
// we will have 2

struct heap
{
  struct heapManager manager;
  unsigned short idx_of_largest_free;
};

#define GETIDX(size) \
  LOG2(ceil(size / 4096.0f), uint64_t)

#define GETSIZE(idx) \
  (2 ^ (idx + 2) * 1024)

void init_heap();
int allocate_page(struct page *page);
void block_coalescing(int idx);
void divide_zone(int idx);

void *zalloc(int size);
bool zfree(void *address);

#endif

// 1 GB, allow allocations from 1  down to 4KB.
// so when we first allocate a block we get the log
//
//
// Programming Thoughts:
//  We need a bitMap per size
//
