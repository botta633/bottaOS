#ifndef MEMs_H
#define MEMs_H

#include "stdbool.h"

struct area
{
  struct area *next;
  int used;
};

struct zone
{
  int idx;
  struct area *firstFree;
  struct area *used;
  int freeAreas;
  int usedAreas;
  int times_accessed;
};

struct heapManager
{
  struct zone zones[10];
  unsigned int activeZones[10];
  unsigned int activeIdxes[10];
};

struct page
{
  void *data;
  int size;
};

#endif
