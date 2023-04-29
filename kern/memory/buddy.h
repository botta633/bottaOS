#ifndef BITMAP_H
#define BITMAP_H

#include "config.h"

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1ULL << (b)))
#define BIT_FLIP(a, b) ((a) ^= (1ULL << (b)))
#define BIT_CHECK(a, b) ({int k; (k = (!!((a) & (1ULL<<(b))))); k; })

#define LIST

typedef struct buddy_bitmap
{
  int bits[BUDDY_BIT_MAP_WIDTH];
  int free_areas;
} buddy_bitmap;

struct pair
{
  int arrIdx;
  int offset;
};

void clear_bit(buddy_bitmap *bimap, int bit);
void set_bit(buddy_bitmap *bimap, int bit);
int get_bit(buddy_bitmap *bimap, int bit);

#endif
