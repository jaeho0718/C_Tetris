#include<stdio.h>
#include<Windows.h>

#define SPACE 32
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ESC 27

#define MAP_X 6
#define MAP_Y 7
#define MAP_WIDTH 80
#define MAP_HEIGHT 20

int key;

void title();
void gameover();
void gotoxy(int, int);

int main() {
    title();
    system("cls");
    printf("겜중");
    system("cls");
    gameover();

    return 0;
}


    void title() {
        printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
        printf("■                                                                          ■\n");
        printf("■                                                                          ■\n");
        printf("■    ■■■■■  ■■■■■  ■■■■■  ■■■■■  ■■■  ■■■■■    ■\n");
        printf("■        ■      ■              ■      ■      ■    ■    ■            ■\n");
        printf("■        ■      ■■■■■      ■      ■  ■        ■    ■■■■■    ■\n");
        printf("■        ■      ■              ■      ■    ■      ■            ■    ■\n");
        printf("■        ■      ■■■■■      ■      ■      ■  ■■■  ■■■■■    ■\n");
        printf("■                                                                          ■\n");
        printf("■                                                                          ■\n");
        printf("■                                                                          ■\n");
        printf("■                                                                          ■\n");
        printf("■                                                                          ■\n");
        printf("■                                          project by. LOUIS PLANTER       ■\n");
        printf("■       →,←,↑,↓ : MOVE                             SHIN SEUNGYEON      ■\n");
        printf("■       space bar : ROTATE                             LEE JAEHO           ■\n");
        printf("■       ESC : QUIT                                     LEE SEUNGJONG       ■\n");
        printf("■                                                                          ■\n");
        printf("■                                                                          ■\n");
        printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

        while (1) {
            if (kbhit()) {
                key == getch();
                if (key == ESC) exit(0);
                else break;
            }
            gotoxy(26, 10);
            printf(">>PRESS ANY KEY TO START<<");
        }
    }


    void gameover() {
        system("cls");
        printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
        printf("■                                                                        ■\n");
        printf("■                                                                        ■\n");
        printf("■                                                                        ■\n");
        printf("■          ■■■■■  ■■■■■    ■  ■    ■■■■■                ■\n");
        printf("■          ■          ■      ■  ■  ■  ■  ■                        ■\n");
        printf("■          ■  ■■■  ■■■■■  ■      ■  ■■■■■                ■\n");
        printf("■          ■      ■  ■      ■  ■      ■  ■                        ■\n");
        printf("■          ■■■■■  ■      ■  ■      ■  ■■■■■                ■\n");
        printf("■                                                                        ■\n");
        printf("■                ■■■■■  ■      ■  ■■■■■  ■■■■■          ■\n");
        printf("■                ■      ■  ■      ■  ■          ■      ■          ■\n");
        printf("■                ■      ■  ■      ■  ■■■■■  ■  ■              ■\n");
        printf("■                ■      ■    ■  ■    ■          ■    ■            ■\n");
        printf("■                ■■■■■      ■      ■■■■■  ■      ■          ■\n");
        printf("■                                                                        ■\n");
        printf("■                                                                        ■\n");
        printf("■                                                                        ■\n");
        printf("■                                                                        ■\n");
        printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");

        while (1) {
            if (kbhit()) {
                key == getch();
                if (key == ESC) exit(0);
                else break;
            }
            gotoxy(26, 17);
            printf(">>PRESS ANY KEY TO QUIT<<");
        }
    }


  

    void gotoxy(int x, int y) {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos;
        pos.X = x;
        pos.Y = y;
        SetConsoleCursorPosition(consoleHandle, pos);
    }


