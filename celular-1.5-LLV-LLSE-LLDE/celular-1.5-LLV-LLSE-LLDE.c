#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

#define T 30 //define o tanto de apps maximo
#define N 15 //define o tamanho do nome dos apps
#define L 3  //quantidade de listas no programa

typedef struct {
	char nome[N];
	int tam;
	int id;
}App;

typedef struct {
    App info;
    int prox;
    int ante;
}no;

typedef struct {
	int IL;
	int FL;
    no vet[T];
}LLDE;

typedef struct {
	int IL;
	int FL;
	int IA;
	int FA;
}Cont;

Cont ControleLLV;//Variavel de controle da LLV

int disp[L];//controla quem esta disponivel nas listas

//importando da funcao gotoxy
void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

//devolve onde eu vou inserir na lista
int alocaNo(LLDE *lista, int local) {
    int d;
    if(disp[local] == -1) {
        return -3;//se a lista estiver cheia
    }
    d = disp[local];
    disp[local] = lista->vet[disp[local]].prox;
    return d;
}

//iniciando listas
void inicia(LLDE *lista, int local) {
    int i;
    disp[local] = 0;
    
	for(i = 0; i < T; i++) {
        lista->vet[i].prox = i + 1;
        lista->vet[i].ante = i - 1;
        lista->vet[i].info.tam = -2;
        lista->vet[i].info.id = -2;
    }
    
    lista->vet[T - 1].prox = -1; 
    lista->vet[T - 1].info.tam = -2;
    lista->vet[T - 1].info.id = -2;
    lista->IL = 0;
    lista->FL = 0;
}

//fun��o para inserir um em uma LLV
void inserirLLV(App StoreED[], int indice, App elemento) {
	int x;		
		
	//caso a lista ja esteja cheia
	if((ControleLLV.IL == ControleLLV.IA) && (ControleLLV.FL == ControleLLV.FA)) {
		return;
	}else {
		if(ControleLLV.IL == -1 && ControleLLV.FL == -1) {//lista estiver vazia
			ControleLLV.IL = 15;
			ControleLLV.FL = 15;
			StoreED[15] = elemento;
			return;
		}	
			
		if(ControleLLV.IL > indice) {//adicionando no inicio da lista
			if(ControleLLV.IL != 1) {
				ControleLLV.IL--;
				StoreED[ControleLLV.IL] = elemento;
			}else {
				ControleLLV.FL++;
					
				for(x = ControleLLV.FL; x >= 0; x--) {
					StoreED[x] = StoreED[x - 1];	
				}
						
				StoreED[ControleLLV.IL] = elemento;						
			}
			return;
		}
			
		if((indice == (ControleLLV.FL + 1)) && (ControleLLV.FL != ControleLLV.FA)) {//adicionando no final
			ControleLLV.FL++;
			StoreED[indice] = elemento;
			return;			
		}else if((ControleLLV.IL != ControleLLV.IA) && (ControleLLV.FL == ControleLLV.FA)) {
			ControleLLV.IL--;
			
			for(x = ControleLLV.IL; x < indice; x++) {
				StoreED[x] = StoreED[x + 1];
			}
			StoreED[indice - 1] = elemento;
			return;
		}			
			
		if((indice - ControleLLV.IL) < (ControleLLV.IL - indice) && ControleLLV.IL != ControleLLV.IA) {	//adicionando no meio da lista
			ControleLLV.IL--;
			for(x = ControleLLV.IL; x < indice; x++) {
				StoreED[x] = StoreED[x + 1];
			}
			StoreED[indice] = elemento;
			return;
		}else {
		   	ControleLLV.FL++;
				
			for(x = ControleLLV.FL; x > indice; x--) {
			   	StoreED[x] = StoreED[x - 1];
			}
			StoreED[indice] = elemento;
			return;
		}  
    }					
}

//inseirir um elemento na lista
void inserirL(LLDE *lista, App elemento, int local) {
	int indice;//recebe o indice disponivel
	int x;
	int posi = -1;

	indice = alocaNo(lista, local);
	
	//se alista estiver cheia
	if(indice == -3) {
		gotoxy(10, 20);
		printf("    Memoria Cheia");
		x = 0;
		while(x < 9) {
			  printf("\n");
			  x++;
		  }
		system("PAUSE");
	}
	
	//fazendo a primeira inser��o na LLDE
	if(lista->vet[lista->IL].info.tam == -2) {
		lista->vet[lista->IL].info = elemento;
		lista->vet[lista->IL].prox = -1;
		return;
	}
	
	//buscando em qual posi��o eu vou inserir meu elemento
	if(abs(elemento.tam - lista->vet[lista->IL].info.tam) <= abs(elemento.tam - lista->vet[lista->FL].info.tam)) {
		for(x = lista->IL; x < T; x = lista->vet[x].prox) {//se for melhor correr pelo inicio
			if(x == -1) {//parar quando chegar ao ultimo elemento da lista
				break;
			}
			
			if(elemento.tam <= lista->vet[x].info.tam && x == lista->IL) {//insetir no inicio
				posi = 1;
				break;
			}
			
			if(elemento.tam >= lista->vet[x].info.tam && lista->vet[x].prox == -1) {//inserir no final
				posi = 2;
				break; 
			}
			
			if(elemento.tam <= lista->vet[x].info.tam) {//meio
				posi = x;			
				break;
			}
		}
	}else {//se for melhor correr pelo fim
		for(x = lista->FL; x < T; x = lista->vet[x].ante) {
			if(x == -1) {//parar quando chegar ao ultimo elemento da lista
				break;
			}
			
			if(elemento.tam <= lista->vet[x].info.tam && x == lista->IL) {//insetir no inicio
				posi = 1;
				break;
			}
			
			if(elemento.tam >= lista->vet[x].info.tam && x == lista->FL) {//inserir no final
				posi = 2;
				break; 
			}
			
			if(elemento.tam >= lista->vet[x].info.tam) {//meio
				posi = lista->vet[x].prox;
				break;
			}
		}
	}
	
	//inserindo o elemento
	if(indice != -3) {//lista n�o vazia
		if(posi == 1) {//inicio
			lista->vet[indice].info = elemento;//recebendo elemento inicial
			lista->vet[indice].prox = lista->IL;//apontando para proximo
			lista->vet[lista->IL].ante = indice;//anterior do inicio da lista para o novo
			lista->IL = indice; //atualizando inicio
			lista->vet[indice].ante = -1;//anterior do novo = -1
		}else if(posi == 2) {//final
			lista->vet[indice].info = elemento;//recebendo final
			lista->vet[indice].ante = lista->FL;//anterior do elemento apontando para o antigo final da lista
			lista->vet[lista->FL].prox = indice;//proximo do antigo final da lista apontando para o novo FL
			lista->FL = indice;//atualizando o final da lista
			lista->vet[indice].prox = -1;//proximo do elemento = -1
		}else if(posi != 1 && posi != 2){//meio
			lista->vet[indice].info = elemento;//recebendo elemento
			lista->vet[indice].prox = posi;//proximo do elemento para o indice
			lista->vet[indice].ante = lista->vet[posi].ante;//anterior do elemento recebendo o anterior da sua posi��o
			lista->vet[lista->vet[posi].ante].prox = indice;//anterior recebe como proximo o indice que entra
			lista->vet[posi].ante = indice;//proximo recebe como anterior o indice que entra
		}
	}
}

//removendo um elemento da lista
void removerL(LLDE *lista, App elemento, int local) {
	int x;
	int posi;
	
	//se a lista estiver vazia
	if(lista->vet[lista->IL].info.tam == -2) {
		printf("Lista Vazia!\n");
		system("PAUSE");
	}
	
	//buscando em qual posi��o eu vou remover o elemento
	if(abs(elemento.tam - lista->vet[lista->IL].info.tam) <= abs(elemento.tam - lista->vet[lista->FL].info.tam)) {
		for(x = lista->IL; x < T; x = lista->vet[x].prox) {//se for melhor correr pelo inicio
			if(x == -1) {//parar quando chegar ao ultimo elemento da lista
				break;
			}
			
			if(elemento.id == lista->vet[x].info.id && x == lista->IL && x == lista->FL) {//remover no inicio e for o unico
				posi = 3;
				break;
			}

			if(elemento.id == lista->vet[x].info.id && x == lista->IL) {//remover no inicio
				posi = 1;
				break;
			}						
			
			if(elemento.id == lista->vet[x].info.id && x == lista->FL) {//remover no final
				posi = 2;
				break; 
			}
			
			if(elemento.id == lista->vet[x].info.id) {//meio
				posi = x;			
				break;
			}
		}
	}else {//se for melhor correr pelo fim
		for(x = lista->FL; x < T; x = lista->vet[x].ante) {
			if(x == -1) {//parar quando chegar ao ultimo elemento da lista
				break;
			}
			
			if(elemento.id == lista->vet[x].info.id && x == lista->IL && x == lista->FL) {//remover no inicio e for o unico
				posi = 3;
				break;
			}

			if(elemento.id == lista->vet[x].info.id && x == lista->IL) {//remover no inicio
				posi = 1;
				break;
			}						
			
			if(elemento.id == lista->vet[x].info.id && x == lista->FL) {//inserir no final
				posi = 2;
				break; 
			}
			
			if(elemento.id == lista->vet[x].info.id) {//meio
				posi = x;			
				break;
			}
		}
	}
	
	//removendo elemento
	if(posi == 1) {//remover no inicio 
		lista->vet[disp[local]].ante = lista->IL;//anterior do disponivel recebe o IL
		lista->IL = lista->vet[lista->IL].prox;//IL recebe o seu proximo como novo IL
		lista->vet[lista->IL].ante = -1;//anterior do novo IL recebe -1
		lista->vet[lista->vet[disp[local]].ante].prox = disp[local];//antigo IL recebe como proximo o disponivel
		disp[local] = lista->vet[disp[local]].ante;//antigo IL se torna o novo disponivel
		return;
	}else if(posi == 2){//remover no fim
		lista->vet[disp[local]].ante = lista->FL;//anterior do disponivel = atual FL
		lista->FL = lista->vet[lista->FL].ante;//FL recebe o anteror do atual FL
		lista->vet[lista->FL].prox = -1;//proximo do FL = -1
		lista->vet[lista->vet[disp[local]].ante].ante = -1;//anterior do antigo FL recebe -1
		lista->vet[lista->vet[disp[local]].ante].prox = disp[local];//proximo do antigo FL = atual disponivel
		disp[local] = lista->vet[disp[local]].ante;//antigo final da lista vira o disponivel
		return;
	}else if(posi == 3){//removendo a unica informa��o da lista
		lista->vet[lista->IL].info.tam = -2;//zerando o elemento
		lista->vet[disp[local]].ante = lista->IL;//anterior do disponivel recebe FL ou IL
		lista->vet[lista->vet[disp[local]].ante].prox = disp[local];//antigo IL o FL recebe como proximo o disponivel
		disp[local] = lista->vet[disp[local]].ante;//disponivel recebe como anterior o antigo IL ou FL da lista
		return;
	}else if(posi != 1 && posi != 2 && posi != 3){//removendo no meio
		lista->vet[lista->vet[posi].ante].prox = lista->vet[posi].prox;//anterior aponta para o proximo do removido
		lista->vet[lista->vet[posi].prox].ante = lista->vet[posi].ante;//proximo do removido aponta para o anterior
		lista->vet[posi].ante = -1;//anterior do removido recebe -1
		lista->vet[posi].prox = disp[local];//proximo do removido recebe atual disponivel
		lista->vet[disp[local]].ante = posi;//anterior do atual disponivel recebe removido
		disp[local] = posi;//removido vira atual disponivel
		return;
	}
}

//funcao para imprimir a LLV
void imprimirLVVed(App aplicativos[], int lista) {
	int x;
	int y = 0;
	int local = 1;
	
	//complementando a interface
	gotoxy(2, 2);
	printf("Nome:");
	gotoxy(15, 2);
	printf("Tamanho:");
	gotoxy(29, 2);
	printf("Id:");
	
	if(lista == 1) {
		for(x = ControleLLV.IL; x <= ControleLLV.FL; x++) {
			if(y < 15) {
				y++;
			}else {
				local = x;
				break;
			}
        }	
	}
	
	y = 2;
	
	if(aplicativos[ControleLLV.IL].tam == -1) {
		return;
	}else if(lista == 0) {
	    for(x = ControleLLV.IL; (y - 1) <= ControleLLV.FL && y <= 16; x++) {
			gotoxy(2, y + 1);
			printf("%s", aplicativos[x].nome);
			gotoxy(18, y + 1);
			printf("%d MB",aplicativos[x].tam);
			gotoxy(32, y + 1);
			printf("%d", aplicativos[x].id);
			y++;
        }		
	}else {		
		for(x = local; x <= ControleLLV.FL; x++) {
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

//funcoes para imprimir os apps
void imprimirED(LLDE lista) {
	int x;
	int y = 2;
	
	//complementando a interface
	gotoxy(2, 2);
	printf("Nome:");
	gotoxy(15, 2);
	printf("Tamanho:");
	gotoxy(29, 2);
	printf("Id:");
	
	if(lista.vet[lista.IL].info.tam == -2) {
		return;
	}
	
    for(x = lista.IL; y < 17; x = lista.vet[x].prox) {//lista vazia
    	if(x == -1) {
			break;
		}
		
		gotoxy(2, y + 1);
		printf("%s", lista.vet[x].info.nome);
		gotoxy(18, y + 1);
		printf("%d MB",lista.vet[x].info.tam);
		gotoxy(32, y + 1);
		printf("%d", lista.vet[x].info.id);
		y++;
    }
}


void imprimirEDpro(LLDE lista) {
	int x;
	int y = 0;
	
	//complementando a interface
	gotoxy(2, 2);
	printf("Nome:");
	gotoxy(18, 2);
	printf("Tamanho:");
	gotoxy(29, 2); 
	printf("Id:");
	
	if(lista.vet[lista.IL].info.tam == -2) {//se a lista estiver vazia
		return;
	}
	
	for(x = lista.IL; y < 15; x = lista.vet[x].prox) {
		if(x == -1) {//recebendo qual o indice de numero 16	
			break;
		}
		y++;
	}
	
	y = 2;
	 
    for(x = x; y < 17; x = lista.vet[x].prox) {
    	if(x == -1) {
			break;
		}
		
		gotoxy(2, y + 1);
		printf("%s", lista.vet[x].info.nome);
		gotoxy(18, y + 1);
		printf("%d MB",lista.vet[x].info.tam);
		gotoxy(32, y + 1);
		printf("%d", lista.vet[x].info.id);
		y++;
    }	
}

//Area de funcoes relacionadas a telas
void telaIni(LLDE lista) {
	int x;
	int i = 0;
	int vet[6];//recebe os indices dos elementos
	   
	//zerendo vetor   	
	for(x = 0; x < 6; x++) {
		vet[x] = -2;
	}
	
	//recebendo indices
	if(lista.vet[lista.IL].info.tam != -2) {
		for(x = lista.IL; i < 6; x = lista.vet[x].prox) {
			if(x == -1) {
				break;
			}	
						
			vet[i] = x;
			i++;		
		} 
	}
	
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

	//espa�amentos superiores
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
	if(lista.vet[lista.IL].info.tam != -2) {
		if(lista.vet[vet[0]].info.tam != -2 && vet[0] != -2) {
			gotoxy(2, 3);
			printf("Nome:");	
			gotoxy(3, 4);
			printf("%s", lista.vet[vet[0]].info.nome);
			gotoxy(2, 5);
			printf("Tamanho:");
			gotoxy(3, 6);
			printf("%d MB", lista.vet[vet[0]].info.tam);
			gotoxy(2, 7);
			printf("Id:");
			gotoxy(3, 8);
			printf("%d", lista.vet[vet[0]].info.id);
		}
					
		if(lista.vet[vet[1]].info.tam != -2 && vet[1] != -2) {
			gotoxy(16, 3);
			printf("Nome:");	
			gotoxy(17, 4);
			printf("%s", lista.vet[vet[1]].info.nome);
			gotoxy(16, 5);
			printf("Tamanho:");
			gotoxy(17, 6);
			printf("%d MB", lista.vet[vet[1]].info.tam);
			gotoxy(16, 7);
			printf("Id:");
			gotoxy(17, 8);
			printf("%d", lista.vet[vet[1]].info.id);
		}											
			
		if(lista.vet[vet[2]].info.tam!= -2 && vet[2] != -2) {
			gotoxy(30, 3);
			printf("Nome:");	
			gotoxy(31, 4);
			printf("%s", lista.vet[vet[2]].info.nome);
			gotoxy(30, 5);
			printf("Tamanho:");
			gotoxy(31, 6);
			printf("%d MB", lista.vet[vet[2]].info.tam);
			gotoxy(30, 7);
			printf("Id:");
			gotoxy(31, 8);
			printf("%d", lista.vet[vet[2]].info.id);			
		}											
		
		if(lista.vet[vet[3]].info.tam != -2 && vet[3] != -2) {
			gotoxy(2, 12);
			printf("Nome:");	
			gotoxy(3, 13);
			printf("%s", lista.vet[vet[3]].info.nome);
			gotoxy(2, 14);
			printf("Tamanho:");
			gotoxy(3, 15);
			printf("%d MB", lista.vet[vet[3]].info.tam);
			gotoxy(2, 16);
			printf("Id:");
			gotoxy(3, 17);
			printf("%d", lista.vet[vet[3]].info.id);
		}
	
				
		if(lista.vet[vet[4]].info.tam != -2 && vet[4] != -2) {
			gotoxy(16, 12);
			printf("Nome:");	
			gotoxy(17, 13);
			printf("%s", lista.vet[vet[4]].info.nome);
			gotoxy(16, 14);
			printf("Tamanho:");
			gotoxy(17, 15);
			printf("%d MB", lista.vet[vet[4]].info.tam);
			gotoxy(16, 16);
			printf("Id:");
			gotoxy(17, 17);
			printf("%d", lista.vet[vet[4]].info.id);
		}											
			
		if(lista.vet[vet[5]].info.tam != -2 && vet[5] != -2) {
			gotoxy(30, 12);
			printf("Nome:");	
			gotoxy(31, 13);
			printf("%s", lista.vet[vet[5]].info.nome);
			gotoxy(30, 14);
			printf("Tamanho:");
			gotoxy(31, 15);
			printf("%d MB", lista.vet[vet[5]].info.tam);
		   	gotoxy(30, 16);
			printf("Id:");
			gotoxy(31, 17);
			printf("%d", lista.vet[vet[5]].info.id);			
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
	
	//espa�amentos superiores
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
	
	//espa�amentos superiores
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
	
	//espa�amentos superiores
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
	
	//espa�amentos superiores
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

//funcao para ler o arquivo
void lerArq(App storeED[]) {
	App elemento;
	FILE *arquivo;
	int indice;
	int x;
	
	//iniciando LLV
	ControleLLV.IL = -1;	 
    ControleLLV.FL = -1;
	ControleLLV.IA = 1;
	ControleLLV.FA = 30;			

	for(x = 0; x < T; x++) {
		storeED[x].tam = -1;
		storeED[x].id = -1;
	}
	
	//abrindo o arquivo
	arquivo = fopen("vStore.txt", "r");
	if(arquivo == NULL) {
	   	gotoxy(0, 60);
		printf("Nao foi possivel carregar os dados de vStore\n");
		exit(1);
	}
	
	//ordenando e adicionando ate o final do arquivo
	while(feof(arquivo) == 0) {
		fgets(elemento.nome, 15, arquivo);
		fscanf(arquivo, "%d\n", & elemento.tam);
		fscanf(arquivo, "%d\n", & elemento.id);
		
		//buscando onde vou adiconar o elemento
		if(ControleLLV.IL == -1 && ControleLLV.FL == -1) {//se a lista estiver vazia
			indice = -5;		
		}else {
			if(elemento.tam <= storeED[ControleLLV.IL].tam) {//se for no come�o da lista
				indice = ControleLLV.IL - 1;
			}
			if(elemento.tam >= storeED[ControleLLV.FL].tam) {//se for no final
				indice = ControleLLV.FL + 1;
			}else { // se for no meio
				for(x = ControleLLV.IL; x <= ControleLLV.FL; x++) {
					if(elemento.tam < storeED[x].tam) {
						indice =  x;
						break;
					}
				}
			}
		}
		
		//inserindo elemento
		inserirLLV(storeED, indice, elemento);		
	}
	//fechando arquivo
	fclose(arquivo);
}

//funcao para rodar um app
void funRum(LLDE meusappsED, LLDE *apprumED, int pagina, int local) {
	int x;
	int id;
	App elemento;
	
	//zerando elemento
	elemento.tam = -2;
	elemento.id = -2;
	
	//se a lista estiver cheia
	if(disp[2] == -1) {
		gotoxy(5, 20);
		printf("-Memoria Cheia");
		gotoxy(2, 28);
		system("PAUSE");
	   	return;	
	}
	
	while(1) {
		if(pagina == 15) {
			system("cls");
			telaMeusappED();	
			imprimirED(meusappsED);
		}else {
			system("cls");
			telaMeusappED();
			imprimirEDpro(meusappsED);
		}	
		
		//Recebendo id selecionado
		gotoxy(2,20);
		printf("Id:");
		scanf("%d", & id);
		gotoxy(0, 50);
				
		if(apprumED->vet[apprumED->IL].info.tam != -2) {//vendo se o app ja foi instalado
		    for(x = apprumED->IL; x < T; x = apprumED->vet[x].prox) {
		    	if(x == -1) {
					break;
				}		    	
		    	
				if(id == apprumED->vet[x].info.id) {
					gotoxy(5, 20);
					printf("-Aplicativo ja selecionado");
					gotoxy(2, 28);
					system("PAUSE");
					return;	
				}
		    }
		}
		
		//buscando qual app vou instalar e intalando
	    for(x = meusappsED.IL; x < T; x = meusappsED.vet[x].prox) {
	    	if(x == -1) {
				break;
			}
			
			if(id == meusappsED.vet[x].info.id) {
				elemento = meusappsED.vet[x].info;
				break;
			}
	    }
	    
		if(elemento.tam != -2) {
			inserirL(apprumED, elemento, local);
			return;
		}else {
			while(1) {
				gotoxy(5, 20);
				printf("-Aplicativo nao encontrado");
				gotoxy(2, 28);
				system("PAUSE");
				return;
				
						
				//Recebendo id selecionado
				gotoxy(2,20);
				printf("Id:");
				scanf("%d", & id);
				gotoxy(0, 50);	
						
				if(apprumED->vet[apprumED->IL].info.tam != -2) {//vendo se o app ja foi instalado
				    for(x = apprumED->IL; x < T; x = apprumED->vet[x].prox) {
				    	if(x == -1) {
							break;
						}		    	
				    	
						if(id == apprumED->vet[x].info.id) {
							gotoxy(5, 20);
							printf("-Aplicativo ja selecionado");
							gotoxy(2, 28);
							system("PAUSE");
							break;	
						}
				    }
				}
				
	 	 	    for(x = meusappsED.IL; x < T; x = meusappsED.vet[x].prox) {
			    	if(x == -1) {
						break;
					}
					
					if(id ==  meusappsED.vet[x].info.id) {
						elemento = meusappsED.vet[x].info;
						break;
					}
			    }
			    
				if(elemento.tam != -2) {
					inserirL(apprumED, elemento, local);
					break;
				}						
			} 	
		}	  			
	}
}

//funcao da opcao de remover um app
int funRemo(LLDE *remove, int pagina, LLDE *apprumED, int local, int chamada) {
	int id = -1;
	int x;
	App elemento;
	
	//zerando elemento
	elemento.tam = -2;
	elemento.id = -2;
	
	//so remove se tiver apps intalados
	while(1) {
		if(pagina == 15) {
			system("cls");
			if(chamada == 1) {
				telaMeusappED();	
			}else if(chamada == 2) {
				telaAppRum();
			}
			imprimirED(*remove);
		}else {
			system("cls");
			if(chamada == 1) {
				telaMeusappED();	
			}else if(chamada == 2) {
				telaAppRum();
			}
			imprimirEDpro(*remove);
		}	

		//Recebendo o id
		gotoxy(2,20);
		printf("Id:");
		scanf("%d", & id);
		gotoxy(0, 50);	
		
		//checando se � um indice valido
	    for(x = remove->IL; x < T; x = remove->vet[x].prox) {
	    	if(x == -1) {
				break;
			}
			
			if(id == remove->vet[x].info.id) {
				elemento = remove->vet[x].info;//removendo do meusappsED
				break;
			}
	    }			
		
		if(elemento.tam != -2) {
			removerL(remove, elemento, local);	
      	    return id;			
		}else {
			while(1) {
				gotoxy(5, 20);
				printf("-Aplicativo nao encontrado");	
				gotoxy(2, 28);
				system("PAUSE");	
				
				//Recebendo o id
				gotoxy(2,20);
				printf("Id:");
				scanf("%d", & id);
				gotoxy(0, 50);	
				
				//checando se � um indice valido
			    for(x = remove->IL; x < T; x = remove->vet[x].prox) {
			    	if(x == -1) {
						break;
					}
					
					if(id == remove->vet[x].info.id) {
						elemento = remove->vet[x].info;;
					}
			    }			
				
				if(elemento.tam != -2) {
					removerL(remove, elemento, local);//removendo do meusappsED
					return id;
				}							
			}		
		}
	}
}

//funcao para intalacao de apps
void funInsta(LLDE storeED, LLDE *meusappsED, int pagina, int local) {
	int id = -2;
	int x;
	App elemento;
	
	//zerando elemento
	elemento.tam = -2;
	elemento.id = -2;
	
	//se a lista estiver cheia
	if(*disp == -1) {
		gotoxy(5, 20);
		printf("-Memoria Cheia");
		gotoxy(2, 28);
		system("PAUSE");
	   	return;	
	}
	
	while(1) {
		if(pagina == 15) {
			system("cls");
			if(local == 0) {
				telaInsta();
			}else if(local == 1) {
				telaMeusappED();
			}else if(local == 2) {
				telaAppRum();
			}
			imprimirED(storeED);
		}else {
			system("cls");
			if(local == 0) {
				telaInsta();
			}else if(local == 1) {
				telaMeusappED();
			}else if(local == 2) {
				telaAppRum();
			}
			imprimirEDpro(storeED);
		}	
		
		//Recebendo id selecionado
		gotoxy(2,20);
		printf("Id:");
		scanf("%d", & id);
		gotoxy(0, 50);
				
		if(meusappsED->vet[meusappsED->IL].info.tam != -2) {//vendo se o app ja foi instalado
		    for(x = meusappsED->IL; x < T; x = meusappsED->vet[x].prox) {
		    	if(x == -1) {
					break;
				}		    	
		    	
				if(id == meusappsED->vet[x].info.id) {
					gotoxy(5, 20);
					printf("-Aplicativo ja selecionado");
					gotoxy(2, 28);
					system("PAUSE");
					return;	
				}
		    }
		}
		
		//buscando qual app vou instalar e intalando
	    for(x = storeED.IL; x < T; x = storeED.vet[x].prox) {
	    	if(x == -1) {
				break;
			}
			
			if(id == storeED.vet[x].info.id) {
				elemento = storeED.vet[x].info;
				break;
			}
	    }
	    
		if(elemento.tam != -2) {
			inserirL(meusappsED, elemento, 1);
			return;
		}else {
			while(1) {
				gotoxy(5, 20);
				printf("-Aplicativo nao encontrado");
				gotoxy(2, 28);
				system("PAUSE");
				return;
				
						
				//Recebendo id selecionado
				gotoxy(2,20);
				printf("Id:");
				scanf("%d", & id);
				gotoxy(0, 50);	
						
				if(meusappsED->vet[meusappsED->IL].info.tam != -2) {//vendo se o app ja foi instalado
				    for(x = meusappsED->IL; x < T; x = meusappsED->vet[x].prox) {
				    	if(x == -1) {
							break;
						}
												
						if(id == meusappsED->vet[x].info.id) {
							gotoxy(5, 20);
							printf("-Aplicativo ja selecionado");
							gotoxy(2, 28);
							system("PAUSE");
							return;	
						}
				    }
				}
				
				//buscando qual app vou instalar e intalando
			    for(x = storeED.IL; x < T; x = storeED.vet[x].prox) {
			    	if(x == -1) {
						break;;
					}	
							    	
					if(id == storeED.vet[x].info.id) {
						elemento = storeED.vet[x].info;
						break;
					}
			    }
			    
	    		if(elemento.tam != -2) {
					inserirL(meusappsED, elemento, 1);
					return;
				}						
			} 	
		}	  			
	}
	return;
}	

//funcoes do menu inicial
void funStoreED(App storeED[], LLDE *meusappsED) {	
	char operacao;
	int pausa;
	int pagina = 15;
	
	//imprimindo interface StoreED
	while(1) {
		if(pagina == 15) {
			//imprimindo os 16 apps iniciais
			system("cls");
			telaStoreED();
			imprimirLVVed(storeED, 0);
		}
		
		//Recebendo opera��o selecionada
		gotoxy(2,20);
		printf("Operacao:");
		scanf(" %c", & operacao);
		gotoxy(0, 50);
		
		switch(operacao) {
			case 'w':
				return;
 			break;
 			case 'q':
     			
            break;
        	case ',':
				if(pagina != 15) {
					pagina--;
					system("cls");
					telaStoreED();
					imprimirLVVed(storeED, 0);
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
					system("cls");
					telaStoreED();
				    imprimirLVVed(storeED, 1);
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

//funcao para 2(MeusappsEd) opcao do meunu
void funMeusappsED(LLDE *meusappsED, LLDE *apprumED) {
	char operacao;
	int pausa;
	int pagina = 15;
	App elemento; 
	int id;
	int x;
	
	//imprimindo interface
	while(1) {		
		if(pagina == 15) {
			//imprimindo os 16 apps iniciais
			system("cls");
			telaMeusappED();
			imprimirED(*meusappsED);
			
		}
				
		//Recebendo operacao selecionada
		gotoxy(2, 20);
		printf("Operacao:");
		scanf(" %c", & operacao);
		gotoxy(0, 50);
		
		switch(operacao) {
			case ',':
				if(pagina != 15) {
					pagina--;
					system("cls");
					telaMeusappED();
					imprimirED(*meusappsED);
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
					system("cls");
					telaMeusappED();
					imprimirEDpro(*meusappsED);
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
 			case 'q'://rodar um app
				funRum(*meusappsED, apprumED, pagina, 2);
            break;
        	case 'w'://removendo elemento
        		id = funRemo(meusappsED, pagina, apprumED, 2, 1);
			
				if(id != -2) {
					//zerando elemento
					elemento.tam = -2;
					elemento.id = -2;				
					
					//checando se o app est� rodando para remover
					if(apprumED->vet[apprumED->IL].info.tam != -2) {
					    for(x = apprumED->IL; x < T; x = apprumED->vet[x].prox) {
					    	if(x == -1) {
								break;
							}
							
							if(id == apprumED->vet[x].info.id) {
								elemento = apprumED->vet[x].info;//removendo do meusappsED
								break;
							}
					    }			
						
						if(elemento.tam != -2) {
							removerL(apprumED, elemento, 2);					
						}
					}
				}        			
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

//funcao para 3(AppRumED) opcao do menu
void funAppRumED(LLDE *apprumED) {	
	char operacao;
	int pausa;
	int pagina = 15;
	
	//imprimindo interface rum
	while(1) {
			if(pagina == 15) {
			//imprimindo os 16 apps iniciais
			system("cls");
			telaAppRum();
			imprimirED(*apprumED);
		}
		
		//Recebendo operacao selecionada
		gotoxy(2,20);
		printf("Operacao:");
		scanf(" %c", & operacao);
		gotoxy(0, 50);
		
		switch(operacao) {
			case 'w':
				return;
 			break;
 			case 'q':
     			funRemo(apprumED, pagina, apprumED, 2, 2);
            break;
        	case ',':
				if(pagina != 15) {
					pagina--;
					system("cls");
					telaAppRum();
					imprimirED(*apprumED);
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
					system("cls");
					telaAppRum();
					imprimirEDpro(*apprumED);
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
	App storeED[T];
	LLDE meusappsED;
	LLDE apprumED;
	char operacao;
	int pausa;

	//iniciando as listas
	inicia(&meusappsED, 1);
	inicia(&apprumED, 2);
	
	//chamando a leitura do arquivo
	lerArq(storeED);

	while(1) {
		telaIni(meusappsED);
		
		//opcao de saida
		gotoxy(2, 28);
		printf("Para desligar o MobileED pressione ';'");
			
		//Recebendo operacao selecionada
		gotoxy(2,20);
		printf("Operacao:");
		scanf(" %c", & operacao);
		gotoxy(0, 50);
			
		switch(operacao) {
			case 'q'://StoreED
				funStoreED(storeED, &meusappsED);
	  		break;
		  	case 'w'://MeusAppsED
   	  		    funMeusappsED(&meusappsED, &apprumED);
			break;
			case 'e'://AppRumED
				funAppRumED(&apprumED);
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