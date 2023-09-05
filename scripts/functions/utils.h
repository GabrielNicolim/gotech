#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> // Include this header file to define the boolean type
#include <ctype.h>

#ifndef UTILS_H
#define UTILS_H

#define MAX_NAME_LENGTH 194
#define MAX_PRODUCT_QUANTITY 9999999

typedef struct Product
{
	long id;
	char name[MAX_NAME_LENGTH];
	long quantity;
	char type;
	double price;
	bool excluido;
} Product;

// conio.c functions
void textcolor(int newcolor);
void textbackground(int newcolor);
void gotoxy(int x, int y);
void cursor (int x);
void clreol(int x);

// Program flow
void loading();
void start();

// Data interaction
void openFile();
int openFileEdit();
void queryAll();
void queryID();
void queryName();
void queryType();
void deleteData();
void generateTable(int column);
void generateVerticalTable(int line, Product product);
void fillTableLine(int line, Product product);
void displaySearchResults(Product** products, int numProdutos);
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
void closeProgram();

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

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL 0
#endif

char* stristr(const char* haystack, const char* needle)
{
    //char* nullptr = NULL;
    const char* pHaystack = haystack;
    const char* pNeedle = needle;
    const char* result = (*pNeedle == 0) ? haystack : NULL;

    while (*pHaystack != 0 && *pNeedle != 0)
    {
        if (tolower((unsigned char)(*pHaystack)) == tolower((unsigned char)(*pNeedle)))
        {
            if (result == NULL)
            {
                result = pHaystack;
            }

            pNeedle++;
        }
        else
        {
            pNeedle = needle;
            if (result != NULL)
            {
                pHaystack = result + 1;
            }

            if (tolower((unsigned char)(*pHaystack)) == tolower((unsigned char)(*pNeedle)))
            {
                result = pHaystack;
                pNeedle++;
            }
            else
            {
                result = NULL;
            }
        }

        pHaystack++;
    }

    return (*pNeedle == 0) ? (char *)(result) : NULL;
}

#ifdef __cplusplus
}
#endif

bool isNumeric(const char* str) {
    int size = strlen(str);
    for (int i = 0; i < size; i++) {
        if (str[i] == ',') {
            continue;
        }
        if (!isdigit(str[i]) && str[i] != '.') {
            return false;
        }
    }
    return true;
}

double convertToDouble(const char* str) {
    char* endptr;
    double num = strtod(str, &endptr);
    if (*endptr != '\0') {
        num = -1;
    }
    return num;
}

void cursor (int x)
{
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

// Clear the line
void clreol(int x)
{
	for(int i=0; i < x; i++)
        printf(" ");
	for(int i=0; i < x; i++)
        printf("\b");
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x - 1;
	coord.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

#endif /* UTILS_H */