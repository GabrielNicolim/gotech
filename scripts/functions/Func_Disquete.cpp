/* 
   	Função para criar o disquete
	
	- passe como parâmetro (a coluna de inicio, a linha de inicio)
	
*/

#include <stdio.h>
#include<stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 80, 28, 1, 1}; // Define os limites para linha (35) e coluna (80)

// Funções conio.c

void textcolor(int newcolor);
void textbackground(int newcolor);
void gotoxy(int x, int y);

// Função utilizada para a criar o disquete
void disquete(int ic, int il);

main()
{
	SetConsoleTitle("Func_Disquete"); 		 // Define o nome do console
    system("mode con:cols=80 lines=28");  // Define o tamanho do console
	
	for(int i = 0; i < 28; i++)
	for(int k = 0; k < 80; k++)
	{
		printf(" ");	
	}
	
	disquete(10, 5);
}

void disquete(int ic, int il)
{
	textbackground(15);
	system("cls");
	
	// Linha 1 => Borda de cima
	textcolor(0);
	gotoxy(ic, il); 
	for(int i = 0; i < 20; i++) putchar(219);
	
	// Linha 2
	gotoxy(ic, (il+1));
	printf("%c%c", 219, 219);
	
	for(int i = 0; i < 16; i++) 
	{
		if(i == 2 or i == 13) textcolor(8);
		if(i > 2  and i < 13) 
		{
			if(i == 3) textcolor(8);
			else if(i % 2 == 0) textcolor(0);
			else textcolor(8);
		}
		else textcolor(9);
		putchar(219);
	}
	
	textcolor(0);
	printf("%c%c", 219, 219);
	
	// Linha 3
	gotoxy(ic, (il+2));
	printf("%c%c", 219, 219);
	
	for(int i = 0; i < 16; i++) 
	{
		if(i == 2 or i == 13) textcolor(8);
		if(i > 2  and i < 13) textcolor(7);
		else textcolor(9);
		putchar(219);
	}
	
	textcolor(0);
	printf("%c%c", 219, 219);
	
	// Linha 4
	
	gotoxy(ic, (il+3));
	
	printf("%c%c", 219, 219);
	textcolor(9);
	for(int i = 0; i < 16; i++) putchar(219);
	textcolor(0);
	printf("%c%c", 219, 219);
	
	// Linha 5
	
	gotoxy(ic, (il+4));
	
	printf("%c%c", 219, 219);
	textcolor(9);
	for(int i = 0; i < 16; i++) putchar(219);
	textcolor(0);
	printf("%c%c", 219, 219);
	
	//Linha 6
	
	gotoxy(ic, (il+5));
	
	printf("%c%c", 219, 219);
	textcolor(9);
	for(int i = 0; i < 16; i++) putchar(219);
	textcolor(0);
	printf("%c%c", 219, 219);
	
	//Linha 7
	
	gotoxy(ic, (il+6));
	
	printf("%c%c", 219, 219);
	textcolor(9);
	for(int i = 0; i < 16; i++) putchar(219);
	textcolor(0);
	printf("%c%c", 219, 219);
	
	// Linha 8
	
	gotoxy(ic, (il+7));
	
	printf("%c%c", 219, 219);
	textcolor(9);
	for(int i = 0; i < 16; i++) putchar(219);
	textcolor(0);
	printf("%c%c", 219, 219);
	
	// Linha 9 => Borda de baixo
	textcolor(0);
	gotoxy(ic, (il+8)); 
	for(int i = 0; i < 20; i++) putchar(219);
	
}


void textcolor(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0xf0) | newcolor);
   vActual.attribute = (csbi.wAttributes & 0xf0) | newcolor;
}

void textbackground(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0x0f) | (newcolor << 4));
   vActual.attribute = (csbi.wAttributes & 0x0f) | (newcolor << 4);
}

void gotoxy(int x, int y)
{
  COORD c;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

