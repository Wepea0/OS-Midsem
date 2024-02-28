#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "frame_functions.h"

static char *frame_info[5]; //Frame info array has 5 elements representing the heading, 
//Number of free frames & number of allocated frames, free_frame list, allocated frame list, 
//physical & virtual memory used 
static int global_free_frames_list[FRAMES_PHYSICAL_MEMORY];
static int global_allocated_frames_list[FRAMES_PHYSICAL_MEMORY];
static Frame_info frame_info_obj;




//Constructor
//ISSUE - Look into using static variables
Frame_info create_Frame_info(){
    frame_info_obj;
    frame_info_obj.free_frames = FRAMES_PHYSICAL_MEMORY;
    frame_info_obj.allocated_frames = 0;

    for (int i = 0; i < 8 ; i++){
        frame_info_obj.allocated_frame_list[i] = -1;
    }

    for (int i = 0; i < 8 ; i++){
        frame_info_obj.free_frame_list[i] = i;
    }

    return frame_info_obj;

}
void print_frame_info(Frame_info frame_obj){
    for (int i = 0; i < 8 ; i++){
        printf("%d\n", frame_obj.allocated_frame_list[i]);
    }
}

void allocate_frame(int frame_to_be_removed){
    //Move from free to allocated
    // Update free frame and allocated frames variables
    if(frame_info_obj.free_frame_list[frame_to_be_removed] != frame_to_be_removed){
        //ISSUE - Throw a frame already allocated error
        return;
    }

    frame_info_obj.free_frame_list[frame_to_be_removed] = -1;
    frame_info_obj.free_frames = frame_info_obj.free_frames - 1;

    frame_info_obj.allocated_frame_list[frame_to_be_removed] = frame_to_be_removed;
    frame_info_obj.allocated_frames =   frame_info_obj.allocated_frames + 1;
    
}

void deallocate_frame(int frame_to_be_removed){
    //Move from allocated to free
    // Update free frame and allocated frames variables
    if(frame_info_obj.allocated_frame_list[frame_to_be_removed] != frame_to_be_removed){
        //ISSUE - Throw a frame not allocated error
        return;
    }
    frame_info_obj.free_frame_list[frame_to_be_removed] = frame_to_be_removed;
    frame_info_obj.free_frames++;

    frame_info_obj.allocated_frame_list[frame_to_be_removed] = -1;
    frame_info_obj.allocated_frames--;
}

int free_frames_exist(){
    //0 represents false
    //Non-zero will mean true and also define the free frames
    return frame_info_obj.free_frames;
}

int * get_free_frames(){
    //Return array of all free frames
    //Use number from free_frames_exist to access all free frames and avoid out of bounds access
    
    memcpy(global_free_frames_list, frame_info_obj.free_frame_list, FRAMES_PHYSICAL_MEMORY*sizeof(int));
    return global_free_frames_list;
        
}

int * get_allocated_frames(){
    //Return array of all allocated frames
    
    memcpy(global_allocated_frames_list, frame_info_obj.allocated_frame_list, FRAMES_PHYSICAL_MEMORY*sizeof(int));
    return global_allocated_frames_list;

}

char ** get_frame_info(){
    //Return string with
    //no. free frames, no. allocated frames
    // used physical memory space, free physical space
    char status_title[] =  "\n\n************* FRAME STATUS REPORT  ****************";
    frame_info[0] = status_title; 

    //Concatenate title of element with number of free frames value from object and then add it to status info array
    char free_frame_string[5];
    sprintf(free_frame_string, "%d", frame_info_obj.free_frames);
    char *free_frames_ptr = (char *)malloc(strlen("Number of free frames - ") + sizeof(free_frame_string));
    strcpy(free_frames_ptr, "Number of free frames - ");
    strcat(free_frames_ptr, free_frame_string);
    frame_info[1] = free_frames_ptr;

    //Concatenate title of element with number of allocated frames value from object and then add it to status info array
    char allocated_frame_string[5];
    sprintf(allocated_frame_string, "%d", frame_info_obj.allocated_frames);
    char *allocated_frames_ptr = (char *)malloc(strlen("Number of allocated frames - ") + sizeof(allocated_frame_string));
    strcpy(allocated_frames_ptr, "Number of allocated frames - ");
    strcat(allocated_frames_ptr, allocated_frame_string);
    frame_info[2] = allocated_frames_ptr;

    //Physical space used 
    char used_space_string[5];
    int used_space = frame_info_obj.allocated_frames * FRAME_SIZE;
    sprintf(used_space_string, "%d", used_space);
    char *used_space_ptr = (char *)malloc(strlen("Used physical memory (in KB) -") + sizeof(used_space_string));
    strcpy(used_space_ptr, "Used physical memory (in KB) - ");
    strcat(used_space_ptr, used_space_string);
    frame_info[3] = used_space_ptr;

    //Physical space free
    char free_space_string[5];
    int free_space = frame_info_obj.free_frames * FRAME_SIZE;
    sprintf(free_space_string, "%d", free_space); 
    char *free_space_ptr = (char *)malloc(strlen("Free physical memory (in KB) - ") + sizeof(free_space_string));
    strcpy(free_space_ptr, "Free physical memory (in KB) - ");
    strcat(free_space_ptr, free_space_string);
    frame_info[4] = free_space_ptr;

    
    
    printf("%s\n", status_title);
    printf("%s\n", free_frames_ptr);
    printf("%s\n", allocated_frames_ptr);
    printf("%s\n", used_space_ptr);
    printf("%s\n", free_space_ptr);

    print_free_allocated_frames();




    // free(free_frames_ptr);
    // free(allocated_frames_ptr);

    return frame_info;
   
}

void free_frame_info_status_obj(char **status_report_obj){
    for(int i = 0; i < sizeof(status_report_obj); i++){
        free(status_report_obj[i]);
    }
    free(status_report_obj);
}

void print_free_allocated_frames(){
    int *allocated_frames_list = get_allocated_frames();
puts("Allocated frames");
for (int i = 0; i < sizeof(allocated_frames_list); i++){
    if(allocated_frames_list[i] > -1){
        printf("%d - ", allocated_frames_list[i]);

    }
}
int * free_frames_list = get_free_frames();
puts("\nFree frames");
for (int i = 0; i < sizeof(free_frames_list); i++){
    if(free_frames_list[i] > -1){
        printf("%d -+ ", free_frames_list[i]);
    }
}
print("\n");
}

//Need to create matrix that models page table to test functions (not need but for 
//iterative counting functionality)

//Create 2d matrix 

// int main(){
    

// Frame_info frame_info_obj;
// frame_info_obj = create_Frame_info();
// // print_frame_info(frame_info_obj);
// // get_frame_info(frame_info_obj);
// allocate_frame(2);

// get_frame_info();
// allocate_frame(3);
// allocate_frame(4);
// allocate_frame(111);
// get_frame_info();
// deallocate_frame(3);
// get_frame_info();
// int *allocated_frames_list = get_allocated_frames();
// puts("Allocated frames");
// for (int i = 0; i < sizeof(allocated_frames_list); i++){
//     if(allocated_frames_list[i] > 0){
//         printf("%d - ", allocated_frames_list[i]);

//     }
// }
// int *free_frames_list = get_free_frames();
// puts("\nFree frames");
// for (int i = 0; i < sizeof(free_frames_list); i++){
//     if(free_frames_list[i] > 0){
//         printf("%d - ", free_frames_list[i]);
//     }
// }



// // free_frame_info_status_obj(status_report_obj);







// return 0;







    
// }
