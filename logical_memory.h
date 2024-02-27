#ifndef LOGICAL_MEMORY_H
#define LOGICAL_MEMORY_H

#define PAGE_SIZE 4
#define NUM_PAGES 5

/**
 * @struct logical_memory
 * @brief Represents the logical memory structure.
 * 
 * This structure contains information about the logical memory, including the page size,
 * the number of pages, the array representing the total logical address space, the array
 * of free pages, the array of allocated pages, and the free page counter, all for a particular process.
 * In this isntance, the memory size is 1024 bytes (page size * number of pages).
 */
struct logical_memory {
    int page_size;
    int no_of_pages;
    int free_pages[NUM_PAGES];
    int free_page_stack[NUM_PAGES];
    int free_stack_top;
    int free_page_counter;
    int allocated_page_stack[NUM_PAGES];
    int allocated_stack_top;
};

void initialize_logical_memory(struct logical_memory* mem);
void visualize_logical_memory(struct logical_memory* mem);
int calculate_frames(struct Process* process);
void _calloc(struct logical_memory* mem, struct Process* process);
// void allocate_memory(struct logical_memory* mem, struct Process* process);

#endif // LOGICAL_MEMORY_H
