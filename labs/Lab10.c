/*
Ben Meyer
bjmgy4
lab 8 
Section D
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isDate(char* token);
int isPhoneNumber(char* token);
int isEmail(char* token);
int isName(char* token);

int main(int argc, char*argv[])
{
    //open the file
    FILE* fp = fopen(argv[1], "r");
    //check file
    if(fp == NULL) 
        {
            printf("your file sucks"); 
            return 0;
        }
    //create a buffer
    char buffer[500];
    //create space for a name
    char* name = malloc(sizeof(char) *20);
    //get through the file
    while (fgets(buffer,500,fp) != NULL)
    {
        //set the token to each word
        char* token = strtok(buffer, " \r\n\t");
        //create a test to see if the last token was a name
        int wasname = 0;
        while (token != NULL)
        {
            //function calls
            if(isPhoneNumber(token) == 1)
            {
                printf("Phone Number: %s\n", token);
            }
            
            else if (isDate(token) == 1)
            {
                printf("Date: %s\n", token);
            }
            else if (isEmail(token) ==1 )
            {
                printf("Email: %s\n", token);
            }
            //if it looks like a name
            else if (isName(token) ==1)
            {
                //if the last word was a name
                if(wasname == 1)
                {
                    printf("BONUS: Full Name: %s %s\n",name, token);
                }
                //if the last word wasn't a name
                else
                {
                    //save the last word
                    wasname = 1;
                    strcpy(name, token);
                }
            }
            //it's not a name
            else
            {
                wasname =0;
            }
            token = strtok(NULL, " \r\n\t");
            
        }
    }
    free(name);
    fclose(fp);
    return 0;
}

int isPhoneNumber(char *token) {
    //check for parentheses
	if(*token == '(' && *(token+4) == ')')
	{
	    //check for the dash
		if( *(token+8) == '-')
		{
		    //check that everything is a digit
			int i;
			for(i=1; i<4; i++)
			{
				if(!isdigit(*(token+i)))
				{
					return 0;
				}
			}
			for(i=5; i<8; i++)
			{
				if(!isdigit(*(token+i)))
				{
					return 0;
				}
			}
			for(i=9; i<=12; i++)
			{
				if(!isdigit(*(token+i)))
				{
					return 0;
				}
			}
			return 1;
		}
		return 0;
	}
	else
	{
		return 0;
	}
}

int isDate(char* token)
{
    //array of valid days
    int validDays[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    char c,k;
    c = *(token+2);
    k = *(token+5);
    if(c== '/' && k == '/')
    {
		//turn dashes to null terminators
		*(token+2) = '\0';
		*(token+5) = '\0';
		//gets rid of period
		*(token+10) = '\0';
		//get month,day,year in terms of ints
		int month, day;
		month = atoi(token);
		day = atoi(token+3);
		//check valid month
		if(month < 1 || month > 12)
		{
			return 0;
		}
		//check valid day
		if(day < 1 || day > validDays[month-1])
		{
			return 0;
		}
		//fix the null terminators
		*(token+2) = '/';
		*(token+5) = '/';
		return 1;
	}
	else
	{
		//no dashes
		return 0;
	}
}

int isEmail(char *token) {
    //get the length
	int len = strlen(token);
	int atpos = 0;
	int dotpos = 0;
	int i;
	for(i=0; i<len; i++)
	{
	    //find the @ sign
		if(*(token+i) == '@')
		{
			atpos = i;
		}
		//find the .
		if(*(token+i) == '.')
		{
			dotpos = i;
		}
	}
	//if the positions are not 0
	if(atpos && dotpos)
	{
		for(i=0; i<atpos; i++)
		{
		    //check to see if it's a number or letter
			if(!isalnum(*(token+i)))
			{
				return 0;
			}
		}
		//check to see if everything after @ is a number or letter
		for(i=(atpos+1); i<dotpos; i++)
		{
			if(!isalnum(*(token+i)))
			{
				return 0;
			}
		}
		
		//create a new string to compare stuff
		char *postfix = (token+(dotpos+1));
		//makes sure that it's com edu or gov
		if(!strcmp(postfix, "com") || !strcmp(postfix, "edu") || !strcmp(postfix, "gov"))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int isName(char* token)
{
    //starts with an uppercase letter followed by a lowercase letter
    if(isupper(token[0]) && islower(token[1]))
    return 1;
    else return 0;
}