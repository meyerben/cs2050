#include <stdlib.h>
#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct node_ { 
	int data;
	struct node_* prev;
	struct node_* next;
} Node;

struct queue{
    Node front;
    Node back;
};

/*
 * Parameters: 
 * head - The current head of the queue
 * data - The data to be enqueued
 *
 * Return: 
 * The new head of the queue
 *
 * The function will take in the head of
 * a queue and a new piece of data
 * and enqueue (insert at the end)
 * that data into the queue
 */
Node* enqueue(Node* queue, int data);
void print_list(Node* head);

int main(void) {
	Node* queue = NULL;
	int i;
	for (i = 0; i < 4; i++) {
		queue = enqueue(queue, i);
	}
	print_list(queue);
	for (i = 0; i < 4; i++) {
		if (queue == NULL) {
			printf(ANSI_COLOR_RED "The queue is too short!\n" ANSI_COLOR_RESET);
			return 1;
		}

		if (queue->data != i) {
			printf(ANSI_COLOR_RED "The queue is out of order!\n" ANSI_COLOR_RESET);
			return 2;
		}

		Node* prev = queue;
		queue = queue->next;
		free(prev);
	}

	printf(ANSI_COLOR_GREEN "You have completed the prelab!\n" ANSI_COLOR_RESET);
	return 0;
}

Node* enqueue(Node* queue, int data) {
	if(queue == NULL)
	{
		Node *newqueue = (Node*)malloc(sizeof(Node));
		newqueue->data = data;
		newqueue->next = NULL;
		return newqueue;
	}
	Node* queue2 = queue;
	while(queue2->next != NULL)
	{
		queue2 = queue2->next;
	}
	
	Node *newqueue = (Node*)malloc(sizeof(Node));
	queue2->next = newqueue;
	newqueue->data = data;
	newqueue->next = NULL;
	return queue;
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
