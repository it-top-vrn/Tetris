/*
	Игра тетрис
	учебный проект консельной версии игры тетрис
	(c) Protsenko Vyacheslav, Kitavina Nata, Sanzharovskiy Dmitriy, Karigin Roman, Frolov Dmitriy, bardin Valentin, Brantsev Vsevolod, Protsenko Mikhail, Starin Andrey
	(c) Computer academy "Step". Voronezh

	Version: 0.1 (20.02.2019)
*/

#include "pch.h" 
#include <iostream> 
#include <string>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <conio.h>

using namespace std;

const int ROW = 20;  //кол строк
const int COL = 10;  // кол столбцов

int score = 0; //счетчик очков
int temp;   //переменная для подсчета заполненности строки
int k = 0;   //подсчет заполненых строк

int game_place[ROW][COL] = {};   //игровое поле
/*
Типы фигур:
1- I    (палка)
2 - J
3 - L
4 - 0   (квадрат)
5 - S
6 - Z
7 - T

int fig_I[4] = { 1,1,1,1 };   //палка
int fig_I[4] = { 1,1,1,1 };   //палка
*/
void InitFig_I(int postion);
void InitFig_J(int postion);
void InitFig_L(int postion);
void InitFig_O();
void InitFig_S(int postion);
void InitFig_Z(int postion);
void InitFig_T(int postion);

void StartFig(int type, int postion);

int GameScare();  // подсчет очков
bool RowFULL(int row);   // определяет заполниность строки
void DelRow();    //удаление заполненной строки
bool GameOver(); //определение проигрыша


int main()
{

}

void InitFig_I(int postion)  //палка
{
	switch (postion)
	{
	case 1: //Горизонтально
	{
	
			game_place[0][3] = 1;
			game_place[0][4] = 1;
			game_place[0][5] = 1;
			game_place[0][6] = 1;
		
	}break;
	case 2: // вертикально
	{
		game_place[0][5] = 1;
		game_place[1][5] = 1;
		game_place[2][5] = 1;
		game_place[3][5] = 1;

	}break;

	}
}

void StartFig(int type, int postion)
{
	switch (type)
	{
	case 1: InitFig_I(postion);
	{


	}break;
	case 2: InitFig_J(postion);
	{

	}break;

	case 3: InitFig_L(postion);
	{

	}break;

	case 4: InitFig_O();
	{

	}break;

	case 5: InitFig_S(postion);
	{

	}break;

	case 6: InitFig_Z(postion);
	{

	}break;

	case 7: InitFig_T(postion);
	{

	}break;

	default:
		break;
	}
}



bool RowFULL(int row)
{
	temp = 0;
	for (int j = 0; j < COL; j++)
	{
		temp = temp + game_place[row][j];
	}
	if (temp == 10)
	{
		return true;
	}
	else
	{
		return false;
	}
}


int GameScare()
{
	
	for (int i = 0; i < ROW; i++)
	{
		if (RowFULL(i));  
		k++;
	}

	switch (k)  //колчичество очков при заполнении строк
	{
	case 1:
	{
		return 100;   //колчичество очков при заполнении 1 й строки
	}break;

	case 2:
	{
		return 300;    //колчичество очков при заполнении 2х строк
	}break;
	case 3:
	{
		return 700;    //колчичество очков при заполнении 3х строк
	}break;

	case 4:
	{
		return 1500;   //колчичество очков при заполнении 4х строк
	}break;

	default:
		return 0;
		break;
	}
}

void DelRow()
{
	int m = 0;  // переменная подмены i
	for (int i = 0; i < ROW; i++)
	{
		if (RowFULL(i));
		{
			m = i;
			do
			{
				for (int j = 0; j < COL; j++)
				{
					game_place[m][j] = game_place[m - 1][j];
				}
				m--;
			} while (m != 0);
		}
	}
}

bool GameOver()
{
	// фун проверки верхней строки поля на наличие в ней "1", 1 -  часть фигуры 
	for (int i = 0; i < COL; i++)
	{
		if (game_place[0][i] == 1)
		{
			return true;
		}
		else
		{
			false;
		}
	}
}