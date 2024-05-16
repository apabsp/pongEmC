//gcc -I./include src/*.c  -o pongGame
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <stdlib.h>
#define SCREEN_HEIGHT 72
#define SCREEN_WIDTH 240


struct barrinha{
    int posY;
    int posX;
    char direction = 'u' // pode ser Up Down Middle
    struct barrinha *next;
};

struct bola{
    char myRepresentation;
    int posX;
    int posY;
    char dirX;
    char dirY;
};

void changeMyBallPosition(struct bola *bolinha) {
    bolinha->posX += bolinha->dirX;
    bolinha->posY += bolinha->dirY;
}

void checkIfBallTouchesPaddle(struct barrinha *headEsquerda, struct barrinha *headDireita, struct bola bolinha){

    struct barrinha *imhere = NULL;
    imhere = headEsquerda;
    while(imhere != NULL){

        if ( bolinha.posX == imhere->posX && bolinha.posY == imhere->posY){

            bolinha.dirX = imhere->direction;
            bolinha.dirY = 
        }
        x = x->next;
    }

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


void game1(){

    screenInit(1);
    keyboardInit();
    timerInit(100); 
    screenDrawBorders(); 

    
    struct barrinha *myLeftPaddle = NULL;
    struct barrinha *myRightPaddle = NULL;
    int height = 10;
    startMyPaddle(&myLeftPaddle, 10, 10, height);
    startMyPaddle(&myRightPaddle, 230, 10, height);

    while (1) {
        positionMyThing(myLeftPaddle);
        positionMyThing(myRightPaddle);
        
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
    }
    

        
}



int main()
{
    int escolha;
    while(1){
        printf("\nOla! Selecione o modo de jogo: \n1- 2 jogadores\n2- 4 jogadores\n");
        scanf("%d", &escolha);
        if(escolha == 1){
        struct bola bolinha;
        //startgame1 function
        game1();

        break;
        }
    }


    return 0;
}
