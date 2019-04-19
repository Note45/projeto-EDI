#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define T 30 //define o tanto de apps maximo

typedef struct {
	char nome[15];
	int tam;
	int id;
}app;

//importando da fun��o gotoxy
void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

//imprimindo a interface inicial
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
		printf("%c", 219);
	}
	
	//espa�amentos superiores
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

//interface da 1(vstore) op��o do menu
void telaVstore(app aplicativos[], int quant) {
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
	
	//espa�amentos superiores
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
		gotoxy(19, x);
		printf("%c", 219);
	}
		
	//complementando a interface para vStore
	gotoxy(2, 2);
	printf("Nome:");
	gotoxy(15, 2);
	printf("Tamanho:");
	gotoxy(29, 2);
	printf("Id:");
	
	for(x = 2; x < quant + 2; x++) {
		gotoxy(2, x + 1);
		printf("%s", aplicativos[x - 2].nome);
		gotoxy(18, x + 1);
		printf("%d MB",aplicativos[x - 2].tam);
		gotoxy(32, x + 1);
		printf("%d", aplicativos[x - 2].id);
	}
		
	//comandos da tela
	gotoxy(5, 22);
	printf("1-Install\n\n\n");
	
	gotoxy(25, 22);
	printf("0-Exit\n\n\n");
}

//imprimindo da 2(myapps) op��o do menu
void telaMyapps(app aplicativos[], int quant) {
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
		printf("%c", 219);
	}
	
	//espa�amentos superiores
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
	
	//complementando a interface para myapps
	gotoxy(2, 2);
	printf("Nome:");
	gotoxy(15, 2);
	printf("Tamanho:");
	gotoxy(29, 2);
	printf("Id:");
	
	for(x = 2; x < quant + 2; x++) {
		gotoxy(2, x + 1);
		printf("%s", aplicativos[x - 2].nome);
		gotoxy(18, x + 1);
		printf("%d MB",aplicativos[x - 2].tam);
		gotoxy(32, x + 1);
		printf("%d", aplicativos[x - 2].id);
	}
	
	//comandos da tela
	gotoxy(3, 22);
	printf("1-Rum\n\n\n");
	
	gotoxy(14, 22);
	printf("2-Remove\n\n\n");
	
	gotoxy(29, 22);
	printf("0-Exit\n\n\n");
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
		troca = 0;//variavel de controle para saber se a ordena��o continua
		
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

//fun��o para ordenar apos ser removido algum app
void ordenaInver(app aplicativos[], int tam) {
	int x;
	int troca;
	app aux;
	
	while(1) {
		troca = 0;//variavel de controle para saber se a ordena��o continua
		
		for(x = 0; x < tam; x++) {
			if(aplicativos[x].tam < aplicativos[x + 1].tam) {
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

//fun��o para rodar apps
void funRum(app myapps[], int quant, app rum[]) {
	int id = 0;
	int x;
	int rodando = quantApp(rum);//recebe quanto apps est�o rodando
	
	while(1) {
		telaMyapps(myapps, quant);
		
		//Recebendo opera��o selecionada
		gotoxy(2,18);
		printf("Id:");
		scanf("%d", & id);
		gotoxy(0, 50);
		
		//procurando o indice referete a esse id
		for(x = 0; x < quant; x++) {
			if(myapps[x].id == id) {
  				rodando = quantApp(rum);
     			rum[rodando].id = myapps[x].id;
     			rum[rodando].tam = myapps[x].tam;
     			strcpy(rum[rodando].nome, myapps[x].nome);
				return;	
			}
		}			
		
		//caso o id n�o seja encontrado
		while(1){
			system("cls");
			telaMyapps(myapps, quant);
			gotoxy(2,18);
			printf("Id nao encontrado - Id:");
			scanf("%d", & id);
			gotoxy(0, 50);
				
			for(x = 0; x < quant; x++) {
				if(myapps[x].id == id) {
	  				rodando = quantApp(rum);
	     			rum[rodando].id = myapps[x].id;
	     			rum[rodando].tam = myapps[x].tam;
	     			strcpy(rum[rodando].nome, myapps[x].nome);
					return;	
				}
			}			
		}		
	}	
}

//fun��o para remover apps
void funRemove(app myapps[], int quant) {
	int id = 0;
	int x;
	int encontrado = 0;
	
	while(1) {
		telaMyapps(myapps, quant);
		
		//Recebendo opera��o selecionada
		gotoxy(2,18);
		printf("Id:");
		scanf("%d", & id);
		gotoxy(0, 50);
		
		//procurando o indice referete a esse id
		for(x = 0; x < quant; x++) {
			if(myapps[x].id == id) {
				strcpy(myapps[x].nome, "");
   				myapps[x].id = 0;
   				myapps[x].tam = 0;
   				encontrado = 1;
	   	   	    break;
			}
		}
		
		//ordenando para retirar a posi��o vazia
		ordenaInver(myapps, quant);	
		ordena(myapps, quant);	
		
		if(encontrado == 1) {
			return;
		
		}else {
			//caso o id n�o seja encontrado
			while(1){
				system("cls");
				telaMyapps(myapps, quant);
				gotoxy(2,18);
				printf("Id nao encontrado - Id:");
				scanf("%d", & id);
				gotoxy(0, 50);
					
				for(x = 0; x < quant; x++) {
					if(myapps[x].id == id) {
						strcpy(myapps[x].nome, "");
		     			myapps[x].id = 0;
		     			myapps[x].tam = 0;
						break;	
					}
				}
				
				//ordenando para retirar a posi��o vazia
				ordenaInver(myapps, quant);	
				ordena(myapps, quant);
				
				if(encontrado == 1) {
					return;
				}						
			}					
		}		
	}	
}

//fun��o para instalar apps
void funInsta(app aplicativos[], int quant, app myapps[]) {
	int id = 0;
	int x;
	int insta = 0;//recebe quanto apps est�o instalados
	
	while(1) {
		telaVstore(aplicativos, quant);
		
		//Recebendo opera��o selecionada
		gotoxy(2,18);
		printf("Id:");
		scanf("%d", & id);
		gotoxy(0, 50);
		
		//procurando o indice referete a esse id
		for(x = 0; x < quant; x++) {
			if(aplicativos[x].id == id) {
  				insta = quantApp(myapps);
     			myapps[insta].id = aplicativos[x].id;
     			myapps[insta].tam = aplicativos[x].tam;
     			strcpy(myapps[insta].nome, aplicativos[x].nome);
				return;	
			}
		}			
		
		//caso o id n�o seja encontrado
		while(1){
			system("cls");
			telaVstore(aplicativos, quant);
			gotoxy(2,18);
			printf("Id nao encontrado - Id:");
			scanf("%d", & id);
			gotoxy(0, 50);
				
			for(x = 0; x < quant; x++) {
				if(aplicativos[x].id == id) {
   					insta = quantApp(myapps);
     				myapps[insta].id = aplicativos[x].id;
     				myapps[insta].tam = aplicativos[x].tam;
     				strcpy(myapps[insta].nome, aplicativos[x].nome);
					return;	
				}
			}			
		}		
	}
}

//op��o 2(myapps) do menu
void funMyapps(App myapps[], int quant, App rum[]) {
	int operacao;
	int pausa;
	int pagina = 15;
	
	//imprimindo interface
	while(1) {
		
		
		//Recebendo opera��o selecionada
		gotoxy(2, 18);
		printf("Action:");
		scanf("%d", & operacao);
		gotoxy(0, 50);
		
		switch(operacao) {
			case 0:
				return;
 			break;
 			case 1:
     			funRum(myapps, quant, rum);
            break;
        	case 2:
        		funRemove(myapps, quant);
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
		}	
	}
}

//op��o 1(vstore) do menu
void funVstore(app aplicativos[], int quant, app myapps[]) {	
	int operacao;
	int pausa;
	
	//imprimindo interface vstore
	while(1) {
		telaVstore(aplicativos, quant);
		//Recebendo opera��o selecionada
		gotoxy(2,18);
		printf("Action:");
		scanf("%d", & operacao);
		gotoxy(0, 50);
		
		switch(operacao) {
			case 0:
				return;
 			break;
 			case 1:
     			funInsta(aplicativos, quant, myapps);
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
		}
	}	
}

int main() {
	FILE *arquivo;
	app vstore[T];
	app myapps[T];
	app rum[T];
	int x;
	int operacao;
	char pausa = 0;//para indentar as palavras do terminal
	int quant_apps = 0;
	int quant_insta = 0;//recebe a quantidade de apps instalados
	
	//zerando o vetor vstore
	for(x = 0; x < T; x++) {
		strcpy(vstore[x].nome, "");
		vstore[x].tam = 0;
		vstore[x].id = 0;
	}
	
	//zererando vetor myapps
	for(x = 0; x < T; x++) {
		strcpy(myapps[x].nome, "");
		myapps[x].tam = 0;
		myapps[x].id = 0;
	}
	
	//zerando rum
	for(x = 0; x < T; x++) {
		strcpy(rum[x].nome, "");
		rum[x].tam = 0;
		rum[x].id = 0;
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
	
		//Recebendo opera��o selecionada
		gotoxy(2,18);
		printf("Action:");
		scanf("%d", & operacao);
		gotoxy(0, 50);
		
		switch(operacao) {
			case 1:				
				funVstore(vstore, quant_apps, myapps);
  			break;
		  	case 2:
		  		//contando e ordenando os apps instalados
		  		quant_insta = quantApp(myapps);
		  		
		  		ordena(myapps, quant_insta);
		  		
		  		//chamando fun��o dessa op��o
		  		funMyapps(myapps, quant_insta, rum);
			break;
			case 3:
				
			break;
			case 0:
				gotoxy(60,60);
				return 0;
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