#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define assert_with_msg(expression, msg) { \
	if (!(expression)) { \
		printf("\x1b[31m%s", msg);\
		assert(expression);\
	}\
}

typedef struct node_ {
	int data;
	struct node_* next;
} Node;

/*
 * Parameters: 
 * filename - The name of an input file
 *
 * Return: The head of a linked list
 *
 * This function will build a linked list
 * from the numbers in the input file. 
 * Unlike previous weeks, the length of
 * this file is UNKNOWN. Every number 
 * in the file should be included in 
 * the linked list. 
 */
Node* build_list(const char* filename);

/*
 * Because this is your first exposure to
 * linked lists, test code has been provided. 
 * After implementing build_list, simply run
 * ./a.out and if you can get the message at 
 * the bottom to print you are finished. 
 */
int main(void) {
	int i;
	//Generates an input file for you to use
	//with the numbers [1, 5)
	const char* filename = "prelab6_input_file.txt";
	FILE* fp = fopen(filename, "w");
	for (i = 0; i < 5; i++) {
		fprintf(fp, "%d\n", i);
	}
	fclose(fp);

	//Calls your build_list function
	Node* head = build_list(filename);

	//This code tests your linked list
	//for correctness. It will check
	//that each node has the correct 
	//value and free your memory as
	//it goes along. If the boolean 
	//condition in one of the assert
	//statements is false then it will
	//crash your program. 
	for (i = 4; i >= 0; i--) {
		char msg[100];
		sprintf(msg, "linked list is to short\ns %d nodes but should be 4\n", 4 - i);
		assert_with_msg(head != NULL, msg);

		sprintf(msg, "linked list nodes are not in correct order\nexpected current node to be %d but was actually %d\n", i, head->data);
		assert_with_msg(head->data == i, msg);
		Node* prev = head;
		head = head->next;
		free(prev);
	}

	printf("Congratulations! You finished the prelab!\n");
	return 0;
}

Node* build_list(const char* filename){
    Node* curr;
    Node* head = NULL;
    //int data;
	FILE* fptr = fopen(filename, "r");
	if(fptr == NULL)printf("boink");
	while(1)
	{
		if(feof(fptr)) break;
		
		curr = (Node*)malloc(sizeof(Node));
		
	    fscanf(fptr, "%d\n", &curr->data);
	    
	    curr->next = head;
	    
	    head = curr;
	    
	}
	return head;
}