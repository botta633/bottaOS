#include "list.h"
#include <stdio.h>




int main() {

  LIST_HEAD(list, node);
  struct list *head;

  LIST_INIT(head);
  
  struct {
    int data;
    LIST_ENTRY(node);
  }element[10];
























 return 0;
}
