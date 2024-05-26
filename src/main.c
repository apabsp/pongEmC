//gcc -I./include src/*.c  -o pongGame
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#define SCREEN_HEIGHT 48
#define SCREEN_WIDTH 180
#define SCORE_TO_WIN 100
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_BLUE "\033[0;34m"


struct barrinha{
    int posY;
    int posX;
    char direction; // pode ser Up Down Middle
    struct barrinha *next;

};

struct bola{
    char myRepresentation[30];
    int posX;
    int posY;
    int dirX;
    int dirY;
    struct bola *next; //Interesting thing about this is that we want to continuously be deleting the head and then filling in the *next
};

struct ballDirection{

    int dirX;
    int dirY;
};


void moveBall(struct bola *bolinha) {
    
    screenGotoxy(bolinha->posX, bolinha->posY);
    printf(" ");
    
    
    bolinha->posX += bolinha->dirX;
    bolinha->posY += bolinha->dirY;
    
    
    screenGotoxy(bolinha->posX, bolinha->posY);
    printf("%s", bolinha->myRepresentation);

}


void centerBallandGoLeft( struct bola *bolinha){

    bolinha->posX = SCREEN_WIDTH/2;
    bolinha->posY = SCREEN_HEIGHT/2;
    bolinha->dirX = -1;
    bolinha-> dirY = 0;
}

void centerBallandGoRight( struct bola *bolinha){

    bolinha->posX = SCREEN_WIDTH/2;
    bolinha->posY = SCREEN_HEIGHT/2;
    bolinha->dirX = 1;
    bolinha-> dirY = 0;
}

void boogieWoogie( struct bola *bolinha){
//potential power up
    bolinha->posX = 30;
    bolinha->posY = 30;
}



void collisionCheck(struct barrinha *headEsquerda, struct barrinha *headDireita, struct bola *bolinha, int *ponteiroDoScoreP1, int *ponteiroDoScoreP2){
    //so for collisions we have a few options:
    // colliding with paddle 1, paddle 2, upper wall, bottom wall, left goal and right goal

    //(if we're in 4playerMode, we add paddle3, paddle4, left wall, right wall, upper goal and botom goal)

    int momentOfImpactX;
    int momentOfImpactY;

    struct barrinha *imhere = NULL;
    imhere = headEsquerda;
    while(imhere != NULL){

        if ( bolinha->posX == imhere->posX && bolinha->posY == imhere->posY){ // WE GET A PADDLE HIT RIGHT HERE on the leftPaddle

            // which part of the paddle is it? upper part? middlep art? bottom part???
            bolinha->dirX=1; //I reverse the result to go the other way, right?
            if(imhere->direction == 'u') {
                bolinha->dirY = -1; // should go up
            } else if(imhere->direction == 'd') {
                bolinha->dirY = 1; // down
            } else {
                bolinha->dirY = 0; // straight ahead
            }
        }
        imhere = imhere->next;
    }

    imhere = headDireita;
    while(imhere != NULL){

        if ( bolinha->posX == imhere->posX && bolinha->posY == imhere->posY){ // WE GET A PADDLE HIT RIGHT HERE on the rightPaddle
            bolinha->dirX=-1;
            if(imhere->direction == 'u') {
                bolinha->dirY = -1; // should go up
            } else if(imhere->direction == 'd') {
                bolinha->dirY = 1; // down
            } else {
                bolinha->dirY = 0; // straight ahead
            }
        }
        imhere = imhere->next;
    }

    //now we need a check to see IF the ball hit the limit of the canvas. If it did so, on the top/bottom, simply bounce back. If it did on the left or right, give score

    if (bolinha->posY == 1){ // supposedly this means it hit the top of the canvas
        //printf("ACERTOU O TOP!!!");
        momentOfImpactX= bolinha->posX;
        momentOfImpactY= bolinha->posY;
        bolinha->dirY =  1;
        screenGotoxy(momentOfImpactX,momentOfImpactY);
        printf("─");

        
    }

    if (bolinha->posY == SCREEN_HEIGHT){ // supposedly this means it hit the top of the canvas, so I need the final result to be negative SCREEN HEIGHT
        screenGotoxy(bolinha->posX, bolinha->posY);
        bolinha->dirY =  -1;
        printf("─");
        

    }


    //first, scores:

    if (bolinha->posX == SCREEN_WIDTH){ // right side has been hit!!!
        *ponteiroDoScoreP1 = *ponteiroDoScoreP1 + 1;
        screenGotoxy(bolinha->posX, bolinha->posY); // might be next pointer here instead
        printf("│");
        centerBallandGoRight(bolinha);
    }


    if (bolinha->posX == 1){ // left side has been hit!!!
        *ponteiroDoScoreP2 = *ponteiroDoScoreP2 + 1;
        screenGotoxy(bolinha->posX, bolinha->posY); // might be next pointer here instead
        printf("│");
        centerBallandGoLeft(bolinha);
    }

    //what now?,right, teleportation of ball in case we get a score.

    // would be cool to check barrinha head n bottom to move it up/down too, so it doesn't go beyond the limits..



}


void debugMode(struct bola *bolinha){
    screenGotoxy(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    printf("                             ");
    screenGotoxy(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    printf("x: %d y: %d", bolinha->posX, bolinha->posY);



}






void startMyPaddle(struct barrinha **head, int startingPositionX, int startingPositionY, int height) { // recommended height is 6
    *head = (struct barrinha *)malloc(sizeof(struct barrinha));
    (*head)->posY = startingPositionY;
    (*head)->posX = startingPositionX;
    (*head)->next = NULL;

    struct barrinha *current = *head;
    current->direction = 'u';

    for (int i = 1; i < height; i++) {
        struct barrinha *meuNovo = (struct barrinha *)malloc(sizeof(struct barrinha));
        meuNovo->posY = startingPositionY + i; 
        meuNovo->posX = startingPositionX;
       // Intencao era se I for menor que 25% do height, mas nao funcionou totalmente.
       
        if ( i <= 1){

            meuNovo->direction = 'u';

        } else if(i >= height - 2){
            meuNovo->direction = 'd';
        }
        else{
            meuNovo->direction = 'm';
        }

        meuNovo->next = NULL;

        current->next = meuNovo;
        current = current->next;
    }
}

void positionMyThing(struct barrinha *head){
    struct barrinha *n = head;
    while( n !=  NULL){
        
        screenGotoxy(n->posX, n->posY);
        printf("%c", n->direction);
        n = n -> next;
        
    }

}

void showScore(int *p1Score, int *p2Score, char player1Name[50], char player2Name[50], int *flag){

    screenGotoxy(20 ,20);
    printf("%s: %d", player1Name, *p1Score);

    screenGotoxy(SCREEN_WIDTH-20, 20);
    printf("%s: %d", player2Name, *p2Score);

    if(*p1Score  >= SCORE_TO_WIN){
        *flag = 1;
        screenClear();
        printf("%s WINS!!!", player1Name);
    }
    if(*p2Score  >= SCORE_TO_WIN){
        *flag = 1;
        screenClear();
        printf("%s WINS!!!", player2Name);
    }

//HITTING THE LEFT SIDE MADE TONY GO UP BY 1
}


void modifyMyThing(struct barrinha *head, int newX, int newY){
    struct barrinha *n = head;

    screenGotoxy(n->posX, n->posY);
    printf(" ");

    while( n !=  NULL){

        if( n->next ==NULL){
            screenGotoxy(n->posX,n->posY);
            printf(" ");
        }
        
        n->posY += newY;
        n->posX += newX;
        n = n->next;
        
    }

}

void gameMode1Log(char nome1[50], char nome2[50], int score1, int score2){
    FILE *game;
    game = fopen("gameMode1.txt", "a");

    fprintf(game, "%s\n%s\n%d %d\n", nome1, nome2, score1, score2);
    fclose(game);
}

void game1(char player1Name[50], char player2Name[50]){

    screenInit(1);
    keyboardInit();
    timerInit(25); 
    screenDrawBorders(); 

    
    struct barrinha *myLeftPaddle = NULL;
    struct barrinha *myRightPaddle = NULL;
    int height = 6;
    startMyPaddle(&myLeftPaddle, 5, SCREEN_HEIGHT/2, height); // remember, this initializes where THE HEAD starts. So the spawn isn't centered. intentional.
    startMyPaddle(&myRightPaddle, SCREEN_WIDTH - 5, SCREEN_HEIGHT/2, height);

    /*Might be cool to turn this entire thing into a bolinha initializer function v*/
    struct bola *bolinha = (struct bola*)malloc(sizeof(struct bola));
    //bolinha->myRepresentation = "0";
    strcpy(bolinha->myRepresentation,"🏐");
    centerBallandGoRight(bolinha);

    struct bola *next = (struct bola*)malloc(sizeof(struct bola));
    
    next->posX = 30;
    next->posY = 30;
    //next->myRepresentation = "O";
    strcpy(next->myRepresentation,"🏐");
    next->dirX = 1;
    next->dirY = 0;
    bolinha->next = next;
    int scoredo1 = 0;
    int scoredo2 = 0;
    int *p1Score = &scoredo1;
    int *p2Score = &scoredo2;
    int flagForGameOver = 0; // turn this into 1 to end game!!

    //(int *p1Score, int *p2Score, char player1Name[50], char player2Name[50])
    while (flagForGameOver == 0) {
        
        //comment this to stop debug mode:
        showScore(p1Score, p2Score, player1Name, player2Name, &flagForGameOver);
        debugMode(bolinha);
        if (timerTimeOver()) {
            positionMyThing(myLeftPaddle);
            positionMyThing(myRightPaddle);
            moveBall(bolinha);
            if (keyhit()) {
                int key = readch();
                if (key == 'w'){
                    modifyMyThing(myLeftPaddle, 0, -1);
                }
                else if (key == 's'){
                    modifyMyThing(myLeftPaddle, 0, 1);
                }
                else if (key == 'i'){
                    modifyMyThing(myRightPaddle, 0, -1);
                }
                else if (key == 'k'){
                    modifyMyThing(myRightPaddle, 0, 1);
                }
                
                
            }
            //void collisionCheck(struct barrinha *headEsquerda, struct barrinha *headDireita, struct bola *bolinha){
            collisionCheck(myLeftPaddle, myRightPaddle, bolinha, p1Score, p2Score);
        }


    }
    
    gameMode1Log(player1Name, player2Name, scoredo1, scoredo2);
        
}

void selectScreen(){
    //so I'm thinking of having nodes that can go back and forth. Depending on the getKey(), it goes up or down on the list! if it encounters null, don't do nothin

    //exactly then, I can have two functions that can be pulled right here, depending on the user's input: he can either up-down or press select
    //function 1 will be for up-down, where we'll iterate through the list and change the node's "active or inactive" variable.
    //function 2 will be for selecting the game mode, again by iterating through the list and checking which node is active

    screenInit(1);

    struct nodeMenuOption{
        int isThisTheOptionChosen; // 0 is for no, 1 is for yes. The HEAD will always start as 1
        struct node *next;
        struct node *previous;

    };
    screenGotoxy(15, 10);
    printf("%s  _____   ____  _   _  _____     %s %s     __  __           _____ _______ ______ _____   _____ %s\n", COLOR_RED, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
    screenGotoxy(15, 11);
    printf("%s |  __ \\ / __ \\| \\ | |/ ____| %s %s       |  \\/  |   /\\    / ____|__   __|  ____|  __ \\ / ____|%s\n", COLOR_RED, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
    screenGotoxy(15, 12);
    printf("%s | |__) | |  | |  \\| | |  __     %s %s    | \\  / |  /  \\  | (___    | |  | |__  | |__) | (___  %s\n", COLOR_RED, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
    screenGotoxy(15, 13);
    printf("%s |  ___/| |  | | . ` | | |_ |     %s %s   | |\\/| | / /\\ \\  \\___ \\   | |  |  __| |  _  / \\___ \\ %s\n", COLOR_RED, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
    screenGotoxy(15, 14);
    printf("%s | |    | |__| | |\\  | |__| |    %s %s    | |  | |/ ____ \\ ____) |  | |  | |____| | \\ \\ ____) |%s\n", COLOR_RED, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
    screenGotoxy(15, 15);
    printf("%s |_|     \\____/|_| \\_|\\_____|  %s %s      |_|  |_/_/    \\_\\_____/   |_|  |______|_|  \\_\\_____/%s feito em C\n", COLOR_RED, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
    screenGotoxy(15, 17);
    printf("por ANTONIO PAULO BARROS, HELOISA TANAKA, RAFAELA VIDAL\n");
    


    while(1){
        
    }
    screenDestroy();
}


void escreverHistoricoDePartidas(){
    FILE *myLittleBigFile, *historico;
    myLittleBigFile = fopen("gameMode1.txt", "r");
    if (myLittleBigFile == NULL) {    
        printf("Não há histórico!");
    }
    else{
        historico = fopen("historico.txt", "w");
        while(!feof(myLittleBigFile)){
            char playerName1Buffer[100], playerName2Buffer[100];
            int score1, score2, len;

            if(fgets(playerName1Buffer, 100, myLittleBigFile) == NULL){
                break;
            };
            len = strlen(playerName1Buffer);
            playerName1Buffer[len - 1] = '\0';

            fgets(playerName2Buffer,100, myLittleBigFile);
            len = strlen(playerName2Buffer);
            playerName2Buffer[len - 1] = '\0';

            fscanf(myLittleBigFile, "%d %d", &score1, &score2);

            fprintf(historico, "%s vs %s (%d - %d)\n", playerName1Buffer, playerName2Buffer, score1, score2);

            fgetc(myLittleBigFile);
        }
        fclose(historico);

    }
    fclose(myLittleBigFile);
}


int main()
{

    //selectScreen();
    int escolha, len;
    while(1){
        escreverHistoricoDePartidas();
        printf("\nOla! Selecione o modo de jogo: \n1- 2 jogadores\n2- 4 jogadores\n");
        scanf("%d", &escolha);
        if(escolha == 1){
            
            char player1Name[50], player2Name[50];
            getchar();
            printf("Digite o nome do Player 1: ");
            fgets(player1Name, 50, stdin);
            len = strlen(player1Name);
            player1Name[len - 1] = '\0';
            
            printf("Digite o nome do Player 2: ");
            fgets(player2Name, 50, stdin);
            len = strlen(player2Name);
            player2Name[len - 1] = '\0';

            struct bola bolinha;
            //startgame1 function
            game1(player1Name,player2Name);

        }
    }


    return 0;
}
