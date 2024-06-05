//gcc -I./include src/*.c  -o pongGame
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#include "nossasFuncoes.h"
#define SCREEN_HEIGHT 48
#define SCREEN_WIDTH 180
#define SCORE_TO_WIN 5
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_BRIGHT_BLUE "\033[1;34m"




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
            printf("%splayer 1 do time VERMELHO:%s teclas %sQ%s e %sA%s ", COLOR_RED, COLOR_RESET, COLOR_RED, COLOR_RESET,COLOR_RED, COLOR_RESET );
            screenGotoxy(26,16);
            printf("Digite o nome do Player 1: \n");
            screenGotoxy(26,17);            
            fgets(player1Name, 50, stdin);
            len = strlen(player1Name);
            player1Name[len - 1] = '\0';


            screenGotoxy(80,15);
            printf("%splayer 2 do time VERMELHO:%s teclas %sG%s e %sB%s ", COLOR_RED, COLOR_RESET, COLOR_RED, COLOR_RESET,COLOR_RED, COLOR_RESET );
            screenGotoxy(80,16);
            printf("Digite o nome do Player 2: \n");
            screenGotoxy(80,17);            
            fgets(player2Name, 50, stdin);
            len = strlen(player2Name);
            player2Name[len - 1] = '\0';

            screenGotoxy(26,20);
            printf("%splayer 1 do time VERDE:%s teclas %sP%s e %sL%s ", COLOR_GREEN, COLOR_RESET, COLOR_GREEN, COLOR_RESET,COLOR_GREEN, COLOR_RESET );
            screenGotoxy(26,21);
            printf("Digite o nome do Player 1: \n");
            screenGotoxy(26,22);            
            fgets(player3Name, 50, stdin);
            len = strlen(player3Name);
            player3Name[len - 1] = '\0';

            screenGotoxy(80,20);
            printf("%splayer 2 do time VERDE:%s teclas %s9%s e %s6%s ", COLOR_GREEN, COLOR_RESET, COLOR_GREEN, COLOR_RESET,COLOR_GREEN, COLOR_RESET );
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
