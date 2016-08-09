/*
Ben Meyer
bjmgy4
lab 3 
Section D
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct student {
    int id;
    char name[20];
    float gpa;
} Student;
 //prototypes
Student findStudent(FILE* fp, int studentId);
Student* getClass(const char* classFile, const char* studentFile, int len);
void bubbleSort(Student* students, int len);
void storeClass(const char* filename, Student* students, int len);
void printClass(Student* students, int len);
int numStudentsInbinaryFile(const char* filename);

int main(int argc, char* argv[])
{
    //define all of comand line arguments
    const char* classf = (argv[1]);
    const char* studentsf = (argv[2]);
    //const char* outf = (argv[3]); 
    
    FILE* file = fopen(classf, "r"); //open and read class.txt to get class size
    if (file == NULL)
    {
        printf("something went wrong");
    }
    int classSize;
    fscanf(file, "%d", &classSize); //scan first line to class size
    fclose(file); //close file
    
    Student* class1 = getClass(classf,studentsf, classSize); //get a whole mess of students as an array of students
    
    bubbleSort(class1,classSize); //rank the students based on how smart they are
    //storeClass(outf,class1,classSize); //store the class into a binary file
    //printf("%d", numStudentsInbinaryFile(studentsf));
    printClass(class1,classSize); //print the class in the command line
    
    return 0;
}

Student findStudent(FILE* fp, int studentId)
{
    Student Stud1;
    fseek(fp, (studentId - 1)* sizeof(Student), SEEK_SET); //find a student by it's number
    fread(&Stud1, sizeof(Student),1, fp); //reads in that student and stores it as a Student struct
    return Stud1;
}

Student* getClass(const char* classfile, const char* studentFile, int len)
{
    FILE* file = fopen(classfile, "r"); //open up the class.txt
    if (file == NULL)
    {
        printf("something went wrong");
    }
    int nothing;
    fscanf(file,"%d", &nothing); //move past first line of the file
    nothing = len;
    FILE* sfile = fopen(studentFile,"rb"); //open student.dat file
    if (sfile == NULL)
    {
        printf("boink");
    }
    
    Student* class = malloc(sizeof(Student)); //free space for an array of students
    
    int i;
    int id;
    for(i=0;i<len;i++)//iterate through the freed array
    {
        fscanf(file, "%d", &id); //scan the file for the student id
        class[i] = findStudent(sfile, id); //use that id to find out about the student and store it into the class
    }
    return class;
    fclose(file);
    fclose(sfile);
}

void bubbleSort(Student* students, int len)
{
    int i;
    int temp;
    for(i=0;i<len;i++) //iterates through the array of students
    {
        if(students[i].gpa<students[i+1].gpa) //moves the student up in the array if they do good
        {
            temp = students[i].gpa;
            students[i].gpa = students[i+1].gpa;
            students[i+1].gpa = temp;
        }
    }
}


void storeClass(const char* filename, Student* students, int len)
{
    FILE* file = fopen(filename, "wb"); //open output.dat
    if(file == NULL) printf("boink"); //check if it works
    fwrite(students,sizeof(Student),len,file); //write students to file
    fclose(file); //close the file
}

void printClass(Student* students, int len)
{
    int i;
    for(i=0;i<len;i++) //iterates through the student array and prints em out
    {
        printf("%d ",students[i].id);
        printf("%s ",students[i].name);
        printf("%.2f\n",students[i].gpa);
    }
}


int numStudentsInbinaryFile(const char* filename)
{
    //the idea here was that the fseek would return the value of the size of the file
    FILE* file = fopen(filename, "rb");
    int size;
    size = fseek(file, sizeof(Student), SEEK_END );
    return size;
    fclose(file);
}