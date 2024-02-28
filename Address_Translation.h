#ifndef ADDRESS_TRANSLATION_H
#define ADDRESS_TRANSLATION_H

#define MAX_PAGES 16
#define MAX_FRAMES 8
#define MAX_OFFSET 4
#define MAX_PROCESS_NUM 16
#define MAX_PROCESS_PAGES 3


typedef struct{
    int process_number;
    int process_size;
    int offset;

    int *page_table;
}Process;

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

void create_process();
void assign_frames();


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

int first_fit(int a[]);


#endif

