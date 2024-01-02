#include "main.h"
#include "../kern/includes/trap.h"
#include "../kern/includes/print.h"
#include "mem.h"

void write_to_serial_port(unsigned short int port, unsigned char data) 
{
      __asm volatile (
        "mov %0, %%al\n\t"    // Move the character to AL register
        "out %%al, %1\n\t"    // Output the character to the COM1 port
        :
        : "r" (data), "d" (port)
        : "eax"
    );
}

void print_word_to_port(const char *data) {

    while(*data != '\0') {
        write_to_serial_port(0X3F8,*data++);
    }
}
void KMain(void)
{   
    const char *color_red = "\033[31mThis text will be displayed in red.\033[0m";
    init_idt();
    init_memory();
    init_kvm();
    int *val = (int *)kalloc();
    printk("came here \n");
    *val = 5;
    printk("%d \n", *val);
    print_word_to_port(color_red);
}
