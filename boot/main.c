#include "main.h"
#include "../kern/includes/trap.h"
#include "../kern/includes/print.h"
#include "mem.h"

void KMain(void)
{
    init_idt();
    init_memory();
    init_kvm();
    int *val = (int *)kalloc();
    printk("came here \n");
    *val = 5;
    printk("%d \n", *val);
}
