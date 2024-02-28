#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "process.h"
#include "physical_memory.h"
#include "logical_memory.h"



int main(){
  srand((unsigned int)time(NULL));

  int num_processes = 5;
  int max_memory_size = 100;


  init_physical_memory();
  visualize_physical_memory(physical_memory, NUM_FRAMES, FRAME_SIZE);

  struct logical_memory logical_memory_instance;
  struct logical_memory* logical_memory = &logical_memory_instance;
  initialize_logical_memory(logical_memory);
  visualize_logical_memory(logical_memory);

  for (int i = 0; i < NUM_PAGES; i++) {
      hierarchical_page_table[i] = NULL;
  }

  struct Process* processes = create_processes(num_processes, max_memory_size);

  for (int i = 0; i < num_processes; i++) {
      printf("Process %d: Size %d, Request Limit %d\n", processes[i].process_id, processes[i].process_size, processes[i].process_request_limit);
      print_page_table(&processes[i]);
  } 
}
