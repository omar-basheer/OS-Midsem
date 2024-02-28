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

struct PageTable{
    struct PageTableEntry page_table_entry[NUM_PAGES]; // single entry in the hierarchical page table, which is a pointer to the next level of the page table
};

extern struct PageTable* hierarchical_page_table[NUM_PAGES];

// extern struct PageTableEntry page_table[NUM_PAGES];
void initialize_page_table(struct Process* process);
void print_page_table(struct Process* process);
void visualize_hierarchical_page_table();
struct PageTable* access_process_page_table(struct Process *process);

#endif /* PAGE_TABLE_H */
