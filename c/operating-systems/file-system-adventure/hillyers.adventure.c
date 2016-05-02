/*******************************************************************************
* File:         hillyers.adventure.c
* Author:       Shawn S Hillyer
* Date:         April 19, 2016
* Description:  
* Creates a series of files that hold descriptions of "rooms" and how they are
* connected; offer to player an interface for playing game using generated
* rooms; exit and display path taken by player
*******************************************************************************/

/* Includes */
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

/* Constants */
#define MIN_CONNECTIONS 3
#define MAX_CONNECTIONS 6
#define MAX_ROOMS 7
#define TOTAL_ROOM_NAMES 10
#define MAX_NAME_LEN 20

const char *USERNAME = "hillyers";
const char *ROOM_NAMES[] = {
	  "Hell's Kitchen"
	, "Manhattan"
	, "Lincoln Tunnel"
	, "SOHO"
	, "Brooklyn Bridge"
	, "Roosevelt Island"
	, "Washington Heights"
	, "Queens"
	, "Rikers Island"
	, "Bronx"
 };

/* Enums */
enum room_type { START_ROOM=0, END_ROOM=1, MID_ROOM=2 };

/* Structs */
struct Room {
	char name[MAX_NAME_LEN];         // a name from the ROOM_NAMES[] array
	int connections;                 // Tally of actual number of connections
	char conn_names[MAX_CONNECTIONS][MAX_NAME_LEN]; // array of strings
	enum room_type type;
	int connected_matrix[MAX_ROOMS]; // 1=connected, 0=not
};

/* Forward-declarations */
// struct Room;
void shuffle_array(int arr[], int n);
void swap(int arr[], int i, int j);
void generate_connections(struct Room rooms[], int size);
void write_to_file(struct Room rooms[], int size);
char * get_directory_name();
void print_location(struct Room rooms[], int i);
int is_connected(struct Room rooms[], int size, int i, char user_string[]);
void print_congratulations(int steps, char ** path);
int get_new_location(struct Room rooms[], int size, char user_string[]);


/*******************************************************************************
* generate_rooms()
* Create 7 different Room structs, one room per file, in a directory called
* <username>.rooms.<process id>
* <username> is hardcoded (See constant USERNAME near header)
* Each room has a room name, 3-6 connections (random), and a type. Connections
* are randomly assigned. All connections must be bidirectional. No room type 
* can be used more than once.
*******************************************************************************/
void generate_rooms(struct Room rooms[], int size) {
	int i, j;
	// Assign names by shuffling an array of values [0..TOTAL_ROOM_NAMES] and
	// selecting first size integers in the array during the init loop
	int rand_indices[10];
	for (i = 0; i < TOTAL_ROOM_NAMES; i++) {
		rand_indices[i] = i;
	}
	shuffle_array(rand_indices, TOTAL_ROOM_NAMES);

	// Initialize each room before making connections
	for (i = 0; i < size; i++) {
		// Set # of connections to 0 and set all connections to 0 except self
		rooms[i].connections = 0;
		for (j = 0; j < MAX_ROOMS; j++) {
			rooms[i].connected_matrix[j] = 0;
		}

		// Set name to name in unique and random index
		strcpy(rooms[i].name, ROOM_NAMES[rand_indices[i]]);
		
		// Set type; random order already so pick the first two as start/end
		enum room_type current_type;
		if (i == 0) current_type = START_ROOM;
		else if (i == 1) current_type = END_ROOM;
		else current_type = MID_ROOM; // All other elements are middle
		rooms[i].type = current_type;
	}

	// Connect the rooms then write the rooms to files
	generate_connections(rooms, size);
	write_to_file(rooms, size);
}


/*******************************************************************************
* generate_connections()
* Subroutine for generate_rooms. Takes an array of rooms and creates logical
* connections between each of them randomly.
* NOTE: We know that a graph with 7 nodes and every node having 3 undirected 
* edges must be connected, so no need to verify that a path from START to END 
* actually exists. This can be proved by diagramming connections on a 7 vertex
* graph with only 2 edges per node and then adding a third to any one node. This
* will force the graph to be connected as the two circuits are joined.
*******************************************************************************/
void generate_connections(struct Room rooms[], int size) {
	int i,         // Loop counter 
	    rand_indx, // Random index to attempt a connection
	    extra;     // Number of extra connections to make

	// Iterate through rooms; connect to 3+extra other rooms
	for (i = 0; i < size; i++) {
		// Give a chance to add extra connections. Using 0-3 causes a float up
		// leaving no nodes with only 3; 0 to 2 tends to not
		extra = rand() % 2; // rand_int_in_range(0, 3);

		// connect rooms until we've made requisite number of connections
		while (rooms[i].connections < MIN_CONNECTIONS + extra) {
			// Try to connect to random node; increment until it succeeds
			rand_indx = rand() % size;
			do {
				// Increment forward if random node failed to connect
				rand_indx = (++rand_indx) % size;
			} while( !connect_rooms(rooms, i, rand_indx) );
		}
	}
	return;
}


/*******************************************************************************
* connect_rooms()
* Subroutine for generate_connections. Associates two rooms together by creating
* a bidirectional linkage between the two rooms. 
* Returns 0 if fails, 1 if succeeds
*******************************************************************************/
int connect_rooms(struct Room rooms[], int i, int j) {
	// cannot connect to self, already connected, or either at max connections
	if (   i == j
		|| rooms[i].connected_matrix[j] == 1
		|| rooms[j].connections == MAX_CONNECTIONS
		|| rooms[i].connections == MAX_CONNECTIONS 
		)
		return 0;
	// otherwise connect in both directions and return success 	
	else {
		rooms[i].connected_matrix[j] = 1;
		rooms[j].connected_matrix[i] = 1;
		rooms[i].connections = rooms[i].connections + 1;
		rooms[j].connections = rooms[j].connections + 1;
		return 1;
	}
}


/*******************************************************************************
* shuffle_array()
* Shuffles an array of values
* cite: www.vogella.com/tutorials/JavaAlgorithmsShuffle/article.html
*******************************************************************************/
void shuffle_array(int arr[], int n) {
	// Get random number from i to n, swap element at i with ele at n
	int i;
	for (i = 0; i < n; i++) {
		int random = i + (rand() % (n - i));
		swap(arr, i, random);
	}
}


/*******************************************************************************
* swap()
* Swaps two elements of an array at indices i and j
* cite: www.vogella.com/tutorials/JavaAlgorithmsShuffle/article.html
*******************************************************************************/
void swap(int arr[], int i, int j) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}


/*******************************************************************************
* write_to_file()
* Create 7 different Room files, one room per file, in a directory called
* <username>.rooms.<process id>
* <username> is hardcoded (See constant USERNAME near header)
* Data comes from an array of struct Room
*******************************************************************************/
void write_to_file(struct Room rooms[], int size) {
	int i, j;
	char * directory = get_directory_name();

	// Make the directory using mkdir()
	// Cite: http://linux.die.net/man/3/mkdir
	mkdir(directory, 0777); // make directory rwx/rwx/rwx for user/grp/world
	
	// Move into the new directory and start writing the files
	// http://linux.die.net/man/3chdir
	chdir(directory);

	// For each Room in the array, write the data
	for (i = 0; i < size; i++) {
		// Open the file for writing, then write each section per specification
		FILE * room_file = fopen (rooms[i].name, "w");
		fprintf(room_file, "ROOM NAME: %s\n", rooms[i].name);
		
		// Loop through the connected_matrix to get strings to write
		int n = 1;
		for (j = 0; j < MAX_ROOMS; j++) {
			if (rooms[i].connected_matrix[j] == 1) {
				fprintf(room_file, "CONNECTION %d: %s\n", n++, rooms[j].name);
			}
		}
		
		// Print the room type depending on setting and an extra newline at end
		fprintf(room_file, "ROOM TYPE: ");
		int type = rooms[i].type;
		switch (type) {
			case START_ROOM: fprintf(room_file, "START_ROOM\n"); 
					break;
			case END_ROOM: fprintf(room_file, "END_ROOM\n"); 
					break;
			case MID_ROOM: fprintf(room_file, "MID_ROOM\n"); 
					break;
		}
		// close the file
		fclose(room_file);
	}

	// Go back up a directory
	chdir(".."); 
}


/*******************************************************************************
* read_from_file()
* Parse all of the files in the directory into the struct Room
* Opens the directory, then processes all of the files, parsing for the needed
* data using sscanf after checking what data is on the line using strstr
*******************************************************************************/
void read_from_file(struct Room rooms[], int size) {
	int i = 0;
	char * directory = get_directory_name();
	chdir(directory);

	// Get a list of all the files using opendir()
	// Cite: stackoverflow.com/questions/612097, 
	// Cite: pubs.opengroup.org/onlinepubs/007908775/xsh/dirent.h.html

	DIR *dir;
	struct dirent *entry;

	// We've already changed into the directory we want, so just open cwd
	if ((dir = opendir (".")) != NULL) {
		// While there are files in the directory, get & process next entry
		// Also ends loop if we read too many files (shouldn't happen!)
		while ((entry = readdir(dir)) != NULL && i < size) {
			// Skip entry if filename is "." or ".." (current or parent directory)
			if (strcmp(entry->d_name, ".") == 0 
				|| strcmp(entry->d_name, "..") == 0) {
				continue; 
			}

			// Open the current file for reading, then read in each part of struct
			FILE * room_file = fopen(entry->d_name, "r");
			int buff_size = 250;
			char line[buff_size];
			char word_1[20];
			char contents[buff_size]; // used to store name of connections/type
			int conn_number; // Not really using, just dmping from sscanf
			int n = 0;
			
			rooms[i].connections = 0; // init before entering next loop

			// While we can read lines from the file, parse and fill rooms[i] struct
			// Cite: sscanf basics: www.cplusplus.com/reference/cstdio/sscanf
			while(fgets(line, buff_size - 1, room_file)) {
				// If the line is the ROOM NAME, read name from file into struct
				if(strstr(line, "ROOM NAME") != NULL) {
					sscanf(line, "ROOM NAME: %19[ a-zA-Z']s", rooms[i].name);
					// printf("rooms[%d].name=%s\n", i, rooms[i].name);
				}

				// If line is a CONNECTION line, increment .connections and read
				// the name of connection to the array of connection strings
				else if (strstr(line, "CONNECTION") != NULL) {
					// Read up to 19 characters into contents[] and copy into struct arr
					// This saves room for the null byte. 
					sscanf(line, "CONNECTION %d: %19[ a-zA-Z']s", &conn_number, contents);
					char * conn_name = rooms[i].conn_names[n++]; // readability purposes
					strcpy(conn_name, contents);
					rooms[i].connections++;
				}

				// If line is ROOM TYPE line, parse the type and set type as appropriate
				else if (strstr(line, "ROOM TYPE") != NULL) {
					sscanf(line, "ROOM TYPE: %s", contents);
					if (strstr(contents, "MID_ROOM") != NULL) {
						rooms[i].type = MID_ROOM;
					}
					else if (strstr(contents, "START_ROOM") != NULL) {
						rooms[i].type = START_ROOM;
					}
					else if (strstr(contents, "END_ROOM") != NULL) {
						rooms[i].type = END_ROOM;
					}
					else {
						printf("This is bad!!");
						return;
					}					
				}
			} // end while fgets
			// Close file, move to next element of array
			fclose(room_file);
			i++;
		} // end while readdir
		closedir(dir);
	} // end if read worked

	else {
		// Could not open directory
		perror("");
		return;
	}

	free(directory);
}


/*******************************************************************************
* get_directory_name()
* Returns a pointer to a directory name string 
* Format: <username>.rooms.<process id>
* username is hardcoded per assignment specifications
*******************************************************************************/
char * get_directory_name() {
	pid_t pid = getpid();
	char roomstr[] = ".rooms.";

	// Copy three parts of string into a string so we can make directory
	// Cite: www.cplusplus.com/reference/cstdio/sprintf
	int buff_size = strlen(USERNAME) + 20 + strlen(roomstr);
	char* directory = malloc(sizeof(char) * buff_size); // 

	sprintf(directory, "%s%s%d", USERNAME, roomstr, pid);
	return directory;
}


/*******************************************************************************
* play_game()
* Main loop. Presents menu to user, gets input, and presents winning message
*******************************************************************************/
void play_game() {
	char * directory = get_directory_name();

	// Allocate array of Room structs, read the data from file structure back in
	struct Room * rooms = malloc (sizeof(struct Room) * MAX_ROOMS);
	read_from_file(rooms, MAX_ROOMS);

	// Init win condition bool, setup lookup table for Room names into index
	int player_has_won = 0; // 1 = true, 0 = false
	int steps_taken = 0;
	int start_index = -1;
	int end_index = -1;
	int current_location;   // Index of current room as stored in rooms[]
	
	// Create and initialize Array of strings to store the path user takes in
	// Cite: stackoverflow.com/questions/5935933 (for dynamic array allocation)
	char ** path_list;
	int path_list_size = MAX_ROOMS * 2; // just a default starting size
	path_list = malloc(path_list_size * sizeof(char *));
	int i;
	for (i = 0; i < path_list_size; i++) {
		path_list[i] = malloc(MAX_NAME_LEN * sizeof(char));
	}

	// Search for the START_ and END_ROOM indices to start/end game loop
	for (i = 0; i < MAX_ROOMS; i++) {
		if(rooms[i].type == START_ROOM)
			start_index = i;
		if(rooms[i].type == END_ROOM)
			end_index = i;
	}
	current_location = start_index;

	// Variables for user input of strings
	char user_string[MAX_NAME_LEN];
	int success = 0; // set to true if the input included only valid character types

	// main game loop
	while(!player_has_won) {
		// Print current location and prompt user for input
		print_location(rooms, current_location);
		printf("WHERE TO? >");
		
		// read input, trim off the \n, then see if it is in the array of connected
		fgets(user_string, sizeof(user_string), stdin);
		user_string[strlen(user_string)-1] = '\0';

		printf("\n");

		// If input is in connected names array for current room
		if (is_connected(rooms, MAX_ROOMS, current_location, user_string) == 1) {
			// Make sure path_list isn't full - realloc if it is
			if (steps_taken == path_list_size) {
				path_list_size *= 2;
				path_list = realloc(path_list, path_list_size * sizeof(char *));
				int k;
				for (k = steps_taken; k < path_list_size; k++) {
					path_list[k] = malloc(MAX_NAME_LEN * sizeof(char));
				}	
			}

			// add new location to path list, increment steps taken by 1
			strcpy(path_list[steps_taken++], user_string);

			// update current_location to index of new room
			current_location = get_new_location(rooms, MAX_ROOMS, user_string);

			// Check to see if player has won
			if (current_location == end_index) {
				// print congrats message, steps, path
				print_congratulations(steps_taken, path_list);
				// Set win condition to true -- we end up back in main
				player_has_won = 1;
			}
		}
		// else if input is not in connected rooms array print error message
		else {
			printf("HUH? I DON'T UNDERSTAND THAT ROOM. TRY AGAIN.\n\n");
		}
	}
	// Free the rooms array
	free(rooms);
	free(directory); // w as dynamically allocated in get_directory_name
	int k;
	for (k = 0; k < path_list_size; k++) {
		free(path_list[k]);
	}
	free(path_list);
}


/*******************************************************************************
* print_location()
* Displays the information to player about the location they are in, passed in
* as the argument, i, including the connection names
*******************************************************************************/
void print_location(struct Room rooms[], int i) {
	printf("CURRENT LOCATION: %s\n", rooms[i].name);
	printf("POSSIBLE CONNECTIONS: ");
	
	// Print each connection separated by comma except last
	int j;
	for (j = 0; j < rooms[i].connections - 1; j++) {
		printf("%s, ", rooms[i].conn_names[j]);
	}

	// Print last connection, period, newline
	printf("%s.\n", rooms[i].conn_names[j]);
}


/*******************************************************************************
* is_connected()
* returns 1 if the room at index i is connected to a room with the name passed 
* in by user_string; returns 0 if not
*******************************************************************************/
int is_connected(struct Room rooms[], int size, int i, char user_string[]) {
	int j;
	for (j = 0; j < rooms[i].connections; j++) {
		if (strcmp(rooms[i].conn_names[j], user_string) == 0)
			return 1;
	}

	// If not found, return false
	return 0;
}


/*******************************************************************************
* get_new_location()
* returns index in rooms[] of the room with .name == user_string
*******************************************************************************/
int get_new_location(struct Room rooms[], int size, char user_string[]) {
	int i;
	for (i = 0; i < size; i++) {
		if (strcmp(rooms[i].name, user_string) == 0)
			return i;
	}	
}


/*******************************************************************************
* print_congratulations()
* Prints congrats message including number of steps and the path to victory
*******************************************************************************/
void print_congratulations(int steps, char ** path) {
	printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", steps);
	
	// Print out the list of steps taken, one per line
	int i;
	for (i = 0; i < steps; i++) {
		printf("%s\n", path[i]);
	}
}


/*******************************************************************************
* main()
* Creates a series of files that hold descriptions of "rooms" and how they are
* connected; offer to player an interface for playing game using generated
* rooms; exit and display path taken by player
*******************************************************************************/
int main(int argc, char const *argv[]) {
	// Seed random numbers
	srand(time(NULL));

	// Generate rooms
	struct Room rooms[MAX_ROOMS];
	generate_rooms(rooms, MAX_ROOMS);

	// Initiate player input loop / main 'game' logic
	play_game();

	// Game loop ends when exit found, return 0 for success.
	// Can verify with 'echo $?' that exit code is 0 from command line prompt
	return 0;
}