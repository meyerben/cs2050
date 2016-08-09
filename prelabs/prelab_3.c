#include <stdio.h>
#include <stdlib.h>

typedef struct student {
    int id;
    char name[20];
    float gpa;
} Student;

Student findStudent(const char* filename, int studentId);

int main(int argc, char* argv[])
{
    Student studer = findStudent(argv[1],3);
    printf("%.20f\n",studer.gpa);
    return 0;
}

Student findStudent(const char* filename, int studentId)
{
    FILE* file = fopen(filename,"rb");
    Student stud = {0,"dog",3.0};
    fseek(file, sizeof(Student)*(studentId-1), SEEK_SET);
    fread(&stud, sizeof(Student),1,file);
    return stud;
    fclose(file);
}