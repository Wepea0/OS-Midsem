#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PAGES 16
#define MAX_FRAMES 64
#define MAX_OFFSET 4
#define MAX_PROCESS_NUM 8

// initializing the memory spaces
int virtual_memory[MAX_PROCESS_NUM][MAX_PAGES][MAX_OFFSET];
int physical_memory[MAX_FRAMES][MAX_OFFSET];

// initializing page table
int page_table[MAX_PAGES];

// initializing outer page table to map processes to page tables
int *outer_page_table[MAX_PROCESS_NUM];

// initializing an array of available page tables
int free_outer_page_tables[8] = {0, 0, 0, 0, 0, 0, 0, 0};

int first_fit(int a[]);
void initializeMemory3D(int block, int row, int col, int mem[][row][col]);
void initializeMemory2D(int row, int col, int mem[][col]);
int first_fit_page_table (int free_outer_page_table[]);

int main(void) {
    srand(time(NULL));
    initializeMemory3D(MAX_PROCESS_NUM, MAX_PAGES, MAX_OFFSET, virtual_memory);
    initializeMemory2D(MAX_FRAMES, MAX_OFFSET, physical_memory);
    initializeMemory2D(MAX_PROCESS_NUM, 1, outer_page_table);

    for (int i = 0; i < MAX_OFFSET; i++) {
        physical_memory[1][i] = 1;
        physical_memory[3][i] = 1;
    }

    initializeMemory2D(MAX_PAGES, 1, page_table);
