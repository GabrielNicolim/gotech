/* 
   	Função para criar a memoria
	
	- passe como parâmetro (a coluna de inicio, a linha de inicio)
	
*/

#include <stdio.h>
#include <stdlib.h>
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

// Função utilizada para a criar a mensagem info de jeito bunitim
void info(int ic, int il);

main()
{
	SetConsoleTitle("Func_Info"); 		 // Define o nome do console
    system("mode con:cols=120 lines=40");  // Define o tamanho do console
	
	for(int i = 0; i < 28; i++)
	for(int k = 0; k < 80; k++)
	{
		printf(" ");	
	}
	
	info(20, 6);
}

void info(int ic, int il)
{
	textbackground(11);
	system("cls");
	textcolor(0);
	// Linha 1 => Borda de cima
	gotoxy(ic,il);	  printf(" ___            __           ");  
	gotoxy(ic,(il+1));printf("|_ _|  _ __    / _|   ___   ");  
	gotoxy(ic,(il+2));printf(" | |  |  _ \\  | |_   / _ \\"); 
	gotoxy(ic,(il+3));printf(" | |  | | | | |  _| | (_) | ");
	gotoxy(ic,(il+4));printf("|___| |_| |_| |_|    \\___/ ");
	
	gotoxy(ic,il);	   
	ic = 19;
	il = 6;
	
	gotoxy((ic),(il+1));printf("%c%c%c%c%c",219,219,219,219,219);  
	gotoxy((ic+15),(il+1));printf("%c%c%c%c",219,219,219,219,219);
	
	gotoxy((ic+2),(il+2)); printf("%c",219);
	gotoxy((ic+7),(il+2)); printf("%c%c%c%c",219,219,219,219);
	gotoxy((ic+15),(il+2)); printf("%c",219);
	gotoxy((ic+22),(il+2)); printf("%c%c%c",219,219,219);
	
	gotoxy((ic+2),(il+3));
	printf("%c",219);
	gotoxy((ic+7),(il+3)); printf("%c",219);
	gotoxy((ic+11),(il+3)); printf("%c",219);
	gotoxy((ic+15),(il+3)); printf("%c%c%c%c",219,219,219,219);
	gotoxy((ic+21),(il+3)); printf("%c",219);
	gotoxy((ic+25),(il+3)); printf("%c",219);

	gotoxy((ic),(il+4));printf("%c%c%c%c%c",219,219,219,219,219); 
	gotoxy((ic+7),(il+4)); printf("%c",219);
	gotoxy((ic+11),(il+4)); printf("%c",219);
	gotoxy((ic+15),(il+4)); printf("%c",219);
	gotoxy((ic+22),(il+4)); printf("%c%c%c",219,219,219);
	
	gotoxy((ic+15),(il+15));
	
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

