#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

static int TLB[3][3] = {0};

//Returns 1 when the assignment is successful and 0 otherwise
//Adds a tlb entry to the tlb if there was a miss in accessing this particular PID and page table
int add_to_tlb(int process_id, int *page_table_ptr){
    
}

void main(){
    for(int i = 0; i<3; i++){
        for(int j = 0; j < 3; j++){
            printf("%d-", TLB[i][j]);
            
        }
        printf("\n");
    }
    return;

}