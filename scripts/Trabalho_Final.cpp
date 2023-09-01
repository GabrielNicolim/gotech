/* 
	Trabalho de FPD 4 Bimestre 2020					
	
	Felipe Lima Estevanatto 06
	Gabriel Gomes Nicolim 08
	
			71/81A
			
		CTI - Bauru - 2020
		
	- Este projeto visa aplicar os conceitos aprendidos em FPD e TP ao longo de 2020.
	
	- Para rodar nas versões antigas do DEVC++ Orwell basta descomentar todas as linhas com uso do text_info(linha 35) e vActual(1959 e 1969)
	Version 5.0 = Code in english and refactored

	Know bugs: 
	- Because of conio.h, modern terminals break the console positions, making the interface seem weird, but the problem can be circumvented by
	maximizing the terminal window with ALT + ENTER or F11 and updating the frame(easier to do this while loading).
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
#include <io.h>
#include "functions\desenhos.h"
#include "functions\utils.h"

#define version 4.9

//text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 160, 38, 1, 1}; // Define os limites para linha (38) e coluna (160)

// Funções conio.c
void textcolor(int newcolor);
void textbackground(int newcolor);
void gotoxy(int x, int y);
void cursor (int x);
void clreol(int x);

// Funções de construção do programa
void loading();
void start(); 
void drawnBorder(); 

// Funções de interação com o usuário 
void queryAll();
void queryType();
void queryName();
void deleteData();
void generateTable(int column);  
void generateVerticalTable(int li); 
void fillTable(int line);
void typesTable(int col, int line, int spacing);
int browseMenu(int start, int end, int p);
void cadastro_visual();
void cadastro_recebimento();
void queryID();

// Menu 
void startMenu();
void generalChange(); 
void subMenu();
void systemInfo();
void shutdown();

// Funções de validação => Validações + Registro
bool isIDRegistered(int aux);
long validateID(int line, int column, int eraseQuantity);
long validateQuantity(int line, int column);
char *validateName(int line, int column);
char validateType(int line, int column);
double validatePrice(int line, int column);

// Mensagem alteraveis e de confirmação
void errorErase (int col, int lin, int errorType, int apagar);
void returningMenu(int line,int column, int delay, bool menu);
bool confirmChoice(int line, int column,int confirmaTipo); 
int obtem_id_alteracao();

// Global variables
int random_menu;
FILE *fp;

void openFile()
{
	if((fp = fopen("estoque.bin", "ab+")) == NULL){
		system("cls"); drawnBorder();
		textcolor(TEXT_COLOR);
		gotoxy(65, 16); printf("Erro na abertura do arquivo!"); //caso haja um problema com o arquivo
		gotoxy(1, 33);
		exit(1);
	}
}

int openFileEdit()
{
	if((fp = fopen("estoque.bin", "rb+")) == NULL){
		cursor(0); 
		gotoxy(40, 16); printf("N%co foram encontrados dados, cadastre algo!", 198);
		getch();
		return 1;
	}
	else return 0;
}

typedef struct Product
{
	long id;
	char name[194];  // Register screen space
	long quantity;
	char type;
	double price;
	bool excluido;
	
} Product;

Product produto;

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
    
	start(); // Função de construção da tela inicial
}

void loading()
{
	drawnBorder(); 
	
	cursor(0);
	
	// Tela de loading com apresentação da versão do programa
	
	textcolor(TEXT_COLOR);
	
	gotoxy(58, 10); printf("Aguarde, estamos preparando tudo para voc%c!",136);
	gotoxy(15, 30); printf("Copyright%c GoTech",184);
	gotoxy(139, 30); printf("Vers%co %.1f",198, version);
	
	textcolor(RED); // Loading vermelho
	
	for(int i = 0; i <= 52; i++){
		gotoxy(52+i, 20);printf("%c", 219);
		Sleep(10);
	}
	
	textcolor(TEXT_COLOR);
	gotoxy(58, 10); printf("     Tudo pronto! Podemos iniciar...                            ");
	Sleep(1500);
	while (kbhit())  //Isso continua se vê que há um input do teclado em espera e, em caso afirmativo, chama getch() para descartar o caractere
    getch();
}

//
// Primeira página que o usuário tem contato 
//

void start() // Apresenta tela de inicio
{	
	while(true){
		drawnBorder(); 
	
		switch(random_menu){ // Menu com icone aleatorio	
			case 0:
				drawnDiskette(38, 6); // Disquete + drawnLogo
				drawnLogo(68, 8);
				break;
			case 1:				// drawnCPU + drawnLogo
				drawnCPU(38, 6); 	
				drawnLogo(68, 8);
				break;	
			case 2:				// drawnLogo
				drawnLogo(52, 8); 	
				break;
			case 3:				// drawnMobo + drawnLogo
				drawnMobo(103, 6); 		
				drawnLogo(40, 8);
				break;		
		}
		
		startMenu();
	}
}

void startMenu()
{	 
	textcolor(TEXT_COLOR);
	
	gotoxy(70, 19); printf("Cadastro");
	gotoxy(70, 21); printf("Pesquisa");
	gotoxy(70, 23); printf("Altera%c%co", 135, 198); 
	gotoxy(70, 25); printf("Info de Sistema");
	gotoxy(70, 27); printf("Sair");
	gotoxy(150, 41); printf("Vers%co %.1f",198, version);
	
	// Chama navegação com setas
	
	int escolha = browseMenu(19, 27, 68);
	
	switch(escolha){
		case 0:
			cadastro_visual();
			break;
		case 1:
			subMenu();
			break;
		case 2:
			generalChange(); 
			break; 
		case 3:
			systemInfo();
			break;
		case 4:
			shutdown();
			break;
	}
		
	return; 
}

//
// Escolhas possiveis no primeiro menu 
//

void cadastro_visual()
{
	openFile();
	
	cursor(1);
	
	do{
		system("cls");
		
		drawnBorder();
		
		typesTable(58, 37, 1);
		
		textcolor(CONTRAST_COLOR); textbackground(15);
		gotoxy(69, 4);  printf(" Cadastro de Produtos "); // Mensagem em destaque no meio da tela
		textbackground(BACKGROUND_COLOR);
			
		gotoxy(20, 31); printf("Digite 0 no campo de ID para retornar ao menu");
		gotoxy(20, 8); 	printf("Id do produto....: ");				
		gotoxy(20, 10); printf("Nome do Produto..: ");		
		gotoxy(20, 12); printf("Quantidade.......: ");			
		gotoxy(20, 14); printf("Tipo.............: ");					
		gotoxy(20, 16); printf("Pre%co Unit%crio...: ", 135, 160);		
			
		cadastro_recebimento(); // Recebe as respostas do usuário
				
	}while( confirmChoice(20,26,3) );
	
	fclose(fp);
	
	return; 
}

void cadastro_recebimento()
{
	textcolor(TEXT_COLOR);
	
	fflush(fp); 
	cursor(1);
	
	int IDaux;	
	do {
		IDaux = validateID(39, 8, 100); 						
		if(IDaux == 0){ 
			start();
			return;												
		}

		if(!isIDRegistered(IDaux)) break;

		errorErase(39, 8, 1 , 70); //coluna, linha, tipo de erro: "[ERRO] ID já cadastrado" e quantidade a se apagar	
		IDaux = -1; 	//continua no loop

	} while(IDaux == -1);
		
	produto.id = IDaux;												// Após validação toda copia para a struct
	strcpy(produto.name, validateName(39, 10));			// Recebe nome e já copia para a struct
	produto.quantity = validateQuantity(39, 12);		// Recebe quantidade e já copia para a struct					
	produto.type = validateType(39, 14);		 			// Recebe tipo e já copia para a struct
	produto.price = validatePrice(39, 16);	 	// Recebe preco e já copia para a struct
	
	textcolor(CONTRAST_COLOR);

	//Se quiser confirmar o cadastro:
   	if( confirmChoice(65, 22, 2) ){
   		
		if(fwrite(&produto, sizeof(produto), 1, fp) != 1){		
			textcolor(RED);
			gotoxy(79, 22); printf("Erro na escrita do arquivo!");
			textcolor(TEXT_COLOR);			
		}
		else{  //se tudo der certo
		
			fflush(fp); //limpa buffer arquivo 
			
			drawnBorder();
			
			switch(random_menu){		
				case 0:
					drawnRAM(85, 8);
					break;
				case 1: 
					drawnGPU(88, 8);
					break;
				case 2:
					drawnDiskette(85, 8);
					break;
			}
			cursor(0); 
			
			textcolor(TEXT_COLOR);
			gotoxy(20,11); printf("Dados salvos com sucesso!");	
			textcolor(CONTRAST_COLOR);		
		}
		
		Sleep(1000);
		while (kbhit())  //Isso continua se vê que há um input do teclado em espera e, em caso afirmativo, chama getch() para descartar o caractere
    	getch();
		
		cursor(1);
			
	}
	return; 
}

long validateID(int line, int column, int eraseQuantity)  // Recebe e valida id
{
	const int MAX_ID_LENGTH = 7;
	char input[MAX_ID_LENGTH + 2]; // +2 to account for newline and null terminator
	long id;
	
	while (true)
    {
        cursor(1);
        fflush(stdin);
        gotoxy(line, column);
        fgets(input, sizeof(input), stdin);
        
        if (input[0] == '0')
        {
            returningMenu(72, 35, 1300, true);
            return 0;
        }
        
        size_t length = strlen(input);
        if (length <= 1)
        {
            continue;
        }
        else if (length > MAX_ID_LENGTH + 1)
        {
            errorErase(line, column, 0, eraseQuantity);
            continue;
        }
        
        bool valid = true;
        for (size_t i = 0; i < length - 1; i++)
        {
            if (!isdigit(input[i]))
            {
                errorErase(line, column, 0, eraseQuantity);
                valid = false;
                break;
            }
        }
        
        if (valid)
        {
            id = strtol(input, NULL, 10);
            return id;
        }
    }
}

bool isIDRegistered(int aux){   //verifica se o ID mandado está presente no arquivo ou não
	
	rewind(fp); 

	//enquanto não chegar o final do arquivo E produto.id for igual auxiliar E não excluido
	while(fread(&produto, sizeof(produto), 1, fp) == 1){																
		if(produto.id == aux){				
			return true;
		}
	}	
	return false;	
}

// Recebe e valida nome tirando espaços e verificando se é vazio
char *validateName(int linha, int coluna) 
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
			errorErase(39, 10, 5, 70); //[ERRO] Sem espaço no estoque!
			continue;
		}

		break;
	}
	
	return output;             
}

// Recebe e valida quantidade
long validateQuantity(int linha, int coluna) 
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
				errorErase( linha, coluna, 2 , 70); //"[ERRO] Quantidade Inválida" quantidade a se apagar
				valido = false;
				break;
			}
			valido = true;
		}

		// Verifica se o valor é muito grande
		if(valido && strtol(aux, NULL, 10) > 9999999){
			errorErase( linha, coluna, 5, 70); 	//"[ERRO] Sem espaço no estoque" e quantidade a se apagar
			valido = false;
		}
		
	};
			
	return strtol(aux, NULL, 10);  //retorna em long o valor
}

char validateType(int linha, int coluna)
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
                errorErase( linha, coluna, 3 , 70); //"[ERRO] Tipo inválido" e quantidade a se apagar	
                break;
        }
	} while(!valido);
		
	return tipo; 
}

double validatePrice(int linha, int coluna) // Recebe preço e valida
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
				errorErase( linha, coluna, 4 , 70 ); //coluna, linha , tipo de erro: "[ERRO] Valor inválido" equantidade a se apagar
				invalido = true;							
				break;
			}
		}
						
		if(!invalido){ // Se valor for numérico
			num = strtod(aux, NULL); // Converte para float

			if(num < 0)
			{
				invalido=true;
				errorErase( linha, coluna, 4 ,70); //coluna, linha, tipo de erro: "[ERRO] Valor inválido" e quantidade a se apagar	
			}
			else if(num > 1000000)
			{
				invalido=true;
				errorErase( linha, coluna, 6, 70);  // coluna, linha, tipo de erro: "[ERRO] Não aceitamos objetos desse valor" e quantidade a se apagar
			}
		}
	} while(invalido);
		
	return num; 
}

void errorErase(int col, int lin, int errorType, int apagar)
{
	cursor(0);	
	textbackground(BACKGROUND_COLOR);
	gotoxy(col, lin); clreol(apagar);
	textbackground(12);
	gotoxy(col, lin);
	switch(errorType){
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
	textbackground(BACKGROUND_COLOR);
	gotoxy(col, lin); clreol(apagar);
	cursor(1);	
	gotoxy(col, lin);	
}

void subMenu()
{
	int choice;
	
	do{	
		drawnBorder();
		
		drawnMagnifier(63, 4);
		
		// Menu
		textcolor(TEXT_COLOR);		
		gotoxy(70, 19);  printf("Geral");
		gotoxy(70, 21);  printf("Busca por ID");
		gotoxy(70, 23);  printf("Busca por Tipo");
		gotoxy(70, 25);  printf("Busca por Nome"); 
		gotoxy(70, 27);  printf("Excluir Dados");
		gotoxy(70, 29);  printf("Retornar ao In%ccio", 161);
			
		choice = browseMenu(19, 29, 68);
		
		switch(choice){		
			case 0:
				queryAll();
				break;
			case 1:
				queryID();
				break;
			case 2:
				queryType();
				break;
			case 3:
				queryName(); 
				break;
			case 4:
				deleteData();
				break;
			case 5: 
				return;
		} 
	} while(choice != 5);
}

bool confirmChoice(int line, int coluna, int confirmaTipo){
	
	char confirmation;
	
	gotoxy(line, coluna); textcolor(CONTRAST_COLOR);		
	switch(confirmaTipo){
		case 0:
			printf("Confirmar Altera%c%ces? (S/N): ", 135, 228);
			break;
		case 1:
			printf("Confirmar Exclus%co? (S/N): ", 198);
			line -= 3;
			break;
		case 2:
			printf("Deseja salvar os dados? (S/N): ");
			line++;
			break;
		case 3:
			printf("Deseja realizar mais um cadastro? (S/N): ");
			line += 10;
			break;
	}			
	textcolor(TEXT_COLOR);
	
	do
	{
		fflush(stdin);
		gotoxy(line + 30, coluna);
		confirmation = toupper(getchar());
				
		if(confirmation != 'S' && confirmation != 'N'){			
			errorErase(line + 30, coluna, 10, 50);
			continue;
		}

		return (confirmation == 'S'); // Confirmação

	} while (confirmation != 'S' && confirmation != 'N');
	
	return false;	
}

void generalChange()
{
	int id, escolha;

	do{
		drawnBorder(); 
		
		drawnHDD(69, 4);
		
		textcolor(TEXT_COLOR);				
		gotoxy(70, 19); printf("Altera%c%co Geral", 135, 198);
		gotoxy(70, 21); printf("Alterar Nome");
		gotoxy(70, 23); printf("Alterar Quantidade");
		gotoxy(70, 25); printf("Alterar Tipo"); 
		gotoxy(70, 27); printf("Alterar Pre%co", 135);
		gotoxy(70, 29); printf("Retornar ao In%ccio", 161);
		
		
		escolha = browseMenu(19, 29, 68); 
		
		if (escolha == 5) return;

		id = obtem_id_alteracao();
		if(id == 0) continue; // ignora o restante do if
		drawnBorder();

		if(escolha == 0) // Se alteraçõa geral for escolhida	
		{
			typesTable(58,37,1);
			
			textcolor(CONTRAST_COLOR); textbackground(15);			
			gotoxy(76, 4); printf("Altera%c%co Geral", 135, 198); // Mensagem em destaque no meio da tela
			textcolor(TEXT_COLOR);    textbackground(BACKGROUND_COLOR);
						
			// Creates table already populated with data
			gotoxy(20, 5);	printf("-Dados originais:");		
			generateVerticalTable(7);

			gotoxy(20, 21);	printf("-Novos dados:");	
			textcolor(CONTRAST_COLOR);
			
			gotoxy(20, 23); printf("Nome do Produto..: ");		
			gotoxy(20, 25); printf("Quantidade.......: ");			
			gotoxy(20, 27); printf("Tipo.............: ");					
			gotoxy(20, 29); printf("Pre%co Unit%crio...: ", 135, 160);
			textcolor(TEXT_COLOR);
			
			cursor(1);
							
			/// Alteração do nome /// Recebimento do novo nome ///
			char aux_nome[150]; // Armazena nome a ser alterado(97)		
			strcpy(aux_nome,validateName(39, 23));
			
			/// Alreração de Quantidade /// Recebimento de nova quantidade ///
			long aux_quantidade = validateQuantity(39, 25);
						
			/// Alteração de tipo /// Recebimento de novo tipo ///
			char aux_tipo = validateType(39, 27);

			/// Alteração de Preço /// Recebimento do novo preço ///
			double num = validatePrice(39, 29);
			
			cursor(1);
			
			if(confirmChoice(70, 31, 0)){
				openFileEdit();

				while(fread(&produto, sizeof(produto), 1, fp) == 1)	
				{
					if(produto.id == id)
					{
						int fposicao = ftell(fp); // guarda a posição do registro atual do arquivo 
						
						//Escreve as alterações na struct
						strcpy(produto.name, aux_nome);
						produto.quantity = aux_quantidade; // Retorna quantidade em int
						produto.type = aux_tipo;
						produto.price = num; 
						
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
							textcolor(TEXT_COLOR);
						}
						break;
						
						fflush(fp);
					}
				}
			}
			
			fclose(fp);
		}
		else if(escolha == 1) // Alterar Nome
		{
			textcolor(TEXT_COLOR);
			
			// Creates table already populated with data
			gotoxy(20,5);	printf("-Dados originais:");		
			generateVerticalTable(7);

			gotoxy(20,21);	printf("-Novos dados:");
			textcolor(CONTRAST_COLOR);
			
			textbackground(15);
			gotoxy(73, 4); printf(" Altera%c%co de nome ", 135, 198);
			textbackground(BACKGROUND_COLOR);
			
			gotoxy(20, 25); printf("Nome do Produto..: ");

			cursor(1);
			
			textcolor(TEXT_COLOR);
					
			/// Alteração do nome
			char aux_nome[150];				
			strcpy(aux_nome,validateName(39,25));
			
			//CONFIRMAR PARA ESCREVER NO ARQUIVO
			if(confirmChoice(20, 27, 0)){  
				
				openFileEdit();

				while(fread(&produto, sizeof(produto), 1, fp) == 1){	
					if(produto.id == id){
						
						int fposicao = ftell(fp); // guarda a posição do registro atual do arquivo 
						
						// Alteração					
						strcpy(produto.name, aux_nome);  //coloca o nome alterado no registro original
				
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
							textcolor(TEXT_COLOR);
						}
											
						fclose(fp);
						break;							
					}
				}
			}
		}
		else if(escolha == 2) //Alterar Quantidade
		{
			textcolor(TEXT_COLOR);
			
			// Creates table already populated with data
			gotoxy(20,5);	printf("-Dados originais:");		
			generateVerticalTable(7);
			
			gotoxy(20,23);	printf("-Novos dados:");	
			textcolor(CONTRAST_COLOR);
			
			textbackground(15);
			gotoxy(71, 4); printf(" Altera%c%co de Quantidade ", 135, 198); // Mensagem em destaque no meio da tela
			textbackground(BACKGROUND_COLOR);
				
			gotoxy(20, 25); printf("Quantidade.......: ");			
			
			cursor(1);
			
			textcolor(TEXT_COLOR);
							
			long aux_quantidade = validateQuantity(39,25);
			
			//CONFIRMAR PARA ESCREVER NO ARQUIVO
			if(confirmChoice(20,27,0)){
				
				openFileEdit();

				while(fread(&produto, sizeof(produto), 1, fp) == 1){	
					if(produto.id == id and !produto.excluido){
						
						int fposicao = ftell(fp); // guarda a posição do registro atual do arquivo 
						
						// Alteração					
						produto.quantity = aux_quantidade;  //coloca o nome alterado no registro original
				
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
							textcolor(TEXT_COLOR);
						}
						
						fflush(fp);
						fclose(fp);						
						break;					
					}
				}
			}
		}
		else if(escolha == 3) //Alterar Tipo
		{	
			textcolor(TEXT_COLOR);
			
			// Creates table already populated with data
			gotoxy(20,5);	printf("-Dados originais:");		
			generateVerticalTable(7);
	     	
			gotoxy(20,23);	printf("-Novos dados:");	
			textcolor(CONTRAST_COLOR);
			
			typesTable(58,37,1);
			
			textbackground(15);	textcolor(CONTRAST_COLOR);		
			gotoxy(73, 4); printf(" Altera%c%co de Tipo ", 135, 198); // Mensagem em destaque no meio da tela	
			textbackground(BACKGROUND_COLOR);
						
			gotoxy(20, 25); printf("Tipo.............: ");					
			textcolor(TEXT_COLOR);
			
			cursor(1);
			char aux_tipo = validateType(39,25);
			
			//CONFIRMAR PARA ESCREVER NO ARQUIVO
			if(confirmChoice(20,27,0)){
				
				openFileEdit();

				while(fread(&produto, sizeof(produto), 1, fp) == 1){	
					if(produto.id == id and !produto.excluido){
						
						int fposicao = ftell(fp); // guarda a posição do registro atual do arquivo 
						
						// Alteração					
						produto.type = aux_tipo;  //coloca o nome alterado no registro original
				
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
							textcolor(TEXT_COLOR);
						}
						
						fclose(fp);						
						break;					
					}
				}
			}
		}
		else if(escolha == 4) //Alterar Preço
		{
			textcolor(TEXT_COLOR);
			
			// Creates table already populated with data
			gotoxy(20,5);	printf("-Dados originais:");		
			generateVerticalTable(7);  //faz a tabela e já completa ela automaticamente
			
			gotoxy(20,23);	printf("-Novos dados:");	
			textcolor(CONTRAST_COLOR);
			textbackground(15);
			gotoxy(75, 4); printf(" Altera%c%co de Pre%co ", 135, 198, 135); // Mensagem em destaque no meio da tela
			textbackground(BACKGROUND_COLOR);						
			gotoxy(20, 25); printf("Pre%co Unit%crio...: ", 135, 160);
			
			cursor(1);
			
			textcolor(TEXT_COLOR);		
			
			double num = validatePrice(39,25);
			
			//CONFIRMAR PARA ESCREVER NO ARQUIVO
			if(confirmChoice(20,27,0)){
				
				openFileEdit();

				while(fread(&produto, sizeof(produto), 1, fp) == 1){	
					if(produto.id == id and !produto.excluido){
						
						int fposicao = ftell(fp); // guarda a posição do registro atual do arquivo 
						
						// Alteração					
						produto.price = num;  //coloca o nome alterado no registro original
				
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
							textcolor(TEXT_COLOR);
						}
						
						fflush(fp);
						fclose(fp);						
						break;					
					}
				}
			}
		}
		id = 0;
	}while(id == 0);
		
	return;
}

int obtem_id_alteracao()
{		
	int aux;
	bool found;

	openFile();

	do {
		drawnBorder();
		
		cursor(1);
		
		textcolor(CONTRAST_COLOR);		
		gotoxy(71, 4); textbackground(15);  printf(" Recebimento de ID "); textbackground(BACKGROUND_COLOR);
		gotoxy(20, 8); 	printf("Id do produto (0 para sair): ");			
		textcolor(TEXT_COLOR);
			
		found = false;

		rewind(fp);	
		
		aux = validateID(49, 8, 100);
			                                                                    
		if(aux == 0) return 0; // Retorna 0 para que a func de generalChange saia do loop 

		if(isIDRegistered(aux)){
			textbackground(15); textcolor(CONTRAST_COLOR); 
			gotoxy(72, 16); printf("  Item encontrado!  ");
			textbackground(BACKGROUND_COLOR);
			Sleep(800);
			found = true;
			break;
		}
		else{
			textcolor(CONTRAST_COLOR); 
			gotoxy(20, 30); printf("Pressione uma tecla para continuar...");
			textbackground(15);
			gotoxy(60, 16); printf(" [ Nenhum item com este ID foi encontrado ] ");
			textbackground(BACKGROUND_COLOR);
			getch();
			found = false;
		}	
				
	} while (!found);
	
	fclose(fp);
	
	return aux; 
}

void systemInfo() // Apresenta as informações do sistema
{
	drawnBorder();
	
	char input;
	const int INFO_X = 20;
    const int INFO_Y = 7;
    const int MAX_INPUT_LENGTH = 2;

	do {
		textcolor(CONTRAST_COLOR); textbackground(15);
		gotoxy(73, 4);  printf(" Info do Sistema ");
		textbackground(BACKGROUND_COLOR);
		
		time_t t = time(NULL);
    	struct tm *tm = localtime(&t);
    	char time_str[20];
        strftime(time_str, sizeof(time_str), "%c", tm);
        gotoxy(125, 4); printf("%s", time_str);
		
		textcolor(CONTRAST_COLOR);	
		gotoxy(INFO_X, INFO_Y); 	 printf("Empresa: ");
		gotoxy(INFO_X, INFO_Y+2);   printf("Nomes: ");
		gotoxy(INFO_X, INFO_Y+4);  printf("N%cmeros: ",163);
		gotoxy(INFO_X, INFO_Y+6);  printf("Turma: ");
		gotoxy(INFO_X, INFO_Y+8);  printf("Ano: ");
		gotoxy(INFO_X, INFO_Y+10);  printf("Sobre o software: ");
		
		textcolor(TEXT_COLOR);						
		gotoxy(INFO_X+9, INFO_Y);	 printf("GoTech");
		gotoxy(INFO_X+7, INFO_Y+2);   printf("Felipe Lima e Gabriel Nicolim");
		gotoxy(INFO_X+9, INFO_Y+4);  printf("06 e 08");
		gotoxy(INFO_X+7, INFO_Y+6);  printf("71A");
		gotoxy(INFO_X+5, INFO_Y+8);  printf("2020");
		gotoxy(INFO_X, INFO_Y+10);  printf("Sobre o software: ");
		
		textcolor(TEXT_COLOR);
		printf("Nosso software, que hoje se encontra na vers%co %.1f, se destina a simular um sistema de gerenciamento de",198, version);
		gotoxy(20, 19); printf("estoque de uma loja de inform%ctica em C/C++.",160);
		gotoxy(20, 21); printf("Para a realiza%c%co desse projeto utilizamos fun%c%ces de cabe%calho da conio.c e conio.h e file da stdio.h.",135,198,135,228,135);
		gotoxy(20, 23); printf("Podem ser registrados perif%cricos e outras pe%cas de computador, que mais tarde podem ser alterados ou excluidos.",130,135);
		
		textcolor(CONTRAST_COLOR);
		gotoxy(20, 30); printf("Pressione 0 para retornar ao menu"); 
		
		fflush(stdin); 
		
		input =	getch();
		
	} while (input != '0');
		
	returningMenu(72, 35, 1500, true);
	
	return;
}

void shutdown()
{
	drawnBorder();
	
	textcolor(TEXT_COLOR);
	gotoxy(62, 17);
	printf("Obrigado por utilizar nosso programa!");
	
	fclose(fp);
	
	textcolor(BACKGROUND_COLOR); 
	gotoxy(80, 34); // Hide cursor

	exit(0);
}

void queryAll()
{
	int cont_tuplas = -1;
	
	char retornar = '0';
	
	openFile();
	
	cursor(0);
	
	bool empty = true;  
	
	while(fread(&produto, sizeof(produto), 1, fp) == 1){// Verifica se o arquivo bin está vazio 
		if(!produto.excluido){		
			empty = false;				//marca o arquivo como contendo dados e conta quantos tem
			cont_tuplas++;
		}
	}
	
	if(empty){	
		drawnBorder();
		textcolor(CONTRAST_COLOR); 
		gotoxy(52, 16); printf("[ N%co h%c nenhum item registrado! Por favor registre algo ]", 198,160);
		gotoxy(62, 30); printf("Pressione qualquer tecla para voltar");
		getch();
		fclose(fp);	
		return;
	}

	int contl = 1, limite, limiteAnte, pag, linha, pag_limite; // Variaveis Auxiliares
	
	pag = 1;
	
	pag_limite = ceil(cont_tuplas / 12);  
	
	generateTable(20);	// Gera drawnBorder e tabela inicial
	
	do{					
		limite = (12 * pag); // 12 linhas de dados por página (oq cabe na tabela)
		
		limiteAnte = (12 * (pag - 1));  // Limite da página anterior 
		
		textcolor(TEXT_COLOR);
		
		gotoxy(20, 31); printf("Pressione 0 para voltar ao menu de pesquisa");
		
		gotoxy(146, 4);	printf("%d", pag); // Número da página 
		
		contl = 1;    //reseta o contador de linha
		linha = 7;	//reseta a linha inicial(pmr da tabela) em q os dados começarão a ser colocados
		
		rewind(fp);
		
		while(fread(&produto, sizeof(produto), 1, fp) == 1){ // segue até o fim do arquivo
				
			if(contl > limiteAnte){ //se a linha atual for maior que o limite inferior:
			
				if(!produto.excluido){ // Só apresenta e vai para a próxima posição se o item não tiver sido excluido 			
					fillTable(linha);    //preenche a tabela
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
					generateTable(20);
				}	
				break;
				
			case char(75): // Seta da esquerda ->
				if(pag > 1) 				
				{
					pag--; // Volta a pagina
					rewind(fp);	
					generateTable(20);	
				} 			
				break;
		}			
	} while (retornar != '0'); 		
	fclose(fp);			
	returningMenu(72, 35, 1500, false);
	
	return;
}

void queryID()
{	
	long searchID;
	bool continua = true;
	
	//textcolor(TEXT_COLOR);
	
	while (continua)
	{
		drawnBorder();
		
		textcolor(CONTRAST_COLOR);
		gotoxy(73, 4); textbackground(15); printf(" Consulta por ID "); textbackground(BACKGROUND_COLOR);
		gotoxy(20, 7); printf("Digite o Id (0 para sair): ");
		textcolor(TEXT_COLOR);

		searchID = validateID(47, 7, 100); 
		
		if(searchID == 0) return;

		openFile(); cursor(0);
		
		if(isIDRegistered(searchID)){			
				
			rewind(fp);
			
			while(!feof(fp) && fread(&produto, sizeof(produto), 1, fp))
			{
				if(produto.id == searchID){				
					generateVerticalTable(11);

					typesTable(58, 37, 1);
			
					textcolor(CONTRAST_COLOR);
					gotoxy(20,30);printf("Pressione uma tecla para continuar...");					
					
					fflush(stdin);
					getch();
					
					break;
				}				
			};
		}
		else {
			textcolor(CONTRAST_COLOR); 
			gotoxy(71, 18);printf("[ C%cdigo inexistente ]",162);
			gotoxy(20, 30);printf("Pressione uma tecla para redigitar...");
			
			getch();
		}
		fclose(fp);
		
	}
		
	return;
}

void queryType()
{	
	drawnBorder();
		
	textcolor(CONTRAST_COLOR);textbackground(15);
	gotoxy(71, 4); printf(" Consulta por Tipo ");
	textbackground(BACKGROUND_COLOR);
			
	typesTable(56, 18, 2);	
	gotoxy(20, 7); printf("Digite tipo a ser pesquisado (0 para sair): ");

	int aux = validateType(64, 7);
	if(aux == '0') return;
	
	cursor(0);
	
	openFile();
	
	int cont_tuplas = -1;
	bool empty = true;
	
	while(fread(&produto, sizeof(produto), 1, fp) == 1){ // segue até o fim do arquivo contando quantos tipos escolhidos tem
		if(produto.type == aux){ 		
			empty = false;
			cont_tuplas++;
		}
	}
	
	if (empty) {
		drawnBorder();
		textcolor(CONTRAST_COLOR); 
		cursor(0); 
		gotoxy(50, 16); printf("[ N%co h%c nenhum item desse tipo registrado! Por favor registre algo ]", 198, 160);
		gotoxy(62, 30); printf("Pressione qualquer tecla para voltar");
		getch();
		return;
	}

	int contl = 1, limite, limiteAnte, pag, linha, pag_limite; // Variaveis Auxiliares		
	char retornar;
	
	pag = 1;
	
	pag_limite = ceil(cont_tuplas / 12);  
	
	generateTable(20);	
	
	do{
		
		limite = (12 * pag); // 12 linhas de dados por página (oq cabe na tabela)
		limiteAnte = (12 * (pag - 1));  // Limite da página anterior 
		
		textcolor(TEXT_COLOR);
		
		gotoxy(20, 31); printf("Pressione 0 para voltar a escolha do tipo");
		gotoxy(146, 4);	printf("%d", pag);
		gotoxy(146, 6); printf("%c", aux);
		
		contl= 1;    //reseta o contador de linha
		linha= 7;	//reseta a linha inicial(pmr da tabela) em q os dados começarão a ser colocados
		
		rewind(fp);
		
		while(fread(&produto, sizeof(produto), 1, fp) == 1)
		{			
			if(contl > limiteAnte){ //se a linha atual for maior que o limite inferior:				
				if(produto.type == aux){					
					fillTable(linha);
					linha += 2; 
				}
			}
			
			if(contl == limite) break;
			else if(produto.type == aux) contl++;
		}
		
		gotoxy(20,34); 
		
		fflush(stdin);
		
		retornar = getch();
		
		switch(retornar){
					
			case char(77): // Se a seta direita for pressionada
				if(pag <= pag_limite)
				{
					pag++; // Avança a página | Limita pag a 10 
					rewind(fp);		//seta a leitura do arquivo na posição inicial do arquivo ("1º linha e coluna")	
					generateTable(20);
				}	
				break;
				
			case char(75): // Se a seta da esquerda
				if(pag > 1){ 				
				
					pag--; // Volta a pagina
					rewind(fp);	
					generateTable(20);	
				} 			
				break;
		}
		
	} while (retornar != '0');  
		
	returningMenu(74, 35, 1500, false);
	
	fclose(fp);
		
	return;
}

void queryName()
{
	char aux[150], comp[150]; // Armazena nome  
	int tam, resultados;
	
	do{
	
		drawnBorder();
			
		cursor(1);
			
		textcolor(CONTRAST_COLOR);
		textbackground(15);
		gotoxy(71, 4);  printf(" Consulta por Nome ");
		
		textbackground(BACKGROUND_COLOR);
		textcolor(TEXT_COLOR); 
		gotoxy(20, 7); printf("Digite o Nome (0 para sair): ");
		
		strcpy(aux, validateName(49, 7));
		
		if(aux[0] == '0'){
			returningMenu(74, 35, 1500, false);
			return;
		}	
		
		cursor(0);
		
		openFile();
				
		resultados = 0;
		
		while(fread(&produto, sizeof(produto), 1, fp) == 1) // segue até o fim do arquivo
		{			
			if(stristr(produto.name, aux) != NULL)
			{
				resultados += 1;
			}
		}
		
		if(resultados == 0)
		{
			textcolor(CONTRAST_COLOR);
			gotoxy(69, 18); printf("[ Nome n%co encontrado ]", 198);			
		}
		else
		{
			if(resultados == 1)
			{
				rewind(fp);
				 
				while(fread(&produto, sizeof(produto), 1, fp) == 1) // segue até o fim do arquivo
				{			
					strcpy(comp, produto.name);
						
					if(strstr(strlwr(comp),strlwr(aux)) != NULL && !produto.excluido)	// Só apresenta e vai para a próxima posição se o item não tiver sido excluido
					{	
						//GERA TABELA COM OS DADOS JÀ INCLUÍDOS
				   		//=================================================================================
				   		generateVerticalTable(11);
						//=================================================================================
						typesTable(58,37,1);
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
				
				generateTable(20);	// Gera drawnBorder e tabela inicial
				
				do{
							
					limite = (12 * pag); // 12 linhas de dados por página (oq cabe na tabela)
					
					limiteAnte = (12 * (pag - 1));  // Limite da página anterior 
					
					textcolor(TEXT_COLOR);
					
					gotoxy(20, 31); printf("Pressione 0 para voltar");
					
					gotoxy(146, 4);	printf("%d", pag); // Número da página 
					
					contl= 1;    //reseta o contador de linha
					linha= 7;	//reseta a linha inicial(pmr da tabela) em q os dados começarão a ser colocados
					
					rewind(fp);
					
					while(fread(&produto, sizeof(produto), 1, fp) == 1) // segue até o fim do arquivo
					{		
						strcpy(comp, produto.name);
						
						if(contl > limiteAnte) //se a linha atual for maior que o limite inferior:
						{
							if(strstr(strlwr(comp), strlwr(aux)) != NULL && !produto.excluido) // Só apresenta e vai para a próxima posição se o item não tiver sido excluido 
							{
								fillTable(linha);    //preenche a tabela
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
								generateTable(20);
							}	
							break;
							
						case char(75): // Se a seta da esquerda
							if(pag > 1) 				
							{
								pag--; // Volta a pagina
								rewind(fp);	
								generateTable(20);	
							} 			
							break;
					}
					
				}while (retornar != '0');  
				
				// Se 0 for pressionado 
				returningMenu(75, 35, 1500,false);
				
				fclose(fp);
				
			}
		}
		
		if(resultados <= 1)
		{
			textcolor(CONTRAST_COLOR);
		
			gotoxy(20, 30); printf("Pressione uma tecla para redigitar...");
			
			getch();	
		}				
	
	}while(aux[0] != '0');
	
	return;
	
}

void deleteData()
{
	cursor(1);
	
	long fposicao;  //"linha" do struct no arquivo
	bool continuar = true;
	int IDaux = 1;
			
	do{
		drawnBorder();
	
		typesTable(58, 37, 1);
		
		textcolor(CONTRAST_COLOR); textbackground(15);
		gotoxy(71, 4);
		printf(" Exclus%co de dados ", 198);
		textbackground(BACKGROUND_COLOR);
		gotoxy(20, 7);
		printf("Digite o c%cdigo do produto a ser excluido (0 para sair): ", 162);
		
		textcolor(TEXT_COLOR);
		
		IDaux = validateID(77, 7, 74); 						
		if(IDaux == 0) return;
			
		openFileEdit();
		
		if(!isIDRegistered(IDaux)) {
			cursor(0);
		
			textcolor(CONTRAST_COLOR);
			gotoxy(68, 18);printf("[ C%cdigo n%co encontrado ]",162,198);
			
			textcolor(CONTRAST_COLOR);
		} else {		
			rewind(fp);
			
			while(!feof(fp)){
				fread(&produto, sizeof(produto), 1, fp);
				if(produto.id == IDaux and !produto.excluido){			
					generateVerticalTable(11);

					break;
				}				
			};
			
			if(!confirmChoice(20, 24, 1)) break;

			rewind(fp);	   		
									
			//Cria o binário temporário para leitura e escrita
			FILE *fp_tmp;
			fp_tmp = fopen("tmp.bin", "wb+");
			if (!fp_tmp) {
				printf("Não foi possível abrir o arquivo temporário.");
				fclose(fp_tmp);
			}
			
			int found = 0;
			
			//Vai copiar tudo pra o novo arquivo temporário EXCETO o ID marcado
			while (fread(&produto, sizeof(Product), 1, fp) == 1) {
				if (produto.id == IDaux ){ 
					textcolor(TEXT_COLOR); textbackground(12);
					gotoxy(20,27);printf(" Cadastro exclu%cdo com sucesso! ",161);
					gotoxy(20,28);printf(" %d registro encontrado e deletado! ", ++found);
					textbackground(BACKGROUND_COLOR);
				} else {
					fwrite(&produto, sizeof(Product), 1, fp_tmp);
				}
			};
			
			fclose(fp);
			fclose(fp_tmp); 						 
				
			//checa se pode ter acesso ( <io.h> )
			if (_access("estoque.bin", 0) == 0)
				if (remove("estoque.bin") == 0) {
					//puts("Arquivo original deletado com sucesso!");
				}
				else
					perror("Não foi possivel deletar o aquivo original!");
			else 
				perror("Erro ao acessar o arquivo!");
			if (_access("tmp.bin", 0) == 0)
				if ( rename( "tmp.bin", "estoque.bin" ) == 0 ) {
					//puts("Arquivo renomeado com sucesso!");
				}
				else
					perror( "Erro renomeando arquivo!");
			else 
				perror("Erro ao acessar o arquivo temporario!");
			textcolor(CONTRAST_COLOR);	
		}
		fclose(fp);
		
		gotoxy(20,30);
		printf("Pressione uma tecla para retornar...");
		getch();
	} while(continuar);
	
	return;
}


void typesTable(int col, int line, int spacing)
{
    textcolor(TEXT_COLOR);

    gotoxy(col,line);    printf(" P - Perif%crico       G - Gpu      C - Cpu",130);
    gotoxy(col,line+spacing);    printf(" M - Mobo             F - Fonte    W - Cabos");
    gotoxy(col,line+2*spacing);    printf(" A - Armazenamento    R - Ram      O - Outros");
}

int browseMenu(int start, int end, int p)
{
	cursor(0);

	int aux = start;
	int input;
	
	while (true)
	{	
		fflush(stdin); 

		gotoxy(p, aux); //Starting position
		printf("%c", 62);

		input = getch();
		
		gotoxy(p, aux); printf(" ");
		
		switch(input)
		{		
			case 72: // Up Arrow
				aux -= 2;
				
				if(aux < start) aux = end;

				gotoxy(p,aux);printf("%c", 62);
				break;

			case 80: // Down Arrow
				aux += 2;

				if(aux > end) aux = start;

				gotoxy(p,aux);printf("%c", 62);
				break;
			case 13:
				return (aux - start) / 2; // Starts at 0
				break;	
		}
	}
}

void generateTable(int column)
{
	drawnBorder();
	typesTable(58,37,1);
	
	textcolor(TEXT_COLOR);
	gotoxy(column, 4);	printf ("+------------------------------------------------------------------------------------------------------------------------+");
	gotoxy(column, 5);	printf ("|    ID    |                                Nome                                |  Pre%co Unit%crio  | Quantidade |  Tipo  |",135, 160);
	gotoxy(column, 6);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(column, 7);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(column, 8);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(column, 9);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(column, 10);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(column, 11);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(column, 12);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(column, 13);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(column, 14);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(column, 15);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(column, 16);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(column, 17);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(column, 18);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(column, 19);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(column, 20);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(column, 21);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(column, 22);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(column, 23);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(column, 24);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(column, 25);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(column, 26);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(column, 27);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(column, 28);	printf ("|------------------------------------------------------------------------------------------------------------------------|");
	gotoxy(column, 29);	printf ("|          |                                                                    |                  |            |        |");
	gotoxy(column, 30);	printf ("+------------------------------------------------------------------------------------------------------------------------+");
	
}

void fillTable(int line)
{ 
	gotoxy(22, line); printf("%ld", produto.id);
	gotoxy(33, line); printf("%.66s", produto.name);
	gotoxy(102, line); printf("%.2f", produto.price);
	gotoxy(123, line); printf("%ld", produto.quantity);
	gotoxy(136, line); printf("%c", produto.type);
}

void generateVerticalTable(int linha)
{
	int tam = strlen(produto.name); 

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
	gotoxy(43, linha+3); printf("%.*s", 97, produto.name);
	if(tam > 97){
		gotoxy(43, linha+3+x); printf("%.*s", 97, produto.name + tam-97);
	}	
	gotoxy(43, linha+5+x); printf("%.2f", produto.price);
	gotoxy(43, linha+7+x); printf("%ld", produto.quantity);
	gotoxy(43, linha+9+x); printf("%c", produto.type);
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

void returningMenu(int linha,int coluna,int delay, bool menu){
	cursor(0);
	textbackground(12);
	textcolor(TEXT_COLOR);
	gotoxy(linha, coluna);
	if(menu)
		printf("Voltando ao menu...");
	else
		printf("Voltando...");	 	
	Sleep(delay);
} 
