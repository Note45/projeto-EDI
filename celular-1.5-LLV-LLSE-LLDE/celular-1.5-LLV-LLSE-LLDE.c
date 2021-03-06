#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>

#define T 30 //define o tanto de apps maximo
#define N 15 //define o tamanho do nome dos apps
#define L 3 //quantidade de elementos para a FILA

typedef struct {
	char nome[N];
	int tam;
	int id;
}App;

typedef struct {
    App info;
    int prox;
    int ante;
}noLLDE;

typedef struct {
    App info;
    int prox;
}noLLSE;

typedef struct {
	int IL;
	int FL;
    noLLDE vet[T];
}LLDE;

typedef struct {
	int quant;
	int IL;
	int FL;
    noLLDE vet[L];
}FILA;

typedef struct {
	int IL;
    noLLSE vet[T];
}LLSE;

typedef struct {
	int IL;
	int FL;
	int IA;
	int FA;
}Cont;

Cont ControleLLV;//variavel de controle da LLV

//disponivel LLDE, LLSE, FILA
int dispLLDE;
int dispLLSE;
int dispFILA;

FILA fila; //usada para instalacao de apps

//importando da funcao gotoxy
void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

//devolve onde eu vou inserir na LLDE
int alocaNoLLDE(LLDE *lista) {
    int d;
    if(dispLLDE == -1) {
        return -3;//se a lista estiver cheia
    }
    d = dispLLDE;
    dispLLDE = lista->vet[dispLLDE].prox;
    return d;
}

//devolve onde eu vou inserir na FILA
int alocaNoFILA(FILA *lista) {
    int d;
    if(dispFILA == -1) {
        return -3;//se a lista estiver cheia
    }
    d = dispFILA;
    dispFILA = lista->vet[dispFILA].prox;
    return d;
}

//onde vou inserir na LLSE
int alocaNoLLSE(LLSE *lista) {
    int d;
    if(dispLLSE == -1) {
        return -3;//se a lista estiver cheia
    }
    d = dispLLSE;
    dispLLSE = lista->vet[dispLLSE].prox;
    return d;
}

//liberando indice do vetor LLSE
void liberaNoLLSE(LLSE * lista, int ind) {
    lista->vet[ind].prox = dispLLSE;
    dispLLSE = ind;
}

//iniciando LLDE
void iniciaLLDE(LLDE *lista) {
    int i;
    dispLLDE = 0;
    
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

//iniciando FILA
void iniciaFILA(FILA *lista) {
    int i;
    dispFILA = 0;
    lista->quant = 0;
    
	for(i = 0; i < L; i++) {
        lista->vet[i].prox = i + 1;
        lista->vet[i].ante = i - 1;
        lista->vet[i].info.tam = -2;
        lista->vet[i].info.id = -2;
    }
    
    lista->vet[L - 1].prox = -1; 
    lista->vet[L - 1].info.tam = -2;
    lista->vet[L - 1].info.id = -2;
    lista->IL = 0;
    lista->FL = 0;
}

//Iniciando LLSE
void iniciaLLSE(LLSE *lista) {
    int i;
    dispLLSE = 1;
    
	for(i = 0; i < T; i++) {
        lista->vet[i].prox = i + 1;
        lista->vet[i].info.tam = -2;
        lista->vet[i].info.id = -2;
    }
    
    lista->vet[T - 1].prox = -1;
    lista->vet[T - 1].info.tam = -2;
    lista->vet[T - 1].info.id = -2;
    lista->IL = 0;
}

//buscando um app em uma LLV
int buscarLLV(App lista[], int id) {
	int x;
	
	for(x = ControleLLV.IL; x <= ControleLLV.FL; x++) {
		if(id == lista[x].id) {
			return x;
		}
	}
	
	x = -2;
	return x;
}

//funcao para inserir um em uma LLV
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

//inseirir um elemento na LLDE
void inserirLLDE(LLDE *lista, App elemento) {
	int indice;//recebe o indice disponivel
	int x;
	int posi = -1;
	int local = -1;

	indice = alocaNoLLDE(lista);
	
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
	
	//fazendo a primeira inserir na LLDE
	if(lista->vet[lista->IL].info.tam == -2) {
		lista->vet[lista->IL].info = elemento;
		lista->vet[lista->IL].prox = -1;
		return;
	}
	
	//buscando em qual posicao vou inserir meu elemento
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
				local = x;			
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
				local = lista->vet[x].prox;
				break;
			}
		}
	}
	
	//inserindo o elemento
	if(indice != -3) {//lista nao vazia
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
		}else if(local != -1){//meio
			lista->vet[indice].info = elemento;//recebendo elemento
			lista->vet[indice].prox = local;//proximo do elemento para o indice
			lista->vet[indice].ante = lista->vet[local].ante;//anterior do elemento recebendo o anterior da sua posi��o
			lista->vet[lista->vet[local].ante].prox = indice;//anterior recebe como proximo o indice que entra
			lista->vet[local].ante = indice;//proximo recebe como anterior o indice que entra
		}
	}
}

//inseirir um elemento na LLSE
void inserirLLSE(LLSE *lista, App elemento) {
	int indice;
	int x;
	int posi;
	int ant;
	int pro;
	
	indice = alocaNoLLSE(lista);
	
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
	
	//fazendo a primeira inserir na LLSE
	if(lista->vet[lista->IL].info.tam == -2) {
		lista->vet[lista->IL].info = elemento;
		lista->vet[lista->IL].prox = -1;
		return;
	}
	
	//buscando em qual posicao vou inserir meu elemento
	for(x = lista->IL; x < T; x = lista->vet[x].prox) {
		if(x == -1) {//parar quando chegar ao ultimo elemento da lista
			break;
		}
		
		if(elemento.tam <= lista->vet[x].info.tam && x == lista->IL) {//insetir no inicio
			posi = 1;
			break;
		}
		
		if(elemento.tam >= lista->vet[x].info.tam && lista->vet[x].prox == -1) {//inserir no final
			posi = 2;
			ant = x;
			break; //recebendo o indice do elemento ao qual o ultimo vai apontar
		}
		
		if(elemento.tam >= lista->vet[x].info.tam && elemento.tam <= lista->vet[lista->vet[x].prox].info.tam) {
			ant = x;//indice que deve ser o anterior ao elemento quando ele entrar na LLSE
			pro = lista->vet[x].prox; //para onde o elemento vai apontar
			break;
		}
	}
	
	//inserindo o elemento
	if(indice != -3) {//lista nao vazia
		if(posi == 1) {//inicio
			lista->vet[indice].info = elemento;//recebendo elemento inicial
			lista->vet[indice].prox = lista->IL;//apontando para proximo
			lista->IL = indice; //atualizando inicio
		}else if(posi == 2) {//final
			lista->vet[indice].info = elemento;//recebendo final
			lista->vet[ant].prox = indice;//anterior apontando para o final
			lista->vet[indice].prox = -1;//atualizando o final
		}else if(posi != 1 && posi != 2){//meio
			lista->vet[indice].info = elemento;//recebendo elemento
			lista->vet[indice].prox = pro;//apontando para o proximo
			lista->vet[ant].prox = indice;//anterior apontando para esse indice
		}
	}
}

//inseirir um elemento na FILA
App inserirFILA(FILA *lista, App elemento) {
	App temp;
	int indice;//recebe o indice disponivel

	if(lista->quant < 3) {
		lista->quant++;
		
		indice = alocaNoFILA(lista);
		
		//fazendo a primeira insercao na FILA
		if(lista->vet[lista->IL].info.tam == -2) {
			lista->vet[lista->IL].info = elemento;
			lista->vet[lista->IL].prox = -1;
			return elemento;
		}		

		lista->vet[indice].info = elemento;//recebendo final
		lista->vet[indice].ante = lista->FL;//anterior do elemento apontando para o antigo final da lista
		lista->vet[lista->FL].prox = indice;//proximo do antigo final da lista apontando para o novo FL
		lista->FL = indice;//atualizando o final da lista
		lista->vet[indice].prox = -1;//proximo do elemento = -1
		return elemento;
	}else {
		lista->quant = 3;
		
		temp = lista->vet[lista->IL].info;//recebendo o app que vai ser retornado para a intalacao no meusappdED
		lista->vet[lista->IL].info = lista->vet[lista->vet[lista->IL].prox].info;//1 recebendo o 2
		lista->vet[lista->vet[lista->IL].prox].info = lista->vet[lista->vet[lista->vet[lista->IL].prox].prox].info; //2 recebendo 3
		lista->vet[lista->vet[lista->vet[lista->IL].prox].prox].info = elemento;//3 recebendo o elemento enviado
		return temp;				
	}
}

//removendo um elemento da LLSE
void removerLLSE(LLSE *lista, App elemento) {
	int x;
	int liberar;
	int posi;
	int ant;
	int pro;
	
	//se a lista estiver vazia
	if(lista->vet[lista->IL].info.tam == -2) {
		printf("Lista Vazia!\n");
		system("PAUSE");
		return;
	}
	
	//buscando qual no vou remover
	for(x = lista->IL; x < T; x = lista->vet[x].prox) {
		if(x == -1) {//parar quando chegar ao ultimo elemento da lista
			break;
		}
		
		if(elemento.tam == lista->vet[x].info.tam && x == lista->IL) {//remover no inicio
			posi = 1;
			liberar = x;
			break;
		}
		
		if(elemento.tam == lista->vet[x].info.tam && lista->vet[x].prox == -1) {//remover no final
			posi = 2;
			liberar = x;
			break; 
		}
		
		if(elemento.tam == lista->vet[x].info.tam) {
			posi = 3;
			pro = lista->vet[x].prox; //para onde o elemento vai apontar
			liberar = x;
			break;
		}
		
		ant = x;//recebendo o anterior ao atual
	}
	
	//removendo elemento
	if(posi == 1) {//remover no inicio
		if(lista->vet[lista->IL].prox == -1) {//se o inicio for o final da lista
			lista->vet[liberar].info.tam = -2;
			lista->vet[liberar].info.id = -2;
			lista->IL = liberar;
			liberaNoLLSE(lista, liberar);
		}else {
			lista->IL = lista->vet[liberar].prox;
			liberaNoLLSE(lista, liberar);
		}		
		return;
	}else if(posi == 3){//remover no meio
		lista->vet[ant].prox = pro;//anteririo ou liberado vai apontar para o proximo ao liberado
		liberaNoLLSE(lista, liberar); //liberar o No
		return;
	}else if(posi == 2){//remover no fim
		lista->vet[ant].prox = -1;//anterior vira o final
		liberaNoLLSE(lista, liberar);//liberando antigo final
		return;
	}
}

//removendo um elemento da LLDE
void removerLLDE(LLDE *lista, App elemento) {
	int x;
	int posi;
	int local = -2;
	
	//se a lista estiver vazia
	if(lista->vet[lista->IL].info.tam == -2) {
		printf("Lista Vazia!\n");
		system("PAUSE");
		return;
	}
	
	//buscando em qual posicao eu vou remover o elemento
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
				local = x;
				posi = 4;			
				break;
			}
		}
	}
	
	//removendo elemento
	if(posi == 1) {//remover no inicio 
		lista->vet[dispLLDE].ante = lista->IL;//anterior do disponivel recebe o IL
		lista->IL = lista->vet[lista->IL].prox;//IL recebe o seu proximo como novo IL
		lista->vet[lista->IL].ante = -1;//anterior do novo IL recebe -1
		lista->vet[lista->vet[dispLLDE].ante].prox = dispLLDE;//antigo IL recebe como proximo o disponivel
		dispLLDE = lista->vet[dispLLDE].ante;//antigo IL se torna o novo disponivel
		return;
	}else if(posi == 2){//remover no fim
		lista->vet[dispLLDE].ante = lista->FL;//anterior do disponivel = atual FL
		lista->FL = lista->vet[lista->FL].ante;//FL recebe o anteror do atual FL
		lista->vet[lista->FL].prox = -1;//proximo do FL = -1
		lista->vet[lista->vet[dispLLDE].ante].ante = -1;//anterior do antigo FL recebe -1
		lista->vet[lista->vet[dispLLDE].ante].prox = dispLLDE;//proximo do antigo FL = atual disponivel
		dispLLDE = lista->vet[dispLLDE].ante;//antigo final da lista vira o disponivel
		return;
	}else if(posi == 3){//removendo a unica informa��o da lista
		lista->vet[lista->IL].info.tam = -2;//zerando o elemento
		lista->vet[dispLLDE].ante = lista->IL;//anterior do disponivel recebe FL ou IL
		lista->vet[lista->vet[dispLLDE].ante].prox = dispLLDE;//antigo IL o FL recebe como proximo o disponivel
		dispLLDE = lista->vet[dispLLDE].ante;//disponivel recebe como anterior o antigo IL ou FL da lista
		return;
	}else if(posi == 4){//removendo no meio
		lista->vet[lista->vet[local].ante].prox = lista->vet[local].prox;//anterior aponta para o proximo do removido
		lista->vet[lista->vet[local].prox].ante = lista->vet[local].ante;//proximo do removido aponta para o anterior
		lista->vet[local].ante = -1;//anterior do removido recebe -1
		lista->vet[local].prox = dispLLDE;//proximo do removido recebe atual disponivel
		lista->vet[dispLLDE].ante = local;//anterior do atual disponivel recebe removido
		dispLLDE = local;//removido vira atual disponivel
		return;
	}
}

//funcoes para imprimir apps
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

void imprimirLLSE(LLSE lista) {
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


void imprimirLLSEpro(LLSE lista) {
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

void imprimirLLDE(LLDE lista) {
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

void imprimirLLDEpro(LLDE lista) {
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
void telaPILHA() {
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
	
	//espa�amentos superiores
	for(x = 2; x < 42; x++) {
		gotoxy(x, 19);
		printf("%c", 219);
	}
	
	for(x = 2; x < 42; x++) {
		gotoxy(x, 21);
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
	
	//PILHA
	for(x = 1; x < 19; x++) {//divisoris verticais
		gotoxy(13, x);
		printf("%c", 219);
		gotoxy(29, x);
		printf("%c\n", 219);
	}
	
	//divisorias horizintais
	for(x = 14; x < 29; x++) {
		gotoxy(x, 5);
		printf("%c", 219);
	}
	
	for(x = 14; x < 29; x++) {
		gotoxy(x, 10);
		printf("%c", 219);
	}
	
	for(x = 14; x < 29; x++) {
		gotoxy(x, 15);
		printf("%c", 219);
	}
		
	//comandos da tela
	gotoxy(2, 23);
	printf("q-Adicionar\n\n\n");
	
	gotoxy(16, 23);
	printf("w-Remover\n\n\n");
	
	gotoxy(32, 23);
	printf("e-Sair\n\n\n");
}

void telaFila(FILA estrutura){
	int x; 
	
	//tela de instalacao fila
	for(x = 50; x < 80; x++) {//topo
		gotoxy(x, 3);
		printf("%c", 219);
	}
	
	//laterais
	for(x = 4; x < 8; x++) {
		gotoxy(50, x);
		printf("%c", 219);
	}
	
	for(x = 4; x < 8; x++) {
		gotoxy(79, x);
		printf("%c", 219);
	}
	
	//divisorias
	for(x = 4; x < 8; x++) {
		gotoxy(59, x);
		printf("%c", 219);
	}
	
	for(x = 4; x < 8; x++) {
		gotoxy(69, x);
		printf("%c", 219);
	}
	
	//imprimindo nome dos apps
	if(estrutura.quant != 0) {
		if(estrutura.quant >= 1) {
			gotoxy(53, 5);
			printf("%c%c%c", estrutura.vet[0].info.nome[0], estrutura.vet[0].info.nome[1], estrutura.vet[0].info.nome[2]);	
		}
		if(estrutura.quant >= 2) {
			gotoxy(62, 5);
			printf("%c%c%c", estrutura.vet[1].info.nome[0], estrutura.vet[1].info.nome[1], estrutura.vet[1].info.nome[2]);	
		}
		if(estrutura.quant == 3) {
			gotoxy(72, 5);
			printf("%c%c%c", estrutura.vet[2].info.nome[0], estrutura.vet[2].info.nome[1], estrutura.vet[2].info.nome[2]);	
		}		
	}
	
	//em baixo
	for(x = 50; x < 80; x++) {
		gotoxy(x, 8);
		printf("%c", 219);
	}
	
	gotoxy(50, 9);
	printf("-Apps em FILA para a operacao-");
}

void telaIni(LLSE lista) {
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

	//Area da tela do app PILHA
	gotoxy(3, 5);
	printf("App PILHA");	
	gotoxy(3, 9);
	printf("a - Iniciar");
	
			
	//imprimindo apps iniciais
	if(lista.vet[lista.IL].info.tam != -2) {			
		if(lista.vet[vet[0]].info.tam != -2 && vet[0] != -2) {
			gotoxy(16, 3);
			printf("Nome:");	
			gotoxy(17, 4);
			printf("%s", lista.vet[vet[0]].info.nome);
			gotoxy(16, 5);
			printf("Tamanho:");
			gotoxy(17, 6);
			printf("%d MB", lista.vet[vet[0]].info.tam);
			gotoxy(16, 7);
			printf("Id:");
			gotoxy(17, 8);
			printf("%d", lista.vet[vet[0]].info.id);
		}											
			
		if(lista.vet[vet[1]].info.tam != -2 && vet[1] != -2) {
			gotoxy(30, 3);
			printf("Nome:");	
			gotoxy(31, 4);
			printf("%s", lista.vet[vet[1]].info.nome);
			gotoxy(30, 5);
			printf("Tamanho:");
			gotoxy(31, 6);
			printf("%d MB", lista.vet[vet[1]].info.tam);
			gotoxy(30, 7);
			printf("Id:");
			gotoxy(31, 8);
			printf("%d", lista.vet[vet[1]].info.id);			
		}											
		
		if(lista.vet[vet[2]].info.tam!= -2 && vet[2] != -2) {
			gotoxy(2, 12);
			printf("Nome:");	
			gotoxy(3, 13);
			printf("%s", lista.vet[vet[2]].info.nome);
			gotoxy(2, 14);
			printf("Tamanho:");
			gotoxy(3, 15);
			printf("%d MB", lista.vet[vet[2]].info.tam);
			gotoxy(2, 16);
			printf("Id:");
			gotoxy(3, 17);
			printf("%d", lista.vet[vet[2]].info.id);
		}
	
				
		if(lista.vet[vet[3]].info.tam != -2 && vet[3] != -2) {
			gotoxy(16, 12);
			printf("Nome:");	
			gotoxy(17, 13);
			printf("%s", lista.vet[vet[3]].info.nome);
			gotoxy(16, 14);
			printf("Tamanho:");
			gotoxy(17, 15);
			printf("%d MB", lista.vet[vet[3]].info.tam);
			gotoxy(16, 16);
			printf("Id:");
			gotoxy(17, 17);
			printf("%d", lista.vet[vet[3]].info.id);
		}											
			
		if(lista.vet[vet[4]].info.tam != -2 && vet[4] != -2) {
			gotoxy(30, 12);
			printf("Nome:");	
			gotoxy(31, 13);
			printf("%s", lista.vet[vet[4]].info.nome);
			gotoxy(30, 14);
			printf("Tamanho:");
			gotoxy(31, 15);
			printf("%d MB", lista.vet[vet[4]].info.tam);
		   	gotoxy(30, 16);
			printf("Id:");
			gotoxy(31, 17);
			printf("%d", lista.vet[vet[4]].info.id);			
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

//funcao de remover um app
void funRemo(LLSE *remove, LLDE *apprumED, int pagina, int chamada) {
	int id = -1;
	int x;
	App elemento;
	
	if(chamada == 0) {
		if(remove->vet[remove->IL].info.tam == -2) {//lista vazia
			gotoxy(12, 20);
			printf("-Nenhum app intalado!");	
			gotoxy(2, 28);
			system("PAUSE");	
			return;	
		}
	}else {
		if(apprumED->vet[apprumED->IL].info.tam == -2) {//lista vazia
			gotoxy(12, 20);
			printf("-Nenhum app rodando!");	
			gotoxy(2, 28);
			system("PAUSE");	
			return;	
		}		   	
	}
	
	//zerando elemento
	elemento.tam = -2;
	elemento.id = -2;
	
	while(1) {//imprimindo tela de onde foi chamado
		if(pagina == 15) {
			system("cls");
			if(chamada == 0) {
				telaMeusappED();
				imprimirLLSE(*remove);	
			}else if(chamada == 1) {
				telaAppRum();
				imprimirLLDE(*apprumED);
			}
		}else {
			system("cls");
			if(chamada == 0) {
				telaMeusappED();
				imprimirLLSEpro(*remove);		
			}else if(chamada == 1) {
				telaAppRum();
				imprimirLLDEpro(*apprumED);
			}
		}	

		//Recebendo o id
		gotoxy(2,20);
		printf("Id:");
		scanf("%d", & id);
		gotoxy(0, 50);	
		
		if(chamada == 0) {//checando se e um indice valido
		    for(x = remove->IL; x < T; x = remove->vet[x].prox) {
		    	if(x == -1) {
					break;
				}
				
				if(id == remove->vet[x].info.id) {
					elemento = remove->vet[x].info;//removendo do meusappsED
					break;
				}
		    }
		}else {			
		    for(x = apprumED->IL; x < T; x = apprumED->vet[x].prox) {
		    	if(x == -1) {
					break;
				}
				
				if(id == apprumED->vet[x].info.id) {
					elemento = apprumED->vet[x].info;//removendo do meusappsED
					break;
				}
		    }			
		}			
		
		if(elemento.tam != -2) {
			if(chamada == 0) {
				removerLLSE(remove, elemento);//removendo do MeusappsED
				
				if(apprumED->vet[apprumED->IL].info.tam != -2) {//removendo app se ele estiver rodando
					elemento.tam = -2;
					elemento.id = -2;
					
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
						removerLLDE(apprumED, elemento);
						return;
					}else {
						gotoxy(5, 20);
						printf("-Erro ao parar o app!");	
						gotoxy(2, 28);
						system("PAUSE");
					}
				}					
	      	    return;				
			}else {//se for chamada de AppRumED
				if(elemento.tam != -2) {
					removerLLDE(apprumED, elemento);
					return;
				}else {
					gotoxy(5, 20);
					printf("-Erro ao parar o app!");	
					gotoxy(2, 28);
					system("PAUSE");
				}				
			}	
      	    return;												
		}else {
			gotoxy(5, 20);
			printf("-Aplicativo nao encontrado");	
			gotoxy(2, 28);
			system("PAUSE");
			return;	
		}
	}
}

//funcao para rodar um app
void funRum(LLSE meusappsED, LLDE *apprumED, int pagina) {
	int x;
	int id;
	App elemento;
	
	//zerando elemento e temp
	elemento.tam = -2;
	elemento.id = -2;
	
	//se a LLDE estiver cheia
	if(dispLLDE == -1) {
		gotoxy(5, 20);
		printf("-Memoria Cheia");
		gotoxy(2, 28);
		system("PAUSE");
	   	return;	
	}
	
	if(pagina == 15) {
	   	//imprimindo os 16 apps iniciais
		system("cls");
		telaMeusappED();
		imprimirLLSE(meusappsED);
	}else {
		system("cls");
		telaMeusappED();
	    imprimirLLSEpro(meusappsED);
	}
	
	//Recebendo id selecionado
	gotoxy(2,20);
	printf("Id:");
	scanf("%d", & id);
	gotoxy(0, 50);
	
	if(apprumED->vet[apprumED->IL].info.tam != -2) {//vendo se o app ja foi iniciados
	    for(x = apprumED->IL; x < L; x = apprumED->vet[x].prox) {
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
    
    //buscando qual elemento vou instalar  
	for(x = meusappsED.IL ; x < T; x = meusappsED.vet[x].prox) {
    	if(x == -1) {
			break;
		}
		
		if(id == meusappsED.vet[x].info.id) {
			elemento = meusappsED.vet[x].info;
			break;
		}
    }		
    
    if(elemento.tam != -2) {
		inserirLLDE(apprumED, elemento);
		return;		
	}else {
		gotoxy(5, 20);
		printf("-Erro na busca do app!");
		gotoxy(2, 28);
		system("PAUSE");
		return;
	}		
	return;	
}

//funcao para intalacao de apps na LLSE(MyappsED)
void funInstaLLSE(App storeED[], LLSE *meusappsED, int pagina) {
	int id = -2;
	int x;
	App elemento;
	App temp;
	
	//zerando elemento
	elemento.tam = -2;
	elemento.id = -2;
	
	//se a lista estiver cheia
	if(dispLLSE == -1) {
		gotoxy(5, 20);
		printf("-Memoria Cheia");
		gotoxy(2, 28);
		system("PAUSE");
	   	return;	
	}
	
	while(1) {	
		if(pagina == 15) {
		   	//imprimindo os 16 apps iniciais
			system("cls");
			telaStoreED();
			imprimirLVVed(storeED, 0);
		}else {
			system("cls");
			telaStoreED();
		    imprimirLVVed(storeED, 1);
		}	
	
		//tela FILA
		telaFila(fila);	  		  		
	
		//Recebendo id selecionado
		gotoxy(2,20);
		printf("Id:");
		scanf("%d", & id);
		gotoxy(0, 50);
		
		if(fila.vet[fila.IL].info.tam != -2) {//vendo se o app ja foi instalado
		    for(x = fila.IL; x < L; x = fila.vet[x].prox) {
		    	if(x == -1) {
					break;
				}		    	
		    	
				if(id == fila.vet[x].info.id) {
					gotoxy(5, 20);
					printf("-Aplicativo ja selecionado");
					gotoxy(2, 28);
					system("PAUSE");
					return;	
				}
		    }
		}			
	    
	    //buscando qual elemento vou instalar
	    x = -2;
		x = buscarLLV(storeED, id);
	    
	    if( x != -2) {
			elemento = storeED[x];
		}else {
			gotoxy(5, 20);
			printf("-Erro na busca do app!");
			gotoxy(2, 28);
			system("PAUSE");
			break;
		}
		
		//colocando app na FILA de instalacao
		if(fila.quant < 3) {
			inserirFILA(&fila, elemento);
			return;
		}else {//se um quarto elemento for instalado o primeiro vai para a LLSE
			temp = inserirFILA(&fila, elemento);
			inserirLLSE(meusappsED, temp);
			return;
		}			
	}
	return;
}	

//funcoes PILHA do menu
void funPilhaED() {
	char operacao;
	int pausa;
	int quantidade = 0;
	
	while(1) {
		telaPILHA();//tela do app PILHA
		
		//imprimindo elementos da pilha
		if(quantidade >= 1) {
			gotoxy(17, 17);
			printf("Elemento 1");
			gotoxy(28,28);
		}
		if(quantidade >= 2) {
			gotoxy(17, 13);
			printf("Elemento 2");
			gotoxy(28,28);
		}
		if(quantidade >= 3) {
			gotoxy(17, 7);
			printf("Elemento 3");
			gotoxy(28,28);
		}
		if(quantidade >= 4) {
			gotoxy(17, 3);
			printf("Elemento 4");
			gotoxy(28,28);
		}		
			  		
		//opera��o selecionada
		gotoxy(2,20);
		printf("Operacao:");
		scanf(" %c", & operacao);
		gotoxy(0, 50);
		
		switch(operacao) {
			case 'q'://adicionar elemento a pilha
				if(quantidade == 4) {
	        		gotoxy(12, 20);
	  				printf(" - Pilha cheia!\n");
	  				pausa = 0;
	  				while(pausa < 9) {
						  printf("\n");
						  pausa++;
					}
					system("PAUSE");					
				}else {
					quantidade++;	
				}	
 			break;
 			case 'w'://removr elemento da pilha
				if(quantidade == 0) {
	        		gotoxy(12, 20);
	  				printf(" - Pilha vazia!\n");
	  				pausa = 0;
	  				while(pausa < 9) {
						  printf("\n");
						  pausa++;
					}
					system("PAUSE");					
				}else {
					quantidade--;	
				}						
            break;
        	case 'e':
        		return;
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

//funcao para 1(StoreED) opcao do menu
void funStoreED(App storeED[], LLSE *meusappsED) {	
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

		//imprimindo fila de instalacao
		telaFila(fila);
			
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
     			funInstaLLSE(storeED, meusappsED, pagina);
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

//funcao para 2(MeusappsEd) opcao do menu
void funMeusappsED(LLSE *meusappsED, LLDE *apprumED) {
	char operacao;
	int pausa;
	int pagina = 15;
	
	//imprimindo interface
	while(1) {		
		if(pagina == 15) {
			//imprimindo os 16 apps iniciais
			system("cls");
			telaMeusappED();
			imprimirLLSE(*meusappsED);	
		}
				
		//recebendo operacao selecionada
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
					imprimirLLSE(*meusappsED);
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
					imprimirLLSEpro(*meusappsED);
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
				funRum(*meusappsED, apprumED, pagina);
            break;
        	case 'w'://removendo elemento
    			funRemo(meusappsED, apprumED, pagina, 0);
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
void funAppRumED(LLSE *meusappsED ,LLDE *apprumED) {	
	char operacao;
	int pausa;
	int pagina = 15;
	
	//imprimindo interface rum
	while(1) {
		if(pagina == 15) {
			//imprimindo os 16 apps iniciais
			system("cls");
			telaAppRum();
			imprimirLLDE(*apprumED);
		}else {
			system("cls");
			telaAppRum();
			imprimirLLDEpro(*apprumED);
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
 			case 'q'://parar a instancia de um app
     			funRemo(meusappsED, apprumED, pagina, 1);
            break;
        	case ',':
				if(pagina != 15) {
					pagina--;
					system("cls");
					telaAppRum();
					imprimirLLDE(*apprumED);
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
					imprimirLLDEpro(*apprumED);
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
	LLSE meusappsED;
	LLDE apprumED;
	char operacao;
	int pausa;

	//iniciando LLSE e LLDE
	iniciaLLSE(&meusappsED);
	iniciaLLDE(&apprumED);
	iniciaFILA(&fila);
	
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
				funAppRumED(&meusappsED, &apprumED);
			break;
			case 'a'://App PILHA
				funPilhaED();
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