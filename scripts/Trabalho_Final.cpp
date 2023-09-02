/*
	Trabalho de FPD 4 Bimestre 2020

	Felipe Lima Estevanatto 06
	Gabriel Gomes Nicolim 08

			71/81A

		CTI - Bauru - 2020

	- Este projeto visa aplicar os conceitos aprendidos em FPD e TP ao longo de 2020.

	Know bugs:
	- To run this code in newer versions of DEVC++ (>Orwell) you need to uncomment all the lines with text_info(linha 35) and vActual(1959 e 1969)
	- Because of conio.h, modern terminals break the console positions, making the interface seem weird, but the problem can be circumvented by
	maximizing the terminal window with ALT + ENTER or F11 and updating the frame(easier to do this while loading).

	Version 5.0 = Code in english and refactored
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

#define version 5.0
#define MAX_NAME_LENGTH 194
//text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 160, 38, 1, 1}; // Define the limits to 38 lines and 160 cols

// conio.c functions
void textcolor(int newcolor);
void textbackground(int newcolor);
void gotoxy(int x, int y);
void cursor (int x);
void clreol(int x);

// Program flow
void loading();
void start();
void drawnBorder();

typedef struct Product
{
	long id;
	char name[MAX_NAME_LENGTH];
	long quantity;
	char type;
	double price;
	boolean excluido;
} Product;

// Data interaction
void openFile();
int openFileEdit();
void queryAll();
void queryID();
void queryName();
void queryType();
void deleteData();
void generateTable(int column);
void generateVerticalTable(int line);
void fillTableLine(int line);
void displaySearchResults(Product** produtos, int numProdutos);
void typesTable(int col, int line, int spacing);
void registerProductUI();
int registerProductData();
int getIDEdit();

// Menu
void startMenu();
void generalChange();
void subMenu();
int browseMenu(int start, int end, int p);
void systemInfo();
void shutdown();

// Receives and validates data
bool isIDRegistered(int aux);
long validateID(int line, int column, int eraseQuantity);
long validateQuantity(int line, int column);
char *validateName(int line, int column);
char validateType(int line, int column);
double validatePrice(int line, int column);

// Error messages
void errorErase(int col, int lin, int errorType, int apagar);
void returningMenu(int line,int column, int delay, bool menu);
bool confirmChoice(int line, int column,int confirmaTipo);

// Global variables
const int MAX_PRODUCT_QUANTITY = 9999999;
Product product;
FILE *fp;

int main()
{
	SetConsoleTitle("GoTech");
    system("mode con:cols=160 lines=37");

    DWORD dwWidth = GetSystemMetrics(SM_CXSCREEN);
	DWORD dwHeight = GetSystemMetrics(SM_CYSCREEN);

    HWND wh = GetConsoleWindow();
    MoveWindow(wh, dwWidth/8 , dwHeight/8 , 1300, 720, TRUE); // Move the windows 20 by 20

	srand(time(NULL));

    loading();

	start();

	return 0;
}

void loading()
{
	drawnBorder();

	cursor(0);

	textcolor(TEXT_COLOR);
	gotoxy(58, 10); printf("Aguarde, estamos preparando tudo para voc%c!",136);
	gotoxy(15, 30); printf("Copyright%c GoTech",184);
	gotoxy(139, 30); printf("Vers%co %.1f",198, version);
	textcolor(LIGHTRED);

	for(int i = 0; i <= 52; i++){
		gotoxy(52+i, 20);
		printf("%c", BLOCK_CHAR);
		Sleep(10);
	}

	textcolor(TEXT_COLOR);
	gotoxy(58, 10);
	printf("     Tudo pronto! Podemos iniciar...                            ");
	Sleep(1500);
	while (kbhit())
    getch();
}

void start()
{
	srand(time(NULL));
	int random_menu = rand() % 4;

	while (true) {
		drawnBorder();

		switch(random_menu){
			case 0:
				drawnDiskette(38, 6);
				drawnLogo(68, 8);
				break;
			case 1:
				drawnCPU(38, 6);
				drawnLogo(68, 8);
				break;
			case 2:
				drawnLogo(52, 8);
				break;
			case 3:
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

	int choice = browseMenu(19, 27, 68);

	switch(choice){
		case 0:
			registerProductUI();
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

void registerProductUI()
{
	cursor(1);

	do {
		system("cls");

		drawnBorder();

		typesTable(58, 37, 1);

		textcolor(CONTRAST_COLOR); textbackground(TEXT_COLOR);
		gotoxy(69, 4);  printf(" Cadastro de Produtos ");
		textbackground(BACKGROUND_COLOR);

		gotoxy(20, 31); printf("Digite 0 no campo de ID para retornar ao menu");
		gotoxy(20, 8); 	printf("Id do Produto....: ");
		gotoxy(20, 10); printf("Nome do Produto..: ");
		gotoxy(20, 12); printf("Quantidade.......: ");
		gotoxy(20, 14); printf("Tipo.............: ");
		gotoxy(20, 16); printf("Pre%co Unit%crio...: ", 135, 160);

		if(registerProductData() == 1) return;

	} while (confirmChoice(20, 26, 3));

	fclose(fp);

	return;
}

int registerProductData()
{
	textcolor(TEXT_COLOR);
	cursor(1);

	int IDaux;
	while (true) {
		IDaux = validateID(39, 8, 100);

		if(IDaux == 0) return 1;
		if(!isIDRegistered(IDaux)) break;

		errorErase(39, 8, 1 , 70); // "[ERRO] ID já cadastrado"
	};
	openFile();

	product.id = IDaux;
	strcpy(product.name, validateName(39, 10));
	product.quantity = validateQuantity(39, 12);
	product.type = validateType(39, 14);
	product.price = validatePrice(39, 16);

	textcolor(CONTRAST_COLOR);

   	if(confirmChoice(65, 22, 2)){

		if (fwrite(&product, sizeof(product), 1, fp) != 1)
		{
			textcolor(LIGHTRED);
			gotoxy(79, 22);
			printf("Erro na escrita do arquivo!");
			textcolor(TEXT_COLOR);
		}
		else {

			fflush(fp);
			drawnBorder();

			srand(time(NULL));
			int random_menu = rand() % 3;

			switch(random_menu)
			{
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
			gotoxy(20,11);
			printf("Dados salvos com sucesso!");
			textcolor(CONTRAST_COLOR);
		}

		Sleep(1000);
		while (kbhit())
    	getch();

		cursor(1);

	}
	return 0;
}

long validateID(int line, int column, int eraseQuantity)
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

bool isIDRegistered(int aux)
{
	rewind(fp);

	while(fread(&product, sizeof(product), 1, fp) == 1){
		if(product.id == aux){
			return true;
		}
	}
	return false;
}

char *validateName(int line, int column)
{
	char name[255];
	char *output = name;

	while(true){
		gotoxy(line, column); fgets(name, sizeof(name), stdin);
		// Remove the newline character (\n) at the end of the string
        name[strcspn(name, "\n")] = '\0';

		// Remove extra spaces
        int after_read = 0;
        int after_write = 0;
        int size = strlen(name);
        int doubleSpace = 0;

		while(name[after_read]) {
			if (isspace(name[after_read])) {
				if (after_write == 0 || isspace(name[after_write - 1])) {
                    after_read++;
                    continue;
                }

                // Check if there are two consecutive spaces
                if (doubleSpace == 0) {
                    name[after_write] = ' ';
                    after_write++;
                    doubleSpace = 1;
                }
            } else {
                name[after_write] = name[after_read];
                after_write++;
                doubleSpace = 0;
            }
            after_read++;
		}
		name[after_write] = '\0'; // Adiciona o caractere nulo ao final do name

        if (after_write == 0 || isspace(name[0])) {
            continue;
        }

		if(after_write > MAX_NAME_LENGTH) {
			errorErase(39, 10, 5, 70); //[ERRO] Sem espaço no estoque!
			continue;
		}

		break;
	}

	return output;
}

long validateQuantity(int line, int column)
{
	char aux[50];
	int size;
	long quantity;

	while (true)
	{
		fflush(stdin);
		gotoxy(line, column);
		fgets(aux, sizeof(aux), stdin);
		// Removes the newline character (\n) at the end of the string
        aux[strcspn(aux, "\n")] = '\0';

		size = strlen(aux);

		if(size <= 0) continue;

		// Formats the string to long
		if (sscanf(aux, "%ld", &quantity) != 1) {
            errorErase(line, column, 2 , 70); //"[ERRO] Quantidade Inválida"
            continue;
        }

		if(quantity > MAX_PRODUCT_QUANTITY){
            errorErase(line, column, 5, 70);  //"[ERRO] Sem espaço no estoque"
			continue;
        }

		break;
	};

	return quantity;
}

char validateType(int line, int column)
{
 	char type;

 	while (true)
	{
 		fflush(stdin);

 		gotoxy(line, column);
		type = toupper(getchar());

		if (type == '\n') continue;

        switch (type) {
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
                return type;
                break;
            default:
                errorErase(line, column, 3 , 70); //"[ERRO] Tipo inválido"
                break;
        }
	};

	return '0';
}

double validatePrice(int line, int column)
{
	char aux[32];
	double num;

	while (true) {
		fflush(stdin);

		gotoxy(line, column); fgets(aux, sizeof(aux), stdin);
		// Removes the newline character (\n) at the end of the string
        aux[strcspn(aux, "\n")] = '\0';

		if (strlen(aux) == 0) continue;

		if (!isNumeric(aux)) {
            errorErase(line, column, 4, 70); //"[ERRO] Valor inválido"
            continue;
        }

		num = convertToDouble(aux);

        if (num < 0) {
            errorErase(line, column, 4, 70); //"[ERRO] Valor inválido"
            continue;
        }

        if (num > 1000000) {
            errorErase(line, column, 6, 70);  //"[ERRO] Não aceitamos objetos desse valor"
            continue;
        }

        break;
	};

	return num;
}

void errorErase(int col, int lin, int errorType, int apagar)
{
	cursor(0);
	textbackground(BACKGROUND_COLOR);
	gotoxy(col, lin); clreol(apagar);
	textbackground(LIGHTRED);
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

bool confirmChoice(int line, int column, int confirmaTipo){

	char confirmation;

	gotoxy(line, column); textcolor(CONTRAST_COLOR);
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

	do {
		fflush(stdin);
		gotoxy(line + 30, column);
		confirmation = toupper(getchar());

		if(confirmation != 'S' && confirmation != 'N'){
			errorErase(line + 30, column, 10, 50);
			continue;
		}

		return (confirmation == 'S');

	} while (confirmation != 'S' && confirmation != 'N');

	return false;
}

void generalChange()
{
	int id, choice;

	while (true) {
		drawnBorder();

		drawnHDD(69, 4);

		textcolor(TEXT_COLOR);
		gotoxy(70, 19); printf("Altera%c%co Geral", 135, 198);
		gotoxy(70, 21); printf("Alterar Nome");
		gotoxy(70, 23); printf("Alterar Quantidade");
		gotoxy(70, 25); printf("Alterar Tipo");
		gotoxy(70, 27); printf("Alterar Pre%co", 135);
		gotoxy(70, 29); printf("Retornar ao In%ccio", 161);

		choice = browseMenu(19, 29, 68);

		if (choice == 5) return;

		id = getIDEdit();
		if(id == 0) continue;

		double price = product.price;
		long aux_quantity = product.quantity;
		char aux_type = product.type;
		char aux_name[MAX_NAME_LENGTH];
		strcpy(aux_name, product.name);

		drawnBorder();
		textcolor(TEXT_COLOR);
		// Creates table already populated with data
		gotoxy(20, 5);	printf("-Dados originais:");
		generateVerticalTable(7);

		gotoxy(20, 21);	printf("-Novos dados:");
		textcolor(CONTRAST_COLOR);
		cursor(1);
		typesTable(58,37,1);

		if(choice == 0) // Alteração geral
		{
			textcolor(CONTRAST_COLOR); textbackground(TEXT_COLOR);
			gotoxy(76, 4);
			printf("Altera%c%co Geral", 135, 198);
			textcolor(TEXT_COLOR);    textbackground(BACKGROUND_COLOR);

			gotoxy(20, 23); printf("Nome do Produto..: ");
			gotoxy(20, 25); printf("Quantidade.......: ");
			gotoxy(20, 27); printf("Tipo.............: ");
			gotoxy(20, 29); printf("Pre%co Unit%crio...: ", 135, 160);

			textcolor(TEXT_COLOR);
			strcpy(aux_name,validateName(39, 23));
			aux_quantity = validateQuantity(39, 25);
			aux_type = validateType(39, 27);
			price = validatePrice(39, 29);
		}
		else if(choice == 1) // Alterar Nome
		{
			textbackground(TEXT_COLOR);
			gotoxy(73, 4); printf(" Altera%c%co de nome ", 135, 198);
			textbackground(BACKGROUND_COLOR);

			gotoxy(20, 25); printf("Nome do Produto..: ");

			textcolor(TEXT_COLOR);
			strcpy(aux_name,validateName(39,25));
		}
		else if(choice == 2) //Alterar Quantidade
		{
			textbackground(TEXT_COLOR);
			gotoxy(71, 4); printf(" Altera%c%co de Quantidade ", 135, 198); // Mensagem em destaque no meio da tela
			textbackground(BACKGROUND_COLOR);

			gotoxy(20, 25); printf("Quantidade.......: ");

			textcolor(TEXT_COLOR);
			aux_quantity = validateQuantity(39,25);
		}
		else if(choice == 3) //Alterar Tipo
		{
			textbackground(TEXT_COLOR);	textcolor(CONTRAST_COLOR);
			gotoxy(73, 4); printf(" Altera%c%co de Tipo ", 135, 198); // Mensagem em destaque no meio da tela
			textbackground(BACKGROUND_COLOR);

			gotoxy(20, 25); printf("Tipo.............: ");

			textcolor(TEXT_COLOR);
			aux_type = validateType(39,25);
		}
		else if(choice == 4) //Alterar Preço
		{
			textbackground(TEXT_COLOR);
			gotoxy(75, 4);
			printf(" Altera%c%co de Pre%co ", 135, 198, 135); // Mensagem em destaque no meio da tela
			textbackground(BACKGROUND_COLOR);

			gotoxy(20, 25);
			printf("Pre%co Unit%crio...: ", 135, 160);

			textcolor(TEXT_COLOR);
			price = validatePrice(39,25);
		}

		if(confirmChoice(70, 31, 0)){

			openFileEdit();

			while(fread(&product, sizeof(product), 1, fp) == 1){
				if(product.id == id){

					int fposicao = ftell(fp); // Store the position of the file pointer

					product.price = price;
					product.quantity = aux_quantity;
					product.type = aux_type;
					strcpy(product.name, aux_name);

					if(fseek (fp, fposicao - (sizeof(product)), SEEK_SET) != 0) //SEEK_SET indica o início do arquivo, funciona igual o rewind(fp);
					{															// porém pode ser usado em verificações pois retorna algo
						gotoxy(20, 29);	printf("Houve um erro catastrofico voltando ao inicio do arquivo!");
						Sleep(1500);
						return;
					}

					if(fwrite(&product, sizeof(product), 1, fp) != 1)   //depois que colocou o "cursor" do leitor em cima da linha correta
					{													//usa-se o fwrite para salvar as alterações
						textcolor(LIGHTRED);
						gotoxy(79, 22); printf("Erro na escrita do arquivo!");
						textcolor(TEXT_COLOR);
					}

					break;
				}
			}
		}

		fclose(fp);
	};

	return;
}

int getIDEdit()
{
	int aux;
	bool found;

	openFile();

	do {
		drawnBorder();

		cursor(1);

		textcolor(CONTRAST_COLOR);
		gotoxy(71, 4); textbackground(TEXT_COLOR);  printf(" Recebimento de ID "); textbackground(BACKGROUND_COLOR);
		gotoxy(20, 8); 	printf("Id do product (0 para sair): ");
		textcolor(TEXT_COLOR);

		found = false;

		rewind(fp);

		aux = validateID(49, 8, 100);

		if(aux == 0) return 0;

		if(isIDRegistered(aux)){
			textbackground(TEXT_COLOR); textcolor(CONTRAST_COLOR);
			gotoxy(72, 16); printf("  Item encontrado!  ");
			textbackground(BACKGROUND_COLOR);
			Sleep(800);
			found = true;
			break;
		}
		else{
			textcolor(CONTRAST_COLOR);
			gotoxy(20, 30); printf("Pressione uma tecla para continuar...");
			textbackground(TEXT_COLOR);
			gotoxy(60, 16); printf(" [ Nenhum item com este ID foi encontrado ] ");
			textbackground(BACKGROUND_COLOR);
			getch();
			found = false;
		}

	} while (!found);

	fclose(fp);

	return aux;
}

void systemInfo()
{
	drawnBorder();

	char input;
	const int INFO_X = 20;
    const int INFO_Y = 7;
    const int MAX_INPUT_LENGTH = 2;

	do {
		textcolor(CONTRAST_COLOR); textbackground(TEXT_COLOR);
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
	openFile();

	cursor(0);

	int numProducts = 0;
    Product** produtos = NULL;

    while (fread(&product, sizeof(product), 1, fp) == 1) {
		numProducts++;
		produtos = (Product**) realloc(produtos, numProducts * sizeof(Product*));
		produtos[numProducts - 1] = (Product*) malloc(sizeof(Product));
		*produtos[numProducts - 1] = product;
    }

	displaySearchResults(produtos, numProducts);

	free(produtos);
	fclose(fp);

	return;
}

void queryID()
{
	long searchID;

	while (true)
	{
		drawnBorder();

		textcolor(CONTRAST_COLOR);
		gotoxy(73, 4); textbackground(TEXT_COLOR); printf(" Consulta por ID "); textbackground(BACKGROUND_COLOR);
		gotoxy(20, 7); printf("Digite o Id (0 para sair): ");
		textcolor(TEXT_COLOR);

		searchID = validateID(47, 7, 100);

		if(searchID == 0) return;

		openFile();
		cursor(0);

		if(!isIDRegistered(searchID)){
			textcolor(CONTRAST_COLOR);
			gotoxy(71, 18);printf("[ C%cdigo inexistente ]",162);
			gotoxy(20, 30);printf("Pressione uma tecla para redigitar...");

			getch();
			continue;
		}
		generateVerticalTable(11);

		typesTable(58, 37, 1);

		textcolor(CONTRAST_COLOR);
		gotoxy(20,30);printf("Pressione uma tecla para continuar...");

		fflush(stdin);
		getch();

		fclose(fp);
	}

	return;
}

void queryType()
{
	drawnBorder();

	textcolor(CONTRAST_COLOR);textbackground(TEXT_COLOR);
	gotoxy(71, 4); printf(" Consulta por Tipo ");
	textbackground(BACKGROUND_COLOR);

	typesTable(56, 18, 2);

	textcolor(TEXT_COLOR);
	gotoxy(20, 7); printf("Digite tipo a ser pesquisado (0 para sair): ");

	char aux = validateType(64, 7);
	if(aux == '0') return;

	cursor(0);

	openFile();

	int numProducts = 0;
    Product** produtos = NULL;

    while (fread(&product, sizeof(product), 1, fp) == 1) {
        if (product.type == aux) {
            numProducts++;
			produtos = (Product**) realloc(produtos, numProducts * sizeof(Product*));
			produtos[numProducts - 1] = (Product*) malloc(sizeof(Product));
			*produtos[numProducts - 1] = product;
        }
    }

	displaySearchResults(produtos, numProducts);

	free(produtos);
	fclose(fp);

	return;
}

void queryName()
{
	char nameSearch[MAX_NAME_LENGTH];

	while (true)
	{
		drawnBorder();
		cursor(1);

		textcolor(CONTRAST_COLOR);
		textbackground(TEXT_COLOR);
		gotoxy(71, 4);  printf(" Consulta por Nome ");

		textbackground(BACKGROUND_COLOR);
		textcolor(TEXT_COLOR);
		gotoxy(20, 7); printf("Digite o Nome (0 para sair): ");

		strcpy(nameSearch, validateName(49, 7));

		if(nameSearch[0] == '0'){
			returningMenu(74, 35, 1500, false);
			return;
		}

		cursor(0);
		openFile();

		int numProducts = 0;
		Product** products = NULL;

		while (fread(&product, sizeof(product), 1, fp) == 1) {
			if (stristr(product.name, nameSearch) != NULL) {
				numProducts++;
				products = (Product**) realloc(products, numProducts * sizeof(Product*));
				products[numProducts - 1] = (Product*) malloc(sizeof(Product));
				*products[numProducts - 1] = product;
			}
		}

		displaySearchResults(products, numProducts);

		returningMenu(75, 35, 1000,false);
		free(products);
		fclose(fp);
	};

	return;

}

void displaySearchResults(Product** produtos, int numProducts) {
	if (numProducts == 0)
	{
		drawnBorder();
		textcolor(CONTRAST_COLOR);
		gotoxy(52, 16); printf("[ N%co h%c nenhum item registrado! Por favor registre algo ]", 198,160);
		gotoxy(62, 30); printf("Pressione qualquer tecla para voltar");
		getch();
		fclose(fp);
		return;
	}

	if(numProducts == 1)
	{
		generateVerticalTable(11);
		typesTable(58, 37, 1);

		textcolor(CONTRAST_COLOR);
		gotoxy(20,30);
		printf("Pressione uma tecla para continuar...");

		fflush(stdin);
		getch();
		return;
	}

	int lineCounter = 1, limit, previousLimit, page=1, line, pageLimit;
	const int MAX_PRODUCTS_PER_PAGE = 12;
	char exitloop;

	pageLimit = ceil(numProducts / MAX_PRODUCTS_PER_PAGE);

	generateTable(20);

	while (true) {
		limit = (MAX_PRODUCTS_PER_PAGE * page);

		previousLimit = (MAX_PRODUCTS_PER_PAGE * (page - 1)); // Limit of the previous page

		textcolor(TEXT_COLOR);

		gotoxy(20, 31); printf("Pressione 0 para voltar ao menu de pesquisa");
		gotoxy(146, 4);	printf("%d", page);

		lineCounter = 1;
		line = 7;

		for(int i = 0; i < numProducts; i++) {
			product = *produtos[i];

			if(lineCounter > previousLimit){
				fillTableLine(line);
				line += 2;
			}

			if(lineCounter == limit) break;
			else lineCounter++;
		}

		gotoxy(20, 34);

		exitloop = getch();

		switch(exitloop){
			case char(77): // Right arrow ->
				if(page <= pageLimit)
				{
					page++;
					rewind(fp);
					generateTable(20);
				}
				break;

			case char(75): // Left arrow <-
				if(page > 1)
				{
					page--;
					rewind(fp);
					generateTable(20);
				}
				break;
			case '0':
				returningMenu(75, 35, 1500, false);
				return;
		}
	};
}

void deleteData()
{
	cursor(1);

	int IDaux = 1;

	while (true) {
		drawnBorder();

		typesTable(58, 37, 1);

		textcolor(CONTRAST_COLOR);
		textbackground(TEXT_COLOR);
		gotoxy(71, 4);
		printf(" Exclus%co de dados ", 198);
		textbackground(BACKGROUND_COLOR);
		gotoxy(20, 7);
		printf("Digite o c%cdigo do product a ser excluido (0 para sair): ", 162);

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
				fread(&product, sizeof(product), 1, fp);
				if(product.id == IDaux){
					generateVerticalTable(11);

					break;
				}
			};

			if(!confirmChoice(20, 24, 1)) break;

			rewind(fp);

			// Creates a temporary file to copy all the data except the one that will be deleted
			FILE *fp_tmp;
			fp_tmp = fopen("tmp.bin", "wb+");
			if (!fp_tmp) {
				printf("Não foi possível abrir o arquivo temporário.");
				fclose(fp_tmp);
			}

			int found = 0;
			while (fread(&product, sizeof(Product), 1, fp) == 1) {
				if (product.id == IDaux){
					textcolor(TEXT_COLOR); textbackground(LIGHTRED);
					gotoxy(20, 27);
					printf(" Cadastro exclu%cdo com sucesso! ", 161);
					gotoxy(20, 28);
					printf(" %d registro encontrado e deletado! ", ++found);
					textbackground(BACKGROUND_COLOR);
				} else {
					fwrite(&product, sizeof(Product), 1, fp_tmp);
				}
			};

			fclose(fp);
			fclose(fp_tmp);

			if (_access("estoque.bin", 0) != 0)
				perror("Erro ao acessar o arquivo!");
			else if (remove("estoque.bin") != 0)
				perror("Não foi possivel deletar o aquivo original!");

			if (_access("tmp.bin", 0) != 0)
				perror("Erro ao acessar o arquivo temporario!");
			else if (rename("tmp.bin", "estoque.bin") != 0)
				perror( "Erro renomeando arquivo!");

			textcolor(CONTRAST_COLOR);
		}
		fclose(fp);

		gotoxy(20,30);
		printf("Pressione uma tecla para retornar...");
		getch();
	};

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

void fillTableLine(int line)
{
	gotoxy(22, line); printf("%ld", product.id);
	gotoxy(33, line); printf("%.66s", product.name);
	gotoxy(102, line); printf("%.2f", product.price);
	gotoxy(123, line); printf("%ld", product.quantity);
	gotoxy(136, line); printf("%c", product.type);
}

void generateVerticalTable(int line)
{
	const int MAX_LINE_LENGTH = 97;

	int nameLength = strlen(product.name);
	int extraLines = (nameLength > MAX_LINE_LENGTH) ? 1 : 0;

	int x = 0;
	if(extraLines) x++;
	gotoxy(20,line);		printf ("+------------------------------------------------------------------------------------------------------------------------+");
	gotoxy(20,line+1);		printf ("|  ID                |                                                                                                   |");
	gotoxy(20,line+2);		printf ("+------------------------------------------------------------------------------------------------------------------------+");
	gotoxy(20,line+3);		printf ("|  Nome              |                                                                                                   |");
	gotoxy(20,line+3+x);	printf ("|");gotoxy(41, line+3+x);printf("|                                                                                                   |");
	gotoxy(20,line+4+x);	printf ("+------------------------------------------------------------------------------------------------------------------------+");
	gotoxy(20,line+5+x);	printf ("|  Pre%co Unit%crio    |                                                                                                   |", 135, 160);
	gotoxy(20,line+6+x);	printf ("+------------------------------------------------------------------------------------------------------------------------+");
	gotoxy(20,line+7+x);	printf ("|  Quantidade        |                                                                                                   |");
	gotoxy(20,line+8+x);	printf ("+------------------------------------------------------------------------------------------------------------------------+");
	gotoxy(20,line+9+x);	printf ("|  Tipo              |                                                                                                   |");
	gotoxy(20,line+10+x);	printf ("+------------------------------------------------------------------------------------------------------------------------+");

	gotoxy(43, line+1); printf("%ld", product.id);
	gotoxy(43, line+3); printf("%.*s", 97, product.name);
	if(extraLines){
		gotoxy(43, line+3+x); printf("%.*s", 97, product.name + nameLength-97);
	}
	gotoxy(43, line+5+x); printf("%.2f", product.price);
	gotoxy(43, line+7+x); printf("%ld", product.quantity);
	gotoxy(43, line+9+x); printf("%c", product.type);
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

void returningMenu(int linha,int coluna,int delay, bool menu){
	cursor(0);
	textbackground(LIGHTRED);
	textcolor(TEXT_COLOR);
	gotoxy(linha, coluna);
	if(menu)
		printf("Voltando ao menu...");
	else
		printf("Voltando...");
	Sleep(delay);
}

void openFile()
{
	if((fp = fopen("estoque.bin", "ab+")) == NULL){
		system("cls"); drawnBorder();
		textcolor(TEXT_COLOR);
		gotoxy(65, 16);
		printf("Erro na abertura do arquivo!");
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
	return 0;
}
