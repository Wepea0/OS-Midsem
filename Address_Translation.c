#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PAGES 16
#define MAX_FRAMES 8
#define MAX_OFFSET 4

// initializing the memory spaces
int  virtual_memory[MAX_PAGES][MAX_OFFSET];
int physical_memory[MAX_FRAMES][MAX_OFFSET];

// initializing page table
int page_table[MAX_PAGES][2];

int first_fit(int a[]);
void initializeMemory(int row, int col, int mem[][col]);

int main(void) {
    initializeMemory(MAX_PAGES, MAX_OFFSET, virtual_memory);
    initializeMemory(MAX_FRAMES, MAX_OFFSET, physical_memory);
    initializeMemory(MAX_PAGES, 2, page_table);

    for (int i = 0; i < MAX_OFFSET; i++) {
        physical_memory[1][i] = 1;
        physical_memory[3][i] = 1;
    }

    for (int i = 0; i < 4; i++) {
        srand(time(NULL));
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
    }
    
}

int first_fit(int logical_address[]) {
    int process_offset = logical_address[1];
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

void initializeMemory(int row, int col, int mem[][col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            mem[i][j] = 0;
        }
    }
}