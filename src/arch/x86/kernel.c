#include "std/stdout.h"
#include "utils/string.h"
#include "terminal/terminal.h"

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
    char str[20];
    intToHex(current_addr,str);

    puts(2,40,"memory segment count: ",background_color);
    puts(2,65,str,background_color);

    return 1;
}

MemoryMapEntry* malloc(){
    for (int i = 0; i < MAX_BLOCKS; i++)
    {
       if (memory_map[i].free == 1){
            memory_map[i].free = 0;
            return &memory_map[i];
       }
    }
}

void free(MemoryMapEntry* entry){
    entry->free = 1;
}

void zero_out_memory(int base_addr, int end_addr) {
    volatile int *ptr = (volatile int *)base_addr;

    while (ptr < (volatile int *)end_addr) {
        *ptr = 0;
        ptr++;
    }
}

void kernel_start() {
    zero_out_memory(BASE_ADDR, END_ADDR);
    prepare_mem_blocks();
    prepare_terminal();
    fill_screen();

    while (1) {
        terminal();
    }
}
