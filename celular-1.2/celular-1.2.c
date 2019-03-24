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
void iniciaL() {
 	int x; 
 	
 	for(x = 0; x < 3 ; x++) {
		ControleL[x].IL = -1;	 
	    ControleL[x].FL = -1;
		ControleL[x].IA = 1;
		ControleL[x].FA = 30;			
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

//área de funções relacionadas a telas
void telaIni() {
	int x;
	
	system("cls");
	
	//verificando quantos apps estão instalados
			

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
	//imprimir os elementos do vetor						
	
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

//função para inserir um elemento
void inserirL(App StoreED[], int indice, int lista, App elemento) {
	int x;		
		
	//caso a lista já esteja cheia
	if((ControleL[lista].IL == ControleL[lista].IA) && (ControleL[lista].FL == ControleL[lista].FA)) {
		return;
	}else {
		if(ControleL[lista].IL == -1 && ControleL[0].FL == -1) {//lista estiver vazia
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

int main() {
	App StoreED[T];
	//App MeusAppsED[T];
	//App AppRumED[T];
	char operacao;
	int pausa;
	
	//iniciando as listas
	iniciaL(ControleL);		
	iniciaL(ControleL);
	iniciaL(ControleL);	
	
	//chamando a leitura do arquivo
	lerArq(StoreED);

	while(1) {
		telaIni();
		
		//opção de saida
		gotoxy(2, 28);
		printf("Para desligar o MobileED pressione ';'");
			
		//Recebendo operação selecionada
		gotoxy(2,20);
		printf("Operacao:");
		scanf(" %c", & operacao);
		gotoxy(0, 50);
			
		switch(operacao) {
			case 'q':
	
	  		break;
		  	case 'w':
	
			break;
			case 'e':
	
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