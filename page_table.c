//
// Created by sblan on 20/02/2024.
//

// Import Dependencies
#include<stdio.h>
#include<stdlib.h>


/** A struct that models the page_table
 * A page table must be maintained for every process that is
 * created**/
struct page_table{
    int table[10][2];
};

struct  PageTableEntry{
    int frame_number;
    int valid;
}

//TODO implement page_table with the idea that every process has its own page table


/** A function that insert a mapping into the page table **/
void insert_mapping(struct page_table obj*, int[]address){

    int page_number = address[0];
    int page_offset = address[1];

    obj.table[page_number] = page_offset;
}

// Struct for a page table entry
