#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h> 
#include <stdbool.h>

#define SPACE 32
#define LEFT 75
#define RIGHT 77
#define DOWN 80

clock_t startDropT, endT, startGroundT;
int x = 8, y = 0;
RECT blockSize;
int blockForm;
int blockRotation = 0;
int nextBlockRotation = 0;
int key;
int nextBlockForm;
int score = 0;
int delLine = 0;

int block[7][4][4][4] = {
	{ // T모양 블럭
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{0,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{    // 번개 블럭
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{   // 번개 블럭 반대
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		}
	},
	{   // 1자형 블럭
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		}
	},
	{   // L자형 블럭
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{1,0,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,0,0,0}
		}
	},
	{   // L자형 블럭 반대
		{
			{0,0,0,0},
			{0,0,1,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{1,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{1,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		}
	},
	{   // 네모 블럭
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		}
	}
};

int space[15 + 1][10 + 2 + 6] = {  // 세로 15+1(아래벽)칸, 가로 10+2(양쪽 벽)+(다음 블록)칸  
	{1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void Init();
void gotoxy(int x, int y);
void CreateRandomForm();
bool CheckCrash(int x, int y);
void DropBlock();
void BlockToGround();
void RemoveLine();
void DrawMap();
void DrawBlock();
void InputKey();
void NextBlockPrint();
void scoreBoard();
void getScore();

int main() {
	Init();
	startDropT = clock();
	blockForm = rand() % 7; //처음 블록만 생성
	CreateRandomForm();

	while (true) {
		DrawMap();
		DrawBlock();
		NextBlockPrint();
		DropBlock();
		BlockToGround();
		RemoveLine();
		InputKey();
		scoreBoard();
		getScore();

	}
	return 0;
}

void Init() {
	CONSOLE_CURSOR_INFO cursorInfo; //콘솔창에 깜빡이는 하얀색 커서를 없애기 위함
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	srand(time(NULL)); //->깜빡이는 하얀새 커버가 계속 나오지 않도록 함.
}
void gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void CreateRandomForm() {
	nextBlockForm = rand() % 7; //블럭이 내려올 때마다 랜덤으로 바뀌게함.
}
bool CheckCrash(int x, int y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				int t = space[i + y][j + x / 2];
				if (t == 1 || t == 2) { // 벽일 때, 블럭일 때
					return true;
				}
			}
		}
	}
	return false;
}
void DropBlock() {
	endT = clock();
	if ((float)(endT - startDropT) >= 800) {
		if (CheckCrash(x, y + 1) == true) return;
		y++;
		startDropT = clock();
		startGroundT = clock();
		system("cls"); //화면을 지워줌
	}//0.8초마다 블럭을 한칸씩 내림
}
void BlockToGround() {
	if (CheckCrash(x, y + 1) == true) {
		if ((float)(endT - startGroundT) > 1500) {
			// 현재 블록 저장
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (block[blockForm][blockRotation][i][j] == 1) {
						space[i + y][j + x / 2] = 2;
					}
				}
			}
			x = 8;
			y = 0;
			blockForm = nextBlockForm;
			CreateRandomForm();
		}
	}
}
void RemoveLine() {
	for (int i = 15; i >= 0; i--) { // 벽라인 제외한 값
		int cnt = 0;
		for (int j = 1; j < 11; j++) { // 
			if (space[i][j] == 2) {
				cnt++;
			}
		}
		if (cnt >= 10) { // 벽돌이 다 차있다면
			for (int j = 0; i - j >= 0; j++) {
				for (int x = 1; x < 11; x++) {
					if (i - j - 1 >= 0)
						space[i - j][x] = space[i - j - 1][x];
					else {     // 천장이면 0저장
						space[i - j][x] = 0;
					}
				}
			}

			delLine += 100;
		}
	}
	//1줄이되면 블럭을 제거함
}
void DrawMap() {
	gotoxy(0, 0);
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 18; j++) {
			if (space[i][j] == 1) {
				gotoxy(j * 2, i);
				printf("□");
			}
			else if (space[i][j] == 2) {
				gotoxy(j * 2, i);
				printf("■");
			}
		}
	}//맵을 그림
}
void DrawBlock() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				gotoxy(x + j * 2, y + i);
				printf("■");
			}
		}
	}
}
void NextBlockPrint() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[nextBlockForm][nextBlockRotation][i][j] == 1) {
				gotoxy(26 + j * 2, 2 + i);
				printf("■");
			}
		}
	}
	gotoxy(28, 1);
	printf("NEXT");
}
void scoreBoard() {
	gotoxy(27, 8);
	printf("SCORE");
	gotoxy(29, 10);
	printf("%d", score);
}

void getScore() {
	score += delLine;
	delLine = 0;
}
/*
[7] : 7개의 블럭
[4] : 4개의 회전모양
[4] : 세로 모양
[4] : 가로 모양
*/
void InputKey() {
	if (_kbhit()) {
		//kbhit()는 입력을 감지하는 함수임.
		//kbhit()로 입력을 감지하면  getch함수로 입력을 받음
		key = _getch();
		switch (key) {
		case SPACE: // space
			blockRotation++;
			if (blockRotation >= 4) blockRotation = 0;
			startGroundT = clock();
			break;
		case LEFT: // left
			if (CheckCrash(x - 2, y) == false) {
				x -= 2;
				startGroundT = clock();
			}
			break;
		case RIGHT: // right
			if (CheckCrash(x + 2, y) == false) {
				x += 2;
				startGroundT = clock();
			}
			break;
		case DOWN: // down
			if (CheckCrash(x, y + 1) == false)
				y++;
			break;
		}
		system("cls");
	}
}