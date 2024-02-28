//
// Created by omar on 2/26/24.
//

#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include "page_table.h"
#include "process.h"

#define NUM_FRAMES 5
#define FRAME_SIZE 4
#define NUM_PAGES 5
#define PAGE_SIZE 4

#define MEMORY_SIZE (FRAME_SIZE * NUM_PAGES)

typedef int bool;
#define true 1
#define false 0

struct Frame{
    int frame_number;
    bool allocated;
};

struct physical_memory{
    int frame_size;
    int no_of_frames;
    int free_frames[NO_OF_FRAMES];
    int free_frame_stack[NO_OF_FRAMES];
    int free_stack_top;
    int free_frame_counter;
    int allocated_frame_stack[NO_OF_FRAMES];
    int allocated_stack_top;
    struct Process *current_process;
};

void initialize_physical_memory(struct physical_memory *mem);
int calculate_process_frames(struct Process *process);void visualize_physical_memory(const struct Frame* memory, int num_frames, int frame_size);

void print_physical_memory();
void allocate_process_frame(struct physical_memory *mem, struct Process *process);
void deallocate_process_frame(struct physical_memory *mem, struct Process *process);

#endif // PHYSICAL_MEMORY_H


