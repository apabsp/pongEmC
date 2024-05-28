//gcc -I./include src/*.c  -o pongGame
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#define SCREEN_HEIGHT 48
#define SCREEN_WIDTH 180
#define SCORE_TO_WIN 2
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_BRIGHT_BLUE "\033[1;34m"


struct barrinha{
    int posY;
    int posX;
    char direction;
    char representationAndColor[30];
    struct barrinha *next;

};

struct bola{
    char myRepresentation[30];
    int posX; 
    int posY; 
    int dirX;
    int dirY;
     //Interesting thing about this is that we want to continuously be deleting the head and then filling in the *next
};

struct ballDirection{

    int dirX;
    int dirY;
};


void moveBall(struct bola *bolinha) {
    
    screenGotoxy(bolinha->posX, bolinha->posY);
    printf(" "); // aqui vou apagando o trail da bola
    
    
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

void centerBallandGoRight(struct bola *bolinha){

    bolinha->posX = SCREEN_WIDTH/2;
    bolinha->posY = SCREEN_HEIGHT/2;
    bolinha->dirX = 1;
    bolinha-> dirY = 0;
}

void collisionCheck(struct barrinha *headEsquerda, struct barrinha *headDireita, struct bola *bolinha, int *ponteiroDoScoreP1, int *ponteiroDoScoreP2){
  struct barrinha *imhere = NULL;

    //COLISAO DOS PADDLES COM A BOLA
    imhere = headEsquerda;
    while(imhere != NULL){
        
        if ( bolinha->posX == imhere->posX && bolinha->posY == imhere->posY){ // Colisao de bola com paddle

            // which part of the paddle is it? upper part? middlep art? bottom part???
            bolinha->dirX=1; //I reverse the result so the ball goes the other way
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

    if (bolinha->posY <= 2){ // supposedly this means it hit the top of the canvas
        
        bolinha->dirY =  1;
    }

    if (bolinha->posY >= SCREEN_HEIGHT - 1){ // hit the bottom of the canvas

        bolinha->dirY =  -1;
    }
    //first, scores:

    if (bolinha->posX >= SCREEN_WIDTH - 2){ // right side has been hit!!!
        *ponteiroDoScoreP1 = *ponteiroDoScoreP1 + 1;
        screenGotoxy(bolinha->posX, bolinha->posY); // might be next pointer here instead
        printf(" │");
        centerBallandGoRight(bolinha);
    }

    if (bolinha->posX <= 1){ // left side has been hit!!!
        *ponteiroDoScoreP2 = *ponteiroDoScoreP2 + 1;
        screenGotoxy(bolinha->posX, bolinha->posY); // might be next pointer here instead
        printf("│");
        centerBallandGoLeft(bolinha);
    }

}

void collisionCheck2(struct barrinha *headEsquerda, struct barrinha *headDireita, struct barrinha *headEsquerda2, struct barrinha *headDireita2, struct bola *bolinha, int *ponteiroDoScoreP1, int *ponteiroDoScoreP2){
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

    imhere = headEsquerda2;
    while(imhere != NULL){

        if ( bolinha->posX == imhere->posX && bolinha->posY == imhere->posY){ // WE GET A PADDLE HIT RIGHT HERE on the leftPaddle


            if(bolinha->dirX =-1){ // this means that paddle 2 hits paddle 1's ball. We want to send it back
                bolinha->dirX=1;
            } // friendly-fire mechanism basically. this is our game's plan. we Want to incentivize chaos among teammates.
            else{
            bolinha->dirX=1;
            } 


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

    imhere = headDireita2;
    while(imhere != NULL){

        if ( bolinha->posX == imhere->posX && bolinha->posY == imhere->posY){ // WE GET A PADDLE HIT RIGHT HERE on the rightPaddle
            
            
            if(bolinha->dirX =1){
                bolinha->dirX = -1;
            }
            else{
                bolinha->dirX=1;
            }
            
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

    if (bolinha->posY <= 2){ // supposedly this means it hit the top of the canvas
        bolinha->dirY =  1;
        
        screenGotoxy(0, 0);
        printf("┌");
        for(int i = 0; i < SCREEN_WIDTH-3; i++){
            printf("─");
        };
        printf("┐");
        
    }

    if (bolinha->posY >= SCREEN_HEIGHT - 1){ // hit the bottom of the canvas
        screenGotoxy(0, SCREEN_HEIGHT);
        printf("└"); //┐  ┘ └   Reconstruct the entire wall as soon as there's contact
        for(int i = 0; i < SCREEN_WIDTH-3; i++){
            printf("─");
        };
        printf("┘");
        bolinha->dirY =  1;
        bolinha->dirY =  -1;   
    }
    //first, scores:

    if (bolinha->posX >= SCREEN_WIDTH - 2){ // right side has been hit!!!
        *ponteiroDoScoreP1 = *ponteiroDoScoreP1 + 1;
        screenGotoxy(bolinha->posX, bolinha->posY); // might be next pointer here instead
        printf(" │");
        centerBallandGoRight(bolinha);
    }

    if (bolinha->posX <= 1){ // left side has been hit!!!
        *ponteiroDoScoreP2 = *ponteiroDoScoreP2 + 1;
        screenGotoxy(bolinha->posX, bolinha->posY); // might be next pointer here instead
        printf("│");
        centerBallandGoLeft(bolinha);
    }
}

void startMyPaddle(struct barrinha **head, int startingPositionX, int startingPositionY, int height, char color) { // recommended height is 6
    *head = (struct barrinha *)malloc(sizeof(struct barrinha));
    (*head)->posY = startingPositionY;
    (*head)->posX = startingPositionX;
    if (color == 'g'){
        strcpy((*head)->representationAndColor, COLOR_GREEN "█" COLOR_RESET);
    }
    else if (color == 'r'){
        strcpy((*head)->representationAndColor, COLOR_RED "█" COLOR_RESET);
    }
    (*head)->next = NULL;

    struct barrinha *current = *head;
    current->direction = 'u';

    for (int i = 1; i < height; i++) {
        struct barrinha *meuNovo = (struct barrinha *)malloc(sizeof(struct barrinha));
        meuNovo->posY = startingPositionY + i; 
        meuNovo->posX = startingPositionX;


        if (color == 'g'){
        strcpy(current->representationAndColor, COLOR_GREEN "█" COLOR_RESET);
        }
        else if (color == 'r'){
        strcpy(current->representationAndColor, COLOR_RED "█" COLOR_RESET);
        }
       
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
        printf("%s", n->representationAndColor);
        n = n -> next;
    }
}

void showScore(int *p1Score, int *p2Score, char player1Name[50], char player2Name[50], int *flag){

    screenGotoxy(50 ,10);
    printf("%s: %d", player1Name, *p1Score);

    screenGotoxy(SCREEN_WIDTH-50, 10);
    printf("%s: %d", player2Name, *p2Score);

    if(*p1Score  >= SCORE_TO_WIN){
        *flag = 1;
        timerInit(3000); // 3 SEGUNDOS DE WAIT TIME
        screenGotoxy(25,5);

        while (!timerTimeOver()) {
                screenGotoxy(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
                printf("%s%s WINS!!!%s", COLOR_RED, player1Name, COLOR_RESET);
        }
    }
    if(*p2Score  >= SCORE_TO_WIN){
        *flag = 1;
        timerInit(3000);
        screenGotoxy(25,5);

        while (!timerTimeOver()) {
                screenGotoxy(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
                printf("%s%s WINS!!!%s", COLOR_GREEN, player2Name, COLOR_RESET);
        }
    }
}

void showScoreGameMode2(int *team1Score, int *team2Score, char player1Name[50], char player2Name[50], char player3Name[50], char player4Name[50], int *flag){

    screenGotoxy(50 ,10);
    printf("%s & %s: %d", player1Name, player2Name, *team1Score);

    screenGotoxy(SCREEN_WIDTH-50, 10);
    printf("%s & %s : %d", player3Name, player4Name, *team2Score);

    if(*team1Score  >= SCORE_TO_WIN){
        *flag = 1;
        timerInit(3000); // 3 SEGUNDOS DE WAIT TIME
        screenGotoxy(25,5);

        while (!timerTimeOver()) {
                screenGotoxy(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
                printf("%s%s & %s WINS!!!%s", COLOR_RED, player1Name, player2Name, COLOR_RESET);
        }
    }
    if(*team2Score  >= SCORE_TO_WIN){
        *flag = 1;
        timerInit(3000);
        screenGotoxy(25,5);

        while (!timerTimeOver()) {
                screenGotoxy(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
                printf("%s%s & %s WINS!!!%s", COLOR_GREEN, player3Name, player4Name, COLOR_RESET);
        }
    }
}

void modifyMyThing(struct barrinha *head, int newX, int newY, int paddleHeight){
    struct barrinha *n = head;
    
    // checa se paddle vai tocar no top ou bottom
    if (head->posY + newY <= 1 || head->posY + newY + paddleHeight >= SCREEN_HEIGHT + 1) {
        return; // esse return e necessario para terminar a funcao em casos onde o if eh vdd
    }

    //limpa a posicao do paddle continuamente, caso possa se mover
    while (n != NULL) {
        screenGotoxy(n->posX, n->posY);
        printf(" ");
        n = n->next;
    }

    n = head;
    while (n != NULL) {
        n->posY += newY;
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
    timerInit(15); 
    
    struct barrinha *myLeftPaddle = NULL;
    struct barrinha *myRightPaddle = NULL;
    int height = 6;
    startMyPaddle(&myLeftPaddle, 5, SCREEN_HEIGHT/2, height, 'r'); // remember, this initializes where THE HEAD starts. So the spawn isn't centered. intentional.
    startMyPaddle(&myRightPaddle, SCREEN_WIDTH - 5, SCREEN_HEIGHT/2, height, 'g');

    struct bola *bolinha = (struct bola*)malloc(sizeof(struct bola));
    strcpy(bolinha->myRepresentation,"🏐");
    centerBallandGoRight(bolinha);
    
    int scoredo1 = 0;
    int scoredo2 = 0;
    int *p1Score = &scoredo1;
    int *p2Score = &scoredo2;
    int flagForGameOver = 0; 
    
    while (flagForGameOver == 0) {
        
        showScore(p1Score, p2Score, player1Name, player2Name, &flagForGameOver);

        if (timerTimeOver()) {
            positionMyThing(myLeftPaddle);
            positionMyThing(myRightPaddle);

            collisionCheck(myLeftPaddle, myRightPaddle, bolinha, p1Score, p2Score);
            moveBall(bolinha);
            if (keyhit()) {
                int key = readch();
                if (key == 'q'){
                    modifyMyThing(myLeftPaddle, 0, -1, height);
                }
                else if (key == 'a'){
                    modifyMyThing(myLeftPaddle, 0, 1, height);
                }
                else if (key == 'p'){
                    modifyMyThing(myRightPaddle, 0, -1, height);
                }
                else if (key == 'l'){
                    modifyMyThing(myRightPaddle, 0, 1, height);
                } 
            }
        }
    }
    
    gameMode1Log(player1Name, player2Name, scoredo1, scoredo2);
    screenClear();
    keyboardDestroy();
    free(bolinha);
}

void gameMode2Log(char nome1[50], char nome2[50], char nome3[50], char nome4[50], int score1, int score2){
        FILE *game;
        game = fopen("gameMode2.txt", "a");

        fprintf(game, "%s\n%s\n%s\n%s\n%d %d\n", nome1, nome2, nome3, nome4, score1, score2);
        fclose(game);
 }

void game2(char player1Name[50], char player2Name[50], char player3Name[50], char player4Name[50]){

    screenInit(1);
    keyboardInit();
    timerInit(25); 
    screenDrawBorders(); 

    
    struct barrinha *myLeftPaddle1 = NULL;
    struct barrinha *myLeftPaddle2 = NULL;
    struct barrinha *myRightPaddle1 = NULL;
    struct barrinha *myRightPaddle2 = NULL;
    int height = 10;
    startMyPaddle(&myLeftPaddle1, 5, SCREEN_HEIGHT/2, height, 'r'); // remember, this initializes where THE HEAD starts. So the spawn isn't centered. intentional.
    startMyPaddle(&myLeftPaddle2, 25, SCREEN_HEIGHT/2, height, 'r'); 
    startMyPaddle(&myRightPaddle1, SCREEN_WIDTH - 5, SCREEN_HEIGHT/2, height, 'g');
    startMyPaddle(&myRightPaddle2, SCREEN_WIDTH - 25, SCREEN_HEIGHT/2, height, 'g');

    struct bola *bolinha = (struct bola*)malloc(sizeof(struct bola));
    strcpy(bolinha->myRepresentation,"🏐");
    
    centerBallandGoLeft(bolinha);
    
    int scoredo1 = 0;
    int scoredo2 = 0;
    int *p1Score = &scoredo1;
    int *p2Score = &scoredo2;
    int flagForGameOver = 0; 

    while (flagForGameOver == 0) {
        
        showScoreGameMode2(p1Score, p2Score, player1Name, player2Name, player3Name, player4Name, &flagForGameOver);

        if (timerTimeOver()) {
            positionMyThing(myLeftPaddle1);
            positionMyThing(myRightPaddle1);
            positionMyThing(myLeftPaddle2);
            positionMyThing(myRightPaddle2);
            collisionCheck2(myLeftPaddle1, myRightPaddle1, myLeftPaddle2, myRightPaddle2, bolinha, p1Score, p2Score);
            moveBall(bolinha); 
            if (keyhit()) {
                int key = readch();
                if (key == 'q'){
                    modifyMyThing(myLeftPaddle1, 0, -1, height);
                }
                else if (key == 'a'){
                    modifyMyThing(myLeftPaddle1, 0, 1, height);
                }
                else if (key == 'g'){
                    modifyMyThing(myLeftPaddle2, 0, -1, height);
                }
                else if (key == 'b'){
                    modifyMyThing(myLeftPaddle2, 0, 1, height);
                }

                else if (key == 'p'){
                    modifyMyThing(myRightPaddle2, 0, -1, height);
                }
                else if (key == 'l'){
                    modifyMyThing(myRightPaddle2, 0, 1, height);
                }

                else if (key == '9'){
                    modifyMyThing(myRightPaddle1, 0, -1, height);
                }
                else if (key == '6'){
                    modifyMyThing(myRightPaddle1, 0, 1, height);
                }
                
            }
        }

    }
    
    gameMode2Log(player1Name, player2Name, player3Name, player4Name, scoredo1, scoredo2);
    keyboardDestroy();
    screenClear();
    free(bolinha);
}

int selectScreen(){

    screenInit(1);
    keyboardInit();
    struct nodeMenuOption{
        int coordenadaYDoMenu; 
        struct nodeMenuOption *next;
        struct nodeMenuOption *previous;
    };

    void clearArrow(){
        screenGotoxy(42,20);       
        printf(" ");
        screenGotoxy(42,21);       
        printf(" ");
        screenGotoxy(42,22);       
        printf(" ");
        screenGotoxy(42,23);       
        printf(" ");
        screenGotoxy(42,24);       
        printf(" ");        
    }

    struct nodeMenuOption opcoes[4]; // temos 4 opçoes no menu por enquanto
    opcoes[0].coordenadaYDoMenu = 20;
    opcoes[0].previous = NULL;
    opcoes[0].next = &opcoes[1];

    opcoes[1].coordenadaYDoMenu = 21;
    opcoes[1].previous = &opcoes[0];
    opcoes[1].next = &opcoes[2];

    opcoes[2].coordenadaYDoMenu = 22;
    opcoes[2].previous = &opcoes[1];
    opcoes[2].next = &opcoes[3];

    opcoes[3].coordenadaYDoMenu = 23;
    opcoes[3].previous = &opcoes[2];
    opcoes[3].next = NULL;

    screenGotoxy(45, 10);
    printf("%s  _____   ____  _   _  _____     %s %s   __  __           _____ _______ ______ _____   _____ %s\n", COLOR_RED, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
    screenGotoxy(45, 11);
    printf("%s |  __ \\ / __ \\| \\ | |/ ____| %s %s     |  \\/  |   /\\    / ____|__   __|  ____|  __ \\ / ____|%s\n", COLOR_RED, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
    screenGotoxy(45, 12);
    printf("%s | |__) | |  | |  \\| | |  __     %s %s  | \\  / |  /  \\  | (___    | |  | |__  | |__) | (___  %s\n", COLOR_RED, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
    screenGotoxy(45, 13);
    printf("%s |  ___/| |  | | . ` | | |_ |     %s %s | |\\/| | / /\\ \\  \\___ \\   | |  |  __| |  _  / \\___ \\ %s\n", COLOR_RED, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
    screenGotoxy(45, 14);
    printf("%s | |    | |__| | |\\  | |__| |    %s %s  | |  | |/ ____ \\ ____) |  | |  | |____| | \\ \\ ____) |%s\n", COLOR_RED, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
    screenGotoxy(45, 15);
    printf("%s |_|     \\____/|_| \\_|\\_____|  %s %s    |_|  |_/_/    \\_\\_____/   |_|  |______|_|  \\_\\_____/%s feito em C\n", COLOR_RED, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
    screenGotoxy(50, 16);
    printf("por ANTONIO PAULO BARROS, HELOISA TANAKA, RAFAELA VIDAL\n");
    
    screenGotoxy(45, 20);
    printf("1 - Instruçoes\n");
    screenGotoxy(45, 21);
    printf("2 - %sPARTIDA 1 vs 1%s\n", COLOR_RED, COLOR_RESET);
    screenGotoxy(45, 22);
    printf("3 - %sPARTIDA 2 vs 2%s\n", COLOR_GREEN, COLOR_RESET);
    screenGotoxy(45, 23);
    printf("4 - %sVisualizar historico%s\n", COLOR_RED, COLOR_RESET);

    screenGotoxy(45, 25);
    printf("Controle nesse menu:\n");
    screenGotoxy(45, 26);
    printf(" W S Enter\n");

    struct nodeMenuOption *wherePlayerIs;
    wherePlayerIs = &opcoes[0];

    while(1){
    
        if(keyhit()){
            int key = readch();
            if(key == '\n'){
                screenClear();
                keyboardDestroy();
                if(wherePlayerIs->coordenadaYDoMenu == 20){
                    return 1; 
                }
                else if(wherePlayerIs->coordenadaYDoMenu == 21){
                    return 2;
                }
                else if(wherePlayerIs->coordenadaYDoMenu == 22){
                    return 3;
                }
                else if(wherePlayerIs->coordenadaYDoMenu == 23){
                    return 4;
                }
                
            }
            else if( key == 's'){
                if (wherePlayerIs->next != NULL){
                    clearArrow();
                    wherePlayerIs = wherePlayerIs->next;
                }

            }
            else if( key == 'w'){
                if (wherePlayerIs->previous != NULL){
                    clearArrow();
                    wherePlayerIs = wherePlayerIs->previous;
                }
            }

        }
        screenGotoxy(42,wherePlayerIs->coordenadaYDoMenu);
        printf("%s➡️%s", COLOR_BLUE, COLOR_RESET);
    }

}

void escreverHistoricoDePartidas() {
    FILE *game1 = fopen("gameMode1.txt", "r");
    FILE *game2 = fopen("gameMode2.txt", "r");
    FILE *historico;

    if (game1 == NULL && game2 == NULL) {
        printf("Não há histórico!\n");
        return;
    }

    historico = fopen("historico.txt", "w");

    if (game1 != NULL) {
        while(!feof(game1)){
            char playerName1Buffer[100], playerName2Buffer[100];
            int score1, score2, len;

            if(fgets(playerName1Buffer, 100, game1) == NULL){
                break;
            };
            len = strlen(playerName1Buffer);
            playerName1Buffer[len - 1] = '\0';

            fgets(playerName2Buffer,100, game1);
            len = strlen(playerName2Buffer);
            playerName2Buffer[len - 1] = '\0';

            fscanf(game1, "%d %d", &score1, &score2);

            fprintf(historico, "%s vs %s (%d - %d)\n", playerName1Buffer, playerName2Buffer, score1, score2);

            fgetc(game1);
        }
        fclose(game1);
    }

    if (game2 != NULL) {
        while(!feof(game2)){
            char playerName1Buffer[100], playerName2Buffer[100], playerName3Buffer[100], playerName4Buffer[100];
            int score1, score2, len;

            if(fgets(playerName1Buffer, 100, game2) == NULL){
                break;
            };
            len = strlen(playerName1Buffer);
            playerName1Buffer[len - 1] = '\0';

            fgets(playerName2Buffer,100, game2);
            len = strlen(playerName2Buffer);
            playerName2Buffer[len - 1] = '\0';

            fgets(playerName3Buffer,100, game2);
            len = strlen(playerName3Buffer);
            playerName3Buffer[len - 1] = '\0';

            fgets(playerName4Buffer,100, game2);
            len = strlen(playerName4Buffer);
            playerName4Buffer[len - 1] = '\0';

            fscanf(game2, "%d %d", &score1, &score2);

            fprintf(historico, "%s & %s vs %s & %s (%d - %d)\n", playerName1Buffer, playerName2Buffer, playerName3Buffer, playerName4Buffer, score1, score2);

            fgetc(game2);
        }
        fclose(game2);
    }

    fclose(historico);
    

}

void mostrarInstrucoes(){

    screenGotoxy(30,10);
    printf("Instruç~oes: ");
    screenGotoxy(26,11);
    printf("%splayer 1 do time Vermelho:%s teclas Q e A ", COLOR_RED, COLOR_RESET);
    screenGotoxy(26,12);
    printf("%splayer 2 do time Vermelho:%s teclas G e B ", COLOR_RED, COLOR_RESET);
    screenGotoxy(26,13);
    printf("%splayer 1 do time Verde:%s teclas P e L ", COLOR_GREEN, COLOR_RESET);
    screenGotoxy(26,14);
    printf("%splayer 2 do time Verde:%s teclas 9 e 6 ", COLOR_GREEN, COLOR_RESET);

    screenGotoxy(20, 3);
    printf("Aperte ENTER para sair dessa tela.\n");
    keyboardInit();
    while(1){
        
        if(keyhit()){
            int key = readch();
            if(key == '\n'){
                break;
            }
        }
    }
    keyboardDestroy();
}

void lerHistorico(){
    FILE *arquivo;
    char linha[256];
    arquivo = fopen("historico.txt", "r");

    if (arquivo == NULL) {
        timerInit(3000);
        while(!timerTimeOver()){
            screenGotoxy(SCREEN_WIDTH/2, SCREEN_HEIGHT);
            printf("Nenhum arquivo historico.txt encontrado");
        }
        return;
    }

    screenGotoxy(20, 3);
    printf("Aperte ENTER para sair dessa tela.\n");
    int counter = 5;
    while (fgets(linha, sizeof(linha), arquivo)) {
        screenGotoxy(20, counter);
        printf("%s", linha);
        counter++;
    }
    keyboardInit();
    while(1){
            if (keyhit()) {
                int key = readch();
                if(key == '\n'){
                    break;
                }    
            }
        }
    keyboardDestroy();
    fclose(arquivo);
    
}


int main()
{
    int escolha, len;
    escreverHistoricoDePartidas();
    char player1Name[50], player2Name[50], player3Name[50], player4Name[50];
    struct bola bolinha;
    while(1){
        
        escolha = selectScreen();

        if(escolha == 1){
            mostrarInstrucoes();
        }else if(escolha == 2){
            
            screenGotoxy(30,10);
            printf("You have selected Game Mode 1:\n");
            screenGotoxy(30,11);
            printf("1 vs 1\n");


            screenGotoxy(26,15);
            printf("%splayer 1:%s teclas %sQ%s e %sE%s ", COLOR_RED, COLOR_RESET, COLOR_RED, COLOR_RESET,COLOR_RED, COLOR_RESET );
            screenGotoxy(26,16);
            printf("Digite o nome do Player 1: \n");
            screenGotoxy(26,17);            
            fgets(player1Name, 50, stdin);
            len = strlen(player1Name);
            player1Name[len - 1] = '\0';
            
            screenGotoxy(26,20);
            printf("%splayer 2:%s teclas %sP%s e %sL%s ", COLOR_GREEN, COLOR_RESET, COLOR_GREEN, COLOR_RESET, COLOR_GREEN, COLOR_RESET);
            screenGotoxy(26,21);
            printf("Digite o nome do Player 2: \n");
            screenGotoxy(26,22);            
            fgets(player2Name, 50, stdin);
            len = strlen(player2Name);
            player2Name[len - 1] = '\0';

            game1(player1Name,player2Name);
            keyboardDestroy();

        }

        else if(escolha == 3){
            
            screenGotoxy(30,10);
            printf("You have selected Game Mode 2:\n");
            screenGotoxy(30,11);
            printf("2 vs 2\n");

            
            screenGotoxy(26,15);
            printf("%splayer 1 do time VERMELHO:%s teclas %sQ%s e %sE%s ", COLOR_RED, COLOR_RESET, COLOR_RED, COLOR_RESET,COLOR_RED, COLOR_RESET );
            screenGotoxy(26,16);
            printf("Digite o nome do Player 1: \n");
            screenGotoxy(26,17);            
            fgets(player1Name, 50, stdin);
            len = strlen(player1Name);
            player1Name[len - 1] = '\0';


            screenGotoxy(80,15);
            printf("%splayer 2 do time VERMELHO:%s teclas %sQ%s e %sE%s ", COLOR_RED, COLOR_RESET, COLOR_RED, COLOR_RESET,COLOR_RED, COLOR_RESET );
            screenGotoxy(80,16);
            printf("Digite o nome do Player 2: \n");
            screenGotoxy(80,17);            
            fgets(player2Name, 50, stdin);
            len = strlen(player2Name);
            player2Name[len - 1] = '\0';

            screenGotoxy(26,20);
            printf("%splayer 1 do time VERDE:%s teclas %sQ%s e %sE%s ", COLOR_GREEN, COLOR_RESET, COLOR_GREEN, COLOR_RESET,COLOR_GREEN, COLOR_RESET );
            screenGotoxy(26,21);
            printf("Digite o nome do Player 1: \n");
            screenGotoxy(26,22);            
            fgets(player3Name, 50, stdin);
            len = strlen(player3Name);
            player3Name[len - 1] = '\0';

            screenGotoxy(80,20);
            printf("%splayer 2 do time VERDE:%s teclas %sQ%s e %sE%s ", COLOR_GREEN, COLOR_RESET, COLOR_GREEN, COLOR_RESET,COLOR_GREEN, COLOR_RESET );
            screenGotoxy(80,21);
            printf("Digite o nome do Player 2: \n");
            screenGotoxy(80,22);            
            fgets(player4Name, 50, stdin);
            len = strlen(player4Name);
            player4Name[len - 1] = '\0';
            

            
            screenClear();
            game2(player1Name, player2Name, player3Name, player4Name);
            keyboardDestroy();
        }
        else if(escolha == 4){
            lerHistorico();
        }

        escreverHistoricoDePartidas();
    }
    return 0;
}
