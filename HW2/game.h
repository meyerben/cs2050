//don't add to this list. You won't need anything else.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//for expandable use.
#define NUMHEROES 6
#define NUMCHOSENHEROES 3
#define MAXNUMSAVEFILES 5
#define MAXPLAYERNAME 20
#define NUMSWORDS 10
#define NUMSHIELDS 8
#define STARTINGBANKVALUE 13000
typedef enum f_
{
	EXIST,
	DOESNOTEXIST
} FileFinder;

typedef struct shield_
{
	char name[40];
	int cost;
	int defense;
	struct shield_* nextShield;
	struct shield_* prevShield;
} Shield;

typedef struct sword_
{
	char name[40];
	int cost;
	int attack;
	struct sword_* nextSword;
	struct sword_* prevSword;
} Sword;

typedef struct shop_
{
	Sword* headSword;
	Shield* headShield;
} Shop;

typedef struct hero_
{
	char name[40];
	Sword* heroSword;
	Shield* heroShield;
	int health;
	int maxHealth;
	int baseDefense;
	int baseAttack;
	int baseSpeed;
} Hero;

typedef struct boss_
{
	char name[40];
	int health;
	int maxHealth;
	int baseDefense;
	int baseAttack;
	int baseSpeed;
} Boss;


//HW1 functions
void deleteFile(int choice, char* filename);
void saveFileData(int choice, char* filename, Hero* heroes, char* playerName, int progress);
char* getPlayerName();
Hero* loadSavedData(char* filename, int haveItems);
Hero* loadInitialData();
Hero* pickHeroes(Hero* heroes);
void sortHeroes(Hero* heroes);
void printHeroes(Hero* heroes, int numHeroes);

FileFinder findSaveFile();
void loadSavedGameHandler();
void DeleteSavedGameHandler();
void loadGameStateData(char*** names, int** states, int* fileCount);
char* choiceToFile(int num);
void freeMemory(char** names, int* states);
void startNewGame();
void playGame(Hero* heroes, char* playerName, Boss* boss, int progress, int choice);
int chooseSaveFile();
Shield* swapShields(Shield *p1, Shield *p2);
Sword* swapSwords(Sword *p1, Sword *p2);


//HW2 functions
Shop* loadShop();

void destroyShop(Shop* shop);

void goShopping(Hero* heroes, Shop* shop);

void printShields(Shield* shields);
void printSwords(Sword* swords);

Sword* removeSwordFromList(Sword** swords, int choice);
Shield* removeShieldFromList(Shield** shields, int choice);

void freeHeroesAndItems(Hero* heroes);

void sortShields(Shield**);
void sortSwords(Sword**);

int findSwordPrice(Sword*, int);
int findShieldPrice(Shield*, int);


