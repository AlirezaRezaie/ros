#ifndef MEMORY_H
#define MEMORY_H

#define BASE_ADDR  0x400000 // 15 MB
#define END_ADDR   0x7000000

                // 0x8000000  is max 128 MB
#define BLOCK_SIZE (50)
#define MAX_BLOCKS ((END_ADDR - BASE_ADDR) / (BLOCK_SIZE))

typedef struct {
    long base_adr;  // Changed to long to accommodate memory addresses
    long end_adr;
    int free;
} MemoryMapEntry;


void zero_out_memory(int base_addr, int end_addr);
void copy_memory(int f_base_addr, int f_end_addr, int mem_ptr);
MemoryMapEntry* malloc(int size);
int prepare_mem_blocks();

#endif
