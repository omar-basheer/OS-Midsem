#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "process.h"
#include "logical_memory.h"

#include "physical_memory.h"
#include <unistd.h>

int main(){
  srand((unsigned int)time(NULL));

  int num_processes = 4;
  int max_memory_size = 10;

  struct physical_memory physical_memory_instance;
  struct physical_memory* physical_memory = &physical_memory_instance;

  initialize_physical_memory(physical_memory);
  visualize_physical_memory(physical_memory);

  struct logical_memory logical_memory_instance;
  struct logical_memory* logical_memory = &logical_memory_instance;

  initialize_logical_memory(logical_memory);
  visualize_logical_memory(logical_memory);

  for (int i = 0; i < NUM_PAGES; i++) {
      hierarchical_page_table[i] = NULL;
  }

  // Create processes
  struct Process* processes = create_processes(num_processes, max_memory_size);
  visualize_hierarchical_page_table();  

  for (int i = 0; i < num_processes; i++) {
      printf("\nProcess %d: Size %d, Request Limit %d\n", processes[i].process_id, processes[i].process_size, processes[i].process_request_limit);
      print_page_table(&processes[i]);

      // Allocate memory to each process
      printf("Requesting memory");
//      sleep(2);
      process_request_memory(&processes[i], (int) processes[i].process_size ,&mem);


  }

}
