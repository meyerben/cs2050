#include <stdio.h>
#include <stdlib.h>

int* read_file(char* filename, int len);
void print_array(int* array, int len);

int *read_file(char* fname, int len)
{
    //Opens and and reads input.txt
	FILE* file=fopen(fname,"r");
	//If the file doesn't open (nothing is found in it)
	if(file==NULL)
	{
		return 0;
	}
	
	int *content = malloc(sizeof(int)*len);
	
	int i;
	str temp;
	int fart;
	for(i=0;i<len;i++)
	{
		fscanf(file, "%c", &temp);
		fart = atoi(temp);
		//content[i] = fart;
	}
	fclose(file);
	return content;
	    
}

void print_array(int* array, int len)
{
   int i;
   for(i=0;i<len;i++)
   {
   	printf("%d", array[i]);
   }
}

int main(int argc, char** argv)
{
    
    //Check to see if ./a.out 5 input.txt are entered
	if(argc!=3)
	{
		printf("\n Insufficient arguments \n ");
		return 0;
	}
	
	int n = atoi(argv[1]);
	
	int *nums = read_file(argv[2], n);
	
	print_array(nums,n);
   return 0; 
}