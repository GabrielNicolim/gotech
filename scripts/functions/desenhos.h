// Source file for drawing functions
// Diskette, CPU, GPU, RAM, Magnifier and Logo

// Colors and Chards
#define CONTRAST_COLOR 0
#define BORDER_COLOR 1
#define BACKGROUND_COLOR 3
#define LIGHTGRAY 7
#define LIGHTBLUE 9
#define LIGHTRED 12
#define TEXT_COLOR 15
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 33
#define BLOCK_CHAR 219

void gotoxy(int x, int y);
void textcolor(int newcolor);
void textbackground(int newcolor);

void drawnBorder()
{
	textbackground(BACKGROUND_COLOR);
	system("cls");

	textcolor(BORDER_COLOR);
	for (int i = 2; i <= SCREEN_HEIGHT; i++) // Left and right borders
    {
        gotoxy(9, i);
        printf("%c%c %*c%c", BLOCK_CHAR, BLOCK_CHAR, SCREEN_WIDTH - 18, BLOCK_CHAR, BLOCK_CHAR);
    }

	for (int i = 9; i <= SCREEN_WIDTH - 8; i++) // Top border
    {
        gotoxy(i, 2);
        printf("%c", BLOCK_CHAR);
    }

	for (int i = 9; i <= SCREEN_WIDTH - 8; i++) // Bottom border
    {
        gotoxy(i, SCREEN_HEIGHT);
        printf("%c", BLOCK_CHAR);
    }

	textcolor(TEXT_COLOR);
}

void drawnDiskette(int column, int line)
{
	// Line 1
	textcolor(CONTRAST_COLOR);
	textbackground(LIGHTBLUE);
	gotoxy(column, line);
	for (int i = 0; i < 20; i++) printf("%c", BLOCK_CHAR);

	// Line 2
	gotoxy(column, (line+1));
	printf("%c", BLOCK_CHAR);
	for(int i = 0; i < 18; i++) putchar(' ');
	printf("%c", BLOCK_CHAR);

	// Line 3
	gotoxy(column, (line+2));
	printf("%c", BLOCK_CHAR);
	for(int i = 0; i < 18; i++) putchar(' ');
	printf("%c", BLOCK_CHAR);

	//detalhes internos
	textbackground(LIGHTGRAY);
	gotoxy(column+3, line+1); printf("  %c%c          ",BLOCK_CHAR,BLOCK_CHAR);
	gotoxy(column+3, line+2); printf("  %c%c          ",BLOCK_CHAR,BLOCK_CHAR);

	// Line 4
	gotoxy(column, (line+3));
	printf("%c", BLOCK_CHAR);
	textbackground(LIGHTBLUE);
	for(int i = 0; i < 18; i++) putchar(' ');
	printf("%c", BLOCK_CHAR);

	// Line 5
	gotoxy(column, (line+4));
	printf("%c", BLOCK_CHAR);
	for(int i = 0; i < 18; i++) putchar(' ');
	printf("%c", BLOCK_CHAR);

	//Line 6 - rodelinha com tracin
	gotoxy(column, (line+5));
	printf("%c", BLOCK_CHAR);
	for(int i = 0; i < 18; i++)
	{
		if(i>6 && i <11)
		{
		textcolor(LIGHTGRAY);
		if(i == 9) textcolor(8);
		}
		else textcolor(LIGHTBLUE);
		putchar(BLOCK_CHAR);

	}
	textcolor(CONTRAST_COLOR);
	printf("%c", BLOCK_CHAR);

	//Line 7 - rodelinha
	gotoxy(column, (line+6));
	printf("%c", BLOCK_CHAR);
	for(int i = 0; i < 18; i++)
	{
		if(i>6 && i <11) textcolor(LIGHTGRAY);
		else textcolor(LIGHTBLUE);
		putchar(BLOCK_CHAR);

	}
	textcolor(CONTRAST_COLOR);
	printf("%c", BLOCK_CHAR);

	// Line 8
	gotoxy(column, (line+7));
	printf("%c", BLOCK_CHAR);
	textbackground(LIGHTBLUE);
	for(int i = 0; i < 18; i++) putchar(' ');
	printf("%c", BLOCK_CHAR);

	// Line 9
	gotoxy(column, (line+8));
	printf("%c", BLOCK_CHAR);
	for(int i = 0; i < 18; i++) putchar(' ');
	printf("%c", BLOCK_CHAR);

	// Line 10 => Borda de baixo
	gotoxy(column, (line+9));
	for(int i = 0; i < 20; i++) putchar(BLOCK_CHAR);
	textbackground(BACKGROUND_COLOR);

	textcolor(TEXT_COLOR);
}

void drawnLogo(int column, int line)
{
	textcolor(CONTRAST_COLOR);

	gotoxy(column - 2, line + 6); printf("%.*s", 58, "__________________________________________________________");

	// Line 1 do texto
	gotoxy(column+1,line);	printf("%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);				gotoxy(column+7,line);	printf("%c",187);
	gotoxy(column+10,line);	printf("%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);				gotoxy(column+16,line);	printf("%c",187);
	gotoxy(column+18,line);	printf("%c%c%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);	gotoxy(column+25,line);	printf("%c",187);
	gotoxy(column+27,line);	printf("%c%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+34,line);	printf("%c",187);
	gotoxy(column+38,line);	printf("%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);				gotoxy(column+44,line);	printf("%c",187);
	gotoxy(column+46,line);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);										gotoxy(column+48,line);	printf("%c",187);
	gotoxy(column+51,line);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);										gotoxy(column+53,line);	printf("%c",187);

	//line 2
	gotoxy(column,line+1);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+2,line+1);	printf("%c%c%c%c%c%c",201,205,205,205,205,188);
	gotoxy(column+9,line+1);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+11,line+1);	printf("%c%c%c%c",201,205,205,205);
	gotoxy(column+15,line+1);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+17,line+1);	printf("%c",187);
	gotoxy(column+21,line+1);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+18,line+1);	printf("%c%c%c",200,205,205);
	gotoxy(column+27,line+1);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+23,line+1);	printf("%c%c%c",201,205,188);
	gotoxy(column+37,line+1);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+29,line+1);	printf("%c%c%c%c%c%c",201,205,205,205,205,188);
	gotoxy(column+46,line+1);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+39,line+1);	printf("%c%c%c%c%c%c",201,205,205,205,205,188);
	gotoxy(column+51,line+1);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+48,line+1);	printf("%c",186);		gotoxy(column+53,line+1);	printf("%c",186);

	//line 3
	gotoxy(column,line+2);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);									gotoxy(column+2,line+2);	printf("%c",186);
	gotoxy(column+5,line+2);	printf("%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);							gotoxy(column+8,line+2);	printf("%c",187);
	gotoxy(column+9,line+2);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);									gotoxy(column+11,line+2);	printf("%c",186);
	gotoxy(column+15,line+2);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);									gotoxy(column+17,line+2);	printf("%c",186);
	gotoxy(column+21,line+2);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);									gotoxy(column+23,line+2);	printf("%c",186);
	gotoxy(column+27,line+2);	printf("%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);			gotoxy(column+33,line+2);	printf("%c",187);
	gotoxy(column+37,line+2);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);									gotoxy(column+39,line+2);	printf("%c",186);
	gotoxy(column+46,line+2);	printf("%c%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);	gotoxy(column+53,line+2);	printf("%c",186);

	//line 4
	gotoxy(column,line+3);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+2,line+3);	printf("%c",186);
	gotoxy(column+6,line+3);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+8,line+3);	printf("%c",186);
	gotoxy(column+9,line+3);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+11,line+3);	printf("%c",186);
	gotoxy(column+15,line+3);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+17,line+3);	printf("%c",186);
	gotoxy(column+21,line+3);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+23,line+3);	printf("%c",186);
	gotoxy(column+27,line+3);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+29,line+3);	printf("%c%c%c%c%c",201,205,205,205,188);
	gotoxy(column+37,line+3);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+39,line+3);	printf("%c",186);
	gotoxy(column+46,line+3);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+48,line+3);	printf("%c%c%c",201,205,205);
	gotoxy(column+51,line+3);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		gotoxy(column+53,line+3);	printf("%c",186);

	//line 5
	gotoxy(column+1,line+4);	printf("%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);			gotoxy(column,line+4);	printf("%c",200);
	gotoxy(column+10,line+4);	printf("%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);			gotoxy(column+7,line+4);	printf("%c%c%c",201,188,200);
	gotoxy(column+21,line+4);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);									gotoxy(column+16,line+4);	printf("%c%c",201,188);
	gotoxy(column+27,line+4);	printf("%c%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);	gotoxy(column+23,line+4);	printf("%c",186);
	gotoxy(column+38,line+4);	printf("%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);			gotoxy(column+34,line+4);	printf("%c",187);
	gotoxy(column+46,line+4);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);									gotoxy(column+37,line+4);	printf("%c",200);
	gotoxy(column+51,line+4);	printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);									gotoxy(column+44,line+4);	printf("%c",187);
	gotoxy(column+48,line+4);	printf("%c",186);										gotoxy(column+53,line+4);	printf("%c",186);

	// Line 6
	gotoxy(column+1,line+5); printf("%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 188);
	gotoxy(column+10,line+5); printf("%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 188);
	gotoxy(column+21,line+5); printf("%c%c%c", 200, 205, 188);
	gotoxy(column+27,line+5); printf("%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 188);
	gotoxy(column+38,line+5); printf("%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 188);
	gotoxy(column+46,line+5); printf("%c%c%c", 200, 205, 188);
	gotoxy(column+51,line+5); printf("%c%c%c", 200, 205, 188);
}

void drawnMagnifier(int column, int line)
{
	textcolor(CONTRAST_COLOR);
	textbackground(BACKGROUND_COLOR);
	// Line 1 - Black border
	gotoxy(column+4, line);
	printf("%c%c%c%c%c%c%c%c%c%c%c", 220, 220, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, 220, 220);
	// Line 2
	gotoxy(column+2, line+1); 	printf("%c%c%c%c", 220, BLOCK_CHAR, BLOCK_CHAR, 223);
	gotoxy(column+13, line+1); 	printf("%c%c%c%c", 223, BLOCK_CHAR, BLOCK_CHAR, 220);
	// Line 3
	gotoxy(column+1, line+2); 	printf("%c%c", BLOCK_CHAR, 223);
	gotoxy(column+16, line+2); 	printf("%c%c", 223, BLOCK_CHAR);
	// Line 4
	gotoxy(column, line+3);  		printf("%c%c", BLOCK_CHAR, 223);
	gotoxy(column+17, line+3); 	printf("%c%c", 223, BLOCK_CHAR);
	// Line 5
	gotoxy(column, line+4);	 	printf("%c", BLOCK_CHAR);
	gotoxy(column+18, line+4);	printf("%c", BLOCK_CHAR);
	// Line 6
	gotoxy(column, line+5);  		printf("%c%c", BLOCK_CHAR, 220);
	gotoxy(column+17, line+5);	printf("%c%c", 220, BLOCK_CHAR);
	// Line 7
	gotoxy(column+1, line+6);		printf("%c%c", BLOCK_CHAR, 220);
	gotoxy(column+16, line+6);	printf("%c%c", 220, BLOCK_CHAR);
	// Line 8
	gotoxy(column+2, line+7); 	printf("%c%c%c%c", 223, BLOCK_CHAR, BLOCK_CHAR, 220);
	gotoxy(column+13, line+7); 	printf("%c%c%c%c", 220, BLOCK_CHAR, BLOCK_CHAR, 223);
	// Line 9
	gotoxy(column+4, line+8); 	printf("%c%c%c%c%c%c%c%c%c%c%c",223 ,223, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, 223, 223);

	// Shine effect
	textcolor(TEXT_COLOR);
	gotoxy(column+3, line+4); printf("%c", BLOCK_CHAR);
	gotoxy(column+4, line+5); printf("%c%c%c", BLOCK_CHAR, BLOCK_CHAR, 220);
	gotoxy(column+7, line+6); printf("%c%c", BLOCK_CHAR, 220);

	// Handle
	textcolor(TEXT_COLOR);
	gotoxy(column+18, line+6); printf("%c%c", BLOCK_CHAR,220);
	gotoxy(column+16, line+7); printf("%c%c%c%c%c%c", BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, 220);
	gotoxy(column+15, line+8); printf("%c%c%c%c%c%c%c%c%c", 223, 223, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR,220);
	gotoxy(column+18, line+9); printf("%c%c%c%c%c%c%c%c", 223, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, 220);
	gotoxy(column+20, line+10);printf("%c%c%c%c%c%c%c%c", 223, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, 220);
	gotoxy(column+22, line+11);printf("%c%c%c%c%c%c%c", 223, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR);
	gotoxy(column+24, line+12);printf("%c%c%c%c%c%c", 223, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR,223);
}

void drawnCPU(int column, int line)
{
	//Quadrados básicos:
	textbackground(6);
	for(int i = 1; i < 10; i++){
		gotoxy(column+1, line+i); printf("                    ");
	}

	textbackground(CONTRAST_COLOR);
	for(int i = 0; i < 9; i++){
		gotoxy(column, line+i); printf("                    ");
	}

	textbackground(LIGHTGRAY);
	for(int i = 1; i < 8; i++){
		gotoxy(column+1, line+i); printf("                  ");
	}

	//escrita C P U
	textcolor(CONTRAST_COLOR);
	gotoxy(column, line);
	for(int i = 0; i < 20; i++) putchar(BLOCK_CHAR);

	// Linha 2  - tracinho
	gotoxy(column, (line+1));

	printf("%c", BLOCK_CHAR);
	textcolor(LIGHTGRAY);
	for(int i = 0; i < 18; i++) putchar(BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);
	printf("%c", BLOCK_CHAR);
	textcolor(6);
	printf("%c", BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);

	// Linha 3  - tracinho
	gotoxy(column, (line+2));

	printf("%c", BLOCK_CHAR);
	textcolor(LIGHTGRAY);
	for(int i = 0; i < 18; i++) putchar(BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);
	printf("%c", BLOCK_CHAR);
	textcolor(6);
	printf("%c", BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);

	// Linha 4

	gotoxy(column, (line+3));

	printf("%c", BLOCK_CHAR);
	textcolor(LIGHTGRAY);
	for(int i = 0; i < 18; i++) putchar(BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);
	printf("%c", BLOCK_CHAR);
	textcolor(6);
	printf("%c", BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);

	// Linha 5

	gotoxy(column, (line+4));

	printf("%c", BLOCK_CHAR);
	textcolor(LIGHTGRAY);
	for(int i = 0; i < 18; i++) putchar(BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);
	printf("%c", BLOCK_CHAR);
	textcolor(6);
	printf("%c", BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);

	//Linha 6 - rodelinha com tracin

	gotoxy(column, (line+5));

	printf("%c", BLOCK_CHAR);
	textcolor(LIGHTGRAY);
	for(int i = 0; i < 18; i++) putchar(BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);
	printf("%c", BLOCK_CHAR);
	textcolor(6);
	printf("%c", BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);

	//Linha 7 - rodelinha

	gotoxy(column, (line+6));

	printf("%c", BLOCK_CHAR);
	textcolor(LIGHTGRAY);
	for(int i = 0; i < 18; i++) putchar(BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);
	printf("%c", BLOCK_CHAR);
	textcolor(6);
	printf("%c", BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);

	// Linha 8

	gotoxy(column, (line+7));

	printf("%c", BLOCK_CHAR);
	textcolor(LIGHTGRAY);
	for(int i = 0; i < 18; i++) putchar(BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);
	printf("%c", BLOCK_CHAR);
	textcolor(6);
	printf("%c", BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);

	// Linha 9
	textcolor(CONTRAST_COLOR);
	gotoxy(column, (line+8));
	for(int i = 0; i < 20; i++) putchar(BLOCK_CHAR);
	textcolor(6);
	printf("%c", BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);

	// Linha 10 => Borda de baixo
	textcolor(6);
	gotoxy((column+1), (line+9));
	for(int i = 0; i < 20; i++) putchar(BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);

	//escrever cpu
	gotoxy((column+3), (line+2)); printf("%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);
	gotoxy((column+3), (line+3)); printf("%c",BLOCK_CHAR);
	gotoxy((column+3), (line+4)); printf("%c",BLOCK_CHAR);      //etra C
	gotoxy((column+3), (line+5)); printf("%c",BLOCK_CHAR);
	gotoxy((column+3), (line+6)); printf("%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);

	gotoxy((column+8), (line+2)); printf("%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);
	gotoxy((column+8), (line+3)); printf("%c",BLOCK_CHAR);		//Letra P
	gotoxy((column+11), (line+3)); printf("%c",BLOCK_CHAR);
	gotoxy((column+8), (line+4)); printf("%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);
	gotoxy((column+8), (line+5)); printf("%c",BLOCK_CHAR);
	gotoxy((column+8), (line+6)); printf("%c",BLOCK_CHAR);

	gotoxy((column+13), (line+2)); printf("%c",BLOCK_CHAR);
	gotoxy((column+16), (line+2)); printf("%c",BLOCK_CHAR);
	gotoxy((column+13), (line+3)); printf("%c",BLOCK_CHAR);
	gotoxy((column+16), (line+3)); printf("%c",BLOCK_CHAR);		//Letra U
	gotoxy((column+13), (line+4)); printf("%c",BLOCK_CHAR);
	gotoxy((column+16), (line+4)); printf("%c",BLOCK_CHAR);
	gotoxy((column+13), (line+5)); printf("%c",BLOCK_CHAR);
	gotoxy((column+16), (line+5)); printf("%c",BLOCK_CHAR);
	gotoxy((column+13), (line+6)); printf("%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);

	gotoxy((column), (line+9)); //só pro end do programa não quebrar as coisas
	textbackground(BACKGROUND_COLOR);
}

void drawnGPU(int column, int line)
{
    // Line 1 - top border
    gotoxy(column, line);
    textcolor(BLOCK_CHAR);
    printf("%c%c%c", BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR);
    textcolor(CONTRAST_COLOR);
    for(int i = 0; i < 35; i++) printf("%c", BLOCK_CHAR);

    // Line 2 - cooler start
    gotoxy(column, (line+1));
    textcolor(BLOCK_CHAR);
    printf("  %c", BLOCK_CHAR);
    for(int i = 0; i < 35; i++)
    {
        textcolor(CONTRAST_COLOR);
        if( i>14 && i<25)
            textcolor(BLOCK_CHAR);
        printf("%c", BLOCK_CHAR);
    }

    //fundo principal
    textbackground(CONTRAST_COLOR);
    for(int i = 0; i < 9; i++){
        gotoxy(column+3,line+i); printf("%.*s", 35, "                                   ");
    }

    // sticker
    textbackground(2);
    gotoxy(column+3,line+2);	printf("%.*s", 35, "                                   ");
    gotoxy(column+3,line+6);	printf("%.*s", 35, "                                   ");
    textbackground(10);
    gotoxy(column+3,line+3);	printf("%.*s", 35, "                                   ");
    gotoxy(column+3,line+4);	printf("%.*s", 35, "                                   ");
    gotoxy(column+3,line+5);	printf("%.*s", 35, "                                   ");

    textbackground(BLOCK_CHAR);
    textcolor(CONTRAST_COLOR);
    // Line 2  - começo do cooler
    gotoxy(column+18, line+1); printf("   %c      ", BLOCK_CHAR);

    // Draw the horizontal lines
    for (int i = 2; i < 8; i++)
    {
        gotoxy(column, line + i);
        textcolor(BLOCK_CHAR);
        printf("  %c", BLOCK_CHAR);

        for (int j = 0; j < 35; j++)
        {
            textcolor(10);
            if (i == 5 && j > 10 && j < 29)
                textcolor(BLOCK_CHAR);
            else if ((i == 3 || i == 4) && j > 11 && j < 28)
                textcolor(BLOCK_CHAR);
            else if ((i == 2 || i == 6) && j > 12 && j < 27)
                textcolor(BLOCK_CHAR);
            printf("%c", BLOCK_CHAR);
        }
    }

    // Line 8 - final do cooler
    gotoxy(column, (line+7));

    textcolor(BLOCK_CHAR);
    printf("  %c", BLOCK_CHAR);
    for(int i = 0; i < 35; i++)
    {
        textcolor(CONTRAST_COLOR);
        if( i>14 && i<25)
            textcolor(BLOCK_CHAR);
        printf("%c", BLOCK_CHAR);
    }

    // Line 9
    gotoxy(column, (line+8));

    textcolor(BLOCK_CHAR);
    printf("  %c", BLOCK_CHAR);
    textcolor(CONTRAST_COLOR);
    for(int i = 0; i < 35; i++) printf("%c", BLOCK_CHAR);

    // Line 10 => Borda de baixo
    gotoxy(column, (line+9));

    textcolor(BLOCK_CHAR);
    printf("  %c", BLOCK_CHAR);
    textcolor(14);
    for(int i = 0; i < 35; i++)
    {
        if(i==4 || i == 18)
        {
            textcolor(CONTRAST_COLOR);
            printf("%c", BLOCK_CHAR);
            textcolor(14);
        }
        if(i>3 && i<18)
            printf("%c", BLOCK_CHAR);
        else
            printf(" ");
    }
    textcolor(CONTRAST_COLOR);
}

void drawnRAM(const int column, const int line)
{
    // Line 1 => Borda de cima
    gotoxy(column, line);
    textcolor(CONTRAST_COLOR);
    printf("%c", BLOCK_CHAR);

    textcolor(2);
    for(int i = 0; i < 41; i++) printf("%c", BLOCK_CHAR);

    textcolor(CONTRAST_COLOR);
    printf("%c", BLOCK_CHAR);

    // Line 2  - tracinho
    gotoxy(column, (line+1));
    textcolor(CONTRAST_COLOR);
    printf(" %c", BLOCK_CHAR);

    for(int i = 0; i < 33; i++)
    {
        textcolor(2);
        if((i+1)%5==0)
        {
            textcolor(LIGHTGRAY);
            printf("%c", BLOCK_CHAR);
        }
        printf("%c", BLOCK_CHAR);
    }

    textcolor(CONTRAST_COLOR);
    printf("%c ", BLOCK_CHAR);

    // Line 3  - tracinho
    gotoxy(column, (line+2));
    textcolor(CONTRAST_COLOR);
    printf("%c", BLOCK_CHAR);

    textcolor(2);
    printf("%c", BLOCK_CHAR);
    for(int i = 0; i < 33; i++)
    {
        textcolor(2);
        if((i+1)%5==0)
        {
            textcolor(LIGHTGRAY);
            printf("%c", BLOCK_CHAR);
        }
        printf("%c", BLOCK_CHAR);
    }
    printf("%c", BLOCK_CHAR);
    textcolor(CONTRAST_COLOR);
    printf("%c", BLOCK_CHAR);

    // Line 4
    gotoxy(column, (line+3));
    textcolor(CONTRAST_COLOR);
    printf(" %c", BLOCK_CHAR);

    textcolor(2);
    for(int i = 0; i < 39; i++) printf("%c", BLOCK_CHAR);

    textcolor(CONTRAST_COLOR);
    printf("%c ", BLOCK_CHAR);

    // Line 5
    gotoxy(column, (line+4));
    textcolor(CONTRAST_COLOR);
    printf("%c", BLOCK_CHAR);

    for(int i = 0; i < 41; i++)
    {
        textcolor(2);
        if((i+1)%2==0)
            textcolor(14);
        printf("%c", BLOCK_CHAR);
    }

    textcolor(CONTRAST_COLOR);
    printf("%c", BLOCK_CHAR);

    //modulos de memória
    textcolor(LIGHTGRAY);
    gotoxy(column+6,line+1); printf("%c%c    %c%c    %c%c    %c%c    %c%c    %c%c", BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR);
    gotoxy(column+6,line+2); printf("%c%c    %c%c    %c%c    %c%c    %c%c    %c%c", BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR);

    //e contatos
    textcolor(14);
    gotoxy(column+2,line+4); printf("%c %c %c %c %c %c %c %c   %c %c %c %c %c %c %c %c %c %c %c %c", BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR, BLOCK_CHAR);
}

void drawnMobo(int column, int line)
{
	// Construir o PCB bruto
	gotoxy(column, line);
	textcolor(CONTRAST_COLOR);
	for(int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 10; j++)
		{
		gotoxy((column+i), (line+j));
		putchar(BLOCK_CHAR);
		}
	}

	//Construir os detalhes
	textcolor(LIGHTGRAY);
	gotoxy(column, (line+1)); printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);
	gotoxy(column, (line+2)); printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);
	gotoxy(column, (line+3)); printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);		//IO traseiro
	gotoxy(column, (line+4)); printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);
	gotoxy(column, (line+5)); printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);

	textcolor(LIGHTGRAY);
	gotoxy((column+6), (line+2)); printf("%c",BLOCK_CHAR);
	gotoxy((column+6), (line+3)); printf("%c",BLOCK_CHAR);
	gotoxy((column+9), (line+2)); printf("%c",BLOCK_CHAR);		//socket do drawnCPU
	gotoxy((column+9), (line+3)); printf("%c",BLOCK_CHAR);
	textcolor(14);
	gotoxy((column+7), (line+2)); printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);
	gotoxy((column+7), (line+3)); printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);

	textcolor(2);
	gotoxy((column+13), (line+1)); printf("%c",BLOCK_CHAR);
	gotoxy((column+13), (line+2)); printf("%c",BLOCK_CHAR);
	gotoxy((column+13), (line+3)); printf("%c",BLOCK_CHAR);    //slots de drawnRAM e etc
	gotoxy((column+13), (line+4)); printf("%c",BLOCK_CHAR);
	gotoxy((column+15), (line+1)); printf("%c",BLOCK_CHAR);
	gotoxy((column+15), (line+2)); printf("%c",BLOCK_CHAR);
	gotoxy((column+15), (line+3)); printf("%c",BLOCK_CHAR);
	gotoxy((column+15), (line+4)); printf("%c",BLOCK_CHAR);
	gotoxy((column+18), (line+1)); printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);

	textcolor(8);
	gotoxy((column+18), (line+3)); printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);    //conectores 24 pinos e etc
	gotoxy((column+18), (line+4)); printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);

	gotoxy((column+4), (line+6)); printf("%c%c%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);  //slots pci-e
	gotoxy((column+4), (line+8)); printf("%c%c%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);

	textcolor(LIGHTRED);
	gotoxy((column+15), (line+6)); printf("%c%c",BLOCK_CHAR,BLOCK_CHAR); //dissipador do chipset
	gotoxy((column+15), (line+7)); printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);

	textcolor(TEXT_COLOR);
	gotoxy((column+14), (line+9)); printf("%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);
	textcolor(CONTRAST_COLOR);

	gotoxy((column+10), (line+10));
}

void drawnHDD(int column, int line)
{
	textcolor(CONTRAST_COLOR);
	for(int i = 0; i < 21; i++)
	{
		for(int j = 0; j < 12; j++)
		{
		gotoxy((column+i), (line+j));
		putchar(BLOCK_CHAR);
		}
	}
	textbackground(CONTRAST_COLOR);
	textcolor(LIGHTGRAY);
	gotoxy(column+6,line+1);		printf("%c%c%c%c%c%c%c%c%c",220,220,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,220,220);
	gotoxy(column+4,line+2);		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",220,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,220);
	gotoxy(column+4,line+3);		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);		//disco magnético
	gotoxy(column+4,line+4);		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);		//e parafusos
	gotoxy(column+5,line+5);		printf("%c%c%c%c%c%c%c%c%c%c%c",223,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,223);
	gotoxy(column+8,line+6);		printf("%c%c%c%c%c",223,223,223,223,223);
	gotoxy(column+1,line);		printf("%c",220);	gotoxy(column+1,line+11);		printf("%c",223);
	gotoxy(column+1,line+5);		printf("%c",223);	gotoxy(column+19,line+5);		printf("%c",223);
	gotoxy(column+19,line);		printf("%c",220);	gotoxy(column+19,line+11);	printf("%c",223);


	textcolor(2);
	gotoxy(column+10,line+7);		printf("%c%c%c%c%c%c%c%c",220,220,220,220,220,220,220,220);
	gotoxy(column+10,line+8);		printf("%c%c%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR); // pcb
	gotoxy(column+12,line+9);		printf("%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);
	gotoxy(column+13,line+10);	printf("%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);
	textcolor(8);
	gotoxy(column+14,line+8);		printf("%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);
	gotoxy(column+15,line+9);		printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);

	textcolor(LIGHTGRAY);
	gotoxy(column+3,line+6);		printf("%c",220);
	gotoxy(column+3,line+7);		printf("%c%c%c",BLOCK_CHAR,BLOCK_CHAR,220);										//baia para a agulha
	gotoxy(column+3,line+8);		printf("%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,220);
	gotoxy(column+3,line+9);		printf("%c%c%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,220,220);
	gotoxy(column+3,line+10);		printf("%c%c%c%c%c%c%c%c%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,220,220);

	textcolor(8);
	textbackground(LIGHTGRAY);
	gotoxy(column+9,line+5);		printf("%c",BLOCK_CHAR);
	gotoxy(column+8,line+6);		printf("%c%c",BLOCK_CHAR,BLOCK_CHAR);
	gotoxy(column+7,line+7);		printf("%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);			//agulha
	gotoxy(column+6,line+8);		printf("%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);
	gotoxy(column+5,line+9);		printf("%c%c%c%c",BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR,BLOCK_CHAR);
	gotoxy(column+6,line+10);		printf("%c%c",223,223);

	textcolor(CONTRAST_COLOR);
	gotoxy(column+9,line+3);		printf("%c%c%c",220,BLOCK_CHAR,220);		///motor para o disco
	gotoxy(column+10,line+4);		printf("%c",223);

	textbackground(BACKGROUND_COLOR);
}
