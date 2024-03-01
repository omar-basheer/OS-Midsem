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
  int max_memory_size = 69;


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
      printf("\nRequesting memory");
      process_request_memory(&processes[i], (int) processes[i].process_size , logical_memory, physical_memory, hierarchical_page_table);
  }

  // Execute processes
  for(int i = 0; i < num_processes; i++){
      printf("Executing Process: %d",i);
      execute_process(&processes[i]);
  }

  for (int i = 0; i < num_processes; i++) {
      printf("\nRequesting additional memory");
      process_request_memory(&processes[i], (int) processes[i].process_size , logical_memory, physical_memory, hierarchical_page_table);
  }

  // Execute processes
  for(int i = 0; i < num_processes; i++){
      printf("Executing Process: %d",i);
      execute_process(&processes[i]);
  }

  visualize_physical_memory(physical_memory);
  visualize_logical_memory(logical_memory);
  visualize_hierarchical_page_table();



  
}
