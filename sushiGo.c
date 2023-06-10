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
void distribute(char *deck[104], char *playerCards[4][8], int round){
    int deckindex = ((round + 1) * (32)) - 32;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 8; j++){
            playerCards[i][j] = deck[deckindex];
            deckindex++; 
        }
    }
}

//calculate score
int calcScore(char *placedCards[4][8], int points[4]){
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
            }else{
                score++;
                //to be continued
            }
            
        }
        points[i] = score;
    }
}

int highest(int arr[4]){
    int max = arr[0];
    int index = 0;
    for(int i = 1; i < 4; i++){
        if(arr[i] > max){
            max = arr[i];
            index = i;
        }
    }
    return index;
}



int main(){
    int points[] = {0, 0, 0, 0}; //players points
    char *deck[104]; //deck of cards
    char *playerCards[4][8]; //cards for each player
    char *placedCards[4][8]; //cards used by the players
    
    iniDeck(deck); //deck initialize
    shuffle(deck);//shuffle deck

    printf("Fiesta GO!\n\n");

    for(int i = 0; i < 3; i++){
        //three rounds, 4 players
        printf(">>>Round %d<<<\n\n", i + 1);

        distribute(deck, playerCards, i);//distribute 8 cards for each player

        //turns
        int index[] = {0, 1, 2, 3}; //index for switching cards
        for(int t = 0; t < 8; t++){
            //if last card then place the break
            if(t == 7){
                for(int j = 0; j < 4; j++){
                    placedCards[j][t] = playerCards[index[j]][0];
                }
                //display picked cards
                for(int j = 0; j < 4; j++){
                    printf("Player %d:", j+1);
                    for(int k = 0; k <= t; k++){
                        printf("%s | ", placedCards[j][k]);
                    }
                    printf("\n");
                }
                printf("\n");
                break;   
            }
           
            //displaying the cards
            for(int j = 0; j < 4; j++){
                printf("player%d: ", j + 1);
                for(int k = 0; k < 8 - t; k++){
                    printf("<%d> %s | ", k, playerCards[index[j]][k]);
                }
                printf("\n");
            }
            printf("\n");

            //placing then removing cards from deck
            for(int j = 0; j < 4; j++){
                int chosenIndex;
                printf("Player %d's turn: ", j + 1);
                //bounds check
                scanf("%d", &chosenIndex);
                while(!((chosenIndex >= 0) && (chosenIndex <= 7 - t))){
                    printf("invalid input:<\n");
                    printf("Player %d's turn: ", j + 1);
                    scanf("%d", &chosenIndex);
                }
              
                //placing card
                placedCards[j][t] = playerCards[index[j]][chosenIndex];

                //removing
                for(int k = chosenIndex; k < 8 - t; k++){
                    playerCards[index[j]][k] = playerCards[index[j]][k+1];
                }
            }
            printf("\n");

            //displaying picked cards
            printf(">>>Picked Cards<<<\n");
            if(t == 6){
                continue;
            }
            for(int j = 0; j < 4; j++){
                printf("Player %d:", j+1);
                for(int k = 0; k <= t; k++){
                    printf("%s | ", placedCards[j][k]);
                }
                printf("\n");
            }

            //switching cards
            for(int j=0; j < 4; j++){
                index[j] = (index[j] + 1) % 4;
            }
            printf("\n>>>Switch!<<<\n\n");
        }
    }

    printf(">>Scores<<\n");
    calcScore(placedCards, points);
    for(int i = 0; i < 4; i++){
        printf("player %d: %d\n", i+1, points[i]);
    }
    printf("The Winner is Player %d with %d points!!!", highest(points) + 1, points[highest(points)]);

    return 0;
}