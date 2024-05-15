//gcc -I./include src/*.c  -o pongGame
#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#define SCREEN_HEIGHT 72
#define SCREEN_WIDTH 240


struct barrinha{
    int posY;
    struct barrinha *next = NULL;



}

//void add(struct noel *entrada, charboum, char nome, int numero){
//   if(entrada == NULL){
//     entrada = (struct noel)malloc(sizeof(struct noel));
//     strcpy((entrada)->boum, boum);
//     strcpy((entrada)->nome, nome);
//     (entrada)->next = NULL; 
//   }
//   else{
//     struct noeln = entrada;
//     while(n->next != NULL){
//     n = n->next;
//     }

//     n->next = (struct noel) malloc(sizeof(struct noel));
//     strcpy(n->next->boum, boum);
//     strcpy(n->next->nome, nome);
//     n->next->next = NULL;
//   }

void startMyPaddle(struct barrinha *head, int startingPosition, int height){
// ex height 5 
    if (head == NULL){
        head =(struct barrinha)malloc(sizeof(struct barrinha));
        head->posYs = tartingPosition; // QUERO INICIAR MINHA LISTA PELA BARRA DE CIMA
    }
    for (int i = 1; i < height; i++ ){
        struct barrinha *meuNovo = (struct barrinha)malloc(sizeof(struct barrinha));
        head->next = meuNovo;
        head = head->next;

    }


}


void game1(){

    screenInit(1);
    keyboardInit();
    timerInit(100); //whats this for? dunno
    screenDrawBorders(); // yo if we wanna make this bigger we gotta go on screen.c and change the values or we can just add some parameters

    //posiçao y de inicio:
    int paddle1Y = 10;
    int paddle2Y = 10;
    while (1) {
        screenGotoxy(20, paddle1Y);
        printf("       ");
        screenGotoxy(60, paddle2Y);
        printf("       ");
        printf("%d", paddle1Y);

        if (keyhit()) { // only one key can be pressed at a time? :( 
            int key = readch();
            if (key == 'w' && paddle1Y > SCREEN_HEIGHT - 69 ) {
                paddle1Y--;
            } else if (key == 's' && paddle1Y < SCREEN_HEIGHT - 10 ) {
                paddle1Y++;
            } else if (key == 'i' && paddle2Y > 1) {
                paddle2Y--;
            } else if (key == 'k' && paddle2Y < SCREEN_HEIGHT - 2) {
                paddle2Y++;
            } else if (key == 27) {
                break;
            }
        }
// 1: 10 2: 11
        screenGotoxy(10, paddle1Y - 1);
        printf("|");
        screenGotoxy(10, paddle1Y);
        printf("|");
        screenGotoxy(10, paddle1Y + 1);
        printf("|");
        
        screenGotoxy(230, paddle2Y - 1);
        printf("|");
        screenGotoxy(230, paddle2Y);
        printf("|");
        screenGotoxy(230, paddle2Y + 1);
        printf("|");

        screenGotoxy(40, 10);
        printf("o");


        /*for (int i = 0; i < altura; i++) {
            for (int j = 0; j < largura; j++) {
                if (j == 0 || j == largura - 1) {
                    printf("%s█%s", COR_AZUL, COR_RESET);
                } else if ((i == 0 || i == altura - 1) && (j > 0 && j < largura - 1)) {
                    printf("%s█%s", COR_AZUL, COR_RESET);
                } else if (j == 2 && (i >= barraEsquerda - 2 && i <= barraEsquerda + 2)) {
                    printf("█");
                } else if (j == largura - 3 && (i >= barraDireita - 2 && i <= barraDireita + 2)) {
                    printf("█");
                } else if (i == (int)bolaY && j == (int)bolaX) {
                    printf("%s●%s", COR_VERMELHO, COR_RESET);
                } else if (aux == 1 && i == (int)segundaBolaY && j == (int)segundaBolaX) {
                    printf("%s●%s", COR_VERMELHO, COR_RESET);
                } else if (j == largura / 2) {
                    printf("|");
                } else {
                    printf(" ");
                }
            }*/

        screenUpdate();

        screenGotoxy(10, paddle1Y - 1);
        printf(" ");
        screenGotoxy(10, paddle1Y);
        printf(" ");
        screenGotoxy(10, paddle1Y + 1);
        printf(" ");

        screenGotoxy(230, paddle2Y - 1);
        printf(" ");
        screenGotoxy(230, paddle2Y);
        printf(" ");
        screenGotoxy(230, paddle2Y + 1);
        printf(" ");
    }

    //screenGotoxy(20, 10);
    //printf("I");
    //screenGotoxy(60, 10);
    //printf("I"); // ideally we use a char here, since a string might go over the intended pixel value
    //printf('c');
    //while(1){


    //}






}


int main()
{
    int escolha;
    while(1){
        printf("\nOla! Selecione o modo de jogo: \n1- 2 jogadores\n2- 4 jogadores");
        scanf("%d", &escolha);
        if(escolha == 1){
        //startgame1 function
        game1();

        break;
        }
    }
    //so first things first, figure out how to make the border I believe

    return 0;
}
