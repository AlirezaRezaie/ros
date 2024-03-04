#include <stddef.h>
#include "memory.h"
#include "../std/stdout.h"

// this static memory alloction was nececery since it would overwrite parts of memory if simply
// put inside bss
MemoryMapEntry memory_map[MAX_BLOCKS];


void memory_map_append(long current_addr, int size, int blk_count) {
    memory_map[blk_count].base_adr = current_addr;
    memory_map[blk_count].end_adr = current_addr + size;
    memory_map[blk_count].free = 1;
}

int prepare_mem_blocks() {
    long long int current_addr = BASE_ADDR;
    int block_count = 0;

    // Loop from 1 GB to 4 GB
    while (current_addr < END_ADDR) {
        // Append current address to memory map with block size information
        memory_map_append(current_addr, BLOCK_SIZE, block_count);

        // Move to the next block
        current_addr += BLOCK_SIZE;
        block_count++;

        // Ensure we don't exceed the maximum number of blocks
        if (block_count >= MAX_BLOCKS) {
            break;
        }
    }

    sprintf(2,40,"Blocks read: %d",block_count);

    return 1;
}

MemoryMapEntry* malloc(int size){
    // the size is in bytes
    int count = 0;
    for (int i = 0; i < MAX_BLOCKS; i++)
    {
       if (memory_map[i].free == 1){
            memory_map[i].free = 0;
            count++;
            if (count*BLOCK_SIZE >= size){
            return &memory_map[i];
            }
       }
    }
}



void zero_out_memory(int base_addr, int end_addr) {
    volatile int *ptr = (volatile int *)base_addr;

    while (ptr < (volatile int *)end_addr) {
        *ptr = 0;
        ptr++;
    }
}
void free(MemoryMapEntry* entry){
    zero_out_memory(entry->base_adr,entry->end_adr);
    entry->free = 1;
}

void copy_memory(int f_base_addr, int f_end_addr, int mem_ptr) {
    volatile int *src_ptr = (volatile int *)f_base_addr;
    volatile int *dest_ptr = (volatile int *)mem_ptr;

    // copym the memory src to dest 4 bytes at the time
    size_t num_elements = (f_end_addr - f_base_addr) / sizeof(int);
    for (size_t i = 0; i < num_elements; ++i) {
        dest_ptr[i] = src_ptr[i];
    }
}
