#pragma warning(disable:4996)
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "blocklist.h"
#include "fps_limit.h"//限制帧率
using namespace std;
int canvas[20][10] = {0};//将已经落下的方块标记为1，正在下落的方块标记为2
Block* fallingblock=NULL;//下落方块
static int canleft;
static int canright;
static int score = 0;//分数
static int speedindex = 60;//衡量下落方块速度快慢的因子（越大越慢，可以用于调节难度）
static int speed(speedindex / 2);
void gotoxy(int x, int y)  //光标移动到(x,y)位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void startupgame() {
	SetConsoleTitle(L"苏维埃方块 by Bx");//设置控制台窗口标题
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT rc = { 0,0, 20, 22 }; // 坐标位置结构体初始化
	SetConsoleWindowInfo(handle, true, &rc);//设置控制台窗口大小
	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };
	SetConsoleCursorInfo(handle, &cursorInfo);//隐藏控制台光标
	cout << "--Soviet Blocks--" << endl;
	cout << "Start Z" << endl;
	cout << "Quit  A" << endl;
	cout << endl << "#Help#" << endl << "Move:←→" << endl << "Rotate:↑" << endl<<"Speed up:↓"<<endl;
	char x=_getch();
	while (x != 'Z'&&x!='z') {
		if (x == 'A'||x=='a')exit(0);
		x = _getch();
	}
	system("cls");
}
void show() {
	gotoxy(0, 0);
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (canvas[i][j] == 0)
				cout << " ";
			if (canvas[i][j]==1)
				cout << "#";
			if (canvas[i][j] == 2)
				cout << "#";
		}
		cout << "|" << endl;
	}
	cout << "-----------" << endl;
	cout << "Score:" << score << endl;
}
void updatewithoutinput() {
	if (speed < speedindex) speed++;
	else {
		int dofallingsexist = 0;//场上是否存在下落方块
		for (int j = 0; j < 10; j++) {//检测全场是否有下落方块
			for (int i = 0; i < 20; i++) {
				if (canvas[i][j] == 2) {//发现下落方块
					dofallingsexist = 1;
					break;
				}
			}
		}
		if (!dofallingsexist) {//加入新方块（待改）
			//canvas[0][rand() % 10] = 2;
			srand(time(NULL));
			switch (1 + rand() % 7)
			{
			case 1:
				fallingblock = new I(0, rand() % 10, rand() % 4);
				break;
			case 2:
				fallingblock = new J(0, rand() % 10, rand() % 4);
				break;
			case 3:
				fallingblock = new L(0, rand() % 10, rand() % 4);
				break;
			case 4:
				fallingblock = new O(0, rand() % 10, rand() % 4);
				break;
			case 5:
				fallingblock = new S(0, rand() % 10, rand() % 4);
				break;
			case 6:
				fallingblock = new Z(0, rand() % 10, rand() % 4);
				break;
			case 7:
				fallingblock = new T(0, rand() % 10, rand() % 4);
				break;
			default:
				break;
			}
		}
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 10; j++) {
				if (i == fallingblock->b0x && j == fallingblock->b0y) canvas[i][j] = 2;
				else if (i == fallingblock->b1x && j == fallingblock->b1y) canvas[i][j] = 2;
				else if (i == fallingblock->b2x && j == fallingblock->b2y) canvas[i][j] = 2;
				else if (i == fallingblock->b3x && j == fallingblock->b3y) canvas[i][j] = 2;
				else if (canvas[i][j] != 1) canvas[i][j] = 0;
			}
		}//标记场地
		int bottomfalling[10] = { 0 };//每一列最下方的正在下落方块的行坐标
		for (int j = 0; j < 10; j++) {//记录每一列最下面的下落方块的行位置
			for (int i = 0; i < 20; i++) {
				if (canvas[i][j] == 2 && (i < 19 && canvas[i + 1][j] != 2 || i == 19)) {//标记每列最底端下落方块的行数
					bottomfalling[j] = i;
				}
			}
		}
		int canfalling = 1;
		for (int j = 0; j < 10; j++) {//检测下落方块是否可下落（待改）
			if (bottomfalling[j] == 19 || canvas[bottomfalling[j] + 1][j] != 0) {
				canfalling = 0;
				break;
			}
		}
		if (canfalling) {//满足可下落条件时所有下落方块下落一格（待改）
			int row = (fallingblock->centerx) + 1;
			int col = fallingblock->centery;
			int face = fallingblock->face;
			fallingblock->Set(row, col, face);
			/*if (canvas[i][j] == 2) {
				canvas[i + 1][j] = 2;
				canvas[i][j] = 0;
			}*/
		}
		else {//不能下落时所有下落方块变为已落下方块（待改）
			canvas[fallingblock->b0x][fallingblock->b0y] = 1;
			canvas[fallingblock->b1x][fallingblock->b1y] = 1;
			canvas[fallingblock->b2x][fallingblock->b2y] = 1;
			canvas[fallingblock->b3x][fallingblock->b3y] = 1;
			delete fallingblock;//析构旧下落方块对象
			fallingblock = NULL;
			/*if (canvas[i][j] == 2) {
				canvas[i][j] = 1;
			}*/
		}
		for (int i = 0; i < 20; i++) {
			if (i < 19 && (canvas[i + 1][0] == 0 && canvas[i + 1][1] == 0 && canvas[i + 1][2] == 0 && canvas[i + 1][3] == 0 && canvas[i + 1][4] == 0 && canvas[i + 1][5] == 0 && canvas[i + 1][6] == 0 && canvas[i + 1][7] == 0 && canvas[i + 1][8] == 0 && canvas[i + 1][9] == 0) && (canvas[i][0] == 1 || canvas[i][1] == 1 || canvas[i][2] == 1 || canvas[i][3] == 1 || canvas[i][4] == 1 || canvas[i][5] == 1 || canvas[i][6] == 1 || canvas[i][7] == 1 || canvas[i][8] == 1 || canvas[i][9] == 1)) {
				for (int j = 0; j < 10; j++) {
					canvas[i + 1][j] = canvas[i + 1][j] ^ canvas[i][j];
					canvas[i][j] = canvas[i + 1][j] ^ canvas[i][j];
					canvas[i + 1][j] = canvas[i + 1][j] ^ canvas[i][j];
				}
			}//一整行满足可下落条件时（注意是已落下方块的一整行，需要和下落方块区分）
			if (canvas[i][0] == 1 && canvas[i][1] == 1 && canvas[i][2] == 1 && canvas[i][3] == 1 && canvas[i][4] == 1 && canvas[i][5] == 1 && canvas[i][6] == 1 && canvas[i][7] == 1 && canvas[i][8] == 1 && canvas[i][9] == 1) {
				canvas[i][0] = canvas[i][1] = canvas[i][2] = canvas[i][3] = canvas[i][4] = canvas[i][5] = canvas[i][6] = canvas[i][7] = canvas[i][8] = canvas[i][9] = 0;
				score++;
			}//一整行满足可消条件时
		}
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 10; j++) {
				if (fallingblock != NULL && i == fallingblock->b0x && j == fallingblock->b0y) canvas[i][j] = 2;
				else if (fallingblock != NULL && i == fallingblock->b1x && j == fallingblock->b1y) canvas[i][j] = 2;
				else if (fallingblock != NULL && i == fallingblock->b2x && j == fallingblock->b2y) canvas[i][j] = 2;
				else if (fallingblock != NULL && i == fallingblock->b3x && j == fallingblock->b3y) canvas[i][j] = 2;
				else if (canvas[i][j] != 1) canvas[i][j] = 0;
			}
		}//再次标记场地
		speed = 0;
	}
	canleft = 1;
	canright = 1;
	if (fallingblock != NULL) {
		if (fallingblock->b0y == 0 || canvas[fallingblock->b0x][fallingblock->b0y - 1] == 1) canleft = 0;
		if (fallingblock->b1y == 0 || canvas[fallingblock->b1x][fallingblock->b1y - 1] == 1) canleft = 0;
		if (fallingblock->b2y == 0 || canvas[fallingblock->b2x][fallingblock->b2y - 1] == 1) canleft = 0;
		if (fallingblock->b3y == 0 || canvas[fallingblock->b3x][fallingblock->b3y - 1] == 1) canleft = 0;
		if (fallingblock->b0y == 9 || canvas[fallingblock->b0x][fallingblock->b0y + 1] == 1) canright = 0;
		if (fallingblock->b1y == 9 || canvas[fallingblock->b1x][fallingblock->b1y + 1] == 1) canright = 0;
		if (fallingblock->b2y == 9 || canvas[fallingblock->b2x][fallingblock->b2y + 1] == 1) canright = 0;
		if (fallingblock->b3y == 9 || canvas[fallingblock->b3x][fallingblock->b3y + 1] == 1) canright = 0;
	}
}
void updatewithinput(int canl,int canr) {
	char input;
	if (_kbhit())  // 判断是否有输入
	{
		input = _getch();
		if (input == 27/*esc*/) {
			system("pause");
			exit(0);
		}
		if (input == 75/*left*/)
			if (canl == 1 && fallingblock != NULL)
				fallingblock->Set(fallingblock->centerx, fallingblock->centery - 1, fallingblock->face);
		if (input == 77/*right*/)
			if (canr == 1 && fallingblock != NULL)
				fallingblock->Set(fallingblock->centerx, fallingblock->centery + 1, fallingblock->face);
		if (input == 72/*up*/)
			if (fallingblock != NULL) {
				fallingblock->Set(fallingblock->centerx, fallingblock->centery, (fallingblock->face + 1) % 4);
				if (canvas[fallingblock->b0x][fallingblock->b0y] == 1 || canvas[fallingblock->b1x][fallingblock->b1y] == 1 || canvas[fallingblock->b2x][fallingblock->b2y] == 1 || canvas[fallingblock->b3x][fallingblock->b3y] == 1)
					fallingblock->Reset();
			}
		if (input == 80/*down*/)
			if (fallingblock != NULL) {
				fallingblock->Set(fallingblock->centerx + 1, fallingblock->centery, fallingblock->face);
				if (fallingblock->b0x>19|| fallingblock->b1x > 19 || fallingblock->b2x > 19|| fallingblock->b3x > 19 ||canvas[fallingblock->b0x][fallingblock->b0y] == 1 || canvas[fallingblock->b1x][fallingblock->b1y] == 1 || canvas[fallingblock->b2x][fallingblock->b2y] == 1 || canvas[fallingblock->b3x][fallingblock->b3y] == 1)
					fallingblock->Reset();
			}
	}
}
int main() {
	//fps_limit fps(240);
	startupgame();
	while (1) {
		show();
		for (int j = 0; j < 10; j++) {
			if (canvas[0][j] == 1) {
				system("pause");
				exit(0);
			}
		}//游戏结束
		//fps.delay();
		updatewithoutinput();
		updatewithinput(canleft,canright);
		//system("pause");
	}
	return 0;
}