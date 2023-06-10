#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

//initalizing deck
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

//shuffling deck
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

//distribute cards to 4 playersa
void distribute(char *deck[104], char *playerHand[4][8], int round){
    int deckindex = ((round + 1) * (32)) - 32;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            playerHand[i][j] = deck[deckindex];
            deckindex++; 
        }
    }
}

//calculate score
int calcScore(char *placedCards[4][8], int payerPoints[4]){
    for(int i = 0; i < 4; i++){
        int score = 0;
        for(int j = 0; j < 8; j++){
            char* card = placedCards[i][j];
            if(strcmp(card, "tawgiLumpia")==0){
                score += 1;
            }else if(strcmp(card, "chickenLumpia")==0){
                score += 2;
            }else if(strcmp(card, "shanghaiLumpia")==0){
                score += 3;
            }else if(strcmp(card, "suka")==0){
                for(int k = j - 1; k >= 0; k--){
                    if(strcmp(placedCards[i][k], "chickenLumpia")==0){
                        score = (score - 2) + (2 * 3);
                        break;
                    }else if(strcmp(placedCards[i][k], "shanghaiLumpia")==0){
                        score = (score - 3) + (3 * 3);
                        break;
                    }else if(strcmp(placedCards[i][k], "tawgiLumpia")==0){
                        score = (score - 1) + (3);
                        break;
                    }else{
                        continue;
                    }
                }
            }
            //to be continued
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
        //three rounds, 4 players
        printf(">>>Round %d<<<\n\n", i + 1);

        distribute(deck, playerHand, i);//distribute 8 cards for each player

        //turns
        for(int t = 0; t < 8; t++){
            int index[] = {0, 1, 2, 3, 4}; //index for switching cards

            //displaying the cards
            for(int j = 0; j < 4; j++){
                printf("player%d: ", j + 1);
                for(int k = 0; k < 8 - t; k++){
                    printf("<%d> %s | ", k, playerHand[index[j]][k]);
                }
                printf("\n");
            }
            printf("\n");

            //placing then removing cards from deck
            for(int j = 0; j < 4; j++){
                int chosenIndex;
                printf("Player %d's turn: ", j + 1);
                scanf("%d", &chosenIndex);
                //choosing card
                placedCards[j][t] = playerHand[index[j]][chosenIndex];

                //removing
                for(int k = chosenIndex; k < 8 - t; k++){
                    playerHand[index[j]][k] = playerHand[index[j]][k+1];
                }
            }
            printf("\n");

            //displaying picked cards
            printf(">>>Picked Cards<<<\n");
            for(int j = 0; j < 4; j++){
                printf("Player %d:", j+1);
                for(int k = 0; k <= t; k++){
                    printf("%s | ", placedCards[j][k]);
                }
                printf("\n");
            }

            //switching cards
            for(int j=0; j < 4; j++){
                index[j] = (index[j] + 1) % 5;
            }
            printf("\n>>>Switch!<<<\n\n");
        }

    }

    return 0;
}