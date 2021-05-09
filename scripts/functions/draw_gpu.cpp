/* 
   	Função para criar uma gpu generica e provavelmente fake
	
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

// Função utilizada para a criar a gpu
void gpu(int ic, int il);

main()
{
	SetConsoleTitle("Func_Gpu"); 		 // Define o nome do console
    system("mode con:cols=80 lines=28");  // Define o tamanho do console
	
	textbackground(3);
	system("cls");
	
	gpu(20, 4);
	
	gotoxy(25,25);
}

void gpu(int ic, int il)
{
	
	// Traseira da placa de video
	textcolor(8);
	gotoxy(ic, il);	printf("%c%c", 219, 219);
	for(int i = 0; i < 10; i++){
		gotoxy(ic+2, il+i);	printf("%c", 219);
	}
	
	//fundo principal	
	textbackground(7);
	for(int i = 0; i < 9; i++){
		gotoxy(ic+3,il+i); printf("                                   ");
	} 
	
	//adesivo generico
	textbackground(2);
	gotoxy(ic+3,il+2);	printf("                                   ");
	gotoxy(ic+3,il+6);	printf("                                   ");
	textbackground(10);
	gotoxy(ic+3,il+3);	printf("                                   ");
	gotoxy(ic+3,il+4);	printf("                                   ");
	gotoxy(ic+3,il+5);	printf("                                   ");
	
	textbackground(8); 
	textcolor(0);
	// Linha 2  - começo do cooler	
	gotoxy(ic+18, il+1); printf("   %c      ",219);
	// Linha 3  
	gotoxy(ic+16, il+2); printf("      %c       ",219);	
	// Linha 4
	gotoxy(ic+15, il+3); printf(" %c%c     %c  %c%c%c  ",220,220,219,220,220,219);
	// Linha 5	- meio do cooler
	gotoxy(ic+14, il+4); printf("    %c%c%c%c%c%c%c%c      ",223,223,220,220,219,219,223,223);	
	//Linha 6 - 
	gotoxy(ic+15, il+5); printf("       %c%c%c%c      ",219,223,220,220);
	//Linha 7
	gotoxy(ic+16, il+6); printf("    %c%c    %c   ",220,219,219);	
	// Linha 8 - final do cooler 
	gotoxy(ic+18, il+7); printf(" %c       %c",219,219);	
	
	// Linha 10 => Borda de baixo
	textbackground(8);
	textcolor(14);
	gotoxy(ic+8, il+9); printf("%c %c %c %c %c %c %c %c",219,219,219,219,219,219,219,219);

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

