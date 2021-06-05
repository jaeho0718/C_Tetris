#include "tetris.hpp"

int space[15 + 1][10 + 2] = {  // 세로 15+1(아래벽)칸, 가로 10+2(양쪽 벽)칸  
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};

clock_t startDropT, endT, startGroundT;
int x = 8, y = 0;
RECT blockSize;
int blockForm; //block 형태 지정
int blockRotation = 0;
int key;
int checkDeleteLine = 0;
bool enableUserAdd = false; //유저가 원하는 블럭 넣을 수 있나.
static int g_nScreenIndex;
static HANDLE g_hScreen[2];

void gotoxy(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], pos);
}

void ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}

void print(const char* string)
{
	DWORD dw;
	WriteFile(g_hScreen[g_nScreenIndex], string, strlen(string), &dw, NULL);
}

void ScreenClear()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 150 * 50, Coor, &dw);
}

void Color(int color) {
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color); //색깔 입히기 위함.
}

void CreateRandomForm(bool noRandomBlock = false) {
	if (noRandomBlock)
		blockForm = rand() % BLOCK_LENGTH - 1;
	else
		blockForm = rand() % BLOCK_LENGTH; //블럭이 내려올 때마다 랜덤으로 바뀌게함.
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
	}//0.8초마다 블럭을 한칸씩 내림
}



void SetBlock(int number) {
	blockForm = number - 49;
	startDropT = clock();
	enableUserAdd = false;
	//사용자가 지정한 블록으로 저장
}

void showBlock() {
	//사용자가 선택할 수 있는 블럭 보여줌
	gotoxy(0, 2);
	int block_x = 0;
	int number_x = 0;

	for (int Block = 0; Block < 7; Block++) {
		gotoxy(block_x, 2);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (block[Block][0][i][j] == 1) {
					gotoxy(block_x + j * 2, 2 + i);
					print("■");
				}
			}
		}
		block_x += 8;
	}

	for (int number = 0; number < 7; number++) {
		gotoxy(number_x + 4, 6);
		char num[2] = { "1" };
		sprintf_s(num, "%d", number + 1);
		print(num);
		number_x += 8;
	}
}

void DrawMap() {
	gotoxy(0, 0);
	Color(8); //Gray
	if (enableUserAdd) {
		ScreenClear();
		print("SELECT BLOCK YOU WANTS. 1~7");
		//Show alert
		showBlock();
	}
	else {
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 12; j++) {
				if (space[i][j] == 1) {
					gotoxy(j * 2, i);
					print("□");
				}
				else if (space[i][j] == 2) {
					gotoxy(j * 2, i);
					print("■");
				}
			}
		}//맵을 그림
	}
}

void SetBlockColor(int Form) {
	switch (Form)
	{
	case 0:
		Color(4); //Red
		break;
	case 1:
		Color(6); //Yellow
		/* code */
		break;
	case 2:
		Color(14); //Light Yellow
		/* code */
		break;
	case 3:
		Color(1); //Blue
		/* code */
		break;
	case 4:
		Color(2); //Green
		/* code */
		break;
	case 5:
		Color(10); //LightGreen
		/* code */
		break;
	case 6:
		Color(3); //AQUA
		/* code */
		break;
	default:
		break;
	}
}


void BlockToGround() {
	if (CheckCrash(x, y + 1) == true) {
		if (blockForm == RANDOM_BLOCK_POS) {
			CreateRandomForm(true);
		}
		else if ((float)(endT - startGroundT) > 1500) {
			// 현재 블록 저장
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (block[blockForm][blockRotation][i][j] == 1) {
						space[i + y][j + x / 2] = 2;
					}
				}
			}
			x = 8;
			y = 0; //초기로 돌아감
			if (!enableUserAdd) {
				CreateRandomForm();
			}
		}
	}
}

void RemoveLine() {
	for (int i = 15; i >= 0; i--) { // 벽라인 제외한 값
		//row 확인용 for loop
		int cnt = 0; //줄에 벽돌이 총 몇개 있는지 확인하기 위한 변수
		for (int j = 1; j < 11; j++) { // 
			//i번째 줄에서 벽돌이 몇개 있는지 확인
			if (space[i][j] == 2) {
				cnt++;
			}
		}
		if (cnt >= 10) { // 벽돌이 다 차있다면
			checkDeleteLine += 1;
			for (int j = 0; i - j >= 0; j++) {
				for (int x = 1; x < 11; x++) {
					if (i - j - 1 >= 0)
						space[i - j][x] = space[i - j - 1][x]; //한줄씩 내림
					else      // 천장이면 0저장
						space[i - j][x] = 0;
				}
			}
		}
	}
	if (checkDeleteLine > 1) {
		//한번에 3줄이 삭제되는지 확인
		startDropT = clock();
		enableUserAdd = true;
	}
	checkDeleteLine = 0;
}

void DrawBlock() {
	SetBlockColor(blockForm);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				gotoxy(x + j * 2, y + i);
				print("■");
			}
		}
	}
	/*
	[7] : 7개의 블럭
	[4] : 4개의 회전모양
	[4] : 세로 모양
	[4] : 가로 모양
	*/
}

void title() {
	while (true) {
		ScreenClear();
		print("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		print("■                                                                          ■\n");
		print("■                                                                          ■\n");
		print("■    ■■■■■  ■■■■■  ■■■■■  ■■■■■  ■■■  ■■■■■    ■\n");
		print("■        ■      ■              ■      ■      ■    ■    ■            ■\n");
		print("■        ■      ■■■■■      ■      ■  ■        ■    ■■■■■    ■\n");
		print("■        ■      ■              ■      ■    ■      ■            ■    ■\n");
		print("■        ■      ■■■■■      ■      ■      ■  ■■■  ■■■■■    ■\n");
		print("■                                                                          ■\n");
		print("■                                                                          ■\n");
		print("■                        >>PRESS ANY KEY TO START<<                        ■\n");
		print("■                                                                          ■\n");
		print("■                                                                          ■\n");
		print("■                                          project by. LOUIS PLANCHER      ■\n");
		print("■       →,←,↑,↓ : MOVE                         SHIN SEUNGYEON      ■\n");
		print("■       space bar : ROTATE                             LEE JAEHO           ■\n");
		print("■       ESC : QUIT                                     LEE SEUNGJONG       ■\n");
		print("■                                                                          ■\n");
		print("■                                                                          ■\n");
		print("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		if (_kbhit()) {
			int key_menu = _getch();
			if (key_menu == ESC) exit(0);
			else break;
		}
		ScreenFlipping();
	}
}

void gameover() {
	while (true) {
		ScreenClear();
		print("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		print("■                                                                        ■\n");
		print("■                                                                        ■\n");
		print("■                                                                        ■\n");
		print("■          ■■■■■  ■■■■■    ■  ■    ■■■■■                ■\n");
		print("■          ■          ■      ■  ■  ■  ■  ■                        ■\n");
		print("■          ■  ■■■  ■■■■■  ■      ■  ■■■■■                ■\n");
		print("■          ■      ■  ■      ■  ■      ■  ■                        ■\n");
		print("■          ■■■■■  ■      ■  ■      ■  ■■■■■                ■\n");
		print("■                                                                        ■\n");
		print("■                ■■■■■  ■      ■  ■■■■■  ■■■■■          ■\n");
		print("■                ■      ■  ■      ■  ■          ■      ■          ■\n");
		print("■                ■      ■  ■      ■  ■■■■■  ■  ■              ■\n");
		print("■                ■      ■    ■  ■    ■          ■    ■            ■\n");
		print("■                ■■■■■      ■      ■■■■■  ■      ■          ■\n");
		print("■                                                                        ■\n");
		print("■                                                                        ■\n");
		print("■                      >>PRESS ANY KEY TO QUIT<<                         ■\n");
		print("■                                                                        ■\n");
		print("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		if (_kbhit()) {
			int key_menu = _getch();
			if (key_menu == ESC) exit(0);
			else break;
		}
		ScreenFlipping();
	}
}

void InitGame() {
	CONSOLE_CURSOR_INFO cursorInfo; //콘솔창에 깜빡이는 하얀색 커서를 없애기 위함
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleCursorInfo(g_hScreen[0], &cursorInfo);
	SetConsoleCursorInfo(g_hScreen[1], &cursorInfo);
	srand(time(NULL)); //->깜빡이는 하얀새 커버가 계속 나오지 않도록 함.
}

void InputKey() {
	if (_kbhit()) {
		//kbhit()는 입력을 감지하는 함수임.
		//kbhit()로 입력을 감지하면  getch함수로 입력을 받음
		key = _getch();

		if (enableUserAdd) {
			//사용자가 블럭을 지정받을 수 있다면
			switch (key)
			{
			case NUMBER1:
				SetBlock(NUMBER1);
				break;
			case NUMBER2:
				SetBlock(NUMBER2);
				break;
			case NUMBER3:
				SetBlock(NUMBER3);
				break;
			case NUMBER4:
				SetBlock(NUMBER4);
				break;
			case NUMBER5:
				SetBlock(NUMBER5);
				break;
			case NUMBER6:
				SetBlock(NUMBER6);
				break;
			}

		}
		else {
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
		}
	}
}

int launch_game() {
	startDropT = clock();
	CreateRandomForm();

	while (true) {
		ScreenClear();
		DrawMap();
		if (!enableUserAdd) {
			//If 2Lines Delete, Until User select block , game is stop.
			DrawBlock();
			DropBlock();
			BlockToGround();
			RemoveLine();
		}
		InputKey();
		ScreenFlipping();
	}
	return 0;
}

int main() {
	InitGame();
	title();
	launch_game();
	gameover();
	return 0;
}