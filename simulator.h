#ifndef SIMULATOR_H
#define SIMULATOR_H
/*
#define VALID_BIT               1   // process is in physical memory
#define INVALID_BIT             0   // process is in backstore
#define VADDR_PAGE_NUMBER_INDEX 0
#define VADDR_PAGE_OFFSET_INDEX 1
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
#define MAX_NUMBER_OF_PROCESSES 8
#define MAX_PROCESS_SIZE        64 // KB
*/

typedef struct { 
    int virtual_address;
    int pid;
    int size;
    //int* page_table;
} Process;

typedef struct {
    Process process_list[4];
    int* main_page_table;
} MMU;


//
//Process createProcess();

//
int* getPhysicalAddress(Process p);

//
void allocateVirtualMemory();

//
int user_fork();

//
void simulateProcessCreation();

//
void simulateMMU();

//
void showProcessContents(Process p);

#endif