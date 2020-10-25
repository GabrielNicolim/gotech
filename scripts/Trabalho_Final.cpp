#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

// Versão 1.5
#define versao 1.5

// Definição de cores 
#define cor_fundo 3
#define cor_borda 1
#define cor_texto 15
#define cor_destaque 0

text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 120, 40, 1, 1}; // Define os limites para linha (35) e coluna (80)

// Funções conio.c
void textcolor(int newcolor);
void textbackground(int newcolor);
void gotoxy(int x, int y);
void cursor (int x);
void clreol(int x);

// Funções de construção do programa

// Função para gerar a parte visual do cadastro 
void cadastro_visual();
// Apresenta o menu e a versão
void loading();
// Apresenta tela de inicio
void inicio(); 
// Função utilizada para a borda
void borda(int cf, int cb, int lc); // (cor de fundo, cor da borda, limite de coluna, limite de linha)
// Função utilizada para criar o disquete
void disquete(int ic, int il); // (coluna de inicio, linha de inicio)
// Função para criar a logo GoTech
void logo(int ic, int il);
// Função utilizada para criar uma lupinha
void lupa(int ic, int il); // (coluna de inicio, linha de inicio)
// Função para geração de cpu
void cpu(int ic, int il);
// Função de geração da gpu
void gpu(int ic, int il);
// Função para geração da memória ram
void ram(int ic, int il);
// Função de geração da placa mãe
void mobo(int ic, int il);
// Função para fazer a consulta dos dados já salvos
void consulta_geral();
// Função para apagar dados do .bin por id
void apaga_dados();
// Função para gerar uma tabela
void gera_tabela(int li);  //
//Função para colocar os dados na tabela
void completa_tabela(int linha);

// Função utilizada para navegar com setasem menus
int navegar_menu(int ini, int fim, int p); // Recebe inicio e fim do menu e a posição do cursor

// Menu 

// Recebe os dados de registro
void cadastro_recebimento();

// Fução de construção do menu da tela inicial
void menu_ini();

// Função para gerar o sub menu de pesquisa
void sub_menu();

// Função para apresentar as Informações do Sistema
void info_de_sistema();

// Função que finaliza a execução do programa no menu
void sair();

//Ponteiro para arquivo
FILE *fp;	

int random_menu; // Var que armazena numero aleatório ente 0 e 4 para gerar um menu diferente 

void abrir_arquivo()
{
	if((fp = fopen("estoque.bin", "ab+")) == NULL) 
	{
		gotoxy(18,11);printf("Erro na abertura do arquivo"); //caso haja um problema com o arquivo
		exit(1);
	}
}

int abrir_arquivo_alterar()
{
	if((fp = fopen("estoque.bin", "rb+")) == NULL) 
	{
		gotoxy(18,11);printf("Nao foram encontrados dados, cadastre algo!");
		getch();
		return 1;
	}
	else
		return 0;
}

struct estrutura
{
	int id;
	char nome[50];
	int quantidade;
	char tipo[1];
	float preco_unitario;
	bool excluido;
}produto;


main()
{
	SetConsoleTitle("GoTech"); 		   // Define o nome do console
    system("mode con:cols=120 lines=40");  // Define o tamanho do console
	srand(time(NULL));
	
	random_menu = rand() % 4;
	
    loading();
	inicio(); // Função de construção da tela inicial
}

void loading()
{
	borda(cor_fundo, cor_borda, 120); 
	cursor(0);
	textcolor(cor_texto);
	
	// Apresentação de versão 
	
	gotoxy(99, 30); printf("Versao %.1f", versao);
	
	gotoxy(15, 30); printf("GoTech");
	
	gotoxy(38, 10); printf("Aguarde, estamos preparando tudo para voce!");
	textcolor(RED); // Loading vermelho
	for(int i = 0; i <= 52; i++)
	{
		gotoxy(32+i, 20);printf("%c", 219);
		Sleep(10);
	}
	textcolor(cor_texto);
	gotoxy(38, 10); printf("       Tudo pronto! Podemos iniciar                               ");
	Sleep(2000);
}

void inicio() // Apresenta tela de inicio
{	
	borda(cor_fundo, cor_borda, 120); 
	//disquete(83, 6);
	//logo(20, 8);
	
	// Aleatorio
	 
	switch(random_menu)
	{
		case 0:
			disquete(18, 6); // Disquete + logo
			logo(48, 8);
			break;
		case 1:
			cpu(18, 6); // cpu + logo
			logo(48, 8);
			break;	
		case 2:
			logo(32, 8); // logo
			break;
		case 3:
			ram(37, 5); // Ram + logo
			logo(32, 11);
			break;
		case 4:
			mobo(83, 6); // placa mae + logo
			logo(20, 8);
			break;		
	}
	
		
	menu_ini();
}

void menu_ini()
{	
	int inic = 50, inil = 19; // Se deseja mudar a posição do texto no menu basta alterar uma das variaveis 
	
	// Menu 
	textcolor(cor_texto);
	gotoxy(inic, inil); 	printf("Cadastro");
	gotoxy(inic, (inil+2)); printf("Pesquisa");
	gotoxy(inic, (inil+4)); printf("Info do Sistema");
	gotoxy(inic, (inil+6)); printf("Sair");
	
	// Chama navegação com setas
	int escolha;
	escolha = navegar_menu(inil, (inil + 6), (inic - 2));
	
	switch(escolha)
	{
		case 0:
			cadastro_visual();
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

void cadastro_visual()
{
	int x = 20, y = 8;
	char dnv='n';
	abrir_arquivo();
	
	cursor(1);
	do{
		
		borda(cor_fundo, cor_borda, 120);
	
		cursor(1);
		textcolor(cor_texto);
		gotoxy(50, 4); printf("Cadastro de Produtos");
		
		gotoxy(x, y); printf("Id do produto: ");				
		gotoxy(x, y + 2); printf("Nome do Produto: ");		
		gotoxy(x, y + 4); printf("Quantidade: ");			
		gotoxy(x, y + 6); printf("Tipo: ");					
		gotoxy(x, y + 8); printf("Preco Unitario: ");		
					
		cadastro_recebimento();
		
		gotoxy(x, y + 20); printf("Deseja realizar mais um cadastro? (S/N):  ");
	
		do{
			fflush(stdin);
			dnv = getche();
			if(dnv != 'n' && dnv != 'N' && dnv != 's' && dnv != 'S')
				{
					Sleep(2000);
					gotoxy(x, y + 20); clreol(70); printf("Valor invalido! digite novamente (S/N): ");
				}
		}while(dnv != 'n' && dnv != 'N' && dnv != 's' && dnv != 'S');
		
		system("cls");
	}while(dnv == 's' || dnv == 'S');
	
	system("cls");
	inicio();
}

void cadastro_recebimento()
{
	int x = 20, y = 8;
	
	fflush(stdin);
	gotoxy(x+15, y); scanf("%d",&produto.id); 				fflush(stdin);
	gotoxy(x+17, y+2); gets(produto.nome);					fflush(stdin);
	gotoxy(x+12, y+4); scanf("%d",&produto.quantidade);		fflush(stdin);
	gotoxy(x+6, y+6);  gets(produto.tipo);					fflush(stdin);
	gotoxy(x+16, y+8); scanf("%f",&produto.preco_unitario);	fflush(stdin);
	produto.excluido = false;
	
	char conf; // variavel de confirmação do loop seguinte
	
	gotoxy(x, y+14); printf("Deseja salvar os dados? (S/N): ");
	
	do{
       	gotoxy(x+31,y+14); 
		fflush(stdin);
		conf = getche();
		fflush(stdin);
		
		if(conf != 's' && conf != 'S'	&& conf != 'n' && conf != 'N')    //verificação de valores
		{
			gotoxy(x+31,y+14); Sleep(500); clreol(2);
				
			gotoxy(x+50,y+14); printf("Digite um caractere valido!");
			Sleep(2000);
			gotoxy(x + 49, y + 14); clreol(30);
		}
   	}while( conf != 's' && conf != 'S'	&& conf != 'n' && conf != 'N' );
   	
   	if( conf == 's' || conf == 'S' )
   	{
	   	if(fwrite(&produto, sizeof(produto), 1, fp) != 1) 
		{
			textcolor(RED);
			gotoxy(x+50,y+14); printf("Erro na escrita do arquivo");
			textcolor(cor_texto);
		}
		else
		{
			fflush( fp );
			//fclose(fp);  
			system("cls");
			borda(cor_fundo, cor_borda, 120);
			textcolor(15);
			gotoxy(18,11); printf("Dados salvos com sucesso!");
		}
		cursor(0);
		Sleep(2000);
		cursor(1);
	}
}

void consulta_geral()
{
	int ir_proxima=0, sair, linha = 7;
	
	abrir_arquivo();
	
	rewind(fp); // seta a leitura do arquivo na posição inicial do arquivo ("1º linha e coluna")
	
	gera_tabela(5);
	
	do
	{
		if(fread(&produto, sizeof(produto), 1, fp) == 1) {
			if(produto.excluido == false) {
				ir_proxima++;
				completa_tabela(linha);
				linha+=2;
				if(ir_proxima == 12)
				{
					ir_proxima = 0;
					textcolor(0);
					gotoxy(20, 31); printf("Deseja ir para a proxima pagina (S-Sim/N-Nao): ");
					char pag = '0';
					while(pag != 'S' && pag != 's' && pag != 'N' && pag != 'n' && pag != '\r')
					{
						if(pag != 'S' && pag != 's' && pag != 'N' && pag != 'n' && pag != '\r')
						{
							gotoxy(20,32); printf("Digite um valor válido!");
						}
						gotoxy(68,31); clreol(2); pag = getche();
					}
					if(pag == 's' || pag == 'S')
					{
						system("cls");
						linha = 6;
						gera_tabela(5);
					}
					else
					{
						system("cls");
						break;
					}
				}
			}
		}
	}while ( !feof(fp) );
	
	gotoxy(20,31); printf("Pressione uma tecla para voltar ao menu...");
	getch();
	fflush(stdin);	
	system("cls");
	textcolor(15);
	inicio();
}

void gera_tabela(int li)
{
	int ci=20;
	system("cls");
	borda(cor_fundo, cor_borda, 120);
	
	textcolor(15);
	gotoxy(ci,4);	printf ("+---------------------------------------------------------------------------------+");
	gotoxy(ci,5);	printf ("|   ID   |      Nome         |  Preço Unitário  |    Quantidade   |     Tipo      |");
	gotoxy(ci,6);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,7);	printf ("|        |                   |                  |                 |               |");
	gotoxy(ci,8);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,9);	printf ("|        |                   |                  |                 |               |");
	gotoxy(ci,10);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,11);	printf ("|        |                   |                  |                 |               |");
	gotoxy(ci,12);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,13);	printf ("|        |                   |                  |                 |               |");
	gotoxy(ci,14);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,15);	printf ("|        |                   |                  |                 |               |");
	gotoxy(ci,16);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,17);	printf ("|        |                   |                  |                 |               |");
	gotoxy(ci,18);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,19);	printf ("|        |                   |                  |                 |               |");
	gotoxy(ci,20);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,21);	printf ("|        |                   |                  |                 |               |");
	gotoxy(ci,22);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,23);	printf ("|        |                   |                  |                 |               |");
	gotoxy(ci,24);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,25);	printf ("|        |                   |                  |                 |               |");
	gotoxy(ci,26);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,27);	printf ("|        |                   |                  |                 |               |");
	gotoxy(ci,28);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,29);	printf ("|        |                   |                  |                 |               |");
	gotoxy(ci,30);	printf ("+---------------------------------------------------------------------------------+");
	
}

void completa_tabela(int linha)
{
	gotoxy(24,linha);  printf("%d", produto.id);
	gotoxy(31,linha); printf("%s", produto.nome);
	//gotoxy(ci+30,li);printf("%s", produto.marca);
	gotoxy(51,linha); printf("%.2f", produto.preco_unitario);
	gotoxy(71,linha); printf("%d", produto.quantidade);
	gotoxy(89,linha); printf("%s", produto.tipo);
	gotoxy(1,60);
}

void excluir_dados() //exclusao lógica
{
	
	system("cls");
	abrir_arquivo_alterar();
	borda(cor_fundo, cor_borda, 120);
	textcolor(15); 
	int aux_codigo,F;
	long fposicao;
	char conf;
	//gotoxy(20,15); printf("Deseja excluir apenas um dado ou o programa todo?");
	//sdsdsds
	
	do{	
	    gotoxy(20,7); printf("Digite o codigo do produto a ser excluido (digite zero para encerrar): ");
	    scanf("%d", &aux_codigo );
	    if (aux_codigo!=0)
	    {
			F = 0;
			rewind(fp);
		    do
		    {
				fread( &produto,sizeof(produto),1,fp);
				if ( produto.id == aux_codigo && produto.excluido == false ) //Se houver um produto com o id e que não foi excluído
				{
			   		F = 1;
			   		fposicao = ftell(fp); // guarda a posição do registro atual do arquivo
			   		gotoxy(20,4);	printf ("|   ID   |      Nome         |  Preço Unitário  |    Quantidade   |     Tipo      |");
			   		completa_tabela(5); //Apresenta-se ao usuário o registro a ser excluído
				   	gotoxy(25,22); printf("Confirma exclusao ? (S/N): ");
				   	// exclusão é uma operação crítica, por isso, sempre será confirmada pelo usuário
					fflush(stdin);
					do 
				   	{
				    	gotoxy(54,22); conf = getche();
				   	}while( conf != 's' && conf != 'S' &&
					   conf != 'n' && conf != 'N' );
				   
				   	if( conf == 's' || conf == 'S' )
				   	{
				   		//posiciona o ponteiro do arquivo no registro a ser excluido logicamente
						fseek (fp,fposicao-(sizeof(produto)),SEEK_SET); 	//em stdio.h
																			//SEEK_SET indica o início do arquivo
						produto.excluido= true; /*atribuição de 's' para o campo excluído para indicar 
							 			que o registro foi excluído ou desativado (exclusão lógica) */
						if(fwrite (&produto,sizeof(produto),1,fp)==1)
						{
							fflush (fp);
							gotoxy(25,24);printf("Cadastro excluido com sucesso!");
							getch();
							system("cls");
						}	
				   	}
				}
			} while ((!F) && (!feof(fp)));  	
		} 
		if (F==0 && aux_codigo!=0)
		{
			gotoxy(20,15);printf("****** C¢digo nao encontrado! Voltando ao menu! ******");
			getch();
		}
		break;
	}while(aux_codigo!=0);
	Sleep(1000);
	system("cls");
	inicio();
}

void sub_menu()
{
	borda(cor_fundo, cor_borda, 120);
	
	int inic = 45, inil = 19; // Se deseja mudar a posição do texto no menu basta alterar uma das variaveis 
	
	lupa(43,4);
	
	// Menu 
	textcolor(cor_texto);
	gotoxy(inic, inil); 	printf("Geral");
	gotoxy(inic, (inil+2)); printf("Pesquisa por Codigo (não feito ainda)");
	gotoxy(inic, (inil+4)); printf("Pesquisa por Nome (não feito ainda)");
	gotoxy(inic, (inil+6)); printf("Excluir dados");
	gotoxy(inic, (inil+8)); printf("Retornar ao Inicio");
	
	int escolha;
	escolha = navegar_menu(inil, (inil + 8), (inic - 2));
	
	switch(escolha)
	{
		case 0:
			consulta_geral();
			break;
		case 1:
			//pesquisa();
			break;
		case 2:
			//pesquisa();
			break;
		case 3:
			excluir_dados();
			break;
		case 4:
			inicio();
			break;
	}
}

void info_de_sistema() // Apresenta as informações do sistema
{
	borda(cor_fundo, cor_borda, 120);

	
	int inix = 20, iniy = 9; // Controla o eixo x e y das informações
	
	// Apresenta as informações do sistema
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

void sair() // Finaliza a execução do programa
{
	borda(cor_fundo, cor_borda, 120);
	
	textcolor(cor_texto);
	gotoxy(42, 17); printf("Obrigado por utilizar nosso programa!");
	textcolor(cor_fundo);
	fclose(fp);
	gotoxy(80, 37);
	exit(1);
}


int navegar_menu(int ini, int fim, int p)
{
	cursor(0); // Desativa o cursor
	int aux = ini; // Recebe posição da seta
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
			return (aux - ini)/2; // Retorna o valor da opção seleciona => inicia em 0
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

void lupa(int ic, int il)
{
	textcolor(0);
	// Linha 1 - Borda Preta
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

void logo(int ic, int il)
{
	textcolor(0);
	
	gotoxy(ic - 2, il + 6); for(int i = 0; i <= 58; i++) printf("_");
		
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
}

void cpu(int ic, int il)
{	
	// Linha 1 => Borda de cima
	textcolor(0);
	gotoxy(ic, il); 
	for(int i = 0; i < 20; i++) putchar(219);
	
	// Linha 2  - tracinho
	gotoxy(ic, (il+1));

	printf("%c", 219);
	textcolor(7);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	textcolor(6);
	printf("%c", 219);
	textcolor(0);
	
	// Linha 3  - tracinho
	gotoxy(ic, (il+2));
	
	printf("%c", 219);
	textcolor(7);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	textcolor(6);
	printf("%c", 219);
	textcolor(0);
	
	// Linha 4
	
	gotoxy(ic, (il+3));
	
	printf("%c", 219);
	textcolor(7);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	textcolor(6);
	printf("%c", 219);
	textcolor(0);
	
	// Linha 5
	
	gotoxy(ic, (il+4));
	
	printf("%c", 219);
	textcolor(7);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	textcolor(6);
	printf("%c", 219);
	textcolor(0);
	
	//Linha 6 - rodelinha com tracin
	
	gotoxy(ic, (il+5));
	
	printf("%c", 219);
	textcolor(7);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	textcolor(6);
	printf("%c", 219);
	textcolor(0);
	
	//Linha 7 - rodelinha 
	
	gotoxy(ic, (il+6));
	
	printf("%c", 219);
	textcolor(7);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	textcolor(6);
	printf("%c", 219);
	textcolor(0);
	
	// Linha 8
	
	gotoxy(ic, (il+7));
	
	printf("%c", 219);
	textcolor(7);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	textcolor(6);
	printf("%c", 219);
	textcolor(0);
		
	// Linha 9 
	textcolor(0);
	gotoxy(ic, (il+8)); 
	for(int i = 0; i < 20; i++) putchar(219);
	textcolor(6);
	printf("%c", 219);
	textcolor(0);
	
	// Linha 10 => Borda de baixo
	textcolor(6);
	gotoxy((ic+1), (il+9)); 
	for(int i = 0; i < 20; i++) putchar(219);
	textcolor(0);
	
	//escrever cpu
	gotoxy((ic+3), (il+2)); printf("%c%c%c%c",219,219,219,219);
	gotoxy((ic+3), (il+3)); printf("%c",219);
	gotoxy((ic+3), (il+4)); printf("%c",219);      //etra C
	gotoxy((ic+3), (il+5)); printf("%c",219);
	gotoxy((ic+3), (il+6)); printf("%c%c%c%c",219,219,219,219);
	
	gotoxy((ic+8), (il+2)); printf("%c%c%c%c",219,219,219,219);
	gotoxy((ic+8), (il+3)); printf("%c",219);		//Letra P
	gotoxy((ic+11), (il+3)); printf("%c",219);
	gotoxy((ic+8), (il+4)); printf("%c%c%c%c",219,219,219,219);
	gotoxy((ic+8), (il+5)); printf("%c",219);
	gotoxy((ic+8), (il+6)); printf("%c",219);
	
	gotoxy((ic+13), (il+2)); printf("%c",219);
	gotoxy((ic+16), (il+2)); printf("%c",219);
	gotoxy((ic+13), (il+3)); printf("%c",219);
	gotoxy((ic+16), (il+3)); printf("%c",219);		//Letra U
	gotoxy((ic+13), (il+4)); printf("%c",219);
	gotoxy((ic+16), (il+4)); printf("%c",219);
	gotoxy((ic+13), (il+5)); printf("%c",219);
	gotoxy((ic+16), (il+5)); printf("%c",219);
	gotoxy((ic+13), (il+6)); printf("%c%c%c%c",219,219,219,219);
	
	gotoxy((ic), (il+9)); //só pro end do programa não quebrar as coisas

}

void gpu(int ic, int il)
{	
	// Linha 1 => Borda de cima
	gotoxy(ic, il);
	textcolor(8);
	printf("%c%c%c", 219, 219, 219);
	textcolor(7);	
	for(int i = 0; i < 35; i++) putchar(219);
	
	// Linha 2  - começo do cooler
	gotoxy(ic, (il+1));
	textcolor(8);
	printf("  %c", 219);
	for(int i = 0; i < 35; i++)
	{
		textcolor(7);
		if( i>14 && i<25)
			textcolor(8);
		putchar(219);
	}
	
	// Linha 3  
	gotoxy(ic, (il+2));
	
	textcolor(8);
	printf("  %c", 219);
	for(int i = 0; i < 35; i++)
	{
		textcolor(2);
		if( i>12 && i<27)
			textcolor(8);
		putchar(219);
	}
	
	// Linha 4
	
	gotoxy(ic, (il+3));
	
	textcolor(8);
	printf("  %c", 219);
	for(int i = 0; i < 35; i++)
	{
		textcolor(10);
		if( i>11 && i<28)
			textcolor(8);
		putchar(219);
	}
	
	// Linha 5	- meio do cooler
	gotoxy(ic, (il+4));
	
	textcolor(8);
	printf("  %c", 219);	
	for(int i = 0; i < 35; i++)
	{
		textcolor(10);
		if( i>10 && i<29)
			textcolor(8);
		putchar(219);
	}
	
	//Linha 6 - 
	
	gotoxy(ic, (il+5));
	
	textcolor(8);
	printf("  %c", 219);
	for(int i = 0; i < 35; i++)
	{
		textcolor(10);
		if( i>11 && i<28)
			textcolor(8);
		putchar(219);
	}
	
	//Linha 7
	
	gotoxy(ic, (il+6));
	
	textcolor(8);
	printf("  %c", 219);
	for(int i = 0; i < 35; i++)
	{
		textcolor(2);
		if( i>12 && i<27)
			textcolor(8);
		putchar(219);
	}
	
	// Linha 8 - final do cooler 
	
	gotoxy(ic, (il+7));
	
	textcolor(8);
	printf("  %c", 219);
	for(int i = 0; i < 35; i++)
	{
		textcolor(7);
		if( i>14 && i<25)
			textcolor(8);
		putchar(219);
	}
	
	// Linha 9
	
	gotoxy(ic, (il+8));
	
	textcolor(8);
	printf("  %c", 219);
	textcolor(7);	
	for(int i = 0; i < 35; i++) putchar(219);
	
	// Linha 10 => Borda de baixo
	gotoxy(ic, (il+9)); 
	
	textcolor(8);
	printf("  %c", 219);
	textcolor(14);	
	for(int i = 0; i < 35; i++) 
		{
			if(i==4 || i == 18)
			{
				textcolor(0);
				putchar(219);
				textcolor(14);
			}
			if(i>3 && i<18)
			putchar(219);
			else
			printf(" ");
		}
	textcolor(0);
	// Acabou :D
}

void ram(int ic, int il)
{	
	// Linha 1 => Borda de cima
	gotoxy(ic, il); 
	
	textcolor(0); printf("%c", 219);
	
	textcolor(2);
	for(int i = 0; i < 41; i++) putchar(219);
	
	textcolor(0); printf("%c", 219);
	
	// Linha 2  - tracinho
	gotoxy(ic, (il+1));
	
	textcolor(0); printf(" %c", 219);
		
	for(int i = 0; i < 33; i++) 
	{
		textcolor(2);
		if((i+1)%5==0) 
		{
			textcolor(7);
			putchar(219);
		}	
		putchar(219);
	}
	
	textcolor(0); printf("%c ", 219);
	
	// Linha 3  - tracinho
	gotoxy(ic, (il+2));
	
	textcolor(0); printf("%c", 219);
	
	textcolor(2);
	putchar(219);
	for(int i = 0; i < 33; i++) 
	{
		textcolor(2);
		if((i+1)%5==0) 
		{
			textcolor(7);
			putchar(219);
		}	
		putchar(219);
	}
	putchar(219);
	textcolor(0); printf("%c", 219);
	
	// Linha 4
	
	gotoxy(ic, (il+3));
	
	textcolor(0); printf(" %c", 219);
	
	textcolor(2);
	for(int i = 0; i < 39; i++) putchar(219);
	
	textcolor(0); printf("%c ", 219);
	
	// Linha 5
	
	gotoxy(ic, (il+4));
	textcolor(0); printf("%c", 219);
	
	for(int i = 0; i < 41; i++) 
	{
		textcolor(2);
		if((i+1)%2==0)
		textcolor(14);
		putchar(219);
	}
	
	textcolor(0); printf("%c", 219);
	
}

void mobo(int ic, int il)
{
	// Construir o PCB bruto
	gotoxy(ic, il); 
	textcolor(0);	
	for(int i = 0; i < 20; i++) 
	{	
		for(int j = 0; j < 10; j++)
		{
		gotoxy((ic+i), (il+j));
		putchar(219);
		}
	}
	
	//Construir os detalhes
	textcolor(7);
	gotoxy(ic, (il+1)); printf("%c%c",219,219);
	gotoxy(ic, (il+2)); printf("%c%c",219,219);
	gotoxy(ic, (il+3)); printf("%c%c",219,219);		//IO traseiro
	gotoxy(ic, (il+4)); printf("%c%c",219,219);
	gotoxy(ic, (il+5)); printf("%c%c",219,219);
	
	textcolor(7);
	gotoxy((ic+6), (il+2)); printf("%c",219);
	gotoxy((ic+6), (il+3)); printf("%c",219);
	gotoxy((ic+9), (il+2)); printf("%c",219);		//socket do cpu
	gotoxy((ic+9), (il+3)); printf("%c",219);
	textcolor(14);
	gotoxy((ic+7), (il+2)); printf("%c%c",219,219);
	gotoxy((ic+7), (il+3)); printf("%c%c",219,219);
	
	textcolor(2);
	gotoxy((ic+13), (il+1)); printf("%c",219);
	gotoxy((ic+13), (il+2)); printf("%c",219);
	gotoxy((ic+13), (il+3)); printf("%c",219);    //slots de ram e etc
	gotoxy((ic+13), (il+4)); printf("%c",219);
	gotoxy((ic+15), (il+1)); printf("%c",219);
	gotoxy((ic+15), (il+2)); printf("%c",219);
	gotoxy((ic+15), (il+3)); printf("%c",219);
	gotoxy((ic+15), (il+4)); printf("%c",219);	
	gotoxy((ic+18), (il+1)); printf("%c%c",219,219);
	
	textcolor(8);
	gotoxy((ic+18), (il+3)); printf("%c%c",219,219);    //conectores 24 pinos e etc
	gotoxy((ic+18), (il+4)); printf("%c%c",219,219);
	
	gotoxy((ic+4), (il+6)); printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);  //slots pci-e
	gotoxy((ic+4), (il+8)); printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
	
	textcolor(RED);
	gotoxy((ic+15), (il+6)); printf("%c%c",219,219); //dissipador do chipset
	gotoxy((ic+15), (il+7)); printf("%c%c",219,219);
	
	textcolor(15);
	gotoxy((ic+14), (il+9)); printf("%c%c%c%c",219,219,219,219);
	textcolor(0);
	
	gotoxy((ic+10), (il+10));	// tirar o exit do programa de perto
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

void clreol(int x)  //função customizada e mais versátil para o programa do clreol da conio.h
{
   for(int i=0; i < x; i++)
           printf(" ");         //preenche com "vazio/em branco" X espaços escolhidos
       for(int i=0; i < x; i++)
           printf("\b");		//volta X vezes o cursor para trás para a posição original após limpar a linha
}

