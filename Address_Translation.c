#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simulator.h"

#define VIRTUAL_MEMORY_SIZE     128 // KB
#define PHYSICAL_MEMORY_SIZE    64  // KB
#define SWAP_TABLE_SIZE         64  // KB
#define PAGE_SIZE               8   // KB w/ 2KB per cell
#define FRAME_SIZE              8   // KB w/ 2KB per cell
#define BYTES_PER_CELL          2   // 2 KB 
#define CELLS_PER_PAGE          4
#define CELLS_PER_FRAME         (CELLS_PER_PAGE)
#define TOTAL_NUMBER_OF_PAGES   (VIRTUAL_MEMORY_SIZE/PAGE_SIZE)     // 16
#define TOTAL_NUMBER_OF_FRAMES  (PHYSICAL_MEMORY_SIZE/FRAME_SIZE)   // 8
#define MAX_NUMBER_OF_PROCESSES 4
#define MAX_PROCESS_SIZE        32 // KB
#define MAX_PROCESS_NUM         (VIRTUAL_MEMORY_SIZE / MAX_PROCESS_SIZE)
#define MAX_PAGE_PER_PROCESS    (MAX_PROCESS_SIZE / (CELLS_PER_PAGE * 2))
#define MAX_OFFSET              4

static int process_count = 0;

// initializing the memory spaces
static int virtual_memory[TOTAL_NUMBER_OF_PAGES][MAX_OFFSET] = {{0}};
static int physical_memory[TOTAL_NUMBER_OF_FRAMES][MAX_OFFSET] = {{0}};

// initializing outer page table to map processes to page tables
static int *outer_page_table[MAX_PROCESS_NUM] = {NULL};

int first_fit(int a[]);
void initializeMemory2D(int row, int col, int mem[][col]);
void fillVirtualMemory(int start, int num_pages);
int user_fork();
void createProcess();

int main(void) {
    srand(time(NULL));
    for (int i = 0; i < MAX_OFFSET; i++) {
        physical_memory[1][i] = 1;
        physical_memory[3][i] = 1;
    }

    createProcess();
    printf("\n");
    createProcess();
    printf("\n");
    createProcess();
    printf("\n");
    createProcess();
    printf("\n");
    createProcess();
    printf("\n");
    createProcess();
}

int first_fit(int logical_address[]) {
    int process_offset = logical_address[2];
    int offset_so_far = 0;
    int valid = 1;
    int frame = -1;

    for (int i = 0; i < TOTAL_NUMBER_OF_FRAMES; i++) {
        for (int j = 0; j < MAX_OFFSET; j++) {
            if (physical_memory[i][j] == 0)  {
                valid++; 
                if (valid == MAX_OFFSET) {
                    for (int k = 0; k < process_offset; k++) {
                        physical_memory[i][k] = 1;
                    }
                    frame = i;
                    goto exit_all_loops;
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

void fillVirtualMemory(int start, int num_pages) {
    for (int i = start; i < start + num_pages; i++) {
        for (int j = 0; j < MAX_OFFSET; j++) {
            virtual_memory[i][j] = 1;
        }
    }
}

int user_fork() {
    int pid = process_count;
    process_count += 1;
    return pid;
}

void createProcess() {
    // Getting random values that are important to the process
    int process_number = user_fork();
    printf("process_number: %d\n", process_number);

    int process_size = rand() % MAX_PROCESS_SIZE;
    int num_pages = (process_size / PAGE_SIZE); // Generate a random number between 1 and MAX_PAGES
    printf("Number of pages for process %d: %d\n", process_number, num_pages);
    int offset_size = (process_size / 2) % CELLS_PER_PAGE;

    // Creating Process
    Process new_process = {process_number * num_pages, process_number, process_size};
    // initializing page table
    int page_table[MAX_PAGE_PER_PROCESS] = {0};
    int *ptr = page_table;
    //initializeMemory2D(MAX_PAGE_PER_PROCESS, 1, page_table);

    fillVirtualMemory(process_number * MAX_PAGE_PER_PROCESS, num_pages);
    outer_page_table[process_number] = ptr;

    for (int i = 0; i < num_pages; i++) {
        int logical_address[3] = {process_number, i, offset_size};
        int frame_number = first_fit(logical_address);
        if (frame_number == -1) {
            printf("The physical memory is full, your page is waiting and has not been loaded yet");
            continue;
        }
        outer_page_table[process_number][i] = frame_number;
        int physical_address[2] = {frame_number, offset_size};

        // printing addresses
        printf("logical Address: [%d, %d, %d]\tPhysical Address: [%d, %d]\n", process_number, i, offset_size, frame_number, offset_size);
    }
}