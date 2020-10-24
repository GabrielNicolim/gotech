#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

// Vers�o 1.2
#define versao 1.2

// Defini��o de cores 
#define cor_fundo 3
#define cor_borda 1
#define cor_texto 15
#define cor_destaque 0

text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 120, 40, 1, 1}; // Define os limites para linha (35) e coluna (80)

// Fun��es conio.c
void textcolor(int newcolor);
void textbackground(int newcolor);
void gotoxy(int x, int y);
void cursor (int x);
void clreol(int x);

// Fun��es de constru��o do programa

// Apresenta o menu e a vers�o
void loading();
// Apresenta tela de inicio
void inicio(); 
// Fun��o utilizada para a borda
void borda(int cf, int cb, int lc); // (cor de fundo, cor da borda, limite de coluna, limite de linha)
// Fun��o utilizada para a criar o disquete
void disquete(int ic, int il); // (coluna de inicio, linha de inicio)

// Fun��o utilizada para navegar com setasem menus
int navegar_menu(int ini, int fim, int p); // Recebe inicio e fim do menu e a posi��o do cursor

// Menu 

// Fu��o de constru��o do menu da tela inicial
void menu_ini();

// Fun��o que finaliza a execu��o do programa no menu
void sair();

// Fun��o para apresentar as Informa��es do Sistema
void info_de_sistema();

// Fun��o para gerar o sub menu de pesquisa
void sub_menu();


main()
{
	SetConsoleTitle("GoTech"); 		   // Define o nome do console
    system("mode con:cols=120 lines=40");  // Define o tamanho do console
    
    loading();
	inicio(); // Fun��o de constru��o da tela inicial
}

void loading()
{
	borda(cor_fundo, cor_borda, 120); 
	cursor(0);
	textcolor(cor_texto);
	
	// Apresenta��o de vers�o 
	
	gotoxy(99, 30); printf("Versao %.1f", versao);
	
	gotoxy(15, 30); printf("GoTech");
	
	gotoxy(38, 10); printf("Aguarde, estamos preparando tudo para voce!");
	textcolor(RED); // Loading vermelho
	for(int i = 0; i <= 52; i++)
	{
		gotoxy(32+i, 20);printf("%c", 219);
		Sleep(20);
	}
	textcolor(cor_texto);
	gotoxy(38, 10); printf("       Tudo pronto! Podemos iniciar                               ");
	Sleep(3000);
}

void inicio() // Apresenta tela de inicio
{	
	borda(cor_fundo, cor_borda, 120); 
	disquete(50, 6);	
	menu_ini();
}

void menu_ini()
{	
	int inic = 50, inil = 19; // Se deseja mudar a posi��o do texto no menu basta alterar uma das variaveis 
	
	// Menu 
	textcolor(cor_texto);
	gotoxy(inic, inil); 	printf("Cadastro");
	gotoxy(inic, (inil+2)); printf("Pesquisa");
	gotoxy(inic, (inil+4)); printf("Info do Sistema");
	gotoxy(inic, (inil+6)); printf("Sair");
	
	// Chama navega��o com setas
	int escolha;
	escolha = navegar_menu(inil, (inil + 6), (inic - 2));
	
	switch(escolha)
	{
		case 0:
			break;
		case 1:
			sub_menu();
			break;
		case 2:
			info_de_sistema();
			break;
		case 3:
			sair();
			break;
	}
}

void sub_menu()
{
	borda(cor_fundo, cor_borda, 120);
	
	int inic = 50, inil = 19; // Se deseja mudar a posi��o do texto no menu basta alterar uma das variaveis 
	
	// Menu 
	textcolor(cor_texto);
	gotoxy(inic, inil); 	printf("Geral");
	gotoxy(inic, (inil+2)); printf("Pesquisa por Codigo");
	gotoxy(inic, (inil+4)); printf("Pesquisa por Nome");
	gotoxy(inic, (inil+6)); printf("Retornar ao Inicio");
	
	int escolha;
	escolha = navegar_menu(inil, (inil + 6), (inic - 2));
	
	switch(escolha)
	{
		case 0:
			break;
		case 1:
			
			break;
		case 2:
			
			break;
		case 3:
			inicio();
			break;
	}
}

void info_de_sistema() // Apresenta as informa��es do sistema
{
	borda(cor_fundo, cor_borda, 120);

	
	int inix = 20, iniy = 9; // Controla o eixo x e y das informa��es
	
	// Apresenta as informa��es do sistema
	textcolor(0);
	gotoxy(54, 4);  printf("Info do Sistema");
	textbackground(cor_fundo);
	
	textcolor(cor_destaque);
	gotoxy(inix, iniy -2); printf("Empresa: ");
	textcolor(cor_texto);
	printf("GoTech");
	
	textcolor(cor_destaque);
	gotoxy(inix, iniy);  printf("Nomes: ");
	textcolor(cor_texto);
	printf("Gabriel Nicolim e Felipe Lima");
	
	textcolor(cor_destaque);
	gotoxy(inix, iniy + 2);  printf("Numeros: ");
	textcolor(cor_texto);
	printf("8 e 6");
	
	textcolor(cor_destaque);
	gotoxy(inix, iniy + 4);  printf("Turmas: ");
	textcolor(cor_texto);
	printf("71A");
	
	textcolor(cor_destaque);
	gotoxy(inix, iniy + 6);  printf("Ano: ");
	textcolor(cor_texto);
	printf("2020");
	
	textcolor(cor_destaque);
	gotoxy(inix, iniy + 8);  printf("Sobre o software: ");
	textcolor(cor_texto);
	printf("Nosso software, que hoje se encontra na versao %.1f, se destina a", versao);
	gotoxy(inix, iniy + 10); printf("simular um sistema de gerenciamento de estoque de uma loja de informatica em C/C++.");
	gotoxy(inix, iniy + 12); printf("Para a realizacao desse projeto utilizamos funcoes de cabecalho da conio.c e conio.h.");
	gotoxy(inix, iniy + 14); printf("Podem ser registrados perifericos e pecas de computador.");
	
	textcolor(cor_destaque);
	gotoxy(inix, iniy + 16); printf("Agradecimentos: ");
	textcolor(cor_texto);
	printf("Deixamos nosso agradecimento a professora Ariane Scarelli e ");
	gotoxy(inix, iniy + 18); printf("Katia Zambombon, por compartilharem conosco parte de seus conhecimentos.");
	
	gotoxy(inix, iniy + 21); printf("Pressione 0 para retornar ao menu"); 
	
	char c;
	
	while(true)
	{
		fflush(stdin); 
		c =	getch();
		
		if(c == '0') inicio(); // Retorna ao inicio se a tecla 0 for pressionada
	}
}

void sair() // Finaliza a execu��o do programa
{
	borda(cor_fundo, cor_borda, 120);
	
	textcolor(cor_texto);
	gotoxy(42, 17); printf("Obrigado por utilizar nosso programa!");
	textcolor(cor_fundo);
	
	gotoxy(80, 37);
	exit(1);
}


int navegar_menu(int ini, int fim, int p)
{
	cursor(0); // Desativa o cursor
	int aux = ini; // Recebe posi��o da seta
	int c; // Armazena entrada do teclado
	
	do
	{
		gotoxy(p,aux);printf("%c", 62);	
			
		fflush(stdin); 
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
			return (aux - ini)/2; // Retorna o valor da op��o seleciona => inicia em 0
			break;	
		}
		
	}while(true);
}

void borda(int cf, int cb, int lc) // (cor de fundo, cor da borda, limite de coluna, limite de linha)
{
	textbackground(cf); // Define cor do fundo
	system("cls"); 
	
	for (int i = 9; i <= (lc - 8); i++) // Parte de cima da borda
	{
		textcolor(cb);
		gotoxy(i,2);printf("%c",219);
	}
	for (int i = 9; i <= (lc - 8); i++) // Parte de baixo da borda 
	{
		textcolor(cb);
		gotoxy(i,33);printf("%c",219);
	}
	for (int i=2; i <= 33; i++) // Borda esquerda 
	{
		textcolor(cb);
		gotoxy(10,i);printf("%c",219);
		gotoxy(9,i);printf("%c",219);
	}
	for (int i=2; i <= 33; i++) // Borda direita
	{
		textcolor(cb);
		gotoxy(112,i);printf("%c",219);
		gotoxy(111,i);printf("%c",219);
	}
	
	printf("\n\n\n\n");
}

void disquete(int ic, int il)
{
	
	// Linha 1 => Borda de cima
	textcolor(0);
	gotoxy(ic, il); 
	for(int i = 0; i < 20; i++) putchar(219);
	
	// Linha 2  - tracinho
	gotoxy(ic, (il+1));
	printf("%c", 219);
	
	for(int i = 0; i < 18; i++) 
	{
		if(i == 2 or i == 15) textcolor(8);
		if(i > 2  and i < 15) 
		{
			textcolor(7);
			if(i > 4 && i < 8) textcolor(0);
		}
		else textcolor(9);
		putchar(219);
	}
	
	textcolor(0);
	printf("%c", 219);
	
	// Linha 3  - tracinho
	gotoxy(ic, (il+2));
	printf("%c", 219);
	
	for(int i = 0; i < 18; i++) 
	{
		if(i == 2 or i == 15) textcolor(8);
		if(i > 2  and i < 15) 
		{
			textcolor(7);
			if(i > 4 && i < 8) textcolor(0);
		}
		else textcolor(9);
		putchar(219);
	}
	
	textcolor(0);
	printf("%c", 219);
	
	// Linha 4
	
	gotoxy(ic, (il+3));
	
	printf("%c", 219);
	textcolor(9);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	
	// Linha 5
	
	gotoxy(ic, (il+4));
	printf("%c", 219);
	textcolor(9);

	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	
	//Linha 6 - rodelinha com tracin
	
	gotoxy(ic, (il+5));
	
	printf("%c", 219);
	for(int i = 0; i < 18; i++) 
	{	
		if(i>6 && i <11) 
		{
		textcolor(7);
		if(i == 9) textcolor(8);
		}
		else textcolor(9);
		putchar(219);
		
	}
	textcolor(0);
	printf("%c", 219);
	
	//Linha 7 - rodelinha 
	
	gotoxy(ic, (il+6));
	
	printf("%c", 219);
	for(int i = 0; i < 18; i++) 
	{	
		if(i>6 && i <11) textcolor(7);
		else textcolor(9);
		putchar(219);
		
	}
	textcolor(0);
	printf("%c", 219);
	
	// Linha 8
	
	gotoxy(ic, (il+7));
	
	printf("%c", 219);
	textcolor(9);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	
	// Linha 9
	
	gotoxy(ic, (il+8));
	
	printf("%c", 219);
	textcolor(9);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	
	// Linha 10 => Borda de baixo
	textcolor(0);
	gotoxy(ic, (il+9)); 
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

void cursor (int x) { 	// Define se o cursor ira aparecer (1) ou n�o (0)
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

void clreol(int x)
{
   for(int i=0; i < x; i++)
           printf(" ");
       for(int i=0; i < x; i++)
           printf("\b");
}

