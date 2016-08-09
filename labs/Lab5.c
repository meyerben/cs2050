#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
 typedef enum {
     PENNY = 1,
     NICKEL = 5,
     DIME = 10,
     QUARTER = 25,
 } Denomination;
 
 typedef struct {
     Denomination denomination;
     int quantity;
 } Coin;
 
 typedef Coin* PiggyBank;
 
 
 PiggyBank loadBank(const char* filename, int* lenPtr);
 char* enumToString(Denomination denomination);
 int totalMoney(PiggyBank bank, int length);
 void printBankToScreen(PiggyBank bank, int length);
 void sortByQuantity(PiggyBank bank, int length);
 void writeToFile(const char* filename, PiggyBank bank, int length);
 PiggyBank minimumChange(int amount);
 
 PiggyBank loadBank(const char* filename, int* lenPtr){
    FILE* fptr = fopen(filename, "r");
    if (fptr == NULL) printf("boink\n");
    
    fscanf(fptr, "%d", lenPtr);
    
    PiggyBank myBank = malloc(sizeof(Coin)* *lenPtr);
    
    int i;
    for(i=0;i<*lenPtr;i++)
    {
        fscanf(fptr, "%u %d", &myBank[i].denomination, &myBank[i].quantity);
    }
    
    fclose(fptr);
    return myBank;
 }
 
 char* enumToString(Denomination denomination){
    switch(denomination) {
        case(PENNY):
            return "penny";
            break;
        case(NICKEL):
            return "nickel";
            break;
        case(DIME):
            return "dime";
            break;
        case(QUARTER):
            return "quarter";
            break;
        default:
            return "boink";
    }
 }
 
int totalmoney(PiggyBank bank, int length){
    int i;
    int sum=0;
    for(i=0;i<length;i++)
    {
        sum += (bank[i].denomination * bank[i].quantity);
    }
    
    return sum;
 }
 
void printBankToScreen(PiggyBank bank, int length){
    int i;
    
    printf("You have %d cents in your piggy bank\n", totalmoney(bank, length) );
    
    for(i=0;i<length;i++)
    {
        printf("%s %d\n", enumToString(bank[i].denomination), bank[i].quantity);
    }
}

void sortByQuantity(PiggyBank bank, int length){
    int i;
    int j;
    Coin temp;
    
    for(i=1;i<length;i++)
    {
        j = i;
    
        while( j > 0 && bank[j].quantity < bank[j-1].quantity)
        {
           temp.quantity = bank[j].quantity;
           temp.denomination = bank[j].denomination;
           bank[j].quantity = bank[j-1].quantity;
           bank[j].denomination = bank[j-1].denomination;
           bank[j-1].quantity = temp.quantity;
           bank[j-1].denomination = temp.denomination;
           
           j--;
        }
        
    }
}

void writeToFile(const char* filename, PiggyBank bank, int length){
    FILE* fptr = fopen(filename, "w");
    if (fptr == NULL) printf("boink\n");
    
    fprintf(fptr, "%d\n", length);
    int i;
    for(i=0;i<length;i++)
    {
        fprintf(fptr, "%u %d\n", bank[i].denomination, bank[i].quantity);
    }
    
    fclose(fptr);
}
 
int main(int argc, char* argv[])
 {
    int length;
    
    PiggyBank myBank = loadBank(argv[1], &length);
    printBankToScreen(myBank, length);
    sortByQuantity(myBank, length);
    writeToFile(argv[2], myBank, length);
    
    free(myBank);
    
    int amount;
    printf("\n\n ***Bonus*** \n\n");
    printf("Enter an amount of change: ");
    scanf("%d", &amount);
    PiggyBank newBank = minimumChange(amount);
    printf("\n%d can be made with: \n", amount);
    
    printf("%d quarters\n", newBank[0].quantity);
    printf("%d dimes\n", newBank[1].quantity);
    printf("%d nickels\n", newBank[2].quantity);
    printf("%d pennies\n", newBank[3].quantity);

    free(newBank);
    
    return 0;
    
 }
 
PiggyBank minimumChange(int amount){
    PiggyBank newBank = malloc(sizeof(Coin)* 4);
    
    newBank[0].denomination = QUARTER;
    newBank[1].denomination = DIME;
    newBank[2].denomination = NICKEL;
    newBank[3].denomination = PENNY;
    
    newBank[0].quantity = amount/25;
    amount -= (newBank[0].quantity * 25);
    
    newBank[1].quantity = amount/10;
    amount -= (newBank[1].quantity * 10);
    
    newBank[2].quantity = amount/5;
    amount -= (newBank[2].quantity * 5);
    
    newBank[3].quantity = amount/1;
    
    return newBank;
}
 