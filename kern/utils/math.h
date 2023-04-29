#ifndef MATH_H
#define MATH_H



#define LOG2(X,type) ((unsigned) (8*sizeof (type) - __builtin_clzll((X)) - 1))

int ceil(float x);
int floor(float x);



#endif
