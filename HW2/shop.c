#include "game.h"


Shop* loadShop()
{
	//create a spot in memory for the shop
	Shop* shop = (Shop*)malloc(sizeof(Shop));
	//initialize both linked lists
	shop->headSword = NULL;
	shop->headShield = NULL;
	//open the file
	FILE* fp = fopen("Items.txt", "r");
	//check the file
	if(fp == NULL) printf("boink!");
	int i;
	//iterate through part the file for shields
	//i needs to equal 1 because it will always run the if statement in the first loop
	for(i=1;i<NUMSHIELDS;i++)
	{
		//if the list is empty (for the first node)
		if(shop->headShield == NULL)
		{
			//make room for a new shield
			Shield *newShield = (Shield*)malloc(sizeof(Shield));
			//give that new shield data
			fscanf(fp, "%s | %d | %d\n", newShield->name, &newShield->cost, &newShield->defense );
			//make it point to NULL and become a valid linked list
			newShield->nextShield = NULL;
			//move the head to the beginning
			shop->headShield = newShield;
		}
		//create a pointer to the head
		Shield* shieldPtr = shop->headShield;
		//iteration to the end of the linked list
		while(shieldPtr->nextShield !=NULL)
		{
			shieldPtr = shieldPtr->nextShield;	
		}
		//create space for a new shield
		Shield *newShield = (Shield*)malloc(sizeof(Shield));
		//the previous tail (not null) needs to point this new shield
		shieldPtr->nextShield = newShield;
		//give this new shield some data
		fscanf(fp, "%s | %d | %d\n", newShield->name, &newShield->cost, &newShield->defense );
		//make sure this new shield points to NULL to end the linked list
		newShield->nextShield = NULL;
	}
	//same for swords
	for(i=1;i<NUMSWORDS;i++)
	{
		if(shop->headSword == NULL)
		{
			Sword *newSword = (Sword*)malloc(sizeof(Sword));
			fscanf(fp, "%s | %d | %d\n", newSword->name, &newSword->cost, &newSword->attack );
			newSword->nextSword = NULL;
			shop->headSword = newSword;
		}
		Sword* SwordPtr = shop->headSword;
		while(SwordPtr->nextSword !=NULL)
		{
			SwordPtr = SwordPtr->nextSword;	
		}
		Sword *newSword = (Sword*)malloc(sizeof(Sword));
		SwordPtr->nextSword = newSword;
		fscanf(fp, "%s | %d | %d\n", newSword->name, &newSword->cost, &newSword->attack );
		newSword->nextSword = NULL;
	}
	//close the file
	fclose(fp);
	//function returns shop
	return shop;
}


void destroyShop(Shop* shop)
{
	//create 2 new pointers at the head of sword and shield
	Shield* currShield = shop->headShield;
	Sword* currSword = shop->headSword;
	//iterate
	while(shop->headShield!=NULL)
	{
		//stepper
		currShield = currShield->nextShield;
		//free shield
		free(shop->headShield);
		//move head
		shop->headShield = currShield;
	}
	while(shop->headSword!=NULL)
	{
		currSword = currSword->nextSword;
		free(shop->headSword);
		shop->headSword = currSword;
	}
	//don't forget to free the shop
	free(shop);
}

/*
void sortShields(Shield** shields)
{
	//create some pointers
	Shield *shieldPtr = *shields; //head pointer
	//as I'm writing comments, i hate that i named this "nextShield" but whatevs
    Shield *nextShield = shieldPtr->nextShield; //next pointer
	//create a variable that allows us to swap values
    int tmpVal;
	//while the nextPtr isn't null iteration
    while(nextShield != NULL){
    		//and while the nextPtr does not equal the headPtr
           while(nextShield != shieldPtr){
           			//and their values aren't in order
                    if(nextShield->cost < shieldPtr->cost){
                    		//swap the values
                            tmpVal = shieldPtr->cost;
                            shieldPtr->cost = nextShield->cost;
                            nextShield->cost = tmpVal;
                    }
                    //move the head (now the 2 ptrs are equal)
                    shieldPtr = shieldPtr->nextShield;
            }
            //move the head back in place
            shieldPtr = *shields;
            //move the nextPtr
            nextShield = nextShield->nextShield;
    }
}*/

void sortShields(Shield** shields)
{
	//create some new pointers
	Shield *aPtr, *bPtr, *newHead;
    //gate
    int changed = 1;
	//create space for a new node
    newHead = (Shield *)malloc(sizeof(Shield));
	//make this new node point to the front node
    newHead->nextShield = *shields;
    //if list is not empty and longer than 1 node
    if( *shields != NULL && (*shields)->nextShield != NULL ) {

		
        while( changed ) {
        	
        	//close gateway
            changed = 0;
            //pointer to the beginning
            bPtr = newHead;
            //pointer to the OG head
            aPtr = newHead->nextShield;
            //iteration
            while( aPtr->nextShield != NULL ) {
                /* push bigger items down */
                //compare the values
                if( aPtr->cost > aPtr->nextShield->cost ) {
                	//swap places
                    bPtr->nextShield = swapShields( aPtr, aPtr->nextShield );
                    //open the gate back up
                    changed = 1;
                }
                //move bPtr up to a;
                bPtr = aPtr;
                if( aPtr->nextShield != NULL )
                	//move aPtr forward
                    aPtr = aPtr->nextShield;
            }
        }
    }
    //aPtr moves to head
    aPtr = newHead->nextShield;
    free( newHead );
}

//works exactly as shields
void sortSwords(Sword** swords)
{
	//create some new pointers
	Sword *aPtr, *bPtr, *newHead;
    int changed = 1;

    newHead = (Sword *)malloc(sizeof(Sword));

    newHead->nextSword = *swords;
    if( *swords != NULL && (*swords)->nextSword != NULL ) {


        while( changed ) {
            changed = 0;
            bPtr = newHead;
            aPtr = newHead->nextSword;
            while( aPtr->nextSword != NULL ) {
                /* push bigger items down */
                if( aPtr->cost > aPtr->nextSword->cost ) {
                    bPtr->nextSword = swapSwords( aPtr, aPtr->nextSword );
                    changed = 1;
                }
                bPtr = aPtr;
                if( aPtr->nextSword != NULL )
                    aPtr = aPtr->nextSword;
            }
        }
    }
    aPtr = newHead->nextSword;
    free( newHead );
}

void printShields(Shield* shields)
{
	//create a new pointer
	Shield *curr;
	//this is for prettier code
	int i = 0;
	//curr points to head; iterates through the list, also increments i
	for(curr = shields;curr!=NULL;curr = curr->nextShield,i++)
	{
		//print it all. yay
		printf("%d: %s: \n     $%d \n     Def: %d\n", i+1, curr->name, curr->cost, curr->defense);
	}
}

//works like shields
void printSwords(Sword* swords)
{
	Sword *curr = (Sword*)malloc(sizeof(Sword));
	int i=0;
	for(curr=swords;curr!=NULL;curr = curr->nextSword,i++)
	{
		
		printf("%d: %s: \n      $%d \n     Atk: %d\n", i+1, curr->name, curr->cost, curr->attack);
	}
}

Sword* removeSwordFromList(Sword** swords, int choice)
{
	int i;
	Sword *currSword, *prevSword;
	prevSword = NULL;
	currSword = *swords;
	for(i=1;i<choice;i++)
	{
		prevSword = currSword;
		currSword = currSword->nextSword;
	}
	if(prevSword == NULL)
	{
		*swords = currSword->nextSword;
	}
	else
	{
		prevSword->nextSword = currSword->nextSword;
	}
	/*       Here Lies               */
	/*********************************/
	/*Spaghetti Code 3/22/16-3/25/16 */
	/*     You will not be missed    */
	/*********************************/
	//Sword* yourSword = (Sword*)malloc(sizeof(Sword));
	//yourSword = currSword;
	//free(currSword);
	/*********************************/
	return currSword;
}

//works the same as shields
Shield* removeShieldFromList(Shield** shields, int choice)
{
	int i;
	Shield *currShield, *prevShield;
	prevShield = NULL;
	currShield = *shields;
	for(i=1;i<choice;i++)
	{
		prevShield = currShield;
		currShield = currShield->nextShield;
	}
	if(prevShield == NULL)
	{
		*shields = currShield->nextShield;
	}
	else
	{
		prevShield->nextShield = currShield->nextShield;
	}
	/*********************************/
	/*       Here Lies               */
	/*Spaghetti Code 3/22/16-3/25/16 */
	/*     You will not be missed    */
	/*********************************/
	//Shield* yourShield = (Shield*)malloc(sizeof(Shield));
	//yourShield = currShield;
	//free(currShield);
	/*********************************/
	return currShield;
}

Shield* swapShields(Shield *p1, Shield *p2)
{
	//p1 pretty much jumps over p2 and they trade places
	p1->nextShield = p2->nextShield;
    p2->nextShield = p1;
    return p2;
}

Sword* swapSwords(Sword *p1, Sword *p2)
{
	p1->nextSword = p2->nextSword;
    p2->nextSword = p1;
    return p2;
}

/***************************START OF FUNCTIONS GIVEN TO YOU**********************************/

void freeHeroesAndItems(Hero* heroes)
{
	int i;
	for(i = 0; i < NUMCHOSENHEROES; i++)
	{
		if(heroes[i].heroSword != NULL)
		{
			free(heroes[i].heroSword);
		}
		if(heroes[i].heroShield != NULL)
		{
			free(heroes[i].heroShield);
		}
	}
	free(heroes);
}

void goShopping(Hero* heroes, Shop* shop)
{

	printf("\n\nNow, you will select a sword and shield for your heroes.\n");

	int firstPass = 1; 

	int bank = STARTINGBANKVALUE;

	while(1)
	{
		printf("Which would you like to look at?\n");
		printf("1: Swords\n2: Shields\n3: Continue to fight\n");
		printf("> ");
		int choice; 
		scanf("%d", &choice);
		while(choice < 1 || choice > 3)
		{
			printf("Invalid choice. Select again: \n");
			printf("> ");
			scanf("%d", &choice);
		}

		if(choice == 3)
		{
			if(firstPass == 1)
			{
				printf("Are you sure you don't want to buy anything?\n");
				printf("1: yes\n2: no\n");
				printf("> ");
				scanf("%d", &choice);
				while(choice < 1 || choice > 2)
				{
					printf("Invalid choice. Select again: \n");
					printf("> ");
					scanf("%d", &choice);
				}
			}
			else
			{
				choice = 1;
			}

			if(choice == 1)
			{
				destroyShop(shop);
				return;
			}
		}
		else if(choice == 2)
		{
			printf("Do you want it sorted (1) or unsorted? (2)\n");
			printf(">");
			int sortChoice;
			scanf("%d", &sortChoice);
			while(sortChoice != 1 && sortChoice != 2)
			{
				printf("Invalid choice, choose again: ");
				printf(">");
				scanf("%d", &sortChoice);
			}

			if(sortChoice == 1)
			{
				sortShields(&(shop->headShield));
			}
			

			while(1)
			{
				printShields(shop->headShield);
				
				while(1)
				{
					printf("\nBudget: %d\n", bank);
					printf("Select a shield (-1 to go back): \n");
					printf("> ");
					scanf("%d", &choice);
	
					while((choice < 1 || choice > NUMSHIELDS) && choice != -1)
					{
						printf("Invalid choice. Select again: \n");
						printf("> ");
						scanf("%d", &choice);
					}
				
					if(choice != -1)
					{
						if(findShieldPrice(shop->headShield, choice) > bank)
						{
							printf("You don't have enough money for that!\n");
						}
						else break;
					}
					else break;
				}

				if(choice == -1)
				{
					break;
				}
				else
				{
					int heroChoice; 

					while(1)
					{
						printHeroes(heroes, NUMCHOSENHEROES);
						printf("Which hero do you want to have the item? (-1 to go back): \n");
						printf("> ");
						scanf("%d", &heroChoice);

						while((heroChoice < 1 || heroChoice > NUMCHOSENHEROES) && heroChoice != -1)
						{
							printf("Invalid choice. Select again: \n");
							printf("> ");
							scanf("%d", &heroChoice);
						}

						if(heroes[heroChoice - 1].heroShield != NULL)
						{
							printf("That hero already has a shield. Choose again.\n");
						}
						else
						{
							break;
						}

					}
					

					if(heroChoice == -1)
					{
						break;
					}
					else
					{
						Shield* item = removeShieldFromList(&(shop->headShield), choice);
						heroes[heroChoice - 1].heroShield = item;
						bank -= item->cost;
						firstPass = 0;
					}
				}
			}
		}
		else if(choice == 1)
		{
			printf("Do you want it sorted (1) or unsorted? (2)\n");
			printf(">");
			int sortChoice;
			scanf("%d", &sortChoice);
			while(sortChoice != 1 && sortChoice != 2)
			{
				printf("Invalid choice, choose again: ");
				printf(">");
				scanf("%d", &sortChoice);
			}

			if(sortChoice == 1)
			{
				sortSwords(&(shop->headSword));
			}
			
			while(1)
			{
				printSwords(shop->headSword);
				
				while(1)
				{
					printf("\nBudget: %d\n", bank);
					printf("Select a sword (-1 to go back): \n");
					printf("> ");
					scanf("%d", &choice);
	
					while((choice < 1 || choice > NUMSWORDS) && choice != -1)
					{
						printf("Invalid choice. Select again: \n");
						printf("> ");
						scanf("%d", &choice);
					}
				
					if(choice != -1)
					{
						if(findSwordPrice(shop->headSword, choice) > bank)
						{
							printf("You don't have enough money for that!\n");
						}
						else break;
					}
					else break;
				}

				if(choice == -1)
				{
					break;
				}
				else
				{
					int heroChoice; 

					while(1)
					{
						printHeroes(heroes, NUMCHOSENHEROES);
						printf("Which hero do you want to have the item? (-1 to go back): \n");
						printf("> ");
						scanf("%d", &heroChoice);

						while((heroChoice < 1 || heroChoice > NUMCHOSENHEROES) && heroChoice != -1)
						{
							printf("Invalid choice. Select again: \n");
							printf("> ");
							scanf("%d", &heroChoice);
						}

						if(heroes[heroChoice - 1].heroSword != NULL)
						{
							printf("That hero already has a sword. Choose again.\n");
						}
						else
						{
							break;
						}
					}
					if(heroChoice == -1)
					{
						break;
					}
					else
					{
						Sword* item = removeSwordFromList(&(shop->headSword), choice);
						heroes[heroChoice - 1].heroSword = item;
						bank -= item->cost;
						firstPass = 0;
					}
				}
			}
		}
	}
}

int findSwordPrice(Sword* swords, int choice)
{
	int i = 1;
	while(i < choice)
	{
		swords = swords->nextSword;
		i++;
	}
	return swords->cost;
}

int findShieldPrice(Shield* shields, int choice)
{
	int i = 1;
	while(i < choice)
	{
		shields = shields->nextShield;
		i++;
	}
	return shields->cost;
}