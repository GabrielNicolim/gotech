#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define col 120 
#define lin 45

text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, col, lin, 1, 1}; // Define os limites para linha (35) e coluna (80)

// Funções conio.c
void textcolor(int newcolor);
void textbackground(int newcolor);
void gotoxy(int x, int y);
void cursor (int x);

// Funções de construção do programa

// Apresenta tela de inicio
void inicio(); 
// Função utilizada para a borda
void borda(int cf, int cb, int lc, int ll); // (cor de fundo, cor da borda, limite de coluna, limite de linha)
// Função utilizada para a criar o disquete
void disquete(int ic, int il); // (coluna de inicio, linha de inicio)
// Fução de construção do menu da tela inicial
void menu_ini();
// Função utilizada para navegar com setasem menus
int navegar_menu(int ini, int fim, int p); // Recebe inicio e fim do menu e a posição do cursor

main()
{
	SetConsoleTitle("Func_Borda"); 		   // Define o nome do console
    system("mode con:cols=120 lines=45");  // Define o tamanho do console
    
	inicio(); // Função de construção da tela inicial
}

void inicio() // Apresenta tela de inicio
{	
	system("cls");
	borda(11, 1, col, lin); 
	disquete((col/3) + 8, 4);
	menu_ini();
	getch(); // Remover
}

void menu_ini()
{
	int inic = (col/2) - 10, inil = (lin)/2; // Se deseja mudar a posição do texto no menu basta alterar uma das variaveis 
	
	// Menu 
	gotoxy(inic, inil); 	printf("*********");
	gotoxy(inic, (inil+2)); printf("*********");
	gotoxy(inic, (inil+4)); printf("*********");
	gotoxy(inic, (inil+6)); printf("*********");
	
	// Chama navegação com setas
	int escolha;
	escolha = navegar_menu(inil, (inil + 6), (inic - 2));
	
	system("cls");
	printf("%d", escolha);
}

int navegar_menu(int ini, int fim, int p)
{
	cursor(0); // Desativa o cursor
	int aux = ini; // Recebe posição da seta
	int c; // Armazena entrada do teclado
	
	do
	{
		gotoxy(p,aux);printf("%c", 62);		
		c = getch();
		gotoxy(p,aux);printf(" ");
		
		switch(c) 
		{
			case 72: // Seta para cima
				aux -= 2;
				
				if(aux < ini) aux  = fim;

				gotoxy(p,aux);printf("%c", 62);
				break;
				
			case 80: // Seta para baixo
				aux+=2;
					
				if(aux > fim) aux = ini;
					
				gotoxy(p,aux);printf("%c", 62);
				break;
				
			case 13:
			return (aux - ini)/2; // Retorna o valor da opção seleciona => inicia em 0
			break;	
		}
		
	}while(true);
}
void borda(int cf, int cb, int lc, int ll) // (cor de fundo, cor da borda, limite de coluna, limite de linha)
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
}

void disquete(int ic, int il)
{
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

void textcolor(int newcolor) // Define a cor do texto
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0xf0) | newcolor);
   vActual.attribute = (csbi.wAttributes & 0xf0) | newcolor;
}

void textbackground(int newcolor) // Define a cor do fundo
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0x0f) | (newcolor << 4));
   vActual.attribute = (csbi.wAttributes & 0x0f) | (newcolor << 4);
}

void gotoxy(int x, int y)	// Move o cursor para a coluna e linha desejada
{
  COORD c;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void cursor (int x) { 	// Define se o cursor ira aparecer (1) ou não (0)
	switch (x) {
		case 0: {
			CONSOLE_CURSOR_INFO cursor = {1, FALSE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
		case 1: {
			CONSOLE_CURSOR_INFO cursor = {1, TRUE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
	}
}


