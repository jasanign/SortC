/*
 * myHeader.h
 *
 *  Created on: Feb 25, 2016
 *      Author: Gajjan Jasani
 */

#include <stdio.h>

// Defined constants to avoid magic numbers
#define LINE_LENGTH 150
#define NUM_PEOPLE 100

/* data type to store address of a contact */
typedef struct {

	char street_address[50];
	char city[15];
	char state[4];
	char zipCode[7];

} Address;

/* Data type to store contact information */
typedef struct {

	char first_name[15];
	char last_name[15];
	Address address;
	char phone[15];

} person_t;

/* Array to store unsorted contacts */
person_t data[NUM_PEOPLE];

/* Array to store sorted contacts */
person_t sorted_data[NUM_PEOPLE];

/* Function prototypes */
void createStructs(FILE* in);
void sort();
void writeToFile(FILE* out);
char* toUpper(char* anyString);