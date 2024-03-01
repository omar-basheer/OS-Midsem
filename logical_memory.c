//
// Created by sblan on 20/02/2024.
//

// Import Dependencies
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "process.h"
#include "logical_memory.h"

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
//struct logical_memory {
//    int page_size; // 4 bytes
//    int no_of_pages;
//    int free_pages[NO_OF_PAGES];
//    int free_page_stack[NO_OF_PAGES];
//    int free_stack_top;
//    int free_page_counter;
//    int allocated_page_stack[NO_OF_PAGES];
//    int allocated_stack_top;
//};

/**
 * Initializes the logical memory structure.
 * 
 * @param mem Pointer to the logical memory structure to be initialized.
 */
void initialize_logical_memory(struct logical_memory* mem) {
    mem->page_size = PAGE_SIZE;
    mem->no_of_pages = NO_OF_PAGES;
    mem->free_stack_top = -1;
    mem->allocated_stack_top = -1;
    mem->free_page_counter = 0;

    // Initialize all pages as free and push them onto stack
    for (int i = 0; i < mem->no_of_pages; i++) {
//        mem->free_pages[i] = i;
        mem->free_page_stack[++mem->free_stack_top] = i; // this is how we push onto the stack
        mem->free_page_counter++;
    }
}

/**
 * Calculates the number of frames required to allocate memory for a process.
 * 
 * @param process A pointer to the Process structure representing the process.
 * @return The number of frames required for the process.
 */
int calculate_pages(struct Process* process) {
    int page_size = 4;
    int process_size = process->process_size;

    // Use ceil() to round up the result
    int page_allocation = (int)ceil((double)process_size / page_size);

    return page_allocation;
}

/**
 * Allocates memory for a process in the logical memory using calloc.
 * Calloc gets the number of pages needed and assigns contiguous addresses
 * to the process
 * 
 * @param mem The logical memory structure.
 * @param process The process structure.
 * @returns returns a pointer to an integer array of size 3. The first index contains the status
 * code indicating if memory was sucessfully allocated (1 for success, -1 for failure, 0 if pages
 * were assigned, but no frames assigned).
 * The second index contains the number of pages/frames allocated. The third index contains
 * the number of bytes allocated
 */
int* _calloc(struct logical_memory* mem, struct Process* process){

    // Initialize return values and frames needed
    static int allocation[3] = {-1,0,0};
    int frames_needed = calculate_pages(process);

    // check if available resources are greater than process need
<<<<<<< Updated upstream
    if(frames_needed > mem->free_page_counter){
        printf("Not enough resources");
        return &allocation;
=======
    if(frames_needed > logical_mem->free_page_counter){
        printf("Not enough Virtual memory!\n");
        return allocation;
>>>>>>> Stashed changes
    }

    // pop pages from the free stack and allocate them to the process
    int allocated_pages[frames_needed];
    for(int i = 0; i < frames_needed; i++ ){
<<<<<<< Updated upstream
        allocated_pages[i] = mem->free_page_stack[mem->free_stack_top]; //pop
        mem->free_stack_top--; //reduce top
        mem->free_page_counter--;
=======
        allocated_pages[i] = logical_mem->free_page_stack[logical_mem->free_stack_top]; //pop
        logical_mem->free_stack_top--; //reduce top
        logical_mem->free_page_counter--;
    }

    // Checkk if enough pages are available
    if(frames_needed > physical_mem->free_frame_counter){
        allocation[0] = 0;
        printf("Not enough Physical memory!\n");
        return allocation;
    }

    // pop frames from the free frame stack and allocate them
    int allocated_frames[frames_needed];
    for(int i = 0; i < frames_needed; i++ ){
        allocated_frames[i] = physical_mem->free_frame_stack[physical_mem->free_stack_top]; //pop
        physical_mem->free_stack_top--; //reduce top
        physical_mem->free_frame_counter--;
>>>>>>> Stashed changes
    }

    // push allocated pages onto the allocated stack
    for(int i = frames_needed - 1; i >= 0; i--){
        mem->allocated_stack_top++;
        mem->allocated_page_stack[mem->allocated_stack_top] = allocated_pages[i];
    }

    // Update the page table for the process
    for(int i = 0; i < frames_needed; i++){
<<<<<<< Updated upstream
        process->page_table[i].frame_number = allocated_pages[i];
        process->page_table[i].valid = 1;
=======
        process->page_table->page_table_entry[i].frame_number = allocated_pages[i];
        process->page_table->page_table_entry[i].valid = 1;
    }
    // print_page_table(process);
    process->no_of_frames_allocated = frames_needed;

    // Update the frames in physical memory
    for(int i = 0; i < frames_needed; i++){
        physical_mem->frames[allocated_frames[i]].allocated = 1;
>>>>>>> Stashed changes
    }

    // Update return value
    allocation[0] = 1;
    allocation[1] = frames_needed;
    allocation[2] = frames_needed * 4;

<<<<<<< Updated upstream
    return &allocation;

=======
    return allocation;
>>>>>>> Stashed changes
}





