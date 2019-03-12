/*
	Игра тетрис
	учебный проект консельной версии игры тетрис
	(c) Protsenko Vyacheslav
	Version: 1.0 (11.03.2019)
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
int global_coor_X;
int global_inc_i;  //при перемещении или вращении координата берет -1 тем самым во время перемещения или вращения координата фигура не опускается
int type;
int pos;

void Fig_I_pos_1();//Горизонтально I //палка   
void Fig_I_pos_2();// вертикально I //палка
void InitFig_I();

void InitFig_O();//kyb

void Fig_J_pos_1(); // вертикально J
void Fig_J_pos_2(); // J Вверх нагами
void Fig_J_pos_3(); //Горизонтально  |___
void Fig_J_pos_4(); // вертикально  ===,
void InitFig_J();

void Fig_L_pos_1();  // вертикально L
void Fig_L_pos_2(); // L Вверх нагами 
void Fig_L_pos_3();  //Горизонтально  ,===
void Fig_L_pos_4();  // вертикально  ___|
void InitFig_L();

void Fig_S_pos_1();  // вертикально S
void Fig_S_pos_2();  // гориз S 
void InitFig_S();

void Fig_Z_pos_1();  // вертикально Z
void Fig_Z_pos_2();  // гориз Z 
void InitFig_Z();

void Fig_T_pos_1();  // вертикально T
void Fig_T_pos_2();  // вертикально  =|
void Fig_T_pos_3();  // T Вверх нагами 
void Fig_T_pos_4();  // Горизонтально  |=
void InitFig_T();

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
void GameScare();  // подсчет очков
void Fig_control(int Figura, int *stop); //управление фигурой(лево,право, переворот)
void PrintGame();// функция вывода фигуры на консоль
void Fig_step(int type);

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
		type = rand()%7+1;
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
		for (global_inc_i = 1; global_inc_i < ROW - 1; global_inc_i++) {
			global_coor_X = global_inc_i;
			InitFig_I();
			global_inc_i = global_coor_X;
			if (!GameCheckerLower())
				break;
			PrintGame();
		}
		PrintGame();
		Turner_1_2();
	}	break;
	case 2:
	{
		for (global_inc_i = 1; global_inc_i < ROW - 1; global_inc_i++) {
			global_coor_X = global_inc_i;
			InitFig_O();
			global_inc_i = global_coor_X;
			if (!GameCheckerLower())
				break;
			PrintGame();
		}
		PrintGame();
		Turner_1_2();
	}	break;
	case 3:
	{
		for (global_inc_i = 1; global_inc_i < ROW - 1; global_inc_i++) {
			global_coor_X = global_inc_i;
			InitFig_J();
			global_inc_i = global_coor_X;
			if (!GameCheckerLower())
				break;
			PrintGame();
		}
		PrintGame();
		Turner_1_2();
	}	break;
	case 4:
	{
		for (global_inc_i = 1; global_inc_i < ROW - 1; global_inc_i++) {
			global_coor_X = global_inc_i;
			InitFig_L();
			global_inc_i = global_coor_X;
			if (!GameCheckerLower())
				break;
			PrintGame();
		}
		PrintGame();
		Turner_1_2();
	}	break;
	case 5:
	{
		for (global_inc_i = 1; global_inc_i < ROW - 1; global_inc_i++) {
			global_coor_X = global_inc_i;
			InitFig_S();
			global_inc_i = global_coor_X;
			if (!GameCheckerLower())
				break;
			PrintGame();
		}
		PrintGame();
		Turner_1_2();
	}	break;
	case 6:
	{
		for (global_inc_i = 1; global_inc_i < ROW - 1; global_inc_i++) {
			global_coor_X = global_inc_i;
			InitFig_Z();
			global_inc_i = global_coor_X;
			if (!GameCheckerLower())
				break;
			PrintGame();
		}
		PrintGame();
		Turner_1_2();
	}	break;
	case 7:
	{
		for (global_inc_i = 1; global_inc_i < ROW - 1; global_inc_i++) {
			global_coor_X = global_inc_i;
			InitFig_T();
			global_inc_i =global_coor_X;
			if (!GameCheckerLower())
				break;
			PrintGame();
		}
		PrintGame();
		Turner_1_2();
	}	break;
	}
}

void InitFig_I()  //палка
{
	if (pos % 2 != 0)	{
		Fig_I_pos_1();//Горизонтально === //палка
	}
	else if (pos % 2 == 0)	{
		Fig_I_pos_2();// вертикально I //палка
	}
}

void Fig_I_pos_1()//Горизонтально === //палка
{
	int I = 1;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit()) {
		Fig_control(I, &stop);
	}
	if (stop == 0)	{
		Fig_Cleaner();
		game_place[global_coor_X][coorY] = 2;
		game_place[global_coor_X][coorY + 1] = 2;
		game_place[global_coor_X][coorY + 2] = 2;
		game_place[global_coor_X][coorY + 3] = 2;
	}
}

void Fig_I_pos_2()// вертикально I //палка
{
	int I = 1;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit()) {
		Fig_control(I, &stop);
	}
	if (stop == 0)	{
		Fig_Cleaner();
		game_place[global_coor_X][coorY+1] = 2;
		game_place[global_coor_X + 1][coorY+1] = 2;
		game_place[global_coor_X + 2][coorY+1] = 2;
		game_place[global_coor_X + 3][coorY+1] = 2;
	}
}

void InitFig_O()   //куб
{
	int O=0;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit()) {
		Fig_control(O, &stop);
	}
	Fig_Cleaner();
	game_place[global_coor_X][coorY] = 2;
	game_place[global_coor_X][coorY + 1] = 2;
	game_place[global_coor_X + 1][coorY] = 2;
	game_place[global_coor_X + 1][coorY + 1] = 2;
}

void InitFig_J()
{
	if (pos == 1)	{
		Fig_J_pos_1();// вертикально J
	}
	else if (pos == 2)	{
		Fig_J_pos_2();//Горизонтально  |___
	}
	else if (pos == 3)	{
		Fig_J_pos_3();// J Вверх нагами
	}
	else if (pos == 4)	{
		Fig_J_pos_4();// вертикально  ===,
	}
}

void Fig_J_pos_1() // вертикально J
{
	int J = 2;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit()) {
		Fig_control(J, &stop);
	}
	if (stop == 0)	{
		Fig_Cleaner();
		game_place[global_coor_X][coorY] = 2;
		game_place[global_coor_X + 1][coorY] = 2;
		game_place[global_coor_X + 2][coorY] = 2;
		game_place[global_coor_X + 2][coorY-1] = 2;
	}
}

void Fig_J_pos_2() //Горизонтально  |___
{
	int J = 2;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit()) {
		Fig_control(J, &stop);
	}
	if (stop == 0)	{
		Fig_Cleaner();
		game_place[global_coor_X][coorY-1] = 2;
		game_place[global_coor_X + 1][coorY-1] = 2;
		game_place[global_coor_X + 1][coorY] = 2;
		game_place[global_coor_X + 1][coorY +1] = 2;
	}
}

void Fig_J_pos_3() // J Вверх нагами
{
	int J = 2;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit()) {
		Fig_control(J, &stop);
	}
	if (stop == 0)	{
		Fig_Cleaner();
		game_place[global_coor_X][coorY + 1] = 2;
		game_place[global_coor_X][coorY] = 2;
		game_place[global_coor_X + 1][coorY] = 2;
		game_place[global_coor_X + 2][coorY] = 2;
	}
}

void Fig_J_pos_4() // вертикально  ===,
{
	int J = 2;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit()) {
		Fig_control(J, &stop);
	}
	if (stop == 0)	{
		Fig_Cleaner();
		game_place[global_coor_X][coorY + 1] = 2;
		game_place[global_coor_X][coorY-1] = 2;
		game_place[global_coor_X][coorY] = 2;
		game_place[global_coor_X + 1][coorY + 1] = 2;
	}
}

void InitFig_L()
{
	if (pos == 1)	{
		Fig_L_pos_1(); // вертикально L
	}
	else if (pos == 2)	{
		Fig_L_pos_2(); //Горизонтально  ,===
	}
	else if (pos == 3)	{
		Fig_L_pos_3(); // L Вверх нагами
	}
	else if (pos == 4)	{
		Fig_L_pos_4();  // вертикально  ___|
	}
}

void Fig_L_pos_1() // вертикально L
{
	int L = 3;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())	{
		Fig_control(L, &stop);
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[global_coor_X][coorY] = 2;
		game_place[global_coor_X+1][coorY] = 2;
		game_place[global_coor_X + 2][coorY] = 2;
		game_place[global_coor_X + 2][coorY + 1] = 2;
	}
}

void Fig_L_pos_2()  //Горизонтально  ,===
{
	int L = 3;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())	{
		Fig_control(L, &stop);
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[global_coor_X][coorY] = 2;
		game_place[global_coor_X][coorY-1] = 2;
		game_place[global_coor_X +1][coorY-1] = 2;
		game_place[global_coor_X][coorY + 1] = 2;
	}
}

void Fig_L_pos_3() // L Вверх нагами 
{
	int L = 3;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())	{
		Fig_control(L, &stop);
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[global_coor_X][coorY] = 2;
		game_place[global_coor_X][coorY+1] = 2;
		game_place[global_coor_X+1][coorY] = 2;
		game_place[global_coor_X + 2][coorY] = 2;
	}
}

void Fig_L_pos_4()  // вертикально  ___|
{
	int L = 3;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())	{
		Fig_control(L, &stop);
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[global_coor_X][coorY+1] = 2;
		game_place[global_coor_X+1][coorY+1] = 2;
		game_place[global_coor_X+1][coorY] = 2;
		game_place[global_coor_X+1][coorY -1] = 2;
	}
}

void InitFig_S()
{
	if (pos % 2 != 0)	{
		Fig_S_pos_1();// вертикально S
	}
	else if (pos % 2 == 0)	{
		Fig_S_pos_2();// гориз S 
	}
}

void Fig_S_pos_1()  // вертикально S
{
	int S = 4;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit()) {
		Fig_control(S, &stop);
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[global_coor_X][coorY] = 2;
		game_place[global_coor_X + 1][coorY] = 2;
		game_place[global_coor_X +1][coorY + 1] = 2;
		game_place[global_coor_X + 2][coorY + 1] = 2;
	}
}

void Fig_S_pos_2()  // гориз S 
{
	int S = 4;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit()) {
		Fig_control(S, &stop);
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[global_coor_X][coorY] = 2;
		game_place[global_coor_X][coorY + 1] = 2;
		game_place[global_coor_X +1][coorY] = 2;
		game_place[global_coor_X +1][coorY -1] = 2;
	}
}

void InitFig_Z()
{
	if (pos % 2 != 0)	{
		Fig_Z_pos_1(); // вертикально Z
	}
	else if (pos % 2 == 0)	{
		Fig_Z_pos_2(); // гориз Z 
	}
}

void Fig_Z_pos_1()  // вертикально Z
{
	int Z = 5;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())	{
		Fig_control(Z, &stop);
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[global_coor_X][coorY + 1] = 2;
		game_place[global_coor_X + 1][coorY + 1] = 2;
		game_place[global_coor_X + 1][coorY] = 2;
		game_place[global_coor_X + 2][coorY] = 2;
	}
}

void Fig_Z_pos_2()  // гориз Z 
{
	int Z = 5;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())	{
		Fig_control(Z, &stop);
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[global_coor_X][coorY] = 2;
		game_place[global_coor_X][coorY - 1] = 2;
		game_place[global_coor_X + 1][coorY] = 2;
		game_place[global_coor_X + 1][coorY + 1] = 2;
	}
}

void Fig_control(int Figura, int *stop) //функция отвечает за движения фигуры
{
	if (global_coor_X == global_inc_i)
		global_coor_X--;

	switch (_getch())
	{
	case (char)72:
	{
		if (pos == 4) {
			pos = 1;
		}
		else {
			pos++;
		}
		if (Checker_FigRotation(Figura, pos) == 0) {
			if (pos == 1) {
				pos = 4;
			}
			else {
				pos--;
			}
			break;
		}
		else {
			if (Figura == 0) {
				break;
			}
			else if (Figura == 1) {
				if (pos % 2 != 0) {
					global_coor_X++;
					Fig_I_pos_1();
				}
				else if (pos % 2 == 0) {
					global_coor_X--;
					Fig_I_pos_2();
				}
			}
			else if (Figura == 2) {
				if (pos == 1) {
					global_coor_X--;
					Fig_J_pos_1();
				}
				else if (pos == 2) {
					
					Fig_J_pos_2();
				}
				else if (pos == 3) {
					Fig_J_pos_3();
				}
				else if (pos == 4) {
					global_coor_X++;
					Fig_J_pos_4();
				}
			}
			else if (Figura == 3) {
				if (pos == 1) {
					Fig_L_pos_1();
				}
				else if (pos == 2) {
					global_coor_X++;
					Fig_L_pos_2();
				}
				else if (pos == 3) {
					global_coor_X--;
					Fig_L_pos_3();
				}
				else if (pos == 4) {
					Fig_L_pos_4();
				}
			}
			else if (Figura == 4) {
				if (pos % 2 != 0) {
					Fig_S_pos_1();
				}
				else if (pos % 2 == 0) {
					Fig_S_pos_2();
				}
			}
			else if (Figura == 5) {
				if (pos % 2 != 0) {
					Fig_Z_pos_1();
				}
				else if (pos % 2 == 0) {
					Fig_Z_pos_2();
				}
			}
			else if (Figura == 6) {
				if (pos == 1) {
					Fig_T_pos_1();
				}else if (pos == 2) {
					Fig_T_pos_2();
				}
				else if (pos == 3) {
					Fig_T_pos_3();
				}
				else if (pos == 4) {
					Fig_T_pos_4();
				}
			}
			*stop = 1;
		}
	}break;
	case (char)77: // right
	{
		stop = 0;
		if (!GameCheckerSideRight()) {  //проверка слева фигуры на наличие 1
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

void InitFig_T()
{
	if (pos == 1)	{
		Fig_T_pos_1(); // вертикально T
	}
	else if (pos == 2)	{
		Fig_T_pos_2(); //Горизонтально =|
	}
	else if (pos == 3)	{
		Fig_T_pos_3(); // T Вверх нагами 
	}
	else if (pos == 4)	{
		Fig_T_pos_4();  // вертикально |=
	}
}

void Fig_T_pos_1()  // вертикально T
{
	int T = 6;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())	{
		Fig_control(T,&stop);
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[global_coor_X][coorY-1] = 2;
		game_place[global_coor_X][coorY] = 2;
		game_place[global_coor_X][coorY + 1] = 2;
		game_place[global_coor_X + 1][coorY] = 2;
	}
}

void Fig_T_pos_2()  // вертикально  =|
{
	int T = 6;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())	{
		Fig_control(T, &stop);
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[global_coor_X +1][coorY] = 2;
		game_place[global_coor_X +1][coorY-1] = 2;
		game_place[global_coor_X + 2][coorY] = 2;
		game_place[global_coor_X][coorY] = 2;
	}
}

void Fig_T_pos_3()  // T Вверх нагами
{
	int T = 6;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())	{
		Fig_control(T, &stop);
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[global_coor_X + 1][coorY-1] = 2;
		game_place[global_coor_X + 1][coorY] = 2;
		game_place[global_coor_X + 1][coorY + 1] = 2;
		game_place[global_coor_X][coorY] = 2;
	}
}

void Fig_T_pos_4()  // Горизонтально |=
{
	int T = 6;
	CleanBufferGetch();
	int stop = 0;
	if (_kbhit())	{
		Fig_control(T, &stop);
	}
	if (stop == 0) {
		Fig_Cleaner();
		game_place[global_coor_X][coorY] = 2;
		game_place[global_coor_X + 1][coorY] = 2;
		game_place[global_coor_X + 2][coorY] = 2;
		game_place[global_coor_X + 1][coorY + 1] = 2;
	}
}

void Find_Fig_in_place() //функция поиска первой координаты фигуры
{
	int stop = 0;
	for (int i = 1; i < ROW - 1; i++)	{
		for (int j = 1; j < COL - 1; j++)
		{
			if (game_place[i][j] == 2)	{
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
	if (Fig == 1 && pos%2 != 0)	{
		Find_Fig_in_place();
		if (game_place[find_X + 1][find_Y-1] != 1 && game_place[find_X+1][find_Y] != 1 && game_place[find_X + 1][find_Y + 1] != 1 && game_place[find_X + 1][find_Y + 2] != 1 /*&& game_place[find_X + 2][find_Y -1] != 1*/)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 1 && pos % 2 == 0)	{
		Find_Fig_in_place();
		if (game_place[find_X-1][find_Y +1] != 1 && game_place[find_X][find_Y + 1] != 1 && game_place[find_X+1][find_Y + 1] != 1 && game_place[find_X+2][find_Y + 1] != 1/* && game_place[find_X + 1][find_Y + 2] != 1*/)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 2 && pos == 1)	{
		Find_Fig_in_place();
		if (game_place[find_X - 1][find_Y+1] != 1 && game_place[find_X][find_Y+1] != 1 && game_place[find_X+1][find_Y+1] != 1 && game_place[find_X + 1][find_Y] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 2 && pos == 2)	{
		Find_Fig_in_place();
		if (game_place[find_X][find_Y-1] != 1 && game_place[find_X+1][find_Y-1] != 1 && game_place[find_X+1][find_Y] != 1 && game_place[find_X+1][find_Y + 1] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 2 && pos == 3)	{
		Find_Fig_in_place();
		if (game_place[find_X][find_Y+1] != 1 && game_place[find_X][find_Y +2] != 1 && game_place[find_X+1][find_Y+1] != 1 && game_place[find_X + 2][find_Y+1] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 2 && pos == 4)	{
		Find_Fig_in_place();
		if (game_place[find_X+1][find_Y-1] != 1 && game_place[find_X+1][find_Y] != 1 && game_place[find_X+1][find_Y+1] != 1 && game_place[find_X+2][find_Y + 1] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 3 && pos == 1)	{
		Find_Fig_in_place();
		if (game_place[find_X][find_Y - 1] != 1 && game_place[find_X+1][find_Y-1] != 1 && game_place[find_X+2][find_Y-1] != 1 && game_place[find_X +2][find_Y] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 3 && pos == 2)	{
		Find_Fig_in_place();
		if (game_place[find_X+1][find_Y-1] != 1 && game_place[find_X+2][find_Y-1] != 1 && game_place[find_X + 1][find_Y] != 1 && game_place[find_X+1][find_Y +1] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 3 && pos == 3)	{
		Find_Fig_in_place();
		if (game_place[find_X-1][find_Y] != 1 && game_place[find_X-1][find_Y + 1] != 1 && game_place[find_X][find_Y+1] != 1 && game_place[find_X + 1][find_Y + 1] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 3 && pos == 4)	{
		Find_Fig_in_place();
		if (game_place[find_X+1][find_Y] != 1 && game_place[find_X+1][find_Y+1] != 1 && game_place[find_X+1][find_Y + 2] != 1 && game_place[find_X][find_Y + 2] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 4 && pos % 2 != 0)	{
		Find_Fig_in_place();
		if (game_place[find_X][find_Y] != 1 && game_place[find_X + 1][find_Y] != 1 && game_place[find_X + 1][find_Y + 1] != 1 && game_place[find_X+2][find_Y + 1] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 4 && pos % 2 == 0)	{
		Find_Fig_in_place();
		if (game_place[find_X][find_Y] != 1 && game_place[find_X][find_Y + 1] != 1 && game_place[find_X + 1][find_Y] != 1 && game_place[find_X+1][find_Y -1] != 1)		{
			return sides = true;
		}
		return sides;
	}
	else if (Fig ==5 && pos%2 != 0)	{
	Find_Fig_in_place();
	if (game_place[find_X][find_Y+2] != 1 && game_place[find_X +1][find_Y+2] != 1 && game_place[find_X + 1][find_Y + 1] != 1 && game_place[find_X + 2][find_Y + 1] != 1)	{
		return sides = true;
	}
	return sides;
	}
	else if (Fig == 5 && pos%2 == 0)	{
		Find_Fig_in_place();
		if (game_place[find_X][find_Y] != 1 && game_place[find_X][find_Y - 1] != 1 && game_place[find_X + 1][find_Y] != 1 && game_place[find_X + 1][find_Y + 1] != 1)	{
			return sides = true;
		}
		return sides;
	}
	else if (Fig == 6 && pos == 1)	{
	Find_Fig_in_place();
	if (game_place[find_X][find_Y] != 1 && game_place[find_X][find_Y - 1] != 1 && game_place[find_X + 1][find_Y] != 1 && game_place[find_X + 1][find_Y + 1] != 1)	{
		return sides = true;
	}
	return sides;
	}
	else if (Fig == 6 && pos == 2)	{
	Find_Fig_in_place();
	if (game_place[find_X][find_Y] != 1 && game_place[find_X][find_Y + 1] != 1 && game_place[find_X + 1][find_Y+1] != 1 && game_place[find_X - 1][find_Y + 1] != 1)	{
		return sides = true;
	}
	return sides;
	}
	else if (Fig == 6 && pos == 3)	{
	Find_Fig_in_place();
	if (game_place[find_X][find_Y] != 1 && game_place[find_X+1][find_Y] != 1 && game_place[find_X + 1][find_Y - 1] != 1 && game_place[find_X + 1][find_Y + 1] != 1)	{
		return sides = true;
	}
	return sides;
	}
	else if (Fig == 6 && pos == 4)	{
	Find_Fig_in_place();
	if (game_place[find_X][find_Y] != 1 && game_place[find_X + 1][find_Y] != 1 && game_place[find_X + 2][find_Y] != 1 && game_place[find_X + 1][find_Y + 1] != 1)	{
		return sides = true;
	}
	return sides;
	}
}

bool GameCheckerLower() //Проверка строки ниже на наличие объекта
{
	low = true; //проверка низа фигуры на наличие 1
	for (int i = 1; i < ROW - 1; i++)	{
		for (int j = 1; j < COL - 1; j++)	{
			if (game_place[i][j] == 2)	{
				if (game_place[i + 1][j] == 1)	{
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
	for (int i = 1; i < ROW - 1; i++)	{
		for (int j = 1; j < COL - 1; j++)	{
			if (game_place[i][j] == 2)	{
				if (game_place[i][j + 1] == 2)	{
					continue;
				}
				else if (game_place[i][j + 1] == 1)	{
					Right = false;
					break;
				}
			}
		}
		if (Right == false)	{
			break;
		}
	}
	return Right;
}

bool GameCheckerSideLeft()  //Проверка левой стороны фигуры на наличие объекта
{
	Left = true;
	for (int i = 1; i < ROW - 1; i++)	{
		for (int j = 1; j < COL - 1; j++)	{
			if (game_place[i][j] == 2)	{
				if (game_place[i][j - 1] == 1)	{
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

void GameScare()
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
		if (RowFULL(i))	{
			m = i;
			do	{
				for (int j = 1; j < COL-1; j++)	{
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
		for (int j = 0; j < COL; j++)	{
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
