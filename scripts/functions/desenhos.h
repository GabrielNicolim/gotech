//Arquivo fonte para funções de desenhos do programa como a borda e os icones de:
// - Disquete, Logo, Lupa, CPU, GPU, RAM, Mobo, HDD	

// Definição de cores 
#define cor_fundo 3
#define cor_borda 1
#define cor_texto 15
#define cor_destaque 0
#define RED 12

//Lembrar esse arquivo das funções conio
void gotoxy(int x, int y);
void textcolor(int newcolor);
void textbackground(int newcolor);

//Desenhos vão ficar todos aqui

void borda() 
{
	int cf = cor_fundo, cb = cor_borda, lc = 160; // (cor de fundo, cor da borda, limite de coluna)
	
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
		gotoxy(152,i);printf("%c",219);
		gotoxy(151,i);printf("%c",219);
	}
	
}

void disquete(int coluna, int linha)
{
	// Linha 1 => Borda de cima
	textcolor(0);
	gotoxy(coluna, linha); 
	for(int i = 0; i < 20; i++) putchar(219);
	
	// Linha 2  - tracinho
	gotoxy(coluna, (linha+1));
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
	gotoxy(coluna, (linha+2));
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
	
	gotoxy(coluna, (linha+3));
	
	printf("%c", 219);
	textcolor(9);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	
	// Linha 5
	
	gotoxy(coluna, (linha+4));
	printf("%c", 219);
	textcolor(9);

	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	
	//Linha 6 - rodelinha com tracin
	
	gotoxy(coluna, (linha+5));
	
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
	
	gotoxy(coluna, (linha+6));
	
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
	
	gotoxy(coluna, (linha+7));
	
	printf("%c", 219);
	textcolor(9);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	
	// Linha 9
	
	gotoxy(coluna, (linha+8));
	
	printf("%c", 219);
	textcolor(9);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	
	// Linha 10 => Borda de baixo
	textcolor(0);
	gotoxy(coluna, (linha+9)); 
	for(int i = 0; i < 20; i++) putchar(219);
	
}

void logo(int coluna, int linha)
{
	textcolor(0);
	
	gotoxy(coluna - 2, linha + 6); for(int i = 0; i <= 58; i++) printf("_");
		
	// Linha 1 do texto
	gotoxy(coluna+1,linha);	printf("%c%c%c%c%c%c",219,219,219,219,219,219);				gotoxy(coluna+7,linha);	printf("%c",187);
	gotoxy(coluna+10,linha);	printf("%c%c%c%c%c%c",219,219,219,219,219,219);				gotoxy(coluna+16,linha);	printf("%c",187);	
	gotoxy(coluna+18,linha);	printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);	gotoxy(coluna+25,linha);	printf("%c",187);
	gotoxy(coluna+27,linha);	printf("%c%c%c%c%c%c%c",219,219,219,219,219,219,219);		gotoxy(coluna+34,linha);	printf("%c",187);
	gotoxy(coluna+38,linha);	printf("%c%c%c%c%c%c",219,219,219,219,219,219);				gotoxy(coluna+44,linha);	printf("%c",187);
	gotoxy(coluna+46,linha);	printf("%c%c",219,219);										gotoxy(coluna+48,linha);	printf("%c",187);
	gotoxy(coluna+51,linha);	printf("%c%c",219,219);										gotoxy(coluna+53,linha);	printf("%c",187);
	
	//linha 2
	gotoxy(coluna,linha+1);	printf("%c%c",219,219);		gotoxy(coluna+2,linha+1);	printf("%c%c%c%c%c%c",201,205,205,205,205,188);
	gotoxy(coluna+9,linha+1);	printf("%c%c",219,219);		gotoxy(coluna+11,linha+1);	printf("%c%c%c%c",201,205,205,205);
	gotoxy(coluna+15,linha+1);	printf("%c%c",219,219);		gotoxy(coluna+17,linha+1);	printf("%c",187);
	gotoxy(coluna+21,linha+1);	printf("%c%c",219,219);		gotoxy(coluna+18,linha+1);	printf("%c%c%c",200,205,205);
	gotoxy(coluna+27,linha+1);	printf("%c%c",219,219);		gotoxy(coluna+23,linha+1);	printf("%c%c%c",201,205,188);
	gotoxy(coluna+37,linha+1);	printf("%c%c",219,219);		gotoxy(coluna+29,linha+1);	printf("%c%c%c%c%c%c",201,205,205,205,205,188);
	gotoxy(coluna+46,linha+1);	printf("%c%c",219,219);		gotoxy(coluna+39,linha+1);	printf("%c%c%c%c%c%c",201,205,205,205,205,188);
	gotoxy(coluna+51,linha+1);	printf("%c%c",219,219);		gotoxy(coluna+48,linha+1);	printf("%c",186);		gotoxy(coluna+53,linha+1);	printf("%c",186);
		
	//linha 3
	gotoxy(coluna,linha+2);	printf("%c%c",219,219);									gotoxy(coluna+2,linha+2);	printf("%c",186);
	gotoxy(coluna+5,linha+2);	printf("%c%c%c",219,219,219);							gotoxy(coluna+8,linha+2);	printf("%c",187);
	gotoxy(coluna+9,linha+2);	printf("%c%c",219,219);									gotoxy(coluna+11,linha+2);	printf("%c",186);
	gotoxy(coluna+15,linha+2);	printf("%c%c",219,219);									gotoxy(coluna+17,linha+2);	printf("%c",186);
	gotoxy(coluna+21,linha+2);	printf("%c%c",219,219);									gotoxy(coluna+23,linha+2);	printf("%c",186);
	gotoxy(coluna+27,linha+2);	printf("%c%c%c%c%c%c",219,219,219,219,219,219);			gotoxy(coluna+33,linha+2);	printf("%c",187);
	gotoxy(coluna+37,linha+2);	printf("%c%c",219,219);									gotoxy(coluna+39,linha+2);	printf("%c",186);
	gotoxy(coluna+46,linha+2);	printf("%c%c%c%c%c%c%c",219,219,219,219,219,219,219);	gotoxy(coluna+53,linha+2);	printf("%c",186);
	
	//linha 4
	gotoxy(coluna,linha+3);	printf("%c%c",219,219);		gotoxy(coluna+2,linha+3);	printf("%c",186);
	gotoxy(coluna+6,linha+3);	printf("%c%c",219,219);		gotoxy(coluna+8,linha+3);	printf("%c",186);
	gotoxy(coluna+9,linha+3);	printf("%c%c",219,219);		gotoxy(coluna+11,linha+3);	printf("%c",186);
	gotoxy(coluna+15,linha+3);	printf("%c%c",219,219);		gotoxy(coluna+17,linha+3);	printf("%c",186);
	gotoxy(coluna+21,linha+3);	printf("%c%c",219,219);		gotoxy(coluna+23,linha+3);	printf("%c",186);
	gotoxy(coluna+27,linha+3);	printf("%c%c",219,219);		gotoxy(coluna+29,linha+3);	printf("%c%c%c%c%c",201,205,205,205,188);
	gotoxy(coluna+37,linha+3);	printf("%c%c",219,219);		gotoxy(coluna+39,linha+3);	printf("%c",186);
	gotoxy(coluna+46,linha+3);	printf("%c%c",219,219);		gotoxy(coluna+48,linha+3);	printf("%c%c%c",201,205,205);
	gotoxy(coluna+51,linha+3);	printf("%c%c",219,219);		gotoxy(coluna+53,linha+3);	printf("%c",186);
		
	//linha 5
	gotoxy(coluna+1,linha+4);	printf("%c%c%c%c%c%c",219,219,219,219,219,219);			gotoxy(coluna,linha+4);	printf("%c",200);
	gotoxy(coluna+10,linha+4);	printf("%c%c%c%c%c%c",219,219,219,219,219,219);			gotoxy(coluna+7,linha+4);	printf("%c%c%c",201,188,200);
	gotoxy(coluna+21,linha+4);	printf("%c%c",219,219);									gotoxy(coluna+16,linha+4);	printf("%c%c",201,188);
	gotoxy(coluna+27,linha+4);	printf("%c%c%c%c%c%c%c",219,219,219,219,219,219,219);	gotoxy(coluna+23,linha+4);	printf("%c",186);
	gotoxy(coluna+38,linha+4);	printf("%c%c%c%c%c%c",219,219,219,219,219,219);			gotoxy(coluna+34,linha+4);	printf("%c",187);
	gotoxy(coluna+46,linha+4);	printf("%c%c",219,219);									gotoxy(coluna+37,linha+4);	printf("%c",200);
	gotoxy(coluna+51,linha+4);	printf("%c%c",219,219);									gotoxy(coluna+44,linha+4);	printf("%c",187);
	gotoxy(coluna+48,linha+4);	printf("%c",186);										gotoxy(coluna+53,linha+4);	printf("%c",186);
	
	//linha 6
		
	gotoxy(coluna+1,linha+5);	printf("%c%c%c%c%c%c%c",200,205,205,205,205,205,188);
	gotoxy(coluna+10,linha+5);	printf("%c%c%c%c%c%c%c",200,205,205,205,205,205,188);
	gotoxy(coluna+21,linha+5);	printf("%c%c%c",200,205,188);
	gotoxy(coluna+27,linha+5);	printf("%c%c%c%c%c%c%c%c",200,205,205,205,205,205,205,188);
	gotoxy(coluna+38,linha+5);	printf("%c%c%c%c%c%c%c",200,205,205,205,205,205,188);
	gotoxy(coluna+46,linha+5);	printf("%c%c%c",200,205,188);
	gotoxy(coluna+51,linha+5);	printf("%c%c%c",200,205,188);
}

void lupa(int coluna, int linha)
{	
	// Linha 1 - Borda Preta
	textcolor(0);
	// Linha 1 - Borda Preta
	gotoxy(coluna+4, linha); 		printf("%c%c%c%c%c%c%c%c%c%c%c",220 ,220, 219, 219, 219, 219, 219, 219, 219, 220, 220);	
	// Linha 2  
	gotoxy(coluna+2, linha+1); 	printf("%c%c%c%c", 220, 219, 219, 223);
	gotoxy(coluna+13, linha+1); 	printf("%c%c%c%c", 223, 219, 219, 220);
	//linha 3
	gotoxy(coluna+1, linha+2); 	printf("%c%c", 219, 223);
	gotoxy(coluna+16, linha+2); 	printf("%c%c", 223, 219);	
	//linha 4
	gotoxy(coluna, linha+3);  		printf("%c%c", 219, 223);
	gotoxy(coluna+17, linha+3); 	printf("%c%c", 223, 219);	
	//linha 5
	gotoxy(coluna, linha+4);	 	printf("%c", 219);
	gotoxy(coluna+18, linha+4);	printf("%c", 219);	
	//linha 6
	gotoxy(coluna, linha+5);  		printf("%c%c", 219, 220);
	gotoxy(coluna+17, linha+5);	printf("%c%c", 220, 219);	
	//linha 7
	gotoxy(coluna+1, linha+6);		printf("%c%c", 219, 220);
	gotoxy(coluna+16, linha+6);	printf("%c%c", 220, 219);	
	// Linha 8  
	gotoxy(coluna+2, linha+7); 	printf("%c%c%c%c", 223, 219, 219, 220);
	gotoxy(coluna+13, linha+7); 	printf("%c%c%c%c", 220, 219, 219, 223);
	// Linha 9 
	gotoxy(coluna+4, linha+8); 	printf("%c%c%c%c%c%c%c%c%c%c%c",223 ,223, 219, 219, 219, 219, 219, 219, 219, 223, 223);		
	
	//brilhinho
	textcolor(15);
	gotoxy(coluna+3, linha+4); printf("%c", 219);
	gotoxy(coluna+4, linha+5); printf("%c%c%c", 219, 219, 220);
	gotoxy(coluna+7, linha+6); printf("%c%c", 219, 220);
	
	//cabo
	textcolor(15);
	gotoxy(coluna+18, linha+6); printf("%c%c", 219,220);
	gotoxy(coluna+16, linha+7); printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 220);
	gotoxy(coluna+15, linha+8); printf("%c%c%c%c%c%c%c%c%c", 223, 223, 219, 219, 219, 219, 219, 219,220);
	gotoxy(coluna+18, linha+9); printf("%c%c%c%c%c%c%c%c", 223, 219, 219, 219, 219, 219, 219, 220);			//cabo
	gotoxy(coluna+20, linha+10);printf("%c%c%c%c%c%c%c%c", 223, 219, 219, 219, 219, 219, 219, 220);
	gotoxy(coluna+22, linha+11);printf("%c%c%c%c%c%c%c", 223, 219, 219, 219, 219, 219, 219);
	gotoxy(coluna+24, linha+12);printf("%c%c%c%c%c%c", 223, 219, 219, 219, 219,223);
	
	// Acabou :D
}

void cpu(int coluna, int linha)
{	
	// Linha 1 => Borda de cima
	textcolor(0);
	gotoxy(coluna, linha); 
	for(int i = 0; i < 20; i++) putchar(219);
	
	// Linha 2  - tracinho
	gotoxy(coluna, (linha+1));

	printf("%c", 219);
	textcolor(7);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	textcolor(6);
	printf("%c", 219);
	textcolor(0);
	
	// Linha 3  - tracinho
	gotoxy(coluna, (linha+2));
	
	printf("%c", 219);
	textcolor(7);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	textcolor(6);
	printf("%c", 219);
	textcolor(0);
	
	// Linha 4
	
	gotoxy(coluna, (linha+3));
	
	printf("%c", 219);
	textcolor(7);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	textcolor(6);
	printf("%c", 219);
	textcolor(0);
	
	// Linha 5
	
	gotoxy(coluna, (linha+4));
	
	printf("%c", 219);
	textcolor(7);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	textcolor(6);
	printf("%c", 219);
	textcolor(0);
	
	//Linha 6 - rodelinha com tracin
	
	gotoxy(coluna, (linha+5));
	
	printf("%c", 219);
	textcolor(7);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	textcolor(6);
	printf("%c", 219);
	textcolor(0);
	
	//Linha 7 - rodelinha 
	
	gotoxy(coluna, (linha+6));
	
	printf("%c", 219);
	textcolor(7);
	for(int i = 0; i < 18; i++) putchar(219);
	textcolor(0);
	printf("%c", 219);
	textcolor(6);
	printf("%c", 219);
	textcolor(0);
	
	// Linha 8
	
	gotoxy(coluna, (linha+7));
	
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
	gotoxy(coluna, (linha+8)); 
	for(int i = 0; i < 20; i++) putchar(219);
	textcolor(6);
	printf("%c", 219);
	textcolor(0);
	
	// Linha 10 => Borda de baixo
	textcolor(6);
	gotoxy((coluna+1), (linha+9)); 
	for(int i = 0; i < 20; i++) putchar(219);
	textcolor(0);
	
	//escrever cpu
	gotoxy((coluna+3), (linha+2)); printf("%c%c%c%c",219,219,219,219);
	gotoxy((coluna+3), (linha+3)); printf("%c",219);
	gotoxy((coluna+3), (linha+4)); printf("%c",219);      //etra C
	gotoxy((coluna+3), (linha+5)); printf("%c",219);
	gotoxy((coluna+3), (linha+6)); printf("%c%c%c%c",219,219,219,219);
	
	gotoxy((coluna+8), (linha+2)); printf("%c%c%c%c",219,219,219,219);
	gotoxy((coluna+8), (linha+3)); printf("%c",219);		//Letra P
	gotoxy((coluna+11), (linha+3)); printf("%c",219);
	gotoxy((coluna+8), (linha+4)); printf("%c%c%c%c",219,219,219,219);
	gotoxy((coluna+8), (linha+5)); printf("%c",219);
	gotoxy((coluna+8), (linha+6)); printf("%c",219);
	
	gotoxy((coluna+13), (linha+2)); printf("%c",219);
	gotoxy((coluna+16), (linha+2)); printf("%c",219);
	gotoxy((coluna+13), (linha+3)); printf("%c",219);
	gotoxy((coluna+16), (linha+3)); printf("%c",219);		//Letra U
	gotoxy((coluna+13), (linha+4)); printf("%c",219);
	gotoxy((coluna+16), (linha+4)); printf("%c",219);
	gotoxy((coluna+13), (linha+5)); printf("%c",219);
	gotoxy((coluna+16), (linha+5)); printf("%c",219);
	gotoxy((coluna+13), (linha+6)); printf("%c%c%c%c",219,219,219,219);
	
	gotoxy((coluna), (linha+9)); //só pro end do programa não quebrar as coisas

}

void gpu(int coluna, int linha)
{	
	// Linha 1 => Borda de cima
	gotoxy(coluna, linha);
	textcolor(8);
	printf("%c%c%c", 219, 219, 219);
	textcolor(7);	
	for(int i = 0; i < 35; i++) putchar(219);
	
	// Linha 2  - começo do cooler
	gotoxy(coluna, (linha+1));
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
	gotoxy(coluna, (linha+2));
	
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
	
	gotoxy(coluna, (linha+3));
	
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
	gotoxy(coluna, (linha+4));
	
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
	
	gotoxy(coluna, (linha+5));
	
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
	
	gotoxy(coluna, (linha+6));
	
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
	
	gotoxy(coluna, (linha+7));
	
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
	
	gotoxy(coluna, (linha+8));
	
	textcolor(8);
	printf("  %c", 219);
	textcolor(7);	
	for(int i = 0; i < 35; i++) putchar(219);
	
	// Linha 10 => Borda de baixo
	gotoxy(coluna, (linha+9)); 
	
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

void ram(int coluna, int linha)
{	
	// Linha 1 => Borda de cima
	gotoxy(coluna, linha); 
	
	textcolor(0); printf("%c", 219);
	
	textcolor(2);
	for(int i = 0; i < 41; i++) putchar(219);
	
	textcolor(0); printf("%c", 219);
	
	// Linha 2  - tracinho
	gotoxy(coluna, (linha+1));
	
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
	gotoxy(coluna, (linha+2));
	
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
	
	gotoxy(coluna, (linha+3));
	
	textcolor(0); printf(" %c", 219);
	
	textcolor(2);
	for(int i = 0; i < 39; i++) putchar(219);
	
	textcolor(0); printf("%c ", 219);
	
	// Linha 5
	
	gotoxy(coluna, (linha+4));
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

void mobo(int coluna, int linha)
{
	// Construir o PCB bruto
	gotoxy(coluna, linha); 
	textcolor(0);	
	for(int i = 0; i < 20; i++) 
	{	
		for(int j = 0; j < 10; j++)
		{
		gotoxy((coluna+i), (linha+j));
		putchar(219);
		}
	}
	
	//Construir os detalhes
	textcolor(7);
	gotoxy(coluna, (linha+1)); printf("%c%c",219,219);
	gotoxy(coluna, (linha+2)); printf("%c%c",219,219);
	gotoxy(coluna, (linha+3)); printf("%c%c",219,219);		//IO traseiro
	gotoxy(coluna, (linha+4)); printf("%c%c",219,219);
	gotoxy(coluna, (linha+5)); printf("%c%c",219,219);
	
	textcolor(7);
	gotoxy((coluna+6), (linha+2)); printf("%c",219);
	gotoxy((coluna+6), (linha+3)); printf("%c",219);
	gotoxy((coluna+9), (linha+2)); printf("%c",219);		//socket do cpu
	gotoxy((coluna+9), (linha+3)); printf("%c",219);
	textcolor(14);
	gotoxy((coluna+7), (linha+2)); printf("%c%c",219,219);
	gotoxy((coluna+7), (linha+3)); printf("%c%c",219,219);
	
	textcolor(2);
	gotoxy((coluna+13), (linha+1)); printf("%c",219);
	gotoxy((coluna+13), (linha+2)); printf("%c",219);
	gotoxy((coluna+13), (linha+3)); printf("%c",219);    //slots de ram e etc
	gotoxy((coluna+13), (linha+4)); printf("%c",219);
	gotoxy((coluna+15), (linha+1)); printf("%c",219);
	gotoxy((coluna+15), (linha+2)); printf("%c",219);
	gotoxy((coluna+15), (linha+3)); printf("%c",219);
	gotoxy((coluna+15), (linha+4)); printf("%c",219);	
	gotoxy((coluna+18), (linha+1)); printf("%c%c",219,219);
	
	textcolor(8);
	gotoxy((coluna+18), (linha+3)); printf("%c%c",219,219);    //conectores 24 pinos e etc
	gotoxy((coluna+18), (linha+4)); printf("%c%c",219,219);
	
	gotoxy((coluna+4), (linha+6)); printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);  //slots pci-e
	gotoxy((coluna+4), (linha+8)); printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
	
	textcolor(RED);
	gotoxy((coluna+15), (linha+6)); printf("%c%c",219,219); //dissipador do chipset
	gotoxy((coluna+15), (linha+7)); printf("%c%c",219,219);
	
	textcolor(15);
	gotoxy((coluna+14), (linha+9)); printf("%c%c%c%c",219,219,219,219);
	textcolor(0);
	
	gotoxy((coluna+10), (linha+10));	// tirar o exit do programa de perto
}

void HDD(int coluna, int linha)
{
	textcolor(0);
	for(int i = 0; i < 21; i++) 
	{	
		for(int j = 0; j < 12; j++)
		{
		gotoxy((coluna+i), (linha+j));
		putchar(219);
		}
	}
	textbackground(0);
	textcolor(7);
	gotoxy(coluna+6,linha+1);		printf("%c%c%c%c%c%c%c%c%c",220,220,219,219,219,219,219,220,220);
	gotoxy(coluna+4,linha+2);		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",220,219,219,219,219,219,219,219,219,219,219,219,220);
	gotoxy(coluna+4,linha+3);		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219);		//disco magnético
	gotoxy(coluna+4,linha+4);		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219);		//e parafusos
	gotoxy(coluna+5,linha+5);		printf("%c%c%c%c%c%c%c%c%c%c%c",223,219,219,219,219,219,219,219,219,219,223);
	gotoxy(coluna+8,linha+6);		printf("%c%c%c%c%c",223,223,223,223,223);
	gotoxy(coluna+1,linha);		printf("%c",220);	gotoxy(coluna+1,linha+11);		printf("%c",223);
	gotoxy(coluna+1,linha+5);		printf("%c",223);	gotoxy(coluna+19,linha+5);		printf("%c",223);
	gotoxy(coluna+19,linha);		printf("%c",220);	gotoxy(coluna+19,linha+11);	printf("%c",223);
		
	textcolor(2);
	gotoxy(coluna+10,linha+7);		printf("%c%c%c%c%c%c%c%c",220,220,220,220,220,220,220,220);
	gotoxy(coluna+10,linha+8);		printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219); // pcb
	gotoxy(coluna+12,linha+9);		printf("%c%c%c%c%c%c",219,219,219,219,219,219);
	gotoxy(coluna+13,linha+10);	printf("%c%c%c%c%c",219,219,219,219,219);
	textcolor(8);
	gotoxy(coluna+14,linha+8);		printf("%c%c%c",219,219,219);
	gotoxy(coluna+15,linha+9);		printf("%c%c",219,219);
	
	textcolor(7);
	gotoxy(coluna+3,linha+6);		printf("%c",220);
	gotoxy(coluna+3,linha+7);		printf("%c%c%c",219,219,220);										//baia para a agulha
	gotoxy(coluna+3,linha+8);		printf("%c%c%c%c%c",219,219,219,219,220);
	gotoxy(coluna+3,linha+9);		printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,220,220);
	gotoxy(coluna+3,linha+10);		printf("%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,220,220);
	
	textcolor(8);
	textbackground(7);
	//gotoxy(coluna+9,linha+4);		printf("%c",220);
	gotoxy(coluna+9,linha+5);		printf("%c",219);
	gotoxy(coluna+8,linha+6);		printf("%c%c",219,219);	
	gotoxy(coluna+7,linha+7);		printf("%c%c%c",219,219,219);			//agulha
	gotoxy(coluna+6,linha+8);		printf("%c%c%c",219,219,219);	
	gotoxy(coluna+5,linha+9);		printf("%c%c%c%c",219,219,219,219);
	gotoxy(coluna+6,linha+10);		printf("%c%c",223,223);	
	
	textcolor(0);
	gotoxy(coluna+9,linha+3);		printf("%c%c%c",220,219,220);		///motor para o disco
	gotoxy(coluna+10,linha+4);		printf("%c",223);
	
	textbackground(cor_fundo);
}
