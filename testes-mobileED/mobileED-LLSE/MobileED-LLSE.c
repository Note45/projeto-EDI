#include <stdio.h>
#define MAX 20

typedef struct {
    int info;
    int prox;
} no;

typedef struct {
    no vet[MAX];
} LLSE;

int disp; 

void inicializar(LLSE * lista) {
    int i;
    disp = 1;
    for(i = 0; i < 5; i++) {
        lista->vet[i].prox = i + 1;
        lista->vet[i].info = -10;
    }
    lista->vet[0].prox = -5;
    lista->vet[5].prox = -1;
    lista->vet[5].info = -10;
}

int alocaNo(LLSE * lista) {
    int d;
    if(disp == -1) {
        return 0;
    }
    d = disp;
    disp = lista->vet[disp].prox;
    return d;
}

void inserir(LLSE * lista, int local, int pos, int info) {
    int d = alocaNo(lista);
    
	lista->vet[d].info = info;
    
	if(d != 0) {
        if(local == 1) {
            lista->vet[d].prox = lista->vet[0].prox;
            lista->vet[0].prox = d;
        } else if(local == 2) {
            int i;
            
			i = lista->vet[0].prox;
            while(lista->vet[i].prox != -5) {
                i = lista->vet[i].prox;
            }
            lista->vet[d].prox = lista->vet[i].prox;
            lista->vet[i].prox = d;
        } else {
            int i;
            int cont;
            i = lista->vet[0].prox;
            cont =  1;
            while(cont < pos) {
                i = lista->vet[i].prox;
                cont++;
            }
            lista->vet[d].prox = lista->vet[i].prox;
            lista->vet[i].prox = d;
        }
    }
}

void liberaNo(LLSE * lista, int ind) {
    lista->vet[ind].prox = disp;
    disp = ind;
}

void remover(LLSE * lista, int local, int pos) {
    int atual;
    if(local == 1) {
        atual = lista->vet[0].prox;
        lista->vet[0].prox = lista->vet[atual].prox;
        liberaNo(lista, atual);
    } else if(local == 2) {
        int i;
        i = lista->vet[0].prox;
        while(lista->vet[lista->vet[i].prox].prox != -5) {
            i = lista->vet[i].prox;
        }
        atual = lista->vet[i].prox;
        lista->vet[i].prox = lista->vet[atual].prox;
        liberaNo(lista, atual);
    } else {
        int i;
        int cont;
        cont = 1;
        i = lista->vet[0].prox;
        while(cont < pos) {
            i = lista->vet[i].prox;
            cont++;
        }
        atual = lista->vet[i].prox;
        lista->vet[i].prox = lista->vet[atual].prox;
        liberaNo(lista, atual);
    }
}

void imprimirL(LLSE lista) {
	int x;

	printf("\nControle:\n");
	printf("0 - Info: %d", x, lista.vet[0].info);
	printf("\t\tProx: %d\n\n", lista.vet[0].prox);
	
	//imprimindo a lista
	for(x = 1; x <= 5; x++) {
		printf("%d - Info: %d", x, lista.vet[x].info);
		printf("\t\tProx: %d\n", lista.vet[x].prox);
	}
	printf("\n\t Disponivel:%d\n", disp);
}

int buscar(LLSE lista, int elemento) {
	int x;

	if(disp == 1) {
		return 1;
	}
	
	for(x = 1; lista.vet[x].prox >= -5; x ++) {
		if(elemento >= lista.vet[x].info) {
			return x;
		}
	}
	
	return x;
}

int main () {
	LLSE lista;
	int opera;
	int elemento;
	int pos  = -1;
	
	//inicializando a lista
	inicializar(&lista);
	
	while(1) {
		//imprimindo a lista
		system("cls");
		imprimirL(lista);
		
		//recebendo a escolha do usuario
		printf("\nDigite uma opercao[1 - inserir][2 - remover]:");
		scanf("%d", & opera);
		
		switch(opera) {
			case 1:
				printf("\nDigite o elemento para inserir:");
				scanf(" %d", & elemento);
				
				//procurando onde vou adicionar
				pos = buscar(lista, elemento);
				
				//inserindo o elemento
				if(pos == 1) {
					inserir(&lista, 1, pos, elemento);
				}else if(pos != 1 && pos != disp) {
					inserir(&lista, 2, pos, elemento);
				}else {
					inserir(&lista, 3, pos, elemento);
				}	
            break;
        	case 2:
        	break;	
			default:
				printf("Operacao nao encontrada!\n");
		}
		
	}
	
	return 0;
}