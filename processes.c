// Import Dependencies
#include "processes.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/** A function that allows the user to create an x number of processes
 * and assigns the size of each process
 */
void create_processes(int num_processes, int min_size, int max_size, int max_requests){

    for (int i = 0; i < num_processes; i++){
        pid_t pid = fork();

        if (pid <0){
            perror ("Process creation failed");
            exit(1);
        } else if (pid == 0){
            // child processes
            int process_size = rand() % (max_size - min_size + 1) + min_size; // generate random size for each process
            int num_requests = rand() % (max_requests) + 1
            access_random(process_size, num_requests);
            exit(0);
        } else{
            // parent process
            int parent_process_size = rand() % (max_size - min_size + 1) + min_size; // generate random size for each process
            int num_requests = rand() % (max_requests) + 1
            access_random(parent_process_size, num_requests);
            wait(NULL);
        }
    }
}

/**
 * Helper function to access the randomly generated size of a process
*/
void access_random(int process_size, int num_requests){
    printf("The process %d has a size of %d bytes\n",getpid(), process_size);
}