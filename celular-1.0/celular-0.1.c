#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>

typedef struct {
	char nome[15];
	int tam;
}app;

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

void tela() {
	int x;
	
	system("cls");
	
	//topo
	for(x = 0; x < 37; x++) {
		gotoxy(0, 0);
		printf("%c", 219);
	}
	
	//esquerda e direita
	for(x = 1; x < 25; x++) {
		gotoxy(0, x);
		printf("%c", 219);
		gotoxy(38, x);
		printf("%c\n", 219);
	}

	//parte de baixo
	for(x = 0; x < 38; x++) {
		gotoxy(0, x);
		printf("%c",219);
	}
	
	//espaçamentos superiores
	for(x = 2; x < 38; x++) {
		gotoxy(x, 19);
		printf("%c", 220);
	}
	
	for(x = 2; x < 38; x++) {
	gotoxy(x, 17);
	printf("%c", 220);
	}
	
	//divisorias
	for(x = 20; x < 25; x++) {
		gotoxy(12, x);
		printf("%c", 219);
	}
	
	for(x = 20; x < 25; x++) {
		gotoxy(25, x);
		printf("%c", 219);
	}
	
	//comandos da tela
	gotoxy(3, 22);
	printf("1-vStore\n\n\n");
	
	gotoxy(14, 22);
	printf("2-My Apps\n\n\n");
	
	gotoxy(29, 22);
	printf("3-Rum\n\n\n");
}

int main() {
	int operacao;
	char pausa = 0;
	FILE *arquivo;
	app vstore[30];
	int x;
	
	//zerando o vetor vstore
	for(x = 0; x < 30; x++) {
		vstore[x].tam = 0;
	}
	
	while(1) {
		tela();
	
		//Recebendo operação selecionada
		gotoxy(2,18);
		printf("Action:");
		scanf("%d", & operacao);
		gotoxy(0, 50);
		
		switch(operacao) {
			case 1:
				printf("Google");
  			break;
		  	case 2:
		  		
			break;
			case 3:
			break;	  
  			default:
  				gotoxy(10, 18);
  				printf(" :Action not found");
  				while(pausa < 10) {
					  printf("\n");
					  pausa++;
				  }
				system("PAUSE");
  				break;
		}
	}
	
	return 0;
}                  