//ISSUE - No need for physical memory 2d array. 1d array works fine as frames are always fully allocated or free
//ISSUE - What are we doing with the physical address (no more frame table needed)
//TODO - Confirm whether using variable to track whether process has had its addresses mapped or putting unmapped processes into a separate list from process_list (will need to modify the names, make them more descriptive)

//TODO #9 - Add check after a process' initial memory request has been identified - to determine whether whole request can be fulfilled
        //If not - Decide on path(Options include: Skip process ie. Reject its request/ Fulfill some/ Make it wait? - Will need to show the actual changes)
        //WAIT - Page table will be created but with no mappings (mappings will be done when memory is deallocated(process finishes execution) 
        //and the check shows memory request can be fulfilled)
        //In order to do this, map frame to virtual memory will need to be decoupled from process creation
        //Check function can also support malloc (function can allocation be fulfilled(params int process size_being_requested))
        //in case of malloc, if cannot be fulfilled, reject and end process

//TODO #6 - Create process object in create process function and add it to process list 
//TODO #8 - Change type of process list to Process object
//TODO #7 - Create function objects to edit process list (add and remove) by process ID
//TODO - Frame object needs to be initialized in simulation function (could be part of setup) - create_frame_obj();




#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "frame_functions.h"
#include "Address_Translation.h"
#include "simulator.h"



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
    //add to first -1 space
}

void remove_from_process_list(int process_id){
    //remove require id and change space to -1;
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

int * generate_process_attributes(){
    srand(time(NULL));
    int process_number = number_of_processes;
    int num_pages = (rand() % (MAX_PAGE_PER_PROCESS)) + 1; // Generate a random number between 1 and MAX_PAGES
    int offset_size = rand() % MAX_OFFSET;

    process_details[0] = process_number;
    process_details[1] = num_pages;
    process_details[2] = offset_size;

    return process_details;
}



int can_fulfill_request(int memory_request){
    int required_num_pages = memory_request;
    if(free_frames_exist() >= required_num_pages){
        printf("\nNumber of free pages = %d, Request = %d. Approved \n", free_frames_exist(), required_num_pages);
        return 1;
    }
    printf("\nNumber of free pages = %d, Request = %d. Declined \n", free_frames_exist(), required_num_pages);
    return 0;

}


int first_fit() {
    int frame = get_next_free_frame();
    return frame;
}


int * map_virtual_addresses(int *page_table_ptr, int num_pages_requested, int *process_details){
    int num_pages = num_pages_requested;
    int process_id = process_details[0];
    int offset_size = process_details[2];

    for (int i = 0; i < num_pages; i++) {
        int logical_address[3] = {process_id, i, offset_size};
        int frame_number = first_fit();
        page_table_ptr[i] = frame_number;
        allocate_frame(frame_number);

        //Scaffolding
        printf("logical Address: [%d, %d, %d]\n", process_id, i, offset_size);

    }
    //Fill virtual memory based on number of pages generated and the number of processes already created
    fillVirtualMemory(process_id * MAX_PAGE_PER_PROCESS, num_pages);
    return page_table_ptr;
}



void create_process(){
    //Create process details
    int *process_details = generate_process_attributes();
    int process_number = process_details[0];
    int num_pages = process_details[1];
    int offset_size = process_details[2];

    //Scaffolding
    printf("Process number = %d\nNumber of Pages = %d\nOffset Size = %d\n", process_number, num_pages, offset_size);

    int new_page_table[MAX_PAGES] = {[0 ... MAX_PAGES-1] = -1};
    int *new_page_table_ptr;

    if(can_fulfill_request(num_pages) == 1){ //Successful mapping for all this process' pages
        new_page_table_ptr = map_virtual_addresses(new_page_table, num_pages, process_details);
        outer_page_table[process_number] = new_page_table_ptr;

    }
    else{ //Process has no mappings for its pages 
        outer_page_table[process_number] = new_page_table;
        printf("Could not allocate physical memory for this process at this time");       
        //TODO #10 In case of normal check, add to process list but with attribute not_mapped_to_physical OR add to separate list of processes waiting for memory

    }


    // //Scaffolding
    // print_virtual_memory();


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
    //TODO #15 add_to_process_list(process obj);


}


int main() {
    Frame_info frame_info_obj = create_Frame_info();
    get_frame_info();

    initializeMemory2D(MAX_PAGES, MAX_OFFSET, virtual_memory);
    initializeMemory2D(MAX_FRAMES, MAX_OFFSET, physical_memory);

    populate_page_table(MAX_PAGES, 1, page_table);
    populate_outer_page_table(MAX_PROCESS_NUM, 1, outer_page_table);

    //Determine how many processes will be created for this one simulation
    int number_simulated_processes = 5;
    for(int i = 0; i < number_simulated_processes; i++){
        create_process();

    //Scaffolding
    //See frame info after each process is created
        get_frame_info();

    }

    puts("\nProcess creation done");
    


    
}





