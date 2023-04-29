#include "main.h"
#include "../kern/includes/trap.h"
#include "../kern/includes/print.h"
#include "../kern/memory/heap.h"
#include "mem.h"

void KMain(void)
{
    init_idt();
    init_memory();
    init_kvm();
    init_heap();
    int *val = (int *)(zalloc(4096));
    printk("came here \n");
    *val = 5;
    printk("%x \n", val);
}
