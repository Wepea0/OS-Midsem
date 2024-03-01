
// Function should count the number of page entries with mapped frame numbers and number without
// Iterative count will be less efficient
// Should maintain a values (free and allocated) that are decremented/incremented when a page is mapped to a frame and incremented/decremented when page mapping to frame is removed. 
// Could have a function that does iterative count but don't currently see use case 
// Should specific frames(free frames, allocated frames) be tracked as well
// Naming convention for frames (frame row number)

// EXTRA FUNCTIONALITIES
// Largest range of contiguous physical memory available

// IMPLEMENTATION ASSUMPTIONS
// Page table containes all necessary rows at creation time
// Page table index with no  frame mapping has X as page table entry
// Frames are referenced by their position on physical memory.


// Virtual memory - 16 pages
// Physical memory - 8 pages 
// Page 

// Should be passed the memory address of the page table* (Not necessary)
// Need to keep track of complete list of frames. List of frames (frame1, frame2...)
// Two variables for number of free and allocated frames.
// List of frames will be free list (another list representing allocated witll be created)
// Allocated frame will be moved from free list to allocated list
// Increment function should pass frame number that wass allocated
// Decrement function should pass frame number that was deallocated
// current status function will return number of free and allocated frames
- The specific frames in both categories
- the total used physical memory 
- total used virtual memory
- total free virtual memory
- total free physical memory

