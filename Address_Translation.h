#ifndef ADDRESS_TRANSLATION_H
#define ADDRESS_TRANSLATION_H

#define MAX_PAGES 16
#define MAX_FRAMES 8
#define MAX_OFFSET 4

#define VIRTUAL_MEMORY_SIZE     128 // KB
#define PHYSICAL_MEMORY_SIZE    64  // KB
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


//TODO #12 - Align on structure of process struct
//Thoughts - Whether to/How to store process page table as attribute


// typedef struct{
//     int process_number;
//     int process_size;
//     int offset;

//     int *page_table;
// }Process;

typedef struct { 
    int process_id;
    int is_complete;
    int size;
    int* page_table;
} Process;


//Variables
// initializing the memory spaces
extern int virtual_memory[MAX_PAGES][MAX_OFFSET];
extern int physical_memory[MAX_FRAMES][MAX_OFFSET];


// initializing outer page table to map processes to page tables
extern int *outer_page_table[MAX_PROCESS_NUM];

//initializing array to store the attributes of created processes
extern int process_details[3];

//Store currently existing process (structs / IDs)
extern int process_list[MAX_PROCESS_NUM];

//Store number of created processes - Used for indexing process_list; - Should be increased when create_process is used
// and decreased when end_process is used
extern int number_of_processes;




//Returns array of attributes of a process that have been generated randomly
//First entry [0] - Process number
//Second entry [1] - Number of pages
//Third entry [2] - Offset size
int * generate_process_attributes();

void initializeMemory2D(int row, int col, int (*mem)[col]);

void initialize_outer_page_table(int row, int col, int *mem[col]);

void populate_outer_page_table(int row, int col, int ** mem);

void populate_page_table(int row, int col, int (*mem));

void fillVirtualMemory(int start, int num_pages);

int first_fit();

//The function `int can_fulfill(int memory_request);` is checking if the system can fulfill a memory request based on the available physical memory.  
//It takes an integer parameter `memory_request` which represents the amount of memory requested by a process.
//Memory request refers to size in  number of pages
int can_fulfill_request(int num_pages_request);

void create_process();

//Maps num of pages to frame numbers
//See generate_process_attributes for values in map_virtual_addresses
//Returns pointer to page table ptr created for the process
int * map_virtual_addresses(int *page_table_ptr, int num_pages_requested, int *process_details);



#endif

