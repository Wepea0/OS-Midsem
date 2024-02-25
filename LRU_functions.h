#ifndef LRU_FUNCTIONS_H
#define LRU_FUNCTIONS_H

//IMPLEMENTATION NOTES
//Empty tlb entry will have -1 at each position
//UPDATE STRATEGY
//Updates priority of Mmost recently accessed entry to highest (if it is not already)
//Reduces priority of all other entries (if change is necessary)

//Checks whether there is free space in TLB
//Returns -1 if not and index of free row if it is
int space_exists();

//Called to check if a particular process entry exists in TLB
//Returns -1 if it does not and index of row it exists at if it does
int entry_exists();

//Adds TLB entry if there was a miss in attempting to access it
//Redirects to one of two other functions depending on whether tlb is full or not
//Update priorities as necessary
int add_to_tlb(int process_id, int *page_table_ptr);

//Called when there is space in TLB
int add_to_tlb_space_exists(int process_id, int *page_table_ptr);

//Called when there is no space in TLB
//Removes least recently used entry and adds new entry
int add_to_tlb_full(int process_id, int *page_table_ptr);

//Called when updating value for TLB entry that already exists in the table but has just been accessed
//Updates priority of entry to highest (if it is not already)
//Reduces priority of all other entries (if change is necessary)
//Returns 1 if successful, 0 if not
int update_tlb_entry(int process_id);




#endif
