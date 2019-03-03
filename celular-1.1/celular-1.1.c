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

//Função para checar o indice onde pode ser adiciondo
int checargemInd(App aplicativos[],int tam, App adicionar) {
	int x;
	
	for(x = 0; x < tam; x++) {
		if(adicionar.tam < aplicativos[x].tam || aplicativos[x].tam == 0) {
			return x;
		}
	} 
	return x;
}

//Função para adicionar ordenar o elemento
void addOrd(App aplicativos[], int tam, App adicionar) {
	int x;
	int pos = checargemInd(aplicativos, T, adicionar);//encontrando onde devo adcionar

	//ordenando para no final adicionar	
	for(x = tam; x > pos; x--) {
		aplicativos[x] = aplicativos[x - 1];
	} 	
	aplicativos[pos] = adicionar;
}

//Função para ler o arquivo
void lerArq(App StoreED[]) {
	int x = 0;
	App elemento;
	FILE *arquivo;
	
	//abrindo o arquivo
	arquivo = fopen("vStore.txt", "r");
	if(arquivo == NULL) {
	   	gotoxy(0, 60);
		printf("Nao foi possivel carregar os dados de vStore\n");
		exit(1);
	}
	
	//ordenando e adicionando até o final do arquivo
	while(feof(arquivo) == 0) {
			fgets(elemento.nome, 15, arquivo);
			fscanf(arquivo, "%d\n", & elemento.tam);
			fscanf(arquivo, "%d\n", & elemento.id);
			
			x++;
			addOrd(StoreED, x, elemento);
	}
	
	//fechando arquivo
	fclose(arquivo);
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
	printf("q-StoreED\n");
	
	gotoxy(15, 23);
	printf("w-Meus AppsED\n");
	
	gotoxy(31, 23);
	printf("e-AppRumED\n\n\n");

}

//interface da 2(MeusAppsED) opção do menu
void telaMeusappED() {
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
	
	//legenda para mudar de pagina
	gotoxy(3, 18);
	printf(", - anterior");
	
	gotoxy(30, 18);
	printf(". - proximo");
	
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
		
	//comandos da tela
	gotoxy(5, 23);
	printf("q-Rum\n\n\n");
	
	gotoxy(16, 23);
	printf("w-Remover\n\n\n");
	
	gotoxy(32, 23);
	printf("e-Sair\n\n\n");
}

//interface da 1(vstore) opção do menu
void telaStoreED() {
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
	
	//legenda para mudar de pagina
	gotoxy(3, 18);
	printf(", - anterior");
	
	gotoxy(30, 18);
	printf(". - proximo");
	
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
		
	//comandos da tela
	gotoxy(5, 23);
	printf("q -Instalar\n\n\n");
	
	gotoxy(28, 23);
	printf("w -Sair\n\n\n");
}

//tela da função Insta
void telaInsta() {
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
	
	//legenda para mudar de pagina
	gotoxy(3, 18);
	printf(", - anterior");
	
	gotoxy(30, 18);
	printf(". - proximo");
	
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
		
	//comandos da tela
	gotoxy(5, 23);
	printf("q -Instalar\n\n\n");
	
	gotoxy(28, 23);
	printf("w -Sair\n\n\n");
}

//Função para imprimir app
void imprimirED(App aplicativos[], int quant) {
	int x;
	
	//complementando a interface para StoreEd
	gotoxy(2, 2);
	printf("Nome:");
	gotoxy(15, 2);
	printf("Tamanho:");
	gotoxy(29, 2);
	printf("Id:");
		
	for(x = 2; x < quant; x++) {
		gotoxy(2, x + 1);
		printf("%s", aplicativos[x - 2].nome);
		gotoxy(18, x + 1);
		printf("%d MB",aplicativos[x - 2].tam);
		gotoxy(32, x + 1);
		printf("%d", aplicativos[x - 2].id);
	}	
}

//Imprimindo proximas paginas
void imprimirEDpro(App aplicativos[], int quant, int inicio) {
	int x;
	int y = 3;
	
	//complementando a interface para StoreEd
	gotoxy(2, 2);
	printf("Nome:");
	gotoxy(18, 2);
	printf("Tamanho:");
	gotoxy(29, 2);
	printf("Id:");
		
	for(x = inicio; x < quant; x++) {
		gotoxy(2, y);
		printf("%s", aplicativos[x].nome);
		gotoxy(18, y);
		printf("%d MB",aplicativos[x].tam);
		gotoxy(32, y);
		printf("%d", aplicativos[x].id);
		y++;
	}	
}

//Função para intalação de apps
void funInsta(App aplicativos[], int quant, App myapps[], int pagina) {
	int id = 0;
	int x;
	int insta = 0;//recebe quanto apps estão instalados
	App elemento;//recebe o elemento a ser ordenado
	
	while(1) {
		if(pagina == 15) {
			system("cls");
			telaInsta();
			imprimirED(aplicativos, 15);
		}else {
			system("cls");
			telaInsta();
			imprimirEDpro(aplicativos, quant, pagina);
		}	

		//Recebendo operação selecionada
		gotoxy(2,20);
		printf("Id:");
		scanf("%d", & id);
		gotoxy(0, 50);
		
		//procurando o indice referete a esse id
		for(x = 0; x < quant; x++) {
			if(aplicativos[x].id == id) {
				//recebendo a quantidade de apps istalados
  				insta = quantApp(myapps);
  				
  				//recebendo o elemento com base no id
  				elemento = aplicativos[x];
				
				addOrd(myapps, insta, elemento);
				   
				return;	
			}
		}			
		
		//caso o id não seja encontrado
		while(1){
			if(pagina == 15) {
				telaInsta();
				imprimirED(aplicativos, 15);
			}else {
				telaInsta();
				imprimirEDpro(aplicativos, quant, pagina);
			}
						
			gotoxy(2,20);
			printf("Id nao encontrado - Id:");
			scanf("%d", & id);
			gotoxy(0, 50);
				
			for(x = 0; x < quant; x++) {
				if(aplicativos[x].id == id) {
					//recebendo a quantidade de apps istalados
	  				insta = quantApp(myapps);
	  				
	  				//recebendo o elemento com base no id
	  				elemento = aplicativos[x];
					
					addOrd(myapps, insta, elemento);
					   
					return;						
				}
			}			
		}		
	}
}

//função para 2(MeusappsEd) opção do meunu

//função para a 1 opção(StoreED) do menu
void funStoreED(App aplicativos[], int quant, App meusappsed[]) {	
	char operacao;
	int pausa;
	int pagina = 15;
	
	//imprimindo interface vstore
	while(1) {
		if(pagina == 15) {
			//imprimindo os 14 apps iniciais
			telaStoreED();
			imprimirED(aplicativos, 15);
		}
		
		//Recebendo operação selecionada
		gotoxy(2,20);
		printf("Operacao:");
		scanf(" %c", & operacao);
		gotoxy(0, 50);
		
		switch(operacao) {
			case 'w':
				return;
 			break;
 			case 'q':
     			funInsta(aplicativos, quant, meusappsed, pagina);
            break;
        	case ',':
				if(pagina != 15) {
					pagina--;;
					telaStoreED();
					imprimirEDpro(aplicativos, quant, pagina);
				}else {
	        		gotoxy(12, 20);
	  				printf(" - Pagina Inicial\n");
	  				pausa = 0;
	  				while(pausa < 9) {
						  printf("\n");
						  pausa++;
				   }			
					system("PAUSE");					  	
				}        		
        	break;
			case '.':
				if(operacao == '.') {
					pagina++;
					telaStoreED();
					imprimirEDpro(aplicativos, quant, pagina);
				}else {
		       		gotoxy(12, 20);
		  				printf(" - Pagina Final\n");
		  				pausa = 0;
		  				while(pausa < 9) {
							  printf("\n");
							  pausa++;
						}				
						system("PAUSE");  
				}				
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
	char operacao;
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
	
	quant_apps = quantApp(StoreED);
		
	//chamando a interface inicial
	while(1) {
		telaIni(MeusAppsED_Ini);
		
		//Recebendo operação selecionada
		gotoxy(2,20);
		printf("Operacao:");
		scanf(" %c", & operacao);
		gotoxy(0, 50);
		
		switch(operacao) {
			case 'q':				
				funStoreED(StoreED, quant_apps, MeusAppsED);
  			break;
		  	case 'w':
				  
			break;
			case 'e':
				
			break;
			case ';':
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