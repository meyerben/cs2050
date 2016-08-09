/*
Ben Meyer
bjmgy4
lab 8 
Section D
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAXARRAYLENGTH 10

typedef struct node_ {
	int data;
	struct node_* left;
	struct node_* right;
} Node;

void quicksort(int array[],int low,int high);
void preorder(Node* root);
void inorder(Node* root);
void postorder(Node* root);
void freeTree(Node* root);
int height(Node* root);
int search(int array[], int val);
Node* buildBalancedTree(int array[],int low, int high);
void printEveryPath(Node* root, int* path, int depth);



int main(void)
{
    //generate seed
    srand(time(NULL));
    //initialize variables
    int i;
    int temp;
    int arr[MAXARRAYLENGTH] = {};
    //create array of length 10
    for(i=0;i<MAXARRAYLENGTH;i++)
    {
        //generate number between 0-99;
       temp = rand()%100;
       //calls function and negates 1 iteration
       if( search(arr,temp)==1) i--;
       //assign value
       else arr[i] = temp;
    }
    //call quicksort function
    quicksort( arr, 0, 9);
    printf("Sorted array: ");
    //iterate through the array
    for(i=0;i<MAXARRAYLENGTH;i++)
    {
        //print the value
        printf("%d  ", arr[i]);
    }
    //initialize BST
    Node* tree = buildBalancedTree(arr,0,9);
    
    printf("\n\n");
    //call functions and print out arrays
    printf("Your height is: %d\n\n", height(tree));
    printf("Your preorder list is: "); preorder(tree); printf("\n");
    printf("Your inorder list is: "); inorder(tree); printf("\n");
    printf("Your postorder list is: "); postorder(tree); printf("\n");
    
    printf("\nBONUS\n");
    int* path = malloc(sizeof(int)*5);
    printEveryPath(tree, path, 0);
    freeTree(tree);
    free(path);
    return 0;
}

int search(int array[],int val)
{
    int i;
    //iterate through array
    for(i=0;i<MAXARRAYLENGTH;i++)
    {
        //if it's already in the array
        if(array[i] == val) return 1; //already in array
    }
    return 0;
}

void quicksort(int array[],int low,int high)
{
    //intialize variables
    int swap,j,temp,i;
        //move i and j
        if(low<high){
            swap=low;
            i=low;
            j=high;
        
        while(i<j){
            while(array[i]<=array[swap] && i<high) i++;
            while(array[j]>array[swap]) j--;
            if(i<j){
                temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
        }

        temp=array[swap];
        array[swap]=array[j];
        array[j]=temp;
        quicksort(array,low,j-1);
        quicksort(array,j+1,high);

    }
}


Node* buildBalancedTree(int array[],int low, int high)
{
    while(low > high) return NULL;
	//get middle element and make it the root of the tree
	int midpoint = (low + high)/2;
	Node *Root = malloc(sizeof(Node));
	Root->data = array[midpoint];
	//construct left tree recurisvely
	Root->left = buildBalancedTree(array, low, midpoint-1);
	//construct right tree recursively
	Root->right = buildBalancedTree(array, midpoint+1, high);
	return Root;
}

int height(Node* root)
{
    //base case
    if (root == NULL)
    {
        return 0;
    }

    //recursion
    int left = height(root->left);
    int right = height(root->right);
    
    if(left > right)
    {
        return left+1;
    }
    else
    {
        return right+1;
    }
}

void preorder(Node* root)
{
    if(root)
    {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}
void inorder(Node* root)
{
    if(root)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
void postorder(Node* root)
{
    if(root)
    {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void freeTree(Node* root) 
{
	//free each node in the tree
	if(root == NULL)
		return;
	//traverse right tree
	freeTree(root->right);
	free(root);

	//traverse left tree
	freeTree(root->left);
}



void printEveryPath(Node* root, int* path, int depth)
{
    //base case
    if (root==NULL) 
    return;
 
    // append this node to the path array
    path[depth] = root->data;
    depth++;
 
    // print it out
    if (root->left==NULL && root->right==NULL) 
    {
        int i;
        for (i=0; i<depth; i++) 
        {
            printf("%d ", *(path +i));
        }
        printf("\n");
        }
    else
    {
        // otherwise try both directions
        printEveryPath(root->left, path, depth);
        printEveryPath(root->right, path, depth);
    }
}