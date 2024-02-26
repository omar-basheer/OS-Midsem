// Import Dependencies
#include <stdio.h>
#include <stdlib.h>

/** A struct that models a process **/
typedef struct{
    int process_id;
    int process_size;
    int process_request_limit;
    int requested_memory_size;
} Process;

// Function to generate a random process size
int generate_random_size(int max_size) {
    return rand() % max_size + 1;
}

// Function to create processes
Process* create_processes(int num_processes, int max_memory_size) {
    Process* processes = (Process*)defined_malloc(num_processes * sizeof(Process)); // our own malloc function

    for (int i = 0; i < num_processes; i++) {
        processes[i].process_id = i;
        processes[i].process_size = generate_random_size(max_memory_size);
        processes[i].process_request_limit = processes[i].process_size / 100;
        processes[i].requested_memory_size = 0;
    }
    return processes;
}

// Function for a process to request memory
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

