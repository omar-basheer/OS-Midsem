
#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H
#define NUM_PAGES 5

#include "processes.h" 

typedef struct {
    int frame_number;   // The frame number associated with the page
    int valid;          // Flag indicating whether the entry is valid
} PageTableEntry;


PageTableEntry page_table[NUM_PAGES];


void init_page_table(struct Process *process);

PageTableEntry* access_process_page_table(struct Process *process);


void print_page_table();

#endif /* PAGE_TABLE_H */
