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

//Returns 1 if successful and 0 otherwise
int pseudo_malloc(int *page_table_ptr, int memory_request);

//Definition which should go into simulator.c 
//Generate random extra allocation (I'm thinking between 1 and 3)
//Generate a random number which will be the process requesting the new allocation (will need to be between and inc 0 and num_processes) 
//in the process list to allocate it
//Check whether 
// - The new memory allocation will push the total over the max for each process
// - Check if the allocation can be fulfilled
// - If it fails either of these, reject memory request


//Malloc will be called after all processes have been created and before execution starts
//Free will be called after processes which have been malloced execute successfully (Will print output to show malloced allocation has been freed)
//Free should also have deallocation of frames.





//TODO #13 determine flow of execution here
int pseudo_free();




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