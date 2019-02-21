/*

Игра "Тетрис"
Учебный проект консольной версии игры "Тетрис"
(c)Ivutin Anton, Starinin Andrey, Kitavina Natl'ya, Sanzhrovskiy Dmitry, Karygin Roman, Frolov Dmitry, Bardin Valentin, Bryantsev Vsevolod, Protsenko Vyacheslav, Protsenko Michail.
(c)Компьтерная академия ШАГ. Воронеж

Версия: 0.1.(Февраль 2019 года.)

*/
#include<iostream>
#include<clocale>

using namespace std;

const int ROW = 20; //количество строк
const int COL = 10; //количество столбцов

int game_place[ROW][COL] = {}; //двумерный массив размерностью 20х10(игровое поле)

/*
Типы фигур:
    1-I (палка)
    2-J ()
    3-L ()
    4-O (квадрат)
    5-S ()
    6-Z ()
    7-T ()
*/

int score = 0; // подсчет очков
int temp; //временная переменная , для подсчета заполненности строки

void InitFig_I(int position);
void InitFig_J(int position);
void InitFig_L(int position);
void InitFig_O();
void InitFig_S(int position);
void InitFig_Z(int position);
void InitFig_T(int position);

void StartFig(int type, int position); //

bool RowFull(int row); // определение заполненности строки
int GameScore(); // определение очков
void DeleteRow(); // удаление заполненных строк

bool GameOver(); // определение проигрыша.

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
	case 2:  // вертикальное положение
	{
		game_place[0][5] = 1;
		game_place[1][5] = 1;
		game_place[2][5] = 1;
		game_place[3][5] = 1;
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
	case 2:InitFig_J(position);
		break;
	case 3:InitFig_L(position);
		break;
	case 4:InitFig_O();
		break;
	case 5:InitFig_S(position);
		break;
	case 6:InitFig_Z(position);
		break;
	case 7:InitFig_T(position);
		break;
	default:
		break;
	}
}
bool GameOver()
{
	//функция проверяет верхнюю строчку игрового поля на наличие в ней "1" (признак фигуры), если есть хоть одня,то проигрыш
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
	temp = 0;
	for (int j = 0; j < COL; j++)
	{
		temp = temp + game_place[row][j]; // 
	}
	if (temp == 10)
		return true;
	else
		return false;
}

int GameScore()
{
	
	int k = 0; // переменная, подсчет заполненных строк
	for (int i = 0; i < ROW; i++)
	{
		if (RowFull(i)) // если строка заполнена, то увеличиваем счетчик заполненных строк на 1
			k++;
	}
	switch (k)
	{
	case 1: return 100; // при заполнение одной строки дается 100 очков
		break;
	case 2: return 300; // при заполнение двух строк дается 300 очков
		break;
	case 3: return 700; // при заполнение трех строк дается 700 очков
		break;
	case 4: return 1500; // при заполнение четырех строк дается 1500 очков
		break;
	default:return 0; // 
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
					game_place[i][j] = game_place[i - 1][j];
				}
				m--;
			} while (m != 0);
			
		}
	}
}