//
// Created by sblan on 20/02/2024.
//

// Import Dependencies
#include "physical_memory.h"
#include<stdio.h>

/**
 * Initializes the physical memory by filling it with 0.
 * The memory size is defined by the constant MEMORY_SIZE.
 */
void initialize_physical_memory(struct physical_memory *mem){
    mem->frame_size = FRAME_SIZE;
    mem->no_of_frames = NO_OF_FRAMES;
    mem->free_stack_top = -1;
    mem->allocated_stack_top = -1;
    mem->free_frame_counter = NO_OF_FRAMES;

    // Initialize all frames as free and push them onto stack
    for (int i = 0; i < mem->no_of_frames; i++) {
        mem->free_frames[i] = i;
        mem->free_frame_stack[++mem->free_stack_top] = i; // this is how we push onto the stack
    }
}

int calculate_process_frames(struct Process *process){
    int process_size = process->process_size;

    // Use ceil() to round up the result
    int frame_allocation = (int)ceil((double)process_size + FRAME_SIZE - 1/ FRAME_SIZE);

    return frame_allocation;
}

/**
 * Allocates a frame in physical memory and updates the page table.
 *
 */
void allocate_process_frame(struct physical_memory *mem, struct Process *process){
    if(mem->free_stack_top >= 0){
        int frame_number = mem->free_frame_stack[mem->free_stack_top--];
        mem->allocated_frame_stack[++mem->allocated_stack_top] = frame_number;

        mem->current_process = process;

        // Update the page table with the allocated frame number
        struct Page *page_table_entry = access_process_page_table(mem->current_process);
        page_table_entry->frame_number = frame_number;
        page_table_entry->valid = true;

        mem->free_frame_counter--;
        printf("Allocated Frame %d for Page\n", frame_number);
    } else{
        printf("No available frames for Page\n");
    }
}

/**
 * Deallocates a frame in physical memory and updates the page table.
 *
 */
void deallocate_frame(struct physical_memory *mem, struct Process *process) {
    if (mem->allocated_stack_top >= 0) {
        // Deallocate a frame
        int frame_number = mem->allocated_frame_stack[mem->allocated_stack_top--];
        mem->free_frame_stack[++mem->free_stack_top] = frame_number;

        mem->current_process = NULL;

        // Update the page table to indicate that the frame is now free
        struct Page *page_table_entry = access_process_page_table(mem->current_process);
        page_table_entry->valid = false;

        // Update the counters
        mem->free_frame_counter++;
        printf("Deallocated Frame %d\n", frame_number);
    } else {
        printf("Error: No frames to allocate\n");
    }
}







// void memory_access(int address) {
//     int page_number = address / PAGE_SIZE;
//     int page_offset = address % PAGE_SIZE;

//     printf("Accessing address %d: Page number %d, Offset %d, Frame number %d\n",address, page_number, page_offset, page_table[page_number].frame_number);

//     // populate the page table if the page is not valid
//     if (page_table[page_number].valid){
//         // access memory
//         char data = physical_memory[page_table[page_number].frame_number * PAGE_SIZE + page_offset];
//         printf("Data: %c\n", data);
//     }
//     else{
//         printf("Page fault: Page %d is not in memory\n", page_number);
//         // find free frame
//         int free_frame = -1;
//         for(int j = 0; j < NUM_PAGES; j++) {
//             if (page_table[j].frame_number == -1) {
//                 free_frame = j;
//                 break;
//             }
//         }

//         if (free_frame != -1){
//             // allocate the free frame and mark it as valid 
//             page_table[page_number].frame_number = free_frame;
//             page_table[page_number].valid = 1;

//             printf("Page %d allocated to frame %d\n", page_number, free_frame);

//             // Accessing memory after page table population
//             char data = physical_memory[page_table[page_number].frame_number * PAGE_SIZE + page_offset];
//             printf("Data: %c\n", data);
//         }
//         else {
//             printf("Error: No free frames available\n");
//             return;
//         }
//     }

// }

