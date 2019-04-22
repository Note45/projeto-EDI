#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

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
}no;

typedef struct {
	int IL;
    no vet[T];
}LLSE;

//importando da função gotoxy
void gotoxy(int x, int y){
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1});
}

//devolve onde eu vou inserir na lista
int alocaNo(LLSE *lista, int *disp) {
    int d;
    if(*disp == -1) {
        return -3;//se a lista estiver cheia
    }
    d = *disp;
    *disp = lista->vet[*disp].prox;
    return d;
}

//iniciando listas
void inicia(LLSE *lista, int *disp) {
    int i;
    *disp = 1;
    
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

//inseirir um elemento na lista
void inserirL(LLSE *lista, App elemento, int *disp) {
	int indice;
	int x;
	int posi;
	int ant;
	int pro;
	
	indice = alocaNo(lista, disp);
	
	//se alista estiver cheia
	if(indice == -3) {
		gotoxy(10, 20);
		printf(" Memoria Cheia");
		x = 0;
		while(x < 9) {
			  printf("\n");
			  x++;
		  }
		system("PAUSE");
	}
	
	//fazendo a primeira inserção na LLSE
	if(lista->vet[0].info.tam == -2) {
		lista->vet[0].info = elemento;
		lista->vet[lista->IL].prox = -1;
		return;
	}
	
	//buscando em qual posição eu vou inserir meu elemento
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
	if(indice != -3) {//lista não vazia
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
	
	/*
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
	*/
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
		
	/*	
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
	*/	
}

//área de funções relacionadas a telas
void telaIni() {
	int x;
	int quant;
	
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
	
	/*imprimindo apps iniciais
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
	*/		
							
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

//função para ler o arquivo
void lerArq(LLSE *storeED, int *disp) {
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
		
		//inserindo elemento
		inserirL(storeED, elemento, disp);
			
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
	if(0) {
		while(1) {
			if(pagina == 15) {
				system("cls");
				telaMeusappED();
			}else {
				system("cls");
				telaMeusappED();
			}	
	
			//Recebendo o id
			gotoxy(2,20);
			printf("Id:");
			scanf("%d", & id);
			gotoxy(0, 50);	
			
			//checando se é um indice valido
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
	if(0) {
		while(1) {
			if(pagina == 15) {
				system("cls");
				telaAppRum();
			}else {
				system("cls");
				telaAppRum();
			}	
	
			//Recebendo o id
			gotoxy(2,20);
			printf("Id:");
			scanf("%d", & id);
			gotoxy(0, 50);	
			
			//checando se é um indice valido
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
		
		//Recebendo id selecionado
		gotoxy(2,20);
		printf("Id:");
		scanf("%d", & id);
		gotoxy(0, 50);
				
		//vendo se o app ja foi instalado
	}
}

//função para rodar apps
void funRumED(App myapps[], int quant, App rum[], int pagina) {
	int id = 0;
	int x;
	int local = 0;//recebe quanto apps estão rodando
	
	if(0) {
		while(1) {
			if(pagina == 15) {
				system("cls");
				telaMeusappED();
				//imprimindo apps
			}else {
				system("cls");
				telaMeusappED();
				//impimindo apps
			}	
	
			//Recebendo id do app
			gotoxy(2,20);
			printf("Id:");
			scanf("%d", & id);
			gotoxy(0, 50);
			
			//verificando se o id e valido
						
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
	int quant;
	
	//imprimindo interface StoreED
	while(1) {
		if(pagina == 15) {
			//imprimindo os 16 apps iniciais
			telaStoreED();
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
     			
            break;
        	case ',':
				if(pagina != 15) {
					pagina--;
					telaStoreED();
					//imprimir pagina anterior
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
				    //imprimir proxima pagina  
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
	int quant;
	
	//imprimindo interface
	while(1) {
		//contando a quantidade de apps caso um seja removido
		
		if(pagina == 15) {
			//imprimindo os 16 apps iniciais
			telaMeusappED();
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
					//imprimir pagina anterior
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
					//imprimir proxima pagina
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
     			
            break;
        	case 'w':
        		
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
	int quant;
	
	//imprimindo interface rum
	while(1) {
		//recebendo novo quant caso algum app seja removido
		
		if(pagina == 15) {
			//imprimindo os 16 apps iniciais

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
     			
            break;
        	case ',':
				if(pagina != 15) {
					pagina--;
					telaAppRum();
					//imprimir pagina anterior
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
					//imprimir proxima pagina
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
	LLSE storeED;
	LLSE meusappsED;
	LLSE apprumED;
	int disp[L];//controla quem esta disponivel nas listas
	char operacao;
	int pausa;

	//iniciando as listas
	inicia(&storeED, &disp[0]);
	inicia(&meusappsED, &disp[1]);
	inicia(&apprumED, &disp[2]);
	
	//chamando a leitura do arquivo
	lerArq(&storeED, &disp[0]);

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
			case 'q'://StoreED
				
	  		break;
		  	case 'w'://MeusAppsED
   	  		   
			break;
			case 'e'://AppRumED
				
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