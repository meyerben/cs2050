#include "game.h"

//Knock yourself out boys and girls. 

Boss* loadBoss()
{
    FILE* fp = fopen("Boss.txt","r");
    if(fp == NULL)
    {
        printf("The file is wonky");
        return NULL;
    }
    
    //INITIALIZE THE BOSS
    Boss* theboss = malloc(sizeof(Boss)); //currently listening exclusively to bruce springsteen
    //scan in values from first line
    fscanf(fp, "%s | %d | %d | %d | %d", 
    theboss->name , &theboss->maxHealth , &theboss->baseDefense,
    &theboss->baseAttack, &theboss->baseSpeed);
    theboss->health = theboss->maxHealth;
    theboss->root = NULL;
    
    
    DecisionTreeNode* root = NULL;
    int numActions;
    //iterates through each tree node of the file
    while(1)
    {
        if(feof(fp)) break;
        
        numActions = 0;
        
        
        
        //INITIALIZE TREENODE
        DecisionTreeNode* newNode = malloc(sizeof(DecisionTreeNode));
        newNode->left = NULL;
        newNode->right = NULL;
        //scan your values into your new tree node
        fscanf(fp, "%d | %d | %d", &newNode->healthFloor, &newNode->healthCeiling, &numActions);
        
        newNode->FirstAction = NULL;
        
        //then attach a queue to your new tree node
        int i;
        for(i=0;i<numActions;i++)
        {
            //create space for a new queue node
            ActionNode* newANode = (ActionNode*)malloc(sizeof(ActionNode));
            //scan the data in from the file
            fscanf(fp, "%u", &newANode->decision );
            //put the node in its rightful place in the queue
            newNode->FirstAction = addActionToList(newNode->FirstAction, newANode);
        }
        
        //then put your tree node(with queue already attached) into a BST
        root = addNodeToTree(root, newNode);
        
    }
    //now you attach your bst to your boss
    theboss->root = root;
    return theboss;
}

ActionNode* addActionToList(ActionNode* front, ActionNode* newAction)
{
    //if there are no actions
    if(front == NULL)
    {   
        //simon says it has to point to NULL
        newAction->next = NULL;
        //put your shiny new action at the front
        return newAction;
    }
    //make a pointer so you dont have to move your front pointer
    ActionNode* curr = front;
	//iterate through to the end of the list 
	while(curr->next != NULL)
	{
	    curr = curr->next;
	}
	//add your shiny new action on the end
	curr->next = newAction;
	//simon still says it has to point to NULL
	newAction->next = NULL;
	
	return front;
}

DecisionTreeNode* addNodeToTree(DecisionTreeNode* root, DecisionTreeNode* newNode)
{
    
    
    //create new node and return
	if(root == NULL)
	{
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode; 
	}
	//insert to the right
	if( newNode->healthCeiling > root->healthCeiling)
	{
	    //recursion till base case
		root->right = addNodeToTree(root->right, newNode);
		return root;
	}
	//insert to the left
	if(newNode->healthCeiling < root->healthCeiling)
	{
	    //recursion again
		root->left = addNodeToTree(root->left, newNode);
		return root;
	}
    return root;
}

ActionNode* fetchNewList(Boss* boss, DecisionTreeNode* root)
{
    //This function is a binary tree search
    //base case: if you have found the node (health is within floor and ceiling)
    if(  root->healthFloor <= boss->health && boss->health <= root->healthCeiling)
    {
        //pointer to first action
        return root->FirstAction;
    }
    
    //if your health is less than the floor, 
    //you should probably check the left side of this node
    else if( boss->health <= root->healthFloor)
    {
        return fetchNewList(boss, root->left);
    }
    
    //if your health is more than the ceiling
    //you should definitely be looking to the right of this node
    else
    {
        return fetchNewList(boss, root->right);
    }
}



void freeBossTree(DecisionTreeNode* root)
{
    //free each node in the tree
	if(root == NULL)
		return;
	//traverse right tree
	freeBossTree(root->right);
	free(root);

	//traverse left tree
	freeBossTree(root->left);
}

void freeActionListInNode(ActionNode* head)
{
    Node* curr = head; //create new node pointer
    while(head!=NULL)
    {
       curr = curr->next; //set new pointer to the next node
       free(head); //free the current pointer
       head = curr; //move head to the next pointer
    }
}
