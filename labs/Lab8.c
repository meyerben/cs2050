/*
Ben Meyer
bjmgy4
lab 8 
Section D
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct node_ {
	int data;
	struct node_* left;
	struct node_* right;
} Node;

Node* insert(Node* root, int data);
Node* buildTree(char* filename);
int min(Node* root);
Node* delete(Node* root, int data);
void freeTree(Node* root);
void printTree(Node* root, int depth);

int main(int argc, char* argv[])
{
    Node* root = buildTree(argv[1]);
    
    
    printf("The initial tree\n");
    printTree(root, 0);
    
    int data;
    printf("Enter a number to delete:");
    scanf("%d", &data);
    delete(root,data);
    printTree(root,0);
    freeTree(root);
    return 0;
}


Node* insert(Node* root, int data) {
	//create new node and return
	if(root == NULL)
	{
	    //allocate space for the new node
		Node* newNode = malloc(sizeof(Node));
		//give it a value
		newNode->data = data;
		//give it a left and right leaf (null)
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode; 
	}
	//insert to the right
	if(data > root->data)
	{
	    //recursion till base case
		root->right = insert(root->right, data);
		return root;
	}
	if(data < root->data)
	{
		root->left = insert(root->left, data);
		return root;
	}
    return root;
}

Node* buildTree(char* filename)
{
    
    //open the file
    FILE* fptr = fopen(filename, "r");
    //check to make sure it opened correctly
    if(fptr == NULL) printf("boink");
    
    //initialize the first node
    Node* root = NULL;
    int tmpval;
    //traverse the file
    while(1)
    {
        if(feof(fptr)) break; //check for end of file
        fscanf(fptr,"%d", &tmpval);//scan the value
        root = insert(root, tmpval); //insert that value into your new tree
    }
    fclose(fptr);
    return root;
}



int min(Node* root)
{
    //create a pointer
    Node* nextPtr = root;
    //traverse the tree's left side
    while(nextPtr->left != NULL)
    {
        //move nextPtr
        nextPtr = nextPtr->left;
    }
    return nextPtr->data;
}

Node* delete(Node* root, int data)
{
    // The root is null
    if (root == NULL) return root;
 
    //searches the left side of the tree for the data
    if (data < root->data)
        root->left = delete(root->left, data);
 
    //searches the right side of the tree
    else if (data > root->data)
        root->right = delete(root->right, data);
 
    //node has been found
    else
    {
        // the root has only a right subtree
        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        //the root has only a left subtree
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }
 
        // node with right and left subtree
        Node* temp = (Node*)malloc(sizeof(Node));
        temp->data = min(root->right);
 
        // Copy the content to this node
        root->data = temp->data;
 
        // Delete the node
        root->right = delete(root->right, temp->data);
        free(temp);
    }
    return root;
}

void freeTree(Node* root) {
	//free each node in the tree
	if(root == NULL)
		return;
	//traverse right tree
	freeTree(root->right);
	free(root);

	//traverse left tree
	freeTree(root->left);
}

void padding(int depth) {
	int i;
	for (i = 0; i < depth; i++) {
		putchar('\t');
	}
}

void printTree(Node* root, int depth) {
	if (root == NULL) {
		padding(depth);
		printf("~\n");
	} else {
		printTree(root->right, depth + 1);
		padding(depth);
		printf("%d\n", root->data);
		printTree(root->left, depth + 1);
	}
}