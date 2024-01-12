#ifndef _TRAP_H_
#define _TRAP_H_

#include "stdint.h"

#define IDT_MAX_DESCRIPTORS 256
#define GDT_OFFSET_KERNEL_CODE 0x8
typedef struct{
    uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU
                              // will load into CS before calling the ISR
	uint8_t	    ist;          // The IST in the TSS that the CPU will 
                              // load into RSP; set to zero for now
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_mid;      // The higher 16 bits of the lower 32 
                              // bits of the ISR's address
	uint32_t    isr_high;     // The higher 32 bits of the ISR's address
	uint32_t    reserved;     // Set to zero
 
} __attribute__((packed)) idt_entry;

__attribute__((aligned(0x10)))
    static idt_entry idt[IDT_MAX_DESCRIPTORS];


typedef struct {
    uint16_t limit;
    uint64_t base; //base address
} __attribute__((packed)) idtr_t;

static idtr_t idtr;

struct TrapFrame {
    int64_t r15;
    int64_t r14;
    int64_t r13;
    int64_t r12;
    int64_t r11;
    int64_t r10;
    int64_t r9;
    int64_t r8;
    int64_t rbp;
    int64_t rdi;
    int64_t rsi;
    int64_t rdx;
    int64_t rcx;
    int64_t rbx;
    int64_t rax;
    int64_t trapno;
    int64_t errorcode;
    int64_t rip;
    int64_t cs;
    int64_t rflags;
    int64_t rsp;
    int64_t ss;
}__attribute__((packed)) ;


__attribute__((noreturn))
    void exception_handler(void);

void idt_set_descriptor(int , void *, uint8_t);
void idt_init(void);
#endif
