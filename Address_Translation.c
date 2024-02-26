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
int outer_page_table[MAX_PROCESS_NUM];

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
    int process_number = rand() % MAX_PROCESS_NUM;
    int num_pages = (rand() % (MAX_PAGES - 1)) + 1; // Generate a random number between 1 and MAX_PAGES
    int offset_size = rand() % MAX_OFFSET;

    printf("Number of pages: %d\n", num_pages);
    int page_table_num = first_fit_page_table(free_outer_page_tables);
    outer_page_table[process_number] = page_table_num;

    for (int i = 0; i < num_pages; i++) {
        int logical_address[3] = {process_number, page_table_num, i};
        int frame_number = first_fit(logical_address);
        page_table[i] = frame_number;
        int physical_address[2] = {frame_number, offset_size};

        // printing addresses
        printf("logical Address: [%d, %d, %d]\tPhysical Address: [%d, %d]\n", process_number, num_pages, offset_size, frame_number, offset_size);
    }

    /*
    for (int i = 0; i < 4; i++) {
        int page_number = rand() % MAX_PAGES;
        int offset = rand() % (MAX_OFFSET + 1);

        int logical_address[2] = {page_number, offset};

        // Placing the process in the virtual memory
        for (int i = 0; i < MAX_OFFSET; i++) {
            virtual_memory[page_number][i] = 1;
        }

        // assigning frame number to a page number in the page table
        int frame_number = first_fit(logical_address);
        page_table[page_number][1] = frame_number;

        // creation of physical address
        int physical_address[2]  = {frame_number, offset};

        // printing addresses
        printf("logical Address: [%d, %d]\tPhysical Address: [%d, %d]\n", page_number, offset, frame_number, offset);
    }*/
    
}

int first_fit(int logical_address[]) {
    int process_offset = logical_address[2];
    int offset_so_far = 0;
    int valid = 0;
    int frame = 0;

    for (int i = 0; i < MAX_FRAMES; i++) {
        for (int j = 0; j < MAX_OFFSET; j++) {
            if (physical_memory[i][j] == 0)  {
                valid++; 
                if (valid == MAX_OFFSET) {
                    for (int k = 0; k < process_offset; k++) {
                        physical_memory[i][k] = 1;
                        frame = i;
                        goto exit_all_loops;
                    }
                }
            }
            else {
                valid = 0;
                break;
            }
        }
    }

    exit_all_loops:
    return frame;
}

int first_fit_page_table (int free_outer_page_table[]) {
    int ans = 0;
    for (int i = 0; i < 8; i++) {
        if (free_outer_page_table[i] == 0) {
            free_outer_page_table[i] = 1;
            ans = i;
            break;
        }
    }
    return ans;
}

void initializeMemory2D(int row, int col, int mem[][col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            mem[i][j] = 0;
        }
    }
}

void initializeMemory3D(int block, int row, int col, int mem[][row][block]) {
    for (int i = 0; i < block; i++) {
        for (int j = 0; j < row; j++) {
            for (int k = 0; k < col; k++) {
                mem[i][j][k] = 0;
            }
        }
    }
}