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

//Prototypes:
Node* enqueue(Node* front, int data);
int dequeue(Node** frontPtr);
void printQueue(Node* front);
void freeQueue(Node* front);
Node* filterEven(Node* head);


int main(void)
{
    Node* queue = NULL;
    int option;
    int val;
    int gate;
    printf("Enter 1 to Enqueue\nEnter 2 to Dequeue\nEnter 3 to quit\n>");
    scanf("%d", &option);
    
    while(gate !=0) {
        switch(option) {
            case(1):
                printf("Enter a number to enqueue:");
                scanf("%d", &val);
                queue = enqueue(queue, val);
                printQueue(queue);
                printf(">");
                scanf("%d", &option);
                break;
            case(2):
                
                printf("%d was dequeued\n",dequeue(&queue));
                printf(">");
                scanf("%d", &option);
                //printf("%d was dequeued\n",dequeue(queueptr));
                break;
            case(3):
                gate = 0;
                break;
        }
    }
    
    printf("Bonus!");
    
    //filterEven(queue);
    //printQueue(queue);
    freeQueue(queue);
    return 0;
}




Node* enqueue(Node* front, int data) {
	if(front == NULL)
	{
		Node *newqueue = (Node*)malloc(sizeof(Node));
		newqueue->data = data;
		newqueue->next = NULL;
		return newqueue;
	}
	Node* queuePtr = front;
	while(queuePtr->next != NULL)
	{
		queuePtr = queuePtr->next;
	}
	
	Node *newqueue = (Node*)malloc(sizeof(Node));
	queuePtr->next = newqueue;
	newqueue->data = data;
	newqueue->next = NULL;
	return front;
}

int dequeue(Node** frontPtr){
    
    int num;
    Node *head = (*frontPtr);
    *frontPtr = (*frontPtr)->next;
    num = head->data;
    free(head);
    return num;
}

void printQueue(Node* front){
    if(front == NULL) return;
    while(front!=NULL) //iterate through list
    {
        printf("%d -> ", front->data); //prints the data for the front in a pretty format
        front = front->next; //moves the front to the next pointer
    }
    printf("NULL \n"); //more pretty formatting
}

void freeQueue(Node* front){
    Node* curr = front; //create new node pointer
    while(front!=NULL)
    {
       curr = curr->next; //set new pointer to the next node
       free(front); //free the current pointer
       front = curr; //move head to the next pointer
    }
}

/*
Node* filterEven(Node* head){
    Node* curr = head;
    if(head->data%2 == 0)
    {
        curr = curr->next;
        free(head);
        head = curr;
    }
    
    
    while (curr->next != NULL)
    {
        Node* prev = curr;
        curr = curr->next;
        Node* temp = curr;
        if(curr->data % 2 ==0)
        {
            temp = temp->next;
            free(curr);
            prev->next = temp;
            curr = temp;
        }
        if(curr->next == NULL && curr->data %2 == 0)
        {
            free(curr);
            prev->next = NULL;
        }
    }
    return head;
}
*/

