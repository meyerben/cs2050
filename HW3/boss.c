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
    Boss* theboss = malloc(sizeof(Boss));
    //currently listening exclusively to bruce springsteen
    fscanf(fp, "%s | %d | %d | %d | %d", 
    theboss->name , &theboss->maxHealth , &theboss->baseDefense,
    &theboss->baseAttack, &theboss->baseSpeed);
    theboss->health = theboss->maxHealth;
    theboss->root = NULL;
    
    DecisionTreeNode* root = NULL;
    int numActions;
    while(1)
    {
        if(feof(fp)) break;
        
        numActions = 0;
        
        
        
        //INITIALIZE TREENODE
        DecisionTreeNode* newNode = malloc(sizeof(DecisionTreeNode));
        newNode->left = NULL;
        newNode->right = NULL;
        
        fscanf(fp, "%d | %d | %d", &newNode->healthFloor, &newNode->healthCeiling, &numActions);
        
        newNode->FirstAction = NULL;
        
        //fscanf(fp, "%u", &newNode->FirstAction->decision);
        
        int i;
        for(i=0;i<numActions;i++)
        {
            ActionNode* newANode = (ActionNode*)malloc(sizeof(ActionNode));
            fscanf(fp, "%u", &newANode->decision );
            newNode->FirstAction = addActionToList(newNode->FirstAction, newANode);
        }
        
        
        root = addNodeToTree(root, newNode);
        
    }
    theboss->root = root;
    return theboss;
}

ActionNode* addActionToList(ActionNode* front, ActionNode* newAction)
{
    
    if(front == NULL)
    {
        newAction->next = NULL;
        return newAction;
    }
    
    ActionNode* curr = front;
	
	while(curr->next != NULL)
	{
	    curr = curr->next;
	}
	curr->next = newAction;
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
	if(newNode->healthCeiling < root->healthCeiling)
	{
		root->left = addNodeToTree(root->left, newNode);
		return root;
	}
    return root;
}

ActionNode* fetchNewList(Boss* boss, DecisionTreeNode* root)
{
      if(  root->healthFloor <= boss->health && boss->health <= root->healthCeiling)
      {
          return root->FirstAction;
      }
      else if( boss->health <= root->healthFloor)
      {
          return fetchNewList(boss, root->left);
      }
      else
      {
          return fetchNewList(boss, root->right);
      }
}

void freeBossTree(DecisionTreeNode* root)
{

}

void freeActionListInNode(ActionNode* head)
{
    
}
