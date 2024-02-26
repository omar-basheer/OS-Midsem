#ifndef PROCESS_H
#define PROCESS_H

// Import Dependencies
#include <stdio.h>
#include <stdlib.h>

// Constants
#define NUM_PAGES 100 // Assuming this is defined elsewhere if not, it should be defined

// Structs
typedef struct PageTableEntry {
    int page_number;
    int frame_number;
    int is_valid;
} PageTableEntry;

typedef struct Process {
    int process_id;
    int process_size;
    int process_request_limit;
    int requested_memory_size;
    PageTableEntry page_table[NUM_PAGES];
} Process;

// Function Prototypes
int generate_random_size(int max_size);
Process* create_processes(int num_processes, int max_memory_size);
void process_request_memory(Process* process, int requested_memory_size);
void free_processes(Process* processes);

#endif /* PROCESS_H */
