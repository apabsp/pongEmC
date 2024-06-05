#ifndef __NOSSASFUNCOES_H__
#define __NOSSASFUNCOES_H__

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


void moveBall(struct bola *bolinha);

void centerBallandGoLeft( struct bola *bolinha);

void centerBallandGoRight(struct bola *bolinha);

void collisionCheck(struct barrinha *headEsquerda, struct barrinha *headDireita, struct bola *bolinha, int *ponteiroDoScoreP1, int *ponteiroDoScoreP2);

void collisionCheck2(struct barrinha *headEsquerda, struct barrinha *headDireita, struct barrinha *headEsquerda2, struct barrinha *headDireita2, struct bola *bolinha, int *ponteiroDoScoreP1, int *ponteiroDoScoreP2);

void startMyPaddle(struct barrinha **head, int startingPositionX, int startingPositionY, int height, char color);

void positionMyThing(struct barrinha *head);

void showScore(int *p1Score, int *p2Score, char player1Name[50], char player2Name[50], int *flag);

void showScoreGameMode2(int *team1Score, int *team2Score, char player1Name[50], char player2Name[50], char player3Name[50], char player4Name[50], int *flag);

void modifyMyThing(struct barrinha *head, int newX, int newY, int paddleHeight);

void gameMode1Log(char nome1[50], char nome2[50], int score1, int score2);

void game1(char player1Name[50], char player2Name[50]);

void gameMode2Log(char nome1[50], char nome2[50], char nome3[50], char nome4[50], int score1, int score2);

void game2(char player1Name[50], char player2Name[50], char player3Name[50], char player4Name[50]);

int selectScreen();

void escreverHistoricoDePartidas();

void mostrarInstrucoes();

void lerHistorico();

void clearArrow();

#endif