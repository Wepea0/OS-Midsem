//ISSUE - Populate TLB with -1 to start
//ISSUE - Hits and misses
//Need to call initialise tlb before rnnung ò````



#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "LRU_functions.h"
#include <stdint.h>

static int TLB[3][3] = {1};

static int misses = 0;
static int hits = 0;

static int (*test_ptr)[3][3] = &TLB;

/// @brief Called when there is space in TLB. Adds new entry to tlb and gives it highest priority
/// @param tlb_index 
/// @param process_id 
/// @param page_table_ptr 
void add_to_tlb_space_exists(int tlb_index, int process_id, int page_table_ptr){
    //Add new entry
    printf("Free index - %d\n", tlb_index);

    TLB[tlb_index][0] = process_id;
    TLB[tlb_index][1] = (intptr_t)page_table_ptr;
    TLB[tlb_index][2] = sizeof(TLB) - 1; //Give lowest priority

    update_tlb_entry(tlb_index);

}

void add_to_tlb_full(int process_id, int page_table_ptr){
    int free_index = remove_entry();
    printf("Free index - %d", free_index);

    TLB[free_index][0] = process_id;
    TLB[free_index][1] = (intptr_t)page_table_ptr;
    TLB[free_index][2] = sizeof(TLB) - 1; 

    update_tlb_entry(free_index);


}



int remove_entry(){
    int lowest_priority = (sizeof(TLB)/sizeof(TLB[0])) - 1;
    for(int i = 0; i < sizeof(TLB); i++){
        if(TLB[i][0] == lowest_priority){
            TLB[i][0] = -1;
            TLB[i][1] = -1;
            TLB[i][2] = -1;
            return i;
        }
    }
    return -1;
}

int add_to_tlb(int process_id, int page_table_ptr){
    int free_index = space_exists();
    if( free_index > -1){
        add_to_tlb_space_exists(free_index, process_id, page_table_ptr);
        return 1;
    }
    else{
        add_to_tlb_full(process_id, page_table_ptr);
        return 1;
    }

    
}

void update_tlb_entry(int process_index){
    int current_priority = TLB[process_index][2];
    if(current_priority == 0){
        return;
    }
    for(int i = 0; i < sizeof(TLB); i++){
       if( TLB[i][2] < current_priority){
        TLB[i][2] = TLB[i][2] + 1;
       }
    }
    TLB[process_index][2] = 0;
    return;
    //Two situations for an update
    //TLB entry is already the highest - DONE
    //TLB entry is not highest
        //At this point an update to the desired process fra'\


}

int entry_exists(int process_id){
    for(int i = 0; i < sizeof(TLB); i++){
        if(TLB[i][0] == process_id){
            return i;
        }
    }
    return -1;
}

int space_exists(){
    for(int i = 0; i < sizeof(TLB); i++){
        if(TLB[i][0] == -1){
            return i;
        }
    }
    return -1;
}



// ******************** Utility function *********************
int ptr_to_integer(int (*page_table_ptr)[3][3]){
    return (intptr_t)page_table_ptr;
}

int * integer_to_ptr(long integer){
    return (int *)integer;
}

void print_tlb(){
    for(int i = 0; i<3; i++){
        for(int j = 0; j < 3; j++){
            printf("%d ~ ", TLB[i][j]);
            
        }
        printf("\n");
    }

}

void initialize_tlb(){
    for(int i = 0; i<3; i++){
        for(int j = 0; j < 3; j++){
            TLB[i][j] = -1;
            
        }
    }

}


void main(){
    initialize_tlb();
    print_tlb();
    
    //    for(int i = 0; i<3; i++){
    //     for(int j = 0; j < 3; j++){
    //         TLB[i][j] = i;
            
    //     }
    // }

    // for(int i = 0; i < sizeof(TLB[0]); i++){
    //     TLB[2][0] = -1;
    // }

    // printf("\n");

    // print_tlb();

    // int tlb_index = space_exists();
    // int test_ptr_int = ptr_to_integer(test_ptr);
    // add_to_tlb_space_exists(tlb_index, 2, test_ptr_int);

    // printf("\n");

    // print_tlb();


    // printf("%d", space_exists());
    // printf("\n%d\n", entry_exists(2));
    return;

}