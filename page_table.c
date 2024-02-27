//
// Created by sblan on 20/02/2024.
//
#include<stdio.h>
#include<stdlib.h>
#include "page_table.h"
#include "process.h"

#define NUM_PAGES 5


/**
 * @brief Definition of the page table array.
 * 
 * This array represents the page table used in the operating system.
 * It contains PageTableEntry structures, which store information about each page.
 * The size of the array is defined by the constant NUM_PAGES.
 */
struct Page page_table[NUM_PAGES];

/**
 * Initializes the page table of a process.
 * Sets the frame number and validity flag of each page entry to default values.
 *
 * @param process The process whose page table is being initialized.
 */
void init_page_table(struct Process* process) {
    for (int i = 0; i < NUM_PAGES; i++) {
        process->page_table[i].frame_number = -1;
        process->page_table[i].valid = 0;
    }
}

/**
 * Accesses the page table of a given process.
 *
 * @param process The process whose page table is to be accessed.
 * @return A pointer to the page table of the process.
 */
struct Page* access_process_page_table(struct Process* process) {
    return process->page_table;
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
void print_page_table() {
    printf("Page table:\n");
    for (int i = 0; i < NUM_PAGES; i++) {
        printf("Page %d: Frame %d\n", i, page_table[i].frame_number);
    }
}


//TODO implement page_table with the idea that every process has its own page table

