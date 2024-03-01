#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "process.h"
#include "logical_memory.h"
#include <unistd.h>

int main(){
  srand((unsigned int)time(NULL));

  // Declare variables
  int num_processes = 5;
  int max_memory_size = 100;
  struct logical_memory mem;
  initialize_logical_memory(&mem);

  // Create processes
  struct Process* processes = create_processes(num_processes, max_memory_size);

  for (int i = 0; i < num_processes; i++) {
      printf("\nProcess %d: Size %d, Request Limit %d\n", processes[i].process_id, processes[i].process_size, processes[i].process_request_limit);
      print_page_table(&processes[i]);

      // Allocate memory to each process
<<<<<<< Updated upstream
      printf("Requesting memory");
//      sleep(2);
      process_request_memory(&processes[i], (int) processes[i].process_size ,&mem);


  }

=======
      printf("\nRequesting memory");
      // sleep(2);
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


  
>>>>>>> Stashed changes
}
