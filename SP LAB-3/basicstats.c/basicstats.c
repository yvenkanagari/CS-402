#include<stdio.h>
# include <string.h>
#include <stdlib.h>
#include<math.h>

struct Node
{
    double data;
    struct Node* next;
};

/* inserting data in linked list*/
void push(struct Node** head_ref, double new_data)
{
    /* allocate node */
    struct Node* new_node =
        (struct Node*) malloc(sizeof(struct Node));
 
    /* put in the data */
    new_node->data = new_data;
 
    /* link the old list off the new node */
    new_node->next = (*head_ref);
 
    /* move the head to point to the new node */
    (*head_ref) = new_node;
}

/* discovering median using middle function */
void printMiddle(struct Node *head)
{
    struct Node *slow_ptr = head;
    struct Node *fast_ptr = head;
 
    if (head!=NULL)
    {
        while (fast_ptr != NULL && fast_ptr->next != NULL)
        {
            fast_ptr = fast_ptr->next->next;
            slow_ptr = slow_ptr->next;
        }
        printf("The median of the numbers is: %f\n\n", slow_ptr->data);
    }
}

int main(){
	FILE *f ; 
	double sum = 0, mean = 0, tmp = 0,std_dev = 0;
	int i = 0;
	struct Node* head = NULL;
	/* reading numbers in text file */
	f = fopen("num.txt", "r") ;
	/* Checking if the file is null */
	if ( f == NULL )
	{
        	printf( "file failed to open. Check again" ) ;
        	exit(-1);
	}
	printf("The numbers in the file are:\n");
	/* Finding sum of all numbers in file */
	while(!feof(f))
	{
	  fscanf(f, "%lf", &tmp);
	  printf("tmp = %f \n", tmp);
	  push(&head, tmp);
	  sum += tmp;
	  i++;
	}
	printf("\n");
	mean = sum / i;
	printf("The number of values: %d \n\n",i);
	/* printing mean of the numbers */
	printf("The mean of the numbers is: %f \n\n",mean);
	/* calling printMiddle function which calculates mode of numbers */
	printMiddle(head);
	int j = 0;
	sum = 0;
	struct Node *dev_ptr = head;
	/* Finding standard deviation of the numbers */
	while(j<i){
		sum += (mean - dev_ptr->data)*(mean - dev_ptr->data);
		dev_ptr = dev_ptr->next;
		j++;
	}
	sum = sum / j;
	std_dev = sqrt(sum);
	printf("The Standard deviation of the numbers is: %f \n\n",std_dev);
	printf("Unused capacity of array is: %d \n\n",i*4);
	/* Closing the file */
	fclose(f);
	return 0;
}
