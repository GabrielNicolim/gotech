/* 
   	Fun��o para criar a placa m�e full chinesa ali express chinese democracy edition com drag�o chines
	
	- passe como par�metro (a coluna de inicio, a linha de inicio)
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>

text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 80, 28, 1, 1}; // Define os limites para linha (35) e coluna (80)

// Fun��es conio.c

// Funções conio.c
void textcolor(int newcolor);
void textbackground(int newcolor);
void gotoxy(int x, int y);

// Fun��o utilizada para a criar o disquete
void HDD(int ic, int il);

main()
{
	SetConsoleTitle("Func_HDD"); 		 // Define o nome do console
    system("mode con:cols=80 lines=28");  // Define o tamanho do console
	
	textbackground(3);
	system("cls");
	
	HDD(20, 4);
	
	gotoxy(25,25);	// tirar o exit do programa de perto
}

void HDD(int ic, int il)
{
	//formar a carcaça inicial e os parafuso:
	textbackground(0);
	for(int i = 0; i < 12; i++) 
	{	
		gotoxy(ic,il+i); printf("                     ");
	}
	//parafusos
	textcolor(7);	
	gotoxy(ic+1,il);		printf("%c                 %c",220,220);
	gotoxy(ic+1,il+5);		printf("%c                 %c",220,220);
	gotoxy(ic+1,il+11);		printf("%c                 %c",223,223);
	
	gotoxy(ic+6,il+1);		printf("%c%c%c%c%c%c%c%c%c",220,220,219,219,219,219,219,220,220);
	gotoxy(ic+4,il+2);		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",220,219,219,219,219,219,219,219,219,219,219,219,220);
	gotoxy(ic+4,il+3);		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219);		//disco magn�tico
	gotoxy(ic+4,il+4);		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219);		//e parafusos
	gotoxy(ic+5,il+5);		printf("%c%c%c%c%c%c%c%c%c%c%c",223,219,219,219,219,219,219,219,219,219,223);
	gotoxy(ic+8,il+6);		printf("%c%c%c%c%c",223,223,223,223,223);
		
	
	textcolor(2);
	gotoxy(ic+10,il+7);		printf("%c%c%c%c%c%c%c%c",220,220,220,220,220,220,220,220);
	gotoxy(ic+10,il+8);		printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219); // pcb
	gotoxy(ic+12,il+9);		printf("%c%c%c%c%c%c",219,219,219,219,219,219);
	gotoxy(ic+13,il+10);	printf("%c%c%c%c%c",219,219,219,219,219);
	textcolor(8);
	gotoxy(ic+14,il+8);		printf("%c%c%c",219,219,219);
	gotoxy(ic+15,il+9);		printf("%c%c",219,219);
	
	textcolor(7);
	gotoxy(ic+3,il+6);		printf("%c",220);
	gotoxy(ic+3,il+7);		printf("%c%c%c",219,219,220);										//baia para a agulha
	gotoxy(ic+3,il+8);		printf("%c%c%c%c%c",219,219,219,219,220);
	gotoxy(ic+3,il+9);		printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,220,220);
	gotoxy(ic+3,il+10);		printf("%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,220,220);
	
	textcolor(8);
	textbackground(7);
	gotoxy(ic+9,il+5);		printf("%c",219);
	gotoxy(ic+8,il+6);		printf("%c%c",219,219);	
	gotoxy(ic+7,il+7);		printf("%c%c%c",219,219,219);			//agulha
	gotoxy(ic+6,il+8);		printf("%c%c%c",219,219,219);	
	gotoxy(ic+5,il+9);		printf("%c%c%c%c",219,219,219,219);
	gotoxy(ic+6,il+10);		printf("%c%c",223,223);	
	
	textcolor(0);
	gotoxy(ic+9,il+3);		printf("%c%c%c",220,219,220);		///motor para o disco
	gotoxy(ic+10,il+4);		printf("%c",223);
	
	textcolor(0);
		
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

