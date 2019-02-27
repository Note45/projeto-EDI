#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define T 30 //define o tanto de apps maximo
#define X 3 //define o tamanho da matriz da tela inicial

typedef struct {
	char nome[15];
	int tam;
	int id;
}App;

//importando da função gotoxy
void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

//imprimindo a interface inicial
void telaIni(App aplicativos[X][X]) {
	int x;
	
	system("cls");
	
	//topo
	for(x = 0; x < 41; x++) {
		gotoxy(0, 0);
		printf("%c", 219);
	}
	
	//esquerda e direita
	for(x = 1; x < 25; x++) {
		gotoxy(0, x);
		printf("%c", 219);
		gotoxy(42, x);
		printf("%c\n", 219);
	}

	//espaçamentos superiores
	for(x = 2; x < 42; x++) {
		gotoxy(x, 21);
		printf("%c", 220);
	}
	
	for(x = 2; x < 42; x++) {
	gotoxy(x, 19);
	printf("%c", 220);
	}
	
	//divisorias
	for(x = 22; x < 25; x++) {
		gotoxy(14, x);
		printf("%c", 219);
	}
	
	for(x = 22; x < 25; x++) {
		gotoxy(30, x);
		printf("%c", 219);
	}
	
		//divisoria da matriz(vertical)
	for(x = 2; x < 20; x++) {
		gotoxy(15, x);
		printf("%c", 219);
	}
	
	for(x = 2; x < 20; x++) {
	   	gotoxy(29, x);
		printf("%c", 219);
	}	
	
	//divisoria da matriz (horizontal)
	for(x = 2; x < 42; x++) {
		gotoxy(x, 10);
		printf("%c", 219);
	}
		
	//parte de baixo
	for(x = 0; x < 43; x++) {
		gotoxy(x, 25);
		printf("%c", 219);
	}
	
	//comandos da tela
	gotoxy(3, 23);
	printf("1-StoreED\n");
	
	gotoxy(16, 23);
	printf("2-Meus AppsED\n");
	
	gotoxy(32, 23);
	printf("3-AppRum\n\n\n");

}

int main() {
	App myappsed_Ini[X][X];
	
	telaIni(myappsed_Ini);
	
	return 0;
}