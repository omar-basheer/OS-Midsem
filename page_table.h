#ifndef PAGE_TABLE_H
#define PAGE_TABLE_H
#define NUM_PAGES 5
#define LEVELS 2


struct Process;

/**
 * @struct PageTableEntry
 * Represents an entry in a page table.
 * Contains the frame number and a flag indicating whether the entry is valid.
 */
struct PageTableEntry{
    int frame_number;   // The frame number associated with the page
    int valid;          // Flag indicating whether the entry is valid
};

extern struct PageTableEntry page_table[NUM_PAGES];
void init_page_table(struct Process *process);
struct PageTableEntry* access_process_page_table(struct Process *process);
void print_page_table(struct Process* process);

#endif /* PAGE_TABLE_H */
