// logical_memory.h

#ifndef LOGICAL_MEMORY_H
#define LOGICAL_MEMORY_H

#include "process.h"

#define PAGE_SIZE 4
#define NO_OF_PAGES 256

struct logical_memory {
    int page_size;
    int no_of_pages;
//    int free_pages[NO_OF_PAGES];
    int free_page_stack[NO_OF_PAGES];
    int free_stack_top;
    int free_page_counter;
    int allocated_page_stack[NO_OF_PAGES];
    int allocated_stack_top;
};

void initialize_logical_memory(struct logical_memory* mem);
int calculate_pages(struct Process* process);
int* _calloc(struct logical_memory* mem, struct Process* process);
// void allocate_memory(struct logical_memory* mem, struct Process* process);

#endif // LOGICAL_MEMORY_H
