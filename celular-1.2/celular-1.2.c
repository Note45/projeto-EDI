#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define T 31 //define o tanto de apps maximo
#define N 15 //define o tamanho do nome dos apps
#define I 6	 //definindo o tamanho do vetor para os apps da tela inicial

typedef struct {
	char nome[N];
	int tam;
	int id;
}App;

typedef struct {
	int IL;
	int FL;
	int IA;
	int FA;
}Cont;

Cont ControleL[3];//Variavel de controle das listas

//importando da função gotoxy
void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

//função para iniciar a lista do vetor
void iniciaL(App vet[]) {
 	int x; 
 	int y;
 	
 	for(x = 0; x < 3 ; x++) {
		ControleL[x].IL = -1;	 
	    ControleL[x].FL = -1;
		ControleL[x].IA = 1;
		ControleL[x].FA = 30;			
	}
	for(y = 0; y < T; y++) {
		vet[y].tam = -1;
	}
}

//função para buscar o indice onde vai ser adicionado o elemento
int buscaI(App vet[], App elemento, int lista) {
	int x = 1;	
	
	//se a lista estiver vazia
	if(ControleL[lista].IL == -1 && ControleL[lista].FL == -1) {
		return -5;		
	}else {
		if(elemento.tam <= vet[ControleL[lista].IL].tam) {//se for no começo da lista
			return ControleL[lista].IL - 1;
		}
		if(elemento.tam >= vet[ControleL[lista].FL].tam) {//se for no final
			return ControleL[lista].FL + 1;
		}else { // se for no meio
			for(x = ControleL[lista].IL; x <= ControleL[lista].FL; x++) {
				if(elemento.tam < vet[x].tam) {
					return x;
				}
			}
		}
	}
	
	return -5;	
}

//função para verificar quantos aplicativos estão cadastrados em uma lista
int quantApp(App aplicativos[], int lista) {
	int x;
	int quantidade = 0;
	
	if(ControleL[lista].IL == -1 && ControleL[lista].FL == -1) {
		return quantidade;
	}else {
		for(x = ControleL[lista].IL; x <= ControleL[lista].FL; x++) {
			if(aplicativos[x].tam != -1) {
				quantidade++;
			}
		}
	}

	return quantidade;
}

//funções para iimprimir os apps
void imprimirED(App aplicativos[], int quant, int lista) {
	int x;
	int y = 2;
	
	//complementando a interface
	gotoxy(2, 2);
	printf("Nome:");
	gotoxy(15, 2);
	printf("Tamanho:");
	gotoxy(29, 2);
	printf("Id:");
	
	if(quant == 0) {
		return;
	}else if(lista != 0) {
	    for(x = ControleL[lista].IL; (y - 1) <= quant && y <= 16; x++) {
			gotoxy(2, y + 1);
			printf("%s", aplicativos[x].nome);
			gotoxy(18, y + 1);
			printf("%d MB",aplicativos[x].tam);
			gotoxy(32, y + 1);
			printf("%d", aplicativos[x].id);
			y++;
        }		
	}else {		
		for(x = ControleL[lista].IL; y <= 16; x++) {
			gotoxy(2, y + 1);
			printf("%s", aplicativos[x].nome);
			gotoxy(18, y + 1);
			printf("%d MB",aplicativos[x].tam);
			gotoxy(32, y + 1);
			printf("%d", aplicativos[x].id);
			y++;
		}
	}	
}


void imprimirEDpro(App aplicativos[], int quant, int lista) {
	int x;
	int y = 3;
	int a;
	int z = 0;
	
	//quantidade de impressões
	a = quant - 15;
	
	//complementando a interface
	gotoxy(2, 2);
	printf("Nome:");
	gotoxy(18, 2);
	printf("Tamanho:");
	gotoxy(29, 2); 
	printf("Id:");
		
	for(x = ControleL[lista].IL + 15; z < a; x++) {
		gotoxy(2, y);
		printf("%s", aplicativos[x].nome);
		gotoxy(18, y);
		printf("%d MB",aplicativos[x].tam);
		gotoxy(32, y);
		printf("%d", aplicativos[x].id);
		y++;
		z++;
	}	
}

//área de funções relacionadas a telas
void telaIni(App vet[]) {
	int x;
	int quant = quantApp(vet, 1);
	
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
	
	//imprimindo apps iniciais
	if(ControleL[1].IL != -1 && ControleL[1].FL != -1) {
		if(quant == 1 || quant > 1) {
			gotoxy(2, 3);
			printf("Nome:");	
			gotoxy(3, 4);
			printf("%s", vet[ControleL[1].IL].nome);
			gotoxy(2, 5);
			printf("Tamanho:");
			gotoxy(3, 6);
			printf("%d MB", vet[ControleL[1].IL].tam);
			gotoxy(2, 7);
			printf("Id:");
			gotoxy(3, 8);
			printf("%d", vet[ControleL[1].IL].id);
		}
					
		if( quant == 2 || quant > 2) {
			gotoxy(16, 3);
			printf("Nome:");	
			gotoxy(17, 4);
			printf("%s", vet[ControleL[1].IL + 1].nome);
			gotoxy(16, 5);
			printf("Tamanho:");
			gotoxy(17, 6);
			printf("%d MB", vet[ControleL[1].IL + 1].tam);
			gotoxy(16, 7);
			printf("Id:");
			gotoxy(17, 8);
			printf("%d", vet[ControleL[1].IL + 1].id);
		}											
			
		if(quant == 3 || quant > 3) {
			gotoxy(30, 3);
			printf("Nome:");	
			gotoxy(31, 4);
			printf("%s", vet[ControleL[1].IL + 2].nome);
			gotoxy(30, 5);
			printf("Tamanho:");
			gotoxy(31, 6);
			printf("%d MB", vet[ControleL[1].IL + 2].tam);
			gotoxy(30, 7);
			printf("Id:");
			gotoxy(31, 8);
			printf("%d", vet[ControleL[1].IL + 2].id);			
		}											
		
		if(quant == 4 || quant > 4) {
			gotoxy(2, 12);
			printf("Nome:");	
			gotoxy(3, 13);
			printf("%s", vet[ControleL[1].IL + 3].nome);
			gotoxy(2, 14);
			printf("Tamanho:");
			gotoxy(3, 15);
			printf("%d MB", vet[ControleL[1].IL + 3].tam);
			gotoxy(2, 16);
			printf("Id:");
			gotoxy(3, 17);
			printf("%d", vet[ControleL[1].IL + 3].id);
		}
	
				
		if(quant == 5 || quant > 5) {
			gotoxy(16, 12);
			printf("Nome:");	
			gotoxy(17, 13);
			printf("%s", vet[ControleL[1].IL + 4].nome);
			gotoxy(16, 14);
			printf("Tamanho:");
			gotoxy(17, 15);
			printf("%d MB", vet[ControleL[1].IL + 4].tam);
			gotoxy(16, 16);
			printf("Id:");
			gotoxy(17, 17);
			printf("%d", vet[ControleL[1].IL + 4].id);
		}											
			
		if(quant == 5 || quant > 5) {
			gotoxy(30, 12);
			printf("Nome:");	
			gotoxy(31, 13);
			printf("%s", vet[ControleL[1].IL + 5].nome);
			gotoxy(30, 14);
			printf("Tamanho:");
			gotoxy(31, 15);
			printf("%d MB", vet[ControleL[1].IL + 5].tam);
		   	gotoxy(30, 16);
			printf("Id:");
			gotoxy(31, 17);
			printf("%d", vet[ControleL[1].IL + 5].id);			
		}
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
	printf("q-Instalar\n\n\n");
	
	gotoxy(28, 23);
	printf("w-Sair\n\n\n");
}

void telaAppRum() {
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
	printf("q-Parar\n\n\n");
	
	gotoxy(28, 23);
	printf("w-Sair\n\n\n");
}

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
	printf("q-Instalar\n\n\n");
	
	gotoxy(28, 23);
	printf("w-Sair\n\n\n");
}

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

//função para inserir um elemento
void inserirL(App StoreED[], int indice, int lista, App elemento) {
	int x;		
		
	//caso a lista já esteja cheia
	if((ControleL[lista].IL == ControleL[lista].IA) && (ControleL[lista].FL == ControleL[lista].FA)) {
		return;
	}else {
		if(ControleL[lista].IL == -1 && ControleL[lista].FL == -1) {//lista estiver vazia
			ControleL[lista].IL = 15;
			ControleL[lista].FL = 15;
			StoreED[15] = elemento;
			return;
		}	
			
		if(ControleL[lista].IL > indice) {//adicionando no inicio da lista
			if(ControleL[lista].IL != 1) {
				ControleL[lista].IL--;
				StoreED[ControleL[lista].IL] = elemento;
			}else {
				ControleL[lista].FL++;
					
				for(x = ControleL[lista].FL; x >= 0; x--) {
					StoreED[x] = StoreED[x - 1];	
				}
						
				StoreED[ControleL[lista].IL] = elemento;						
			}
			return;
		}
		
		//adicionando no final	
		if((indice == (ControleL[lista].FL + 1)) && (ControleL[lista].FL != ControleL[lista].FA)) {//adicionando no final
			ControleL[lista].FL++;
			StoreED[indice] = elemento;
			return;			
		}else if((ControleL[lista].IL != ControleL[lista].IA) && (ControleL[lista].FL == ControleL[lista].FA)) {
			ControleL[lista].IL--;
			
			for(x = ControleL[lista].IL; x < indice; x++) {
				StoreED[x] = StoreED[x + 1];
			}
			StoreED[indice - 1] = elemento;
			return;
		}			
			
		//adicionando no meio da lista
		if((indice - ControleL[lista].IL) < (ControleL[lista].IL - indice) && ControleL[lista].IL != ControleL[lista].IA) {
			ControleL[lista].IL--;
			for(x = ControleL[lista].IL; x < indice; x++) {
				StoreED[x] = StoreED[x + 1];
			}
			StoreED[indice] = elemento;
			return;
		}else {
		   	ControleL[lista].FL++;
				
			for(x = ControleL[lista].FL; x > indice; x--) {
			   	StoreED[x] = StoreED[x - 1];
			}
			StoreED[indice] = elemento;
			return;
		}  
    }					
}

//função para remover um app
void remoL(App vet[], int lista, int indice) {
	int x; 
	
	//lista vazia
	if(ControleL[lista].IL == -1 && ControleL[lista].FL == -1) {
		return;
	}else {
		//se a lista só tiver um elemento
		if(ControleL[lista].IL == ControleL[lista].FL) {
			ControleL[lista].IL = -1;
			ControleL[lista].FL = -1;
			return;
		}
		
		//procurando indice do elemento
		for(x = ControleL[lista].IL; x <= ControleL[lista].FL; x++) {
			if(vet[x].id == indice) {
				indice = x;
				break;
			}
		}		
		
		if(ControleL[lista].IL == indice) {//removendo do inicio da lista
			ControleL[lista].IL++;
			return;
		}else if(ControleL[lista].FL == indice) {//removendo do final da listas
			ControleL[lista].FL--;
			return;
		}else {
			//removendo do meio da lista
			if((indice - ControleL[lista].IL) < (ControleL[lista].IL - indice)) {// perto do inicio
				ControleL[lista].IL++;
				
				for(x = indice; x >= ControleL[lista].IL; x--) {
					vet[x] = vet[x - 1];
				}
				return;
			}else {//perto do final
			   	ControleL[lista].FL--;
					
				for(x = indice; x <= ControleL[lista].FL; x++) {
				   	vet[x] = vet[x + 1];
				}
				return;
			} 			
		}
	}  	
}			   	

//função para ler o arquivo
void lerArq(App StoreED[]) {
	int indice;
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
		
		//buscando onde vou adiconar o elemento
		indice = buscaI(StoreED, elemento, 0);
		
		//inserindo elemento
		inserirL(StoreED, indice, 0, elemento);		
	}
	//fechando arquivo
	fclose(arquivo);
}

//função da opção de remover um app
void funRemo(App myapps[], int pagina, App rum[]) {
	int id = -1;
	int x;
	int quant;
	
	//so remove se tiver apps intalados
	if(ControleL[1].IL != -1 && ControleL[1].FL != -1) {
		while(1) {
			if(pagina == 15) {
				system("cls");
				telaMeusappED();
				quant = quantApp(myapps, 1);
				imprimirED(myapps, quant, 1);
			}else {
				system("cls");
				telaMeusappED();
				quant = quantApp(myapps, 1);
				imprimirEDpro(myapps, quant, 1);
			}	
	
			//Recebendo o id
			gotoxy(2,20);
			printf("Id:");
			scanf("%d", & id);
			gotoxy(0, 50);	
			
			//checando se é um indice valido
			for(x = ControleL[1].IL; x <= ControleL[1].FL; x++) {
				if(myapps[x].id == id) {
					x = -10;
					break;
				}
			}			
			
			if(x == -10) {
				//Removendo indice do myapps
				remoL(myapps, 1, id);
				
				//checando se ele está rodando e parando
				if(ControleL[2].IL != -1 && ControleL[2].FL != -1) {
					for(x = ControleL[2].IL; x <= ControleL[2].FL; x++) {
						if(rum[x].id == id) {
							x = -10;
							break;
						}
					}
					if(x == -10) {
						remoL(rum, 2, id);
						return;	
					}else {
						return;
					}
				}else {
					return;
				}			
			}else {	
			   	//caso o id não seja encontrado
				while(1){
					if(pagina == 15) {
						telaMeusappED();
						imprimirED(myapps, quant, 1);
					}else {
						telaMeusappED();
						imprimirEDpro(myapps, quant, 1);
					}
									
					gotoxy(2,20);
					printf("Id nao encontrado - Id:");
					scanf("%d", & id);
					gotoxy(0, 50);

					//checando se é um indice valido
					for(x = ControleL[1].IL; x <= ControleL[1].FL; x++) {
						if(myapps[x].id == id) {
							x = -10;
							break;
						}
					}			
					
					if(x == -10) {
						//Removendo indice do myapps
						remoL(myapps, 1, id);
						
						//checando se ele está rodando e parando
						if(ControleL[2].IL != -1 && ControleL[2].FL != -1) {
							for(x = ControleL[2].IL; x <= ControleL[2].FL; x++) {
								if(rum[x].id == id) {
									x = -10;
									break;
								}
							}
							if(x == -10) {
								remoL(rum, 2, id);
								return;	
							}else {
								return;
							}
						}else {
							return;
						}											
					}
				}	
			}	
		}
	}else{
		gotoxy(2,20);
		printf("Nenhum app instalado!");
		gotoxy(2, 28);
		system("PAUSE");
		return;	
	}
}

//função da opção parar a execução de um app
void funStop( int pagina, App rum[]) {
	int id = -1;
	int x;
	int quant;
	
	//so remove se tiver apps rodando
	if(ControleL[2].IL != -1 && ControleL[2].FL != -1) {
		while(1) {
			if(pagina == 15) {
				system("cls");
				telaAppRum();
				quant = quantApp(rum, 2);
				imprimirED(rum, quant, 2);
			}else {
				system("cls");
				telaAppRum();
				quant = quantApp(rum, 2);
				imprimirEDpro(rum, quant, 2);
			}	
	
			//Recebendo o id
			gotoxy(2,20);
			printf("Id:");
			scanf("%d", & id);
			gotoxy(0, 50);	
			
			//checando se é um indice valido
			for(x = ControleL[2].IL; x <= ControleL[2].FL; x++) {
				if(rum[x].id == id) {
					x = -10;
					break;
				}
			}			
			
			if(x == -10) {//checando se ele está rodando e parando
				if(ControleL[2].IL != -1 && ControleL[2].FL != -1) {
					for(x = ControleL[2].IL; x <= ControleL[2].FL; x++) {
						if(rum[x].id == id) {
							x = -10;
							break;
						}
					}
					if(x == -10) {
						remoL(rum, 2, id);
						return;	
					}else {
						return;
					}
				}else {
					return;
				}			
			}else {	
			   	//caso o id não seja encontrado
				while(1){
					if(pagina == 15) {
						telaAppRum();
						imprimirED(rum, quant, 2);
					}else {
						telaAppRum();
						imprimirEDpro(rum, quant, 2);
					}
									
					gotoxy(2,20);
					printf("Id nao encontrado - Id:");
					scanf("%d", & id);
					gotoxy(0, 50);

					//checando se é um indice valido
					for(x = ControleL[2].IL; x <= ControleL[2].FL; x++) {
						if(rum[x].id == id) {
							x = -10;
							break;
						}
					}			
					
					if(x == -10) {//checando se ele está rodando e parando
						if(ControleL[2].IL != -1 && ControleL[2].FL != -1) {
							for(x = ControleL[2].IL; x <= ControleL[2].FL; x++) {
								if(rum[x].id == id) {
									x = -10;
									break;
								}
							}
							if(x == -10) {
								remoL(rum, 2, id);
								return;	
							}else {
								return;
							}
						}else {
							return;
						}											
					}
				}	
			}	
		}
	}else{
		gotoxy(2,20);
		printf("Nenhum app rodando!");
		gotoxy(2, 28);
		system("PAUSE");
		return;	
	}
}

//função para intalação de apps
void funInsta(App aplicativos[], int quant, App myapps[], int pagina) {
	int id = 0;
	int x;
	int local = -1;//recebe quanto onde vou intalar o aplicativo
	
	while(1) {
		if(pagina == 15) {
			system("cls");
			telaInsta();
			imprimirED(aplicativos, quant, 0);
		}else {
			system("cls");
			telaInsta();
			imprimirEDpro(aplicativos, quant, 0);
		}	
		
		//Recebendo operação selecionada
		gotoxy(2,20);
		printf("Id:");
		scanf("%d", & id);
		gotoxy(0, 50);
		
		if((ControleL[1].IL != ControleL[1].IA) || (ControleL[1].FL != ControleL[1].FA)) {
			//verificando se e um id valido
			for(x = ControleL[0].IL; x <= ControleL[0].FL; x++) {
	   			if(aplicativos[x].id == id) {
					x = -100;
					break;
				}
			}
			
			if(x != -100) {
				gotoxy(5, 20);
				printf("-Aplicativo instalado/nao encontrado");
				gotoxy(2, 28);
				system("PAUSE");
				return;				
			}
			
			//vendo se o app ja foi instalado
			for(x = ControleL[1].IL; x <= ControleL[1].FL; x++) {
				if(myapps[x].id == id){
					gotoxy(5, 20);
					printf("-Aplicativo instalado/nao encontrado");
					gotoxy(2, 28);
					system("PAUSE");
					return;
				}			
			}	
			
			//encontrando qual app eu vou intalar
			for(x = ControleL[0].IL; x <= ControleL[0].FL; x++) {
				if(aplicativos[x].id == id) {
					break;
				}
			}
			
			local = buscaI(myapps, aplicativos[x], 1);
			
			inserirL(myapps, local, 1, aplicativos[x]);	
			
			return;	
		}else if(ControleL[1].IL == ControleL[1].IA  && ControleL[1].FL == ControleL[1].FA){
			gotoxy(5, 20);
			printf("-Memoria cheia!");
			gotoxy(2, 28);
			system("PAUSE");
			return;				
		}else {
			//caso o id não seja encontrado
			while(1){
				if(pagina == 15) {
					telaInsta();
					imprimirED(aplicativos, quant, 0);
				}else {
					telaInsta();
					imprimirEDpro(aplicativos, quant, 0);
				}
							
				gotoxy(2,20);
				printf("Id nao encontrado - Id:");
				scanf("%d", & id);
				gotoxy(0, 50);
				
				//verificando se e um id valido
				for(x = ControleL[0].IL; x <= ControleL[0].FL; x++) {
		   			if(aplicativos[x].id == id) {
						x = -100;
						break;
					}
				}
				
				if(x != -100) {
					gotoxy(5, 20);
					printf("-Aplicativo instalado/nao encontrado");
					gotoxy(2, 28);
					system("PAUSE");
					return;				
				}
				
				//vendo se o app ja foi instalado				
				if((ControleL[1].IL != ControleL[1].IA) || (ControleL[1].FL != ControleL[1].FA)) {
					for(x = ControleL[1].IL; x <= ControleL[1].FL; x++) {
						if(myapps[x].id == id){
							gotoxy(5, 20);
							printf("-Aplicativo instalado/nao encontrado");
						   	gotoxy(2, 28);
							system("PAUSE");
							return;
						}			
					}
					
					//encontrando qual app eu vou intalar
					for(x = ControleL[0].IL; x <= ControleL[0].FL; x++) {
						if(aplicativos[x].id == id) {
							break;
						}
					}
					
					local = buscaI(myapps, aplicativos[x], 1);
					
					inserirL(myapps, local, 1, aplicativos[x]);	
					
					return;					
				}	
						 			
            }		
	    }
	}
}

//função para rodar apps
void funRumED(App myapps[], int quant, App rum[], int pagina) {
	int id = 0;
	int x;
	int local = 0;//recebe quanto apps estão rodando
	
	if(ControleL[1].IL != -1 && ControleL[1].FL != -1) {
		while(1) {
			if(pagina == 15) {
				system("cls");
				telaMeusappED();
				imprimirED(myapps, quant, 1);
			}else {
				system("cls");
				telaMeusappED();
				imprimirEDpro(myapps, quant, 1);
			}	
	
			//Recebendo id do app
			gotoxy(2,20);
			printf("Id:");
			scanf("%d", & id);
			gotoxy(0, 50);
			
			//verificando se e um id valido
			for(x = ControleL[1].IL; x <= ControleL[1].FL; x++) {
		   		if(myapps[x].id == id) {
					x = -100;
					break;
				}
			}
				
			if(x != -100) {
				gotoxy(5, 20);
				printf("-Aplicativo instalado/nao encontrado");
				gotoxy(2, 28);
				system("PAUSE");
				return;				
			}						
		
			//vendo se o app ja está rodando
			for(x = ControleL[2].IL; x <= ControleL[2].FL; x++) {
				if(rum[x].id == id){
					gotoxy(5, 20);
					printf("-Aplicativo rodando/nao encontrado");
					gotoxy(2, 28);
					system("PAUSE");
					return;
				}			
			}	
							
			if(ControleL[2].IL != ControleL[2].IA || ControleL[2].FL != ControleL[2].FA) {
				//encontrando qual app eu rodar
				for(x = ControleL[1].IL; x <= ControleL[1].FL; x++) {
					if(myapps[x].id == id) {
						break;
					}
				}
				
				local = buscaI(rum, myapps[x], 2);
				
				inserirL(rum, local, 2, myapps[x]);	
				
				return;	
			}else if(ControleL[2].IL == ControleL[2].IA  && ControleL[2].FL == ControleL[2].FA){
				gotoxy(5, 20);
				printf("-Memoria cheia!");
				gotoxy(2, 28);
				system("PAUSE");
				return;	
			}else {		
			//caso o id não seja encontrado
				while(1){
					if(pagina == 15) {
						telaMeusappED();
						imprimirED(myapps, quant, 1);
					}else {
						telaMeusappED();
						imprimirEDpro(myapps, quant, 1);
					}
								
					gotoxy(2,20);
					printf("Id nao encontrado - Id:");
					id = 0;
					scanf("%d", & id);
					gotoxy(0, 50);

					//verificando se e um id valido
					for(x = ControleL[1].IL; x <= ControleL[1].FL; x++) {
				   		if(myapps[x].id == id) {
							x = -100;
							break;
						}
					}
						
					if(x != -100) {
						gotoxy(5, 20);
						printf("-Aplicativo instalado/nao encontrado");
						gotoxy(2, 28);
						system("PAUSE");
						return;				
					}
					
					//vendo se o app ja está rodando
					for(x = ControleL[2].IL; x <= ControleL[2].FL; x++) {
						if(rum[x].id == id){
							gotoxy(5, 20);
							printf("-Aplicativo rodando/nao encontrado");
							gotoxy(2, 28);
							system("PAUSE");
							return;
						}			
					}																		
					//vendo se o app ja esta rodando
					if(ControleL[2].IL != ControleL[2].IA || ControleL[2].FL != ControleL[2].FA) {					
						//encontrando qual app vou rodar
						for(x = ControleL[1].IL; x <= ControleL[1].FL; x++) {
							if(myapps[x].id == id) {
								break;
							}
						}
						
						local = buscaI(rum, myapps[x], 2);
						
						inserirL(rum, local, 2, myapps[x]);	
						
						return;	
					}					  				
				}
			}		
		}
	}else {
		gotoxy(2,20);
		printf("Nenhum app instalado!");
		gotoxy(2, 28);
		system("PAUSE");
		return;			
	}
}	

//funções do menu inicial
void funStoreED(App aplicativos[], App meusappsed[]) {	
	char operacao;
	int pausa;
	int pagina = 15;
	int quant = quantApp(aplicativos, 0);
	
	//imprimindo interface StoreED
	while(1) {
		if(pagina == 15) {
			//imprimindo os 16 apps iniciais
			telaStoreED();
			imprimirED(aplicativos, quant, 0);
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
					pagina--;
					telaStoreED();
					imprimirEDpro(aplicativos, quant, 0);
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
					imprimirEDpro(aplicativos, quant, 0);
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

//função para 2(MeusappsEd) opção do meunu
void funMeusappsED(App myapps[], App rum[]) {
	char operacao;
	int pausa;
	int pagina = 15;
	int quant = quantApp(myapps, 1);
	
	//imprimindo interface
	while(1) {
		//contando a quantidade de apps caso um seja removido
		quant = quantApp(myapps, 1);
		
		if(pagina == 15) {
			//imprimindo os 16 apps iniciais
			telaMeusappED();
			imprimirED(myapps, quant, 1);
		}
				
		//Recebendo operação selecionada
		gotoxy(2, 20);
		printf("Action:");
		scanf(" %c", & operacao);
		gotoxy(0, 50);
		
		switch(operacao) {
			case ',':
				if(pagina != 15) {
					pagina--;
					telaMeusappED();
					imprimirEDpro(myapps, quant, 1);
				}else {
	        		gotoxy(12, 20);
	  				printf("- Pagina Inicial\n");
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
					telaMeusappED();
					imprimirEDpro(myapps, quant, 1);
				}else {
		       		gotoxy(12, 20);
		  				printf("- Pagina Final\n");
		  				pausa = 0;
		  				while(pausa < 9) {
							  printf("\n");
							  pausa++;
						}				
						system("PAUSE");  
				}								
			break;		  		
			case 'e':
				return;
 			break;
 			case 'q':
 				quant = quantApp(myapps, 1);
     			funRumED(myapps, quant, rum, pagina);
            break;
        	case 'w':
        		funRemo(myapps, pagina, rum);
        	break;	
        	default:
        		gotoxy(10, 20);
  				printf("-Operacao nao encontrada\n");
  				pausa = 0;
  				while(pausa < 9) {
					  printf("\n");
					  pausa++;
				  }
				system("PAUSE");	
		}	
	}
}

//função para 3(AppRumED) opçao do menu
void funAppRumED(App rum[]) {	
	char operacao;
	int pausa;
	int pagina = 15;
	int quant = quantApp(rum, 2);
	
	//imprimindo interface rum
	while(1) {
		//recebendo novo quant caso algum app seja removido
		quant = quantApp(rum, 2);
		
		if(pagina == 15) {
			//imprimindo os 16 apps iniciais
			telaAppRum();
			imprimirED(rum, quant, 2);
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
     			funStop(pagina, rum);
            break;
        	case ',':
				if(pagina != 15) {
					pagina--;
					telaAppRum();
					imprimirEDpro(rum, quant, 2);
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
					telaAppRum();
					imprimirEDpro(rum, quant, 2);
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
	App MeusAppsED[T];
	App AppRumED[T];
	char operacao;
	int pausa;
	
	//iniciando as listas
	iniciaL(StoreED);		
	iniciaL(MeusAppsED);
	iniciaL(AppRumED);	
	
	//chamando a leitura do arquivo
	lerArq(StoreED);

	while(1) {
		telaIni(MeusAppsED);
		
		//opção de saida
		gotoxy(2, 28);
		printf("Para desligar o MobileED pressione ';'");
			
		//Recebendo operação selecionada
		gotoxy(2,20);
		printf("Operacao:");
		scanf(" %c", & operacao);
		gotoxy(0, 50);
			
		switch(operacao) {
			case 'q'://StoreED
				funStoreED(StoreED, MeusAppsED);
	  		break;
		  	case 'w'://MeusAppsED
   	  		   funMeusappsED(MeusAppsED, AppRumED);
			break;
			case 'e'://AppRumED
				funAppRumED(AppRumED);
			break;
			case ';':
				system("cls");
				gotoxy(0,0);
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