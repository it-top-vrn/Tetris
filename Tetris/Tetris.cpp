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
#include <ctime>
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

void Fig_I_pos_1(int x);//Горизонтально I //палка    ++++
void Fig_I_pos_2(int x);// вертикально I //палка
void InitFig_I(int x);

void InitFig_O(int x);// +++

void Fig_J_pos_1(int x); // вертикально J
void Fig_J_pos_2(int x); // J Вверх нагами
void Fig_J_pos_3(int x); //Горизонтально  |___
void Fig_J_pos_4(int x); // вертикально  ===,
void InitFig_J(int x);

void Fig_L_pos_1(int x);  // вертикально L
void Fig_L_pos_2(int x); // L Вверх нагами 
void Fig_L_pos_3(int x);  //Горизонтально  ,===
void Fig_L_pos_4(int x);  // вертикально  ___|
void InitFig_L(int x);

void Fig_S_pos_1(int x);  // вертикально S
void Fig_S_pos_2(int x);  // гориз S 
void InitFig_S(int x);

void Fig_Z_pos_1(int x);  // вертикально Z
void Fig_Z_pos_2(int x);  // гориз Z 
void InitFig_Z(int x);

void Fig_T_pos_1(int x);  // вертикально T
void Fig_T_pos_2(int x);  // вертикально  =|
void Fig_T_pos_3(int x);  // T Вверх нагами 
void Fig_T_pos_4(int x);  // Горизонтально  |=
void InitFig_T(int x);

void StartFig(int type, int postion);

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
int GameScare();  // подсчет очков

void PrintGame();// функция вывода фигуры на консоль
void Fig_step(int type);
int gobal_coor_X;
int type;
int pos;

int main()
{
	setlocale(LC_ALL, ".866");
	srand(time(NULL));
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

	do
	{
		type = 7;//rand()%7+1;
		pos = rand()%4+1;
		Fig_step(type);
		GameScare();
	} while (GameOver());
	PrintGame();
	cout << "Scare = " << k << endl;
	cout << endl << "GAME OVER" << endl;
}

void CleanBufferGetch() {
	if (_kbhit()) {
		char ch = _getch();
	}
}

void Fig_step(int type)
{
	coorY = 5;
	switch (type)
	{
	case 1:
	{
		coorY--;
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
	}	break;
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
	}	break;
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
	}	break;
	case 4:
	{
		for (int i = 1; i < ROW - 1; i++) {
			InitFig_L(i);
			if (!GameCheckerLower())
				break;
			PrintGame();
		}	
		PrintGame();
		Turner_1_2();
	}	break;
	case 5:
	{
		for (int i = 1; i < ROW - 1; i++) {
			InitFig_S(i);
			if (!GameCheckerLower())
				break;
			PrintGame();
		}
		PrintGame();
		Turner_1_2();
	}	break;
	case 6:
	{
		for (int i = 1; i < ROW - 1; i++) {
			InitFig_Z(i);
			if (!GameCheckerLower())
				break;
			PrintGame();
		}
		PrintGame();
		Turner_1_2();
	}	break;
	case 7:
	{
		for (int i = 1; i < ROW - 1; i++) {
			gobal_coor_X = i;
			InitFig_T(i);
			i=gobal_coor_X;
			if (!GameCheckerLower())
				break;
			PrintGame();
		}
		PrintGame();
		Turner_1_2();
	}	break;
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
			if (Checker_FigRotation(stick, pos) == 0) {
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
	game_place[x][coorY + 1] = 2;
	game_place[x + 1][coorY] = 2;
	game_place[x + 1][coorY + 1] = 2;
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
		game_place[x + 0][coorY+1] = 2;
		game_place[x + 1][coorY+1] = 2;
		game_place[x + 2][coorY+1] = 2;
		game_place[x + 2][coorY] = 2;
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
		game_place[x][coorY+1] = 2;
		game_place[x + 1][coorY+1] = 2;
		game_place[x + 1][coorY + 2] = 2;
		game_place[x + 1][coorY + 3] = 2;
	}
}

void Fig_J_pos_3(int x) // J Вверх нагами
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
		game_place[x][coorY + 2] = 2;
		game_place[x][coorY+1] = 2;
		game_place[x + 1][coorY+1] = 2;
		game_place[x + 2][coorY+1] = 2;
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
		game_place[x][coorY + 3] = 2;
		game_place[x][coorY+1] = 2;
		game_place[x][coorY + 2] = 2;
		game_place[x + 1][coorY + 3] = 2;
	}
}

void InitFig_L(int x)
{
	if (pos == 1)
	{
		Fig_L_pos_1(x); // вертикально L
	}
	else if (pos == 2)
	{
		Fig_L_pos_2(x); //Горизонтально  ,===
	}
	else if (pos == 3)
	{
		Fig_L_pos_3(x); // L Вверх нагами
	}
	else if (pos == 4)
	{
		Fig_L_pos_4(x);  // вертикально  ___|
	}
}

void Fig_L_pos_1(int x) // вертикально L
{
	int L = 3;
	CleanBufferGetch();
	//Right = GameCheckerSideRight();//проверка слева фигуры на наличие 1
	//Left = GameCheckerSideLeft();//проверка справа фигуры на наличие 1
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			pos++;
			if (Checker_FigRotation(L, pos) == 0) {
				pos--;
				break;
			}
			else {
				Fig_L_pos_2(x);
				stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!GameCheckerSideRight()) //проверка слева фигуры на наличие 1
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!GameCheckerSideLeft()){ //проверка справа фигуры на наличие 1
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0){
		if (x == 1) x++;
		Fig_Cleaner();
		game_place[x-1][coorY] = 2;
		game_place[x][coorY] = 2;
		game_place[x + 1][coorY] = 2;
		game_place[x + 1][coorY + 1] = 2;
	}
}

void Fig_L_pos_2(int x)  //Горизонтально  ,===
{
	int L = 3;
	CleanBufferGetch();
	//Right = GameCheckerSideRight();//проверка слева фигуры на наличие 1
	//Left = GameCheckerSideLeft();//проверка справа фигуры на наличие 1
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			pos++;
			if (Checker_FigRotation(L, pos) == 0) {
				pos--;
				break;
			}
			else {
				Fig_L_pos_3(x);
				stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!GameCheckerSideRight()) //проверка слева фигуры на наличие 1
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!GameCheckerSideLeft()) { //проверка справа фигуры на наличие 1
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[x][coorY] = 2;
		game_place[x][coorY-1] = 2;
		game_place[x+1][coorY-1] = 2;
		game_place[x][coorY + 1] = 2;
	}
}

void Fig_L_pos_3(int x) // L Вверх нагами 
{
	int L = 3;
	CleanBufferGetch();
	//Right = GameCheckerSideRight();//проверка слева фигуры на наличие 1
	//Left = GameCheckerSideLeft();//проверка справа фигуры на наличие 1
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			pos++;
			if (Checker_FigRotation(L, pos) == 0) {
				pos--;
				break;
			}
			else {
				Fig_L_pos_4(x-1);
				stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!GameCheckerSideRight()) //проверка слева фигуры на наличие 1
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!GameCheckerSideLeft()) { //проверка справа фигуры на наличие 1
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0) {
		if (x == 1) x++;
		Fig_Cleaner();
		game_place[x][coorY] = 2;
		game_place[x - 1][coorY] = 2;
		game_place[x - 1][coorY - 1] = 2;
		game_place[x + 1][coorY] = 2;
	}
}

void Fig_L_pos_4(int x)  // вертикально  ___|
{
	int L = 3;
	CleanBufferGetch();
	//Right = GameCheckerSideRight();//проверка слева фигуры на наличие 1
	//Left = GameCheckerSideLeft();//проверка справа фигуры на наличие 1
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			pos = 1;
			if (Checker_FigRotation(L, pos) == 0) {
				pos = 4;
				break;
			}
			else {
				Fig_L_pos_1(x-1);
				stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!GameCheckerSideRight()) //проверка слева фигуры на наличие 1
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!GameCheckerSideLeft()) { //проверка справа фигуры на наличие 1
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0) {
		if (x == 1) x++;
		Fig_Cleaner();
		game_place[x][coorY] = 2;
		game_place[x-1][coorY+1] = 2;
		game_place[x][coorY + 1] = 2;
		game_place[x][coorY -1] = 2;
	}
}

void InitFig_S(int x)
{
	if (pos % 2 != 0)
	{
		if (pos > 4) {
			pos = 1;
		}
		Fig_S_pos_1(x);// вертикально S
	}
	else if (pos % 2 == 0)
	{
		if (pos > 4) {
			pos = 2;
		}
		if (x > 1) {
			x--;
		}
		Fig_S_pos_2(x);// гориз S 
	}
}

void Fig_S_pos_1(int x)  // вертикально S
{
	int S = 4;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			pos = 2;
			if (Checker_FigRotation(S, pos) == 0) {
				pos = 1;
				break;
			}
			else {
				Fig_S_pos_2(x-1);
				stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!GameCheckerSideRight()) //проверка слева фигуры на наличие 1
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!GameCheckerSideLeft()) { //проверка справа фигуры на наличие 1
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[x][coorY] = 2;
		game_place[x + 1][coorY] = 2;
		game_place[x+1][coorY + 1] = 2;
		game_place[x + 2][coorY + 1] = 2;
	}
}

void Fig_S_pos_2(int x)  // гориз S 
{
	int S = 4;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
			case (char)72:
			{
				pos = 1;
				if (Checker_FigRotation(S, pos) == 0) {
					pos = 2;
					break;
				}
				else {
					Fig_S_pos_1(x-1);
					stop = 1;
				}
			}break;
		case (char)77: // right
		{
			stop = 0;
			if (!GameCheckerSideRight()) //проверка слева фигуры на наличие 1
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!GameCheckerSideLeft()) { //проверка справа фигуры на наличие 1
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[x+1][coorY] = 2;
		game_place[x+1][coorY -1] = 2;
		game_place[x][coorY] = 2;
		game_place[x][coorY + 1] = 2;
	}
}

void InitFig_Z(int x)
{
	if (pos % 2 != 0)
	{
		if (pos > 4) {
			pos = 1;
		}
		Fig_Z_pos_1(x); // вертикально Z
	}
	else if (pos % 2 == 0)
	{
		if (pos > 4) {
			pos = 2;
		}
		if (x > 1) {
			x--;
		}
		Fig_Z_pos_2(x); // гориз Z 
	}
}

void Fig_Z_pos_1(int x)  // вертикально Z
{
	int Z = 5;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			pos = 2;
			if (Checker_FigRotation(Z, pos) == 0) {
				pos = 1;
				break;
			}
			else {
				Fig_Z_pos_2(x - 1);
				stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!GameCheckerSideRight()) //проверка слева фигуры на наличие 1
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!GameCheckerSideLeft()) { //проверка справа фигуры на наличие 1
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[x][coorY + 1] = 2;
		game_place[x + 1][coorY + 1] = 2;
		game_place[x + 1][coorY] = 2;
		game_place[x + 2][coorY] = 2;
	}
}

void Fig_Z_pos_2(int x)  // гориз Z 
{
	int Z = 5;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			pos = 1;
			if (Checker_FigRotation(Z, pos) == 0) {
				pos = 2;
				break;
			}
			else {
				Fig_Z_pos_1(x );
				stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!GameCheckerSideRight()) //проверка слева фигуры на наличие 1
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!GameCheckerSideLeft()) { //проверка справа фигуры на наличие 1
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[x][coorY] = 2;
		game_place[x][coorY - 1] = 2;
		game_place[x + 1][coorY] = 2;
		game_place[x + 1][coorY + 1] = 2;
	}
}

void InitFig_T(int x)
{
	if (pos == 1)
	{
		Fig_T_pos_1(x); // вертикально T
	}
	else if (pos == 2)
	{
		Fig_T_pos_2(x); //Горизонтально =|
	}
	else if (pos == 3)
	{
		Fig_T_pos_3(x); // T Вверх нагами 
	}
	else if (pos == 4)
	{
		Fig_T_pos_4(x);  // вертикально |=
	}
}

void Fig_T_pos_1(int x)  // вертикально T
{
	int T = 6;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			pos = 2;
			if (Checker_FigRotation(T, pos) == 0) {
				pos = 1;
				break;
			}
			else {
				if (x == gobal_coor_X)
					x--;
				Fig_T_pos_2(x);
				gobal_coor_X--; stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!GameCheckerSideRight()) //проверка слева фигуры на наличие 1
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!GameCheckerSideLeft()) { //проверка справа фигуры на наличие 1
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[x][coorY-1] = 2;
		game_place[x][coorY] = 2;
		game_place[x][coorY + 1] = 2;
		game_place[x + 1][coorY] = 2;
	}
}

void Fig_T_pos_2(int x)  // вертикально  =|
{
	int T = 6;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			pos = 3;
			if (Checker_FigRotation(T, pos) == 0) {
				pos = 2;
				break;
			}
			else {
				if (x == gobal_coor_X)
					x--;
				Fig_T_pos_3(x);
				gobal_coor_X--; stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!GameCheckerSideRight()) //проверка слева фигуры на наличие 1
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!GameCheckerSideLeft()) { //проверка справа фигуры на наличие 1
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[x+1][coorY] = 2;
		game_place[x+1][coorY-1] = 2;
		game_place[x + 2][coorY] = 2;
		game_place[x][coorY] = 2;
	}
}

void Fig_T_pos_3(int x)  // T Вверх нагами
{
	int T = 6;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			pos = 4;
			if (Checker_FigRotation(T, pos) == 0) {
				pos = 3;
				break;
			}
			else {
				if (x == gobal_coor_X)
					x--;
				Fig_T_pos_4(x);
				gobal_coor_X--; stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!GameCheckerSideRight()) //проверка слева фигуры на наличие 1
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!GameCheckerSideLeft()) { //проверка справа фигуры на наличие 1
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[x + 1][coorY-1] = 2;
		game_place[x + 1][coorY] = 2;
		game_place[x + 1][coorY + 1] = 2;
		game_place[x][coorY] = 2;
	}
}

void Fig_T_pos_4(int x)  // Горизонтально |=
{
	int T = 6;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())
	{
		switch (_getch())
		{
		case (char)72:
		{
			pos = 1;
			if (Checker_FigRotation(T, pos) == 0) {
				pos = 4;
				break;
			}
			else {
				if (x == gobal_coor_X)
					x--;
				Fig_T_pos_3(x);
				gobal_coor_X--; stop = 1;
			}
		}break;
		case (char)77: // right
		{
			stop = 0;
			if (!GameCheckerSideRight()) //проверка слева фигуры на наличие 1
			{
				break;
			}
			else {
				coorY++;
			}
		}break;
		case (char)75: // left
		{
			if (!GameCheckerSideLeft()) { //проверка справа фигуры на наличие 1
				break;
			}
			else {
				coorY--;
			}
		}break;
		}
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[x][coorY] = 2;
		game_place[x + 1][coorY] = 2;
		game_place[x + 2][coorY] = 2;
		game_place[x + 1][coorY + 1] = 2;
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
	int stop = 0;
	for (int i = 1; i < ROW - 1; i++)
	{
		for (int j = 1; j < COL - 1; j++)
		{
			if (game_place[i][j] == 2)
			{
				find_X = i;   //первая координата найденой фигуры
				find_Y = j;
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
	if (Fig == 1 && pos == 1)
	{
		Find_Fig_in_place();
		if (game_place[find_X + 2][find_Y] != 1 && game_place[find_X + 3][find_Y + 1] != 1 && game_place[find_X + 2][find_Y + 1] != 1 && game_place[find_X + 2][find_Y + 2] != 1 && game_place[find_X + 3][find_Y + 2] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 1 && pos == 2)
	{
		Find_Fig_in_place();
		if (game_place[find_X][find_Y - 2] != 1 && game_place[find_X][find_Y - 1] != 1 && game_place[find_X][find_Y + 1] != 1 && game_place[find_X][find_Y + 3] != 1 && game_place[find_X + 1][find_Y + 2] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 2 && pos == 1)
	{
		Find_Fig_in_place();
		if (game_place[find_X + 1][find_Y] != 1 && game_place[find_X+2][find_Y] != 1 && game_place[find_X+2][find_Y-1] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 2 && pos == 2)
	{
		Find_Fig_in_place();
		if (game_place[find_X - 1][find_Y-2] != 1 && game_place[find_X][find_Y-2] != 1 && game_place[find_X][find_Y - 1] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 2 && pos == 3)
	{
		Find_Fig_in_place();
		if (game_place[find_X - 1][find_Y] != 1 && game_place[find_X-1][find_Y +1] != 1 && game_place[find_X+1][find_Y] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 2 && pos == 4)
	{
		Find_Fig_in_place();
		if (game_place[find_X][find_Y-1] != 1 && game_place[find_X][find_Y + 1] != 1 && game_place[find_X][find_Y+2] != 1 && game_place[find_X+1][find_Y + 2] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 3 && pos == 1)
	{
		Find_Fig_in_place();
		if (game_place[find_X][find_Y - 1] != 1 && game_place[find_X+1][find_Y-1] != 1 && game_place[find_X+2][find_Y-1] != 1 && game_place[find_X +2][find_Y] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 3 && pos == 2)
	{
		Find_Fig_in_place();
		if (game_place[find_X+1][find_Y-1] != 1 && game_place[find_X+2][find_Y-1] != 1 && game_place[find_X + 1][find_Y] != 1 && game_place[find_X+1][find_Y +1] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 3 && pos == 3)
	{
		Find_Fig_in_place();
		if (game_place[find_X][find_Y+1] != 1 && game_place[find_X][find_Y + 2] != 1 && game_place[find_X + 1][find_Y+2] != 1 && game_place[find_X + 2][find_Y + 2] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 3 && pos == 4)
	{
		Find_Fig_in_place();
		if (game_place[find_X+1][find_Y] != 1 && game_place[find_X+1][find_Y+1] != 1 && game_place[find_X+1][find_Y + 2] != 1 && game_place[find_X][find_Y + 2] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 4 && pos == 1)
	{
		Find_Fig_in_place();
		if (game_place[find_X][find_Y] != 1 && game_place[find_X + 1][find_Y] != 1 && game_place[find_X + 1][find_Y + 1] != 1 && game_place[find_X+2][find_Y + 1] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 4 && pos == 2)
	{
		Find_Fig_in_place();
		if (game_place[find_X + 1][find_Y] != 1 && game_place[find_X + 1][find_Y + 1] != 1 && game_place[find_X + 2][find_Y] != 1 && game_place[find_X+2][find_Y -1] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig ==5 && pos == 1)
	{
	Find_Fig_in_place();
	if (game_place[find_X][find_Y+2] != 1 && game_place[find_X +1][find_Y+2] != 1 && game_place[find_X + 1][find_Y + 1] != 1 && game_place[find_X + 2][find_Y + 1] != 1)	{
		return sides = true;
	}
	return sides;
	}
	else if (Fig == 5 && pos == 2)
	{
		Find_Fig_in_place();
		if (game_place[find_X][find_Y] != 1 && game_place[find_X][find_Y - 1] != 1 && game_place[find_X + 1][find_Y] != 1 && game_place[find_X + 1][find_Y + 1] != 1)
		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 6 && pos == 1)
	{
	Find_Fig_in_place();
	if (game_place[find_X][find_Y] != 1 && game_place[find_X][find_Y - 1] != 1 && game_place[find_X + 1][find_Y] != 1 && game_place[find_X + 1][find_Y + 1] != 1)
	{
		return sides = true;
	}
	return sides;
	}
	else if (Fig == 6 && pos == 2)
	{
	Find_Fig_in_place();
	if (game_place[find_X][find_Y] != 1 && game_place[find_X][find_Y + 1] != 1 && game_place[find_X + 1][find_Y+1] != 1 && game_place[find_X - 1][find_Y + 1] != 1)
	{
		return sides = true;
	}
	return sides;
	}
	else if (Fig == 6 && pos == 3)
	{
	Find_Fig_in_place();
	if (game_place[find_X][find_Y] != 1 && game_place[find_X+1][find_Y] != 1 && game_place[find_X + 1][find_Y - 1] != 1 && game_place[find_X + 1][find_Y + 1] != 1)
	{
		return sides = true;
	}
	return sides;
	}
	else if (Fig == 6 && pos == 4)
	{
	Find_Fig_in_place();
	if (game_place[find_X][find_Y] != 1 && game_place[find_X + 1][find_Y] != 1 && game_place[find_X + 2][find_Y] != 1 && game_place[find_X + 1][find_Y + 1] != 1)
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
	for (int i = 1; i < ROW - 1; i++)
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
		if (Left == false)	{
			break;
		}
	}
	return Left;
}

bool RowFULL(int row)
{
	temp = 0;
	for (int j = 1; j < COL-1; j++)	{
		temp = temp + game_place[row][j];
	}
	if (temp == 10)	{
		return true;
	}
	else{
		return false;
	}
}

int GameScare()
{
	int full_col = 0;
	for (int i = 1; i < ROW-1; i++)	{
		if (RowFULL(i))
			full_col++;
	}
	switch (full_col)  //колчичество очков при заполнении строк
	{
	case 1:
	{
		k=k+ 100;   //колчичество очков при заполнении 1 й строки
	}break;

	case 2:
	{
		k = k + 300;    //колчичество очков при заполнении 2х строк
	}break;
	case 3:
	{
		k = k + 700;    //колчичество очков при заполнении 3х строк
	}break;

	case 4:
	{
		k = k + 1500;   //колчичество очков при заполнении 4х строк
	}break;

	default:
		return 0;
		break;
	}
	DelRow();
}

void DelRow()
{
	int m = 0;  // переменная подмены i
	for (int i = 1; i < ROW-1; i++)	{
		if (RowFULL(i))		{
			m = i;
			do	
			{
				for (int j = 1; j < COL-1; j++)
				{
					game_place[m][j] = game_place[m - 1][j];
				}
				m--;
			} while (m != 1);
		}
	}
}

bool GameOver() // фун проверки верхней строки поля на наличие в ней "1", 1 -  часть фигуры 
{
	for (int i = 1; i < COL - 1; i++)	{
		if (game_place[1][i] == 1)	{
			return false;
		}
	}
	return true;
}

void PrintGame()
{
	int time = 200;
	system("cls");
	if (k > 1000 && k <= 5000) {
		time = 150;
	}
	if (k > 7000) {
		time = 100;
	}
	cout << "Scare = " << k <<endl;
	for (int i = 0; i < ROW; i++)	{
		for (int j = 0; j < COL; j++)		{
			if (game_place[i][j] == 0) {
				cout << " ";
			}
			else if (game_place[i][j] == 1) {
				cout << /*"1";*/char(219);
			}
			else if (game_place[i][j] == 2) {
				cout << /*"2";*/char(219);
			}
		}
		cout << endl;
	}
	Sleep(time);
}

void Fig_Cleaner()
{
	int part = 0;
	for (int i = 1; i < ROW; i++)	{
		for (int j = 1; j < COL; j++)	{
			if (game_place[i][j] == 2)	{
				game_place[i][j] = 0;
				part++;
			}
		}
		if (part == 4)
			break;
	}
}

void Turner_1_2()
{
	int part = 0;
	for (int i = 1; i < ROW; i++)	{
		for (int j = 1; j < COL; j++)	{
			if (game_place[i][j] == 2)	{
				game_place[i][j] = 1;
				part++;
			}
		}
		if (part == 4)
			break;
	}
}
