#ifndef LRU_FUNCTIONS_H
#define LRU_FUNCTIONS_H

//IMPLEMENTATION NOTES
//Empty tlb entry will have -1 at each position
//Highest priority is 0
//Lowest priority = number of rows in TLB
//Index 0 = Process ID
//Index 1 = Page table ptr
//Index 2 = Priority
//UPDATE STRATEGY
//Updates priority of Mmost recently accessed entry to highest (if it is not already)
//Reduces priority of all other entries (if change is necessary)


 //             ****************   HELPER VARIABLES     ************************
//An array containing the TLB
//First entry [0] - Process ID
//Second entry [1] - Page number
//Third entry [2] - Frame number
//Fourth entry [3] - Priority
extern int TLB[3][4];

extern int misses;
extern int hits;
extern int hit_rate;

//An array containing the number of hits, misses and hit rate
//First entry [0] - Hits
//Second entry [1] - Misses
//Third entry [2] - Hit rate
extern int lookup_stats[3];

extern int (*test_ptr)[3][3];

int get_entry_from_master_table(int process_id, int pointer_to_master_table);

//Checks whether there is free space in TLB
//Returns -1 if not and index of free row if it is
int space_exists();

//Called to check if a particular process entry exists in TLB
//Returns -1 if it does not and index of row it exists at if it does
int entry_exists(int process_id, int page_number);

//Adds TLB entry if there was a miss in attempting to access it
//Redirects to one of two other functions depending on whether tlb is full or not
//Update priorities as necessary
int add_to_tlb(int process_id, int page_number, int frame_number);

//Called when there is space in TLB
void add_to_tlb_space_exists(int tlb_index, int process_id, int page_number, int frame_number);

//Removes least recently used entry and adds new entry
void add_to_tlb_full(int process_id, int page_number, int frame_number);

//Called when updating value for TLB entry that already exists in the table but has just been accessed
//Updates priority of entry to highest (if it is not already)
//Reduces priority of all other entries (if change is necessary)
//Returns 1 if successful, 0 if not
//Uses process_index to access the row of the process_id to update its priority
int update_tlb_entry(int process_id, int page_number);

//Remove lowest priority entry from tlb
int remove_entry();

int ptr_to_integer(int (*page_table_ptr)[3][3]);

int * integer_to_ptr(long integer);

void print_tlb();

//Fill TLB will -1 values to indicate empty slots
void initialize_tlb();

//Returns int representing frame number if the process ID has a frame_number in TLB
//Returns -1 if the process ID does not have frame number in TLB
int lookup(int process_ID, int page_number);

//Update (increase) the number of hits
void update_hits();

//Update (increase) the number of misses
void update_misses();

//Returns an array containing the number of hits, misses and hit rate
//First entry [0] - Hits
//Second entry [1] - Misses
//Third entry [2] - Hit rate
int * get_lookup_stats();




#endif
