/*
Игра "Тетрис"
Учебный проект консольной версии игры "Тетрис"
(c) Карыгин Роман, Санжаровский Дмитрий, Фролов Дмитрий, Китавина Наталья, Бардин Валентин,
Брянцев Всеволод, Проценко Михаил, Проценко Вячеслов, Ивутин Антон, Старинин Андрей.
(с) Компьютерная академия ШАГ. Воронеж
Версия 0.1 (21.02.2019)
*/

#include "pch.h"
#include <iostream>
using namespace std;

const int ROW = 20; // строки
const int COL = 10; // столбцы
int game_place[ROW][COL] = {}; // объявляем двумерный массив игрового поля ( {} - заполнение массива 0)

/*
	Типы фигур:
	1 - I (палка)
	2 - J 
	3 - L
	4 - O (квадрат)
	5 - S
	6 - Z
	7 - T
*/

int score = 0; // переменная, подсчитывающая очки в игре
int temp, // переменная темп - для подсчета суммы строк,

void InitFig_I(int position); //Функция появления фигуры I
void InitFig_J(int position);
void InitFig_L(int position);
void InitFig_O();
void InitFig_S(int position);
void InitFig_Z(int position);
void InitFig_T(int position);
void StartFigures(int type, int position); // Функция старта фигур
bool RowFull(int row);
bool GameOver(); // функция определения проигрыша
int GameScore(); // Функция определения очков
void DeleteRow(); // Функция удаления строки при ее заполнении




int main()
{
	setlocale(LC_ALL, "rus");
}
void InitFig_I(int position)
{
	switch (position)
	{
	case 1: // горизонтальное положение
	{
		game_place[0][3] = 1;
		game_place[0][4] = 1;
		game_place[0][5] = 1;
		game_place[0][6] = 1;

	}
		break;
	case 2: // вертикальное положение
	{
		game_place[0][5] = 1;
		game_place[1][5] = 1;
		game_place[2][5] = 1;
		game_place[3][5] = 1;
	}
		break;
	}
}
void StartFigures(int type, int position) 
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
	default:
		break;
	}
}

bool GameOver()
{	// функция проверяет верхнюю строчку на наличие в ней "1". Если есть хоть одна "1", игра окончена.
	for (int i = 0; i < COL; i++)
	{
		if (game_place[0][i] == 1)
			return true;
		else
			return false;
	}
}

bool RowFull(int row)
{
	int temp = 0;
	for (int j = 0; j < COL; j++)
	{
		temp = temp + game_place[row][j];
	}
	if (temp == 10)
		return true;
	else
		return false;
}

int GameScore()
{
	
	int k=0;  //переменная к - подсчитывает количество строк, сумма в которых равна 10
	for (int i = 0; i < ROW; i++)
	{
		
		if (RowFull(i)) // если строка заполненна, то увеличиваем счетчик
		{
			k++;
		}
	}
	switch (k) // если одновременно заполненных строк 1 - 100 очков, 2 - 300 очков, 3 - 700 очков, 4 - 1500 очков, 0 - возврат.
	{
	case 1: return 100; break;
	case 2: return 300; break;
	case 3: return 700; break;
	case 4: return 1500; break;
	default: return 0; break;
	}
}

void DeleteRow()
{
	int m = 0; // временная переменная для внесения адреса заполненной строки
	for (int i = 0; i < ROW; i++)
	{
		if (RowFull(i))
		{
			m = i; // находим, какая строка заполнена
			do 
			{
				for (int j = 0; j < COL; j++)
				{
					game_place[m][j] = game_place[m - 1][j];
				}
				m--;
			}while (m!=0)
		}
	}
}

