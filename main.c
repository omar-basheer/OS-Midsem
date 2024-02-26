#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "processes.h"


int main(){
  srand((unsigned int)time(NULL));

  int num_processes = 5;
  int max_memory_size = 100;

  Process* processes = create_processes(num_processes, max_memory_size);

  for (int i = 0; i < num_processes; i++) {
      printf("Process %d: Size %d, Request Limit %d\n", processes[i].process_id, processes[i].process_size, processes[i].process_request_limit);
  } 
}
