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

void Fig_I_pos_1(int x, int y);//Горизонтально I //палка
void Fig_I_pos_2(int x, int y);// вертикально I //палка
void InitFig_I(int postion);

void Fig_J_pos_1(int x, int y); // вертикально J
void Fig_J_pos_2(int x, int y); // J Вверх нагами
void Fig_J_pos_3(int x, int y); //Горизонтально  |___
void Fig_J_pos_4(int x, int y); // вертикально  ===,
void InitFig_J(int postion);

void Fig_L_pos_1(int x, int y);  // вертикально L
void Fig_L_pos_2(int x, int y); // L Вверх нагами 
void Fig_L_pos_3(int x, int y);  //Горизонтально  ,===
void Fig_L_pos_4(int x, int y);  // вертикально  ___|
void InitFig_L(int postion);

void InitFig_O();

void Fig_S_pos_1(int x, int y);  // вертикально S
void Fig_S_pos_2(int x, int y);  // гориз S 
void InitFig_S(int postion);

void Fig_Z_pos_1(int x, int y);  // вертикально Z
void Fig_Z_pos_2(int x, int y);  // гориз Z 
void InitFig_Z(int postion);

void Fig_T_pos_1(int x, int y);  // вертикально T
void Fig_T_pos_2(int x, int y);  // T Вверх нагами 
void Fig_T_pos_3(int x, int y);  //Горизонтально  |=
void Fig_T_pos_4(int x, int y);  // вертикально  =|
void InitFig_T(int postion);

void StartFig(int type, int postion);

int GameScare();  // подсчет очков
bool RowFULL(int row);   // определяет заполниность строки
void DelRow();    //удаление заполненной строки
bool GameOver(); //определение проигрыша


int main()
{

}

void Fig_I_pos_1(int x, int y)//Горизонтально I //палка
{
	game_place[x][y] = 1;
	game_place[x][y + 1] = 1;
	game_place[x][y + 2] = 1;
	game_place[x][y + 3] = 1;
}

void Fig_I_pos_2(int x, int y)// вертикально I //палка
{ 
	game_place[x][y] = 1;
	game_place[x+1][y] = 1;
	game_place[x+2][y] = 1;
	game_place[x+3][y] = 1;
}

void InitFig_I(int postion)  //палка
{
	switch (postion)
	{
	case 1: //Горизонтально
	{
		Fig_I_pos_1(0, 3);
		//game_place[0][3] = 1;
		//game_place[0][4] = 1;
		//game_place[0][5] = 1;
		//game_place[0][6] = 1;

	}break;
	case 2: // вертикально
	{
		Fig_I_pos_1(0, 5);
		//game_place[0][5] = 1;
		//game_place[1][5] = 1;
		//game_place[2][5] = 1;
		//game_place[3][5] = 1;

	}break;

	}
}

void InitFig_O()   //кубик
{   
	game_place[0][4] = 1;
	game_place[0][5] = 1;
	game_place[1][4] = 1;
	game_place[1][5] = 1;
}

void Fig_J_pos_1(int x, int y) // вертикально J
{
	
	game_place[x+0][y] = 1;
	game_place[x+1][y] = 1;
	game_place[x+2][y] = 1;
	game_place[x+2][y-1] = 1;
}

void Fig_J_pos_2(int x, int y) // J Вверх нагами
{

	game_place[x][y+1] = 1;
	game_place[x][y] = 1;
	game_place[x+1][y] = 1;
	game_place[x+2][y] = 1;
}

void Fig_J_pos_3(int x, int y) //Горизонтально  |___
{

	game_place[x][y] = 1;
	game_place[x+1][y] = 1;
	game_place[x+1][y+1] = 1;
	game_place[x+1][y+2] = 1;
}

void Fig_J_pos_4(int x, int y) // вертикально  ===,
{

	game_place[x][y+2] = 1;
	game_place[x][y] = 1;
	game_place[x][y+1] = 1;
	game_place[x+1][y+2] = 1;
}


void InitFig_J(int postion)
{
	switch (postion)
	{
	case 1: // вертикально J
	{
		Fig_J_pos_1(0, 5);
		//game_place[0][5] = 1;
		//game_place[1][5] = 1;
		//game_place[2][5] = 1;
		//game_place[2][4] = 1;

	}break;
	case 2: // J Вверх нагами 
	{
		Fig_J_pos_2(0, 5);
		//game_place[0][6] = 1;
		//game_place[0][5] = 1;
		//game_place[1][5] = 1;
		//game_place[2][5] = 1;


	}break;

	case 3: //Горизонтально  |___
	{
		Fig_J_pos_3(0, 4);
		//game_place[0][4] = 1;
		//game_place[1][4] = 1;
		//game_place[1][5] = 1;
		//game_place[1][6] = 1;

	}break;

	case 4: // вертикально  ===,
	{
		Fig_J_pos_4(0, 4);
		//game_place[0][6] = 1;
		//game_place[0][4] = 1;
		//game_place[0][5] = 1;
		//game_place[1][6] = 1;
	}break;

	}
}

void Fig_L_pos_1(int x, int y) // вертикально L
{

	game_place[x][y] = 1;
	game_place[x+1][y] = 1;
	game_place[x+2][y] = 1;
	game_place[x+2][y+1] = 1;
}

void Fig_L_pos_2(int x, int y) // L Вверх нагами 
{

	game_place[x][y-1] = 1;
	game_place[x][y] = 1;
	game_place[x+1][y] = 1;
	game_place[x+2][y] = 1;
}

void Fig_L_pos_3(int x, int y)  //Горизонтально  ,===
{

	game_place[x][y] = 1;
	game_place[x+1][y] = 1;
	game_place[x][y+1] = 1;
	game_place[x][y+2] = 1;
}

void Fig_L_pos_4(int x, int y)  // вертикально  ___|
{

	game_place[x][y+2] = 1;
	game_place[x+1][y] = 1;
	game_place[x+1][y+1] = 1;
	game_place[x+1][y+2] = 1;
}

void InitFig_L(int postion)
{
	switch (postion)
	{
	case 1: // вертикально L
	{
		Fig_L_pos_1(0, 5);
		//game_place[0][5] = 1;
		//game_place[1][5] = 1;
		//game_place[2][5] = 1;
		//game_place[2][6] = 1;

	}break;
	case 2: // L Вверх нагами 
	{
		Fig_L_pos_2(0, 5);
		//game_place[0][4] = 1;
		//game_place[0][5] = 1;
		//game_place[1][5] = 1;
		//game_place[2][5] = 1;


	}break;

	case 3: //Горизонтально  ,===
	{
		Fig_L_pos_3(0, 4);
		//game_place[0][4] = 1;
		//game_place[1][4] = 1;
		//game_place[0][5] = 1;
		//game_place[0][6] = 1;

	}break;

	case 4: // вертикально  ___|
	{
		Fig_L_pos_4(0, 4);
		//game_place[0][6] = 1;
		//game_place[1][4] = 1;
		//game_place[1][5] = 1;
		//game_place[1][6] = 1;
	}break;
	}

}

void Fig_S_pos_1(int x, int y)  // вертикально S
{

	game_place[x][y] = 1;
	game_place[x+1][y] = 1;
	game_place[x+1][y+1] = 1;
	game_place[x+2][y+1] = 1;
}

void Fig_S_pos_2(int x, int y)  // гориз S 
{

	game_place[x][y+1] = 1;
	game_place[x][y+2] = 1;
	game_place[x+1][y] = 1;
	game_place[x+1][y+1] = 1;
}

void InitFig_S(int postion)
{
	switch (postion)
	{
	case 1: // вертикально S
	{
		Fig_S_pos_1(0, 5)
		//game_place[0][5] = 1;
		//game_place[1][5] = 1;
		//game_place[1][6] = 1;
		//game_place[2][6] = 1;

	}break;
	case 2: // гориз S 
	{
		Fig_S_pos_2(0, 4)
		//game_place[0][5] = 1;
		//game_place[0][6] = 1;
		//game_place[1][4] = 1;
		//game_place[1][5] = 1;


	}break;
	}
}

void Fig_Z_pos_1(int x, int y)  // вертикально Z
{

	game_place[x][y+1] = 1;
	game_place[x+1][y+1] = 1;
	game_place[x+1][y] = 1;
	game_place[x+2][y] = 1;
}

void Fig_Z_pos_2(int x, int y)  // гориз Z 
{

	game_place[x][y] = 1;
	game_place[x][y+1] = 1;
	game_place[x+1][y+1] = 1;
	game_place[x+1][y+2] = 1;
}

void InitFig_Z(int postion)
{
	switch (postion)
	{
	case 1: // вертикально Z
	{
		Fig_Z_pos_1(0, 4);
		//game_place[0][5] = 1;
		//game_place[1][5] = 1;
		//game_place[1][4] = 1;
		//game_place[2][4] = 1;

	}break;
	case 2: // гориз Z 
	{
		Fig_Z_pos_2(0, 4);
		//game_place[0][4] = 1;
		//game_place[0][5] = 1;
		//game_place[1][5] = 1;
		//game_place[1][6] = 1;


	}break;
	}
}

void Fig_T_pos_1(int x, int y)  // вертикально T
{

	game_place[x][y] = 1;
	game_place[x][y+1] = 1;
	game_place[x][y+2] = 1;
	game_place[x+1][y+1] = 1;
}

void Fig_T_pos_2(int x, int y)  // T Вверх нагами 
{

	game_place[x+1][y] = 1;
	game_place[x+1][y+1] = 1;
	game_place[x+1][y+2] = 1;
	game_place[x][y+1] = 1;
}

void Fig_T_pos_3(int x, int y)  //Горизонтально  |=
{

	game_place[x][y] = 1;
	game_place[x+1][y] = 1;
	game_place[x+2][y] = 1;
	game_place[x+1][y+1] = 1;
}

void Fig_T_pos_4(int x, int y)  // вертикально  =|
{

	game_place[x][y] = 1;
	game_place[x+1][y] = 1;
	game_place[x+2][y] = 1;
	game_place[x+1][y-1] = 1;
}

void InitFig_T(int postion)
{
	switch (postion)
	{
	case 1: // вертикально T
	{
		Fig_T_pos_1(0, 4);
		//game_place[0][4] = 1;
		//game_place[0][5] = 1;
		//game_place[0][6] = 1;
		//game_place[1][5] = 1;

	}break;
	case 2: // T Вверх нагами 
	{
		Fig_T_pos_2(0, 4);
		//game_place[1][4] = 1;
		//game_place[1][5] = 1;
		//game_place[1][6] = 1;
		//game_place[0][5] = 1;

	}break;

	case 3: //Горизонтально  |=
	{
		Fig_T_pos_3(0, 5);
		//game_place[0][5] = 1;
		//game_place[1][5] = 1;
		//game_place[2][5] = 1;
		//game_place[1][6] = 1;

	}break;

	case 4: // вертикально  =|
	{
		Fig_T_pos_4(0, 5);
		//game_place[0][5] = 1;
		//game_place[1][5] = 1;
		//game_place[2][5] = 1;
		//game_place[1][4] = 1;
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
