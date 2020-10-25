/* 
   	Função para criar o logo
	
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

// Função utilizada para a criar a logo da gotech
void gotech(int ic, int il);

main()
{
	SetConsoleTitle("Func_logo"); 		 // Define o nome do console
    system("mode con:cols=80 lines=28");  // Define o tamanho do console
	
	for(int i = 0; i < 28; i++)
	for(int k = 0; k < 80; k++)
	{
		printf(" ");	
	}
	
	gotech(10, 4);
}

void gotech(int ic, int il)
{
	textbackground(15);
	system("cls");
	textcolor(0);
	// Linha 1 do texto
	gotoxy(ic+1,il);	printf("%c%c%c%c%c%c",219,219,219,219,219,219);				gotoxy(ic+7,il);	printf("%c",187);
	gotoxy(ic+10,il);	printf("%c%c%c%c%c%c",219,219,219,219,219,219);				gotoxy(ic+16,il);	printf("%c",187);	
	gotoxy(ic+18,il);	printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);	gotoxy(ic+25,il);	printf("%c",187);
	gotoxy(ic+27,il);	printf("%c%c%c%c%c%c%c",219,219,219,219,219,219,219);		gotoxy(ic+34,il);	printf("%c",187);
	gotoxy(ic+38,il);	printf("%c%c%c%c%c%c",219,219,219,219,219,219);				gotoxy(ic+44,il);	printf("%c",187);
	gotoxy(ic+46,il);	printf("%c%c",219,219);										gotoxy(ic+48,il);	printf("%c",187);
	gotoxy(ic+51,il);	printf("%c%c",219,219);										gotoxy(ic+53,il);	printf("%c",187);
	
	//linha 2
	gotoxy(ic,il+1);	printf("%c%c",219,219);		gotoxy(ic+2,il+1);	printf("%c%c%c%c%c%c",201,205,205,205,205,188);
	gotoxy(ic+9,il+1);	printf("%c%c",219,219);		gotoxy(ic+11,il+1);	printf("%c%c%c%c",201,205,205,205);
	gotoxy(ic+15,il+1);	printf("%c%c",219,219);		gotoxy(ic+17,il+1);	printf("%c",187);
	gotoxy(ic+21,il+1);	printf("%c%c",219,219);		gotoxy(ic+18,il+1);	printf("%c%c%c",200,205,205);
	gotoxy(ic+27,il+1);	printf("%c%c",219,219);		gotoxy(ic+23,il+1);	printf("%c%c%c",201,205,188);
	gotoxy(ic+37,il+1);	printf("%c%c",219,219);		gotoxy(ic+29,il+1);	printf("%c%c%c%c%c%c",201,205,205,205,205,188);
	gotoxy(ic+46,il+1);	printf("%c%c",219,219);		gotoxy(ic+39,il+1);	printf("%c%c%c%c%c%c",201,205,205,205,205,188);
	gotoxy(ic+51,il+1);	printf("%c%c",219,219);		gotoxy(ic+48,il+1);	printf("%c",186);		gotoxy(ic+53,il+1);	printf("%c",186);
		
	//linha 3
	gotoxy(ic,il+2);	printf("%c%c",219,219);									gotoxy(ic+2,il+2);	printf("%c",186);
	gotoxy(ic+5,il+2);	printf("%c%c%c",219,219,219);							gotoxy(ic+8,il+2);	printf("%c",187);
	gotoxy(ic+9,il+2);	printf("%c%c",219,219);									gotoxy(ic+11,il+2);	printf("%c",186);
	gotoxy(ic+15,il+2);	printf("%c%c",219,219);									gotoxy(ic+17,il+2);	printf("%c",186);
	gotoxy(ic+21,il+2);	printf("%c%c",219,219);									gotoxy(ic+23,il+2);	printf("%c",186);
	gotoxy(ic+27,il+2);	printf("%c%c%c%c%c%c",219,219,219,219,219,219);			gotoxy(ic+33,il+2);	printf("%c",187);
	gotoxy(ic+37,il+2);	printf("%c%c",219,219);									gotoxy(ic+39,il+2);	printf("%c",186);
	gotoxy(ic+46,il+2);	printf("%c%c%c%c%c%c%c",219,219,219,219,219,219,219);	gotoxy(ic+53,il+2);	printf("%c",186);
	
	//linha 4
	gotoxy(ic,il+3);	printf("%c%c",219,219);		gotoxy(ic+2,il+3);	printf("%c",186);
	gotoxy(ic+6,il+3);	printf("%c%c",219,219);		gotoxy(ic+8,il+3);	printf("%c",186);
	gotoxy(ic+9,il+3);	printf("%c%c",219,219);		gotoxy(ic+11,il+3);	printf("%c",186);
	gotoxy(ic+15,il+3);	printf("%c%c",219,219);		gotoxy(ic+17,il+3);	printf("%c",186);
	gotoxy(ic+21,il+3);	printf("%c%c",219,219);		gotoxy(ic+23,il+3);	printf("%c",186);
	gotoxy(ic+27,il+3);	printf("%c%c",219,219);		gotoxy(ic+29,il+3);	printf("%c%c%c%c%c",201,205,205,205,188);
	gotoxy(ic+37,il+3);	printf("%c%c",219,219);		gotoxy(ic+39,il+3);	printf("%c",186);
	gotoxy(ic+46,il+3);	printf("%c%c",219,219);		gotoxy(ic+48,il+3);	printf("%c%c%c",201,205,205);
	gotoxy(ic+51,il+3);	printf("%c%c",219,219);		gotoxy(ic+53,il+3);	printf("%c",186);
		
	//linha 5
	gotoxy(ic+1,il+4);	printf("%c%c%c%c%c%c",219,219,219,219,219,219);			gotoxy(ic,il+4);	printf("%c",200);
	gotoxy(ic+10,il+4);	printf("%c%c%c%c%c%c",219,219,219,219,219,219);			gotoxy(ic+7,il+4);	printf("%c%c%c",201,188,200);
	gotoxy(ic+21,il+4);	printf("%c%c",219,219);									gotoxy(ic+16,il+4);	printf("%c%c",201,188);
	gotoxy(ic+27,il+4);	printf("%c%c%c%c%c%c%c",219,219,219,219,219,219,219);	gotoxy(ic+23,il+4);	printf("%c",186);
	gotoxy(ic+38,il+4);	printf("%c%c%c%c%c%c",219,219,219,219,219,219);			gotoxy(ic+34,il+4);	printf("%c",187);
	gotoxy(ic+46,il+4);	printf("%c%c",219,219);									gotoxy(ic+37,il+4);	printf("%c",200);
	gotoxy(ic+51,il+4);	printf("%c%c",219,219);									gotoxy(ic+44,il+4);	printf("%c",187);
	gotoxy(ic+48,il+4);	printf("%c",186);										gotoxy(ic+53,il+4);	printf("%c",186);
	
	//linha 6
		
	gotoxy(ic+1,il+5);	printf("%c%c%c%c%c%c%c",200,205,205,205,205,205,188);
	gotoxy(ic+10,il+5);	printf("%c%c%c%c%c%c%c",200,205,205,205,205,205,188);
	gotoxy(ic+21,il+5);	printf("%c%c%c",200,205,188);
	gotoxy(ic+27,il+5);	printf("%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,188);
	gotoxy(ic+38,il+5);	printf("%c%c%c%c%c%c%c",200,205,205,205,205,205,188);
	gotoxy(ic+46,il+5);	printf("%c%c%c",200,205,188);
	gotoxy(ic+51,il+5);	printf("%c%c%c",200,205,188);
	
	gotoxy(ic+8,il+7);
	
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

