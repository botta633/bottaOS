#pragma once

#include "trap.h"
#include "print.h"
#include <stdint.h>

 
#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1ULL << (b)))
#define BIT_FLIP(a, b) ((a) ^= (1ULL << (b)))
#define BIT_CHECK(a, b) ({int k; (k = (!!((a) & (1ULL<<(b))))); k; })

#define P (0x0)
#define RW (0x1)
#define US (0x2)
#define RSVD (0x3)
#define ID (0x4)
#define PK (0x5)
#define SS (0x6)
#define SGX (0xF)


__attribute__((interrupt)) 
void div_by_0_handler(struct TrapFrame *frame);
__attribute__((interrupt)) 
void page_fault_handler(struct TrapFrame *frame);
    
