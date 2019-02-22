#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

int main() {
	int x;
	int y;
	
	//criando interface
	system("cls");
	//topo
	for(x = 0; x < 35; x++) {
		gotoxy(0, 0);
		printf("%c", 219);
	}
	
	//esquerda e direita
	for(x = 0; x < 25; x++) {
		gotoxy(0, x);
		printf("%c", 219);
		gotoxy(37, x);
		printf("%c\n", 219);
	}

	//parte de baixo
	for(x = 0; x < 37; x++) {
		gotoxy(0, x);
		printf("%c",219);
	}
	
	//divisôes
	for(x = 2; x < 37; x++) {
		gotoxy(x, 16);
		printf("%c", 220);
	}
	
	for(x = 17; x <=25; x++) {
		gotoxy(11, x);
		printf("%c", 219);
	}
	
	for(x = 17; x <=25; x++) {
		gotoxy(22, x);
		printf("%c", 219);
	}
	
}