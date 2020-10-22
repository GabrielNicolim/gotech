/* 
   	Função para borda e cor de texto e fundo
	
	- passe como parâmetro (cor de fundo, cor de texto, cor da borda, limite de coluna, limite de linha)
	
*/

#include <stdio.h>
#include<stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 120, 35, 1, 1}; // Define os limites para linha (35) e coluna (80)

// Funções conio.c

void textcolor(int newcolor);
void textbackground(int newcolor);
void gotoxy(int x, int y);

// Função utilizada para a borda
void borda(int cf, int ct, int cb, int lc, int ll);

main()
{
	SetConsoleTitle("Func_Borda"); 		   // Define o nome do console
    system("mode con:cols=120 lines=35");  // Define o tamanho do console
	
	borda(0, 2, 10, 120, 35);
}

void borda(int cf, int ct, int cb, int lc, int ll)
{
	textbackground(cf); // Define cor do fundo
	system("cls"); 
	
	textcolor(cb); // Define cor da borda
	
	// Cria a linha => Char 219
	
	for(int i = 0; i < ll; i++) // Realiza a criação de uma borda por toda a folha
	{
		for(int k = 0; k < lc; k++)
		{
			if(k == 0 || k == 1) putchar(219);
			else if(k == (lc - 1) || k == (lc - 2)) putchar(219);
			else if(i == 0) putchar(219);
			else if(i == (ll - 1)) putchar(219);
			else putchar(32);
		}
	}
		
	getch();
	
	textcolor(ct); // Define cor do texto
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

