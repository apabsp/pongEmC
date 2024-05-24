//gcc -I./include src/*.c  -o pongGame
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#define SCREEN_HEIGHT 72
#define SCREEN_WIDTH 240
#define SCORE_TO_WIN 2

struct barrinha{
    int posY;
    int posX;
    char direction; // pode ser Up Down Middle
    struct barrinha *next;

};

struct bola{
    char myRepresentation;
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
    printf("%c", bolinha->myRepresentation);

}


void centerBallandGoLeft( struct bola *bolinha){

    bolinha->posX = 120;
    bolinha->posY = 30;
    bolinha->dirX = 1;
    bolinha-> dirY = 0;
}

void centerBallandGoRight( struct bola *bolinha){

    bolinha->posX = 120;
    bolinha->posY = 30;
    bolinha->dirX = -1;
    bolinha-> dirY = 0;
}

void boogieWoogie( struct bola *bolinha){

    bolinha->posX = 30;
    bolinha->posY = 30;
}



void collisionCheck(struct barrinha *headEsquerda, struct barrinha *headDireita, struct bola *bolinha, int *ponteiroDoScoreP1, int *ponteiroDoScoreP2){
    //so for collisions we have a few options:
    // colliding with paddle 1, paddle 2, upper wall, bottom wall, left goal and right goal

    //(if we're in 4playerMode, we add paddle3, paddle4, left wall, right wall, upper goal and botom goal)

    struct barrinha *imhere = NULL;
    imhere = headEsquerda;
    while(imhere != NULL){

        if ( bolinha->posX == imhere->posX && bolinha->posY == imhere->posY){ // WE GET A PADDLE HIT RIGHT HERE on the leftPaddle

            // which part of the paddle is it? upper part? middlep art? bottom part???
            bolinha->dirX=1; //I reverse the result to go the other way, right?
            if(imhere->direction == 'u') {
                bolinha->dirY = 1; // should go up
            } else if(imhere->direction == 'd') {
                bolinha->dirY = -1; // down
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
                bolinha->dirY = 1; // should go up
            } else if(imhere->direction == 'd') {
                bolinha->dirY = -1; // down
            } else {
                bolinha->dirY = 0; // straight ahead
            }
        }
        imhere = imhere->next;
    }

    //now we need a check to see IF the ball hit the limit of the canvas. If it did so, on the top/bottom, simply bounce back. If it did on the left or right, give score

    if (bolinha->posY == SCREEN_HEIGHT - 13){ // supposedly this means it hit the bottom of the canvas
        bolinha->dirY =  -1;

    }

    if (bolinha->posY == 2){ // supposedly this means it hit the top of the canvas, so I need the final result to be negative SCREEN HEIGHT
        bolinha->dirY =  1;

    }


    //first, scores:

    if (bolinha->posX == SCREEN_WIDTH){ // right side has been hit!!!
        *ponteiroDoScoreP1 = *ponteiroDoScoreP1 + 1;
        screenGotoxy(bolinha->posX, bolinha->posY); // might be next pointer here instead
        printf(" ");
        centerBallandGoLeft(bolinha);
    }


    if (bolinha->posX == 0){
        *ponteiroDoScoreP2 = *ponteiroDoScoreP2 + 1;
        screenGotoxy(bolinha->posX, bolinha->posY); // might be next pointer here instead
        printf(" ");
        centerBallandGoRight(bolinha);
    }

    //what now?,right, teleportation of ball in case we get a score.

    // would be cool to check barrinha head n bottom to move it up/down too, so it doesn't go beyond the limits..



}

// file handle now....
//when game1() starts, open file and read from it. then write when game ends

void debugMode(struct bola *bolinha){
    screenGotoxy(SCREEN_WIDTH/2,SCREEN_HEIGHT/2); // maybe i'm not using the defined values actually
    printf("x: %d y: %d", bolinha->posX, bolinha->posY);

}


//int flag = 0;

//if(flag == 0){
//    changeMyBallPosition(bolinha, -1, -1)
//}


void startMyPaddle(struct barrinha **head, int startingPositionX, int startingPositionY, int height) {
    *head = (struct barrinha *)malloc(sizeof(struct barrinha));
    (*head)->posY = startingPositionY;
    (*head)->posX = startingPositionX;
    (*head)->next = NULL;

    struct barrinha *current = *head;


    for (int i = 1; i < height; i++) {
        struct barrinha *meuNovo = (struct barrinha *)malloc(sizeof(struct barrinha));
        meuNovo->posY = startingPositionY + i; 
        meuNovo->posX = startingPositionX;
       
        if ( height / i > height/2){

            meuNovo->direction = 'd';

        } else if(i == height/2){
            meuNovo->direction = 'm';
        }
        else{
            meuNovo->direction = 'u';
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
        printf("|");
        n = n -> next;
        
    }

}

void showScore(int *p1Score, int *p2Score, char player1Name[50], char player2Name[50], int *flag){

    screenGotoxy(40 ,20);
    printf("%s: %d", player1Name, *p1Score);

    screenGotoxy(180, 20);
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

    screenGotoxy(head->posX, n->posY);
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
    int height = 10;
    startMyPaddle(&myLeftPaddle, 10, 10, height);
    startMyPaddle(&myRightPaddle, 230, 10, height);

    /*Might be cool to turn this entire thing into a bolinha initializer function v*/
    struct bola *bolinha = (struct bola*)malloc(sizeof(struct bola));
    bolinha->posX = 30;
    bolinha->posY = 30;
    bolinha->myRepresentation = 'O';
    bolinha->dirX = 1;
    bolinha->dirY = 0;

    struct bola *next = (struct bola*)malloc(sizeof(struct bola));
    
    next->posX = 30;
    next->posY = 30;
    next->myRepresentation = 'O';
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

            fgets(playerName1Buffer, 100, myLittleBigFile);
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
