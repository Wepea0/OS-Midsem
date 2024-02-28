//ISSUE - Functions defined in main cannot be called from outside of it, causing problems during integration
//ISSUE - Initialize function for outer page table causing issue as it attempts to assign to 2d array when a 1d array of int pointers has been declared;
//ISSUE - Population of outer page table after process details have been randomly generated assigns values as if outer page table is 2d array instead of 1d
//ISSUE - Pge table is global variable but different page tables need to be assigned for each table in the list. Need to make sure different page tables are being assigned - check scope and possible redefining of value
//ISSUE - What are we doing with the physical address (no more frame table needed)
//ISSUE - Look into using process structs (if necessary)
//ISSUE - Need to harmonize process ID and process number usage 
//ISSUE - Difference between MAX PROCESS PAGES and MAX PAGES

//TODO - Add check after a process' initial memory request has been identified - to determine whether whole request can be fulfilled
        //If not - Decide on path(Options include: Skip process ie. Reject its request/ Fulfill some/ Make it wait? - Will need to show the actual changes)


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "frame_functions.h"
#include "Address_Translation.h"



// initializing the memory spaces
int virtual_memory[MAX_PAGES][MAX_OFFSET];
int physical_memory[MAX_FRAMES][MAX_OFFSET];

// initializing page table
int page_table[MAX_PAGES];

// initializing outer page table to map processes to page tables
int *outer_page_table[MAX_PROCESS_NUM];

//initializing array to store the attributes of created processes
int process_details[3];

int process_list[MAX_PROCESS_NUM] = {[0 ... MAX_PROCESS_NUM-1] = -1};


int number_of_processes;


void add_to_process_list(int process_id){
    //add to first non -1 space
}

void remove_from_process_list(int process_id){
    //remove require id and change space to -1;
}


void initializeMemory2D(int row, int col, int (*mem)[col]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            mem[i][j] = 0;
        }
    }
}

void populate_outer_page_table(int row, int col, int ** mem){
     for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            mem[i] = 0;
        }
    } 
}

void populate_page_table(int row, int col, int (*mem)){
     for (int i = 0; i < row; i++) {
            mem[i] = 0;
    } 
}

void fillVirtualMemory(int start, int num_pages) {
    // printf("\nStart = %d\nNum_pages = %d", start, num_pages);
    for (int i = start; i < start + num_pages; i++) {
        for (int j = 0; j < MAX_OFFSET; j++) {
            virtual_memory[i][j] = 1;
        }
    }
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


int * generate_process_attributes(){
    int process_number = number_of_processes;
    int num_pages = (rand() % (MAX_PROCESS_PAGES - 1)) + 1; // Generate a random number between 1 and MAX_PAGES
    int offset_size = rand() % MAX_OFFSET;

    process_details[0] = process_number;
    process_details[1] = num_pages;
    process_details[2] = offset_size;

    return process_details;
}


void print_virtual_memory(){
    printf("\n     ****************         Virtual memory allocation  ******************\n");
    for(int i = 0; i < MAX_PAGES; i++){
        for(int j = 0; j < MAX_OFFSET; j++){
            printf("%d  *  ", virtual_memory[i][j] );
        }
        printf("\n");
    }
}

void create_process(){
    //Create process details
    int *process_details = generate_process_attributes();
    int process_number = process_details[0];
    int num_pages = process_details[1];
    int offset_size = process_details[2];

    //Scaffolding
    printf("Process number = %d\nNumber of Pages = %d\nOffset Size = %d\n", process_number, num_pages, offset_size);

    //Fill virtual memory based on number of pages generated and the number of processes already created
    fillVirtualMemory(process_number * MAX_PROCESS_PAGES, num_pages);

    // //Scaffolding
    // print_virtual_memory();

    //Fill page table for this particular process
    for (int i = 0; i < num_pages; i++) {
        int logical_address[3] = {process_number, i, offset_size};
        int frame_number = first_fit(logical_address);
        page_table[i] = frame_number;
        int physical_address[2] = {frame_number, offset_size}; //Needed?
        printf("logical Address: [%d, %d, %d]\tPhysical Address: [%d, %d]\n", process_number, i, offset_size, frame_number, offset_size);

    }

    //Assign this page table to this process in the master (outer) page table
    outer_page_table[process_number] = page_table;

    //Scaffolding - Print the newest entry of the outer page table
    int *test_page_table;
    test_page_table = outer_page_table[process_number];
    printf("\nCurrent process number %d\nPage table entries:\n", process_number);
    for(int i = 0; i < num_pages; i++){
        printf("Page number: %d  -- maps to --  Frame number:%d\n", i, test_page_table[i]);

    
    }

    //Increment process number
    number_of_processes++;

    //Add to process list
    //add_to_process_list(process_number);
    print_virtual_memory();

}


int main(void) {
    Frame_info frame_info_obj = create_Frame_info();
    get_frame_info();

    srand(time(NULL));
    initializeMemory2D(MAX_PAGES, MAX_OFFSET, virtual_memory);
    initializeMemory2D(MAX_FRAMES, MAX_OFFSET, physical_memory);

    populate_page_table(MAX_PAGES, 1, page_table);
    populate_outer_page_table(MAX_PROCESS_NUM, 1, outer_page_table);

    //Determine how many processes will be created for this one simulation
    int number_simulated_processes = 2;
    for(int i = 0; i < number_simulated_processes; i++){
        create_process();

    }
    


    
}





