/* 
	Trabalho de FPD 4 Bimestre 2020					
	
	Felipe Lima Estevanatto 06
	Gabriel Gomes Nicolim 08
	
			71/81A
			
		CTI - Bauru - 2020
		
	- Este projeto visa aplicar os conceitos aprendidos em FPD e TP ao longo de 2020.
	
*/

#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <strings.h>

// Versão 2.4
#define versao 2.4

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

// Apresenta o menu e a versão
void loading();
// Apresenta tela de inicio
void inicio(); 
// Função utilizada para a borda
void borda(); 

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
// Realiza a consulta por tipo do produto
void consulta_tipo_recebimento();
void consulta_tipo(char aux);
// Fonção que realiza a busca por nome
void consulta_nome();
// Função para apagar dados do .bin por id
void excluir_dados();
// Função para gerar uma tabela
void gera_tabela(int li);  //
//Função para colocar os dados na tabela
void completa_tabela(int linha);
void completa_tabela_vertical(int coluna); 
// Função para gerar tabela de tipo 
void tabela_tipos();
// Função utilizada para navegar com setasem menus
int navegar_menu(int ini, int fim, int p); // Recebe inicio e fim do menu e a posição do cursor

// Menu 

// Fução de construção do menu da tela inicial
void menu_ini();

// Função para gerar a parte visual do cadastro 
void cadastro_visual();
// Recebe os dados de registro
void cadastro_recebimento();

/* Funções do submenu */
void consulta_id(); // Encontra o produto pelo id

// Função para gerar o sub menu de pesquisa
void sub_menu();

// Função para apresentar as Informações do Sistema
void info_de_sistema();

// Função que finaliza a execução do programa no menu
void sair();

// Funções de checagem

// Função para validar código consultado
int valida_id_consulta(int *id_final);

// Funções de validação => Validações + Registro

// Valida id no registro
void valida_id_recebimento();
// Valida quantidade no registro
void valida_quantidade_recebimento();
// Valida nome no registro
void valida_nome_recebimento();
// Valida tipo digitado
void valida_tipo_recebimento();
// Valida preço digitado
void valida_preco_recebimento();

FILE *fp; //Ponteiro para arquivo

int random_menu; // Var que armazena numero aleatório ente 0 e 4 para gerar um menu diferente 

void abrir_arquivo()
{
	if((fp = fopen("estoque.bin", "ab+")) == NULL) 
	{
		gotoxy(15, 11);printf("Erro na abertura do arquivo"); //caso haja um problema com o arquivo
		exit(1);
	}
}

int abrir_arquivo_alterar()
{
	if((fp = fopen("estoque.bin", "rb+")) == NULL) 
	{
		cursor(0); 
		gotoxy(40, 16);printf("N%co foram encontrados dados, cadastre algo!", 198);
		getch();
		return 1;
	}
	else return 0;
}

struct estrutura
{
	long id;
	char nome[50];
	int quantidade;
	char tipo;
	float preco_unitario;
	bool excluido;
	
}produto;


main()
{
	SetConsoleTitle("GoTech"); 		   // Define o nome do console
    system("mode con:cols=120 lines=40");  // Define o tamanho do console
    
	srand(time(NULL));
	random_menu = rand() % 4; // Escolhe o menu que será exibido ao usuário
	
    loading();
	inicio(); // Função de construção da tela inicial
}

void loading()
{
	borda(); 
	cursor(0);
	
	// Apresentação de versão 
	
	textcolor(cor_texto);
	gotoxy(38, 10); printf("Aguarde, estamos preparando tudo para voc%c!",136);
	gotoxy(15, 30); printf("Copyright%c GoTech",184);
	gotoxy(99, 30); printf("Vers%co %.1f",198, versao);
	
	textcolor(RED); // Loading vermelho
	for(int i = 0; i <= 52; i++)
	{
		gotoxy(32+i, 20);printf("%c", 219);
//		Sleep(50);
	}
	textcolor(cor_texto);
	gotoxy(38, 10); printf("       Tudo pronto! Podemos iniciar...                            ");
	Sleep(2500);
}

//
// Primeira página que o usuário tem contato 
//

void inicio() // Apresenta tela de inicio
{	
	while(true)
	{
		borda(); 
	
		switch(random_menu) // Menu aleatorio
		{
			case 0:
				disquete(18, 6); // Disquete + logo
				logo(48, 8);
				break;
			case 1:				// cpu + logo
				cpu(18, 6); 	
				logo(48, 8);
				break;	
			case 2:				// logo
				logo(32, 8); 	
				break;
			case 3:				// Ram + logo
				ram(37, 4); 	
				logo(32, 10);
				break;
			case 4:				// Ram + logo
				mobo(83, 6); 		
				logo(20, 8);
				break;		
		}
		
		menu_ini();
	}
}

void menu_ini()
{	
	// Menu 
	
	textcolor(cor_texto);
	
	gotoxy(50, 19); printf("Cadastro");
	gotoxy(50, 21); printf("Pesquisa");
	gotoxy(50, 23); printf("Info do Sistema");
	gotoxy(50, 25); printf("Sair");
	
	// Chama navegação com setas
	
	int escolha;
	escolha = navegar_menu(19, 25, 48);
	
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
	
	return; 
}

//
// Escolhas possiveis no primeiro menu 
//

void cadastro_visual()
{
	char dnv = 'n';
	
	abrir_arquivo();
	
	cursor(1);
	
	do{
		
		borda();
		tabela_tipos();
		
		textcolor(cor_destaque);
	
		gotoxy(20, 31); printf("Digite 0 no campo de ID para retornar ao menu");
		gotoxy(50, 4); printf("Cadastro de Produtos"); // Mensagem em destaque no meio da tela
		
		gotoxy(20, 8); 	printf("Id do produto....: ");				
		gotoxy(20, 10); printf("Nome do Produto..: ");		
		gotoxy(20, 12); printf("Quantidade.......: ");			
		gotoxy(20, 14); printf("Tipo.............: ");					
		gotoxy(20, 16); printf("Preco Unit%crio...: ",160);		
			
		cadastro_recebimento(); // Recebe as respostas do usuário
		
		textcolor(cor_destaque);
		gotoxy(20, 28); printf("Deseja realizar mais um cadastro? (S/N): ");
	
		do{
			fflush(stdin);
			
			dnv = getche();
			
			if(dnv != 'n' && dnv != 'N' && dnv != 's' && dnv != 'S')
			{
				Sleep(80);
				gotoxy(20, 28); clreol(70); printf("Valor inv%clido! digite novamente (S/N): ", 160);
				Sleep(20); gotoxy(60, 28); clreol(1);
			}
				
		}while(dnv != 'n' && dnv != 'N' && dnv != 's' && dnv != 'S');
		
		system("cls");
		
	}while(dnv == 's' || dnv == 'S');
	
	fclose(fp);
	
	return; 
}

void cadastro_recebimento()
{
	textcolor(cor_texto);
	
	fflush( fp ); 
	
	gotoxy(39, 8);  valida_id_recebimento();		 // Recebe id
	gotoxy(39, 10); valida_nome_recebimento();		 // Recebe nome
	gotoxy(39, 12); valida_quantidade_recebimento(); // Recebe quantidade
	gotoxy(39, 14); valida_tipo_recebimento();		 // Recebe tipo
	gotoxy(39, 16); valida_preco_recebimento();	 	 // Recebe preco
	produto.excluido = false;						 // Define excluido
	
	char conf; // variavel de confirmação do loop seguinte
	
	textcolor(cor_destaque);
	gotoxy(20, 22); printf("Deseja salvar os dados? (S/N): ");
	
	do{
		
		fflush(stdin); //limpa buffer teclado
		
		conf = getche();
		
		if(conf != 's' && conf != 'S'	&& conf != 'n' && conf != 'N')    //verificação de valores
		{			
			Sleep(100);
			gotoxy(20, 22); printf("Valor inv%clido! digite novamente (S/N): ",160);
			Sleep(50); gotoxy(60, 22); clreol(1);
		}
		
   	}while( conf != 's' && conf != 'S'	&& conf != 'n' && conf != 'N' );
   	
   	if( conf == 's' || conf == 'S' )
   	{
		if(fwrite(&produto, sizeof(produto), 1, fp) != 1) 
		{
			textcolor(RED);
			gotoxy(79, 22); printf("Erro na escrita do arquivo!");
			textcolor(cor_texto);
		}
		else  //se tudo der certo
		{
			fflush( fp ); //limpa buffer arquivo 
			
			borda();
			
			textcolor(cor_destaque);
			gotoxy(18,11); printf("Dados salvos com sucesso!");
		}
		
		cursor(0); 
		Sleep(1500);
		cursor(1);
		
		return; 
	}
}

// 
// Parte do recebimento de dados 
// 

void valida_id_recebimento()  // Recebe e valida id
{
	char id[30];
	int tam;		// Armazena tamanho da string
	int k,c;   	   // Auxiliares
	int aux;		//int auxiliar que armazenará a id digitada
	
	bool valido;
	
	do
	{	
		k = 1;  //loop principal
		c = 0;  //se não for número

		rewind(fp);
		
		fflush(stdin);
		
		gets(id);
		
		tam = strlen(id); // pega tamanho da string e joga em uma int tamanho
		
		if(tam == 0) // Se nada foi digitado 	
		{
			gotoxy(39,8);	// Retorna a posição de inicio e pergunta novamente
			k = 0;
		} 
		else if(id[0] == '0')	// Se o primeiro digito de id for igual a 0 
		{
			cursor(0);
			textbackground(12);
			gotoxy(52, 35);			 // Apresenta mensagem a baixo da borda
			printf("Voltando ao menu...");
			Sleep(1500);
			inicio();
		} 
		else 
		{
			if(tam > 6) c = 1; // Define como invalido se id > 6 
			else 
			{
				for(int i = 0; i < tam; i++) // verifica caractere por caractere se é número
				{
					if(id[i] != '0' && id[i] != '1' && id[i] != '2' && id[i] != '3' && id[i] != '4' && id[i] != '5' && id[i] != '6' && id[i] != '7' && id[i] != '8' && id[i] != '9') 
					{
						c = 1; //marca id como invalido para cair no if mais embaixo
						break;
					}
				} 	
			}
			
			if(c == 1)  // Erro se não for numerico ou for muito grande
			{
				k = 0; //continua no loop 
				
				textbackground(cor_fundo);
				gotoxy(38, 8); clreol(72);
				textbackground(12);
				gotoxy(39, 8); printf("[ERRO] ID inv%clido",160);
				Sleep(1500);
				textbackground(cor_fundo);
				gotoxy(39, 8); clreol(72);
				gotoxy(39,8);				
			}
			else
			{
				valido = true;
				
				//aux é int e id é char
				aux = atoi(id); // converte a string para int (tambem poderia ser aux = strtol (id,NULL,10); )
			
				//enquanto não chegar o final do arquivo E (produto.id for diferente de auxiliar OU (produto.id for igual auxiliar E for excluido) )
				while(fread(&produto, sizeof(produto), 1, fp) == 1)							
				{	
					if(produto.id == aux and !produto.excluido)
					{
						valido = false;
						break;
					}
				}	
				
				if(!valido)
				{
					textbackground(cor_fundo);
					gotoxy(38, 8); clreol(70);
					textbackground(12);
					gotoxy(39, 8); printf("[ERRO] ID j%c cadastrado", 131);
					Sleep(1500);
					textbackground(cor_fundo);
					gotoxy(38, 8); clreol(70);
					gotoxy(39, 8);
					k = 0; 	//continua no loop
				}
				else break;	
			}
		}	
		
	}while(k == 0);
	
	produto.id = aux;   // converte a string para int e manda para a struct
					
	return; 
}

void valida_nome_recebimento() // Recebe e valida nome
{
	char aux[50], aux_final[50]; // Armazena nome | Armazena nome sem espaço 
	
	int k, j; 		 // Var auxiliar 
	int tam;	// Armazena tamanho da string

	while(true)
	{
		k = 0;
		j = 0;
		
		fflush(stdin);
		gets(aux);
		
		tam = strlen(aux);
		
		if(tam == 0) gotoxy(39, 10); // Se nada for digitado
		else break;
	}
	
	gotoxy(39, 10); clreol(70);
	gotoxy(39, 10); printf("%s", aux);
	
	strcpy(produto.nome, aux);
	
	return; 
}

void valida_quantidade_recebimento() // Recebe e valida quantidade
{
	char aux[50];
	
	int tam;
	int k, c; // Auxiliares
	
	do
	{
		fflush(stdin);
		
		k = 1;
		c = 0;
		
		gets(aux);
		tam = strlen(aux); // Tamanho da string
		
		if(tam == 0)	// Se nada for digitado pergunta novamente
		{
			gotoxy(39, 12);
			k = 0;
		} 
		else 
		{
			for(int i = 0; i < tam; i++) 
			{
				if(aux[i] != '0' && aux[i] != '1' && aux[i] != '2' && aux[i] != '3' && aux[i] != '4' && aux[i] != '5' && aux[i] != '6' && aux[i] != '7' && aux[i] != '8' && aux[i] != '9') 
				{ // Se não é numérico 
					c = 1;	// Apresenta erro
					break;
				}
				else // Se é numérico
				{
					k = 1;
					c = 0;
				} 
			}	
			
			if(c == 1) // Erro
			{
				k = 0;	// Repete a pergunta
				
				textbackground(cor_fundo);
				gotoxy(39, 12); clreol(72);
				textbackground(12);
				gotoxy(39, 12); printf("[ERRO] Quantidade inv%clida",160);
				Sleep(1000); // tempo de erro na tela
				textbackground(cor_fundo);
				gotoxy(39, 12); clreol(72);
				gotoxy(39, 12);
			}
		}
	}while(k == 0);
	
	produto.quantidade = atoi(aux); // Retorna quantidade inteira 
	
	return; 
}

void valida_tipo_recebimento() // Recebe e valida tipo 
{
 	char aux;
 	
 	do
 	{
 		
 		fflush(stdin);
 	
 		aux = getche();
		
		aux = toupper(aux);
		
		// Verifica se é um dos tipos listados
		if(aux == 'P' || aux == 'G' || aux == 'C' || aux == 'M' || aux == 'F' || aux == 'W' || aux == 'A' || aux == 'R' || aux == 'O') break;
		else // Apresenta erro
		{
			textbackground(cor_fundo);
			gotoxy(39, 14); clreol(72);
			textbackground(12);
			gotoxy(39, 14); printf("[ERRO] Tipo inv%clido",160);			
			Sleep(1000); // tempo de erro na tela
			textbackground(cor_fundo);
			gotoxy(39, 14); clreol(72);
			gotoxy(39, 14);
		}
		
	}while(true);
	
	produto.tipo = aux;
	
	return; 
}

void valida_preco_recebimento() // Recebe preço e valida
{
	char aux[30];
	int tam;
	char* end; // Ponteiro de conversão 
	float num;
	int k;
	
	do
	{	
		fflush(stdin);
		
		gets(aux);
		
		tam = strlen(aux); // Recebe tamanho da string
		
		k = 0;
		
		if(tam == 0) gotoxy(39, 16); // Se nada for digitado
		else
		{
			for(int i = 0; i < tam; i++)
			{
				if((aux[i] < '0' || aux[i] > '9') && aux[i] != '.') // Verifica se é numérico
				{ 
					// Erro
					
					k = 1;
						
					textbackground(cor_fundo);
					gotoxy(39, 16); clreol(72);
					textbackground(12);
					gotoxy(39, 16); printf("[ERRO] Valor invalido");			
					Sleep(1000); // Tempo de erro
					textbackground(cor_fundo);
					gotoxy(39, 16); clreol(72);
					gotoxy(39, 16);	
					
					break;
				}
			}			
			
			if(k == 0) // Se valor for numérico
			{
				num = strtod(aux, &end); // Converte para float
				
				if(num > -1) break; // Se valor positivo
				else // Se valor negativo 
				{
					// Erro
					textbackground(cor_fundo);
					gotoxy(39, 16); clreol(72);
					textbackground(12);
					gotoxy(39, 16); printf("[ERRO] Valor inv%clido",160);			
					Sleep(1000);
					textbackground(cor_fundo);
					gotoxy(39, 16); clreol(72);
					gotoxy(39, 16);	
				}
			}
		}
	}while(true);
	
	produto.preco_unitario = num; 
	
	return; 
}

// Revisão primária => 28/10/2020 

/* 
	- Funções de recebimento e validação alteradas
	- Tempo das mensagens de erro reduzido
	- Erros lógicos resolvidos
*/

void sub_menu() // Gera a parte visual e realiza a escolha da opção do submenu 
{
	while(true)
	{
		borda();
		
		lupa(43, 4);
		
		// Menu 
		
		textcolor(cor_texto);
		gotoxy(45, 19);  printf("Geral");
		gotoxy(45, 21);  printf("Busca por ID");
		gotoxy(45, 23);  printf("Busca por Tipo");
		gotoxy(45, 25);  printf("Busca por Nome"); 
		gotoxy(45, 27);  printf("Excluir dados");
		gotoxy(45, 29);  printf("Retornar ao In%ccio", 161);
		
		int escolha;
		escolha = navegar_menu(19, 29, 43);
		
		switch(escolha)
		{
			case 0:
				consulta_geral();
				break;
			case 1:
				consulta_id();
				break;
			case 2:
				consulta_tipo_recebimento();
				break;
			case 3:
				consulta_nome(); 
				break;
			case 4:
				excluir_dados();
				break;
			case 5: 
				return; // Retorna ao menu inicial 
		} 
	}
}

void info_de_sistema() // Apresenta as informações do sistema
{
	borda();
	
	int inix = 20, iniy = 9; // Controla o eixo x e y das informações
	
	// Apresenta as informações do sistema
	textcolor(cor_destaque);
	gotoxy(54, 4);  printf("Info do Sistema");
	textbackground(cor_fundo);
	
	textcolor(cor_destaque);
	gotoxy(20, 7); printf("Empresa: ");
	textcolor(cor_texto);
	printf("GoTech");
	
	textcolor(cor_destaque);
	gotoxy(20, 9);  printf("Nomes: ");
	textcolor(cor_texto);
	printf("Gabriel Nicolim e Felipe Lima");
	
	textcolor(cor_destaque);
	gotoxy(20, 11);  printf("N%cmeros: ",163);
	textcolor(cor_texto);
	printf("08 e 06");
	
	textcolor(cor_destaque);
	gotoxy(20, 13);  printf("Turmas: ");
	textcolor(cor_texto);
	printf("71A");
	
	textcolor(cor_destaque);
	gotoxy(20, 15);  printf("Ano: ");
	textcolor(cor_texto);
	printf("2020");
	
	textcolor(cor_destaque);
	gotoxy(20, 17);  printf("Sobre o software: ");
	textcolor(cor_texto);
	printf("Nosso software, que hoje se encontra na vers%co %.1f, se destina a",198, versao);
	gotoxy(20, 19); printf("simular um sistema de gerenciamento de estoque de uma loja de inform%ctica em C/C++.",160);
	gotoxy(20, 21); printf("Para a realiza%c%co desse projeto utilizamos fun%c%ces de cabe%calho da conio.c e conio.h.",135,198,135,228,135);
	gotoxy(20, 23); printf("Podem ser registrados perif%cricos e outras pe%cas de computador.",130,135);
	
	textcolor(cor_destaque);
	gotoxy(20, 25); printf("Agradecimentos: ");
	textcolor(cor_texto);
	printf("Deixamos nosso agradecimento a professora Ariane Scarelli e ");
	gotoxy(20, 27); printf("K%ctia Zambombon, por compartilharem conosco parte de seus conhecimentos.",160);
	
	textcolor(cor_destaque);
	gotoxy(20, 30); printf("Pressione 0 para retornar ao menu"); 
	
	char c;
	
	do
	{
		fflush(stdin); 
		
		c =	getch();
			
	}while(c != '0');
	
	return; 
}

void sair() // Finaliza a execução do programa
{
	borda();
	
	textcolor(cor_texto);
	
	gotoxy(42, 17); printf("Obrigado por utilizar nosso programa!");
	
	fclose(fp);
	
	textcolor(cor_fundo); gotoxy(80, 37); // Esconde mensagem de encerramento 
	
	exit(1);
}

//
// Sub menu 
//

void consulta_geral()
{
	int cont_tuplas = 0; // Contador de registros 
	char retornar = '0';
	
	abrir_arquivo();
	
	cursor(0); // Desliga o cursor
	
	bool vazio = true;  // Verifica se o arquivo bin está vazio 
	
	while(fread(&produto, sizeof(produto), 1, fp) == 1)
	{
		if(!produto.excluido)
		{
			vazio = false;
			cont_tuplas++;
		}
	}
	
	if(!vazio)
	{
		int contl = 1, limite, limiteAnte, pag, linha, pag_limite; // Variaveis Auxiliares
		
		pag = 1;
		
		pag_limite = ceil(cont_tuplas / 12);  
		
		gera_tabela(5);	// Gera borda e tabela inicial
		
		do
		{			
			limite = (12 * pag); // 12 linhas de dados por página (oq cabe na tabela)
			limiteAnte = (12 * (pag - 1));  // Limite da página anterior 
			
			textcolor(cor_texto);
			
			gotoxy(20, 31); printf("Pressione 0 para voltar ao menu de pesquisa");
			gotoxy(107, 4);	printf("%d", pag); // Número da página 
			
			contl= 1;    //reseta o contador de linha
			linha= 7;	//reseta a linha inicial(pmr da tabela) em q os dados começarão a ser colocados
			
			rewind(fp);
			
			while(fread(&produto, sizeof(produto), 1, fp) == 1) // segue até o fim do arquivo
			{			
				if(contl > limiteAnte) //se a linha atual for maior que o limite inferior:
				{
					if(!produto.excluido) // Só apresenta e vai para a próxima posição se o item não tiver sido excluido 
					{
						completa_tabela(linha);    //preenche a tabela
						linha += 2; 
					}
				}
				
				if(contl == limite) break; //se a linha atual for igual ao limite quebra
				else contl++; //adiciona mais uma linha ao contador
			}
			
			gotoxy(20,34); 
			
			fflush(stdin);
			
			retornar = getch();
			
			switch(retornar)
			{
				case char(77): // Se a seta direita for pressionada
					if(pag <= pag_limite) 
					{
						pag++; // Avança a página | Limita pag a 10 
						rewind(fp);		//seta a leitura do arquivo na posição inicial do arquivo ("1º linha e coluna")	
						gera_tabela(5);
					}	
					break;
					
				case char(75): // Se a seta da esquerda
					if(pag > 1) 				
					{
						pag--; // Volta a pagina
						rewind(fp);	
						gera_tabela(5);	
					} 			
					break;
			}
			
		}while (retornar != '0');  
			
		// Se 0 for pressionado 
		
		textbackground(12);
		gotoxy(52, 35);			 // Apresenta mensagem a baixo da borda
		printf("Voltando ao Menu...");
		Sleep(1500);
		textbackground(cor_fundo);
		
		fclose(fp);	// fecha o arquivo
		return;    // Retorna ao submenu
	}
	else
	{
		borda();
		textcolor(cor_destaque); 
		gotoxy(32, 16); printf("[ N%co h%c nenhum item registrado! Por favor registre algo ]", 198,160);
		getche();
		fclose(fp);	// fecha o arquivo
		return; 
	}			
}

// Revisão Final para entrega => 05/11/2020 

/* 
	- Funções foram alteradas a fim de retirar a "recursividade" (ERRO GRAVE)
	- Erros lógicos resolvidos
	- Foram retiradas linhas sem sentido 
*/

void consulta_id()   //consulta por id
{	
	
	int k;
	int aux;
	int id_busca; // Armazena id digitado pelo usuário durante a busca 
		
	abrir_arquivo();
	
	textcolor(cor_texto);
	
	do
	{
		// Construção visual
		borda();
		
		k = 0;
		aux = 0; 
			
		textcolor(cor_destaque);
		gotoxy(54, 4); printf("Consulta por ID");
		gotoxy(20, 7); printf("Digite o Id (0 para sair): ");
		textcolor(cor_texto);
		
		aux = valida_id_consulta(&id_busca);
		
		if(aux == 0) break;
		else if(aux == 1) // Retorna ao sub menu por conta de um erro no id digitado pelo usuario
		{
			gotoxy(47, 7); 		clreol(50);
			textbackground(12); 
			textcolor(cor_texto);
			printf("Id inv%clido",160);
			Sleep(1000);
			textbackground(cor_fundo);
			gotoxy(47, 7); clreol(50);	
		} 
		else if(aux == 3)  //retorno de 3 significa que o id é válido
		{
			rewind(fp);	
			
			while( !feof(fp) )  //enquanto no for o fim de um arquivo...
			{
				if(fread(&produto, sizeof(produto), 1, fp) == 1 && !produto.excluido && produto.id == id_busca)
				{					
		
					gotoxy(20,11);	printf ("+--------------------------------------------------------------------------------+");
					gotoxy(20,12);	printf ("|  ID                |                                                           |");
			   		gotoxy(20,13);	printf ("|--------------------|-----------------------------------------------------------|");
					gotoxy(20,14);	printf ("|  Nome              |                                                           |");
					gotoxy(20,15);	printf ("|--------------------|-----------------------------------------------------------|");
					gotoxy(20,16);	printf ("|  Pre%co Unit%crio    |                                                           |", 135, 160);
					gotoxy(20,17);	printf ("|--------------------|-----------------------------------------------------------|");
					gotoxy(20,18);	printf ("|  Quantidade        |                                                           |");
					gotoxy(20,19);	printf ("|--------------------|-----------------------------------------------------------|");
					gotoxy(20,20);	printf ("|  Tipo              |                                                           |");
					gotoxy(20,21);	printf ("+--------------------------------------------------------------------------------+");

					completa_tabela_vertical(43); //Apresenta-se ao usuário o registro pesquisado
					
					tabela_tipos();
					
					textcolor(cor_destaque);
					gotoxy(20,30);printf("Pressione uma tecla para continuar...");
					
					fflush(stdin);
					getch();
					
					k = 1; //para não apresentar erro de código inexistente
					
					break;	//sai do loop pra n ter q fazer verificação extra (preguiça)
				}				
			}
			if(k == 0)
			{
				textcolor(cor_destaque); 
				gotoxy(50, 18);printf("[ C%cdigo inexistente ]",162);
				gotoxy(20, 30);printf("Pressione uma tecla para redigitar...");
				
				getch();
				
			}
		}
		
	}while(true);
	
	fclose(fp); //fecha arquivo
	
	return;
}

int valida_id_consulta(int *id_final)
{
	char id[30];
	int tam;
	int k;
	
	do
	{
		k = 1;
		cursor(1);
		gets(id);
		tam = strlen(id);
		
		if(tam == 0)  //se não for digitado nada (apenas enter) volta a posição inicial
		{
			gotoxy(47,7);
			k = 0;
		} 
		else if(id[0] == '0')   //se for digitado 0 como o primeiro número retorna ao submenu
		{
			cursor(0);
			textbackground(12);
			gotoxy(52, 35);			 // Apresenta mensagem a baixo da borda
			printf("Voltando ao menu...");
			Sleep(1500);
			return 0;
		}
		else 
			for(int i = 0; i < tam; i++) 
				if(id[i] != '0' && id[i] != '1' && id[i] != '2' && id[i] != '3' && id[i] != '4' && id[i] != '5' && id[i] != '6' && id[i] != '7' && id[i] != '8' && id[i] != '9') 
					return 1;			
	}while(k != 1);
	
	cursor(0);
	
	*id_final = atoi(id); //manda por referencia o id em forma de int
	
	return 3;
}	

void consulta_tipo_recebimento()
{
	char aux;
	
	do{
		borda();
		
		textcolor(cor_texto); 
		
		textcolor(cor_destaque);
    
    	gotoxy(36, 18);    printf(" P - Perif%crico       G - Gpu      C - Cpu", 130);
    	gotoxy(36, 20);    printf(" M - Mobo             F - Fonte    W - Cabos");
    	gotoxy(36, 22);    printf(" A - Armazenamento    R - Ram      O - Outros");
		
		textcolor(cor_destaque);
		gotoxy(52, 4); printf("Consulta por Tipo", 198);
		
		gotoxy(20,7); printf("Digite tipo a ser pesquisado (0 para sair): ");
		
		textcolor(cor_texto);
		
		do
	 	{
	 		
	 		fflush(stdin);
	 	
	 		aux = getche();
			
			aux = toupper(aux);  //passa o auxiliar para maiusculo
			
			// Verifica se é um dos tipos listados
		
			if(aux != 'P' && aux != 'G' && aux != 'C' && aux != 'M' && aux != 'F' && aux != 'W' && aux != 'A' && aux != 'R' && aux != 'O' && aux != '0' )
			{
				textbackground(cor_fundo); // Apresenta erro
				textbackground(12);
				gotoxy(64, 7); printf("[ERRO] Tipo inv%clido",160);			
				Sleep(1000); // tempo de erro na tela
				textbackground(cor_fundo);
				gotoxy(64, 7); clreol(30);
				//gotoxy(39, 14);
			}
			
		}while(aux != 'P' && aux != 'G' && aux != 'C' && aux != 'M' && aux != 'F' && aux != 'W' && aux != 'A' && aux != 'R' && aux != 'O' && aux != '0' );
		
		if(aux != '0')
		{
			Sleep(500);
			consulta_tipo(aux);
		}
		
	}while(aux != '0');
	
	return;
}

void consulta_tipo(char aux)
{	
	int cont_tuplas = 0;
	
	abrir_arquivo();
	
	cursor(0); // Desliga o cursor
	
	gera_tabela(5);	// Gera borda e tabela inicial
	
	bool vazio;
	
	vazio = true;
	
	while(fread(&produto, sizeof(produto), 1, fp) == 1) // segue até o fim do arquivo
	{
		if(produto.tipo == aux && !produto.excluido) 
		{
			vazio = false;
			cont_tuplas++;
		}
	}
	
	if(!vazio)
	{
		int contl = 1, limite, limiteAnte, pag, linha, pag_limite; // Variaveis Auxiliares
		
		char retornar;
		
		pag = 1;
		
		pag_limite = ceil(cont_tuplas / 12);  
		
		gera_tabela(5);	// Gera borda e tabela inicial
		
		do
		{			
			limite = (12 * pag); // 12 linhas de dados por página (oq cabe na tabela)
			limiteAnte = (12 * (pag - 1));  // Limite da página anterior 
			
			textcolor(cor_texto);
			
			gotoxy(20, 31); printf("Pressione 0 para voltar ao menu de pesquisa");
			gotoxy(107, 4);	printf("%d", pag); // Número da página 
			gotoxy(107, 6); printf("%c", aux);
			
			contl= 1;    //reseta o contador de linha
			linha= 7;	//reseta a linha inicial(pmr da tabela) em q os dados começarão a ser colocados
			
			rewind(fp);
			
			while(fread(&produto, sizeof(produto), 1, fp) == 1) // segue até o fim do arquivo
			{			
				if(contl > limiteAnte) //se a linha atual for maior que o limite inferior:
				{
					if(produto.tipo == aux && !produto.excluido) // Só apresenta e vai para a próxima posição se o item não tiver sido excluido 
					{
						completa_tabela(linha);    //preenche a tabela
						linha += 2; 
					}
				}
				
				if(contl == limite) break; //se a linha atual for igual ao limite quebra
				else contl++; //adiciona mais uma linha ao contador
			}
			
			gotoxy(20,34); 
			
			fflush(stdin);
			
			retornar = getch();
			
			switch(retornar)
			{
				case char(77): // Se a seta direita for pressionada
					if(pag <= pag_limite) 
					{
						pag++; // Avança a página | Limita pag a 10 
						rewind(fp);		//seta a leitura do arquivo na posição inicial do arquivo ("1º linha e coluna")	
						gera_tabela(5);
					}	
					break;
					
				case char(75): // Se a seta da esquerda
					if(pag > 1) 				
					{
						pag--; // Volta a pagina
						rewind(fp);	
						gera_tabela(5);	
					} 			
					break;
			}
			
		}while (retornar != '0');  
			
		// Se 0 for pressionado 
		cursor(0);
		textbackground(12);
		gotoxy(54, 35);			 // Apresenta mensagem a baixo da borda
		printf("Voltando...");
		Sleep(1500);
		
		textbackground(cor_fundo);
	}		
	else
	{
		borda();
		textcolor(cor_destaque); 
		gotoxy(28, 16); printf("[ N%co h%c nenhum item desse tipo registrado! Por favor registre algo ]", 198,160);
		
		getche(); 
	}
	
	fclose(fp);	// fecha o arquivo
	
	return;
}

void consulta_nome()
{
	
	char aux[50], comp[50]; // Armazena nome  
	int tam, k, j;
	
	do{
	
		borda();
			
		cursor(1);
			
		textcolor(cor_destaque); 
		gotoxy(52, 4); printf("Consulta por Nome");
		gotoxy(20, 7); printf("Digite o Nome (0 para sair): ");
		textcolor(cor_texto);
		
		do{
			
			k = 0;
			j = 0;
			
			fflush(stdin);
			gets(aux);
			
			tam = strlen(aux);
			
			if(tam == 0) gotoxy(49, 7); // Se nada for digitado
			
		}while(tam == 0);
		
		if(aux[0] == '0')
			return;
		
		cursor(0);
		
		abrir_arquivo();
				
		k = 1;
		
		rewind(fp);
		
		while(fread(&produto, sizeof(produto), 1, fp) == 1) // segue até o fim do arquivo
		{			
			strcpy(comp, produto.nome);
				
			if(strstr(strlwr(comp),strlwr(aux)) != NULL && !produto.excluido)	// Só apresenta e vai para a próxima posição se o item não tiver sido excluido
			{
				gotoxy(20,11);	printf ("+--------------------------------------------------------------------------------+");
				gotoxy(20,12);	printf ("|  ID                |                                                           |");
		   		gotoxy(20,13);	printf ("|--------------------------------------------------------------------------------|");
				gotoxy(20,14);	printf ("|  Nome              |                                                           |");
				gotoxy(20,15);	printf ("|--------------------------------------------------------------------------------|");
				gotoxy(20,16);	printf ("|  Pre%co Unit%crio    |                                                           |", 135, 160);
				gotoxy(20,17);	printf ("|--------------------------------------------------------------------------------|");
				gotoxy(20,18);	printf ("|  Quantidade        |                                                           |");
				gotoxy(20,19);	printf ("|--------------------------------------------------------------------------------|");
				gotoxy(20,20);	printf ("|  Tipo              |                                                           |");
				gotoxy(20,21);	printf ("+--------------------------------------------------------------------------------+");
				
				completa_tabela_vertical(43);    //preenche a tabela
				
				tabela_tipos();
				
				k = 0;
				break;
			} 
			else k = 1;		
		}
		
		if(k == 1) 
		{
			textcolor(cor_destaque);
			gotoxy(48, 18); printf("[ Nome n%co encontrado ]", 198);			
		}
				
		textcolor(cor_destaque);
		gotoxy(20, 30); printf("Pressione uma tecla para redigitar...");	
			
			
		getch();
	
	}while(aux[0] != '0');
	
	return;
	
}

void excluir_dados() //exclusao lógica (continua no binário)
{
	cursor(1); // Liga o cursor
	
	int aux_codigo, F, k, tam; // Auxiliares
	long fposicao;
	char conf, id[50];

	do{
		
		borda();
		tabela_tipos(); //apresenta a info doq as letras significam
		
		if(abrir_arquivo_alterar() == 0) //abre o arquivo no modo de alteração de dados   
		{
			textcolor(cor_destaque);
			gotoxy(52, 4); printf("Exclus%co de dados", 198);
			gotoxy(20,7); printf("Digite o c%cdigo do produto a ser excluido (0 para sair): ",162);
			
			textcolor(cor_texto);
			      			
			k = 0;
			
			gets(id);
			
		    tam = strlen(id);
		    
		    if(tam == 0) gotoxy(77, 7); // Se nada for digitado
		    else if(id[0] == '0') // Se 0 for digitado
			{
				cursor(0);
				textbackground(12);
				gotoxy(52, 35);			 // Apresenta mensagem a baixo da borda
				printf("Voltando ao menu...");
				Sleep(1500);
			} 
		    else // Se algo diferente de 0 for digitado
		    {
		    	for(int i = 0; i < tam; i++)
				{
					if(id[i] != '0' && id[i] != '1' && id[i] != '2' && id[i] != '3' && id[i] != '4' && id[i] != '5' && id[i] != '6' && id[i] != '7' && id[i] != '8' && id[i] != '9') 
					{ // Confere se é numérico  
						k = 1; // Se não for numérico 
						break;	
					}	
				} 
		    	
		    	if(k == 1) // Se um caractere não numérico for digitado
		    	{
		    		textcolor(cor_texto);
		    		gotoxy(77, 7); clreol(34);
					textbackground(12);
		    		gotoxy(77, 7); printf("[ERRO] Id Inv%clido", 160);
					Sleep(1000);
					textbackground(cor_fundo); gotoxy(77, 7); clreol(34);
				}
		    	else // Se o ID for valido e numérico
		    	{ 
		    		aux_codigo = atoi(id); // Converte string em int 
		    		
			    	F = 0;
			    	
					rewind(fp);  //volta ao inicio do arquivo (para segunda repetição)
					
				    do
				    {
						fread(&produto, sizeof(produto), 1, fp);
						
						if (produto.id == aux_codigo && !produto.excluido) //Se houver um produto com o id e que não foi excluído
						{
					   		F = 1;  // F = 1 significa que o arquivo foi achado
					   		
					   		fposicao = ftell(fp); // guarda a posição do registro atual do arquivo
					   		
					   		textcolor(cor_texto);
					   		gotoxy(20,11);	printf ("+--------------------------------------------------------------------------------+");
							gotoxy(20,12);	printf ("|  ID                |                                                           |");
					   		gotoxy(20,13);	printf ("|--------------------------------------------------------------------------------|");
							gotoxy(20,14);	printf ("|  Nome              |                                                           |");
							gotoxy(20,15);	printf ("|--------------------------------------------------------------------------------|");
							gotoxy(20,16);	printf ("|  Pre%co Unit%crio    |                                                           |", 135, 160);
							gotoxy(20,17);	printf ("|--------------------------------------------------------------------------------|");
							gotoxy(20,18);	printf ("|  Quantidade        |                                                           |");
							gotoxy(20,19);	printf ("|--------------------------------------------------------------------------------|");
							gotoxy(20,20);	printf ("|  Tipo              |                                                           |");
							gotoxy(20,21);	printf ("+--------------------------------------------------------------------------------+");
							
							completa_tabela_vertical(43); //Apresenta-se ao usuário o registro a ser excluído
							
							textcolor(cor_destaque);
							gotoxy(20,30);printf("Pressione uma tecla para continuar...");
					
					   		textcolor(cor_destaque);
						   	gotoxy(20,24); printf("Confirma exclus%co ? (S/N): ", 198);
						   	
						   	// exclusão é uma operação crítica, por isso, sempre será confirmada pelo usuário
							do 
						   	{
						   		fflush(stdin);
						   		textcolor(cor_texto);
						    	gotoxy(47,24); conf = getche(); // Confirmação 
						    	
						    	if(conf != 's' && conf != 'S' && conf != 'n' && conf != 'N') 
						    	{
						    		gotoxy(47, 24); clreol(5);	
								}
								
						   	}while( conf != 's' && conf != 'S' && conf != 'n' && conf != 'N' );
						   
						   	if( conf == 's' || conf == 'S' )
						   	{
						   		//posiciona o ponteiro do arquivo no registro a ser excluido logicamente
								if(fseek (fp, fposicao-(sizeof(produto)), SEEK_SET) != 0) 	//SEEK_SET indica o início do arquivo, 
								{															//funciona igual o rewind(fp); porém pode ser usado em verificações pois retorna algo
									gotoxy(20, 11);	printf("Houve um erro catastrofico voltando ao inicio do arquivo!");
									Sleep(1500);
									return;
								}
																					
								produto.excluido= true; //atribuição de true para o campo excluído para indicar que o registro foi excluído ou desativado (exclusão lógica) 
								
								if(fwrite(&produto, sizeof(produto), 1, fp) == 1)
								{
									cursor(0);
									fflush (fp);
									textcolor(cor_destaque);
									gotoxy(20,26);printf("Cadastro exclu%cdo com sucesso!",161);
									
									getch();
									
									fflush(fp);			// limpeza de buffers 
									fclose(fp);			// fechamento do arquivo
						
								}	
						   	}
						   	else break; 
						}
					} while ((!F) && (!feof(fp)));  
					
					if (F==0 && aux_codigo!=0)  //código não encontrado
					{
						cursor(0);
						
						textcolor(cor_destaque);
						gotoxy(46, 18);printf("[ C%cdigo n%co encontrado ]",162,198);
						
						textcolor(cor_destaque);
						gotoxy(20,30);printf("Pressione uma tecla para retornar...");
					
						getch();
						
						fflush(fp);			// limpeza de buffers 
						fclose(fp);			// fechamento do arquivo
						
					}		
				}
			}
		}
		else break; // Sai do loop 
		
	}while( id[0] != '0');
	
	return;
}


void tabela_tipos()
{
    textcolor(cor_texto);
    
    gotoxy(38,37);    printf(" P - Perif%crico       G - Gpu      C - Cpu",130);
    gotoxy(38,38);    printf(" M - Mobo             F - Fonte    W - Cabos");
    gotoxy(38,39);    printf(" A - Armazenamento    R - Ram      O - Outros");
}

int navegar_menu(int ini, int fim, int p)
{
	cursor(0); // Desativa o cursor
	
	int aux = ini; // Recebe posição da seta
	int c; // Armazena entrada do teclado
	
	do
	{
		gotoxy(p,aux); printf("%c", 62);	
			
		fflush(stdin); 
		
		c = getch();
		
		gotoxy(p,aux); printf(" ");
		
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

void gera_tabela(int li)
{
	int ci = 20;

	borda();
	tabela_tipos(); //apresenta a info doq as letras significam
	
	textcolor(cor_texto);
	gotoxy(ci,4);	printf ("+---------------------------------------------------------------------------------+");
	gotoxy(ci,5);	printf ("|   ID   |             Nome              |  Pre%co Unit%crio  | Quantidade |  Tipo  |",135, 160);
	gotoxy(ci,6);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,7);	printf ("|        |                               |                  |            |        |");
	gotoxy(ci,8);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,9);	printf ("|        |                               |                  |            |        |");
	gotoxy(ci,10);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,11);	printf ("|        |                               |                  |            |        |");
	gotoxy(ci,12);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,13);	printf ("|        |                               |                  |            |        |");
	gotoxy(ci,14);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,15);	printf ("|        |                               |                  |            |        |");
	gotoxy(ci,16);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,17);	printf ("|        |                               |                  |            |        |");
	gotoxy(ci,18);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,19);	printf ("|        |                               |                  |            |        |");
	gotoxy(ci,20);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,21);	printf ("|        |                               |                  |            |        |");
	gotoxy(ci,22);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,23);	printf ("|        |                               |                  |            |        |");
	gotoxy(ci,24);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,25);	printf ("|        |                               |                  |            |        |");
	gotoxy(ci,26);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,27);	printf ("|        |                               |                  |            |        |");
	gotoxy(ci,28);	printf ("|---------------------------------------------------------------------------------|");
	gotoxy(ci,29);	printf ("|        |                               |                  |            |        |");
	gotoxy(ci,30);	printf ("+---------------------------------------------------------------------------------+");
	
}

void completa_tabela(int linha)  //função para colocar os dados na tabela
{ 
	if(!produto.excluido)
	{
		int tam = strlen(produto.nome);
		
		if(tam > 29) tam = 29; // define o tamanho máximo a ser apresentado (29 espaços na tabela)
		
		gotoxy(22,linha); printf("%d", produto.id);
		gotoxy(31,linha); for(int i = 0; i < tam; i++) printf("%c", produto.nome[i]); 		
		gotoxy(63,linha); printf("%.2f", produto.preco_unitario);
		gotoxy(82,linha); printf("%d", produto.quantidade);
		gotoxy(97,linha); printf("%c", produto.tipo);	
	}
}


void completa_tabela_vertical(int coluna)  //função para colocar os dados na tabela
{	
	if(!produto.excluido)
	{
		int tam = strlen(produto.nome); 
			
		gotoxy(coluna, 12); printf("%d", produto.id);
		gotoxy(coluna, 14); for(int i = 0; i < tam; i++) printf("%c", produto.nome[i]); 		
		gotoxy(coluna, 16); printf("%.2f", produto.preco_unitario);
		gotoxy(coluna, 18); printf("%d", produto.quantidade);
		gotoxy(coluna, 20); printf("%c", produto.tipo);	
	}
}

void borda() 
{
	int cf = cor_fundo, cb = cor_borda, lc = 120; // (cor de fundo, cor da borda, limite de coluna)
	
	textbackground(cf); // Define cor do fundo
	system("cls"); 		//limpa sempre a tela quando é chamada
	
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
	gotoxy(ic+18, il+5); printf("%c", 219);
	gotoxy(ic+18, il+6); printf("%c%c%c", 219, 219, 219);
	gotoxy(ic+16, il+7); printf("%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+18, il+8); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+21, il+9); printf("%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+24, il+10);printf("%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+26, il+10);printf("%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+26, il+11);printf("%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219, 219, 219);
	
	
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

/*

	Revisão Final - 5/11/2020
	
	- Linhas extras removidas
	- Espaçamentos adicionados
	- Comentários adicionados
	- Alteraçõs nas funções de exclusão e apresentação
	- Erros de "Recursividade" removidos
	- Pendências de memória corrigidos 
	
*/
