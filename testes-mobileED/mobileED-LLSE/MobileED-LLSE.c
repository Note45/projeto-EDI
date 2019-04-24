#include <stdio.h>
#include <stdlib.h>
#define MAX 6

typedef struct {
    int info;
    int prox;
} no;

typedef struct {
	int IL;
    no vet[MAX];
} LLSE;

int disp;

//liberando indice do vetor
void liberaNo(LLSE * lista, int ind) {
    lista->vet[ind].prox = disp;
    disp = ind;
}

//devolve onde eu vou inserir no vetor
int alocaNo(LLSE *lista) {
    int d;
    if(disp == -1) {
        return -3;//se a lista estiver cheia
    }
    d = disp;
    disp = lista->vet[disp].prox;
    return d;
}

//inicia a LLSE
void inicializar(LLSE *lista) {
    int i;
    disp = 1;
    for(i = 0; i < MAX; i++) {
        lista->vet[i].prox = i + 1;
        lista->vet[i].info = -2;
    }
    lista->vet[MAX - 1].prox = -1;
    lista->vet[MAX - 1].info = -2;
    lista->IL = 0;
}

void imprimir(LLSE lista) {
	int x;
	
	for(x = lista.IL; x < MAX; x = lista.vet[x].prox) {
		if(x == -1) {
			break;
		}
		
		printf("\n%d - Info: %d", x, lista.vet[x].info);
		printf("\t\t\tProx: %d", lista.vet[x].prox);
	}
	
	printf("\n\nDisponivel: %d\n", disp);
}

void inserir(LLSE *lista, int elemento) {
	int indice;
	int x;
	int posi;
	int ant;
	int pro;
	
	indice = alocaNo(lista);
	
	//se alista estiver cheia
	if(indice == -3) {
		printf("\n\nLista Cheia!\n\n");
		system("PAUSE");
	}
	
	//fazendo a primeira inserção na LLSE
	if(lista->vet[0].info == -2) {
		lista->vet[0].info = elemento;
		lista->vet[lista->IL].prox = -1;
		return;
	}
	
	//buscando em qual posição eu vou inserir meu elemento
	for(x = lista->IL; x < MAX; x = lista->vet[x].prox) {
		if(x == -1) {//parar quando chegar ao ultimo elemento da lista
			break;
		}
		
		if(elemento <= lista->vet[x].info && x == lista->IL) {//insetir no inicio
			posi = 1;
			break;
		}
		
		if(elemento >= lista->vet[x].info && lista->vet[x].prox == -1) {//inserir no final
			posi = 2;
			ant = x;
			break; //recebendo o indice do elemento ao qual o ultimo vai apontar
		}
		
		if(elemento >= lista->vet[x].info && elemento <= lista->vet[lista->vet[x].prox].info) {
			ant = x;//indice que deve ser o anterior ao elemento quando ele entrar na LLSE
			pro = lista->vet[x].prox; //para onde o elemento vai apontar
			break;
		}
	}
	
	//inserindo o elemento
	if(indice != -3) {//lista não vazia
		if(posi == 1) {//inicio
			lista->vet[indice].info = elemento;
			lista->vet[indice].prox = lista->IL;
			lista->IL = indice; 
		}else if(posi == 2) {//final
			lista->vet[indice].info = elemento;
			lista->vet[ant].prox = indice;
			lista->vet[indice].prox = -1;
		}else if(posi != 1 && posi != 2){//meio
			lista->vet[indice].info = elemento;
			lista->vet[indice].prox = pro;
			lista->vet[ant].prox = indice;
		}
	}
}

void removerL(LLSE *lista, int elemento) {
	int x;
	int liberar;
	int posi;
	int ant;
	int pro;
	
	//se a lista estiver vazia
	if(lista->vet[lista->IL].info == -2) {
		printf("Lista Vazia!\n");
		system("PAUSE");
	}
	
	//buscando qual no vou remover
	for(x = lista->IL; x < MAX; x = lista->vet[x].prox) {
		if(x == -1) {//parar quando chegar ao ultimo elemento da lista
			break;
		}
		
		if(elemento == lista->vet[x].info && x == lista->IL) {//remover no inicio
			posi = 1;
			break;
		}
		
		if(elemento == lista->vet[x].info && lista->vet[x].prox == -1) {//remover no final
			posi = 2;
			liberar = x;
			break; 
		}
		
		if(elemento == lista->vet[x].info) {
			posi = 3;
			pro = lista->vet[x].prox; //para onde o elemento vai apontar
			liberar = x;
			break;
		}
		
		ant = x;//recebendo o anterior ao atual
	}
	
	//removendo elemento
	if(posi == 1) {//remover no inicio
		liberar = lista->IL;//antigo inicio da lista
		lista->IL = lista->vet[liberar].prox;//novo inicio
		liberaNo(lista, liberar);//liberar antigo inicio
	}else if(posi == 3){//remover no meio
		lista->vet[ant].prox = pro;//anteririo ou liberado vai apontar para o proximo ao liberado
		liberaNo(lista, liberar); //liberar o No
	}else if(posi == 2){//remover no fim
		lista->vet[ant].prox = -1;//anterior vira o final
		liberaNo(lista, liberar);//liberando antigo final
	}
}

int main() {
	LLSE lista;
	int elemento;
	
	//iniciando a lista
	inicializar(&lista);
	
	while(1) {
		printf("\nDigite 1-inserir, 2-remover, 3-imprimir: ");
		scanf("%d", & elemento);
		
		switch(elemento) {
			case 1:
				printf("\nDigite o elemento: ");
				scanf("%d", & elemento);
				
				inserir(&lista, elemento);
				printf("\n");
			break;
			case 2:
				printf("\nDigite o elemento: ");
				scanf("%d", & elemento);
				
				removerL(&lista, elemento);
				printf("\n");
			break;
			case 3:
				imprimir(lista);
			break;			 
			default:
				printf("\nOperacao nao encontrada!\n\n");
				system("PAUSE");
		}
	}
		
	return 0;
}