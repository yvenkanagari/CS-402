/* Assignment
NAME: Yogith
DATE OF SUBMISSION: 30-03-2022

Program break down:

- The program first takes a file as command line input and performs some checks on it
- Then the number of lines are counted
- The program iterates over each line and stores the valid inputs in an array of the struct Employee
- Then, the array is sorted using BubbleSort technique
- Finally, a switch case block is implementes in an infinite loop to perform various actions
*/
#include "workersDB.h"
#include "readfile.h"

// Globals
struct Employee DB[MAXCAPACITY];
int no_of_entries;
int pointer;


// Count the number of lines in the text file containing all the data
int count_lines(char* filename){
    FILE *fp;
    int count = 0;  // Line counter
    char c;  // To store a character read from file

    fp = fopen(filename, "r");

    // Check if file exists
    if (fp == NULL){
        fprintf(stderr,"[!]Could not open file %s\n", filename);
        return 0;
    }

    // Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;

    // Close the file
    fclose(fp);

    return count;
}


// perform the bubble sort to sort by ID
void bubbleSort(){
  // loop to access each array element
  for (int step = 0; step < no_of_entries - 1; ++step) {
      
    // loop to compare array elements
    for (int i = 0; i < no_of_entries - step - 1; ++i) {
      
      // compare two adjacent elements
      // change > to < to sort in descending order
      if (DB[i].id > DB[i+1].id) {
        
        // swapping occurs if elements
        // are not in the intended order
        struct Employee temp = DB[i];
        DB[i] = DB[i+1];
        DB[i+1] = temp;
      }
    }
  }
}


// Check if input line is a valid DB Schema
int check_valid(char *line){
    int i;
    int id;
    int salary;
    int count=1;
    char* words[4];
    char *pch;
    
    // Check if there are 4 words separated by spaces
    for (i = 0; line[i] != '\0'; i++){
        if (line[i] == ' ' && line[i+1] != ' ')
            count++;
    }

    if (count != 4){
        return -1;
    }

    // Put words into array
    count = 0;
    pch = strtok(line, " ");
    while (pch != NULL){
        words[count] = pch;
        count++;
        pch = strtok(NULL, " ");
    }

    // Check Valid ID
    // The six digit ID value must be between 100000 and 999999 inclusive.
    id = atoi(words[0]);
    if(id != 0 && strlen(words[0])==6 && atoi(words[0])==atof(words[0])){
        ;
    }
    else{
        return -1;
    }

    // Salary amounts must be between $30,000 and $150,000 inclusive.
    // The salary is a positive whole number amount (no decimals).
    salary = atoi(words[3]);
    if(salary != 0 && salary>=30000 && salary <= 150000 && atoi(words[3])==atof(words[3]) ) {
        ;
    }
    else{
        return -1;
    }
    
    DB[pointer].id = id;
    DB[pointer].salary =  salary;
    memset(DB[pointer].firstname, 0, MAXNAME);
    memset(DB[pointer].lastname, 0, MAXNAME);
    strncpy(DB[pointer].firstname, words[1], MAXNAME-1);
    strncpy(DB[pointer].lastname, words[2], MAXNAME-1);
    pointer++;
    return 0;
}


// Read the database items
int read_db(char* filename){
    FILE * fp;
    int status = 0;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        char *temp = (char *)malloc(read);
        strcpy(temp, line);
        if (check_valid(temp) != 0){
           status = -1;
        }
        free(temp);
    }

    fclose(fp);
    if (line)
        free(line);
    return status;
}


// Print a single row of DB
void print_cell(int i){
    // print first name
    printf("%s",DB[i].firstname);
    for (unsigned long j=0; j<=(15-strlen(DB[i].firstname)); j++){
        printf(" ");
    }

    // print lastname name
    printf("%s",DB[i].lastname);
    for (unsigned long j=0; j<=(16-strlen(DB[i].lastname)); j++){
        printf(" ");
    }

    // print salary
    printf("%d",DB[i].salary);
    for (int j=0; j<=(8-count_digs(DB[i].salary)); j++){
        printf(" ");
    }

    printf("%d\n", DB[i].id);
}

// Print DB
void print_db(){
    int i;

    // Sort before printing
    bubbleSort();

    // Print
    printf("Name\t\t\t\tSalary\t   ID\n");
    printf("-----------------------------------------------------\n");
    for(i=0; i<no_of_entries; i++){
        print_cell(i);
    }
    printf("-----------------------------------------------------\n");
    printf("Number of Employees (%d)\n", no_of_entries);
}


// Print menu
void print_menu(){
    printf("\nEmployee DB Menu:\n----------------------------------\n(1) Print the Database\n");
    printf("(2) Lookup by ID\n(3) Lookup by Last Name\n(4) Add an Employee\n(5) Quit\n----------------------------------\n");
}


// Lookup user by id
void lookup_id(){
    int id;
    int flag=0;
    printf("Enter a 6 digit employee id: ");
    if(scanf("%d", &id ) <= 0){
        fprintf(stderr,"Invalid ID\n");
        return;
    }

    for(int i=0; i < no_of_entries; i++){
        if(DB[i].id == id){
            printf("Name\t\t\t\tSalary\t   ID\n");
            printf("-----------------------------------------------------\n");
            print_cell(i);
            printf("-----------------------------------------------------\n");
            flag = 1;
        }
    }
    
    if(flag == 0){
        printf("Employee with id %d not found in DB\n", id);
    }

}


// Lookup user by last name
void lookup_last(){
    char lastname[MAXNAME];
    int flag=0;
    printf("Enter Employee's last name (no extra spaces): ");
    if(scanf(" %s", lastname) <= 0){
        fprintf(stderr,"Invalid Lastname\n");
        return;
    }

    for(int i=0; i < no_of_entries; i++){
        if(strcasecmp(DB[i].lastname, lastname)==0){
            printf("\nName\t\t\t\tSalary\t   ID\n");
            printf("-----------------------------------------------------\n");
            print_cell(i);
            printf("-----------------------------------------------------\n");
            flag = 1;
        }
    }
    
    if(flag == 0){
        printf("Employee with lastname %s not found in DB\n", lastname);
    }

}


// Add newb entry
void add_new(){
    char firstname[MAXNAME];
    char lastname[MAXNAME];
    int salary;
    int choice;

    printf("Enter the first name of the employee: ");
    scanf(" %s",firstname);
    trim(firstname);


    printf("Enter the last name of the employee: ");
    scanf(" %s",lastname);
    trim(lastname);

    printf("Enter employee's salary (30000 to 150000): ");
    scanf("%d", &salary);

    printf("do you want to add the following employee to the DB?\n");
    printf("%s %s, salary: %d\n", firstname, lastname, salary);

    printf("Enter 1 for yes, 0 for no: ");
    scanf("%d", &choice);

    if (choice == 1){
        memset(DB[no_of_entries].firstname, 0, MAXNAME);
        memset(DB[no_of_entries].lastname, 0, MAXNAME);
        strncpy(DB[no_of_entries].firstname, firstname, MAXNAME);
        strncpy(DB[no_of_entries].lastname, lastname, MAXNAME);
        DB[no_of_entries].id = DB[no_of_entries-1].id+1;
        DB[no_of_entries].salary = salary;
        no_of_entries ++;
    }
}


// Main function
int main(int argc, char *argv[]){
    int choice;

    // Check for correct command line arguments
    if(argc != 2){
        fprintf(stderr,"[!] Incorrect Usage\n");
        printf("[+] Usage: %s database.txt\n", argv[0]);
        exit(-1);
    }

    // Check if file exists;
    if (access (argv[1],F_OK) != 0 && open_file(argv[1])==0){
        fprintf(stderr, "[!] The file %s does not exist\n", argv[1]);
        exit(-2);
    }

    // Check if the file has any data:
    no_of_entries = count_lines(argv[1]);
    if(no_of_entries==0){
        fprintf(stderr, "[!] Could Not Read Any Data From %s\n ",argv[1]);
        exit(-3);
    }
    
    pointer = 0;
    read_db(argv[1]);
    bubbleSort();
    no_of_entries = pointer;

    while(1){
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                print_db();
                break;
            case 2:
                lookup_id();
                break;
            case 3:
                lookup_last();
                break;
            case 4:
                add_new();
                break;
            case 5:
                printf("goodbye!\n");
                exit(EXIT_SUCCESS);
            default:
                printf("Hey, 10 is not between 1 and 5, try again...\n");
        }
    }

}
