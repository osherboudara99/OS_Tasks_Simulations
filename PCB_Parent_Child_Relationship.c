//Osher Boudara COMP322 PCB Parent-Child simulation
#include <stdio.h>
#include <stdlib.h>

int n;
struct node1
{
    int process_id;
    struct node1 *link;
};

typedef struct node1 list_type;

struct node2
{
    int parent;
    list_type *children;
}*pcb_array=NULL;


typedef struct node2 pcb;

void print_processes()
{
    list_type *current_child_ptr;
    
    printf("\nProcess hierarchy:\n");
    
    for(int i=0; i < n; i++)
    {
        if((pcb_array[i].parent != -1) && (pcb_array[i].children != NULL))
        {
            current_child_ptr = pcb_array[i].children;
            
            while(current_child_ptr != NULL)
            {
                printf("    Process %d is the parent of Process %d \n",i, current_child_ptr->process_id);
                current_child_ptr = current_child_ptr->link;
            }
        }
    }
}
void pcb_init()
{
    
    printf("Enter the maximum number of processes: ");
    scanf("%d", &n);
    
    pcb_array = (pcb*)(malloc)(n*sizeof(pcb));
    
    pcb_array[0].parent = 0;
    pcb_array[0].children = 0;
    
    
    for(int i = 1; i < n; i++)
    {
        pcb_array[i].parent = -1;
        pcb_array[i].children = NULL;
    }
    
    printf("Process 0 was created as the top-level process.");
    return;
    
    
}

void child_process_creation()
{
    
    int p_process_index;
    int c = 1;
    list_type *new_child, *current_node;
    
    printf("Enter the parent process index: ");
    scanf("%d", &p_process_index);
    
    //search for avaiable index without a parent
    while((c < n) && (pcb_array[c].parent != -1))
    {
        c++;
    }
    
    if(c==n)
    {
        printf("Out of processes!\n");
        return;
    }
    
    // init new child
    new_child = (list_type*)malloc(sizeof(list_type));
    new_child->process_id = c;
    new_child->link = NULL;
    
    // store parent id
    pcb_array[c].parent = p_process_index;
    
    if(pcb_array[p_process_index].children == NULL)
    {
        pcb_array[p_process_index].children = new_child;
    }
    else
    {
        
        current_node = pcb_array[p_process_index].children;
        
        while(current_node->link != NULL)
        {
            current_node = current_node->link;
        }
        
        current_node->link = new_child;
    }
    printf("Process %d was created as a child of Process %d\n", c, p_process_index);
    print_processes();
    
}

void destroy_children(list_type* node_ptr)
{
    
    int id_placeholder;
    
    if(node_ptr == NULL)
    {
        return;
    }
    else
    {
        
        destroy_children(node_ptr->link);
        
        id_placeholder = node_ptr->process_id;
        destroy_children(pcb_array[id_placeholder].children);
        
        printf("\nProcess %d was destroyed. \n", node_ptr->process_id);
        
        free(node_ptr);
        pcb_array[id_placeholder].parent = -1;
        node_ptr = NULL;
    }
    

}

void destroy_child_selection()
{
    int parent_process;
    
    printf("Enter the index of the parent process whose descendants are to be destroyed: ");
    scanf("%d", &parent_process);
    if(parent_process >= 0){
        destroy_children(pcb_array[parent_process].children);
        pcb_array[parent_process].children = NULL;
    }
    else{
        printf("Process does not exist. Returning to main menu.\n");
    }
    
    print_processes();
}


void free_and_quit()
{
    
    if(pcb_array == NULL)
    {
        return;
    }
    else
    {
        destroy_children(pcb_array[0].children);
        free(pcb_array);
    }
    printf("\nQuitting program...\n");
    
    return;
    
    
}

int main() {
    int choice = 0;
    while(choice != 4) {
        printf("\n\nProcess creation and destruction \n ------------------------------ \n 1) Enter parameters \n 2) Create a new child process \n 3) Destroy all descendants of a process \n 4) Quit program and free memory \n");
        printf("\n Enter Selection: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: printf ("\nOption 1 selected. \n\n"),pcb_init(); break;
            case 2: printf ("\nOption 2 selected.  \n\n"),child_process_creation(); break;
            case 3: printf ("\nOption 3 selected.  \n\n"),destroy_child_selection(); break;
            case 4: printf ("\nOption 4 selected.  \n\n"),free_and_quit(); break;
            default: printf("\nInvalid option!\n"); break;
        }
    }
    return 0;
}