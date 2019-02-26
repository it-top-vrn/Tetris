/*
	Игра "Тетрис"
	Учебный проект консольной версии игры "Тетрис"
	(c) Bryantsev Vsevolod, Kitavina Natal'ia, Sanzharovskiy Dmitriy, Karygin Roman, Frolov Dmitriy, Bardin Valentin, Ivutin Anton, Protsenko Vyacheslav, Protsenko Mikhael, Starinin Andrey
	(c) Компьютерная академия ШАГ. Воронеж

	V0.1 (Февраль 2019)
*/
#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <time.h>
using namespace std;
const int ROW = 20; // количество строк
const int COL = 10; // количество столбцов
int game_place[ROW][COL] = {}; // двумерный массив - игровое поле
/*
Типы фигур: 
1 - I
2 - J
3 - L
4 - O
5 - S
6 - Z 
7 - T
*/
int score = 0; // переменная для подсчета очков во время игры
int temp; // временная переменная, для подсчета заполненности строки
void InitFig_I(int position);
void InitFig_J(int position);
void InitFig_L(int position);
void InitFig_O();
void InitFig_S(int position);
void InitFig_Z(int position);
void InitFig_T(int position);
void StartFig(int type, int position);
bool GameOver(); // функция определения проигрыша
bool RowFull(int row); // функция определения заполненности строки
int GameScore(); // функция определения очков
void DeleteRow(); // функция очистки строки
int main()
{
    
}
void Fig_I_Poz1(int x, int y) // фигура I, горизонтальное положение
{
	game_place[x][y] = 1;
	game_place[x][y + 1] = 1;
	game_place[x][y + 2] = 1;
	game_place[x][y + 3] = 1;
}
void Fig_I_Poz2(int x, int y) // фигура I, вертикальное положение
{
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y] = 1;
	game_place[x + 3][y] = 1;
}
void Fig_J_Poz1(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y - 1] = 1;
	game_place[x + 2][y] = 1;
}
void Fig_J_Poz2(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 1][y + 1] = 1;
	game_place[x + 1][y + 2] = 1;
}
void Fig_J_Poz3(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x][y + 1] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y] = 1;
}
void Fig_J_Poz4(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x][y + 1] = 1;
	game_place[x][y + 2] = 1;
	game_place[x + 1][y + 2] = 1;
}
void Fig_L_Poz1(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y] = 1;
	game_place[x + 2][y + 1] = 1;
}
void Fig_L_Poz2(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x][y + 1] = 1;
	game_place[x][y + 2] = 1;
	game_place[x + 1][y] = 1;
}
void Fig_L_Poz3(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x][y + 1] = 1;
	game_place[x + 1][y + 1] = 1;
	game_place[x + 2][y + 1] = 1;
}
void Fig_L_Poz4(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 1][y - 1] = 1;
	game_place[x + 1][y - 2] = 1;
}
void Fig_O_Poz(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x][y + 1] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 1][y + 1] = 1;
}
void Fig_S_Poz1(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x][y - 1] = 1;
	game_place[x + 1][y - 1] = 1;
	game_place[x + 1][y - 2] = 1;
}
void Fig_S_Poz2(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 1][y + 1] = 1;
	game_place[x + 2][y + 1] = 1;
}
void Fig_Z_Poz1(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x][y + 1] = 1;
	game_place[x + 1][y + 1] = 1;
	game_place[x + 1][y + 2] = 1;
}
void Fig_Z_Poz2(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 1][y - 1] = 1;
	game_place[x + 2][y - 1] = 1;
}
void Fig_T_Poz1(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x][y + 1] = 1;
	game_place[x][y + 2] = 1;
	game_place[x + 1][y + 1] = 1;
}
void Fig_T_Poz2(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 1][y + 1] = 1;
	game_place[x + 1][y + 2] = 1;
}
void Fig_T_Poz3(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y] = 1;
	game_place[x + 1][y - 1] = 1;
}
void Fig_T_Poz4(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y] = 1;
	game_place[x + 1][y + 1] = 1;
}
void InitFig_I(int position)
{
	switch (position)
	{
	case 1: // горизонтальное положение
	{
		Fig_I_Poz1(0, 3);
	}
		break;
	case 2: // вертикальное положение
	{
		Fig_I_Poz2(0, 5);
	}
		break;
	}
}
void InitFig_J(int position)
{
	switch (position)
	{
	case 1:
	{
		Fig_J_Poz1(0, 5);
	}
	break;
	case 2:
	{
		Fig_J_Poz2(0, 4);
	}
	break;
	case 3:
	{
		Fig_J_Poz3(0, 4);
	}
	break;
	case 4:
	{
		Fig_J_Poz4(0, 3);
	}
	break;
	}
}
void InitFig_L(int position)
{
	switch (position)
	{
	case 1:
	{
		Fig_L_Poz1(0, 5);
	}
	break;
	case 2:
	{
		Fig_L_Poz2(0, 4);
	}
	break;
	case 3:
	{
		Fig_L_Poz3(0, 4);
	}
	break;
	case 4:
	{
		Fig_L_Poz4(0, 6);
	}
	break;
	}
}
void InitFig_O()
{
	Fig_O_Poz(0, 4);
}
void InitFig_S(int position)
{
	switch (position)
	{
	case 1:
	{
		Fig_S_Poz1(0, 6);
	}
	break;
	case 2:
	{
		Fig_S_Poz2(0, 4);
	}
	break;
	}
}
void InitFig_Z(int position)
{
	switch (position)
	{
	case 1:
	{
		Fig_Z_Poz1(0, 4);
	}
	break;
	case 2:
	{
		Fig_Z_Poz2(0, 6);
	}
	break;
	}
}
void InitFig_T(int position)
{
	switch (position)
	{
	case 1:
	{
		Fig_T_Poz1(0, 4);
	}
	break;
	case 2:
	{
		Fig_T_Poz2(0, 4);
	}
	break;
	case 3:
	{
		Fig_T_Poz3(0, 5);
	}
	break;
	case 4:
	{
		Fig_T_Poz4(0, 4);
	}
	break;
	}
}
void StartFig(int type, int position)
{
	switch (type)
	{
	case 1:
		InitFig_I(position);
		break;
	case 2:
		InitFig_J(position);
		break;
	case 3:
		InitFig_L(position);
		break;
	case 4:
		InitFig_O();
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
						if (i >= 1)
						{
							Fig_I_Poz1_Delete(i - 1, 3);
						}
						Fig_I_Poz1(i, 3);
					}
					break;
				}	
				case 2:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_I_Poz2_Delete(i - 1, 5);
						}
						Fig_I_Poz2(i, 5);
					}
					break;
				}
			}
			break;
		}
		case 2:
		{
			switch (poz)
			{
				case 1:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_J_Poz1_Delete(i - 1, 5);
						}
						Fig_J_Poz1(i, 5);
					}
					break;
				}
				case 2:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_J_Poz2_Delete(i - 1, 4);
						}
						Fig_J_Poz2(i, 4);
					}
					break;
				}
				case 3:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_J_Poz3_Delete(i - 1, 4);
						}
						Fig_J_Poz3(i, 4);
					}
					break;
				}
				case 4:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_J_Poz4_Delete(i - 1, 3);
						}
						Fig_J_Poz4(i, 3);
					}
					break;
				}
			}
			break;
		}
		case 3:
		{
			switch (poz)
			{
				case 1:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_L_Poz1_Delete(i - 1, 5);
						}
						Fig_L_Poz1(i, 5);
					}
					break;
				}
				case 2:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_L_Poz2_Delete(i - 1, 4);
						}
						Fig_L_Poz2(i, 4);
					}
					break;
				}
				case 3:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_L_Poz3_Delete(i - 1, 4);
						}
						Fig_L_Poz3(i, 4);
					}
					break;
				}
				case 4:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_L_Poz4_Delete(i - 1, 6);
						}
						Fig_L_Poz4(i, 6);
					}
					break;
				}
			}
			break;
		}
		case 4:
		{
			switch (poz)
			{
				case 1:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_O_Poz_Delete(i - 1, 4);
						}
						Fig_O_Poz(i, 4);
					}
					break;
				}
			}
			break;
		}
		case 5:
		{
			switch (poz)
			{
				case 1:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_S_Poz1_Delete(i - 1, 6);
						}
						Fig_S_Poz1(i, 6);
					}
					break;
				}
				case 2:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_S_Poz2_Delete(i - 1, 4);
						}
						Fig_S_Poz2(i, 4);
					}
					break;
				}
			}
			break;
		}
		case 6:
		{
			switch (poz)
			{
				case 1:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_Z_Poz1_Delete(i - 1, 4);
						}
						Fig_Z_Poz1(i, 4);
					}
					break;
				}
				case 2:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_Z_Poz2_Delete(i - 1, 6);
						}
						Fig_Z_Poz2(i, 6);
					}
					break;
				}
			}
			break;
		}
		case 7:
		{
			switch (poz)
			{
				case 1:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_T_Poz1_Delete(i - 1, 4);
						}
						Fig_T_Poz1(i, 4);
					}
					break;
				}
				case 2:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_T_Poz2_Delete(i - 1, 4);
						}
						Fig_T_Poz2(i, 4);
					}
					break;
				}
				case 3:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_T_Poz3_Delete(i - 1, 5);
						}
						Fig_T_Poz3(i, 5);
					}
					break;
				}
				case 4:
				{
					for (int i = 0; i < ROW; i++)
					{
						if (i >= 1)
						{
							Fig_T_Poz4_Delete(i - 1, 4);
						}
						Fig_T_Poz4(i, 4);
					}
					break;
				}
			}
			break;
		}
	}
}
bool GameOver() 
{
	// функция проверяет верхнюю строку массива, если хотя бы один ее элемент будет равен "1", то игра закончится
	for (int i = 0; i < COL; i++)
	{
		if (game_place[0][i] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool RowFull(int row)
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
int GameScore()
{
	int k = 0; // переменная для подсчета заполненных строк
	for (int i = 0; i < ROW; i++)
	{
		
		if (RowFull(i)) // если строка заполнена, то увеличиваем счетчик заполненных строк на 1
		{
			k++;
		}
	}
	switch (k)
	{
	case 1:
		return 100; // при заполнении одной строки дается + 100 очков
		break;
	case 2:
		return 300; // при заполнении двух строк дается + 300 очков
		break;
	case 3:
		return 700; // при заполнении трех строк дается + 700 очков
		break;
	case 4: 
		return 1500; // при заполнении четырех строк дается + 1500 очков
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
// функция рандомного выбора фигуры
int FigureNumber()
{
	srand(time(0));
	int number = rand() % 7 + 1;
	return number;
}
// функция рандомного выбора позиции фигуры
int FigurePositionNumber()
{
	srand(time(0));
	int number = 0;
	switch (FigureNumber())
	{
	case 1:
		number = rand() % 2 + 1;
		break;
	case 2:
		number = rand() % 4 + 1;
		break;
	case 3:
		number = rand() % 4 + 1;
		break;
	case 4:
		number = 1;
		break;
	case 5:
		number = rand() % 2 + 1;
		break;
	case 6:
		number = rand() % 2 + 1;
		break;
	case 7:
		number = rand() % 4 + 1;
		break;
	}
}
void Fig_I_Poz1_Delete(int x, int y) 
{
	game_place[x][y] = 0;
	game_place[x][y + 1] = 0;
	game_place[x][y + 2] = 0;
	game_place[x][y + 3] = 0;
}
void Fig_I_Poz2_Delete(int x, int y) 
{
	game_place[x][y] = 0;
	game_place[x + 1][y] = 0;
	game_place[x + 2][y] = 0;
	game_place[x + 3][y] = 0;
}
void Fig_J_Poz1_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x + 1][y] = 0;
	game_place[x + 2][y - 1] = 0;
	game_place[x + 2][y] = 0;
}
void Fig_J_Poz2_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x + 1][y] = 0;
	game_place[x + 1][y + 1] = 0;
	game_place[x + 1][y + 2] = 0;
}
void Fig_J_Poz3_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x][y + 1] = 0;
	game_place[x + 1][y] = 0;
	game_place[x + 2][y] = 0;
}
void Fig_J_Poz4_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x][y + 1] = 0;
	game_place[x][y + 2] = 0;
	game_place[x + 1][y + 2] = 0;
}
void Fig_L_Poz1_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x + 1][y] = 0;
	game_place[x + 2][y] = 0;
	game_place[x + 2][y + 1] = 0;
}
void Fig_L_Poz2_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x][y + 1] = 0;
	game_place[x][y + 2] = 0;
	game_place[x + 1][y] = 0;
}
void Fig_L_Poz3_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x][y + 1] = 0;
	game_place[x + 1][y + 1] = 0;
	game_place[x + 2][y + 1] = 0;
}
void Fig_L_Poz4_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x + 1][y] = 0;
	game_place[x + 1][y - 1] = 0;
	game_place[x + 1][y - 2] = 0;
}
void Fig_O_Poz_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x][y + 1] = 0;
	game_place[x + 1][y] = 0;
	game_place[x + 1][y + 1] = 0;
}
void Fig_S_Poz1_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x][y - 1] = 0;
	game_place[x + 1][y - 1] = 0;
	game_place[x + 1][y - 2] = 0;
}
void Fig_S_Poz2_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x + 1][y] = 0;
	game_place[x + 1][y + 1] = 0;
	game_place[x + 2][y + 1] = 0;
}
void Fig_Z_Poz1_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x][y + 1] = 0;
	game_place[x + 1][y + 1] = 0;
	game_place[x + 1][y + 2] = 0;
}
void Fig_Z_Poz2_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x + 1][y] = 0;
	game_place[x + 1][y - 1] = 0;
	game_place[x + 2][y - 1] = 0;
}
void Fig_T_Poz1_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x][y + 1] = 0;
	game_place[x][y + 2] = 0;
	game_place[x + 1][y + 1] = 0;
}
void Fig_T_Poz2_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x + 1][y] = 0;
	game_place[x + 1][y + 1] = 0;
	game_place[x + 1][y + 2] = 0;
}
void Fig_T_Poz3_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x + 1][y] = 0;
	game_place[x + 2][y] = 0;
	game_place[x + 1][y - 1] = 0;
}
void Fig_T_Poz4_Delete(int x, int y)
{
	game_place[x][y] = 0;
	game_place[x + 1][y] = 0;
	game_place[x + 2][y] = 0;
	game_place[x + 1][y + 1] = 0;
}