/*
 * struct_sort.c
 *
 * This program reads the contact information from any given text, 
 * sorts them by last names and writes the sorted output to 
 * another text file.
 *
 *  Created on: Feb 25, 2016
 *      Author: Gajjan Jasani
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "myHeader.h"

/* Variable to keep track of number of contacts (structs) */
int counter;

/*
 *  Function: main
 *  Use: The entry point to this program. This function 
 *  makes sure the number os arguments provided matches the 
 *  program requirements, calls low level functions to read from 
 *  contacts from file, sort them and write the sorted contacts to 
 *  another file
 *  argc  : number of arguments provided
 *  argv[]: array to hold arguments
 */

int main(int argc, char* argv[]){
	// pointer for input file
	FILE* in_file;
	// pointer for output file
	FILE* out_file;

	// Making sure 3 arguments are provided at the beginning 
	// of the program
	if(argc != 3) {
		printf("Usage: struct_sort inputFile outputFile\n");
		exit(1);
	}
	
	// Making sure the input file is readable
	in_file = fopen(argv[1],"r");
	if(in_file == NULL) {
		fprintf(stderr,
				"ERROR: couldn't open %s for reading\n",
												argv[1]);
		exit(1);
	}

	// Making sure the output file is readable
	out_file = fopen(argv[2],"w");
	if(out_file == NULL) {
		fprintf(stderr,
				"ERROR: couldn't open %s for writing\n",
												argv[2]);
		exit(1);
	}

	// Calling helper functions to read, sort and write contacts
	createStructs(in_file);
	sort();
	writeToFile(out_file);

	// closing the open files after done using them
	fclose(in_file);
	fclose(out_file);

	return 0;
}

/*
 *  Function: createStructs
 *  Use: Read the contacts from input file, break them and and
 *  store them into structs, and store those structs in struct
 *  array
 *  in: Pointer to the input file
 */
void createStructs (FILE* in){
	
	// array to store the line read from input file
	char buffer[LINE_LENGTH];
	counter = 0;

	// breaking the line in to appropriate string and storing
	// them in struct
	while(fgets(buffer, sizeof(buffer), in) != NULL) {

		sscanf(buffer , " %[^,], %[^,], %[^,], %[^,], "
				"%[^,], %[^,], %[^,\n]", data[counter].first_name,
				data[counter].last_name,
				data[counter].address.street_address,
				data[counter].address.city,
				data[counter].address.state,
				data[counter].address.zipCode,
				data[counter].phone);
		counter++;		// counting the number of structs
	}
}

/*
 *  Function: sort
 *  Use: Sort the structs (contacts) using the last name of the 
 *  contacts ignoring the case. If the last name are the same
 *  then compare the first name
 */

void sort(){
	
	// counters for the sorting loops
	int l, m;
	// making sure the global variable doesn't change to
	// avoid side effects
	int n = counter;
	// temporary struct to for swapping purpose
	person_t temp;

	// Sorting the structs/contacts
	for (l = 0; l < n; l++) {
		for (m = 0; m < n - 1; m++) {
			// if the last names are not equal
			if (strcmp(toUpper(data[m].last_name),
					   toUpper(data[m+1].last_name)) > 0) {
				temp = data[m];
				data[m] = data[m + 1];
				data[m+1] = temp;
			// if the last names are equal compare 
			// first names
			} else if (strcmp(toUpper(data[m].last_name),
					toUpper(data[m+1].last_name)) == 0){
				if (strcmp(toUpper(data[m].first_name),
						toUpper(data[m+1].first_name)) > 0) {
					temp = data[m];
					data[m] = data[m + 1];
					data[m+1] = temp;
				}
			}
		}
	}
}

/*
 *  Function: writeToFile
 *  Use: Write the sorted contacts from structs to the output file
 *  out: pointer to the output file
 */
void writeToFile(FILE* out){

	int j = 0;
	
	while(j < counter){
		// formatting the output line for uniformity
		fprintf(out, "%s, %s, %s, %s, %s, %s, %s\n",data[j].first_name,
				data[j].last_name, data[j].address.street_address,
				data[j].address.city, data[j].address.state,
				data[j].address.zipCode, data[j].phone);
		j++;
	}
}

/*
 *  Helper Function: toUpper
 *  Use: Create an all upper case copy of a given string
 *  for comparision purpose without modifying the given
 *  string
 *  anyString: string that needs to be converted to all upper case
 *  Return: All upper case copy of the given string
 *
 */
char* toUpper(char* anyString){

	int i = 0;
	char* upper = calloc (sizeof(char), 20);

	while(anyString[i]){
		upper[i] = toupper(anyString[i]);
		i++;
	}

	return upper;
}
