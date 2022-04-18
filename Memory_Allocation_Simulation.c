//Osher Boudara COMP322 Memory Allocation Simulation
#include <stdio.h>
#include <stdlib.h>

struct node{
    int id;
    int start;
    int end;
    struct node* link;
}* block_ptr = NULL;

typedef struct node block_type;


int pm_size;
int remaining;


void block_init() {
   
    // prompt for size of physical memory
    printf("Enter the size of physical memory: ");
    scanf("%d", &pm_size);

   
    remaining = pm_size;

    // allocate memory for linked list of blocks
    block_ptr = (block_type *)malloc(sizeof(block_type));
    // create "dummy" block with id -1, staring/ending address of 0 and link of NULL
    block_ptr->id = -1;
    block_ptr->start = 0;
    block_ptr->end = 0;
    block_ptr->link = NULL;

    return;
}
   
void print_blocks() {

    block_type* current_ptr = block_ptr;
   
    printf("\nID\tStart\tEnd\n");
    printf("-------------------\n");
    // print each block in list with while-loop, loop until end of list,
    //advancing "current block" pointer
    current_ptr = current_ptr->link;
    while (current_ptr != NULL){
        printf("%d\t%d\t%d\n", current_ptr->id, current_ptr->start, current_ptr->end);
        current_ptr = current_ptr->link;
    }
    
    return;
}

void first_fit_memory_allocation() {
   
    int block_id, block_size;
    block_type* current_ptr = block_ptr;
    block_type* new_block_ptr;
    int hole_start, hole_end, hole_size;
   
    printf("Enter block id: ");
    scanf("%d", &block_id);
   
    printf("Enter block size: ");
    scanf("%d", &block_size);
    // if block size is larger than remaining memory, print message, return
    if (block_size > remaining){
        printf("Not enough memory...");
        return;
    }
    // allocate memory for new block, set block id
    new_block_ptr = (block_type *)malloc(sizeof(block_type));
    new_block_ptr->id = block_id;
    // if block list is "empty",
    if(block_ptr->link == NULL) {
        //set fields for new block, link to block list, reduce remaining memory, return
   
        new_block_ptr->start = block_ptr->start;
        new_block_ptr->end = block_ptr->start + block_size;
        new_block_ptr->link = NULL;
        block_ptr->link = new_block_ptr;
        remaining -= block_size;
        
        return;
    }

    // while not end of list, loop
    while (current_ptr != NULL){
        //if duplicate id, print message, return
        if (block_id == current_ptr->id){
            printf("Duplicate ID...");
            free(new_block_ptr);
            return;
        }
        current_ptr =current_ptr->link;
    }

    current_ptr = block_ptr;
    while (current_ptr != NULL){
        //set values for start and end of current hole
        hole_start = current_ptr->end;
        if (current_ptr->link != NULL){
            hole_end = current_ptr->link->start;
        }
        else {
            hole_end = pm_size;
        }
        
   
        hole_size = (hole_end - hole_start);

        // if block fits in hole, set fields for new block, link to block list, reduce remaining memory, return
        if (block_size <= hole_size) {
       
            new_block_ptr->start = hole_start;
            new_block_ptr->end = hole_start + block_size;
            new_block_ptr->link = current_ptr->link;
            current_ptr->link = new_block_ptr;
            remaining -= block_size;
            return;
        }
        // advance "current block" pointer
        current_ptr = current_ptr->link;
    }
       
    // if end of list reached, print message no fitting hole
    printf("There is no fitting hole");
    
    return;
}


void best_fit_memory_allocation() {
 int block_id, block_size;
    block_type* current_ptr = block_ptr;
    block_type* new_block_ptr;
    block_type* best_block_ptr;
    int hole_start, hole_end, hole_size;
    int at_least_one = 0;
    int best_so_far = pm_size;
    int best_start;
   
    printf("Enter block id: ");
    scanf("%d", &block_id);
   
    printf("Enter block size: ");
    scanf("%d", &block_size);
    // if block size is larger than remaining memory, print message, return
    if (block_size > remaining){
        printf("Not enough memory...");
        return;
    }
    // allocate memory for new block, set block id
    new_block_ptr = (block_type *)malloc(sizeof(block_type));
    new_block_ptr->id = block_id;
    // if block list is "empty",
    if(block_ptr->link == NULL) {
        //set fields for new block, link to block list, reduce remaining memory, return
   
        new_block_ptr->start = block_ptr->start;
        new_block_ptr->end = block_ptr->start + block_size;
        new_block_ptr->link = NULL;
        block_ptr->link = new_block_ptr;
        remaining -= block_size;
        free(new_block_ptr);
        return;
    }

    // while not end of list, loop
    while (current_ptr != NULL){
        //if duplicate id, print message, return
        if (block_id == current_ptr->id){
            printf("Duplicate ID...");
            free(new_block_ptr);
            return;
        }
        current_ptr = current_ptr->link;
    }

    current_ptr = block_ptr;
    while (current_ptr != NULL){
        //set values for start and end of current hole
        hole_start = current_ptr->end;
        if (current_ptr->link != NULL){
            hole_end = current_ptr->link->start;
        }
        else {
            hole_end = pm_size;
        }
   
        hole_size = hole_end - hole_start;

        // if block fits in hole,
        if (block_size <= hole_size) {
            //set flag "at least one" fitting hole found
           
            at_least_one = 1;
       
            // if current hole is smaller than best so far
            if(hole_size < best_so_far) {
                // set new value for "best so far", "best start", copy "best block" to current block
                best_so_far = hole_size;
                best_start = hole_start;
                best_block_ptr = current_ptr;
            } 
            
        }
        
        current_ptr = current_ptr->link;
        
       
    }
   
    // if no hole was found large enough, print message, return
   
    if(at_least_one == 0){
        printf("There is no fitting hole");
        free(new_block_ptr);
        free(best_block_ptr);
        return;
    }

    new_block_ptr->start = best_start;
    new_block_ptr->end = best_start + block_size;
    new_block_ptr->link = best_block_ptr->link;
    best_block_ptr->link = new_block_ptr;
    remaining -= block_size;
   
// set fields for new block, link to block list, reduce remaining memory
    return;
}


void worst_fit_memory_allocation() {
 int block_id, block_size;
    block_type* current_ptr = block_ptr;
    block_type* new_block_ptr;
    block_type* worst_block_ptr;
    int hole_start, hole_end, hole_size;
    int at_least_one = 0;
    int worst_so_far = 0;
    int worst_start;
   
    printf("Enter block id: ");
    scanf("%d", &block_id);
   
    printf("Enter block size: ");
    scanf("%d", &block_size);
    // if block size is larger than remaining memory, print message, return
    if (block_size > remaining){
        printf("Not enough memory...");
        return;
    }
    // allocate memory for new block, set block id
    new_block_ptr = (block_type *)malloc(sizeof(block_type));
    new_block_ptr->id = block_id;
    // if block list is "empty",
    if(block_ptr->link == NULL) {
        //set fields for new block, link to block list, reduce remaining memory, return
   
        new_block_ptr->start = block_ptr->start;
        new_block_ptr->end = block_ptr->start + block_size;
        new_block_ptr->link = NULL;
        block_ptr->link = new_block_ptr;
        remaining -= block_size;
        free(new_block_ptr);
        return;
    }

    // while not end of list, loop
    while (current_ptr != NULL){
        //if duplicate id, print message, return
        if (block_id == current_ptr->id){
            printf("Duplicate ID...");
            free(new_block_ptr);
            return;
        }
        current_ptr = current_ptr->link;
    }

    current_ptr = block_ptr;
    while (current_ptr != NULL){
        //set values for start and end of current hole
        hole_start = current_ptr->end;
        if (current_ptr->link != NULL){
            hole_end = current_ptr->link->start;
        }
        else {
            hole_end = pm_size;
        }
   
        hole_size = hole_end - hole_start;

        // if block fits in hole,
        if (block_size <= hole_size) {
            //set flag "at least one" fitting hole found
           
            at_least_one = 1;
       
            // if current hole is smaller than best so far
            if(hole_size > worst_so_far) {
                // set new value for "best so far", "best start", copy "best block" to current block
                worst_so_far = hole_size;
                worst_start = hole_start;
                worst_block_ptr = current_ptr;
            } 
            
        }
        
        current_ptr = current_ptr->link;
        
       
    }
   
    // if no hole was found large enough, print message, return
   
    if(at_least_one == 0){
        printf("There is no fitting hole");
        free(new_block_ptr);
        free(worst_block_ptr);
        return;
    }

    new_block_ptr->start = worst_start;
    new_block_ptr->end = worst_start + block_size;
    new_block_ptr->link = worst_block_ptr->link;
    worst_block_ptr->link = new_block_ptr;
    remaining -= block_size;
   
// set fields for new block, link to block list, reduce remaining memory
    return;
}

void deallocate_block() {

    block_type* current_ptr = block_ptr;
    block_type* previous_ptr;
    int block_size, block_id;
   
    printf("Enter block id: ");
    scanf("%d", &block_id);

    // while id not found and end of block list not reached
    while((current_ptr != NULL) && (block_id != current_ptr->id)){
        // advance "previous block" pointer and "current block" pointer
        previous_ptr = current_ptr;
       
        current_ptr = current_ptr->link;
       
    }

// if "current block" is NULL, print message id not found
    if(current_ptr == NULL){
        printf("ID not found...");
        return;
    }
   
    previous_ptr->link = current_ptr->link;
    block_size = current_ptr->end - current_ptr->start;
    remaining += block_size;
    // else remove block, adjusting "previous block" pointer around it, increment remaining memory with block size, free block with matching id
    free(current_ptr);
    return;
}


void memory_compaction() {
    block_type* current_ptr = block_ptr;
    int block_size;
    int prev_block_end = block_ptr->end;
    // while end of block list not reached
    while(current_ptr != NULL){
        block_size = current_ptr->end - current_ptr->start;
        current_ptr->start = prev_block_end;
        current_ptr->end = prev_block_end + block_size;
        prev_block_end = current_ptr->end;
        current_ptr = current_ptr->link;
    }
// adjust start and end fields of each block, compacting together
    return;
}


void free_memory(block_type *node) {
   
// if node is NULL return
    if(node == NULL)
    {
        return;
    }
    else{
        free_memory(node->link);
        
    }
    free(node);
   
// else call self on link field of node, free node
    return;
}

int main() {
    int choice = 0;
    while(choice != 7) {
        printf("\n\nMemory Allocation \n ---------------- \n 1) Enter parameters \n 2) Allocate memory for block using First-Fit \n 3) Allocate memory for block using Best-Fit \n 4) Allocate memory for block using Worst-Fit \n 5) Deallocate memory for block \n 6) Defragment memory \n 7) Quit and free memory \n");
        printf("\n Enter Selection: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: printf("\nBlock Initialization (Option 1) selected. \n\n"), block_init(); break;
            case 2: printf("\nFirst-Fit Allocation (Option 2) selected. \n\n"), first_fit_memory_allocation(); print_blocks(); break;
            case 3: printf("\nBest-Fit Allocation (Option 3) selected. \n\n"), best_fit_memory_allocation(); print_blocks(); break;
            case 4: printf("\nWorst-Fit Allocation (Option 4) selected. \n\n"), worst_fit_memory_allocation(); print_blocks(); break;
            case 5: printf("\nDeallocation of Block (Option 5) selected.  \n\n"), deallocate_block(); print_blocks(); break;
            case 6: printf("\nDefragmentation of Memory (Option 6) selected.  \n\n"), memory_compaction(); print_blocks(); break;
            case 7: printf("\nFree Memory and Quit (Option 7) selected.  \n\n"), free_memory(block_ptr); break;
            default: printf("\nInvalid option!\n"); break;
        }
    }
    return 1;
}

