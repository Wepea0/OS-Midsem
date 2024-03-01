//TODO #2 - Need to call initialise_tlb before running (should be called in simulation)
//ISSUE - Need to compose functions into a complete flow. Think about everything that needs to happen with TLB and 
//        put them together into larger functions that can be called from other programs




#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "LRU_functions.h"
#include <stdint.h>

int TLB[3][4] = {1};

int misses = 0;
int hits = 0;
int hit_rate = 0;
#define TLB_ROWS 3


//An array containing the number of hits, misses and hit rate
//First entry [0] - Hits
//Second entry [1] - Misses
//Third entry [2] - Hit rate
int lookup_stats[3];


/// @brief Called when there is space in TLB. Adds new entry to tlb and gives it highest priority
/// @param tlb_index 
/// @param process_id 
/// @param page_table_ptr 
void add_to_tlb_space_exists(int tlb_index, int process_id, int page_number, int frame_number){
    //Add new entry
    printf("Free index - %d\n", tlb_index);

    TLB[tlb_index][0] = process_id;
    TLB[tlb_index][1] = page_number;
    TLB[tlb_index][2] = frame_number;

    TLB[tlb_index][3] = sizeof(TLB) - 1; //Give smallest priority

    update_tlb_entry(process_id, page_number);

}

void add_to_tlb_full(int process_id, int page_number, int frame_number){
    int free_index = remove_entry();
    printf("Free index - %d", free_index);

    TLB[free_index][0] = process_id;
    TLB[free_index][1] = page_number;
    TLB[free_index][2] = frame_number;

    TLB[free_index][3] = sizeof(TLB) - 1; 

    update_tlb_entry(free_index, page_number);

}



int remove_entry(){
    int lowest_priority = (sizeof(TLB)/sizeof(TLB[0])) - 1;
    for(int i = 0; i < sizeof(TLB); i++){
        if(TLB[i][3] == lowest_priority){
            TLB[i][0] = -1;
            TLB[i][1] = -1;
            TLB[i][2] = -1;
            TLB[i][3] = -1;

            return i;
        }
    }
    return -1;
}

int add_to_tlb(int process_id, int page_number, int frame_number){
    int free_index = space_exists();
    if( free_index > -1){
        add_to_tlb_space_exists(free_index, process_id, page_number, frame_number);
        return 1;
    }
    else{
        add_to_tlb_full(process_id, page_number, frame_number);
        return 1;
    }

    
}

int update_tlb_entry(int process_id, int page_number){
    //Find priority of required process
    int current_priority;
    for(int i = 0; i < 3; i ++){
        if(TLB[i][0] == process_id){
            if(TLB[i][1] == page_number){
                current_priority = TLB[i][3];
            }
        }
    }
    if(current_priority == 0){
        return 1;
    }

    //Lower all other priorities - as applicable
    for(int i = 0; i < TLB_ROWS; i++){
       if( TLB[i][3] < current_priority){
        TLB[i][3] = TLB[i][3] + 1;
       }
    }

    //Set priority of looked up entry to highest
    for(int i = 0; i < 3; i ++){
        if(TLB[i][0] == process_id){
            if(TLB[i][1] == page_number){
                TLB[i][3] = 0;
            }
        }
    }

    return 1;
    

}

int entry_exists(int process_id, int page_number){
    for(int i = 0; i < TLB_ROWS; i ++){
        if(TLB[i][0] == process_id){
            if(TLB[i][1] == page_number){
                return i;
            }
        }
    }
    return -1;
}

int space_exists(){
    for(int i = 0; i < TLB_ROWS; i++){
        if(TLB[i][0] == -1){
            return i;
        }
    }
    return -1;
}

int lookup(int process_ID, int page_number){
    int entry_value = entry_exists(process_ID, page_number);
    if(entry_value > -1){
        update_hits();
        update_tlb_entry(process_ID, page_number);  //Once hit happens, the priority of looked up entry is changed
        return TLB[entry_value][1];
    }
    else{
        update_misses();
        //TODO #1 - Missed entry needs to added to table
        return -1;
    }
}

void update_hits(){
    hits++;
}

void update_misses(){
    misses++;
}

int * get_lookup_stats(){
    lookup_stats[0] = hits;
    lookup_stats[1] = misses;
    
    hit_rate = (hits / (hits + misses)) * 100;
    lookup_stats[2] = hit_rate;

    return lookup_stats;
}



// ******************** Utility function *********************
int ptr_to_integer(int (*page_table_ptr)[3][3]){
    return (intptr_t)page_table_ptr;
}

int * integer_to_ptr(long integer){
    return (int *)integer;
}

void print_tlb(){
    puts("Process ID  ~      Page No          ~       Frame No        ~           Priority");
    for(int i = 0; i< TLB_ROWS; i++){
        for(int j = 0; j < 4; j++){
            printf("%d           ~           ", TLB[i][j]);
            
        }
        printf("\n");
    }

}

void initialize_tlb(){
    for(int i = 0; i<3; i++){
        for(int j = 0; j < 4; j++){
            TLB[i][j] = -1;
            
        }
    }

}


void main(){
    initialize_tlb();
    print_tlb();
    
       for(int i = 0; i<3; i++){
        for(int j = 0; j < 4; j++){
            TLB[i][j] = i;
            
        }
    }

    for(int i = 0; i < sizeof(TLB[0]); i++){
        TLB[2][0] = -1;
    }

    printf("\n");

    print_tlb();

    add_to_tlb(0, 9, 3);

    printf("\n");

    print_tlb();


    // printf("%d", space_exists());
    printf("\n%d\n", entry_exists(2, 2));
    return;

}