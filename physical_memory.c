//
// Created by sblan on 20/02/2024.
//physical_memory.c
// Import Dependencies
#include<stdio.h>
#include<stdlib.h>
#include "physical_memory.h"

/**
 * Initializes the physical memory by filling it with 0.
 * The memory size is defined by the constant MEMORY_SIZE.
 */
void initialize_physical_memory(struct physical_memory *mem){
    mem->frame_size = FRAME_SIZE;
    mem->no_of_frames = NUM_FRAMES;
    mem->free_stack_top = -1;
    mem->allocated_stack_top = -1;
    mem->free_frame_counter = NUM_FRAMES;

    // Initialize all frames as free and push them onto stack
    for (int i = 0; i < mem->no_of_frames; i++) {
        mem->frames[i].frame_number = i;
        mem->frames[i].allocated = false;
        mem->free_frame_stack[++mem->free_stack_top] = i; // this is how we push onto the stack
    }
}

/**
 * Visualizes the physical memory by printing the contents of each frame.
 *
 * @param memory The array of frames representing the physical memory.
 * @param num_frames The number of frames in the physical memory.
 * @param frame_size The size of each frame in bytes.
 */
void visualize_physical_memory(struct physical_memory *mem) {
    printf("\nPhysical Memory :\n");

    // Header row
    printf("     | Frame Size |  Num Frames |    Free Frames   | Allocated Frames\n");
    printf("-----+------------+-------------+------------------+------------------\n");

    // Content rows
    printf("     |     %d      |       %d     |", mem->frame_size, mem->free_frame_counter);

    // Display free pages
    if (mem->free_stack_top == -1) {
        printf("None");
    } else {
        printf("  [");
        for (int i = 0; i <= mem->free_stack_top; i++) {
            printf("%d%s", mem->frames[i].frame_number, (i < mem->free_stack_top) ? ", " : "");
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
            printf("%d%s", mem->allocated_frame_stack[i], (i < mem->allocated_stack_top) ? ", " : "");
        }
        printf("]");
    }

    printf("\n");
    printf("\n");
}

/**
 * Deallocates a frame in physical memory and updates the page table.
 *
 */
// void deallocate_frame(struct physical_memory *mem, struct Process *process) {
//     if (mem->allocated_stack_top >= 0) {
//         // Deallocate a frame
//         int frame_number = mem->allocated_frame_stack[mem->allocated_stack_top--];
//         mem->free_frame_stack[++mem->free_stack_top] = frame_number;

//         // Update the page table to indicate that the frame is now free
//         struct Page *page_table = access_process_page_table(mem->current_process);
//         page_table[page_number]->frame_number = -1;
//         page_table[page_number]->valid = false;

//         mem->current_process = NULL;

//         // Update the counters
//         mem->free_frame_counter++;
//         printf("Deallocated Frame %d\n", frame_number);
//     } else {
//         printf("Error: No frames to allocate\n");
//     }
// }




// void visualize_physical_memory(const struct Frame* memory, int num_frames, int frame_size) {
//     printf("Physical Memory (%d bytes per frame):\n", frame_size);

//     // Header row
//     printf("  | ");
//     for (int i = 0; i < num_frames; i++) {
//         printf("Frame %d | ", i);
//     }
//     printf("\n");
//     printf("--+---------+---------+---------+---------+---------+--\n");

//     // Content rows
//     for (int i = 0; i < frame_size; i++) {
//         printf("  |   ");
//         for (int j = 0; j < num_frames; j++) {
//             printf("%02X    |   ", memory[j].data); // Print data in hexadecimal format
//         }
//         printf("\n");
//         }
// }


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

