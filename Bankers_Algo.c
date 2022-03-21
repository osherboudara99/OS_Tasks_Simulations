//Osher Boudara COMP322 Banker's Algorithm Simulation for Resource Allocation

#include <stdio.h>
#include <stdlib.h>

int *resource = NULL;
int *available = NULL;

int *max_claim = NULL;
int *allocated = NULL;
int *need = NULL;

int num_resources;
int num_processes;



void print_resource() {
 
	printf("\nResources: \n");
	 
	for(int j = 0; j < num_resources; j++){
		printf("\tr%d", j);
	}
	printf("\n");
	// printing total units corresponding to each resource index 
	for(int j = 0; j < num_resources; j++){
		printf("\t%d", resource[j]);
	}
	printf("\n");   
	return;
}


void print_available() {

	printf("\nAvailable: \n");
 
	for(int j = 0; j < num_resources; j++){
		printf("\tr%d", j);
	}
	printf("\n");
	
	// printing available units corresponding to each resource index 
	for(int j = 0; j < num_resources; j++){
		printf("\t%d", available[j]);
	}
	printf("\n");
	return;
}



void print_max_claims() { 
	
	printf("\nMax Claims: \n");

	for(int j = 0; j < num_resources; j++){
		printf("\tr%d", j);
	}
	
	printf("\n");
	
	for(int j = 0; j < num_processes; j++){
		printf("p%d\t", j);
		for(int i = 0; i < num_resources; i++){
		    //print max number of units each process may request from a resource
			printf("%d\t", max_claim[j*num_resources+i]);
		}
		printf("\n");
	}
 
	return;
}



void print_allocated() { 
	
	printf("\nAllocated: \n");
	
	for(int j = 0; j < num_resources; j++){
		printf("\tr%d", j);
	}
	
	printf("\n");
	 
	for(int j = 0; j < num_processes; j++){
		printf("p%d\t", j);
		for(int i = 0; i < num_resources; i++){
		    //print number of units each process has allocated from each resource
			printf("%d\t", allocated[j*num_resources+i]);
		}
		printf("\n");
	}
	return;
}

void print_need() { 
	
	printf("\nNeed: \n");
	 
	for(int j = 0; j < num_resources; j++){
		printf("\tr%d", j);
	}
	printf("\n");
	//print number of units each process needs from each resource
	for(int j = 0; j < num_processes; j++){
		printf("p%d\t", j);
		for(int i = 0; i < num_resources; i++){
			printf("%d\t", need[j*num_resources+i]);
		}
		printf("\n");
	}
	return;
}


void resource_process_init() {

	int units;
	// prompts number of processes and number of resources 
	printf("\nEnter number of processes: ");
	scanf("%d", &num_processes);

	printf("\nEnter number of resources: ");
	scanf("%d", &num_resources);

	

	resource = (int*)malloc(num_resources*sizeof(int));
	available = (int*)malloc(num_resources*sizeof(int));
	max_claim = (int*)malloc(num_resources * num_processes * sizeof(int));
	allocated = (int*)malloc(num_resources * num_processes * sizeof(int));
	need = (int*)malloc(num_resources * num_processes * sizeof(int));
	
	printf("\nEnter number of units for resources (r0 to r%d):", num_processes);

	for(int j = 0; j < num_resources; j++){
		scanf("%d", &units);
		// intializing resource and available vectors indices
		resource[j] = units;
		available[j] = units;
	}
 
	for(int i = 0; i < num_processes; i++){
		printf("\nEnter maximum units process p%d will request from each resource (r0 to r%d):", i, num_resources);
		for(int j = 0; j < num_resources; j++){	
			scanf("%d", &units);

			max_claim[i * num_resources + j] = units;
			need[i * num_resources + j] = units;
		}
	}
	
	for(int i = 0; i < num_processes; i++){
		printf("\nEnter number of units of each resource (r0 to r%d) allocated to process p%d:", num_resources, i);
		for(int j = 0; j < num_resources; j++){	
			scanf("%d", &units);

			allocated[i * num_resources + j] = units;
			need[i * num_resources + j] -= units;
			available[j] -= units;
		}
	}
	
	print_resource();
	
	print_available();
	
	print_max_claims();
	
	print_allocated();
	
	print_need();

	return;
}


void bankers_algo() {
    
    int *done = (int*)calloc(num_processes, sizeof(int));
    int less_or_equal;
    int at_least_one = 1;
    
    int amount_done = 0;
    
    while((amount_done < num_processes) && (at_least_one == 1)){
        at_least_one = 0;
        
        for(int i = 0; i < num_processes; i++){
            less_or_equal = 1;
            
            if(done[i] == 0){
                
                printf("Comparing: < ");
                
                for(int j = 0; j < num_resources; j++){
                    printf("%d ", need[i*num_resources + j]);
                }
                printf(" > <= < ");
                
                for(int j = 0; j < num_resources; j++){
                    printf("%d ", available[j]);
                }
                
                printf("> : ");
                
                for(int j = 0; j < num_resources; j++){
                    less_or_equal &= (need[i*num_resources+j] <= available[j]);
                }
                
                
                if(less_or_equal == 1){
                    at_least_one = 1;
                    done[i] = 1;
                    printf("Yes, p%d can be processed.\n", i);
                    
                    for(int j = 0; j < num_resources; j++){
                        available[j] += allocated[i*num_resources+j];
                        
                        allocated[i*num_resources+j] = 0;
                        
                        
                    }
                    amount_done++;
                }
                
                else{
                    printf("No, p%d could not processed.\n", i);
                }
            }
        }
    }
    
    if(at_least_one == 0){
        printf("Deadlock among processes: ");
        for(int i = 0; i < num_processes; i++){
            if(done[i] == 0){
                printf("p%d  ", i);
            }
        }
    }
    printf("\n");
	return;
}



void free_quit() {
	if(resource != NULL)
	{
		free(resource);
		free(available);
		free(max_claim);
		free(allocated);
		free(need);
	    printf("Memory has been freed.\n");
    }
    printf("Quitting program...\n");
    return;
}


int main() {
    int choice = 0;
    while(choice != 3) {
        printf("\n\nBanker's Algorithm \n ---------------- \n 1) Enter parameters for processes and resources \n 2) Determine safe sequence with Banker's Algorithm \n 3) Quit and free memory \n");
        printf("\n Enter Selection: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: printf("\nProcess and Resource Initialization (Option 1) selected. \n\n"), resource_process_init(); break;
            case 2: printf("\n Banker's Algorithm (Option 2) selected. \n\n"),bankers_algo(); break;
            case 3: printf("\n Freeing memory and Quitting (Option 3) selected. \n\n"),free_quit(); break;
            default: printf("\nInvalid option!\n"); break;
        }
    }
    return 0;
}
