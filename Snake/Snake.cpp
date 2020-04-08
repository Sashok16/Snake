#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

bool gameOver;
int width;
int height;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;

enum eDirection {
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

eDirection dir;

void SizeOfConsole(int&, int&);
void Setup();
void Draw();
void Input();
void Logic();

int main()
{
	HANDLE hCon;
	COORD cPos;
	SizeOfConsole(width, height);
	Setup();
	bool restart = true;
	while (restart) {
		while (!gameOver) {
			Draw();
			Input();
			Logic();
		}
		system("cls");
		char answer;
		cout << "Are you finished? (y/n): ";
		cin >> answer;
		if (answer == 'y') {
			restart = false;
			system("cls");
			cout << endl << "Good bey";
		}
		else if (answer == 'n') {
			Setup();
		}

	}
	return 0;
}
void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruitX = rand() % (width / 2 - 2) ;
	fruitY = rand() % (height / 2 - 2);
	score = 0;
	for (int i = 0; i < 100; i++) {
		if (tailX[i] != 0) tailX[i] = 0;
		if (tailY[i] != 0) tailY[i] = 0;
	}
	nTail = 0;
}

void Draw() {
	system("cls");
	for (int i = 0; i < width + 1; i++) {
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height + 1; i++) {
		for (int j = 0; j < width ; j++) {
			if (j == 0 || j == width - 1)
				cout << "#";
			if (i == y && j == x)
				cout << "S";
			else if (i == fruitY && j == fruitX)
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						cout << "s";
					}
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 1; i++) {
		cout << "#";
	}
	cout << endl;

	cout << "Score: " << score << endl;
}
void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic() {
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailY[0] = y;
	tailX[0] = x;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}


	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	/*if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;*/

	if (x >= width - 1)
		x = 0;
	else if (x < 0)
		x = width - 2;

	if (y >= height + 1)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y) {
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = rand() % (width / 2 - 2);
		fruitY = rand() % (height / 2 - 2);
		nTail++;
	}
}

void SizeOfConsole(int& WIDTHCONSL, int& HIGHTCONSL)
{
	HANDLE hWndConsole;
	if (hWndConsole = GetStdHandle(-12))
	{
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
		{
			WIDTHCONSL = (consoleInfo.srWindow.Right - consoleInfo.srWindow.Left) / 2;
			HIGHTCONSL = (consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top) / 2;
		}
		else
			cout << "Error: " << GetLastError() << endl;
	}
	else
		cout << "Error: " << GetLastError() << endl;
}