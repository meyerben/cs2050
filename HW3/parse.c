#include "game.h"

//If you haven't knocked yourself out in boss.c, do it here.
//Otherwise, knock yourself out again. 

void ParseShieldInfo(Shield* s, FILE* fp)
{
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
}

void ParseSwordInfo(Sword* s, FILE* fp)
{
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
            s->attack = atoi(token);
        }
        else
        {
            strcat(s->description,token);
        }
    }
}
