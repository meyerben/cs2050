#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

/*
 * Parameters:
 * token - A string
 *
 * Return:
 * 1 if the string is a valid phone number,
 * 0 otherwise
 *
 * A valid phone number takes the form
 * (XXX)XXX-XXXX where X is a digit 0-9. 
 */
int isPhoneNumber(char* token);
int isDate(char* token);
int isEmail(char* token);

int main(void) {
	//This is a valid phone number
	assert(isPhoneNumber("(123)456-7890") == 1);
	assert(isEmail("ben@gmail.com")    ==    1);
    assert(isDate("03/31/2005")           == 1);
	
	//These are not valid phone numbers
	assert(isPhoneNumber("123-456-7890")    == 0);
	assert(isPhoneNumber("1234567890")      == 0);
	assert(isPhoneNumber("(123) 456-7890") == 0);
	assert(isPhoneNumber("Hello World")     == 0);
	assert(isPhoneNumber("")				== 0);
	

	printf("Congratulations! You finsihed the prelab!");
	return 0;
}

int isPhoneNumber(char *token) {
	if(*token == '(' && *(token+4) == ')')
	{
		if( *(token+8) == '-')
		{
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
			for(i=9; i<13; i++)
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
    int validDays[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    char c,k;
    c = *(token+2);
    k = *(token+5);
    if(c== '/' && k == '/')
    {
		//turn dashes to null terminators
		*(token+2) = '\0';
		*(token+5) = '\0';
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
	int len = strlen(token);
	int atpos = 0;
	int dotpos = 0;
	int i;
	for(i=0; i<len; i++)
	{
		if(*(token+i) == '@')
		{
			atpos = i;
		}
		if(*(token+i) == '.')
		{
			dotpos = i;
		}
	}
	if(atpos && dotpos)
	{
		for(i=0; i<atpos; i++)
		{
			if(!isalnum(*(token+i)))
			{
				return 0;
			}
		}
		for(i=(atpos+1); i<dotpos; i++)
		{
			if(!isalnum(*(token+i)))
			{
				return 0;
			}
		}
		char *postfix = (token+(dotpos+1));
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