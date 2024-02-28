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
#define NUM_PAGES 5


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
    mem->free_page_counter = 0;

    // Initialize all pages as free and push them onto stack
    for (int i = 0; i < mem->no_of_pages; i++) {
        mem->free_pages[i] = i;
        mem->free_page_stack[++mem->free_stack_top] = i; // this is how we push onto the stack
        mem->free_page_counter++;
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
void _calloc(struct logical_memory* mem, struct Process* process){

    int frames_needed = calculate_frames(process);

    // check if available resources are greater than need
    if(mem->free_page_counter < frames_needed){
        printf("Not enough resources");
        return;
    }

    // pop pages from the free stack and allocate them to the process
    int allocated_pages[frames_needed];
    for(int i = 0; i < frames_needed; i++ ){
        allocated_pages[i] = mem->free_page_stack[mem->free_stack_top--]; 
        mem->free_pages[allocated_pages[i]] = 0;
    }

    // push allocated pages onto the allocated stack
    for(int i = frames_needed - 1; i >= 0; i--){
        mem->allocated_stack_top++;
        mem->allocated_page_stack[mem->allocated_stack_top] = allocated_pages[i];
    }

    // Update the page table for the process
    for(int i = 0; i < frames_needed; i++){
        process->page_table[i].page_table->frame_number = allocated_pages[i];
        process->page_table[i].page_table->valid = 1;
    }

}

//TODO implement malloc with above doc string
// void malloc()


