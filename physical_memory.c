//
// Created by sblan on 20/02/2024.
//

// Import Dependencies
#include<stdio.h>
#include<stdlib.h>

/** A struct that models the physical memory/ram of a computer
 *  In this isntance, ram has 128 frames of size 12 **/

struct physical_memory
    int frame_size = 4; //bytes
    int no_of_frames = 128;
    int memory_size = frame_size * no_of_frames

    int ram[no_of_frames][frame_size] // 2D array to represent RAM with 100 units of storage


};