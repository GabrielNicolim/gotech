/* 
   	Função para criar uma gpu generica e provavelmente fake
	
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

// Função utilizada para a criar a lupa
void lupa(int ic, int il);

main()
{
	SetConsoleTitle("Func_Lupa"); 		 // Define o nome do console
    system("mode con:cols=80 lines=28");  // Define o tamanho do console
	
	for(int i = 0; i < 28; i++)
	for(int k = 0; k < 80; k++)
	{
		printf(" ");	
	}
	
	lupa(10, 4);
}

void lupa(int ic, int il)
{
	textbackground(15);  //12 linhas
	system("cls");
	
	// Linha 1 - Borda Preta
	textcolor(0);
	gotoxy(ic+6, il); printf("%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219);	
	// Linha 2  
	gotoxy(ic+3, il+1); printf("%c%c%c", 219, 219, 219);
	gotoxy(ic+13, il+1); printf("%c%c%c", 219, 219, 219);
	//linha 3
	gotoxy(ic+1, il+2); printf("%c%c", 219, 219);
	gotoxy(ic+16, il+2); printf("%c%c", 219, 219);	
	//linha 4
	gotoxy(ic, il+3);  printf("%c", 219);
	gotoxy(ic+18, il+3); printf("%c", 219);	
	//linha 5
	gotoxy(ic, il+4);	 printf("%c", 219);
	gotoxy(ic+18, il+4); printf("%c", 219);	
	//linha 6
	gotoxy(ic, il+5);  printf("%c", 219);
	gotoxy(ic+18, il+5); printf("%c", 219);	
	//linha 7
	gotoxy(ic+1, il+6); printf("%c%c", 219, 219);
	gotoxy(ic+16, il+6); printf("%c%c", 219, 219);	
	// Linha 8  
	gotoxy(ic+3, il+7); printf("%c%c%c", 219, 219, 219);
	gotoxy(ic+13, il+7); printf("%c%c%c", 219, 219, 219);
	// Linha 9 
	gotoxy(ic+6, il+8); printf("%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219);
	
	//Interior Lupa
	textcolor(3);
	gotoxy(ic+6, il+1); printf("%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+3, il+2); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+1, il+3); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+1, il+4); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+1, il+5); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+3, il+6); printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+6, il+7); printf("%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219);
	//brilhinho
	textcolor(15);
	gotoxy(ic+3, il+4); printf("%c", 219);
	gotoxy(ic+4, il+5); printf("%c%c", 219, 219);
	gotoxy(ic+7, il+6); printf("%c", 219);
	
	//cabo
	textcolor(BLACK);
	gotoxy(ic+18, il+5); printf("%c%c%c", 219, 219, 219);
	gotoxy(ic+18, il+6); printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219);
	gotoxy(ic+16, il+7); printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+18, il+8); printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+21, il+9); printf("%c%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+24, il+10);printf("%c%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+26, il+10);printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+26, il+11);printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	
	
	gotoxy(ic+25, il+15);
	
	// Acabou :D
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

