//
// Created by sblan on 20/02/2024.
// logical_memory.c

// Import Dependencies
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "process.h"
#include "logical_memory.h"
// #include "physical_memory.h"


#define PAGE_SIZE 5
#define NUM_PAGES 7


/**
 * Initializes the logical memory structure.
 * 
 * @param mem Pointer to the logical memory structure to be initialized.
 */
void initialize_logical_memory(struct logical_memory* mem) {
    mem->page_size = PAGE_SIZE;
    mem->no_of_pages = NUM_PAGES;
    mem->free_stack_top = -1;
    mem->allocated_stack_top = -1;
    mem->free_page_counter = NUM_PAGES;

    // Initialize all pages as free and push them onto stack
    for (int i = 0; i < mem->no_of_pages; i++) {
        mem->free_pages[i] = i;
        mem->free_page_stack[++mem->free_stack_top] = i; // this is how we push onto the stack
    }
}

void visualize_logical_memory(struct logical_memory* mem) {
    printf("Logical Memory :\n");

    // Header row
    printf("     | Page Size |  Num Pages |    Free Pages   | Allocated Pages\n");
    printf("-----+-----------+------------+-----------------+-----------------\n");

    // Content rows
    printf("     |    %d      |      %d     |", mem->page_size, mem->free_page_counter);

    // Display free pages
    if (mem->free_stack_top == -1) {
        printf("None");
    } else {
        printf(" [");
        for (int i = 0; i <= mem->free_stack_top; i++) {
            printf("%d%s", mem->free_pages[i], (i < mem->free_stack_top) ? ", " : "");
        }
        printf("]");
    }

    printf(" | ");

    // Display allocated pages
    if (mem->allocated_stack_top == -1) {
        printf("None");
    } else {
        printf(" [");
        for (int i = 0; i <= mem->allocated_stack_top; i++) {
            printf("%d%s", mem->allocated_page_stack[i], (i < mem->allocated_stack_top) ? ", " : "");
        }
        printf("]");
    }

    printf("\n");
    printf("\n");
}

/**
 * Calculates the number of frames required to allocate memory for a process.
 * 
 * @param process A pointer to the Process structure representing the process.
 * @return The number of frames required for the process.
 */
int calculate_frames(struct Process* process) {
    int process_size = process->process_size;
    int page_allocation = (int)ceil((double)process_size / PAGE_SIZE);
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
int* _calloc(struct logical_memory* logical_mem, struct physical_memory* physical_mem, struct Process* process){

    // Initialize return values and frames needed
    // static int allocation[3] = {-1,0,0};
    int* allocation = (int*)malloc(3 * sizeof(int));
    if (allocation == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    allocation[0] = -1; // Default value indicating failure
    allocation[1] = 0;
    allocation[2] = 0;

    int frames_needed = calculate_frames(process);

    // check if available resources are greater than process need
    if(frames_needed > logical_mem->free_page_counter){
        printf("Not enough Virtual memory!\n");

    }

    // pop pages from the free stack and allocate them to the process
    int allocated_pages[frames_needed];
    for(int i = 0; i < frames_needed; i++ ){
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
    }

    // push allocated pages onto the allocated stack
    for(int i = frames_needed - 1; i >= 0; i--){
        logical_mem->allocated_stack_top++;
        logical_mem->allocated_page_stack[logical_mem->allocated_stack_top] = allocated_pages[i];
    }

    // push allocated frames onto the allocated stack
    for(int i = frames_needed - 1; i >= 0; i--){
        physical_mem->allocated_stack_top++;
        physical_mem->allocated_frame_stack[physical_mem->allocated_stack_top] = allocated_frames[i];
    }

    // Update the page table for the process
    for(int i = 0; i < frames_needed; i++){
        process->page_table->page_table_entry[i].frame_number = allocated_pages[i];
        process->page_table->page_table_entry[i].valid = 1;
    }
    // print_page_table(process);

    process->no_of_frames_allocated = frames_needed;


    // Update the frames in physical memory
    for(int i = 0; i < frames_needed; i++){
        physical_mem->frames[allocated_frames[i]].allocated = 1;
    }

    // Update return value
    allocation[0] = 1;
    allocation[1] = frames_needed;
    allocation[2] = frames_needed * 4;

    return allocation;

}





