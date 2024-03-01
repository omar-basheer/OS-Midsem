//
// Created by sblan on 20/02/2024.
//physical_memory.c
// Import Dependencies
#include<stdio.h>
#include<stdlib.h>
#include "physical_memory.h"

struct PageTable* hierarchical_page_table[NUM_PAGES];

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
        mem->free_frame_stack[++mem->free_stack_top] = i; // this is how we push onto the stack
    }
}


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
 * Handles page faults and uses the LRU page replacement algorithm.
 *
 * @param page_number The page number to allocate a frame for.
 */
void handle_page_fault(int page_number, struct Process* process) {
    // Check if the page is already in physical memory
    if (process->page_table->page_table_entry->valid) {
        printf("Page %d is already in physical memory (No page fault)\n", page_number);
    } else {
        printf("Page Fault! Page%d not in physical memory\n", page_number);
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

        // Update the page table to indicate that the frame is now free
        struct Page *page_table = access_process_page_table(mem->current_process);
        process->page_table->page_table_entry->frame_number = -1;
        process->page_table->page_table_entry->valid = false;

        mem->current_process = NULL;

        // Update the counters
        mem->free_frame_counter++;
        printf("Deallocated Frame %d\n", frame_number);
    } else {
        printf("Error: No frames to allocate\n");
    }
}


