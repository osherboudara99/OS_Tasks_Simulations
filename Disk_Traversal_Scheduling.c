#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

// Declare dynamic array to store sequence of traversed tracks
int* sequence = NULL;
int sequence_size;

void disk_init() {

	// prompt for the sequence size
	printf("\n Enter size of sequence: ");
	scanf("%d", &sequence_size);

	// allocate memory for sequence of traversed tracks
	sequence = (int*)malloc(sequence_size * sizeof(int));

	// prompt for starting track, store in index 0
	printf("\n Enter starting track: ");
	scanf("%d", &sequence[0]);
	
	// prompt for sequence of tracks to seek, store in index 1 to "sequence size-1"
	printf("\n Enter sequence of tracks to seek: ");
	for (int i=1; i < sequence_size; i++){
		scanf("%d", &sequence[i]);
	}
	return;

} 



void fifo_disk_scheduling() {

	int total_distance = sequence[0];
	
	// calculate total distance of traversed tracks

	for(int i = 1; i < sequence_size; i++){
		total_distance += abs(sequence[i]-sequence[i-1]);
	}

	// print sequence of traversal
	printf("\n Traversed sequence: ");
	for(int i = 0; i < sequence_size; i++){
		printf("%d ", sequence[i]);
	}
	// print total distance of tracks traversed
    printf("\n Total amount of traversed tracks: %d", total_distance);
	return;

} 


//shortest seek time first
void sstf_disk_scheduling() {  

	// initialize current track and distance traversed to starting track, other variables
	int total_distance = sequence[0];
	int current_track = sequence[0]; 
	int amount_done = 1;
	int shortest_distance, index_of_shortest;
	int* marked_tracks = (int*)calloc(sequence_size, sizeof(int));
	
	printf("\n Traversed sequence: %d ", sequence[0]);
	
	// until every track is traversed
	while(amount_done < sequence_size){
	
		// initialize shortest distance to INT_MAX
		shortest_distance = INT_MAX;
		
		
		for(int i = 1; i < sequence_size; i++){

			// if not already traversed
			if(marked_tracks[i] == 0){

				//if distance to traverse is shorter than current shortest distance
				if((abs(sequence[i]-current_track)) < shortest_distance){

					// set current shortest distance and index of the track	w/ shortest distance
					shortest_distance = (abs(sequence[i]-current_track));
					index_of_shortest = i;
				}
			}
		}

		// mark index as traversed
		marked_tracks[index_of_shortest] = 1;
		
		// increment number of tracks that have been traversed
		amount_done++;

		// update total distance traversed
		total_distance += shortest_distance;

		//set current track to new position, print position
		current_track = sequence[index_of_shortest];
		printf("%d ", current_track);
	}
								
  	// print total distance traversed

	printf("\n Total amount of traversed tracks: %d", total_distance);
	return;
	

} 


void scan_disk_scheduling() {

	// initialize current track and distance traversed to starting track, other variables
	int total_distance = sequence[0];
	int current_track = sequence[0]; 
	int amount_done = 1;
	int shortest_distance, index_of_shortest;
	int* marked_tracks = (int*)calloc(sequence_size, sizeof(int));
	int direction, at_least_one;
	
	//prompt for initial direction (0 is decreasing and 1 is increasing)

	printf("\n Enter initial direction (0 = decreasing, 1 = increasing): ");
	scanf("%d",&direction);

	printf("\n Traversed sequence: %d ", sequence[0]);
	
	// until every track is traversed
	while(amount_done < sequence_size){
	
		// initialize shortest distance to INT_MAX
		shortest_distance = INT_MAX;
		at_least_one = 0;
		
		
		for(int i = 1; i < sequence_size; i++){

			// if not already traversed
			if(marked_tracks[i] == 0){

				//if distance to traverse is shorter than current shortest distance
				if((abs(sequence[i]-current_track)) < shortest_distance){

					if(((sequence[i] > current_track) && (direction == 1)) || ((sequence[i] < current_track) && (direction == 0))){

						// set current shortest distance and index of the track	w/ shortest distance
						shortest_distance = (abs(sequence[i]-current_track));
						index_of_shortest = i;
						at_least_one = 1;
					}
				}
			}
		}
		if(at_least_one == 1){
	    	// mark index as traversed
			marked_tracks[index_of_shortest] = 1;
			
			// increment number of tracks that have been traversed
			amount_done++;

			// update total distance traversed
			total_distance += shortest_distance;

			//set current track to new position, print position
			current_track = sequence[index_of_shortest];
			printf("%d ", current_track);
		}
		else{ // else change direction
			direction = 1 - direction;
		}
	}

 	// print total distance traversed

 	printf("\n Total amount of traversed tracks: %d", total_distance);
	return;


} 


void c_scan_disk_scheduling() {

	
	// initialize current track and distance traversed to starting track, other variables
	int total_distance = sequence[0];
	int current_track = sequence[0]; 
	int amount_done = 1;
	int shortest_distance, index_of_shortest;
	int* marked_tracks = (int*)calloc(sequence_size, sizeof(int));
	int at_least_one;
	int reached_end = 0;
	

	printf("\n Traversed sequence: %d ", sequence[0]);
	
	// until every track is traversed
	while(amount_done < sequence_size){
	
		// initialize shortest distance to INT_MAX
		shortest_distance = INT_MAX;
		at_least_one = 0;
		
		
		for(int i = 1; i < sequence_size; i++){

			// if not already traversed
			if(marked_tracks[i] == 0){

				//if distance to traverse is shorter than current shortest distance
				if(((sequence[i]-current_track) < shortest_distance) && (sequence[i] > current_track)){
						// set current shortest distance and index of the track	w/ shortest distance
						shortest_distance = (abs(sequence[i]-current_track));
						index_of_shortest = i;
						at_least_one = 1;
				}
			}
		}
		if(at_least_one == 1){
	    	// mark index as traversed
			marked_tracks[index_of_shortest] = 1;
			
			// increment number of tracks that have been traversed
			amount_done++;
			if(reached_end == 0){
				// update total distance traversed
				total_distance += shortest_distance;
			}
			else{
				// we do this to compensate for looping back to zero so we adjust over calculated total distance
				total_distance -= shortest_distance; 
				reached_end = 0;
			}

			//set current track to new position, print position
			current_track = sequence[index_of_shortest];
			printf("%d ", current_track);
		}
		else{ // else jump to track zero
			total_distance += current_track;
			current_track = 0;
			reached_end = 1;
		}
	}

 	// print total distance traversed

 	printf("\n Total amount of traversed tracks: %d", total_distance);
	return;

} 



void free_memory() {

	// if sequence is not NULL, free sequence

	if(sequence != NULL){
		free(sequence);
	}
    
    printf("\n Quitting program...");
	return;

} 


int main() {
    int choice = 0;
    while(choice != 6) {
        printf("\n\n Disk Scheduling \n ---------------- \n 1) Enter parameters \n 2) Calculate distance to traverse tracks using FIFO \n 3) Calculate distance to traverse tracks using SSTF \n 4) Calculate distance to traverse tracks using Scan \n 5) Calculate distance to traverse tracks using C-Scan \n 6) Quit and free memory \n");
        printf("\n Enter Selection: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: printf("\n Disk Initialization (Option 1) selected. \n\n"), disk_init(); break;
            case 2: printf("\n First-In-First-Out Scheduling (Option 2) selected. \n\n"), fifo_disk_scheduling(); break;
            case 3: printf("\n Shortest-Seek-Time-First Scheduling (Option 3) selected. \n\n"), sstf_disk_scheduling(); break;
            case 4: printf("\n Scan Scheduling (Option 4) selected. \n\n"), scan_disk_scheduling(); break;
            case 5: printf("\n C-Scan Scheduling (Option 5) selected. \n\n"), c_scan_disk_scheduling(); break;
            case 6: printf("\n Free Memory and Quit (Option 6) selected.  \n\n"), free_memory(); break;
            default: printf("\n Invalid option!\n"); break;
        }
    }
    return 1;
}
