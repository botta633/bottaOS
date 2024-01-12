#include "../includes/exception.h"


void div_by_0_handler(struct TrapFrame *frame){

    printk("Divide by 0 error");
    frame->rip++;
}


void page_fault_handler(struct TrapFrame *frame) {
    uint64_t error_code;
    
    __asm__ volatile (
        "pop %[result]" // Inline assembly to pop top of stack into %[result]
        : [result] "=r" (error_code) // Output operand: result in register
    );

    printk("Came to this handler\n");


    if(!BIT_CHECK(error_code, P))
        printk("Error address is not mapped");

    uint64_t cr2_val;

    // Inline assembly to move the value from the RAX register to variable x
    __asm__ volatile (
        "movq %%rax, %[variable]" // Move the value from RAX to %[variable]
        : [variable] "=r" (cr2_val) // Output operand: variable holding the register value
        : // No input operand needed for RAX; it's implicitly used
    );

    printk("cr2 val is %ud", cr2_val);

}


