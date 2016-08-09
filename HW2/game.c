#include "game.h"

int main(void)
{
	while (1)
	{
		FileFinder finder = findSaveFile();
		int choice; 

		printf("Welcome to the Gauntlet!\n");
		printf("Select your option.\n");

		printf("1: start a new game\n");
		if (finder == EXIST)
		{
			printf("2: start a saved game\n");
			printf("3: delete a saved file\n");
			printf("4: quit\n");
			printf(">");	
			scanf("%d", &choice);
			while(choice < 1 || choice > 5)
			{
				printf("Invalid option. Try again: \n");
				printf(">");
				scanf("%d", &choice);
			}
			switch (choice)
			{
			case 1:
				startNewGame();
				break;
			case 2:
				loadSavedGameHandler();
				break;
			case 3:
				DeleteSavedGameHandler();
				break;
			case 4:
				return 0;
			}
		}
		else
		{
			printf("2: quit\n");
			printf(">");
			scanf("%d", &choice);
			while(choice < 1 || choice > 2)
			{
				printf("Invalid option. Try again: \n");
				printf(">");
				scanf("%d", &choice);
			}
			switch (choice)
			{
			case 1:
				startNewGame();
				break;
			case 2:
				return 0;
			}
		}
	}
}

char* getPlayerName()
{
	char* name = malloc(sizeof(char)*MAXPLAYERNAME);
	printf("Please input your name: ");
	scanf("%s", name);
	printf("Hello %s. Welcome to the gauntlet.\n", name);
	return name;
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
	Shop* s;
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
			s = loadShop();
			//Maybe?
			//testShop(s);
			goShopping(chosenHeroes, s);
			saveFileData(choice, choiceToFile(choice-1), chosenHeroes, playerName, 3);
		//fight the boss (a boss? Maybe find some way to get more than one boss in there?)
		case 3: 
			printHeroes(chosenHeroes, NUMCHOSENHEROES);
			freeHeroesAndItems(chosenHeroes);
			//fight	
			break;
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
