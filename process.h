#ifndef PROCESS_H
#define PROCESS_H

// Import Dependencies
#include <stdio.h>
#include <stdlib.h>
#include "page_table.h"
#include "logical_memory.h"
#include "physical_memory.h"

struct physical_memory;
struct PageTableEntry;

/**
 * @struct Process
 * @brief Represents a process in the operating system.
 * 
 * The Process struct contains information about a process, including its ID, size, request limit,
 * requested memory size, and page table entries.
 */
struct Process{
    int process_id;                     /**< The ID of the process. */
    int process_size;                   /**< The size of the process. */
    int process_request_limit;          /**< The request limit of the process. */
    int requested_memory_size;          /**< The size of memory requested by the process. */
    int requested; 
    int extra;
    struct PageTable* page_table;
    int no_of_frames_allocated;
    float total_memory_accesses;
    float total_hits;
    float total_misses;
};


// Function Prototypes
int generate_random_size(int max_size);
struct Process* create_processes(int num_processes, int max_memory_size);
void perform_memory_allocation(struct logical_memory* logical_mem, struct physical_memory* physical_mem, struct Process* process, int requested_memory_size);
void process_request_memory(struct Process* process, int requested_memory_size, struct logical_memory* logical_mem, struct physical_memory* physical_mem, struct PageTable* hierarchical_page_table[NUM_PAGES]);
void free_processes(struct Process* processes);
void execute_process(struct Process* process);
void process_stats(struct Process* process);

#endif /* PROCESS_H */
