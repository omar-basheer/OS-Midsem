#ifndef PROCESS_H
#define PROCESS_H

// Import Dependencies
#include <stdio.h>
#include <stdlib.h>
#include "page_table.h"
#include "logical_memory.h"

struct Page;

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
<<<<<<< Updated upstream
    struct Page page_table[NUM_PAGES]; /**< The page table entries for the process. */
=======
    struct PageTable* page_table;
    int no_of_frames_allocated;
    int total_memory_accesses;
    int total_hits;
    int total_misses;
>>>>>>> Stashed changes
};

// Function Prototypes
int generate_random_size(int max_size);
struct Process* create_processes(int num_processes, int max_memory_size);
void process_request_memory(struct Process* process, int requested_memory_size, struct logical_memory* mem);
void free_processes(struct Process* processes);
void execute_process(struct Process* process);
void process_stats(struct Process* process);

#endif /* PROCESS_H */
