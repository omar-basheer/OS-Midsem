//
// Created by sblan on 20/02/2024.
//

// Import Dependencies
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

#define PAGE_SIZE 4 
#define NUM_PAGES 5
#define MEMORY_SIZE (PAGE_SIZE * NUM_PAGES)

/**
 * @brief Declaration of the physical memory array.
 * 
 * This array represents the physical memory used by the program.
 * It has a size of MEMORY_SIZE.
 */
char physical_memory[MEMORY_SIZE];


/**
 * Initializes the physical memory by filling it with characters from 'a' to 'z'.
 * The memory size is defined by the constant MEMORY_SIZE.
 */
void init_physical_memory(){
    for (int i = 0; i < MEMORY_SIZE; i++) {
        physical_memory[i] = 'a' + (i % 26);
    }
}

/**
 * Prints the contents of the physical memory.
 * This function iterates over each frame in the physical memory
 * and prints the characters stored in each frame.
 */
void print_physical_memory() {
    printf("Physical memory contents:\n");
    for (int frame_number = 0; frame_number < NUM_PAGES; frame_number++) {
        printf("Frame %d: ", frame_number);
        for (int offset = 0; offset < PAGE_SIZE; offset++) {
            printf("%c ", physical_memory[frame_number * PAGE_SIZE + offset]);
        }
        printf("\n");
    }
}

void memory_access(int address) {
    int page_number = address / PAGE_SIZE;
    int page_offset = address % PAGE_SIZE;

    printf("Accessing address %d: Page number %d, Offset %d, Frame number %d\n",address, page_number, page_offset, page_table[page_number].frame_number);

    // populate the page table if the page is not valid
    if (page_table[page_number].valid){
        // access memory
        char data = physical_memory[page_table[page_number].frame_number * PAGE_SIZE + page_offset];
        printf("Data: %c\n", data);
    }
    else{
        printf("Page fault: Page %d is not in memory\n", page_number);
        // find free frame
        int free_frame = -1;
        for(int j = 0; j < NUM_PAGES; j++) {
            if (page_table[j].frame_number == -1) {
                free_frame = j;
                break;
            }
        }

        if (free_frame != -1){
            // allocate the free frame and mark it as valid 
            page_table[page_number].frame_number = free_frame;
            page_table[page_number].valid = 1;

            printf("Page %d allocated to frame %d\n", page_number, free_frame);

            // Accessing memory after page table population
            char data = physical_memory[page_table[page_number].frame_number * PAGE_SIZE + page_offset];
            printf("Data: %c\n", data);
        }
        else {
            printf("Error: No free frames available\n");
            return;
        }
    }

}



int main(){
    srand(time(NULL));
    init_page_table();
    init_physical_memory();

    print_page_table();
    print_physical_memory();

    //generate random memory access requests
    for (int i = 0; i < 10; i++) {
        int address = rand() % MEMORY_SIZE;
        memory_access(address);
    }
    
    print_page_table();
    return 0;
}

