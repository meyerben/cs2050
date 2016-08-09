#include <stdlib.h>
#include <stdio.h>

typedef struct node_ {
	int data;
	struct node_* left;
	struct node_* right;
} Node;

Node* buildBalancedTree(int array[], int low, int high);


void printTree(Node* root, int depth);
void padding(int depth);

int main(int argc, char* argv[]) {
	int array[] = {1, 2, 3, 4, 5, 6, 7};
	Node* root = buildBalancedTree(array, 0, 6);
	printTree(root, 0);
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

void padding(int depth) {
	int i;
	for (i = 0; i < depth; i++) {
		putchar('\t');
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