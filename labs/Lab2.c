/*
Ben Meyer
bjmgy4
lab 2 
Section D
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct song{
    char* name;
    int rating;
    int numTimesPlayed;
} Song;

//The largest valid size of a song name
#define MAXNAMESIZE 20

Song* readAlbum(const char* filename, int* lenPtr);
void printAlbum(Song* album, int len);
int changeRating(char* title, int rating, Song* album, int len);
int listenToSong(char* title, Song* album, int len);
void bubble_sort(Song* album, int len);

int main(int argc, char*argv[]){
    int length;
    Song* album = readAlbum(argv[1], &length);
    
    int on = 1;
    while(on==1)
    {
        printAlbum(album, length);
        int sel;
        printf("\nEnter 1 to listen to a song\nEnter 2 to change a rating\nEnter 0 to quit\n");
        scanf("%d", &sel);
        char* song = malloc(sizeof(char) * MAXNAMESIZE);
        switch(sel)
        {   
            case 1: // If the user enters 1 to listen to a song
            printf("\nEnter a title:");
            scanf("%s", song);
            if(listenToSong(song, album, length) == -1) printf("unable to find %s\n\n", song);
            else listenToSong(song, album, length);
            break;
            
            case 2: //if the user enters 2 to rate a song
            printf("\nEnter a title:");
            scanf("%s", song);
            int rating;
            printf("Enter a new rating:\n");
            scanf("%d", &rating);
            if(changeRating(song,rating, album, length) == -1) printf("unable to find %s\n\n", song);
            else changeRating(song,rating, album, length);
            break;
            
            case 0: //if the user chooses to exit the program
            on = 0;
            break;
            
            
        }
            
    
    }
    free(album);
    return 0;
}

Song* readAlbum(const char* filename, int* lenPtr)
{
    //Opens and and reads input1.txt
	FILE* file=fopen(filename,"r");
	//If the file doesn't open (nothing is found in it)
	if(file==NULL)
	{
		return 0;
	}
	
	fscanf(file, "%d", lenPtr); //find length of file from first line of file
	
	Song* album = malloc(sizeof(Song) * *lenPtr); //free memory for array struct
	
	int j;
	for(j=0;j<*lenPtr;j++) //for each index in struct array
	{
	    album[j].name = malloc(sizeof(char) * MAXNAMESIZE);    //free memory for the album name                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
	}
	
	int i;
	for(i=0;i< *lenPtr;i++) //iterates through the file and scans to the struct
	{
	    fscanf(file, "%s" , album[i].name);
	    fscanf(file, "%d" , &album[i].rating);
	    fscanf(file, "%d" , &album[i].numTimesPlayed);
	}
	
	return album;
	
	fclose(file);
}


void printAlbum(Song* album, int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        printf("%s %d %d\n", album[i].name, album[i].rating, album[i].numTimesPlayed);
    }
}


int changeRating(char* title, int rating, Song* album, int len)
{
  int i;
  for(i=0;i<len;i++)
  {
      if (strcmp(title, album[i].name)== 0)
      album[i].rating = rating;
  }
  if (i>len) i=-1;
  return i;
  
}

int listenToSong(char* title, Song* album, int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        if (strcmp(title, album[i].name)== 0)
        album[i].numTimesPlayed++;
    }
    if (i>len) i=-1;
    return i;
}
