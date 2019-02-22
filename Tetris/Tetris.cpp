/*
	Игра "Тетрис"
	Учебный проект консольной версии игры "Тетрис"
	(с) Bardin Valentin, Starinin Andrey, Kitavina Natal'ya, Sanzharovskij Dmitry, Karygin Roman, Frolov Dmitry, Bryantsev Vsevolod, Ivutin Anton, Protsenko Vyacheslav,
	Protsenko Mikahil.
	(c) Компьютерная академия ШАГ Воронеж
	
	Версия: 0.1 (Февраль 2019 г.)
*/

#include <iostream>

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

void InitFig_I(int position);
void InitFig_J(int position);
void InitFig_L(int position);
void InitFig_O();
void InitFig_S(int position);
void InitFig_Z(int position);
void InitFig_T(int position);
void StartFig(int type, int position); // Описываем фигуры

bool RowFull(int row);			// Определение заполненности строки
int GameScore();				// Определение очков
void DeleteRow();				// Удаление заполенной строки

bool GameOver();				// Определение проигрыша

void Game();

int main() 
{
	Game();
}

void Fig_I_Poz1(int x, int y) // Фигура I, горизонтальное положение
{
	game_place[x][y] = 1;
	game_place[x][y+1] = 1;
	game_place[x][y+2] = 1;
	game_place[x][y+3] = 1;
}
void Fig_I_Poz2(int x, int y) // Фигура I, вертикальное положение
{
	game_place[x][y] = 1;
	game_place[x+1][y] = 1;
	game_place[x+2][y] = 1;
	game_place[x+3][y] = 1;
}

void Fig_J_Poz1(int x, int y)
{
	game_place[x][y] = 1;
	game_place[x+1][y] = 1;
	game_place[x+2][y-1] = 1;
	game_place[x+2][y] = 1;
}

void InitFig_I(int position) 
{
	switch (position) 
	{
		case 1: 
		{ // Горизонтальное положение
			Fig_I_Poz1(0, 3);		
		}
			break;
		case 2: 
		{ // Вертикальное положение
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
		{ // Вертикальное положение J
			Fig_J_Poz1(0,5);
		}
			break;
		case 2: 
		{ // Повернули на 90
			game_place[0][4] = 1;
			game_place[1][4] = 1;
			game_place[1][5] = 1;
			game_place[1][6] = 1;
		}
			break;
		case 3: 
		{ // Повернули на 90
			game_place[0][4] = 1;
			game_place[0][5] = 1;
			game_place[1][4] = 1;
			game_place[2][4] = 1;
		}
			break;
		case 4:
		{ // Повернули на 90
			game_place[0][4] = 1;
			game_place[0][5] = 1;
			game_place[0][6] = 1;
			game_place[1][6] = 1;
		}
			break;
	}
}

void InitFig_L(int position) 
{
	switch (position) 
	{
		case 1: 
		{ // Вертикальное положение L
			game_place[0][4] = 1;
			game_place[1][4] = 1;
			game_place[2][4] = 1;
			game_place[2][5] = 1;
		}
			break;
		case 2: 
		{ // Повернули на 90
			game_place[0][4] = 1;
			game_place[0][5] = 1;
			game_place[0][6] = 1;
			game_place[1][4] = 1;
		}
			break;
		case 3: 
		{ // Повернули на 90
			game_place[0][4] = 1;
			game_place[0][5] = 1;
			game_place[1][5] = 1;
			game_place[2][5] = 1;
		}
			break;
		case 4: 
		{ // Повернули на 90
			game_place[0][5] = 1;
			game_place[1][5] = 1;
			game_place[1][4] = 1;
			game_place[1][3] = 1;
		}
			break;
	}
}

void InitFig_O() 
{
	game_place[0][4] = 1;
	game_place[0][5] = 1;
	game_place[1][4] = 1;
	game_place[1][5] = 1;
}

void InitFig_S(int position) 
{
	switch (position) 
	{
		case 1: 
		{ // S
			game_place[0][5] = 1;
			game_place[0][6] = 1;
			game_place[1][5] = 1;
			game_place[1][4] = 1;
		}
			break;
		case 2: 
		{
			game_place[0][4] = 1;
			game_place[1][4] = 1;
			game_place[1][5] = 1;
			game_place[2][5] = 1;
		}
			break;
	}
}
void InitFig_Z(int position) 
{
	switch (position) 
	{
		case 1: 
		{ // Z
			game_place[0][4] = 1;
			game_place[0][5] = 1;
			game_place[1][5] = 1;
			game_place[1][6] = 1;
		}
			break;
		case 2:
		{
			game_place[0][5] = 1;
			game_place[1][5] = 1;
			game_place[1][4] = 1;
			game_place[2][4] = 1;
		}
			break;
	}
}
void InitFig_T(int position)
{
	switch (position) 
	{
		case 1: 
		{ // T
			game_place[0][4] = 1;
			game_place[0][5] = 1;
			game_place[0][6] = 1;
			game_place[1][5] = 1;
		}
			break;
		case 2: 
		{ // Повернули
			game_place[0][5] = 1;
			game_place[1][5] = 1;
			game_place[2][5] = 1;
			game_place[1][4] = 1;
		}
			break;
		case 3: 
		{ // Повернули
			game_place[0][5] = 1;
			game_place[1][4] = 1;
			game_place[1][5] = 1;
			game_place[1][6] = 1;
		}
			break;
		case 4: 
		{ // Повернули
			game_place[0][4] = 1;
			game_place[1][4] = 1;
			game_place[2][4] = 1;
			game_place[1][5] = 1;
		}
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

bool RowFull(int row) 
{
	temp = 0;
	for (int j = 0; j < COL; j++) 
	{
		temp += game_place[row][j];
	}

	if (temp == 10) 
	{
		return true;
	} else {
		return false;
	}
}

int GameScore() 
{
	int k = 0;	// Переменная для подсчета заполненных строк
	for (int i = 0; i < ROW; i++) 
	{	
		if (RowFull(i)) 
		{		// Если строка заполенная, то увеличиваем счетчик заполненых строк на 1
			k++;
		}
	}
// Добавление очков при полном заполнении строки 
	switch (k) 
	{
		case 1: 
		{
			return 100;			// При заполнении 1 строки 100 очков
			break;
		}
		case 2: 
		{
			return 300;			// При заполнении 2 строк 300 очков
			break;
		}
		case 3: 
		{
			return 700;			// При заполнении 3 строк 700 очков
			break;
		}
		case 4: 
		{
			return 1500;		// При заполнении 4 строк 1500 очков
			break;
		}
		default: 
		{
			return 0;
			break;
		}
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
