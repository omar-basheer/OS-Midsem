// Import Dependencies
#include <stdio.h>
#include <stdlib.h>
#include "page_table.c"

/**
 * @struct Process
 * @brief Represents a process in the operating system.
 * 
 * The Process struct contains information about a process, including its ID, size, request limit,
 * requested memory size, and page table entries.
 */
typedef struct{
    int process_id;                     /**< The ID of the process. */
    int process_size;                   /**< The size of the process. */
    int process_request_limit;          /**< The request limit of the process. */
    int requested_memory_size;          /**< The size of memory requested by the process. */
    PageTableEntry page_table[NUM_PAGES]; /**< The page table entries for the process. */
} Process;

/**
 * Generates a random size within the specified maximum size.
 *
 * @param max_size The maximum size for the random number.
 * @return The randomly generated size.
 */
int generate_random_size(int max_size) {
    return rand() % max_size + 1;
}

/**
 * Creates an array of processes.
 *
 * @param num_processes The number of processes to create.
 * @param max_memory_size The maximum memory size for each process.
 * @return A pointer to the array of processes.
 */
Process* create_processes(int num_processes, int max_memory_size) {
    Process* processes = (Process*)defined_malloc(num_processes * sizeof(Process)); // our own malloc function

    for (int i = 0; i < num_processes; i++) {
        processes[i].process_id = i;
        processes[i].process_size = generate_random_size(max_memory_size);
        processes[i].process_request_limit = processes[i].process_size / 100;
        processes[i].requested_memory_size = 0;
        init_page_table(&processes[i]);
    }

    return processes;
}

/**
 * Allocates memory for a process based on the requested memory size.
 * 
 * @param process The process for which memory is being allocated.
 * @param requested_memory_size The size of memory requested by the process.
 */
void process_request_memory(Process* process, int requested_memory_size) {
    if (process->process_request_limit > 0 && requested_memory_size <= process->process_size) {
        
        printf("Process %d: Requested memory successfully allocated (%d MB)\n", process->process_id, requested_memory_size);
        process->process_request_limit--;
        process->requested_memory_size = requested_memory_size; // Update requested memory size
    } else {
        printf("Process %d: Memory request failed.\n", process->process_id);
    }
}

// Function to free allocated memory for processes
void free_processes(Process* processes) {
    free(processes);
}

