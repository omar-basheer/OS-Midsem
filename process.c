// process.c
// Import Dependencies
#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "page_table.h"
// #include "logical_memory.h"
// #include "physical_memory.h"

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
struct Process* create_processes(int num_processes, int max_memory_size) {
    struct Process* processes = (struct Process*)malloc(num_processes * sizeof(struct Process));
    if (processes == NULL) {
        printf("Error: Memory allocation failed for processes\n");
        return NULL;
    }
    
    for (int i = 0; i < num_processes; i++) {
        processes[i].process_id = i;
        processes[i].process_size = generate_random_size(max_memory_size);
        processes[i].process_request_limit = rand() % 5 + 1;
        processes[i].requested_memory_size = 0;
        initialize_page_table(&processes[i]);
    }
    return processes;
}

/**
 * Allocates memory for a process based on the requested memory size.
 * 
 * @param process The process for which memory is being allocated.
 * @param requested_memory_size The size of memory requested by the process.
 * @param mem Instance of the logical memory struct
 */
void process_request_memory(struct Process* process, int requested_memory_size, struct logical_memory* logical_mem, struct physical_memory* physical_mem) {
//    if (process->process_request_limit > 0 && requested_memory_size <= process->process_size) {

        printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n");
        // Request for memory
        int* calloc = _calloc(logical_mem, physical_mem, process);

        int allocated_size = calloc[2];
        int status = calloc[0];
        printf("Status -> %d \n",status);

        if(status == 1) {
            printf("Process %d: Requested memory successfully allocated (%d Bytes)\n", process->process_id, allocated_size);
            process->process_request_limit--;
            process->requested_memory_size = requested_memory_size; // Update requested memory size
        } else {
        printf("Process %d: Memory request failed.\n", process->process_id);
    }
}

// Function to free allocated memory for processes
void free_processes(struct Process* processes) {
    free(processes);
}




