/* 
   	Função para borda e cor de texto e fundo
	
	- passe como parâmetro (cor de fundo, cor de texto, cor da borda, limite de coluna, limite de linha)
	
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define cor_fundo 3
#define cor_borda 1
#define cor_texto 15
#define cor_destaque 0
#define RED 12

//text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 120, 35, 1, 1}; // Define os limites para linha (35) e coluna (80)

// Funções conio.c
void textcolor(int newcolor);
void textbackground(int newcolor);
void gotoxy(int x, int y);

// Função utilizada para a borda
void borda();

main()
{
	SetConsoleTitle("Func_Borda"); 		   // Define o nome do console
    system("mode con:cols=160 lines=37");  // Define o tamanho do console
	
	DWORD dwWidth = GetSystemMetrics(SM_CXSCREEN);  // essas funções pegam o tamanho da tela em pixels (ex: 1920 x 1080)
	DWORD dwHeight = GetSystemMetrics(SM_CYSCREEN);
    
    HWND wh = GetConsoleWindow(); // precisa disso pro MoveWindow  (HWND é como é indentificada a janela do Windows "identificador de janelas" 
    MoveWindow(wh, dwWidth/8 , dwHeight/8 , 1300, 720, TRUE); // move a janela para uma cordenada determinada a setando num tamanho determinado de 20 em 20
	
	borda();
	
	gotoxy(25,37); 
}

void borda()
{
	textbackground(cor_fundo); // Define cor do fundo
	system("cls"); 		//limpa sempre a tela quando é chamada
	
	textcolor(cor_borda);
	for (int i=2; i <= 33; i++) // Borda esquerda e direita
	{
		gotoxy(9,i);printf("%c%c                                                                                                                                            %c%c",219,219,219,219);
	}
	
	for (int i = 9; i <= (160 - 8); i++) // Parte de cima da borda
	{
		gotoxy(i,2);printf("%c",219);
	}
	for (int i = 9; i <= (160 - 8); i++) // Parte de baixo da borda 
	{
		gotoxy(i,33);printf("%c",219);
	}
			
	textcolor(cor_texto); // Define cor do texto
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

