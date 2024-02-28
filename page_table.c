//
// Created by sblan on 20/02/2024.
//
#include<stdio.h>
#include<stdlib.h>
#include "page_table.h"
#include "process.h"

#define NUM_PAGES 5
#define LEVELS 2

struct PageTable* hierarchical_page_table[NUM_PAGES];

/**
 * Initializes the single page table of a process.
 * Sets the frame number and validity flag of each page entry to default values.
 *
 * @param process The process whose page table is being initialized.
 */
void init_page_table(struct Process* process) {
    int index = -1;
    for (int i = 0; i < NUM_PAGES; i++) {
        if (hierarchical_page_table[i] == NULL) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Page Fault: No free space in the hierarchical page table\n");
        return;
    }

    hierarchical_page_table[index] = (struct PageTable*)malloc(sizeof(struct PageTable));

    for (int i = 0; i < NUM_PAGES; i++) {
        hierarchical_page_table[index]->page_table[i].frame_number = -1;
        hierarchical_page_table[index]->page_table[i].valid = 0;
    }

    process->page_table = hierarchical_page_table[index];
}




/**
 * Prints the page table, displaying the mapping between page numbers and frame numbers.
 * 
 * This function iterates over the page table array and prints each page number along with its corresponding frame number.
 * The page table is assumed to be a global array named "page_table" with a size of "NUM_PAGES".
 * 
 * Example output:
 * Page table:
 * Page 0: Frame 2
 * Page 1: Frame 4
 * Page 2: Frame 1
 * ...
 */
void print_page_table(struct Process* process) {
    printf("Page table:\n");
    for (int i = 0; i < NUM_PAGES; i++) {
        printf("Page %d: Frame %d\n", i, process->page_table[i].page_table->frame_number);
    }
}

/**
 * Accesses the page table of a given process.
 *
 * @param process The process whose page table is to be accessed.
 * @return A pointer to the page table of the process.
 */
// struct PageTableEntry* access_process_page_table(struct Process* process) {
//     return process->page_table;
// }

