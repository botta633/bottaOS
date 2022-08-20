#include "utils.h"
#include <stdint.h>



//Display related variables
#define VGA_WIDTH 80
#define VGA_HEIGHT 20
uint16_t* video_mem = (uint16_t*)(0xb8000);
int col = 0;
int row = 0;

void print_char(char c, int color) {
  if(col >= VGA_WIDTH || c == '\n')
  {
    col = 0; 
    cow++;
    if(c == '\n')
      return;

  }
  video_mem[(row*VGA_WIDTH) + col] = (color << 8) | c;
  col++;
}


void initialize_terminal(){

  for(row; row < VGA_HEIGHT; row++)
    for(col; col < VGA_WIDTH; col++)
      print_char(' ', 0);
  row = 0;
  col = 0;

}

size_t strlen(const char *str) {
  size_t len = 0;
  while(*str++){
    len++;
}

return len;
}

void print_message(const char *msg){
  int len = strlen(msg);
  for(int i = 0; i < len; i++) {
    print_char(msg[i], 0xa);
  }

}
