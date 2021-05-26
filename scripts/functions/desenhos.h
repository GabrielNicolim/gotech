//Arquivo fonte para funções de desenhos do programa como a borda e os icones de:
//-Disquete, Logo, Lupa, CPU, GPU, RAM, Mobo, HDD	

//			09/05/2021 - Por quê refatorar esse programa antigo e mal feito?
//			R: Saudades de mexer com macaco++ e procrastinação de trabalhos atuais

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
	textbackground(cor_fundo); // Define cor do fundo
	system("cls"); 		//limpa sempre a tela quando é chamada
	
	textcolor(cor_borda);
	for (int i=2; i <= 33; i++) // Borda esquerda e direita
	{
		gotoxy(9,i);printf("%c%c                                                                                                                                            %c%c",219,219,219,219);
	}
	
	for (int i = 9; i <= (160 - 8); i++) // Parte de cima da borda
	{
		gotoxy(i,2);printf("%c",219);
	}
	for (int i = 9; i <= (160 - 8); i++) // Parte de baixo da borda 
	{
		gotoxy(i,33);printf("%c",219);
	}
			
	textcolor(cor_texto); // Define cor do texto
	
}

void disquete(int ic, int il)
{
	//quadrados basicos	
	textbackground(0);
	for(int i = 0; i < 10; i++){
		gotoxy(ic, il+i); printf("                    ");
	}
	
	textbackground(9);
	for(int i = 1; i < 9; i++){
		gotoxy(ic+1, il+i); printf("                  ");
	}
	
	//detalhes internos
	textbackground(7);
	textcolor(0);
	gotoxy(ic+3, il+1); printf("  %c%c          ",219,219);
	gotoxy(ic+3, il+2); printf("  %c%c          ",219,219);
	
	textcolor(8);
	gotoxy(ic+8, il+5); printf("  %c ",219);
	gotoxy(ic+8, il+6); printf("    ");
	
}

void logo(int ic, int il)
{
	textcolor(0);
	textbackground(cor_fundo);
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

void lupa(int ic, int il)
{	
	textcolor(0);
	textbackground(3);
	// Linha 1 - Borda Preta
	gotoxy(ic+4, il); 		printf("%c%c%c%c%c%c%c%c%c%c%c",220 ,220, 219, 219, 219, 219, 219, 219, 219, 220, 220);	
	// Linha 2  
	gotoxy(ic+2, il+1); 	printf("%c%c%c%c       %c%c%c%c", 220, 219, 219, 223, 223, 219, 219, 220);
	//linha 3
	gotoxy(ic+1, il+2); 	printf("%c%c             %c%c", 219, 223, 223, 219);
	//linha 4
	gotoxy(ic, il+3);  		printf("%c%c               %c%c", 219, 223, 223, 219);
	//linha 5
	gotoxy(ic, il+4);	 	printf("%c                 %c", 219, 219);	
	//linha 6
	gotoxy(ic, il+5);  		printf("%c%c               %c%c", 219, 220, 220, 219);
	//linha 7
	gotoxy(ic+1, il+6);		printf("%c%c             %c%c", 219, 220, 220, 219);	
	// Linha 8  
	gotoxy(ic+2, il+7); 	printf("%c%c%c%c       %c%c%c%c", 223, 219, 219, 220, 220, 219, 219, 223);
	// Linha 9 
	gotoxy(ic+4, il+8); 	printf("%c%c%c%c%c%c%c%c%c%c%c",223 ,223, 219, 219, 219, 219, 219, 219, 219, 223, 223);		
	
	//brilhinho
	textcolor(15);
	gotoxy(ic+3, il+4); printf("%c", 219);
	gotoxy(ic+4, il+5); printf("%c%c%c", 219, 219, 220);
	gotoxy(ic+7, il+6); printf("%c%c", 219, 220);
	
	//cabo
	textcolor(15);
	gotoxy(ic+18, il+6); printf("%c%c", 219,220);
	gotoxy(ic+16, il+7); printf("%c%c%c%c%c%c", 219, 219, 219, 219, 219, 220);
	gotoxy(ic+15, il+8); printf("%c%c%c%c%c%c%c%c%c", 223, 223, 219, 219, 219, 219, 219, 219,220);
	gotoxy(ic+18, il+9); printf("%c%c%c%c%c%c%c%c", 223, 219, 219, 219, 219, 219, 219, 220);			//cabo
	gotoxy(ic+20, il+10); printf("%c%c%c%c%c%c%c%c", 223, 219, 219, 219, 219, 219, 219, 220);
	gotoxy(ic+22, il+11);printf("%c%c%c%c%c%c%c", 223, 219, 219, 219, 219, 219, 219);
	gotoxy(ic+24, il+12);printf("%c%c%c%c%c", 223, 219, 219, 219, 219,223);
}

void cpu(int ic, int il)
{	
	//Quadrados básicos:
	textbackground(6);
	for(int i = 1; i < 10; i++){
		gotoxy(ic+1, il+i); printf("                    ");
	}
	
	textbackground(0);
	for(int i = 0; i < 9; i++){
		gotoxy(ic, il+i); printf("                    ");
	}
	
	textbackground(7);
	for(int i = 1; i < 8; i++){
		gotoxy(ic+1, il+i); printf("                  ");
	}
	
	//escrita C P U
	textcolor(0);
	textbackground(7);
	
	gotoxy((ic+3), (il+2)); printf("%c%c%c%c %c%c%c%c %c  %c",219,219,219,219,219,219,219,219,219,219);
	gotoxy((ic+3), (il+3)); printf("%c    %c  %c %c  %c",219,219,219,219,219);
	gotoxy((ic+3), (il+4)); printf("%c    %c%c%c%c %c  %c",219,219,219,219,219,219,219);   
	gotoxy((ic+3), (il+5)); printf("%c    %c    %c  %c",219,219,219,219);
	gotoxy((ic+3), (il+6)); printf("%c%c%c%c %c    %c%c%c%c",219,219,219,219,219,219,219,219,219);

}

void gpu(int ic, int il)
{	
	// Traseira da placa de video
	textcolor(8);
	gotoxy(ic, il);	printf("%c%c", 219, 219);
	for(int i = 0; i < 10; i++){
		gotoxy(ic+2, il+i);	printf("%c", 219);
	}
	
	//fundo principal	
	textbackground(7);
	for(int i = 0; i < 9; i++){
		gotoxy(ic+3,il+i); printf("                                   ");
	} 
	
	//adesivo generico
	textbackground(2);
	gotoxy(ic+3,il+2);	printf("                                   ");
	gotoxy(ic+3,il+6);	printf("                                   ");
	textbackground(10);
	gotoxy(ic+3,il+3);	printf("                                   ");
	gotoxy(ic+3,il+4);	printf("                                   ");
	gotoxy(ic+3,il+5);	printf("                                   ");
	
	textbackground(8); 
	textcolor(0);
	// Linha 2  - começo do cooler	
	gotoxy(ic+18, il+1); printf("   %c      ",219);
	// Linha 3  
	gotoxy(ic+16, il+2); printf("      %c       ",219);	
	// Linha 4
	gotoxy(ic+15, il+3); printf(" %c%c     %c  %c%c%c  ",220,220,219,220,220,219);
	// Linha 5	- meio do cooler
	gotoxy(ic+14, il+4); printf("    %c%c%c%c%c%c%c%c      ",223,223,220,220,219,219,223,223);	
	//Linha 6 - 
	gotoxy(ic+15, il+5); printf("       %c%c%c%c      ",219,223,220,220);
	//Linha 7
	gotoxy(ic+16, il+6); printf("    %c%c    %c   ",220,219,219);	
	// Linha 8 - final do cooler 
	gotoxy(ic+18, il+7); printf(" %c       %c",219,219);	
	
	// Linha 10 => Borda de baixo
	textbackground(8);
	textcolor(14);
	gotoxy(ic+8, il+9); printf("%c %c %c %c %c %c %c %c",219,219,219,219,219,219,219,219);

	textcolor(0);
	// Acabou :D
}

void ram(int ic, int il)
{	
	//fundo principal
	textcolor(0);
	textbackground(2);
	gotoxy(ic,il); printf("%c                                          %c",219,219);
	gotoxy(ic+1,il+1); printf("%c                                        %c",219,219);
	gotoxy(ic,il+2); printf("%c                                          %c",219,219);
	gotoxy(ic+1,il+3); printf("%c                                        %c",219,219);
	gotoxy(ic,il+4); printf("%c                                          %c",219,219);
	
	//modulos de memória
	textcolor(7);
	gotoxy(ic+6,il+1); printf("%c%c    %c%c    %c%c    %c%c    %c%c    %c%c",219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(ic+6,il+2); printf("%c%c    %c%c    %c%c    %c%c    %c%c    %c%c",219,219,219,219,219,219,219,219,219,219,219,219);

	//e contatos
	textcolor(14);
	gotoxy(ic+2,il+4); printf("%c %c %c %c %c %c %c %c   %c %c %c %c %c %c %c %c %c %c %c %c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
}

void mobo(int ic, int il)
{
	// Construir o PCB bruto
	textbackground(0);
	for(int i = 0; i < 10; i++){
		gotoxy(ic, il+i); printf("                    ");
	}
	
	//Construir os detalhes
	textcolor(7);
	gotoxy(ic, (il+1)); printf("%c%c",219,219);
	gotoxy(ic, (il+2)); printf("%c%c    %c  %c",219,219,219,219);
	gotoxy(ic, (il+3)); printf("%c%c    %c  %c",219,219,219,219);	//IO traseiro e socket
	gotoxy(ic, (il+4)); printf("%c%c",219,219);
	gotoxy(ic, (il+5)); printf("%c%c",219,219);	//externo 7=cinza 14=brilhino
	
	textcolor(14);
	gotoxy((ic+7), (il+2)); printf("%c%c",219,219);
	gotoxy((ic+7), (il+3)); printf("%c%c",219,219);
	
	textcolor(2);
	gotoxy((ic+13), (il+1)); printf("%c %c  %c%c",219,219,219,219);
	gotoxy((ic+13), (il+2)); printf("%c %c",219,219);
	gotoxy((ic+13), (il+3)); printf("%c %c",219,219);		//slots de ram e etc
	gotoxy((ic+13), (il+4)); printf("%c %c",219,219);
	
	textcolor(8);
	gotoxy((ic+18), (il+3)); printf("%c%c",219,219);    //conectores 24 pinos e etc
	gotoxy((ic+18), (il+4)); printf("%c%c",219,219);
	
	gotoxy((ic+4), (il+6)); printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);  //slots pci-e
	gotoxy((ic+4), (il+8)); printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
	
	textcolor(12);
	gotoxy((ic+15), (il+6)); printf("%c%c",219,219); //dissipador do chipset
	gotoxy((ic+15), (il+7)); printf("%c%c",219,219);
	
	textcolor(15);
	gotoxy((ic+14), (il+9)); printf("%c%c%c%c",219,219,219,219); //conectores frontais
	textcolor(0);
}

void HDD(int ic, int il)
{
	//formar a carcaça inicial e os parafuso:
	textbackground(0);
	for(int i = 0; i < 12; i++) 
	{	
		gotoxy(ic,il+i); printf("                     ");
	}
	//parafusos
	textcolor(7);	
	gotoxy(ic+1,il);		printf("%c                 %c",220,220);
	gotoxy(ic+1,il+5);		printf("%c                 %c",220,220);
	gotoxy(ic+1,il+11);		printf("%c                 %c",223,223);
	
	gotoxy(ic+6,il+1);		printf("%c%c%c%c%c%c%c%c%c",220,220,219,219,219,219,219,220,220);
	gotoxy(ic+4,il+2);		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",220,219,219,219,219,219,219,219,219,219,219,219,220);
	gotoxy(ic+4,il+3);		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219);		//disco magnético
	gotoxy(ic+4,il+4);		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219);		//e parafusos
	gotoxy(ic+5,il+5);		printf("%c%c%c%c%c%c%c%c%c%c%c",223,219,219,219,219,219,219,219,219,219,223);
	gotoxy(ic+8,il+6);		printf("%c%c%c%c%c",223,223,223,223,223);
		
	
	textcolor(2);
	gotoxy(ic+10,il+7);		printf("%c%c%c%c%c%c%c%c",220,220,220,220,220,220,220,220);
	gotoxy(ic+10,il+8);		printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219); // pcb
	gotoxy(ic+12,il+9);		printf("%c%c%c%c%c%c",219,219,219,219,219,219);
	gotoxy(ic+13,il+10);	printf("%c%c%c%c%c",219,219,219,219,219);
	textcolor(8);
	gotoxy(ic+14,il+8);		printf("%c%c%c",219,219,219);
	gotoxy(ic+15,il+9);		printf("%c%c",219,219);
	
	textcolor(7);
	gotoxy(ic+3,il+6);		printf("%c",220);
	gotoxy(ic+3,il+7);		printf("%c%c%c",219,219,220);										//baia para a agulha
	gotoxy(ic+3,il+8);		printf("%c%c%c%c%c",219,219,219,219,220);
	gotoxy(ic+3,il+9);		printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,220,220);
	gotoxy(ic+3,il+10);		printf("%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,220,220);
	
	textcolor(8);
	textbackground(7);
	gotoxy(ic+9,il+5);		printf("%c",219);
	gotoxy(ic+8,il+6);		printf("%c%c",219,219);	
	gotoxy(ic+7,il+7);		printf("%c%c%c",219,219,219);			//agulha
	gotoxy(ic+6,il+8);		printf("%c%c%c",219,219,219);	
	gotoxy(ic+5,il+9);		printf("%c%c%c%c",219,219,219,219);
	gotoxy(ic+6,il+10);		printf("%c%c",223,223);	
	
	textcolor(0);
	gotoxy(ic+9,il+3);		printf("%c%c%c",220,219,220);		///motor para o disco
	gotoxy(ic+10,il+4);		printf("%c",223);
	
	textbackground(cor_fundo);
}
