/*
	Игра тетрис
	учебный проект консельной версии игры тетрис
	(c) Protsenko Vyacheslav, Kitavina Nata, Sanzharovskiy Dmitriy, Karigin Roman, Frolov Dmitriy, bardin Valentin, Brantsev Vsevolod, Protsenko Mikhail, Starin Andrey
	(c) Computer academy "Step". Voronezh
	Version: 0.1 (04.03.2019)
*/

#include "pch.h" 
#include <iostream> 
#include <string>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <conio.h>

using namespace std;

const int ROW = 22;  //кол строк
const int COL = 12;  // кол столбцов

int score = 0; //счетчик очков
int temp;   //переменная для подсчета заполненности строки
int k = 0;   //подсчет заполненых строк

int game_place[ROW][COL] = {};   //игровое поле

bool Left;   //проверка слева фигуры на наличие 1
bool Right;  //проверка справа фигуры на наличие 1

bool low; //проверка низа фигуры на наличие 1
bool sides;  //Проверка стороны фигуры перед вращением

int coorY = 4; //стартовая координата Y для фигур

int find_X;   //первая координата найденой фигуры
int find_Y;

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

void Fig_I_pos_1(int x);//Горизонтально I //палка    ++++
void Fig_I_pos_2(int x);// вертикально I //палка
void InitFig_I(int x);

void InitFig_O(int x);// +++

void Fig_J_pos_1(int x); // вертикально J
void Fig_J_pos_2(int x); // J Вверх нагами
void Fig_J_pos_3(int x); //Горизонтально  |___
void Fig_J_pos_4(int x); // вертикально  ===,
void InitFig_J(int x);

void Fig_L_pos_1(int x, int y);  // вертикально L
void Fig_L_pos_2(int x, int y); // L Вверх нагами 
void Fig_L_pos_3(int x, int y);  //Горизонтально  ,===
void Fig_L_pos_4(int x, int y);  // вертикально  ___|
void InitFig_L(int postion);



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

bool GameCheckerLower(); //Проверка строки ниже на наличие объекта
bool GameCheckerSideRight(); //Проверка правой стороны фигуры на наличие объекта
bool GameCheckerSideLeft();  //Проверка левой стороны фигуры на наличие объекта

bool Checker_FigRotation(int Fig, int pos);  //Проверка стороны фигуры перед вращением

void Fig_Cleaner(); //Затирание прошлого положения фигуры
void Turner_1_2(); //Замена 2 фигуры на 1 после остановки фигуры

void CleanBufferGetch(); //клинер буфера клавы

void Find_Fig_in_place(); //функция поиска первой координаты фигуры

void PrintGame();// функция вывода фигуры на консоль
void Fig_step(int type);

int type = 3;
int pos = 1;

int main()
{
	setlocale(LC_ALL, ".866");

	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (i == 0 || i == ROW - 1) {
				game_place[i][j] = 1;
			}
			else if (j == 0 || j == COL - 1) {
				game_place[i][j] = 1;
			}
		}
	}
	/*pos = rand();*/

	do
	{
		Fig_step(type);

	} while (GameOver());
	PrintGame();
	cout << endl << "GAME OVER" << endl;
}

void CleanBufferGetch() {
	if (_kbhit()) {
		char ch = _getch();
	}
}

void Fig_step(int type)
{
	coorY = 4;
	switch (type)
	{
	case 1:
	{
		for (int i = 1; i < ROW - 1; i++)
		{
			InitFig_I(i);
			if (!GameCheckerLower())
			{
				InitFig_I(i);
				PrintGame();
				break;
			}
			PrintGame();
		}
		Turner_1_2();
	}
	break;
	case 2:
	{
		for (int i = 1; i < ROW - 1; i++)
		{
			InitFig_O(i);
			if (!GameCheckerLower())
			{
				InitFig_O(i);
				PrintGame();
				break;
			}
			PrintGame();
		}
		Turner_1_2();
	}
	break;
	case 3:
	{
		for (int i = 1; i < ROW - 1; i++)
		{
			InitFig_J(i);
			if (!GameCheckerLower())
			{
				InitFig_J(i);
				PrintGame();
				break;
			}
			PrintGame();
		}
		Turner_1_2();
	}
	break;
	case 4:
	{
		Turner_1_2();
	}
	break;
	}
}

void InitFig_I(int x)  //палка
{
	if (pos % 2 != 0)
	{
		if (pos > 4) {
			pos = 1;
		}
		Fig_I_pos_1(x);//Горизонтально === //палка
	}
	else if (pos % 2 == 0)
	{
		if (pos > 4) {
			pos = 2;
		}
		if (x > 1) {
			x--;
		}
		Fig_I_pos_2(x);// вертикально I //палка
	}
}

void Fig_I_pos_1(int x)//Горизонтально === //палка
{
	int stick = 1;
	CleanBufferGetch();
	Right = GameCheckerSideRight();//проверка слева фигуры на наличие 1
	Left = GameCheckerSideLeft();//проверка справа фигуры на наличие 1
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			if (Checker_FigRotation(stick,pos)==0) {
				break;
			}
			else {
				InitFig_I(x);
				coorY++;
				pos++;
				stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!Right)
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!Left)
			{
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0)
	{
		Fig_Cleaner();
		game_place[x][coorY] = 2;
		game_place[x][coorY + 1] = 2;
		game_place[x][coorY + 2] = 2;
		game_place[x][coorY + 3] = 2;
	}
}

void Fig_I_pos_2(int x)// вертикально I //палка
{
	int stick = 1;
	CleanBufferGetch();
	Right = GameCheckerSideRight();//проверка слева фигуры на наличие 1
	Left = GameCheckerSideLeft(); //проверка справа фигуры на наличие 1
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			if (Checker_FigRotation(stick, pos) == 0) {
				break;
			}
			else {
				InitFig_I(x);
				coorY--;
				pos++;
				stop = 1;
			}
		}break;
		case (char)77: // right
		{
			if (!Right)
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!Left)
			{
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0)
	{
		Fig_Cleaner();
		game_place[x][coorY] = 2;
		game_place[x + 1][coorY] = 2;
		game_place[x + 2][coorY] = 2;
		game_place[x + 3][coorY] = 2;
	}
}

void InitFig_O(int x)   //кубик
{
	CleanBufferGetch();
	Right = GameCheckerSideRight();//проверка слева фигуры на наличие 1
	Left = GameCheckerSideLeft(); //проверка справа фигуры на наличие 1
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)77: // right
		{
			if (!Right)
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!Left)
			{
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	Fig_Cleaner();
	game_place[x][coorY] = 2;
	game_place[x][coorY+1] = 2;
	game_place[x+1][coorY] = 2;
	game_place[x+1][coorY+1] = 2;
}

void InitFig_J(int x)
{
	if (pos == 1)
	{
		Fig_J_pos_1(x);// вертикально J
	}
	else if (pos == 2)
	{
		Fig_J_pos_2(x);//Горизонтально  |___
	}
	else if (pos == 3)
	{
		Fig_J_pos_3(x);// J Вверх нагами
	}
	else if (pos == 4)
	{
		Fig_J_pos_4(x);// вертикально  ===,
	}
}

void Fig_J_pos_1(int x) // вертикально J
{
	int J = 2;
	CleanBufferGetch();
	Right = GameCheckerSideRight();//проверка слева фигуры на наличие 1
	Left = GameCheckerSideLeft();//проверка справа фигуры на наличие 1
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			if (Checker_FigRotation(J, pos) == 0) {
				break;
			}
			else {
				coorY--;
				Fig_J_pos_2(x);
				pos++;
				stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!Right)
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!Left)
			{
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0)
	{
		Fig_Cleaner();
		game_place[x + 0][coorY] = 2;
		game_place[x + 1][coorY] = 2;
		game_place[x + 2][coorY] = 2;
		game_place[x + 2][coorY - 1] = 2;
	}
}

void Fig_J_pos_2(int x) //Горизонтально  |___
{
	int J = 2;
	CleanBufferGetch();
	Right = GameCheckerSideRight();//проверка слева фигуры на наличие 1
	Left = GameCheckerSideLeft();//проверка справа фигуры на наличие 1
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			if (Checker_FigRotation(J, pos) == 0) {
				break;
			}
			else {
				coorY++;
				Fig_J_pos_3(x);
				pos++;
				stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!Right)
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!Left)
			{
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0)
	{
		Fig_Cleaner();
		game_place[x][coorY] = 2;
		game_place[x + 1][coorY] = 2;
		game_place[x + 1][coorY + 1] = 2;
		game_place[x + 1][coorY + 2] = 2;
	}
}

void Fig_J_pos_3(int x) 
{
	int J = 2;
	CleanBufferGetch();
	Right = GameCheckerSideRight();//проверка слева фигуры на наличие 1
	Left = GameCheckerSideLeft();//проверка справа фигуры на наличие 1
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			if (Checker_FigRotation(J, pos) == 0) {
				break;
			}
			else {
				coorY--;
				Fig_J_pos_4(x);
				pos++;
				stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!Right)
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!Left)
			{
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0)
	{
	Fig_Cleaner();
	game_place[x][coorY + 1] = 2;
	game_place[x][coorY] = 2;
	game_place[x + 1][coorY] = 2;
	game_place[x + 2][coorY] = 2;
	}
}

void Fig_J_pos_4(int x) // вертикально  ===,
{
	int J = 2;
	CleanBufferGetch();
	Right = GameCheckerSideRight();//проверка слева фигуры на наличие 1
	Left = GameCheckerSideLeft();//проверка справа фигуры на наличие 1
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			if (Checker_FigRotation(J, pos) == 0) {
				break;
			}
			else {
				coorY++;
				pos = 1;
				Fig_J_pos_1(x);
				stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!Right)
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!Left)
			{
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0)
	{
		Fig_Cleaner();
		game_place[x][coorY + 2] = 2;
		game_place[x][coorY] = 2;
		game_place[x][coorY + 1] = 2;
		game_place[x + 1][coorY + 2] = 2;
	}
}

void Fig_L_pos_1(int x, int y) // вертикально L
{

	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y] = 1;
	game_place[x + 2][y + 1] = 1;
}

void Fig_L_pos_2(int x, int y) // L Вверх нагами 
{

	game_place[x][y - 1] = 1;
	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y] = 1;
}

void Fig_L_pos_3(int x, int y)  //Горизонтально  ,===
{

	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x][y + 1] = 1;
	game_place[x][y + 2] = 1;
}

void Fig_L_pos_4(int x, int y)  // вертикально  ___|
{

	game_place[x][y + 2] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 1][y + 1] = 1;
	game_place[x + 1][y + 2] = 1;
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
	game_place[x + 1][y] = 1;
	game_place[x + 1][y + 1] = 1;
	game_place[x + 2][y + 1] = 1;
}

void Fig_S_pos_2(int x, int y)  // гориз S 
{

	game_place[x][y + 1] = 1;
	game_place[x][y + 2] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 1][y + 1] = 1;
}

void InitFig_S(int postion)
{
	switch (postion)
	{
	case 1: // вертикально S
	{
		Fig_S_pos_1(0, 5);
		//game_place[0][5] = 1;
		//game_place[1][5] = 1;
		//game_place[1][6] = 1;
		//game_place[2][6] = 1;

	}break;
	case 2: // гориз S 
	{
		Fig_S_pos_2(0, 4);
		//game_place[0][5] = 1;
		//game_place[0][6] = 1;
		//game_place[1][4] = 1;
		//game_place[1][5] = 1;


	}break;
	}
}

void Fig_Z_pos_1(int x, int y)  // вертикально Z
{

	game_place[x][y + 1] = 1;
	game_place[x + 1][y + 1] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y] = 1;
}

void Fig_Z_pos_2(int x, int y)  // гориз Z 
{

	game_place[x][y] = 1;
	game_place[x][y + 1] = 1;
	game_place[x + 1][y + 1] = 1;
	game_place[x + 1][y + 2] = 1;
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
	game_place[x][y + 1] = 1;
	game_place[x][y + 2] = 1;
	game_place[x + 1][y + 1] = 1;
}

void Fig_T_pos_2(int x, int y)  // T Вверх нагами 
{

	game_place[x + 1][y] = 1;
	game_place[x + 1][y + 1] = 1;
	game_place[x + 1][y + 2] = 1;
	game_place[x][y + 1] = 1;
}

void Fig_T_pos_3(int x, int y)  //Горизонтально  |=
{

	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y] = 1;
	game_place[x + 1][y + 1] = 1;
}

void Fig_T_pos_4(int x, int y)  // вертикально  =|
{

	game_place[x][y] = 1;
	game_place[x + 1][y] = 1;
	game_place[x + 2][y] = 1;
	game_place[x + 1][y - 1] = 1;
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

//void StartFig(int type, int postion)
//{
//	switch (type)
//	{
//	case 1: InitFig_I(postion);
//	{
//
//
//	}break;
//	case 2: InitFig_J(postion);
//	{
//
//	}break;
//
//	case 3: InitFig_L(postion);
//	{
//
//	}break;
//
//	case 4: InitFig_O();
//	{
//
//	}break;
//
//	case 5: InitFig_S(postion);
//	{
//
//	}break;
//
//	case 6: InitFig_Z(postion);
//	{
//
//	}break;
//
//	case 7: InitFig_T(postion);
//	{
//
//	}break;
//
//	default:
//		break;
//	}
//}

void Find_Fig_in_place() //функция поиска первой координаты фигуры
{
	int stop=0;
	for (int i = 1; i < ROW - 1; i++)
	{
		for (int j = 1; j < COL - 1; j++)
		{
			if (game_place[i][j] == 2)
			{
				find_X=i;   //первая координата найденой фигуры
				find_Y=j;
				stop = 1;
				break;
			}
		}
		if (stop == 1) {
			break;
		}
	}
}

bool Checker_FigRotation(int Fig, int pos)  //Проверка стороны фигуры перед вращением
{
	sides = false;
	if (Fig==1 && pos==1)
	{
		Find_Fig_in_place();
		if (game_place[find_X + 2][find_Y] != 1 && game_place[find_X + 3][find_Y +1] != 1 && game_place[find_X +2][find_Y +1] != 1 && game_place[find_X +2][find_Y + 2] != 1 && game_place[find_X + 3][find_Y + 2] != 1)
		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 1 && pos == 2)
	{
		Find_Fig_in_place();
		if (game_place[find_X][find_Y - 2] != 1 && game_place[find_X][find_Y - 1] != 1 && game_place[find_X][find_Y + 1] != 1 && game_place[find_X][find_Y + 3] != 1 && game_place[find_X + 1][find_Y + 2] != 1)
		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 2 && pos == 1)
	{
		Find_Fig_in_place();
		if (game_place[find_X+1][find_Y-1] != 1 && game_place[find_X+1][find_Y] != 1 && game_place[find_X][find_Y + 1] != 1 && game_place[find_X][find_Y + 3] != 1 && game_place[find_X + 1][find_Y + 2] != 1)
		{
			return sides = true;
		}
		return sides;
	}
}

bool GameCheckerLower() //Проверка строки ниже на наличие объекта
{
	low = true; //проверка низа фигуры на наличие 1
	for (int i = 1; i < ROW - 1; i++)
	{
		for (int j = 1; j < COL - 1; j++)
		{
			if (game_place[i][j] == 2)
			{
				if (game_place[i + 1][j] == 1)
				{
					return low = false;
					break;
				}
			}
		}
	}
	return low;
}

bool GameCheckerSideRight() //Проверка правой стороны фигуры на наличие объекта
{
	Right = true;
	for (int i = 1; i < ROW - 1; i++)
	{
		for (int j = 1; j < COL - 1; j++)
		{
			if (game_place[i][j] == 2)
			{
				if (game_place[i][j + 1] == 2)
				{
					continue;
				}
				else if (game_place[i][j + 1] == 1)
				{
					Right = false;
					break;
				}
			}
		}
		if (Right == false)
		{
			break;
		}
	}
	return Right;
}

bool GameCheckerSideLeft()  //Проверка левой стороны фигуры на наличие объекта
{
	Left = true;
	for (int i = 0; i < ROW - 1; i++)
	{
		for (int j = 1; j < COL - 1; j++)
		{
			if (game_place[i][j] == 2)
			{
				if (game_place[i][j - 1] == 1)
				{
					Left = false;
					break;
				}
			}
		}
		if (Left == false)
		{
			break;
		}
	}
	return Left;
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
		if (RowFULL(i))
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
		if (RowFULL(i))
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
	for (int i = 1; i < COL-1; i++)
	{
		if (game_place[1][i] == 1)
		{
			return false;
		}
	}
	return true;
}

void PrintGame()
{
	system("cls");
	//for (int i = 0; i < ROW; i++)
	//{
	//	for (int j = 0; j < COL; j++)
	//	{
	//		if (i == 0 || i == ROW - 1) {
	//			game_place[i][j] = 1;
	//		}
	//		else if (j == 0 || j == COL - 1) {
	//			game_place[i][j] = 1;
	//		}
	//	}
	//}
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (game_place[i][j] == 0) {
				cout << " ";
			}
			else if (game_place[i][j] == 1) {
				cout << "1";
			}
			else if (game_place[i][j] == 2) {
				cout << "2";/*char(219);*/
			}
			else {

			}
		}
		cout << endl;
	}
	Sleep(100);
}

void Fig_Cleaner()
{
	int part = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (game_place[i][j] == 2)
			{
				game_place[i][j] = 0;
				part++;
			}
		}
		if (part == 8)
			break;
	}
}

void Turner_1_2()
{
	int part = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (game_place[i][j] == 2)
			{
				game_place[i][j] = 1;
				part++;
			}
		}
		if (part == 4)
			break;
	}
}





//void Fig_step(int type, int pos)
//{
//	switch (type)
//	{
//	case 1:
//	{
//		switch (pos)
//		{
//		case 1:
//		{
//			*Ystart = 4;
//			for (int i = 1; i < ROW; i++)
//			{
//				GameChecker();
//				if (*niz == 1)
//				{
//					break;
//				}
//
//				if (_kbhit()) {
//					switch (_getch())
//					{
//					case (char)77:  // право
//					{
//						if (*sprava == 1)
//						{
//							Fig_I_pos_1(i, *Ystart);
//						}
//						else {
//							*Ystart = *Ystart + 1;
//							Fig_I_pos_1(i, *Ystart);
//						}
//						//do {
//							//*Ystart = *Ystart + 1;
//							//Fig_I_pos_1(i, *Ystart);
//							//counter--;
//						//} while (counter != 0);
//					}
//					break;
//					case (char)75:  // лево
//
//						if (*sleva == 1)
//						{
//							Fig_I_pos_1(i, *Ystart);
//						}
//						else {
//							*Ystart = *Ystart - 1;
//							Fig_I_pos_1(i, *Ystart);
//						}
//						break;
//					}
//				}
//				else {
//					Fig_I_pos_1(i, *Ystart);
//				}
//			}
//			Turner_1_2();
//		}
//		break;
//		}
//	case 2:
//	{
//		*Ystart = 4;
//		for (int i = 1; i < ROW; i++)
//		{
//			GameChecker();
//			if (*niz == 1)
//			{
//				break;
//			}
//
//			if (_kbhit()) {
//				switch (_getch())
//				{
//				case (char)77:  // право
//				{
//					if (*sprava == 1)
//					{
//						Fig_I_pos_2(i, *Ystart);
//					}
//					else {
//						*Ystart = *Ystart + 1;
//						Fig_I_pos_2(i, *Ystart);
//					}
//					//do {
//						//*Ystart = *Ystart + 1;
//						//Fig_I_pos_1(i, *Ystart);
//						//counter--;
//					//} while (counter != 0);
//				}
//				break;
//				case (char)75:  // лево
//
//					if (*sleva == 1)
//					{
//						Fig_I_pos_2(i, *Ystart);
//					}
//					else {
//						*Ystart = *Ystart - 1;
//						Fig_I_pos_2(i, *Ystart);
//					}
//					break;
//				}
//			}
//			else {
//				Fig_I_pos_2(i, *Ystart);
//			}
//		}
//		Turner_1_2();
//	}
//	break;
//
//	}
//	break;
//	}
//
//}
