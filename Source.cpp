#include <iostream>
#include <ctime>
#include <conio.h>
#include "windows.h"
using namespace std;

bool GameOver;
const int n = 20;
const int m = 50;
int timer = 0, x, y, enemyX, enemyY, enemyX1, enemyY1, score;
char sym;
//enum eDirection { DOWN };
//eDirection dir;

 // Попытка создать чаровский массив
char field[n][m] = {
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#' },
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' },
};
void Setup();
// Отрисовка карты
void Place();
// Навигация
void Move();
// Выстрел
/*void Shout();*/
// Выстрел
bool shout();
// Логика
void Logic();

int main() {
	setlocale(LC_ALL, "Russian");
	setlocale(LC_ALL, "ru");

	// Попытка вывести чаровский массив
	/*
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << ' ' << field[i][j];
			if (i == n - 2 && j == (m - 1) / 2)
				cout << " A";
			if (i >= 0 && j == m - 1)
				cout << " #";
		}
		cout << endl;
	}*/

	Setup();
	while (!GameOver) {
		Place();
		Move();
		Logic();

	}

	return 0;
}
void Setup() {
	bool GameOver = false;
	x = (m - 1) / 2;
	y = n - 2;
	srand(time(NULL));
	enemyX = rand() % (m - 1) + 1;
	enemyY = 1;
	enemyX1 = rand() % (m - 1) + 1;
	enemyY1 = 1;
	score = 0;
}
// Отрисовка карты
void Place() {
	system("cls");
	cout << "\t\t\tGalaga!\n\n";

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			if (i == 0 && j >= 0 || i >= 0 && j == 0 || i == n - 1 && j >= 0 || j == m - 1 && i >= 0)
				cout << "#";
			else if (i == y && j == x)
				cout << "A";
			else if (i == enemyY && j == enemyX || i == enemyY1 && j == enemyX1) {
				cout << "V";
				timer += 100;
				if (timer % 1000 == 0) {
					enemyY++;
					enemyY1++;
					timer = 0;
				}
			}
			/*else if (shout) {
				if (i == y && j == x)
					cout << "|";
			}*/
			else
				cout << " ";
		cout << endl;
	}
	cout << "Score: " << score << endl;
}
// Навигация
void Move() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a': case 'A':
			x--;
			break;
		case 'd': case 'D':
			x++;
			break;
		case 'p': case 'P':
			system("cls");
			cout << "Пауза.\n";
			system("pause");
			break;
			/*case 'f': case 'F':
				for (int i = 0; i < n - 3; i++) {
					cout << "|";
					cout << endl;
				}
				Sleep(10);
				system("cls");
				break;*/
		case 'q': case 'Q':
			cout << "\t\tВы действительно хотите выйти?\n";
			cout << "\t\t1. Да;\n";
			cout << "\t\t2. Нет.\n\n";
			int answer;
			cout << "\t\tВвод -> ";
			cin >> answer;
			switch (answer) {
			case 1:
				GameOver = true;
				break;
			case 2:	break;
			}
		}
	}
}
// Выстрел
/*void Shout() {
	if (_kbhit()) {
		sym = _getch();
		if (sym == 'f')
	for (int i = 0; i < n - 3; i++)
		//for (int j = 0; j < m - 1; j++) {
			if (i > y)
				cout << "|";
			Sleep(10);
			/ *if (i == enemyY) {
				score += 10;
				enemyX = rand() % (m - 1) + 1;
				enemyY = 1;
			}
			if (i == enemyY1) {
				score += 10;
				enemyX1 = rand() % (m - 1) + 1;
				enemyY1 = 1;
			}* /
		//}
	system("cls");
	}
}*/
// Выстрел
bool shout() {
	if (_kbhit())
		sym = _getch();
	if (sym == 'f')
		return true;
	return false;
}
// Логика
void Logic() {
	// Движение вниз
	/*if (DOWN) {
		enemyY++;
		enemyY1++;
	}*/

	// Обработка столкновения с самолётом, либо с краем игрового поля
	if (enemyY == n - 1 || x == enemyX && y == enemyY) {
		score -= 10;
		enemyX = rand() % (m - 1) + 1;
		enemyY = 1;
	}

	if (enemyY1 == n - 1 || x == enemyX1 && y == enemyY1) {
		score -= 10;
		enemyX1 = rand() % (m - 1) + 1;
		enemyY1 = 1;
	}

	// Касание края карты самолётом
	if (x == 0 && y == n - 2) {
		x++;
	}
	if (x == m - 1 && y == n - 2) {
		x--;
	}
}