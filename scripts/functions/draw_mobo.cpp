/* 
   	Função para criar a placa mãe full chinesa ali express chinese democracy edition dragão chines
	
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
void mobo(int ic, int il);

main()
{
	SetConsoleTitle("Func_Mobo"); 		 // Define o nome do console
    system("mode con:cols=80 lines=28");  // Define o tamanho do console
	
	textbackground(3);
	system("cls");
	
	mobo(20, 4);
	
	gotoxy(25, 25);	// tirar o exit do programa de perto
}

void mobo(int ic, int il)
{
	
	// Construir o PCB bruto
	textbackground(0);
	for(int i = 0; i < 10; i++){
		gotoxy(ic, il+i); printf("                    ");
	}
	
	//Construir os detalhes
	textcolor(7);
	gotoxy(ic, (il+1)); printf("%c%c",219,219);
	gotoxy(ic, (il+2)); printf("%c%c    %c  %c",219,219,219,219);
	gotoxy(ic, (il+3)); printf("%c%c    %c  %c",219,219,219,219);	//IO traseiro e socket
	gotoxy(ic, (il+4)); printf("%c%c",219,219);
	gotoxy(ic, (il+5)); printf("%c%c",219,219);	//externo 7=cinza 14=brilhino
	
	textcolor(14);
	gotoxy((ic+7), (il+2)); printf("%c%c",219,219);
	gotoxy((ic+7), (il+3)); printf("%c%c",219,219);
	
	textcolor(2);
	gotoxy((ic+13), (il+1)); printf("%c %c  %c%c",219,219,219,219);
	gotoxy((ic+13), (il+2)); printf("%c %c",219,219);
	gotoxy((ic+13), (il+3)); printf("%c %c",219,219);		//slots de ram e etc
	gotoxy((ic+13), (il+4)); printf("%c %c",219,219);
	
	textcolor(8);
	gotoxy((ic+18), (il+3)); printf("%c%c",219,219);    //conectores 24 pinos e etc
	gotoxy((ic+18), (il+4)); printf("%c%c",219,219);
	
	gotoxy((ic+4), (il+6)); printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);  //slots pci-e
	gotoxy((ic+4), (il+8)); printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
	
	textcolor(12);
	gotoxy((ic+15), (il+6)); printf("%c%c",219,219); //dissipador do chipset
	gotoxy((ic+15), (il+7)); printf("%c%c",219,219);
	
	textcolor(15);
	gotoxy((ic+14), (il+9)); printf("%c%c%c%c",219,219,219,219); //conectores frontais
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

