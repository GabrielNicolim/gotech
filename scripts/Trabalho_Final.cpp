/* 
	Trabalho de FPD 4 Bimestre 2020					
	
	Felipe Lima Estevanatto 06
	Gabriel Gomes Nicolim 08
	
			71/81A
			
		CTI - Bauru - 2020
		
	- Este projeto visa aplicar os conceitos aprendidos em FPD e TP ao longo de 2020.
	
	-Para rodar nas versões antigas do DEVC++ Orwell basta descomentar todas as linhas com uso do text_info(linha 35) e vActual(1959 e 1969)
	Versão 4.8 = Refatoração de código e correção de bugs
	Bug conhecidos: 
	- Graças a conio.h, terminais modernos quebram a posições da tela, quebrando toda a interface, porém o problema
	é apenas visual e pode ser corrigido ao maximizar a janela do terminal com ALT + ENTER ou F11 e mexendo no prompt de comando.
	- A pesquisa por nome não está funcionando corretamente
*/


#ifdef _WIN32
#include <conio.h>
#endif

#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <io.h> //para checagem se o arquivo existe
#include "functions\desenhos.h"

#define versao 4.8

//text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 160, 38, 1, 1}; // Define os limites para linha (38) e coluna (160)

// Funções conio.c

void textcolor(int newcolor);
void textbackground(int newcolor);
void gotoxy(int x, int y);
void cursor (int x);
void clreol(int x);

// Funções de construção do programa

void loading();
void inicio(); 
void borda(); 

// Desenhos presentes no arquivo desenhos.h (Todos com int ic, int il para escolher posição)
// - Disquete, Logo, Lupa, CPU, GPU, RAM, Mobo, HDD	

// Funções de interação com o usuário 
void consulta_geral();
void consulta_tipo();
void consulta_nome();
void excluir_dados();
void gera_tabela(int li);  
void gera_tabela_vertical(int li); 
void completa_tabela(int linha);
void tabela_tipos(int col, int linha, int L);
int navegar_menu(int ini, int fim, int p); // Recebe inicio e fim do menu e a posição do cursor
void cadastro_visual();
void cadastro_recebimento();
void consulta_id();

// Menu 

void menu_ini();
void alteracao(); 
void sub_menu();
void info_de_sistema();
void sair();

//==============================================
// Funções de validação => Validações + Registro
//================================================

bool isID_cadastrado(int aux);
long valida_id(int linha, int coluna, int qntapagar);
long valida_quantidade_recebimento(int linha, int coluna);
char *valida_nome_recebimento(int linha, int coluna);
char valida_tipo_recebimento(int linha, int coluna);
double valida_preco_recebimento(int linha, int coluna);

// Mensagem alteraveis e de confirmação
void erro_apagar (int col, int lin, int tipo_erro, int apagar);
void voltando_menu(int linha,int coluna, int delay, bool menu);
bool confirmarSN(int linha, int coluna,int confirmaTipo); 


// Variáveis globais

int obtem_id_alteracao();
int random_menu; // Var que armazena numero aleatório ente 0 e 3 para gerar um menu diferente 

FILE *fp; //Ponteiro para arquivo


void abrir_arquivo()
{
	if((fp = fopen("estoque.bin", "ab+")) == NULL){
		system("cls"); borda();
		textcolor(cor_texto);
		gotoxy(65, 16); printf("Erro na abertura do arquivo!"); //caso haja um problema com o arquivo
		gotoxy(1, 33);
		exit(1);
	}
}

int abrir_arquivo_alterar()
{
	if((fp = fopen("estoque.bin", "rb+")) == NULL){
		cursor(0); 
		gotoxy(40, 16); printf("N%co foram encontrados dados, cadastre algo!", 198);
		getch();
		return 1;
	}
	else return 0;
}

struct estrutura
{
	long id = 1;
	char nome[194];  // espaço da tela de cadastro
	long quantidade;
	char tipo;
	double preco_unitario;
	bool excluido;
	
} produto;

//======================================================================
//							Começo do programa
//======================================================================

main()
{
	SetConsoleTitle("GoTech"); 		   // Define o nome do console
    system("mode con:cols=160 lines=37");  // Define o tamanho do console
    
    //======================================================================
	//Pega o tamanho do monitor e joga o programa pro meio do monitor
	//======================================================================
    DWORD dwWidth = GetSystemMetrics(SM_CXSCREEN);  // pegam o tamanho da tela em pixels (ex: 1920 x 1080)
	DWORD dwHeight = GetSystemMetrics(SM_CYSCREEN);
    
    HWND wh = GetConsoleWindow(); // precisa disso pro MoveWindow  (HWND é como é indentificada a janela do Windows "identificador de janelas")
    MoveWindow(wh, dwWidth/8 , dwHeight/8 , 1300, 720, TRUE); // move a janela para uma cordenada determinada a setando num tamanho determinado de 20 em 20
    
    //======================================================================
    
	srand(time(NULL));
	random_menu = rand() % 4; // Escolhe o menu que será exibido ao usuário de maneira randomizada
	
    loading();
    
	inicio(); // Função de construção da tela inicial
}

void loading()
{
	borda(); 
	
	cursor(0);
	
	// Tela de loading com apresentação da versão do programa
	
	textcolor(cor_texto);
	
	gotoxy(58, 10); printf("Aguarde, estamos preparando tudo para voc%c!",136);
	gotoxy(15, 30); printf("Copyright%c GoTech",184);
	gotoxy(139, 30); printf("Vers%co %.1f",198, versao);
	
	textcolor(RED); // Loading vermelho
	
	for(int i = 0; i <= 52; i++){
		gotoxy(52+i, 20);printf("%c", 219);
		Sleep(10);
	}
	
	textcolor(cor_texto);
	gotoxy(58, 10); printf("     Tudo pronto! Podemos iniciar...                            ");
	Sleep(1500);
	while (kbhit())  //Isso continua se vê que há um input do teclado em espera e, em caso afirmativo, chama getch() para descartar o caractere
    getch();
}

//
// Primeira página que o usuário tem contato 
//

void inicio() // Apresenta tela de inicio
{	
	while(true){
		borda(); 
	
		switch(random_menu){ // Menu com icone aleatorio	
			case 0:
				disquete(38, 6); // Disquete + logo
				logo(68, 8);
				break;
			case 1:				// cpu + logo
				cpu(38, 6); 	
				logo(68, 8);
				break;	
			case 2:				// logo
				logo(52, 8); 	
				break;
			case 3:				// mobo + logo
				mobo(103, 6); 		
				logo(40, 8);
				break;		
		}
		
		menu_ini();
	}
}

void menu_ini()
{	 
	textcolor(cor_texto);
	
	gotoxy(70, 19); printf("Cadastro");
	gotoxy(70, 21); printf("Pesquisa");
	gotoxy(70, 23); printf("Altera%c%co", 135, 198); 
	gotoxy(70, 25); printf("Info de Sistema");
	gotoxy(70, 27); printf("Sair");
	gotoxy(150, 41); printf("Vers%co %.1f",198, versao);
	
	// Chama navegação com setas
	
	int escolha = navegar_menu(19, 27, 68);
	
	switch(escolha){
		case 0:
			cadastro_visual();
			break;
		case 1:
			sub_menu();
			break;
		case 2:
			alteracao(); 
			break; 
		case 3:
			info_de_sistema();
			break;
		case 4:
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
	abrir_arquivo();
	
	cursor(1);
	
	do{
		system("cls");
		
		borda();
		
		tabela_tipos(58, 37, 1);
		
		textcolor(cor_destaque); textbackground(15);
		gotoxy(69, 4);  printf(" Cadastro de Produtos "); // Mensagem em destaque no meio da tela
		textbackground(cor_fundo);
			
		gotoxy(20, 31); printf("Digite 0 no campo de ID para retornar ao menu");
		gotoxy(20, 8); 	printf("Id do produto....: ");				
		gotoxy(20, 10); printf("Nome do Produto..: ");		
		gotoxy(20, 12); printf("Quantidade.......: ");			
		gotoxy(20, 14); printf("Tipo.............: ");					
		gotoxy(20, 16); printf("Pre%co Unit%crio...: ", 135, 160);		
			
		cadastro_recebimento(); // Recebe as respostas do usuário
				
	}while( confirmarSN(20,26,3) );
	
	fclose(fp);
	
	return; 
}

void cadastro_recebimento()
{
	textcolor(cor_texto);
	
	fflush(fp); 
	cursor(1);
	
	int IDaux;	
	do {
		IDaux = valida_id(39, 8, 100); 						
		if(IDaux == 0){ 
			inicio();
			return;												
		}

		if(!isID_cadastrado(IDaux)) break;

		erro_apagar(39, 8, 1 , 70); //coluna, linha, tipo de erro: "[ERRO] ID já cadastrado" e quantidade a se apagar	
		IDaux = -1; 	//continua no loop

	} while(IDaux == -1);
		
	produto.id = IDaux;												// Após validação toda copia para a struct
	strcpy(produto.nome, valida_nome_recebimento(39, 10));			// Recebe nome e já copia para a struct
	produto.quantidade = valida_quantidade_recebimento(39, 12);		// Recebe quantidade e já copia para a struct					
	produto.tipo = valida_tipo_recebimento(39, 14);		 			// Recebe tipo e já copia para a struct
	produto.preco_unitario = valida_preco_recebimento(39, 16);	 	// Recebe preco e já copia para a struct
	produto.excluido = false;						 				// Define como não excluido
	
	textcolor(cor_destaque);

	//Se quiser confirmar o cadastro:
   	if( confirmarSN(65, 22, 2) ){
   		
		if(fwrite(&produto, sizeof(produto), 1, fp) != 1){		
			textcolor(RED);
			gotoxy(79, 22); printf("Erro na escrita do arquivo!");
			textcolor(cor_texto);			
		}
		else{  //se tudo der certo
		
			fflush( fp ); //limpa buffer arquivo 
			
			borda();
			
			switch(random_menu){		
				case 0:
					ram(85, 8);
					break;
				case 1: 
					gpu(88, 8);
					break;
				case 2:
					disquete(85, 8);
					break;
			}
			cursor(0); 
			
			textcolor(cor_texto);
			gotoxy(20,11); printf("Dados salvos com sucesso!");	
			textcolor(cor_destaque);		
		}
		
		Sleep(1000);
		while (kbhit())  //Isso continua se vê que há um input do teclado em espera e, em caso afirmativo, chama getch() para descartar o caractere
    	getch();
		
		cursor(1);
			
	}
	return; 
}

// 
// Parte do recebimento de dados 
// 

long valida_id(int linha, int coluna, int qntapagar)  // Recebe e valida id
{
	char aux[80];
	long tam, id;		// Armazena tamanho da string | Auxiliar 1 e 2 | int auxiliar que armazenará a id digitada
	bool valido;
	
	do{		
		valido = true;
		cursor(1);
		
		fflush(stdin);
				
		gotoxy(linha, coluna); fgets(aux, sizeof(aux), stdin);
		
		tam = strlen(aux);

		if(tam <= 1) continue; // Se nada foi digitado retorna a posição de inicio e pergunta novamente

		if(aux[0] == '0'){	
			// Se o primeiro digito de id for igual a 0 volta pro menu
			voltando_menu(72, 35, 1300, true);
			return 0;
		}
		
		if(tam > 7){  //se id > 999999
			erro_apagar( linha, coluna, 0 , qntapagar); //coluna, linha, tipo de erro: "[ERRO] ID inválido" e quantidade a se apagar
			valido = false;
			continue;
		}

		for(int i = 0; i < tam-1; i++){ // verifica caractere por caractere se é número	
			if(!isdigit(aux[i])) 
			{
				erro_apagar( linha, coluna, 0 , qntapagar); //coluna, linha, tipo de erro: "[ERRO] ID inválido" e quantidade a se apagar
				valido = false;
				break;
			}
		}
		if(valido) {				
			id = strtol(aux, NULL, 10); //Converte a "string" para long int
		}
	} while(!valido);
	
	return id;
}

bool isID_cadastrado(int aux){   //verifica se o ID mandado está presente no arquivo ou não
	
	rewind(fp); 

	//enquanto não chegar o final do arquivo E produto.id for igual auxiliar E não excluido
	while(fread(&produto, sizeof(produto), 1, fp) == 1){																
		if(produto.id == aux and !produto.excluido){				
			return true;
		}
	}	
	return false;	
}

// Recebe e valida nome tirando espaços e verificando se é vazio
char *valida_nome_recebimento(int linha, int coluna) 
{
	char nome[255];
	char *output = nome;

	while(true){
		gotoxy(linha, coluna); fgets(nome, sizeof(nome), stdin);
		// Remove o caractere de nova linha (\n) no final da string
        nome[strcspn(nome, "\n")] = '\0';

		// Remove espaços antes de qualquer letra
        int pos_leitura = 0;
        int pos_escrita = 0;
        int tamanho = strlen(nome);
        int espacoDuplo = 0;

		while(nome[pos_leitura]) {
			if (isspace(nome[pos_leitura])) {
				if (pos_escrita == 0 || isspace(nome[pos_escrita - 1])) {
                    pos_leitura++;
                    continue;
                }

                // Verifica se há espaços duplos
                if (espacoDuplo == 0) {
                    nome[pos_escrita] = ' ';
                    pos_escrita++;
                    espacoDuplo = 1;
                }
            } else {
                nome[pos_escrita] = nome[pos_leitura];
                pos_escrita++;
                espacoDuplo = 0;
            }
            pos_leitura++;
		}
		nome[pos_escrita] = '\0'; // Adiciona o caractere nulo ao final do nome

		// Verifica se nada foi digitado
        if (pos_escrita == 0 || isspace(nome[0])) {
            continue;
        }

		// Verifica o tamanho do nome
		if(pos_escrita > 150) {
			erro_apagar(39, 10, 5, 70); //[ERRO] Sem espaço no estoque!
			continue;
		}

		break;
	}
	
	return output;             
}

// Recebe e valida quantidade
long valida_quantidade_recebimento(int linha, int coluna) 
{
	char aux[50];
	
	int tam;
	bool valido = false;
	
	while(!valido) {
		fflush(stdin);
		
		gotoxy(linha, coluna); fgets(aux, sizeof(aux), stdin);
		// Remove o caractere de nova linha (\n) no final da string
        aux[strcspn(aux, "\n")] = '\0';

		tam = strlen(aux);

		// Se nada foi digitado
		if(tam <= 0) continue;

		// Verifica se todos os caracteres são dígitos
		for(int i = 0; i < tam; i++){
			if(!isdigit(aux[i])){
				erro_apagar( linha, coluna, 2 , 70); //"[ERRO] Quantidade Inválida" quantidade a se apagar
				valido = false;
				break;
			}
			valido = true;
		}

		// Verifica se o valor é muito grande
		if(valido && strtol(aux, NULL, 10) > 9999999){
			erro_apagar( linha, coluna, 5, 70); 	//"[ERRO] Sem espaço no estoque" e quantidade a se apagar
			valido = false;
		}
		
	};
			
	return strtol(aux, NULL, 10);  //retorna em long o valor
}

char valida_tipo_recebimento(int linha, int coluna) // Recebe e valida tipo 
{
 	char tipo;
 	bool valido = false;
 	
 	do {	
 		
 		fflush(stdin);
 	
 		gotoxy(linha, coluna); 
		tipo = toupper(getchar());
		
		if (tipo == '\n') continue; // Se nada foi digitado

		// Verifica se o tipo é válido
        switch (tipo) {
            case 'P':
            case 'G':
            case 'C':
            case 'M':
            case 'F':
            case 'W':
            case 'A':
            case 'R':
            case 'O':
			case '0':
                valido = true;
                break;
            default:
                erro_apagar( linha, coluna, 3 , 70); //"[ERRO] Tipo inválido" e quantidade a se apagar	
                break;
        }
	} while(!valido);
		
	return tipo; 
}

double valida_preco_recebimento(int linha, int coluna) // Recebe preço e valida
{
	char aux[32];
	int tam;
	double num;
	bool invalido = false;
	
	do {	
		fflush(stdin);
		
		gotoxy(linha, coluna); fgets(aux, sizeof(aux), stdin);
		// Remove o caractere de nova linha (\n) no final da string
        aux[strcspn(aux, "\n")] = '\0';

		tam = strlen(aux);
		
		if(tam == 0) continue; // Se nada for digitado

		for(int i = 0; i < tam; i++){
			if(aux[i] == ',') aux[i]='.';

			if(!isdigit(aux[i]) && aux[i] != '.') { // Verifica se é numérico	 
				erro_apagar( linha, coluna, 4 , 70 ); //coluna, linha , tipo de erro: "[ERRO] Valor inválido" equantidade a se apagar
				invalido = true;							
				break;
			}
		}
						
		if(!invalido){ // Se valor for numérico
			num = strtod(aux, NULL); // Converte para float

			if(num < 0)
			{
				invalido=true;
				erro_apagar( linha, coluna, 4 ,70); //coluna, linha, tipo de erro: "[ERRO] Valor inválido" e quantidade a se apagar	
			}
			else if(num > 1000000)
			{
				invalido=true;
				erro_apagar( linha, coluna, 6, 70);  // coluna, linha, tipo de erro: "[ERRO] Não aceitamos objetos desse valor" e quantidade a se apagar
			}
		}
	} while(invalido);
		
	return num; 
}

void erro_apagar(int col, int lin, int tipo_erro, int apagar)
{
	cursor(0);	
	textbackground(cor_fundo);
	gotoxy(col, lin); clreol(apagar);
	textbackground(12);
	gotoxy(col, lin); //seta o cursor no lugar para apresentar o erro
	switch(tipo_erro){
		case 0:
			printf("[ERRO] ID inv%clido",160);	//[ERRO] Id inválido
			break;
		case 1:
			printf("[ERRO] ID j%c cadastrado", 131); //[ERRO] Id já cadastrado
			break;
		case 2:
			printf("[ERRO] Quantidade inv%clida",160); //[ERRO] Quantidade inválida
			break;
		case 3:
			printf("[ERRO] Tipo inv%clido",160);	//[ERRO] Tipo inválido
			break;
		case 4:
			printf("[ERRO] Valor inv%clido",160); //[ERRO] Valor inválido
			break;
		case 5:
			printf("[ERRO] Sem espa%co no estoque!",135);	//[ERRO] Sem espaço no estoque!
			break;
		case 6:
			printf("[ERRO] N%co aceitamos objetos desse valor", 198);	//[ERRO] Não aceitamos objetos desse valor
			break;
		default:
			printf("[ERRO] Valor inv%clido",160); //[ERRO] Valor inválido
			break;
	}	
	Sleep(1000);
	while (kbhit())  //Isso continua se vê que há um input do teclado em espera e, em caso afirmativo, chama getch() para descartar o caractere
    getch();
	textbackground(cor_fundo);
	gotoxy(col, lin); clreol(apagar);
	cursor(1);	
	gotoxy(col, lin);	
}

void sub_menu() // Gera a parte visual e realiza a escolha da opção do submenu 
{
	int escolha;
	
	do{	
		borda();
		
		lupa(63, 4);
		
		// Menu 
		
		textcolor(cor_texto);		
		gotoxy(70, 19);  printf("Geral");
		gotoxy(70, 21);  printf("Busca por ID");
		gotoxy(70, 23);  printf("Busca por Tipo");
		gotoxy(70, 25);  printf("Busca por Nome"); 
		gotoxy(70, 27);  printf("Excluir Dados");
		gotoxy(70, 29);  printf("Retornar ao In%ccio", 161);
			
		escolha = navegar_menu(19, 29, 68);
		
		switch(escolha){		
			case 0:
				consulta_geral();
				break;
			case 1:
				consulta_id();
				break;
			case 2:
				consulta_tipo();
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
	}while(escolha != 5);
}

bool confirmarSN(int linha, int coluna, int confirmaTipo){
	
	char confirmar;
	
	gotoxy(linha, coluna); textcolor(cor_destaque);		
	switch(confirmaTipo){
		case 0:
			printf("Confirmar Altera%c%ces? (S/N): ", 135, 228);
			break;
		case 1:
			printf("Confirmar Exclus%co? (S/N): ", 198);
			linha -= 3;
		break;
			case 2:
			printf("Deseja salvar os dados? (S/N): ");
			linha++;
		break;
			case 3:
			printf("Deseja realizar mais um cadastro? (S/N): ");
			linha += 10;
		break;
	}			
	textcolor(cor_texto);
	
	do{
		fflush(stdin);
		gotoxy(linha + 30, coluna);
		confirmar = toupper(getchar());
				
		if(confirmar != 'S' && confirmar != 'N'){			
			erro_apagar(linha + 30, coluna, 10, 50);      //erro default do switch
			continue;
		}

		return (confirmar == 'S'); // Confirmação

	} while(confirmar != 'S' && confirmar != 'N');
	
	return 0;	
}

void alteracao()
{
	int id, escolha;

	do{
		borda(); 
		
		HDD(69, 4);
		
		textcolor(cor_texto);				
		gotoxy(70, 19); printf("Altera%c%co Geral", 135, 198);
		gotoxy(70, 21); printf("Alterar Nome");
		gotoxy(70, 23); printf("Alterar Quantidade");
		gotoxy(70, 25); printf("Alterar Tipo"); 
		gotoxy(70, 27); printf("Alterar Pre%co", 135);
		gotoxy(70, 29); printf("Retornar ao In%ccio", 161);
		
		
		escolha = navegar_menu(19, 29, 68); 
		
		if(escolha == 0){ // Se alteraçõa geral for escolhida		
			id = obtem_id_alteracao();
			if(id == 0) continue; // ignora o restante do if
			
			borda();
			
			tabela_tipos(58,37,1);
			
			textcolor(cor_destaque); textbackground(15);			
			gotoxy(76, 4); printf("Altera%c%co Geral", 135, 198); // Mensagem em destaque no meio da tela
			textcolor(cor_texto);    textbackground(cor_fundo);
						
			//GERA TABELA COM OS DADOS JÀ INCLUÍDOS
			//=================================================================================
			gotoxy(20, 5);	printf("-Dados originais:");		
			gera_tabela_vertical(7);  //faz a tabela e já completa ela automaticamente
			//=================================================================================

			gotoxy(20, 21);	printf("-Novos dados:");	
			textcolor(cor_destaque);
			
			gotoxy(20, 23); printf("Nome do Produto..: ");		
			gotoxy(20, 25); printf("Quantidade.......: ");			
			gotoxy(20, 27); printf("Tipo.............: ");					
			gotoxy(20, 29); printf("Pre%co Unit%crio...: ", 135, 160);
			textcolor(cor_texto);
			
			cursor(1);
							
			/// Alteração do nome /// Recebimento do novo nome ///
			
			char aux_nome[150]; // Armazena nome a ser alterado(97)		
			strcpy(aux_nome,valida_nome_recebimento(39, 23));
			
			/// Alreração de Quantidade /// Recebimento de nova quantidade ///
					
			long aux_quantidade = valida_quantidade_recebimento(39, 25);
						
			/// Alteração de tipo /// Recebimento de novo tipo ///
			
			char aux_tipo = valida_tipo_recebimento(39, 27);

			/// Alteração de Preço /// Recebimento do novo preço ///
			
			double num = valida_preco_recebimento(39, 29);
			
			cursor(1);
			
			if(confirmarSN(70, 31, 0)){
				abrir_arquivo_alterar();

				while(fread(&produto, sizeof(produto), 1, fp) == 1)	
				{
					if(produto.id == id and !produto.excluido)
					{
						int fposicao = ftell(fp); // guarda a posição do registro atual do arquivo 
						
						//Escreve as alterações na struct
						strcpy(produto.nome, aux_nome);
						produto.quantidade = aux_quantidade; // Retorna quantidade em int
						produto.tipo = aux_tipo;
						produto.preco_unitario = num; 
						
						if(fseek (fp, fposicao - (sizeof(produto)), SEEK_SET) != 0) 	//SEEK_SET indica o início do arquivo, funciona igual o rewind(fp); 
						{																// porém pode ser usado em verificações pois retorna algo
							gotoxy(60, 11);	printf("Houve um erro catastrofico voltando ao inicio do arquivo!");
							Sleep(1500);
							return;
						}
							
						if(fwrite(&produto, sizeof(produto), 1, fp) != 1)   //depois que colocou o "cursor" do leitor em cima da linha correta
						{													//usa-se o fwrite para salvar as alterações no arquivo
							textcolor(RED);
							gotoxy(79, 22); printf("Erro na escrita do arquivo!");
							textcolor(cor_texto);
						}
						break;
						
						fflush(fp);
					}
				}
			}
			
			fclose(fp);
			
			id = 0; 
		}
		else if(escolha == 1) // Alterar Nome
		{
			id = obtem_id_alteracao();	
			if(id == 0) continue; // ignora o restante do if
			
			borda();
			
			textcolor(cor_texto);
			
			//GERA TABELA COM OS DADOS JÀ INCLUÍDOS
			//=================================================================================
			gotoxy(20,5);	printf("-Dados originais:");		
			gera_tabela_vertical(7);  //faz a tabela e já completa ela automaticamente
			//=================================================================================

			gotoxy(20,21);	printf("-Novos dados:");	
			textcolor(cor_destaque);
			
			textbackground(15);
			gotoxy(73, 4); printf(" Altera%c%co de nome ", 135, 198); // Mensagem em destaque no meio da tela
			textbackground(cor_fundo);
			
			gotoxy(20, 25); printf("Nome do Produto..: ");		

			cursor(1);
			
			textcolor(cor_texto);
					
			/// Alteração do nome /// Recebimento do novo nome ///
			
			char aux_nome[150]; // Armazena nome						
			strcpy(aux_nome,valida_nome_recebimento(39,25));
			
			//CONFIRMAR PARA ESCREVER NO ARQUIVO
			if(confirmarSN(20,27,0)){  
				
				abrir_arquivo_alterar();

				while(fread(&produto, sizeof(produto), 1, fp) == 1){	
					if(produto.id == id and !produto.excluido){
						
						int fposicao = ftell(fp); // guarda a posição do registro atual do arquivo 
						
						// Alteração					
						strcpy(produto.nome, aux_nome);  //coloca o nome alterado no registro original
				
						if(fseek (fp, fposicao - (sizeof(produto)), SEEK_SET) != 0) 	//SEEK_SET indica o início do arquivo, funciona igual o rewind(fp); 
						{														// porém pode ser usado em verificações pois retorna algo
							gotoxy(20, 29);	printf("Houve um erro catastrofico voltando ao inicio do arquivo!");
							Sleep(1500);
							return;
						}
							
						if(fwrite(&produto, sizeof(produto), 1, fp) != 1)   //depois que colocou o "cursor" do leitor em cima da linha correta
						{													//usa-se o fwrite para salvar as alterações
							textcolor(RED);
							gotoxy(79, 22); printf("Erro na escrita do arquivo!");
							textcolor(cor_texto);
						}
						
						fflush(fp);						
						fclose(fp);
						break;							
					}
				}
			}
				
			id = 0; 
		}
		else if(escolha == 2) //Alterar Quantidade
		{
			id = obtem_id_alteracao();
			if(id == 0) continue; // ignora o restante do if
			
			borda();
			
			textcolor(cor_texto);
			
			//GERA TABELA COM OS DADOS JÀ INCLUÍDOS
			//=================================================================================
			gotoxy(20,5);	printf("-Dados originais:");		
			gera_tabela_vertical(7);  //faz a tabela e já completa ela automaticamente
			//=================================================================================
			
			gotoxy(20,23);	printf("-Novos dados:");	
			textcolor(cor_destaque);
			
			textbackground(15);
			gotoxy(71, 4); printf(" Altera%c%co de Quantidade ", 135, 198); // Mensagem em destaque no meio da tela
			textbackground(cor_fundo);
				
			gotoxy(20, 25); printf("Quantidade.......: ");			
			
			cursor(1);
			
			textcolor(cor_texto);
							
			long aux_quantidade = valida_quantidade_recebimento(39,25);
			
			//CONFIRMAR PARA ESCREVER NO ARQUIVO
			if(confirmarSN(20,27,0)){
				
				abrir_arquivo_alterar();

				while(fread(&produto, sizeof(produto), 1, fp) == 1){	
					if(produto.id == id and !produto.excluido){
						
						int fposicao = ftell(fp); // guarda a posição do registro atual do arquivo 
						
						// Alteração					
						produto.quantidade = aux_quantidade;  //coloca o nome alterado no registro original
				
						if(fseek (fp, fposicao - (sizeof(produto)), SEEK_SET) != 0) 	//SEEK_SET indica o início do arquivo, funciona igual o rewind(fp); 
						{														// porém pode ser usado em verificações pois retorna algo
							gotoxy(20, 29);	printf("Houve um erro catastrofico voltando ao inicio do arquivo!");
							Sleep(1500);
							return;
						}
							
						if(fwrite(&produto, sizeof(produto), 1, fp) != 1)   //depois que colocou o "cursor" do leitor em cima da linha correta
						{													//usa-se o fwrite para salvar as alterações
							textcolor(RED);
							gotoxy(79, 22); printf("Erro na escrita do arquivo!");
							textcolor(cor_texto);
						}
						
						fflush(fp);
						fclose(fp);						
						break;					
					}
				}
			}
						
			id = 0; 
		}
		else if(escolha == 3) //Alterar Tipo
		{
			id = obtem_id_alteracao();
			if(id == 0) continue; // ignora o restante do if
			
			borda();
			
			textcolor(cor_texto);
			
			//GERA TABELA COM OS DADOS JÀ INCLUÍDOS
			//=================================================================================
			gotoxy(20,5);	printf("-Dados originais:");		
			gera_tabela_vertical(7);  //faz a tabela e já completa ela automaticamente
			//=================================================================================
	     	
			gotoxy(20,23);	printf("-Novos dados:");	
			textcolor(cor_destaque);
			
			tabela_tipos(58,37,1);
			
			textbackground(15);	textcolor(cor_destaque);		
			gotoxy(73, 4); printf(" Altera%c%co de Tipo ", 135, 198); // Mensagem em destaque no meio da tela	
			textbackground(cor_fundo);
						
			gotoxy(20, 25); printf("Tipo.............: ");					
			textcolor(cor_texto);
			
			cursor(1);
			char aux_tipo = valida_tipo_recebimento(39,25);
			
			//CONFIRMAR PARA ESCREVER NO ARQUIVO
			if(confirmarSN(20,27,0)){
				
				abrir_arquivo_alterar();

				while(fread(&produto, sizeof(produto), 1, fp) == 1){	
					if(produto.id == id and !produto.excluido){
						
						int fposicao = ftell(fp); // guarda a posição do registro atual do arquivo 
						
						// Alteração					
						produto.tipo = aux_tipo;  //coloca o nome alterado no registro original
				
						if(fseek (fp, fposicao - (sizeof(produto)), SEEK_SET) != 0) 	//SEEK_SET indica o início do arquivo, funciona igual o rewind(fp); 
						{														// porém pode ser usado em verificações pois retorna algo
							gotoxy(20, 29);	printf("Houve um erro catastrofico voltando ao inicio do arquivo!");
							Sleep(1500);
							return;
						}
							
						if(fwrite(&produto, sizeof(produto), 1, fp) != 1)   //depois que colocou o "cursor" do leitor em cima da linha correta
						{													//usa-se o fwrite para salvar as alterações
							textcolor(RED);
							gotoxy(79, 22); printf("Erro na escrita do arquivo!");
							textcolor(cor_texto);
						}
						
						fflush(fp);
						fclose(fp);						
						break;					
					}
				}
			}
					
			id = 0; 
		}
		else if(escolha == 4) //Alterar Preço
		{
			id = obtem_id_alteracao();
			if(id == 0) continue; // ignora o restante do if
			
			borda();
			
			textcolor(cor_texto);
			
			//GERA TABELA COM OS DADOS JÀ INCLUÍDOS
			//=================================================================================
			gotoxy(20,5);	printf("-Dados originais:");		
			gera_tabela_vertical(7);  //faz a tabela e já completa ela automaticamente
			//=================================================================================
			
			gotoxy(20,23);	printf("-Novos dados:");	
			textcolor(cor_destaque);
			textbackground(15);
			gotoxy(75, 4); printf(" Altera%c%co de Pre%co ", 135, 198, 135); // Mensagem em destaque no meio da tela
			textbackground(cor_fundo);						
			gotoxy(20, 25); printf("Pre%co Unit%crio...: ", 135, 160);
			
			cursor(1);
			
			textcolor(cor_texto);		
			
			double num = valida_preco_recebimento(39,25);
			
			//CONFIRMAR PARA ESCREVER NO ARQUIVO
			if(confirmarSN(20,27,0)){
				
				abrir_arquivo_alterar();

				while(fread(&produto, sizeof(produto), 1, fp) == 1){	
					if(produto.id == id and !produto.excluido){
						
						int fposicao = ftell(fp); // guarda a posição do registro atual do arquivo 
						
						// Alteração					
						produto.preco_unitario = num;  //coloca o nome alterado no registro original
				
						if(fseek (fp, fposicao - (sizeof(produto)), SEEK_SET) != 0) 	//SEEK_SET indica o início do arquivo, funciona igual o rewind(fp); 
						{														// porém pode ser usado em verificações pois retorna algo
							gotoxy(20, 29);	printf("Houve um erro catastrofico voltando ao inicio do arquivo!");
							Sleep(1500);
							return;
						}
							
						if(fwrite(&produto, sizeof(produto), 1, fp) != 1)   //depois que colocou o "cursor" do leitor em cima da linha correta
						{													//usa-se o fwrite para salvar as alterações
							textcolor(RED);
							gotoxy(79, 22); printf("Erro na escrita do arquivo!");
							textcolor(cor_texto);
						}
						
						fflush(fp);
						fclose(fp);						
						break;					
					}
				}
			}
					
			id = 0; 
		}
		else if(escolha == 5) break; //sair do menu
		
	}while(id == 0);
		
	return;
}

int obtem_id_alteracao()
{		
	int aux; // auxiliar que armazenará a id digitada
	bool encontrado;
	
	abrir_arquivo();
	
	do{
		borda();
		
		cursor(1);
		
		textcolor(cor_destaque);		
		gotoxy(71, 4); textbackground(15);  printf(" Recebimento de ID "); textbackground(cor_fundo);
		gotoxy(20, 8); 	printf("Id do produto (0 para sair): ");			
		textcolor(cor_texto);
			
		encontrado = false;  //loop principal

		rewind(fp);	
		
		aux = valida_id(49, 8, 100);
			                                                                    
		if(aux == 0) return 0; // Retorna 0 para que a func de alteracao saia do loop 

		if(isID_cadastrado(aux)){
			textbackground(15); textcolor(cor_destaque); 
			gotoxy(72, 16); printf("  Item encontrado!  ");
			textbackground(cor_fundo);
			Sleep(800);
			encontrado = true;
			break;
		}
		else{
			textcolor(cor_destaque); 
			gotoxy(20, 30); printf("Pressione uma tecla para continuar...");
			textbackground(15);
			gotoxy(60, 16); printf(" [ Nenhum item com este ID foi encontrado ] ");
			textbackground(cor_fundo);
			getch();
			encontrado = false;
		}	
				
	}while(!encontrado);
	
	fclose(fp);
	
	return aux; 
}

void info_de_sistema() // Apresenta as informações do sistema
{
	borda();
	
	char input;
	
	do{		
		int L = 20, C = 7; // Controla o eixo x e y das informações
		
		// Apresenta as informações do sistema
		textcolor(cor_destaque); textbackground(15);
		gotoxy(73, 4);  printf(" Info do Sistema ");
		textbackground(cor_fundo);
		
		time_t t = time(NULL);
    	struct tm *tm = localtime(&t);
    	gotoxy(125, 4);printf("%s", asctime(tm));
		
		textcolor(cor_destaque);	
		gotoxy(L, C); 	 printf("Empresa: ");
		gotoxy(L, C+2);   printf("Nomes: ");
		gotoxy(L, C+4);  printf("N%cmeros: ",163);
		gotoxy(L, C+6);  printf("Turma: ");
		gotoxy(L, C+8);  printf("Ano: ");
		gotoxy(L, C+10);  printf("Sobre o software: ");
		
		textcolor(cor_texto);						
		gotoxy(L+9, C);	 printf("GoTech");
		gotoxy(L+7, C+2);   printf("Felipe Lima e Gabriel Nicolim");
		gotoxy(L+9, C+4);  printf("06 e 08");
		gotoxy(L+7, C+6);  printf("71A");
		gotoxy(L+5, C+8);  printf("2020");
		gotoxy(L, C+10);  printf("Sobre o software: ");
			
		textcolor(cor_texto);
		printf("Nosso software, que hoje se encontra na vers%co %.1f, se destina a simular um sistema de gerenciamento de",198, versao);
		gotoxy(20, 19); printf("estoque de uma loja de inform%ctica em C/C++.",160);
		gotoxy(20, 21); printf("Para a realiza%c%co desse projeto utilizamos fun%c%ces de cabe%calho da conio.c e conio.h e file da stdio.h.",135,198,135,228,135);
		gotoxy(20, 23); printf("Podem ser registrados perif%cricos e outras pe%cas de computador, que mais tarde podem ser alterados ou excluidos.",130,135);
			
		textcolor(cor_destaque);
		gotoxy(20, 30); printf("Pressione 0 para retornar ao menu"); 
		
		fflush(stdin); 
			
		input =	getch();
			
	}while(input != '0');
		
	voltando_menu(72, 35, 1500, true); // Apresenta mensagem Voltando pro menu... abaixo da borda
	
	return;
}

void sair() // Finaliza a execução do programa
{
	borda();
	
	textcolor(cor_texto);
	
	gotoxy(62, 17); printf("Obrigado por utilizar nosso programa!");
	
	fclose(fp);
	
	textcolor(cor_fundo); gotoxy(80, 34); // Esconde mensagem de encerramento 
	
	exit(1);
}

//
// Sub menu 
//

void consulta_geral()
{
	int cont_tuplas = - 1; // Contador de registros 
	
	char retornar = '0';
	
	abrir_arquivo();
	
	cursor(0); // Desliga o cursor
	
	bool vazio = true;  
	
	while(fread(&produto, sizeof(produto), 1, fp) == 1){// Verifica se o arquivo bin está vazio 
		if(!produto.excluido){		
			vazio = false;				//marca o arquivo como contendo dados e conta quantos tem
			cont_tuplas++;
		}
	}
	
	if(vazio){	
		borda();
		textcolor(cor_destaque); 
		gotoxy(52, 16); printf("[ N%co h%c nenhum item registrado! Por favor registre algo ]", 198,160);
		gotoxy(62, 30); printf("Pressione qualquer tecla para voltar");
		getch();
		fclose(fp);	
		return;
	}

	int contl = 1, limite, limiteAnte, pag, linha, pag_limite; // Variaveis Auxiliares
	
	pag = 1;
	
	pag_limite = ceil(cont_tuplas / 12);  
	
	gera_tabela(5);	// Gera borda e tabela inicial
	
	do{					
		limite = (12 * pag); // 12 linhas de dados por página (oq cabe na tabela)
		
		limiteAnte = (12 * (pag - 1));  // Limite da página anterior 
		
		textcolor(cor_texto);
		
		gotoxy(20, 31); printf("Pressione 0 para voltar ao menu de pesquisa");
		
		gotoxy(146, 4);	printf("%d", pag); // Número da página 
		
		contl = 1;    //reseta o contador de linha
		linha = 7;	//reseta a linha inicial(pmr da tabela) em q os dados começarão a ser colocados
		
		rewind(fp);
		
		while(fread(&produto, sizeof(produto), 1, fp) == 1){ // segue até o fim do arquivo
				
			if(contl > limiteAnte){ //se a linha atual for maior que o limite inferior:
			
				if(!produto.excluido){ // Só apresenta e vai para a próxima posição se o item não tiver sido excluido 			
					completa_tabela(linha);    //preenche a tabela
					linha += 2; 
				}
			}
			
			if(contl == limite) break; //se a linha atual for igual ao limite quebra
			else contl++; //adiciona mais uma linha ao contador
		}
		
		gotoxy(20, 34); 
		
		fflush(stdin);
		
		retornar = getch();
		
		switch(retornar){	
			case char(77): // Seta da direita <-
				if(pag <= pag_limite) 
				{
					pag++; // Avança a página | Limita pag a 10 
					rewind(fp);		//seta a leitura do arquivo na posição inicial do arquivo ("1º linha e coluna")	
					gera_tabela(5);
				}	
				break;
				
			case char(75): // Seta da esquerda ->
				if(pag > 1) 				
				{
					pag--; // Volta a pagina
					rewind(fp);	
					gera_tabela(5);	
				} 			
				break;
		}			
	}while (retornar != '0'); 		
	fclose(fp);			
	voltando_menu(72, 35, 1500, false); // Apresenta mensagem Voltando... abaixo da borda
	
	return;
}

void consulta_id()   //consulta por id
{	
	
	long id_busca; // Armazena id digitado pelo usuário durante a busca 
	bool continua = true;
	
	textcolor(cor_texto);
	
	do{
		
		borda();
			
		textcolor(cor_destaque);
		gotoxy(73, 4); textbackground(15); printf(" Consulta por ID "); textbackground(cor_fundo);
		gotoxy(20, 7); printf("Digite o Id (0 para sair): ");
		textcolor(cor_texto);

		id_busca = valida_id(47, 7, 100); 
		
		if(id_busca == 0) return;
		else{
			abrir_arquivo(); cursor(0);
			
			if(isID_cadastrado(id_busca)){			
					
				rewind(fp);
				
				while(!feof(fp) && fread(&produto, sizeof(produto), 1, fp) ){
					
					if(produto.id == id_busca and !produto.excluido){				
						//GERA TABELA COM OS DADOS JÀ INCLUÍDOS
				   		//=================================================================================
				   		gera_tabela_vertical(11);
						//=================================================================================
						
						tabela_tipos(58, 37, 1);
				
						textcolor(cor_destaque);
						gotoxy(20,30);printf("Pressione uma tecla para continuar...");					
						
						fflush(stdin);
						getch();
						
						break;	//sai do loop
					}				
				};
			}
			else{
				textcolor(cor_destaque); 
				gotoxy(71, 18);printf("[ C%cdigo inexistente ]",162);
				gotoxy(20, 30);printf("Pressione uma tecla para redigitar...");
				
				getch();
			}
			fclose(fp); //fecha arquivo
		}
		
	}while(continua);
		
	return;
}

void consulta_tipo()
{	
	
	borda();
		
	textcolor(cor_destaque);textbackground(15);
	gotoxy(71, 4); printf(" Consulta por Tipo ");
	textbackground(cor_fundo);
			
	tabela_tipos(56, 18, 2);	
	gotoxy(20, 7); printf("Digite tipo a ser pesquisado (0 para sair): ");

	int aux = valida_tipo_recebimento(64, 7);
	if(aux == '0') return;
	
	cursor(0); // Desliga o cursor
	
	abrir_arquivo();
	
	int cont_tuplas = -1;
	bool vazio = true;
	
	while(fread(&produto, sizeof(produto), 1, fp) == 1){ // segue até o fim do arquivo contando quantos tipos escolhidos tem
		if(produto.tipo == aux && !produto.excluido){ 		
			vazio = false;
			cont_tuplas++;
		}
	}
	
	if(!vazio){	
		int contl = 1, limite, limiteAnte, pag, linha, pag_limite; // Variaveis Auxiliares		
		char retornar;
		
		pag = 1;
		
		pag_limite = ceil(cont_tuplas / 12);  
		
		gera_tabela(5);	
		
		do{
			
			limite = (12 * pag); // 12 linhas de dados por página (oq cabe na tabela)
			limiteAnte = (12 * (pag - 1));  // Limite da página anterior 
			
			textcolor(cor_texto);
			
			gotoxy(20, 31); printf("Pressione 0 para voltar a escolha do tipo");
			gotoxy(146, 4);	printf("%d", pag); // Número da página 
			gotoxy(146, 6); printf("%c", aux);
			
			contl= 1;    //reseta o contador de linha
			linha= 7;	//reseta a linha inicial(pmr da tabela) em q os dados começarão a ser colocados
			
			rewind(fp);
			
			while(fread(&produto, sizeof(produto), 1, fp) == 1) // segue até o fim do arquivo
			{			
				if(contl > limiteAnte){ //se a linha atual for maior que o limite inferior:				
					if(produto.tipo == aux && !produto.excluido){ // Só apresenta e vai para a próxima posição se o item não tiver sido excluido 					
						completa_tabela(linha);    //preenche a tabela
						linha += 2; 
					}
				}
				
				if(contl == limite) break; //se a linha atual for igual ao limite quebra
				else if(!produto.excluido and produto.tipo == aux) contl++; //adiciona mais uma linha ao contador
			}
			
			gotoxy(20,34); 
			
			fflush(stdin);
			
			retornar = getch();
			
			switch(retornar){
						
				case char(77): // Se a seta direita for pressionada
					if(pag <= pag_limite){ 
					
						pag++; // Avança a página | Limita pag a 10 
						rewind(fp);		//seta a leitura do arquivo na posição inicial do arquivo ("1º linha e coluna")	
						gera_tabela(5);
					}	
					break;
					
				case char(75): // Se a seta da esquerda
					if(pag > 1){ 				
					
						pag--; // Volta a pagina
						rewind(fp);	
						gera_tabela(5);	
					} 			
					break;
			}
			
		}while (retornar != '0');  
			
		// Se 0 for pressionado 
		voltando_menu(74, 35, 1500, false); // Apresenta mensagem Voltando... abaixo da borda
	}		
	else{
		borda();
		textcolor(cor_destaque); 
		cursor(0); 
		gotoxy(50, 16); printf("[ N%co h%c nenhum item desse tipo registrado! Por favor registre algo ]", 198, 160);
		gotoxy(62, 30); printf("Pressione qualquer tecla para voltar");
		getch(); 
	}
	
	fclose(fp);	// fecha o arquivo
		
	return;
}

void consulta_nome()
{

	char aux[150], comp[150]; // Armazena nome  
	int tam, resultados;
	
	do{
	
		borda();
			
		cursor(1);
			
		textcolor(cor_destaque);
		textbackground(15);
		gotoxy(71, 4);  printf(" Consulta por Nome ");
		
		textbackground(cor_fundo);
		textcolor(cor_texto); 
		gotoxy(20, 7); printf("Digite o Nome (0 para sair): ");
		
		strcpy(aux, valida_nome_recebimento(49, 7));
		
		if(aux[0] == '0'){
			voltando_menu(74, 35, 1500, false); // Apresenta mensagem Voltando... abaixo da borda
			return;
		}	
		
		cursor(0);
		
		abrir_arquivo();
				
		resultados = 0;
		
		while(fread(&produto, sizeof(produto), 1, fp) == 1) // segue até o fim do arquivo
		{			
			strcpy(comp, produto.nome);
				
			if(strstr(strlwr(comp), strlwr(aux)) != NULL && !produto.excluido)	// Só apresenta e vai para a próxima posição se o item não tiver sido excluido
			{	
				resultados += 1;
			} 	
		}
		
		if(resultados == 0) 
		{
			textcolor(cor_destaque);
			gotoxy(69, 18); printf("[ Nome n%co encontrado ]", 198);			
		}
		else
		{
			if(resultados == 1)
			{
				rewind(fp);
				 
				while(fread(&produto, sizeof(produto), 1, fp) == 1) // segue até o fim do arquivo
				{			
					strcpy(comp, produto.nome);
						
					if(strstr(strlwr(comp),strlwr(aux)) != NULL && !produto.excluido)	// Só apresenta e vai para a próxima posição se o item não tiver sido excluido
					{	
						//GERA TABELA COM OS DADOS JÀ INCLUÍDOS
				   		//=================================================================================
				   		gera_tabela_vertical(11);
						//=================================================================================
						tabela_tipos(58,37,1);
						break;
					} 	
				}	
			}
			else
			{
				
				int cont_tuplas = resultados; // Contador de registros 
			
				char retornar = '0';
				
				cursor(0); // Desliga o cursor
		
				int contl = 1, limite, limiteAnte, pag, linha, pag_limite; // Variaveis Auxiliares
				
				pag = 1;
				
				pag_limite = ceil(cont_tuplas / 12);  
				
				gera_tabela(5);	// Gera borda e tabela inicial
				
				do{
							
					limite = (12 * pag); // 12 linhas de dados por página (oq cabe na tabela)
					
					limiteAnte = (12 * (pag - 1));  // Limite da página anterior 
					
					textcolor(cor_texto);
					
					gotoxy(20, 31); printf("Pressione 0 para voltar");
					
					gotoxy(146, 4);	printf("%d", pag); // Número da página 
					
					contl= 1;    //reseta o contador de linha
					linha= 7;	//reseta a linha inicial(pmr da tabela) em q os dados começarão a ser colocados
					
					rewind(fp);
					
					while(fread(&produto, sizeof(produto), 1, fp) == 1) // segue até o fim do arquivo
					{		
						strcpy(comp, produto.nome);
						
						if(contl > limiteAnte) //se a linha atual for maior que o limite inferior:
						{
							if(strstr(strlwr(comp), strlwr(aux)) != NULL && !produto.excluido) // Só apresenta e vai para a próxima posição se o item não tiver sido excluido 
							{
								completa_tabela(linha);    //preenche a tabela
								linha += 2; 
							}
						}
						
						if(contl == limite) break; //se a linha atual for igual ao limite quebra
						else if(strstr(strlwr(comp), strlwr(aux)) != NULL) contl++; //adiciona mais uma linha ao contador
					}
					
					gotoxy(20, 34); 
					
					fflush(stdin);
					
					retornar = getch();
					
					switch(retornar){
									
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
				voltando_menu(75, 35, 1500,false);
				
				fclose(fp);
				
			}
		}
		
		if(resultados <= 1)
		{
			textcolor(cor_destaque);
		
			gotoxy(20, 30); printf("Pressione uma tecla para redigitar...");
			
			getch();	
		}				
	
	}while(aux[0] != '0');
	
	return;
	
}

//exclusao lógica (continua no binário)
void excluir_dados()
{
	cursor(1); // Liga o cursor
	
	long fposicao;  //"linha" do struct no arquivo
	bool continuar = true;
	int IDaux = 1;
			
	do{
		borda();
	
		tabela_tipos(58, 37, 1); //apresenta a info doq as letras significam
		
		textcolor(cor_destaque); textbackground(15);
		gotoxy(71, 4); printf(" Exclus%co de dados ", 198);
		textbackground(cor_fundo);
		gotoxy(20, 7); printf("Digite o c%cdigo do produto a ser excluido (0 para sair): ", 162);
		
		textcolor(cor_texto);
		
		//Vai receber a id digitada e já validar e devolver 0 se quiser voltar
		IDaux = valida_id(77, 7, 74); 
								
		if(IDaux == 0) return;
			
		abrir_arquivo_alterar();
		
		if(!isID_cadastrado(IDaux)) { // se o id não for encontrado
			cursor(0);
		
			textcolor(cor_destaque);
			gotoxy(68, 18);printf("[ C%cdigo n%co encontrado ]",162,198);
			
			textcolor(cor_destaque);
		} else {		
			rewind(fp);  //volta ao inicio do arquivo para mostrar o dado na tela
			
			while(!feof(fp)){
				fread(&produto, sizeof(produto), 1, fp);
				if(produto.id == IDaux and !produto.excluido){
								
					//GERA TABELA COM OS DADOS JÀ INCLUÍDOS
					//=================================================================================
					gera_tabela_vertical(11);
					//=================================================================================
					
					break;
				}				
			};
			
			// Se o usuário não quiser excluir o produto
			if(!confirmarSN(20, 24, 1)) break;

			rewind(fp);
			fflush(fp);				   		
									
			//Cria o binário temporário para leitura e escrita
			FILE *fp_tmp;
			fp_tmp = fopen("tmp.bin", "wb+");
			if (!fp_tmp) {
				printf("Não foi possível abrir o arquivo temporário.");
				fclose(fp_tmp);
			}
			
			int encontrado = 0;
			
			//Vai copiar tudo pra o novo arquivo temporário EXCETO o ID marcado
			while (fread(&produto, sizeof(struct estrutura), 1, fp) == 1) {
				if (produto.id == IDaux ){ 
					textcolor(cor_texto); textbackground(12);
					gotoxy(20,27);printf(" Cadastro exclu%cdo com sucesso! ",161);
					gotoxy(20,28);printf(" %d registro encontrado e deletado! ", ++encontrado);
					textbackground(cor_fundo);
				} else {
					fwrite(&produto, sizeof(struct estrutura), 1, fp_tmp);
				}
			};
			
			fclose(fp);
			fclose(fp_tmp); 						 
				
			//checa se pode ter acesso ( <io.h> )
			if (_access_s("estoque.bin", 0) == 0)
				if (remove("estoque.bin") == 0) {
					//puts("Arquivo original deletado com sucesso!");
				}
				else
					perror("Não foi possivel deletar o aquivo original!");
			else 
				perror("Erro ao acessar o arquivo!");
			if (_access_s("tmp.bin", 0) == 0)
				if ( rename( "tmp.bin", "estoque.bin" ) == 0 ) {
					//puts("Arquivo renomeado com sucesso!");
				}
				else
					perror( "Erro renomeando arquivo!");
			else 
				perror("Erro ao acessar o arquivo temporario!");
			textcolor(cor_destaque);	
		}
		fflush(fp);
		fclose(fp);
		
		gotoxy(20,30);printf("Pressione uma tecla para retornar...");
		getch();
	} while(continuar);
	
	return;
}


void tabela_tipos(int col, int linha, int L)
{
    textcolor(cor_texto);
    
    gotoxy(col,linha);    printf(" P - Perif%crico       G - Gpu      C - Cpu",130);
    gotoxy(col,linha+L);    printf(" M - Mobo             F - Fonte    W - Cabos");
    gotoxy(col,linha+L+L);    printf(" A - Armazenamento    R - Ram      O - Outros");
}

int navegar_menu(int ini, int fim, int p)
{
	cursor(0); // Desativa o cursor
	
	int aux = ini; // Recebe posição da seta
	int input;
	
	do{	
		gotoxy(p, aux); printf("%c", 62);	//posição inicial da seta
			
		fflush(stdin); 
		
		input = getch();
		
		gotoxy(p, aux); printf(" ");
		
		switch(input){		
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
	tabela_tipos(58,37,1); //apresenta a info doq as letras significam
	
	textcolor(cor_texto);
	gotoxy(ci,4);	printf ("+------------------------------------------------------------------------------------------------------------------------+");
	gotoxy(ci,5);	printf ("|    ID    |                                Nome                                |  Pre%co Unit%crio  | Quantidade |  Tipo  |",135, 160);
	gotoxy(ci,6);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(ci,7);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(ci,8);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(ci,9);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(ci,10);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(ci,11);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(ci,12);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(ci,13);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(ci,14);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(ci,15);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(ci,16);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(ci,17);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(ci,18);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(ci,19);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(ci,20);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(ci,21);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(ci,22);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(ci,23);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(ci,24);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(ci,25);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(ci,26);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(ci,27);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(ci,28);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(ci,29);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(ci,30);	printf ("+------------------------------------------------------------------------------------------------------------------------+");
	
}

void completa_tabela(int linha)  //função para colocar os dados na tabela
{ 
	if(!produto.excluido){
		gotoxy(22, linha); printf("%ld", produto.id);
		gotoxy(33, linha); printf("%.66s", produto.nome); // Máximo de 66 caracteres
		gotoxy(102, linha); printf("%.2f", produto.preco_unitario);
		gotoxy(123, linha); printf("%ld", produto.quantidade);
		gotoxy(136, linha); printf("%c", produto.tipo);	
	}
}

void gera_tabela_vertical(int linha)
{
	if(!produto.excluido){
	
		int tam = strlen(produto.nome); 
	
		int x = 0;
		if(tam > 97) x++;
		gotoxy(20,linha);		printf ("+------------------------------------------------------------------------------------------------------------------------+");
		gotoxy(20,linha+1);		printf ("|  ID                |                                                                                                   |");
		gotoxy(20,linha+2);		printf ("+------------------------------------------------------------------------------------------------------------------------+");
		gotoxy(20,linha+3);		printf ("|  Nome              |                                                                                                   |");
		gotoxy(20,linha+3+x);	printf ("|");gotoxy(41, linha+3+x);printf("|                                                                                                   |");
		gotoxy(20,linha+4+x);	printf ("+------------------------------------------------------------------------------------------------------------------------+");
		gotoxy(20,linha+5+x);	printf ("|  Pre%co Unit%crio    |                                                                                                   |", 135, 160);
		gotoxy(20,linha+6+x);	printf ("+------------------------------------------------------------------------------------------------------------------------+");
		gotoxy(20,linha+7+x);	printf ("|  Quantidade        |                                                                                                   |");
		gotoxy(20,linha+8+x);	printf ("+------------------------------------------------------------------------------------------------------------------------+");
		gotoxy(20,linha+9+x);	printf ("|  Tipo              |                                                                                                   |");
		gotoxy(20,linha+10+x);	printf ("+------------------------------------------------------------------------------------------------------------------------+");
	
		gotoxy(43, linha+1); printf("%ld", produto.id);
		gotoxy(43, linha+3); printf("%.*s", 97, produto.nome);
		if(tam > 97){
			gotoxy(43, linha+3+x); printf("%.*s", 97, produto.nome + tam-97);
		}	
		gotoxy(43, linha+5+x); printf("%.2f", produto.preco_unitario);
		gotoxy(43, linha+7+x); printf("%ld", produto.quantidade);
		gotoxy(43, linha+9+x); printf("%c", produto.tipo);
	}	
}

void textcolor(int newcolor) // Define a cor do texto (vActual está aqui)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0xf0) | newcolor);
   //vActual.attribute = (csbi.wAttributes & 0xf0) | newcolor;
}

void textbackground(int newcolor) // Define a cor do fundo (vActual está aqui)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0x0f) | (newcolor << 4));
   //vActual.attribute = (csbi.wAttributes & 0x0f) | (newcolor << 4);
}

// Move o cursor para a coluna e linha desejada
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x - 1;
	coord.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void cursor (int x) { 	// Define se o cursor ira aparecer sim(1) ou não(0)
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

void voltando_menu(int linha,int coluna,int delay, bool menu){  //Apresenta a mensagem de voltar ao menu, espera e vai pro menu
	cursor(0);
	textbackground(12);
	textcolor(cor_texto);
	gotoxy(linha, coluna);
	if(menu) {
		printf("Voltando ao menu...");
	} else{
		printf("Voltando...");
	}		 	
	Sleep(delay);
} 