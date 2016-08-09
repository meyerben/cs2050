//don't add to this list. You won't need anything else.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//for expandable use.
#define NUMHEROES 6
#define NUMCHOSENHEROES 3
#define MAXNUMSAVEFILES 5
#define MAXPLAYERNAME 20

//for locating the save file
typedef enum f_
{
	EXIST,
	DOESNOTEXIST
} FileFinder;

//MVP OF THE HOMEWORK
//Mostly self-expalanatory pieces. 
typedef struct hero_
{
	char name[40];
	int health;
	int baseDefense;
	int baseAttack;
	int baseSpeed;
} Hero;

//Not used in this HW, just defined to prep for later HWs
typedef struct boss_
{
	char name[40];
	int health;
	int maxHealth;
	int baseDefense;
	int baseAttack;
	int baseSpeed;
} Boss;


//THAT'S A LOT OF FUNCTIONS. GET EXCITED.
void deleteFile(int choice, char* filename);
void saveFileData(int choice, char* filename, Hero* heroes, char* playerName, int progress);
char* getPlayerName();
Hero* loadSavedData(char* filename);
Hero* loadInitialData();
Hero* pickHeroes(Hero* heroes);
void sortHeroes(Hero* heroes);
void printHeroes(Hero* heroes, int numHeroes);
//The following ones are all done for you. Just call them as instructed. 
FileFinder findSaveFile();
void loadSavedGameHandler();
void DeleteSavedGameHandler();
void loadGameStateData(char*** names, int** states, int* fileCount);
char* choiceToFile(int num);
void freeMemory(char** names, int* states);
void startNewGame();
void playGame(Hero* heroes, char* playerName, Boss* boss, int progress, int choice);
int chooseSaveFile();

int main(void)
{
	//initialize some variables
	FileFinder gate; 
	int option;
	int flag = 0;
	//find out if gate exists
	gate = findSaveFile();
	
	printf("Welcome to the Gauntlet!\n");
	printf("Select your option.\n");
	if(gate == EXIST) //If it exists, there will be plenty of options for the user in the main menu
	{
		
		printf("1: start a new game\n2: start a saved game\n3: delete a saved file\n4: quit\n");
		scanf("%d", &option);
		
		while(option<1 || option >4) //error check
		{
			printf("invalid choice, please input a valid option");
			scanf("%d", &option);
		}
	}
	else //If no save files exist, they only have the option to escape
	{
	printf("1: start a new game\n2: quit\n");
	scanf("%d", &option);
	
	while(option<1 || option >2) //error check
		{
			printf("invalid choice, please input a valid option");
			scanf("%d", &option);
		}
		if (option == 2) option=4; //This is so that we only need one switch statement. to quit is option 4 even when displayed and accepts 2 when there is no save file.
	}
	
	switch(option) {  //pretty simple, just call old functions to keep this switch statement short
		case(1): //Start a new game
		startNewGame();
		flag++;
		break;
		
		case(2): //Start a saved game
		loadSavedGameHandler();
		break;
		
		case(3): //delete a saved file;
		DeleteSavedGameHandler();
		break;
		
		case(4):
		flag += 1;
		break;
		
		default:
		printf("boink"); //something went wrong
		
	}
	
	return 0;
}

void deleteFile(int choice, char* filename)
{
	
	int ret = remove(filename); //deletes the filenum.txt file

   if(ret == 0) //error checking
   {
      printf("File deleted successfully");
   }
   else 
   {
      printf("Error: unable to delete the file");
   }
   //if the file doesn't delete, it doesn't create any known bugs, it takes up more disk space
   
	//******These animals will come in handy for my strange way of moving the file pointer.******
	char* dog = malloc(sizeof(char)*MAXPLAYERNAME);
	int cat;
	
	FILE* fp = fopen("gamestate.txt", "r+"); //gamestate.txt is hardcoded in there, but this will never change.
	if(fp== NULL) printf("boink");
	
	//scan first line and decrement it by one. then replace it with the new value
	//bonus: this also moves the file pointer
	int numFiles;
	fscanf(fp, "%d", &numFiles);
	numFiles--;
	rewind(fp);
	fprintf(fp, "%d", numFiles);
	
	int i;
	for(i=0;i<choice-1;i++)
	{
		fscanf(fp, "%s | %d", dog, &cat); // this is to let me move the file pointer using dogs and cats as placeholders
	}
	fprintf(fp, "\n%s | %d", "000", 0); //print the default
	fprintf(fp,"%s", " "); //this is to help gamestate.txt look neat (I think it still works with bad spacing, but it's ugly af)
	free(dog); //save the dogs
	fclose(fp);
	//******no animals were hurt in the making of this function******
}

void saveFileData(int choice, char* filename, Hero* heroes, char* playerName, int progress)
{
	int i;
	
	//more dogs and cats
	char* dog = malloc(sizeof(char)*MAXPLAYERNAME);
	int cat;
	
	//open up gamestate and filenum.txt
	FILE* fp = fopen("gamestate.txt", "r+");
	if(fp == NULL) printf("boink");
	FILE* Fptr = fopen(choiceToFile(choice-1), "w+");
	
	heroes = malloc(sizeof(Hero)*NUMCHOSENHEROES);
	switch(progress){
		case(1): //If progress is equal to 1 (they chose their name)
		
		fscanf(fp, "%d", &i); //moves ptr past number of save files
		i++;
		rewind(fp);
		fprintf(fp, "%d\n",i);
		
		for(i=0;i<choice-1;i++)
		{
			fscanf(fp, "%s | %d", dog, &cat); // this is to let me move the file pointer using dogs and cats as placeholders
		}
		fprintf(fp, "\n%s | %d", playerName, progress);
		fprintf(fp,"%s", " ");
		
		for(i=0;i<NUMCHOSENHEROES;i++)
		{
			fprintf(Fptr, "%s | %d | %d | %d | %d\n", heroes[i].name, heroes[i].health, heroes[i].baseDefense, heroes[i].baseAttack, heroes[i].baseSpeed);
		} //This is to create the file and write the hero data to it, but it hasn't been going so hot.
		
		break;
		
		
		fscanf(fp, "%d", &i); //move pointer past first line
		for(i=0;i<choice-1;i++)
		{
			fscanf(fp, "%s | %d", dog, &cat); // this is to let me move the file pointer using dogs and cats as placeholders
		}
		fprintf(fp, "\n%s | %d", playerName, progress);
		fprintf(fp,"%s", " ");
		case(2):

		fscanf(fp, "%d", &i); //move pointer past first line
		for(i=0;i<choice-1;i++)
		{
			fscanf(fp, "%s | %d", dog, &cat); // this is to let me move the file pointer using dogs and cats as placeholders
		}
		fprintf(fp, "%s | %d", playerName, progress);
		fprintf(fp,"%s", " ");
		
		for(i=0;i<NUMCHOSENHEROES;i++)
		{
			fprintf(Fptr, "%s | %d | %d | %d | %d\n", heroes[i].name, heroes[i].health, heroes[i].baseDefense, heroes[i].baseAttack, heroes[i].baseSpeed);
		}
		break;
		
	}	
}

char* getPlayerName()
{
	
	//all pretty self explanatory 
	char* name = malloc(sizeof(char) * MAXPLAYERNAME);
	printf("Please input your name: \n");
	scanf("%s", name);
	printf("Hello %s, Welcome to the gauntlet.\n", name);
	return(name);
	free(name);
}

Hero* loadSavedData(char* filename)
{
	//malloc some space for heroes
	Hero* heroes = malloc(sizeof(Hero)*NUMHEROES);
	//open file for reading
	FILE* fp = fopen(filename, "r");
	if (fp == NULL) printf("boink"); //error check
	
	int i;
	for(i=0;i<NUMCHOSENHEROES;i++)
	{
	fscanf(fp, "%s | %d | %d | %d | %d", heroes[i].name , &heroes[i].health, &heroes[i].baseDefense, &heroes[i].baseAttack, &heroes[i].baseSpeed);
	}
	//tbh i have no real way to check if this works, because I can't seem to pass any values to filenum.txt
	return heroes;
	free(heroes);
	
}

Hero* loadInitialData()
{
	//make some room
	Hero* heroes = malloc(sizeof(Hero)*NUMHEROES);
	//open some files
	FILE* fp = fopen("Heroes.txt", "r");
	if(fp == NULL) printf("boink");
	
	int i;
	for(i=0;i<NUMHEROES;i++)
	{
		fscanf(fp, "%s | %d | %d | %d | %d", heroes[i].name , &heroes[i].health, &heroes[i].baseDefense, &heroes[i].baseAttack, &heroes[i].baseSpeed);
	}
	sortHeroes(heroes);
	return(heroes);
	free(heroes);
}

Hero* pickHeroes(Hero* heroes)
{
	int choice;
	//int i;
	int selections[3]; //an array to make sure no one picks the same hero twice
	
	//Free up space for the new Hero array
	Hero* chosenHeroes = malloc(sizeof(Hero)*NUMCHOSENHEROES);
	
	//print out all 6 heroes
	printHeroes(heroes,NUMHEROES);
	printf("Please pick your first hero: \n");
	scanf("%d",&choice);

	while(choice<1 || choice> NUMHEROES)
	{ printf("Invalid choice, please pick a valid hero number. \n");
		scanf("%d", &choice);
	}
	
	chosenHeroes[0] = heroes[choice];
	selections[0] = choice;
	
	printf("Please pick your second hero: \n");
	scanf("%d", &choice);
	
	while(choice<1 || choice> NUMHEROES || choice == selections[0])
	{printf("Invalid choice, please pick a valid hero number. \n");
		scanf("%d", &choice);
	}
	
	chosenHeroes[1] = heroes[choice];
	selections[1] = choice;
	
	printf("Please pick your third hero: \n");
	scanf("%d", &choice);
	
	while(choice<1 || choice> NUMHEROES || choice == selections[0] || choice == selections[1])
	{printf("Invalid choice, please pick a valid hero number. \n"); 
		scanf("%d", &choice);
	}
	
	chosenHeroes[2] = heroes[choice];
	
	return chosenHeroes;
	
}

void sortHeroes(Hero* heroes)
{
	//hey it works
	
	int i,j;
	char temp[40];

	for(i=0;i<NUMHEROES;i++) //iterates through the array
	{
      for(j=i+1;j<NUMHEROES;j++) //iterates ahead of i 
      {
           if(strcmp(heroes[i].name, heroes[j].name) > 0) //if one string is alphabetically before the other
           {
              strcpy(temp, heroes[i].name); //copy the first string into temp
              strcpy(heroes[i].name , heroes[j].name); //copy the second string into the first
              strcpy(heroes[j].name , temp); // copy temp(the first string) into the second
           }
      }
  }
}

void printHeroes(Hero* heroes, int numHeroes)
{
	int i;
	for(i=0;i<numHeroes;i++)
	{
		printf("%d: %s\n", i+1, heroes[i].name);
		printf("     Health: %d\n",heroes[i].health);
		printf("     Defense: %d\n",heroes[i].baseDefense);//Health, Defense, Attack, Speed
		printf("     Attack: %d\n",heroes[i].baseAttack);
		printf("     Speed: %d\n\n",heroes[i].baseSpeed);
	}
	printf("\n");
}



/***************************************START OF FUNCTIONS GIVEN TO YOU*********************************************************************/

FileFinder findSaveFile()
{
	printf("Checking save file...\n\n");
	//This should exist. Make sure the file is with your HW. 
	FILE* fp = fopen("gamestate.txt", "r");
	if(!fp)
	{
		//You will have to debug this...it could be for a variety of reasons. 
		perror("gamestate.txt read error");
		exit(1);
	}

	int numFiles;

	//read the number of save file slots that are taken up, and 
	//interpret accordingly. 
	if(fscanf(fp, "%d", &numFiles) < 1)
	{
		printf("gamestate.txt: failed to read number of save files. Check input file.\n");
		exit(1);
	}

	FileFinder f;
	if (numFiles == 0) 
	{ 
		
		f = DOESNOTEXIST;
	}
	else 
	{ 
		f = EXIST; 
	}
	
	fclose(fp);
	
	printf("Check complete.\n\n");
	return f;
}

void loadSavedGameHandler()
{
	//initial load of all data that might be needed. 
	char** names;
	int* states;
	int numFiles;
	int choice;

	loadGameStateData(&names, &states, &numFiles);

	while(1)
	{
		printf("\nChoose a file you would like to load: \n");
		printf("(-1 to return to main menu)\n");
		printf(">");
		scanf("%d", &choice);
		while((choice < 1 || choice > MAXNUMSAVEFILES) && choice != -1)
		{
			printf("Invalid choice. Please choose a different option:\n ");
			printf(">");
			scanf("%d", &choice);
	
		}
	
		if(choice == -1)
		{
			freeMemory(names, states);
			return;
		}
	
		if(states[choice-1] == 0)
		{
			printf("There is no saved file present in this slot.\n");
		}
		else
		{
			//From here, a valid saved file has been selected, so we need to interpret where
			//the save file is in terms of game progression. This way we know what data to load

			//the state value will never be anything other than 0, 1, or 2. 
			if(states[choice-1] == 1)
			{
				//Heroes have not been selected yet.
				playGame(loadInitialData(), names[choice-1], NULL, states[choice-1], choice);
			}
			else
			{
				//Heroes have already been selected. 
				Hero* heroes = loadSavedData(choiceToFile(choice-1));
				if(!heroes)
				{
					printf("Failed to load heroes. Exiting...\n");
					freeMemory(names, states);
					exit(1);
				}
				playGame(heroes, names[choice-1], NULL, states[choice-1], choice);
			}
	
			freeMemory(names, states);
			return;
		}
	}
}

void DeleteSavedGameHandler()
{

	//Everything in this file is almost identical to the function above, just different ending actions.
	//Could move a lot of this to its own function, but eh
	char** names;
	int* states;
	int numFiles;
	int flag = 0;
	int choice = -1;

	while (1)
	{
		//Small optimization. If we didn't delete a file, we don't have to reload the data
		//since nothing changed. 
		if(flag == 0)
		{
			//to cover the first time the loop goes through.
			//Can't free if nothing's been loaded yet.
			if(choice != -1)
			{
				freeMemory(names, states);
			}
			loadGameStateData(&names, &states, &numFiles);
		}

		printf("\nChoose a file you would like to delete: \n");
		printf("(-1 to return to main menu)\n");
		printf(">");
		scanf("%d", &choice);
		while((choice < 1 || choice > MAXNUMSAVEFILES) && choice != -1)
		{
			printf("Invalid choice. Please choose a different option:\n ");
			printf(">");
			scanf("%d", &choice);
		}

		if(choice == -1)
		{
			//This is the only way to get out of this function. 
			freeMemory(names, states);
			return;
		}

		if(states[choice-1] == 0)
		{
			//shouldn't get here, but just in case. 
			//can't get here because the numFiles controls what's 
			//a valid value for chioce.
			printf("There is no saved file present in this slot.\n");
			flag = 1;
		}
		else
		{
			deleteFile(choice, choiceToFile(choice-1));
			flag = 0;
		}
	}
}

void loadGameStateData(char*** names, int** states, int* fileCount)
{
	printf("\n\n");
	//All memory is allocated here, and once the data is loaded 
	//The variables passed by reference into this function will be set up. 
	char** n = malloc(sizeof(char*)*MAXNUMSAVEFILES);
	int i;
	for(i = 0; i < MAXNUMSAVEFILES; i++)
	{
		n[i] = malloc(sizeof(char)*MAXPLAYERNAME);
	}

	int* s = malloc(sizeof(int)*MAXNUMSAVEFILES);

	//again, should not fail. 
	FILE* fp = fopen("gamestate.txt", "r");
	if(!fp)
	{
		perror("gamestate.txt");
		freeMemory(n, s);
		exit(1);
	}

	int numFiles;
	if(fscanf(fp, "%d", &numFiles) < 1)
	{
		printf("gamestate.txt: could not read the number of save files. Check input file.\n");
		freeMemory(n,s);
		exit(1);
	}
	//Load all the data, interpret the data, and print to the user what
	//was found in the list of save file slots. 
	for(i = 0; i < MAXNUMSAVEFILES; i++)
	{
		if(fscanf(fp, "%s | %d", n[i], &s[i]) < 2)
		{
			printf("gamestate.txt: could not read save file data #%d. Check input file.\n", i+1);
			freeMemory(n,s);
			exit(1);
		}
		//NOTE: everything shown to the user is for human readability. 
		//Stuff starts at 1, but internally stuff still starts at 0. 
		switch(s[i])
		{
			case 0: 
				printf("%d: [No File Present]\n", i+1);
				break;
			case 1: 
				printf("%d: %s - ", i+1, n[i]);
				printf("Heroes have not been selected.\n"); 
				break;
			case 2: 
				printf("%d: %s - ", i+1, n[i]);
				printf("Heroes have been selected.\n"); 
				break;
		}
	}
	
	fclose(fp);

	//complete the links after everything is loaded. 
	*names = n;
	*states = s;
	*fileCount = numFiles;
}

//helpful function to know what file we are loading from/saving to
char* choiceToFile(int num)
{
	switch(num)
	{
		case 0: return "file1.txt"; break;
		case 1: return "file2.txt"; break;
		case 2: return "file3.txt"; break;
		case 3: return "file4.txt"; break;
		case 4: return "file5.txt"; break;
		default: 
			printf("Something happened with the save file choice. See Daniel.\n"); 
			exit(1); break;
	}
}

void freeMemory(char** names, int* states)
{
	int i;
	//seg faults? Check input file/gdb. 
	for(i = 0; i < MAXNUMSAVEFILES; i++)
	{
		free(names[i]);
	}
	free(names);
	free(states);
}

void startNewGame()
{
	//I don't think anything else needs to be here?
	Hero* heroes = loadInitialData();
	//doesn't matter what the value of choice is, since progress = 0 means get a choice value first. 
	playGame(heroes, NULL, NULL, 0, -1);
}

void playGame(Hero* heroes, char* playerName, Boss* boss, int progress, int choice)
{

	//Added flavor 
	if(progress > 0)
	{
		printf("\nWelcome back %s.\n\n", playerName);
	}

	//holds what the last thing done was.
	int initialprogress = progress;

	Hero* chosenHeroes;

	//another check for how the data is laid out. This is so we can immediately print out
	//heroes if we have already selected heroes. 
	if(progress > 1)
	{
		chosenHeroes = heroes;
	}	
	
	switch(progress)
	{
		//initial player identification
		case 0:
			playerName = getPlayerName();
			choice = chooseSaveFile();
			saveFileData(choice, choiceToFile(choice-1), NULL, playerName, 1);
		//hero selection
		case 1:
			chosenHeroes = pickHeroes(heroes);
			saveFileData(choice, choiceToFile(choice-1), chosenHeroes, playerName, 2);
			free(heroes);
		//equip heroes with items 
		case 2:
			//shop
			printHeroes(chosenHeroes, NUMCHOSENHEROES);
			free(chosenHeroes);
			//should never be past this point, so stop the pitfalling here. 
			break;
		//fight the boss (a boss? Maybe find some way to get more than one boss in there?)
		case 3: 
			//fight
			printf("Why is progree value 3? It should not be here yet.\n");
		default:
			//What?
			printf("Something fatal happened with the progress value. Check gamestate.txt.\n");
			break;
	}
	
	printf("\n\n**********Until Next Homework!*************\n\n");

	//I don't actually remember why I did this, but it works. 
	//I think because if it's a save file, it's freed elsewhere?
	if(initialprogress == 0)
	{
		free(playerName);
	}
	return;
}

int chooseSaveFile()
{
	//Initial load for data management. 
	char** names;
	int* states;
	int numFiles;
	int choice;
	int confirm = 1;

	loadGameStateData(&names, &states, &numFiles);
	
	//Get a chosen file slot to save to. The file slot must be valid, and 
	//old files can be overriden. 
	while(1)
	{
		confirm = 1;
		printf("\nChoose a file you would like to save to: \n");
		printf(">");
		scanf("%d", &choice);
		while((choice < 1 || choice > MAXNUMSAVEFILES))
		{
			printf("Invalid choice. Please choose a different option:\n ");
			printf(">");
			scanf("%d", &choice);
		}

		if(states[choice-1] != 0)
		{
			printf("There is a file here. Would you like to override it? (1 = yes, 0 = no)\n");
			printf(">");
			scanf("%d", &confirm);
			while(confirm != 1 && confirm != 0)
			{
				printf("Invalid choice. Please choose a different option:\n ");
				printf(">");
				scanf("%d", &confirm);
			}
		}

		if(confirm == 1)
		{
			//Go ahead and delete the old hero file immediately if there is one. 
			if(states[choice-1] == 2)
			{
				deleteFile(choice, choiceToFile(choice-1));
			}
			freeMemory(names, states);
			//I haven't found a bug yet with the state = 1, but there might be one somewhere. 
			return choice;
		}
	}
}
