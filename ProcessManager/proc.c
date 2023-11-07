#include "proc.h"
#include "../boot/mem.h"
#include "../kern/includes/trap.h"

#include "../kern/includes/debug.h"
#include "../kern/includes/print.h"
#include "../kern/includes/lib.h"

extern struct TSS Tss;
static struct Process process_table[NUM_PROC];
static int pid_num = 1;

int main(void);

static void set_tss(struct Process *proc)
{
  Tss.rsp0 = proc->stack







