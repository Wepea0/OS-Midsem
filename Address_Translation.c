#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "frame_functions.h"

#define MAX_PAGES 128
#define MAX_FRAMES 64
#define MAX_OFFSET 4
#define MAX_PROCESS_NUM 8
#define MAX_PROCESS_PAGES 8

// initializing the memory spaces
int virtual_memory[MAX_PAGES][MAX_OFFSET];
int physical_memory[MAX_FRAMES][MAX_OFFSET];

// initializing page table
int page_table[MAX_PAGES];

// initializing outer page table to map processes to page tables
int *outer_page_table[MAX_PROCESS_NUM];

int first_fit(int a[]);
void initializeMemory2D(int row, int col, int mem[][col]);
void fillVirtualMemory(int start, int num_pages);

int main(void) {
    Frame_info frame_info_obj = create_Frame_info();
    get_frame_info();
//     srand(time(NULL));
//     initializeMemory2D(MAX_PAGES, MAX_OFFSET, virtual_memory);
//     initializeMemory2D(MAX_FRAMES, MAX_OFFSET, physical_memory);
//     initializeMemory2D(MAX_PROCESS_NUM, 1, outer_page_table);

//     for (int i = 0; i < MAX_OFFSET; i++) {
//         physical_memory[1][i] = 1;
//         physical_memory[3][i] = 1;
//     }

//     initializeMemory2D(MAX_PAGES, 1, page_table);

//     int process_number = rand() % MAX_PROCESS_NUM;
//     int num_pages = (rand() % (MAX_PROCESS_PAGES - 1)) + 1; // Generate a random number between 1 and MAX_PAGES
//     int offset_size = rand() % MAX_OFFSET;

//     fillVirtualMemory(process_number * MAX_PAGES, num_pages);
//     printf("Number of pages: %d\n", num_pages);
//     outer_page_table[process_number] = page_table;

//     for (int i = 0; i < num_pages; i++) {
//         int logical_address[3] = {process_number, i, offset_size};
//         int frame_number = first_fit(logical_address);
//         outer_page_table[process_number][i] = frame_number;
//         int physical_address[2] = {frame_number, offset_size};

//         // printing addresses
//         printf("logical Address: [%d, %d, %d]\tPhysical Address: [%d, %d]\n", process_number, i, offset_size, frame_number, offset_size);
//     }
// }

// int first_fit(int logical_address[]) {
//     int process_offset = logical_address[2];
//     int offset_so_far = 0;
//     int valid = 0;
//     int frame = 0;

//     for (int i = 0; i < MAX_FRAMES; i++) {
//         for (int j = 0; j < MAX_OFFSET; j++) {
//             if (physical_memory[i][j] == 0)  {
//                 valid++; 
//                 if (valid == MAX_OFFSET) {
//                     for (int k = 0; k < process_offset; k++) {
//                         physical_memory[i][k] = 1;
//                         frame = i;
//                         goto exit_all_loops;
//                     }
//                 }
//             }
//             else {
//                 valid = 0;
//                 break;
//             }
//         }
//     }

//     exit_all_loops:
//     return frame;
// }

// void initializeMemory2D(int row, int col, int mem[][col]) {
//     for (int i = 0; i < row; i++) {
//         for (int j = 0; j < col; j++) {
//             mem[i][j] = 0;
//         }
//     }
// }

// void fillVirtualMemory(int start, int num_pages) {
//     for (int i = start; i < start + num_pages; i++) {
//         for (int j = 0; j < MAX_OFFSET; j++) {
//             virtual_memory[i][j] = 1;
//         }
//     }
}