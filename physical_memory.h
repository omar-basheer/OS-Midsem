//
// Created by omar on 2/26/24.
//

#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include "page_table.h"

#define NUM_FRAMES 5
#define FRAME_SIZE 4
#define NUM_PAGES 128
#define MEMORY_SIZE (FRAME_SIZE * NUM_PAGES)

struct Frame{
    int data;
};

extern struct Frame physical_memory[NUM_FRAMES];

void print_physical_memory();








#endif PHYSICAL_MEMORY_H


