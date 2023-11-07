#include "buddy.h"


void clear_bit(buddy_bitmap* bitmap, int bit){
      //we have every sizeof int * 8
  unsigned int arr_idx = bit/((sizeof(int) * 8));
  unsigned int byte_idx = bit%((sizeof(int) * 8));

BIT_CLEAR(bitmap->bits[arr_idx], byte_idx);

}
void set_bit(buddy_bitmap* bitmap, int bit){
  //we have every sizeof int * 8
  unsigned int arr_idx = bit/((sizeof(int) * 8));
  unsigned int byte_idx = bit%((sizeof(int) * 8));

BIT_SET(bitmap->bits[arr_idx], byte_idx);
}

int get_bit(buddy_bitmap* bitmap, int bit){
  unsigned int arr_idx = bit/((sizeof(int) * 8));
  unsigned int byte_idx = bit%((sizeof(int) * 8));

  return BIT_CHECK(bitmap->bits[arr_idx], byte_idx);

}
