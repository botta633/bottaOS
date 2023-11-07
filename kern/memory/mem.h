#ifndef MEMs_H
#define MEMs_H

#include "stdbool.h"


//forward declaration of classes
struct area;
struct zone;
struct page;

/* struct area
 * Pointing to next free area and gets replaced there by data
 * Neet to maintain metdata about size
 */

struct area
{
  struct area *next;
  int size;
  void *data;
};

/*struct zone
 * group of areas of the same size
 *@field int idx, an index to indicate the size of areas in this zone
 */
struct zone
{
  struct area *firstFree;
  struct area *used;
  int idx;
  // bookkeeping and statistics
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

#endifa a 
