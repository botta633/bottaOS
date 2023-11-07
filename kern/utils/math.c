#include "math.h"

int ceil(float x){
  int temp = (int) x;

  if(temp == x)
    return temp;
  else{
    if(x < 0)
      return temp - 1;
    return temp + 1;

  }
}


int floor(float x){
  int temp = (int) x;

  if(temp == x)
    return temp;
  else{
    if(x < 0)
      return temp + 1;
    return temp - 1;

  }
}
