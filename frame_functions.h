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

//Move from free to allocated
// Update free frame and allocated frames variables
void allocate_frame(int frame_number);
    

//Move from allocated to free
// Update free frame and allocated frames variables
void deallocate_frame(int frame_number);
    

//Return string with
//no. free frames, no. allocated frames
// used physical memory space, free physical space
// free frames
// allocated frames
char ** get_frame_info();
    

//0 represents false
//Non-zero will mean true and also define the free frames
int free_frames_exist();
    

//Return array of free frames with -1 showing frames which are allocated
//Use number from free_frames_exist to access all free frames and avoid out of bounds access
int * get_free_frames();

//Returns array of allocated frames which -1 showing frames which are free
//Use number from (free_frames_exist - total frames) to access all free frames and avoid out of bounds access
int * get_allocated_frames();


    
#endif