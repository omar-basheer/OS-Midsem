//
// Created by omar on 2/26/24.
//
#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include "page_table.h"
#include "process.h"

#define NUM_FRAMES 7
#define FRAME_SIZE 5
#define NUM_PAGES 7
#define PAGE_SIZE 5
#define MEMORY_SIZE (FRAME_SIZE * NUM_FRAMES)

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
    struct Frame frames[NUM_FRAMES];
    int free_frame_stack[NUM_FRAMES];
    int free_stack_top;
    int free_frame_counter;
    int allocated_frame_stack[NUM_FRAMES];
    int allocated_stack_top;
    struct Process *current_process;
};

void initialize_physical_memory(struct physical_memory *mem);
void visualize_physical_memory(struct physical_memory *mem);
// int calculate_process_frames(struct Process *process);
// void visualize_physical_memory(const struct Frame* memory, int num_frames, int frame_size);
// void allocate_process_frame(struct physical_memory *mem, struct Process *process);
// void deallocate_process_frame(struct physical_memory *mem, struct Process *process);

#endif // PHYSICAL_MEMORY_H


