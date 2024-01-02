#ifndef MEMs_H
#define MEMs_H

#include "stdbool.h"
#include "../../boot/mem.h"


//forward declaration of classes
struct block;
struct zone;

/* struct area
 * Pointing to next free area and gets replaced there by data
 * Neet to maintain metdata about size
 */

struct block
{
    struct Page *first_page;
    struct block *next;
    int size;
    void *data;
};

/*struct zone
 * group of areas of the same size
 *@field int idx, an index to indicate the size of areas in this zone
 */
struct zone
{
    struct block *first_free;
    struct zone *next;
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

void *zalloc(int size);

#endif
