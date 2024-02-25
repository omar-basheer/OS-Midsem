//
// Created by sblan on 20/02/2024.
//

// Import Dependencies
#include<stdio.h>
#include<stdlib.h>

/** A struct that models the physical memory/ram of a computer
 *  In this isntance, the memory size is **/
struct logical_memory{
    int page_size = 8; //bytes
    int no_of_blocks = 8 ;
    int m = 6;
    int n = 3;

    int logical_space[no_of_pages][page_size]; // 2D array to represent the logical address space
};

/** Converts a logical address to a page number **/
int[] logical_address_to_page(struct logical_memory *obj){

    // Get exponents of address space and page size
    int m = obj->m;
    int n = obj->n;

   // Calculate page number
   int page_number = m - n;
   int page_offset = n;

   // Store values in array
   int[2] translated_address = {page_number, page_offset};

   return translated_address;
}

/** Malloc should get the size of the process, divide it by the
 * page size to determine the number of frames that need to be
 * allocated to the process. The process cannot exceed this
 */

//TODO implement malloc with above doc string