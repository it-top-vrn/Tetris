/*
	Игра "Тетрис"
	Учебный проект консольной версии игры "Тетрис"
	(с) Bardin Valentin, Starinin Andrey, Kitavina Natal'ya, Sanzharovskij Dmitry, Karygin Roman, Frolov Dmitry, Bryantsev Vsevolod, Ivutin Anton, Protsenko Vyacheslav,
	Protsenko Mikahil.
	(c) Компьютерная академия ШАГ Воронеж
	Версия 0.2
*/

#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

const int ROW = 20;				// Кол-во строк
const int COL = 10;				// Кол-во столбцов

int game_place[ROW][COL]{};		// Объявляем массив размером 20x10 (игровое поле) и инициализировали его 0

int score = 0;					// Подсчет очков
int temp;						// Переменная, для подсчета заполненности строки

int init = 1; // переменная для отображения фигуры
int del = 0; // переменная для удаления фигуры

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

/* 
	Создание фигур или их затирание
	x - координата по вертикали (строки)
	y - координата по горизонтали (столбцы)
	d - то, чем заполняется (либо "0", либо "1")
*/

void Fig_I_Poz1(int x, int y, int d);
void Fig_I_Poz2(int x, int y, int d);

void Fig_J_Poz1(int x, int y, int d);
void Fig_J_Poz2(int x, int y, int d);
void Fig_J_Poz3(int x, int y, int d);
void Fig_J_Poz4(int x, int y, int d);

void Fig_L_Poz1(int x, int y, int d);
void Fig_L_Poz2(int x, int y, int d);
void Fig_L_Poz3(int x, int y, int d);
void Fig_L_Poz4(int x, int y, int d);

void Fig_O_Poz(int x, int y, int d);

void Fig_Z_Poz1(int x, int y, int d);
void Fig_Z_Poz2(int x, int y, int d);

void Fig_S_Poz1(int x, int y, int d);
void Fig_S_Poz2(int x, int y, int d);

void Fig_T_Poz1(int x, int y, int d);
void Fig_T_Poz2(int x, int y, int d);
void Fig_T_Poz3(int x, int y, int d);
void Fig_T_Poz4(int x, int y, int d);

void InitFig_I(int position);
void InitFig_J(int position);
void InitFig_L(int position);
void InitFig_O();
void InitFig_S(int position);
void InitFig_Z(int position);
void InitFig_T(int position);
void StartFig(int type, int position); // Фигуры на старте

// "Падение" фигур вниз
void StepFig_I(int position, int x, int y);
void StepFig(int type, int position, int x, int y);

bool RowFull(int row);			// Определение заполненности строки
int  GameScore();				// Определение очков
void DeleteRow();				// Удаление заполенной строки

bool GameOver();				// Определение проигрыша

void Game();

int main()
{
	setlocale(LC_ALL, ".866");
}

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
/*
	Создание фигур или их затирание
	x - координата по вертикали (строки)
	y - координата по горизонтали (столбцы)
	d - то, чем заполняется (либо "0", либо "1")
*/
void Fig_I_Poz1(int x, int y, int d)
{
	game_place[x][y] = d;
	game_place[x][y + 1] = d;
	game_place[x][y + 2] = d;
	game_place[x][y + 3] = d;
}
void Fig_I_Poz2(int x, int y, int d)
{
	game_place[x][y] = d;
	game_place[x + 1][y] = d;
	game_place[x + 2][y] = d;
	game_place[x + 3][y] = d;
}

void Fig_J_Poz1(int x, int y, int d)
{
	game_place[x][y] = d;
	game_place[x + 1][y] = d;
	game_place[x + 2][y] = d;
	game_place[x + 2][y - 1] = d;
}
void Fig_J_Poz2(int x, int y, int d)
{
	game_place[x][y] = d;
	game_place[x + 1][y] = d;
	game_place[x + 1][y + 1] = d;
	game_place[x + 1][y + 2] = d;
}
void Fig_J_Poz3(int x, int y, int d)
{
	game_place[x][y] = d;
	game_place[x][y + 1] = d;
	game_place[x + 1][y] = d;
	game_place[x + 2][y] = d;
}
void Fig_J_Poz4(int x, int y, int d)
{
	game_place[x][y] = d;
	game_place[x][y + 1] = d;
	game_place[x][y + 2] = d;
	game_place[x + 1][y + 2] = d;
}

void Fig_L_Poz1(int x, int y, int d)
{}
void Fig_L_Poz2(int x, int y, int d)
{}
void Fig_L_Poz3(int x, int y, int d)
{}
void Fig_L_Poz4(int x, int y, int d)
{}

void Fig_O_Poz(int x, int y, int d)
{}

void Fig_Z_Poz1(int x, int y, int d)
{}
void Fig_Z_Poz2(int x, int y, int d)
{}

void Fig_S_Poz1(int x, int y, int d)
{}
void Fig_S_Poz2(int x, int y, int d)
{}

void Fig_T_Poz1(int x, int y, int d)
{}
void Fig_T_Poz2(int x, int y, int d)
{}
void Fig_T_Poz3(int x, int y, int d)
{}
void Fig_T_Poz4(int x, int y, int d)
{}

// Фигуры на старте
void InitFig_I(int position)
{
	switch (position)
	{
	case 1: Fig_I_Poz1(0, 3, init);
		break;
	case 2: Fig_I_Poz2(0, 5, init);
		break;
	}
}

void InitFig_J(int position)
{
	switch (position)
	{
	case 1:	Fig_J_Poz1(0, 5, init);
		break;
	case 2:	Fig_J_Poz2(0, 5, init);
		break;
	case 3:	Fig_J_Poz3(0, 5, init);
		break;
	case 4:	Fig_J_Poz4(0, 5, init);
		break;
	}
}

void InitFig_L(int position)
{
	switch (position)
	{
	case 1:	Fig_L_Poz1(0, 5);
		break;
	case 2:	Fig_L_Poz2(0, 5);
		break;
	case 3:	Fig_L_Poz3(0, 5);
		break;
	case 4:	Fig_L_Poz4(0, 5);
		break;
	}
}
void InitFig_O()
{
	Fig_O_Poz(0, 5);
}

void InitFig_S(int position)
{
	switch (position)
	{
	case 1:	Fig_S_Poz1(0, 5);
		break;
	case 2:	Fig_S_Poz2(0, 5);
		break;
	}
}

void InitFig_Z(int position)
{
	switch (position)
	{
	case 1:	Fig_Z_Poz1();
		break;
	case 2:	Fig_Z_Poz2();
		break;
	}
}

void InitFig_T(int position)
{
	switch (position)
	{
	case 1:	Fig_T_Poz1();
		break;
	case 2:	Fig_T_Poz2();
		break;
	case 3:	Fig_T_Poz3();
		break;
	case 4:	Fig_T_Poz4();
		break;
	}
}

// Выбор фигуры и её конфигурации
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

// "Падение" фигур вниз

void StepFig_I(int position, int x, int y)
{
	switch (position)
	{
		case 1:
		{
			Fig_I_Poz1(x-1, y, del);
			Fig_I_Poz1(x, y, init);
		}
			break;
		case 2:
		{
			Fig_I_Poz2(x-1, y, del);
			Fig_I_Poz2(x, y, init);
		}
			break;
	}
}
void StepFig(int type, int position, int x, int y)
{
	switch (type)
	{
		case 1: StepFig_I(position, x, y);
			break;
		case 2: StepFig_J(position, x, y);
			break;
		case 3: StepFig_L(position, x, y);
			break;
		case 4: StepFig_O(x, y);
			break;
		case 5: StepFig_S(position, x, y);
			break;
		case 6: StepFig_Z(position, x, y);
			break;
		case 7: StepFig_T(position, x, y);
			break;
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
