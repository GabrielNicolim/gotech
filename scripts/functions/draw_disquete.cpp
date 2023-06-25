/* 
   	Função para criar o disquete
	
	- passe como parâmetro (a coluna de inicio, a linha de inicio)
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

//text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 80, 28, 1, 1}; // Define os limites para linha (35) e coluna (80)

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
	
	textbackground(3);
	system("cls");
	
	disquete(20, 4);
}

void disquete(int ic, int il){
	
	//quadrados basicos	
	textbackground(0);
	for(int i = 0; i < 10; i++){
		gotoxy(ic, il+i); printf("                    ");
	}
	
	textbackground(9);
	for(int i = 1; i < 9; i++){
		gotoxy(ic+1, il+i); printf("                  ");
	}
	
	//detalhes internos
	textbackground(7);
	textcolor(0);
	gotoxy(ic+3, il+1); printf("  %c%c          ",219,219);
	gotoxy(ic+3, il+2); printf("  %c%c          ",219,219);
	
	textcolor(8);
	gotoxy(ic+8, il+5); printf("  %c ",219);
	gotoxy(ic+8, il+6); printf("    ");
	
	gotoxy(25,25);
}

void textcolor(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0xf0) | newcolor);
   //vActual.attribute = (csbi.wAttributes & 0xf0) | newcolor;
}

void textbackground(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0x0f) | (newcolor << 4));
   //vActual.attribute = (csbi.wAttributes & 0x0f) | (newcolor << 4);
}

void gotoxy(int x, int y)
{
  COORD c;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

