#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

int main() {
	int x;
	
	system("cls");
	//topo
	int y;
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
	
	//espa�amento superior
	for(x = 2; x < 38; x++) {
		gotoxy(x, 19);
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
	
	return 0;
}                  