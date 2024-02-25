//
// Created by sblan on 20/02/2024.
//

// Import Dependencies
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PAGE_SIZE 4
#define NO_OF_PAGES 256

/** A struct that models the physical memory/ram of a computer
 *  In this isntance, the memory size is 1024 bytes **/
struct logical_memory {
    int page_size; // 4 bytes
    int no_of_pages;
//    int logical_space[NO_OF_PAGES]; // Array that represents the total logical address space
    int free_pages[NO_OF_PAGES];
    int allocated_pages[NO_OF_PAGES];
    int free_page_counter;
};

/** A function that initializes the variables for each
 * instanceof the stract
 * @param mem Pointer to an instance of the logical_memory struct
 */
void initialize_logical_memory(struct logical_memory* mem) {
    mem->page_size = PAGE_SIZE;
    mem->no_of_pages = NO_OF_PAGES;
    mem->free_page_counter = 0;

    // Populate the free address array
    for (int i = 0; i < mem->no_of_blocks; i++) {
        mem->free_pages[i] = i;
        mem->free_page_counter++;
    }
}


/** A function that calculates the number of frames needed by a process **/
int calculate_frames(struct processes* process) {
    int page_size = 4;
    int process_size = process->process_size;

    // Use ceil() to round up the result
    int frame_allocation = (int)ceil((double)process_size / page_size);

    return frame_allocation;
}


/** Calloc gets the number of pages needed and assigns contiguous addresses
 * to the process **/
void calloc(struct logical_memory* mem, struct processes *process){

    int frames_needed = calculate_frames(process);

    // check if avaialble resources are greater than need
    if(mem->free_page_counter < frames_needed){
        printf('Not enough resources')
        return;
    }

    // A for loop that attempts to assign address spaces contiguously
    for(int i = 0; i < frames_needed; i++ ){

    }

}


/** Converts a logical address to a page number **/
int[] logical_address_to_page(struct logical_memory *obj){

    // Get exponents of address space and page size
    int m = obj->m;
    int n = obj->n;

   // Calculate page number
   int page_number = m - n;
   int page_offset = n;

   // Store values in array
   int[2] translated_address = {page_number, page_offset};

   return translated_address;
}


//TODO implement malloc with above doc string