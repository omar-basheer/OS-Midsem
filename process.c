// process.c
// Import Dependencies
#include <stdio.h>
#include <stdlib.h>
#include "process.h"
#include "page_table.h"

#include <unistd.h>

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
        // processes[i].process_size = generate_random_size(max_memory_size);
        processes[i].process_size = 5;
        processes[i].process_request_limit = rand() % 5 + 1;
        processes[i].requested_memory_size = 1;
        initialize_page_table(&processes[i]);
        processes[i].requested = 0;
        processes[i].extra = 1;
        processes[i].no_of_frames_allocated=0;
        processes[i].total_memory_accesses = 0;
        processes[i].total_hits = 0;
        processes[i].total_misses = 0;

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
void process_request_memory(struct Process* process, int requested_memory_size, struct logical_memory* logical_mem, struct physical_memory* physical_mem, struct PageTable* hierarchical_page_table[NUM_PAGES]) {
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n");
    if (process->requested == 1){
        if (process->extra == 0) {
            printf("Process %d: No extra memory needed.\n", process->process_id);
            perform_memory_allocation(logical_mem, physical_mem, process, requested_memory_size);
            return;
        }else{
            // Generate a random number to add to the current process size
            int extra_memory = rand() % 10;
            printf("Process %d: Size: %d Requesting exta memory of size %d\n", process->process_id, process->process_size, 5);
            requested_memory_size = 5;
            perform_memory_allocation(logical_mem, physical_mem, process, requested_memory_size);
        }
        // printf("Process %d: Size: %d Requesting exta memory of size %d\n", process->process_id, extra_memory, requested_memory_size-extra_memory);
        // requested_memory_size += extra_memory;
    }
    perform_memory_allocation(logical_mem, physical_mem, process, requested_memory_size);
}

void perform_memory_allocation(struct logical_memory* logical_mem, struct physical_memory* physical_mem, struct Process* process, int requested_memory_size) {
    // Perform memory allocation
    int* calloc_result = _calloc(logical_mem, physical_mem, process, requested_memory_size);

    // Extract the relevant information from the allocation result
    int allocated_size = calloc_result[2];
    int status = calloc_result[0];
    int num_pages = calloc_result[1];

    // Print status message
    printf("Status -> %d\n", status);
    if (status == 1) {
        printf("Process %d, Size %d: Requested memory successfully.\nAllocated (%d Bytes -> %d Page(s))\n", process->process_id, process->process_size, allocated_size, num_pages);
        process->process_request_limit--;
        process->requested_memory_size = requested_memory_size; // Update requested memory size
        process->requested = 1;
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
            if(translate_address(process,i) >= 0){ //page hit
                process->total_memory_accesses++;
                process->total_hits++;
                sleep(1);
            } else{ //page fault
                process->total_memory_accesses++;
                process->total_misses++;
            }
        }
    // Access memory 1.5 times
    } else{
        for (int i = 0; i < no_of_frames*1.5; i++) {
            if(translate_address(process,i) >= 0){ //page hit
                process->total_memory_accesses++;
                process->total_hits++;
                sleep(1);
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
    float total_accesses = process->total_memory_accesses;
    float hit_rate = (process->total_hits/total_accesses) * 100;
    float miss_rate = (process->total_misses/total_accesses) * 100;

    printf("\n");
    printf("Process %d Statistics: \n",process->process_id);
    printf("Total Memory Access Attempts: %f\n",total_accesses);
    printf("Total Hits: %f \n",process->total_hits);
    printf("Hit Rate: %f \n",hit_rate);
    printf("Total Misses: %f \n",process->total_misses);
    printf("Miss Rate: %f \n \n",miss_rate);

}

// Function to free allocated memory for processes
void free_processes(struct Process* processes) {
    free(processes);
}


        // Request for memory
        // int* calloc = _calloc(logical_mem, physical_mem, process);

        // int allocated_size = calloc[2];
        // int status = calloc[0];
        // int num_pages = calloc[1];
        // printf("Status -> %d \n",status);

        // if(status == 1) {
        //     printf("Process %d, Size %d: Requested memory successfully. \n Allocated (%d Bytes -> %d Page(s) )\n", process->process_id, process->process_size, allocated_size, num_pages);
        //     process->process_request_limit--;
        //     process->requested_memory_size = requested_memory_size; // Update requested memory size
        //     process->requested = 1;
        // } else {
        // printf("Process %d: Memory request failed.\n", process->process_id);
        // }




