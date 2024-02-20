//
// Created by sblan on 20/02/2024.
//

// Import Dependencies
#include<stdio.h>
#include<stdlib.h>


/** A struct that models the page_table **/
struct page_table{
    int table[10][2];
};


/** A function that insert a mapping into the page table **/
void insert_mapping(struct page_table obj*, int[]address){

    int page_number = address[0];
    int page_offset = address[1];

    obj.table[page_number] = page_offset;
}
