#include <stdio.h>
#include <time.h>
#include <stdlib.h>


void iniDeck(char *deck[104]){
    int i = 0;
    while(i < 14){
        deck[i] = "ccb";
        i++;
    };
    while(i < 28){
        deck[i] = "lb";
        i++;
    };
    while(i < 42){
        deck[i] = "empanada";
        i++;
    };
    while(i < 54){
        deck[i] = "2cupRice";
        i++;
    };
    while(i < 64){
        deck[i] = "halohalo";
        i++;
    };
    while(i < 70){
        deck[i] = "suka";
        i++;
    };
    while(i < 78){
        deck[i] = "3cupRice";
        i++;
    };
    while(i < 84){
        deck[i] = "1cupRice";
        i++;
    };
    while(i < 94){
        deck[i] = "chickenLumpia";
        i++;
    };
    while(i < 99){
        deck[i] = "tawgiLumpia";
        i++;
    };
    while(i < 104){
        deck[i] = "shanghaiLumpia";
        i++;
    };

}

void shuffle(char *array[104]){
    int n = 104;
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--){
        int j = rand() % (i + 1);
        char *temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void distribute(char *deck[104], char *playerHand[4][8], int round){
    int deckindex = ((round + 1) * (32)) - 32;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            playerHand[i][j] = deck[deckindex];
            deckindex++; 
        }
    }
}



int main(){
    int playerPoints[] = {0, 0, 0, 0}; //players points
    char *deck[104]; //deck of cards
    char *playerHand[4][8]; //cards for each player
    char *placedCards[4][8]; //cards used by the players
    
    iniDeck(deck); //deck initialize
    shuffle(deck);//shuffle deck

    printf("Fiesta GO!\n\n");

    for(int i = 0; i < 3; i++){
        //three rounds 4 players
        printf("Round %d\n", i + 1);

        distribute(deck, playerHand, i);//distribute 8 cards for each player
        
        for(int j = 0; j < 4; j++){
            printf("player%d: ", j + 1);
            for(int k = 0; k < 8; k++){
                printf("%d %s, ", k + 1, playerHand[j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }

    printf("hi");
    return 0;
}