#include "mem.h"
#include "../kern/includes/print.h"
#include "../kern/includes/debug.h"
#include "../kern/includes/lib.h"
#include "stddef.h"
#include "stdbool.h"
#include "utils.h"
#include <stdint.h>

#define KERN_MEM_SIZE (10 * 1024 * 1024)
typedef uint64_t pte_t;

#define NUM_ENTRIES 512
#define PHYSICAL_MEM_START (0x100000)

static void free_region(uint64_t v, uint64_t e);

static struct FreeMemRegion free_mem_region[50];
static struct Page free_memory;
static uint64_t memory_end;
extern char end;

struct Page *free_mem = (struct Page *)(PHYSICAL_MEM_START );

uint64_t entries[NUM_ENTRIES];

static void create_mapping(uint64_t virtual_address) {
    uint64_t level4_index = (virtual_address >> 39) & 0x1FF;
    uint64_t level3_index = (virtual_address >> 30) & 0x1FF;
    uint64_t level2_index = (virtual_address >> 21) & 0x1FF;
    uint64_t level1_index = (virtual_address >> 12) & 0x1FF;
}


void kfree(uint64_t v)
{
    ASSERT(v % PAGE_SIZE == 0);
    ASSERT(v >= (uint64_t) & end);
    ASSERT(v+PAGE_SIZE <= 0xffff800040000000);

    struct Page *page_address = (struct Page*)v;
    page_address->next = free_mem;
    free_mem = page_address;
}


void* kalloc(void)
{
    void *temp = free_mem;
    free_mem = free_mem->next;
    return temp;
}

static void initialize_page_tables(){
    uint64_t *pml4 =kalloc();
    memset(pml4, 0, PAGE_SIZE);
    //setup recursive mapping
    pml4[511] = (uint64_t)pml4;
}

//maybe later on depend on the machine specs for getting
//memory size using bios
void initialize_physical_memory(){
    struct Page* addr = (struct Page *)(KERN_MEM_SIZE + PHYSICAL_MEM_START);
    free_mem = addr;
    for(; (uint64_t)addr > PHYSICAL_MEM_START;
            addr -= PAGE_SIZE) {
        addr->next = addr - PAGE_SIZE;
    }
    initialize_page_tables();

}
