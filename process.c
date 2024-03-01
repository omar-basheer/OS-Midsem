// Import Dependencies
#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "page_table.h"
<<<<<<< Updated upstream
#include "logical_memory.h"
=======
#include <unistd.h>
// #include "logical_memory.h"
// #include "physical_memory.h"
>>>>>>> Stashed changes

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

    for (int i = 0; i < num_processes; i++) {
        processes[i].process_id = i;
        processes[i].process_size = generate_random_size(max_memory_size);
        processes[i].process_request_limit = rand() % 5 + 1;
<<<<<<< Updated upstream
        processes[i].requested_memory_size = 0;
        init_page_table(&processes[i]);
=======
        processes[i].requested_memory_size = 1;
        initialize_page_table(&processes[i]);
        processes->no_of_frames_allocated=0;
        processes[i].total_memory_accesses = 0;
        processes[i].total_hits = 0;
        processes[i].total_misses = 0;
>>>>>>> Stashed changes
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
void process_request_memory(struct Process* process, int requested_memory_size, struct logical_memory* mem) {
//    if (process->process_request_limit > 0 && requested_memory_size <= process->process_size) {

        printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n");
        // Request for memory
        int* calloc = _calloc(mem, process);


        int allocated_size = calloc[2];
        int status = calloc[0];
        printf("Status -> %d \n",status);

        if(status == 1) {
            printf("Process %d: Requested memory successfully allocated (%d Bytes)\n", process->process_id,
                   allocated_size);
            process->process_request_limit--;
            process->requested_memory_size = requested_memory_size; // Update requested memory size
        } else {
        printf("Process %d: Memory request failed.\n", process->process_id);
    }
}

/** Translates a virtual address to a physical addrss
 *
 * @param process Takes a pointer to a process
 * @param page_number Takes the virtual address/page number
 * @return returns the translated addresss
 */
int translate_address(struct Process* process, int page_number){
    return process->page_table->page_table_entry[page_number].frame_number;
}

/** Executes a process with varying access patterns
 *
 * @param process A pointer to the process that is to be executed
 */
void execute_process(struct Process* process) {
    int no_of_frames = process->no_of_frames_allocated;

    // Randomly Decicde access pattern
    int access_pattern = rand() % 2 + 1;;

    // Access using sequential access
    if (access_pattern == 1) {
    for (int i = 0; i < no_of_frames; i++) {
        if(translate_address(process,i) > 0){ //page hit
            process->total_memory_accesses++;
            process->total_hits++;
            sleep(0.25);
        } else{ //page fault
            process->total_memory_accesses++;
            process->total_misses++;
        }
    }
    // Access memory 1.5 times
        } else{
        for (int i = 0; i < no_of_frames*1.5; i++) {
            if(translate_address(process,i) > 0){ //page hit
                process->total_memory_accesses++;
                process->total_hits++;
                sleep(0.25);
            } else{ //page fault
                process->total_memory_accesses++;
                process->total_misses++;
            }
        }
    }


    printf("\n Process Execution Complete \n");
    process_stats(process); // Calculate and display process stats

}

void process_stats(struct Process* process){
    int total_accesses = process->total_memory_accesses;
    float hit_rate = (process->total_hits/total_accesses) * 100;
    float miss_rate = (process->total_misses/total_accesses) * 100;

    printf("Process %d Statistics: \n",process->process_id);
    printf("Total Memory Access Attempts: %d\n",total_accesses);
    printf("Hit Rate: %f \n",hit_rate);
    printf("Miss Rate: %f \n \n",miss_rate);
}


// Function to free allocated memory for processes
void free_processes(struct Process* processes) {
    free(processes);
}







