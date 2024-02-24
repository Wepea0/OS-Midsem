#ifndef FRAME_FUNCTIONS_H
#define FRAME_FUNCTIONS_H
#define FRAMES_PHYSICAL_MEMORY 8
#define PAGES_VIRTUAL_MEMORY 16
#define PAGE_SIZE 8 //In Kilobytes
#define FRAME_SIZE 8 


typedef struct{
        int free_frames;
        int allocated_frames;

        
        int allocated_frame_list[FRAMES_PHYSICAL_MEMORY];
        int free_frame_list[8];
    }Frame_info;


Frame_info create_Frame_info();

void print_frame_info();

void allocate_frame(int frame_number);
    //Move from free to allocated
    // Update free frame and allocated frames variables


void deallocate_frame(int frame_number);
    //Move from allocated to free
    // Update free frame and allocated frames variables


char ** get_frame_info();
    //Return string with
    //no. free frames, no. allocated frames
    // used physical memory space, free physical space
    // free frames
    // allocated frames


int free_frames_exist();
    //0 represents false
    //Non-zero will mean true and also define the free frames


int * get_free_frames();
    //Return array of all free frames
    //Use number from free_frames_exist to access all free frames and avoid out of bounds access

int * get_allocated_frames();


    
#endif