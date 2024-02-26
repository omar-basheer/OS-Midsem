//
// Created by sblan on 20/02/2024.
//

// Import Dependencies
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "processes.c"

#define PAGE_SIZE 4
#define NO_OF_PAGES 256

/**
 * @struct logical_memory
 * @brief Represents the logical memory structure.
 * 
 * This structure contains information about the logical memory, including the page size,
 * the number of pages, the array representing the total logical address space, the array
 * of free pages, the array of allocated pages, and the free page counter, all for a particular process.
 * In this isntance, the memory size is 1024 bytes (page size * number of pages).
 */
struct logical_memory {
    int page_size; // 4 bytes
    int no_of_pages;
    bool free_pages[NO_OF_PAGES];
    int free_page_stack[NO_OF_PAGES];
    int stack_top;

    // int allocated_pages[NO_OF_PAGES];
    // int free_page_counter;
};

/**
 * Initializes the logical memory structure.
 * 
 * @param mem Pointer to the logical memory structure to be initialized.
 */
void initialize_logical_memory(struct logical_memory* mem) {
    mem->page_size = PAGE_SIZE;
    mem->no_of_pages = NO_OF_PAGES;
    mem->stack_top = -1;

    // Initialize all pages as free and push them onto stack
    for (int i = 0; i < mem->no_of_blocks; i++) {
        mem->free_pages[i] = i;
        mem->free_page_stack[++mem->stack_top] = i; // this is how we push onto the stack
        // mem->free_page_counter++;
    }
}

/**
 * Calculates the number of frames required to allocate memory for a process.
 * 
 * @param process A pointer to the Process structure representing the process.
 * @return The number of frames required for the process.
 */
int calculate_frames(struct Process* process) {
    int page_size = 4;
    int process_size = process->process_size;

    // Use ceil() to round up the result
    int frame_allocation = (int)ceil((double)process_size / page_size);

    return frame_allocation;
}

/**
 * Allocates memory for a process in the logical memory using calloc.
 * Calloc gets the number of pages needed and assigns contiguous addresses
 * to the process
 * 
 * @param mem The logical memory structure.
 * @param process The process structure.
 */
void calloc(struct logical_memory* mem, struct processes *process){

    int frames_needed = calculate_frames(process);

    // check if available resources are greater than need
    if(mem->free_page_counter < frames_needed){
        printf('Not enough resources')
        return;
    }

    // A for loop that attempts to assign address spaces contiguously
    int allocated_pages[frames_needed];
    for(int i = 0; i < frames_needed; i++ ){
        allocated_pages[i] = mem->free_page_stack[mem->stack_top--]; 
        mem->free_pages[allocated_pages[i]] = false;
    }

    // Update the page table for the process
    for(int i = 0; i < frames_needed; i++){
        process->page_table[i].frame_number = allocated_pages[i];
        process->page_table[i].valid =  1;
    }

}


//TODO implement malloc with above doc string