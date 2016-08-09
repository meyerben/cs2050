/*
Ben Meyer
bjmgy4
lab 6 
Section D
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//define your node
typedef struct node_{
    int data;
    struct node_* next;
} Node;

//Prototypes
Node* build_list(const char* filename);
void print_list(Node* head);
void multiply_by(Node* head, int val);
void free_list(Node* head);
Node* reverse_list(Node* head);

int main(int argc, char* argv[])
{
    int val;
    Node* head = build_list(argv[1]); //call build_list function to build a list from a file
    print_list(head); //print out the list we just built
    printf("Enter a number to multiply: "); 
    scanf("%d",&val);
    multiply_by(head, val); //multiply all the values of the list by the new value
    print_list(head); //print out the modified list
    
    
    printf("\nBonus\n");
    //Node* newhead = reverse_list(head); //creates a new list from the reverse_list function
    //print_list(newhead); //prints out our brand new list
    free_list(head); //free the linked list we created
    //free_list(newhead); //free the second list
    return 0;
}

Node* build_list(const char* filename){
    Node* curr; 
    Node* head = NULL;//initialize the linked list with NULL
	FILE* fptr = fopen(filename, "r"); //open the file
	if(fptr == NULL)printf("boink");
	while(1)
	{
		if(feof(fptr)) break; //while there are still values in the file
		
		curr = (Node*)malloc(sizeof(Node)); //create space for the new node
		
	    fscanf(fptr, "%d\n", &curr->data); //give a value to the new node
	    
	    curr->next = head; //set the new node to point to previous node
	    
	    head = curr; //move the head to front of the list
	    
	}
	fclose(fptr); //close the file
	return head; //return our new pointer
}

void print_list(Node* head){
    if(head == NULL) return;
    while(head!=NULL) //iterate through list
    {
        printf("%d -> ", head->data); //prints the data for the head in a pretty format
        head = head->next; //moves the head to the next pointer
    }
    printf("NULL \n"); //more pretty formatting
}

void multiply_by(Node* head, int val){
    while(head!=NULL)//iterate through list
    {
        head->data *= val; //multiply the new value to the data
        head = head->next; //move the head to the next pointer
    }
}

void free_list(Node* head){
    Node* curr = head; //create new node pointer
    while(head!=NULL)
    {
       curr = curr->next; //set new pointer to the next node
       free(head); //free the current pointer
       head = curr; //move head to the next pointer
    }
}

//This function is very similar to the make_list function, but we read in values from a linked list instead of a file
Node* reverse_list(Node* head){
    Node* curr; //create a current pointer
    Node* newhead = NULL;
    while(1)
    {
        if(head == NULL) break;
        curr = (Node*)malloc(sizeof(Node));
        curr->data = head->data;
        head = head->next;
        curr->next = newhead;
        newhead = curr;
    }
    return newhead;
}