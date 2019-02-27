#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define T 30 //define o tanto de apps maximo
#define Y 3 //define o tanto de colunos da matriz inicial
#define X 2	//define o tanto de linhas da matriz inicial
#define N 15 //define o tamanho do nome dos apps

typedef struct {
	char nome[N];
	int tam;
	int id;
}App;

//importando da função gotoxy
void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

//quantidade de apps na loja
int quantApp(App aplicativos[]) {
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
void ordena(App aplicativos[], int tam) {
	int x;
	int troca;
	App aux;
	
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

//função para ordenar para colocar os zerados para o final
void ordenaInver(App aplicativos[], int tam) {
	int x;
	int troca;
	App aux;
	
	while(1) {
		troca = 0;//variavel de controle para saber se a ordenação continua
		
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

//lendo o arquivo e adicionando no vetor
void lerArq(App StoreED[]) {
	FILE *arquivo;
	int x;
	 	
	//abrindo o arquivo de texto 
	arquivo = fopen("vStore.txt", "r");
	if(arquivo == NULL) {
	   	gotoxy(0, 28);
		printf("Nao foi possivel carregar os dados de vStore\n");
	}
	
	//gravando o arquivo de texto na memoria
	for(x = 0; x < T; x++) {
		fgets(StoreED[x].nome, 15, arquivo);
		fscanf(arquivo, "%d\n", & StoreED[x].tam);
		fscanf(arquivo, "%d\n", & StoreED[x].id);	
	}
}

//imprimindo a interface inicial
void telaIni(App aplicativos[X][Y]) {
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
		gotoxy(13, x);
		printf("%c", 219);
	}
	
	for(x = 22; x < 25; x++) {
		gotoxy(29, x);
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
	
	gotoxy(15, 23);
	printf("2-Meus AppsED\n");
	
	gotoxy(31, 23);
	printf("3-AppRumED\n\n\n");

}

//interface da 1(vstore) opção do menu
void telaStoreED(App aplicativos[], int quant) {
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

	//parte de baixo
	for(x = 0; x < 42; x++) {
		gotoxy(0, x);
		printf("%c",219);
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
		gotoxy(20, x);
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
	gotoxy(5, 23);
	printf("1-Instalar\n\n\n");
	
	gotoxy(28, 23);
	printf("0-Sair\n\n\n");
}

//Função para a 1 opção(StoreED) do menu
void funStoreED(App aplicativos[], int quant, App meusappsed[]) {	
	int operacao;
	int pausa;
	
	//imprimindo interface vstore
	while(1) {
		telaStoreED(aplicativos, quant);
		
		//Recebendo operação selecionada
		gotoxy(2,20);
		printf("Operacao:");
		scanf("%d", & operacao);
		gotoxy(0, 50);
		
		switch(operacao) {
			case 0:
				return;
 			break;
 			case 1:
     			
            break;
        	default:
        		gotoxy(12, 20);
  				printf(" - Operacao nao encontrada\n");
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
	App StoreED[T];
	App MeusAppsED_Ini[X][Y];
	App MeusAppsED[T];
	App AppRumED[T];
	int x;	
	int y;
	int quant_apps = 0;
	int operacao;
	int pausa;
	
	//zerando o vetor StoreEd
	for(x = 0; x < T; x++) {
		strcpy(StoreED[x].nome, "");
		StoreED[x].tam = 0;
		StoreED[x].id = 0;
	}
	
	//zererando vetor MeusAppsEd_Ini
	for(x = 0; x < X; x++) {
		for(y = 0; y < Y; y++) {
			strcpy(MeusAppsED_Ini[x][y].nome, "");
			MeusAppsED_Ini[x][y].tam = 0;
			MeusAppsED_Ini[x][y].id = 0;
		}
	}
	
	//zerando MeusAppsEd
	for(x = 0; x < T; x++) {
		strcpy(MeusAppsED[x].nome, "");
		MeusAppsED[x].tam = 0;
		MeusAppsED[x].id = 0;
	}
	
	//zerando AppRumEd
	for(x = 0; x < T; x++) {
		strcpy(AppRumED[x].nome, "");
		AppRumED[x].tam = 0;
		AppRumED[x].id = 0;
	}

	//chamando a leitura do arquivo
	lerArq(StoreED);
	
	//ordenando o vetor StoreEd
	quant_apps = quantApp(StoreED);
	
	ordena(StoreED, quant_apps);
	
	//chamando a interface inicial
	while(1) {
		telaIni(MeusAppsED_Ini);
		
		//Recebendo operação selecionada
		gotoxy(2,20);
		printf("Operacao:");
		scanf("%d", & operacao);
		gotoxy(0, 50);
		
		switch(operacao) {
			case 1:				
				funStoreED(StoreED, quant_apps, MeusAppsED);
  			break;
		  	case 2:
		 
			break;
			case 3:
				
			break;
			case 0:
				gotoxy(60,60);
				return 0;
			break;	  
  			default:
  				gotoxy(12, 20);
  				printf(" - Operacao nao encontrada\n");
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