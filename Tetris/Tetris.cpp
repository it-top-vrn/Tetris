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

const int ROW = 20;		// кол-во строки
const int COL = 10;		//кол -во колонок
int scores = 0;			// очки
int temp = 0;
int k = 0;
int Game_Play[ROW][COL];	// 2мерный массив 20х10

/*
	типы фигур:
	1 - I (палка)
	2 - L
	3 - J
	4 - 0 (квадрат)
	5 - S
	6 - Z
	7 - T
*/
int figure_I[4] = { 1,1,1,1 };
int figure_L[4] = { 1,1,1,1 };

void InitFig_I(int position);
void InitFig_L(int position);
void InitFig_J(int position);
void InitFig_0();
void InitFig_S(int position);
void InitFig_Z(int position);
void InitFig_T(int position);
bool GameOver();
bool ROWfull(int row);
int GameScores();
void DeleteROW();	// удаляет строку есть она полностью заполнена 
void StartFigure(int type, int position);

int mail() {
	

	return 0;
}

bool GameOver() {
	// если хоть одна вверхняя ячейка заполнена (ровна 1) тогда, гейм овер 
	for (int i = 0; i < COL; i++)
	{
		if (Game_Play[0][i] == 1) {
			return true;
		}
		else {
			return false;
		}
	}
}

int GameScores() {
	
	for (int i = 0; i < ROW; i++)
	{
		temp = 0;
		for (int j = 0; j < COL; j++)
		{
			if (ROWfull(i)) {
				k++;
			}
		}
	}

	if (k == 0) {	// при заполнении 0 строки 0 очков
		return 0;
	}
	if (k == 1) {	// при заполнении 1 строки 100 очков
		return 100;
	}
	if (k == 2) {	// при заполнении 2 строки 300 очков
		return 300;
	}
	if (k == 3) {	// при заполнении 3 строки 700 очков
		return 700;
	}
	if (k == 4) {	// при заполнении 4 строки 1500 очков
		return 1500;
	}
}

bool ROWfull(int row) {
	for (int j = 0; j < COL; j++)
	{
		temp = temp + Game_Play[row][j];
	
	}
	if (temp == 10) {
		return true;
	}
	else {
		return false;
	}
}


void DeleteROW() {
	int m = 0;
	for (int i = 0; i < ROW; i++)
	{
		if (ROWfull(i)) {
			m = i;
			do {
				for (int j = 0; j < COL; j++)
				{
					Game_Play[m][j] = Game_Play[m - 1][j];
				}
				m--;
			} while (m != 0);
		}
	}
}


void StartFigure(int type, int position) {
	switch (type)
	{
	case 1:
		InitFig_I(position);
		break;
	case 2:
		InitFig_L(position);
		break;
	case 3:
		InitFig_J(position);
		break;
	case 4:
		InitFig_0();
		break;
	case 5:
		InitFig_S(position);
		break;
	case 6:
		InitFig_Z(position);
		break;
	case 7:
		InitFig_T(position);
		break;
	default:
		break;
	}
}



void InitFig_I(int position) {
	switch (position)
	{
	case 1:		// gorizontalnoe polozhenie
		for (int i = 0; i < COL; i++)
		{
			if (i > 2 && i <= 6) {
				Game_Play[0][i] = 1;
			}
		}
		break;
	case 2:		// vertikalnoe polozhenie
		for (int i = 0; i < COL; i++)
		{
			if (i < 4) {
				Game_Play[i][5] = 1;
			}
		}
		break;
	}
}