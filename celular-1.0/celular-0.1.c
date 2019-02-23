#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <string.h>
#define T 30 //define o tanto de apps

typedef struct {
	char nome[15];
	int tam;
	int id;
}app;

//importando da função gotoxy
void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

//imprimindo a interface 
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

//quantidade de apps na loja
int quantApp(app aplicativos[]) {
	int x;
	int quantidade = 0;
	
	for(x = 0; x < T; x++) {
		if(aplicativos[x].tam != 0) {
			quantidade++;
		}
	}

	return quantidade;
}

//odenando um vetor do tipo app
void ordena(app aplicativos[], int tam) {
	int x;
	int troca;
	app aux;
	
	while(1) {
		troca = 0;//variavel de controle para saber se a ordenação continua
		
		for(x = 0; x < tam; x++) {
			if(aplicativos[x].tam > aplicativos[x + 1].tam && aplicativos[x + 1].tam != 0) {
				aux = aplicativos[x];//jogando valor para area de troca
				aplicativos[x] = aplicativos[x + 1];//valor do proximo indice no atual
				aplicativos[x + 1] = aux; //pegando valor da area de troca e colocando no proximo indice
				troca = 1; //ouve troca
			}
		}
		
		if(troca == 0) { //verificar se tem trocas a fazer
			break;
		}
	}
}

int main() {
	FILE *arquivo;
	app vstore[T];
	int x;
	int operacao;
	char pausa = 0;//para indentar as palavras do terminal
	int quant_apps = 0;
	
	//zerando o vetor vstore
	for(x = 0; x < T; x++) {
		vstore[x].tam = 0;
		vstore[x].id = 0;
	}
	
	//abrindo o arquivo de texto 
	arquivo = fopen("vStore.txt", "r");
	if(arquivo == NULL) {
	   	gotoxy(0, 28);
		printf("Nao foi possivel carregar os dados de vStore\n");
	}
	
	//gravando o arquivo de texto na memoria
	for(x = 0; x < T; x++) {
		fgets(vstore[x].nome, 15, arquivo);
		fscanf(arquivo, "%d\n", & vstore[x].tam);
		fscanf(arquivo, "%d\n", & vstore[x].id);	
	}
	
	//ordenando vetor vstore
	quant_apps = quantApp(vstore);
	
	ordena(vstore, quant_apps);
	
	while(1) {
		tela();
	
		//Recebendo operação selecionada
		gotoxy(2,18);
		printf("Action:");
		scanf("%d", & operacao);
		gotoxy(0, 50);
		
		switch(operacao) {
			case 1:

  			break;
		  	case 2:
		  		
			break;
			case 3:
			break;	  
  			default:
  				gotoxy(10, 18);
  				printf(" - Action not found\n");
  				pausa = 0;
  				while(pausa < 9) {
					  printf("\n");
					  pausa++;
				  }
				system("PAUSE");
  				break;
		}
	}
	
	return 0;
}                  