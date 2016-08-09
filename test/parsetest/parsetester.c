#include "game.h"

int main(void)
{
    
    FILE* fp = fopen("Items.txt","r");
		
		//If the file is NULL, give an error message and quit.
		if(fp == NULL)
		{
			printf("\nError, could not open item file.");
		}
	
    Shield* s 		 = NULL;
    s = (Shield*)malloc(sizeof(Shield));
    
    int i;
    char buffer[100];
    fgets(buffer, 100, fp);
    char* token = strtok(buffer, "|");
    for(i=0; token!=NULL;i++,token = strtok(NULL, "|\n"))
    {
        if(i==0)
        {
            strcat(s->name, token);
        }
        else if(i==1)
        {
            s->cost = atoi(token);
        }
        else if(i==2)
        {
            s->defense = atoi(token);
        }
        else
        {
            strcat(s->description,token);
        }
    }
    
    printf("%s\n\t Cost: %d\n\t Defense: %d\n",s->name, s->cost, s->defense);
	printf("%s\n\n", s->description);
    return 0;
}

