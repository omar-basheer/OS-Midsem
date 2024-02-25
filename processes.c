// Import Dependencies
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int process_id;
    int process_size;
    int process_request_limit;
    //TODO implement request size

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

    }
    return processes;
}