
#include <string.h>

#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#define SCREEN_HEIGHT 100
#define SCREEN_WIDTH 100
void game1(){

    screenInit(1);
    keyboardInit();
    timerInit(50); //whats this for? dunno
    screenDrawBorders(); // yo if we wanna make this bigger we gotta go on screen.c and change the values or we can just add some parameters

    //posiçao y de inicio:
    int paddle1Y = 10;
    int paddle2Y = 10;
    while (1) {
        screenGotoxy(20, paddle1Y);
        printf("       ");
        screenGotoxy(60, paddle2Y);
        printf("       ");


        if (keyhit()) { // only one key can be pressed at a time? :( mann nooo actually I can just do a buncha checks. if w and s are being pressed, do this.
            int key = readch();
            if (key == 'w' && paddle1Y > 1) {
                paddle1Y--;
            } else if (key == 's' && paddle1Y < SCREEN_HEIGHT - 2) {
                paddle1Y++;
            } else if (key == 'i' && paddle2Y > 1) {
                paddle2Y--;
            } else if (key == 'k' && paddle2Y < SCREEN_HEIGHT - 2) {
                paddle2Y++;
            } else if (key == 27) {
                break;
            }
        }

        screenGotoxy(20, paddle1Y);
        printf("paddle1");
        screenGotoxy(60, paddle2Y);
        printf("paddle2");

        screenUpdate();
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
