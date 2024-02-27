#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H
#define NUM_PAGES 5


struct Process;

/**
 * @struct PageTableEntry
 * Represents an entry in a page table.
 * Contains the frame number and a flag indicating whether the entry is valid.
 */
struct Page{
    int frame_number;   // The frame number associated with the page
    int valid;          // Flag indicating whether the entry is valid
};

extern struct Page page_table[NUM_PAGES];
void init_page_table(struct Process *process);
struct Page* access_process_page_table(struct Process *process);
void print_page_table();

#endif /* PAGE_TABLE_H */
