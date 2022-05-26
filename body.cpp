#pragma warning(disable:4996)
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "blocklist.h"
#include "fps_limit.h"//����֡��
using namespace std;
int canvas[20][10] = {0};//���Ѿ����µķ�����Ϊ1����������ķ�����Ϊ2
Block* fallingblock=NULL;//���䷽��
static int canleft;
static int canright;
static int score = 0;//����
static int speedindex = 60;//�������䷽���ٶȿ��������ӣ�Խ��Խ�����������ڵ����Ѷȣ�
static int speed(speedindex / 2);
void gotoxy(int x, int y)  //����ƶ���(x,y)λ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}
void startupgame() {
	SetConsoleTitle(L"��ά������ by Bx");//���ÿ���̨���ڱ���
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT rc = { 0,0, 20, 22 }; // ����λ�ýṹ���ʼ��
	SetConsoleWindowInfo(handle, true, &rc);//���ÿ���̨���ڴ�С
	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };
	SetConsoleCursorInfo(handle, &cursorInfo);//���ؿ���̨���
	cout << "--Soviet Blocks--" << endl;
	cout << "Start Z" << endl;
	cout << "Quit  A" << endl;
	cout << endl << "#Help#" << endl << "Move:����" << endl << "Rotate:��" << endl<<"Speed up:��"<<endl;
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
		int dofallingsexist = 0;//�����Ƿ�������䷽��
		for (int j = 0; j < 10; j++) {//���ȫ���Ƿ������䷽��
			for (int i = 0; i < 20; i++) {
				if (canvas[i][j] == 2) {//�������䷽��
					dofallingsexist = 1;
					break;
				}
			}
		}
		if (!dofallingsexist) {//�����·��飨���ģ�
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
		}//��ǳ���
		int bottomfalling[10] = { 0 };//ÿһ�����·����������䷽���������
		for (int j = 0; j < 10; j++) {//��¼ÿһ������������䷽�����λ��
			for (int i = 0; i < 20; i++) {
				if (canvas[i][j] == 2 && (i < 19 && canvas[i + 1][j] != 2 || i == 19)) {//���ÿ����׶����䷽�������
					bottomfalling[j] = i;
				}
			}
		}
		int canfalling = 1;
		for (int j = 0; j < 10; j++) {//������䷽���Ƿ�����䣨���ģ�
			if (bottomfalling[j] == 19 || canvas[bottomfalling[j] + 1][j] != 0) {
				canfalling = 0;
				break;
			}
		}
		if (canfalling) {//�������������ʱ�������䷽������һ�񣨴��ģ�
			int row = (fallingblock->centerx) + 1;
			int col = fallingblock->centery;
			int face = fallingblock->face;
			fallingblock->Set(row, col, face);
			/*if (canvas[i][j] == 2) {
				canvas[i + 1][j] = 2;
				canvas[i][j] = 0;
			}*/
		}
		else {//��������ʱ�������䷽���Ϊ�����·��飨���ģ�
			canvas[fallingblock->b0x][fallingblock->b0y] = 1;
			canvas[fallingblock->b1x][fallingblock->b1y] = 1;
			canvas[fallingblock->b2x][fallingblock->b2y] = 1;
			canvas[fallingblock->b3x][fallingblock->b3y] = 1;
			delete fallingblock;//���������䷽�����
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
			}//һ�����������������ʱ��ע���������·����һ���У���Ҫ�����䷽�����֣�
			if (canvas[i][0] == 1 && canvas[i][1] == 1 && canvas[i][2] == 1 && canvas[i][3] == 1 && canvas[i][4] == 1 && canvas[i][5] == 1 && canvas[i][6] == 1 && canvas[i][7] == 1 && canvas[i][8] == 1 && canvas[i][9] == 1) {
				canvas[i][0] = canvas[i][1] = canvas[i][2] = canvas[i][3] = canvas[i][4] = canvas[i][5] = canvas[i][6] = canvas[i][7] = canvas[i][8] = canvas[i][9] = 0;
				score++;
			}//һ���������������ʱ
		}
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 10; j++) {
				if (fallingblock != NULL && i == fallingblock->b0x && j == fallingblock->b0y) canvas[i][j] = 2;
				else if (fallingblock != NULL && i == fallingblock->b1x && j == fallingblock->b1y) canvas[i][j] = 2;
				else if (fallingblock != NULL && i == fallingblock->b2x && j == fallingblock->b2y) canvas[i][j] = 2;
				else if (fallingblock != NULL && i == fallingblock->b3x && j == fallingblock->b3y) canvas[i][j] = 2;
				else if (canvas[i][j] != 1) canvas[i][j] = 0;
			}
		}//�ٴα�ǳ���
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
	if (_kbhit())  // �ж��Ƿ�������
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
		}//��Ϸ����
		//fps.delay();
		updatewithoutinput();
		updatewithinput(canleft,canright);
		//system("pause");
	}
	return 0;
}