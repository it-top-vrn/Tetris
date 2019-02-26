/*
	Игра тетрис
	Учебный проект консульной версии игры тетрис
	(c) Protsenko Mikhail, Kitavina Nataya, Samzharovskiy Dmitriy, Karigyn Roman, Frolov Dmitriy, Bardin Valentin, Bryantsev Vsevolod, Protsenko Vyacheslav, Starinin Andrey
	(c) Компьютерная академия ШАГ . Воронеж
	Версия 0.1 (21.02.2019)
*/

#include "pch.h"
#include <iostream>
#include <time.h>
#include <math.h>
#include <conio.h>

using namespace std;

const int ROW = 20;				// Кол-во строк
const int COL = 10;				// Кол-во столбцов

int game_place[ROW][COL]{};		// Объявляем массив размером 20x10 (игровое поле) и инициализировали его 0

/*
	Типы фигур
	1 - I (Палка)
	2 - J
	3 - L
	4 - O (Квадрат)
	5 - S
	6 - Z
	7 - T
*/


int score = 0;					// Подсчет очков
int temp;						// Переменная, для подсчета заполненности строки
int check = 0;
int *pcheck = &check;

void InitFig_I(int position);
void InitFig_J(int position);
void InitFig_L(int position);
void InitFig_O();
void InitFig_S(int position);
void InitFig_Z(int position);
void InitFig_T(int position);
void StartFig(int type, int position); // Описываем фигуры


void Fig_I_Poz1(int x, int y);
void Fig_I_Poz2(int x, int y);

void Fig_J_Poz1(int x, int y);
void Fig_J_Poz2(int x, int y);
void Fig_J_Poz3(int x, int y);
void Fig_J_Poz4(int x, int y);

void Fig_L_Poz1(int x, int y);
void Fig_L_Poz2(int x, int y);
void Fig_L_Poz3(int x, int y);
void Fig_L_Poz4(int x, int y);

void Fig_Z_Poz1(int x, int y);
void Fig_Z_Poz2(int x, int y);

void Fig_S_Poz1(int x, int y);
void Fig_S_Poz2(int x, int y);

void Fig_T_Poz1(int x, int y);
void Fig_T_Poz2(int x, int y);
void Fig_T_Poz3(int x, int y);
void Fig_T_Poz4(int x, int y);


bool RowFull(int row);			// Определение заполненности строки
int GameScore();				// Определение очков
void DeleteRow();				// Удаление заполенной строки

bool GameOver();				// Определение проигрыша
bool CheckStep(int x, int y, int check);

void Game();

int main()
{
	Game();
}

bool CheckStep(int x, int y, int check) {

	switch (check)
	{
	case 1:   // проверка 1 координатного горизонтального элемента
		if (game_place[x + 1][y] != 1 ) {
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 2:   // проверка 2 координатного горизонтального элемента
		if (game_place[x + 1][y] != 1 || game_place[x + 1][y + 1] != 1) {
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 3:  // проверка 3 координатного горизонтального элемента
		if (game_place[x + 1][y] != 1 || game_place[x + 1][y + 1] != 1 || game_place[x + 1][y + 2] != 1){
			return false;
		}
		else
		{
			return true;
		}
		break;
	case 4:   // проверка 4 координатного горизонтального элемента
		if (game_place[x + 1][y] != 1 || game_place[x + 1][y + 1] != 1|| game_place[x + 1][y + 2] != 1 || game_place[x + 1][y + 3] != 1) {
			return false;
		}
		else
		{
			return true;
		}
		break;
	default:
		break;
	}

}

void Fig_I_Poz1(int x, int y) // Фигура I , горизонтальное положение 
{
	game_place[x][y] = 1;
	game_place[x][y + 1] = 1;
	game_place[x][y + 2] = 1;
	game_place[x][y + 3] = 1;
	if (CheckStep(x, y, 4)) {
		*pcheck = 1;
	}
}
void Fig_I_Poz2(int x, int y) // Фигура I , вертикальное положение 
{
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y] = 1;
	game_place[x + 3][y] = 1;
	if (CheckStep(x, y, 1)) {
		*pcheck = 1;
	}
}

void Fig_J_Pos1(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y - 1] = 1;
	game_place[x + 2][y] = 1;
	if (CheckStep(x, y, 2)) {
		*pcheck = 1;
	}
}
void Fig_J_Pos2(int x, int y)
{
	game_place[x][y - 1] = 1;
	game_place[x + 1][y - 1] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 1][y + 1] = 1;
	if (CheckStep(x, y, 3)) {
		*pcheck = 1;
	}
}
void Fig_J_Pos3(int x, int y)
{
	game_place[x][y - 1] = 1;
	game_place[x][y] = 1;
	game_place[x + 1][y - 1] = 1;
	game_place[x + 1][y + 1] = 1;
	if (CheckStep(x, y, 3)) {
		*pcheck = 1;
	}
}
void Fig_J_Pos4(int x, int y)
{
	game_place[x][y - 1] = 1;
	game_place[x][y] = 1;
	game_place[x][y + 1] = 1;
	game_place[x + 2][y - 1] = 1;
	if (CheckStep(x, y, 3)) {
		*pcheck = 1;
	}
}

void Fig_L_Pos1(int x, int y)
{
	game_place[x][y - 1] = 1;
	game_place[x + 1][y - 1] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 1][y + 1] = 1;
	if (CheckStep(x, y, 3)) {
		*pcheck = 1;
	}
}
void Fig_L_Pos2(int x, int y)
{
	game_place[x][y + 1] = 1;
	game_place[x + 1][y - 1] = 1;
	game_place[x + 2][y - 1] = 1;
	game_place[x + 2][y] = 1;
	if (CheckStep(x, y, 3)) {
		*pcheck = 1;
	}
}
void Fig_L_Pos3(int x, int y)
{
	game_place[x][y - 1] = 1;
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y] = 1;
	if (CheckStep(x, y, 2)) {
		*pcheck = 1;
	}
}
void Fig_L_Pos4(int x, int y)
{
	game_place[x][y - 1] = 1;
	game_place[x][y] = 1;
	game_place[x][y + 1] = 1;
	game_place[x + 1][y - 1] = 1;
	if (CheckStep(x, y, 3)) {
		*pcheck = 1;
	}
}

void Fig_O_Pos(int x, int y)
{
	game_place[x][y - 1] = 1;
	game_place[x][y] = 1;
	game_place[x + 1][y - 1] = 1;
	game_place[x + 1][y] = 1;
	if (CheckStep(x, y, 2)) {
		*pcheck = 1;
	}
}

void Fig_S_Pos1(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 1][y - 1] = 1;
	game_place[x][y + 1] = 1;
	if (CheckStep(x, y, 3)) {
		*pcheck = 1;
	}
}
void Fig_S_Pos2(int x, int y)
{
	game_place[x][y - 1] = 1;
	game_place[x + 1][y - 1] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y] = 1;
	if (CheckStep(x, y, 2)) {
		*pcheck = 1;
	}
}

void Fig_Z_Pos1(int x, int y)
{
	game_place[x][y - 1] = 1;
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 1][y + 1] = 1;
	if (CheckStep(x, y, 3)) {
		*pcheck = 1;
	}
}
void Fig_Z_Pos2(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 1][y - 1] = 1;
	game_place[x + 2][y - 1] = 1;
	if (CheckStep(x, y, 2)) {
		*pcheck = 1;
	}
}

void Fig_T_Pos1(int x, int y)
{
	game_place[x][y - 1] = 1;
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x][y + 1] = 1;
	if (CheckStep(x, y, 3)) {
		*pcheck = 1;
	}
}
void Fig_T_Pos2(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y] = 1;
	game_place[x + 1][y - 1] = 1;
	if (CheckStep(x, y, 2)) {
		*pcheck = 1;
	}
}
void Fig_T_Pos3(int x, int y)
{
	game_place[x][y - 1] = 1;
	game_place[x + 1][y - 1] = 1;
	game_place[x + 2][y - 1] = 1;
	game_place[x + 1][y] = 1;
	if (CheckStep(x, y, 2)) {
		*pcheck = 1;
	}
}
void Fig_T_Pos4(int x, int y)
{
	game_place[x][y - 1] = 1;
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x][y + 1] = 1;
	if (CheckStep(x, y, 3)) {
		*pcheck = 1;
	}
}

void InitFig_I(int position)
{
	switch (position)
	{
	case 1: Fig_I_Poz1(0, 3);
		break;
	case 2: Fig_I_Poz2(0, 5);
		break;
	}

}

void InitFig_J(int position)
{
	switch (position)
	{
	case 1:	Fig_J_Pos1(0, 5);
		break;
	case 2:	Fig_J_Pos2(0, 5);
		break;
	case 3:	Fig_J_Pos3(0, 5);
		break;
	case 4:	Fig_J_Pos4(0, 5);
		break;
	}
}

void InitFig_L(int position)
{
	switch (position)
	{
	case 1:	Fig_L_Pos1(0, 5);
		break;
	case 2:	Fig_L_Pos2(0, 5);
		break;
	case 3:	Fig_L_Pos3(0, 5);
		break;
	case 4:	Fig_L_Pos4(0, 5);
		break;
	}
}
void InitFig_O()
{
	Fig_O_Pos(0, 5);
}

void InitFig_S(int position)
{
	switch (position)
	{
	case 1:	Fig_S_Pos1(0, 5);
		break;
	case 2:	Fig_S_Pos2(0, 5);
		break;
	}
}

void InitFig_Z(int position)
{
	switch (position)
	{
	case 1:	Fig_Z_Pos1(0, 5);
		break;
	case 2:	Fig_Z_Pos2(0, 5);
		break;
	}
}

void InitFig_T(int position)
{
	switch (position)
	{
	case 1:	Fig_T_Pos1(0, 5);
		break;
	case 2:	Fig_T_Pos2(0, 5);
		break;
	case 3:	Fig_T_Pos3(0, 5);
		break;
	case 4:	Fig_T_Pos4(0, 5);
		break;
	}
}

void StartFig(int type, int position)
{
	switch (type)
	{
	case 1: InitFig_I(position);
		break;
	case 2: InitFig_J(position);
		break;
	case 3: InitFig_L(position);
		break;
	case 4: InitFig_O();
		break;
	case 5: InitFig_S(position);
		break;
	case 6: InitFig_Z(position);
		break;
	case 7: InitFig_T(position);
		break;
	}
}

void Fig_Step(int type, int poz)
{
	switch (type)
	{
	case 1:
	{
		switch (poz)
		{
		case 1:
		{
			for (int i = 0; i < ROW; i++)
			{
				Fig_I_Poz1(i, 3);
				if (*pcheck == 1) {
					*pcheck = 0;
					break;
				}

			}
		}
		}
	}
	}
}

bool RowFull(int row)
{
	temp = 0;
	for (int j = 0; j < COL; j++)
		temp += game_place[row][j];

	if (temp == 10)
		return true;
	else
		return false;
}

int GameScore()
{
	int k = 0;	// Переменная для подсчета заполненных строк
	for (int i = 0; i < ROW; i++)
	{
		if (RowFull(i))	// Если строка заполенная, то увеличиваем счетчик заполненых строк на 1
			k++;
	}
	// Добавление очков при полном заполнении строки 
	switch (k)
	{
	case 1:
		return 100;			// При заполнении 1 строки 100 очков
		break;
	case 2:
		return 300;			// При заполнении 2 строк 300 очков
		break;
	case 3:
		return 700;			// При заполнении 3 строк 700 очков
		break;
	case 4:
		return 1500;		// При заполнении 4 строк 1500 очков
		break;
	default:
		return 0;
		break;
	}
}

void DeleteRow()
{
	int m = 0;

	for (int i = 0; i < ROW; i++)
	{
		if (RowFull(i))
		{		// Если строка заполненная, то заменяем ее строкой выше
			m = i;
			do {
				for (int j = 0; j > COL; j++)
					game_place[m][j] == game_place[m - 1][j];
				m--;
			} while (m != 0);
		}
	}
}

// Функция для проверки верхней строчки игрового поля на наличие в ней 1 (признак фигуры), если есть хоть одна то игра окончена	
bool GameOver()
{
	for (int i = 0; i < COL; i++)
	{
		if (game_place[0][i] == 1)
			return true;
		else
			return false;
	}
}

