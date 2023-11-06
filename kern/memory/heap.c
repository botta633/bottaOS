#include "heap.h"
#include "../includes/lib.h"
#include "../includes/print.h"
#include "../../boot/mem.h"
//
// to be resolved in runtime

struct heap *heap = (struct heap *)(P2V(PMEM_KERN_START));

void init_heap()
{

  int i = 0;

  for (; i < 9; i++)
  {
    // to study the effect of caching heap->manager.zones[i]
    heap->manager.zones[i].firstFree = NULL;
    heap->manager.zones[i].used = NULL;
    heap->manager.zones[i].freeAreas = 0;
    heap->manager.zones[i].usedAreas = 0;
    heap->manager.zones[i].times_accessed = 0;
    heap->manager.activeZones[i] = 0;
    heap->manager.activeIdxes[i] = 0;
    heap->manager.zones[i].idx = i;
  }

  // initializing the largest zone with two free Areas
  void *first_free = (void *)(P2V(PMEM_KERN_START) + sizeof(struct heap));
  memset(first_free, 0, GETSIZE(i));

  heap->manager.zones[i].firstFree = first_free;
  heap->manager.zones[i].firstFree->next = NULL;
  heap->manager.zones[i].freeAreas = 1;
  heap->manager.zones[i].usedAreas = 0;
  heap->manager.zones[i].times_accessed = 0;
  heap->manager.zones[i].used = NULL;
  heap->manager.zones[i].idx = i;
  heap->manager.activeIdxes[i] = 1;
  heap->idx_of_largest_free = i;
}

static void divide_area(struct area *area, int size)
{
  area->next = area + (size >> 1);
  area->next->next = NULL;
}

static struct area *split_zone_to_match_size(struct zone *zone, int size)
{

  struct zone *temp = zone;
  struct area *tempArea = temp->firstFree;

  while (temp->idx != GETIDX(size))
  {
    tempArea = temp->firstFree;
    temp->freeAreas--;
    temp->firstFree = tempArea->next;
    divide_area(tempArea, GETSIZE(temp->idx));
    heap->manager.zones[temp->idx - 1].freeAreas += 2;
    heap->manager.zones[temp->idx - 1].firstFree = tempArea;
    if (GETIDX(size) == temp->idx)
      break;
    temp = &(heap->manager.zones[temp->idx - 1]);
  }

  tempArea->used = 1;
  temp->freeAreas--;
  temp->used = tempArea;
  temp->firstFree = tempArea->next;

  return tempArea;
}

// main function of zone allocator
void *zalloc(int size)
{
  int largest_idx = 0;

  for (int i = GETIDX(size); i < 10; i++)
    if (heap->manager.zones[i].freeAreas >= 1)
      return (void *)split_zone_to_match_size(&(heap->manager.zones[i]), size);

  return NULL;
}
