/*
Ben Meyer
bjmgy4
lab 1 
Section D
*/

#include <stdlib.h>
#include <stdio.h>


//Function prototypes
double *read_file(char* filename, int length);

double find_min(double* array, int length);

double find_max(double* array, int length);

double find_avg(double* array, int length);

void write_to_file(char* filename, double* array, int length);


//Start of main
int main(int argc, char* argv[])
{
    if (argc != 4) {
        printf("Wrong number of arguments");
        return 0;
    }
    
    int n = atoi(argv[1]); //sets variable n to first argument as an int
    
    double* arr = read_file(argv[2], n); //calls read_file and sets it's value to arr
    
    write_to_file(argv[3], arr, n); //calls function write_to_file
    
    free(arr); //free memory used by arr

    return 0;
}


//Function Definitions
double* read_file(char* filename, int length)
{
   //Opens and and reads input1.txt
	FILE* file=fopen(filename,"r");
	//If the file doesn't open (nothing is found in it)
	if(file==NULL)
	{
		return 0;
	} 
	
	double* array = malloc(sizeof(double) * length); //free memory for array
	
	int i;
	for(i=0;i<length;i++) //iterates through the file and scans to an array
	{
	    fscanf(file, "%lf" , &array[i]); //scans as a double
	}
	
	return array; //read_file needs a double* returned
	
	fclose(file); //close file
	
}

double find_min(double* array, int length)
{
    int i = 0;
    double min = array[i];
    for(i=0;i<length;i++)
    {
        if (array[i] < min)
        min = array[i];
    }
    return min;
}

double find_max(double* array, int length)
{
    int i = 0;
    double max= array[i];
    for(i=0;i<length;i++)
    {
        if (array[i] > max)
        max = array[i];
    }
    return max;
}

double find_avg(double* array, int length)
{
   int i;
   double sum;
   for(i=0;i<length;i++) //iterates through the array and adds to the lump sum of everything in input file
   {
       sum += array[i];
   }
   
   return sum/length; //divides the sum by the amount to find average
}

void write_to_file(char* filename, double* array, int length)
{
    printf("min: %lf\n",find_min(array, length)); //prints min to command line
    printf("max: %lf\n",find_max(array, length)); //prints max to command line
    printf("avg: %lf\n",find_avg(array, length)); //prints avg to command line
    
    //Opens and and writes to ouput1.txt
	FILE* file=fopen(filename,"w");
	//If the file doesn't exist
	if(file==NULL)
	{
		printf("whoops");
	}
	
	int i;
	for(i=length-1; i!=-1; i--) //iterates through the array backwards
	{
	    fprintf(file, "%.3lf \n",array[i]); //prints the array to the txt file
	}
    fclose(file); //close file
}
