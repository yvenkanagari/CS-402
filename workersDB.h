#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define MAXNAME 64
#define MAXCAPACITY 1024

struct Employee{
 char firstname[MAXNAME];
 char lastname[MAXNAME]; 
 int id;
 int salary;
 };

// Count the number of digits in an integer
static inline int count_digs(int n){
    int count = 0;
    do{
        count++;
        n/= 10;
    } while(n != 0);
    return count;
}


// Remove any white spaces at the beginning or the end
static inline char *trim(char *str){
  char *end;
  while(isspace((unsigned char)*str)) str++;
  
  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

// Count the number of lines in the text file containing all the data
int count_lines(char* filename);

// perform the bubble sort to sort by ID
void bubbleSort();

// Check if input line is a valid DB Schema
int check_valid(char *line);

// Read the database items
int read_db(char* filename);

// Print a single row of the DB
void print_cell(int i);

// Print DB
void print_db();

// Print menu
void print_menu();

// Lookup user by id
void lookup_id();

// Lookup user by last name
void lookup_last();

// Add newb entry
void add_new();