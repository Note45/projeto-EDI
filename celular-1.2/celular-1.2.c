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
	int IL;
	int FL;
	int IA;
	int FA;
}App;

//importando da fun��o gotoxy
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

//fun��o para iniciar a lista do vetor
void iniciaV(App vet[]) {
 	vet[0].IL = -1;
 	vet[0].FL = -1;
 	vet[0].IA = 1;
 	vet[0].IL = 30;
}

//fun��o para checar o indice onde pode ser adiciondo
int checargemInd(App aplicativos[],int tam, App adicionar) {
	int x;
	
	for(x = 0; x < tam; x++) {
		if(adicionar.tam < aplicativos[x].tam || aplicativos[x].tam == 0) {
			return x;
		}
	} 
	return x;
}

//fun��o para adicionar ordenar o elemento
void addOrd(App aplicativos[], int tam, App adicionar) {
	int x;
	int pos = checargemInd(aplicativos, T, adicionar);//encontrando onde devo adcionar

	//ordenando para no final adicionar	
	for(x = tam; x > pos; x--) {
		aplicativos[x] = aplicativos[x - 1];
	} 	
	aplicativos[pos] = adicionar;
}

//fun��o para ler o arquivo
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
	
	//ordenando e adicionando at� o final do arquivo
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
void telaIni(App MyappsIni[]) {
	int x;
	
	system("cls");
	
	//verificando quantos apps est�o instalados
			

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

//interface da 2(MeusAppsED) op��o do menu
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

//interface da 1(vstore) op��o do menu
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

//tela da fun��o AppRumED
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

//tela da fun��o Insta
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

//fun��o para imprimir app
void imprimirED(App aplicativos[], int quant) {
	int x;
	
	//complementando a interface para StoreEd
	gotoxy(2, 2);
	printf("Nome:");
	gotoxy(15, 2);
	printf("Tamanho:");
	gotoxy(29, 2);
	printf("Id:");
		
	for(x = 2; x <= quant; x++) {
		gotoxy(2, x + 1);
		printf("%s", aplicativos[x - 2].nome);
		gotoxy(18, x + 1);
		printf("%d MB",aplicativos[x - 2].tam);
		gotoxy(32, x + 1);
		printf("%d", aplicativos[x - 2].id);
	}	
}

//fmprimindo proximas paginas
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
		
	for(x = inicio - 1; x < quant; x++) {
		gotoxy(2, y);
		printf("%s", aplicativos[x].nome);
		gotoxy(18, y);
		printf("%d MB",aplicativos[x].tam);
		gotoxy(32, y);
		printf("%d", aplicativos[x].id);
		y++;
	}	
}


//fun��o para intala��o de apps
void funInsta(App aplicativos[], int quant, App myapps[], int pagina, App Myapps_Ini[]) {
	int id = 0;
	int q = -1;
	int x;
	int y;
	int z = 0;
	int insta = 0;//recebe quanto apps est�o instalados
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
		
		//recebendo quantos apps est�o instalados na tela inicial

		
		//Recebendo opera��o selecionada
		gotoxy(2,20);
		printf("Id:");
		scanf("%d", & id);
		gotoxy(0, 50);
		
		//vendo se o app ja foi instalado
		for(x = 0; x < quant; x++) {
			if(myapps[x].id == id){
				gotoxy(5, 20);
				printf("-Aplicativo instalado/nao encontrado");
				gotoxy(2, 28);
				system("PAUSE");
				return;
			}			
		}
		
		//procurando o indice referete a esse id
		for(x = 0; x < quant; x++) {
			if(aplicativos[x].id == id) {			
				//recebendo a quantidade de apps istalados
				insta = quantApp(myapps);
	  				
	  			//recebendo o elemento com base no id
	  			elemento = aplicativos[x];
					
				addOrd(myapps, insta, elemento);
				
				//adicionando app ao vetor da tela inicial se ouver espa�o
  
				return;	
			}
		}			
		
		//caso o id n�o seja encontrado
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
			
			//vendo se o app ja foi instalado
			for(x = 0; x < quant; x++) {
				if(myapps[x].id == id){
					gotoxy(5, 20);
					printf("-Aplicativo instalado/nao encontrado");
					gotoxy(2, 28);
					system("PAUSE");
					return;
				}			
			}			
				
			for(x = 0; x < quant; x++) {
				if(aplicativos[x].id == id) {
					//recebendo a quantidade de apps istalados
	  				insta = quantApp(myapps);
	  				
	  				//recebendo o elemento com base no id
	  				elemento = aplicativos[x];
					
					addOrd(myapps, insta, elemento);

					//adicionando app ao vetor da tela inicial se ouver espa�o
  										   
					return;						
				}
			}			
		}		
	}
}

//fun��o para rodar apps
void funRumED(App myapps[], int quant, App rum[], int pagina) {
	int id = 0;
	int x;
	int rodando = 0;//recebe quanto apps est�o instalados
	App elemento;//recebe o elemento a ser ordenado
	
	while(1) {
		if(pagina == 15) {
			system("cls");
			telaMeusappED();
			imprimirED(myapps, quant + 1);
		}else {
			system("cls");
			telaMeusappED();
			imprimirEDpro(myapps, quant, pagina);
		}	

		//Recebendo opera��o selecionada
		gotoxy(2,20);
		printf("Id:");
		scanf("%d", & id);
		gotoxy(0, 50);
		
		//vendo se o app ja est� rodando
		for(x = 0; x < quant; x++) {
			if(rum[x].id == id){
				gotoxy(5, 20);
				printf("-Aplicativo rodando/nao encontrado");
				gotoxy(2, 28);
				system("PAUSE");
				return;
			}			
		}	
			
		//procurando o indice referete a esse id
		for(x = 0; x < quant; x++) {
			if(myapps[x].id == id) {
				//recebendo a quantidade de apps istalados
  				rodando = quantApp(rum);
  				
  				//recebendo o elemento com base no id
  				elemento = myapps[x];
				
				addOrd(rum, rodando, elemento);
				   
				return;	
			}
		}			
		
		//caso o id n�o seja encontrado
		while(1){
			if(pagina == 15) {
				telaMeusappED();
				imprimirED(myapps, quant + 1);
			}else {
				telaMeusappED();
				imprimirEDpro(myapps, quant, pagina);
			}
						
			gotoxy(2,20);
			printf("Id nao encontrado - Id:");
			id = 0;
			scanf("%d", & id);
			gotoxy(0, 50);
			
			//vendo se o app ja est� rodando
			for(x = 0; x < quant; x++) {
				if(rum[x].id == id){
					gotoxy(5, 20);
					printf("-Aplicativo rodando/nao encontrado");
					gotoxy(2, 28);
					system("PAUSE");
					return;
				}			
			}			
				  	
			for(x = 0; x < quant; x++) {
				if(myapps[x].id == id) {
					//recebendo a quantidade de apps istalados
	  				rodando = quantApp(rum);
	  				
	  				//recebendo o elemento com base no id
	  				elemento = myapps[x];
					
					addOrd(rum, rodando, elemento);
					   
					return;						
				}
			}			
		}		
	}
}

//fun��o para remover apps
void funRemo(App myapps[], int quant, int pagina, App rum[], App MeusApp_Ini[]) {
	int id = 0;
	int x;
	int y;
	int z = 0;
	int a;
	int quant_rum = quantApp(rum);
	
	//so remove se tiver apps intalados
	if(quant > 0) {
		while(1) {
			if(pagina == 15) {
				system("cls");
				telaMeusappED();
				imprimirED(myapps, quant + 1);
			}else {
				system("cls");
				telaMeusappED();
				imprimirEDpro(myapps, quant, pagina);
			}	
	
			//Recebendo opera��o selecionada
			gotoxy(2,20);
			printf("Id:");
			scanf("%d", & id);
			gotoxy(0, 50);	

			//procurando o indice referete a esse id
			for(x = 0; x < quant; x++) {
				if(myapps[x].id == id) {
					//removendo app instalado
					strcpy(myapps[x].nome, "");
					myapps[x].id = 0;
					myapps[x].id = 0;
					
					//reordenando o vetor
					for(y = x; y < quant; y++) {
						myapps[y] = myapps[y + 1];
					}
					
					//removendo apps que est�o rodando
					if(quant_rum != 0) {
						for(y = 0; y < quant_rum; y++) {
							if(rum[y].id == id) {
								//removendo app instalado
								strcpy(rum[y].nome, "");
								rum[y].id = 0;
								rum[y].id = 0;
								
								//reordenando o vetor
								for(z = y; z < quant; z++) {
									rum[z] = rum[z + 1];
								}						
							}
						}
					}
					
					//removendo o app se ele estiver na tela inicial

					return;
				}
			}			
			
			//caso o id n�o seja encontrado
			while(1){
				if(pagina == 15) {
					telaMeusappED();
					imprimirED(myapps, quant + 1);
				}else {
					telaMeusappED();
					imprimirEDpro(myapps, quant, pagina);
				}
							
				gotoxy(2,20);
				printf("Id nao encontrado - Id:");
				scanf("%d", & id);
				gotoxy(0, 50);
				
				//procurando o indice referete a esse id
				for(x = 0; x < quant; x++) {
					if(myapps[x].id == id) {
						//removendo app instalado
						strcpy(myapps[x].nome, "");
						myapps[x].id = 0;
						myapps[x].id = 0;
						
						//reordenando o vetor
						for(y = x; y < quant; y++) {
							myapps[y] = myapps[y + 1];
						}
						
						quant_rum = quantApp(rum);
						//removendo app se ele tamb�m estiver rodando
						if(quant_rum != 0) {
							for(y = 0; y < quant_rum; y++) {
								if(rum[y].id == id) {
									//removendo app instalado
									strcpy(rum[y].nome, "");
									rum[y].id = 0;
									rum[y].id = 0;
									
									//reordenando o vetor
									for(z = y; z < quant; z++) {
										rum[z] = rum[z + 1];
									}						
								}
							}
						}
						
						//removendo o app se ele estiver na tela inicial
												
						return;
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

//fun��o para parar um app que esteja eecutando
void stopED(App rum[], int quant, int pagina) {
	int id = 0;
	int x;
	int y;

	while(1) {
		if(pagina == 15) {
			system("cls");
			telaAppRum();
			imprimirED(rum, quant + 1);
		}else {
			system("cls");
			telaAppRum();
			imprimirEDpro(rum, quant + 1, pagina);
		}	

		//Recebendo opera��o selecionada
		gotoxy(2,20);
		printf("Id:");
		scanf("%d", & id);
		gotoxy(0, 50);
		
		//procurando o indice referete a esse id
		for(x = 0; x < quant; x++) {
			if(rum[x].id == id) {
				//removendo app instalado
				strcpy(rum[x].nome, "");
				rum[x].id = 0;
				rum[x].id = 0;
				
				//reordenando o vetor
				for(y = x; y < quant; y++) {
					rum[y] = rum[y + 1];
				}
				return;
			}
		}
				  		
		//caso o id n�o seja encontrado
		while(1){
			if(pagina == 15) {
				telaMeusappED();
				imprimirED(rum, quant + 1);
			}else {
				telaMeusappED();
				imprimirEDpro(rum, quant + 1, pagina);
			}
						
			gotoxy(2,20);
			printf("Id nao encontrado - Id:");
			id = 0;
			scanf("%d", & id);
			gotoxy(0, 50);
				
			//procurando o indice referete a esse id
			for(x = 0; x < quant; x++) {
				if(rum[x].id == id) {
					//removendo app instalado
					strcpy(rum[x].nome, "");
					rum[x].id = 0;
					rum[x].id = 0;
					
					//reordenando o vetor
					for(y = x; y < quant; y++) {
						rum[y] = rum[y + 1];
					}
					return;
				}
			}			
		}		
	}	
}

//fun��o para 3(AppRumED) op�ao do menu
void funAppRumED(App rum[], int quant) {	
	char operacao;
	int pausa;
	int pagina = 15;
	
	//imprimindo interface vstore
	while(1) {
		//recebendo novo quant caso algum app seja removido
		quant = quantApp(rum);
		
		if(pagina == 15) {
			//imprimindo os 14 apps iniciais
			telaAppRum();
			imprimirED(rum, quant + 1);
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
     			stopED(rum, quant, pagina);
            break;
        	case ',':
				if(pagina != 15) {
					pagina--;
					telaAppRum();
					imprimirEDpro(rum, quant + 1, pagina);
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
					imprimirEDpro(rum, quant + 1, pagina);
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
				

//fun��o para 2(MeusappsEd) op��o do meunu
void funMeusappsED(App myapps[], int quant, App rum[], App MeusApp_Ini[]) {
	char operacao;
	int pausa;
	int pagina = 15;
	
	//imprimindo interface
	while(1) {
		//contando a quantidade de apps caso um seja removido
		quant = quantApp(myapps);
		
		if(pagina == 15) {
			//imprimindo os 14 apps iniciais
			telaMeusappED();
			imprimirED(myapps, quant + 1);
		}
				
		//Recebendo opera��o selecionada
		gotoxy(2, 20);
		printf("Action:");
		scanf(" %c", & operacao);
		gotoxy(0, 50);
		
		switch(operacao) {
			case ',':
				if(pagina != 15) {
					pagina--;
					telaMeusappED();
					imprimirEDpro(myapps, quant + 1, pagina);
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
					imprimirEDpro(myapps, quant + 1, pagina);
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
 				quant = quantApp(myapps);
     			funRumED(myapps, quant, rum, pagina);
            break;
        	case 'w':
        		quant = quantApp(myapps);
        		funRemo(myapps, quant, pagina, rum, MeusApp_Ini);
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

//fun��o para a 1 op��o(StoreED) do menu
void funStoreED(App aplicativos[], int quant, App meusappsed[], App Myapps_Ini[]) {	
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
     			funInsta(aplicativos, quant, meusappsed, pagina, Myapps_Ini);
            break;
        	case ',':
				if(pagina != 15) {
					pagina--;
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
	App MeusAppsED_Ini[I];
	App MeusAppsED[T];
	App AppRumED[T];
	int quant_apps = 0;
	char operacao;
	int pausa;
	
	//zerando o vetor StoreEd
	iniciaV(StoreED);
	
	//zererando vetor MeusAppsEd_Ini
	iniciaV(MeusAppsED);
	
	//zerando MeusAppsEd
	iniciaV(MeusAppsED_Ini);
	
	//zerando AppRumEd
	iniciaV(MeusAppsED);

	//chamando a leitura do arquivo
	lerArq(StoreED);
	
	//chamando a interface inicial
	while(1) {
		telaIni(MeusAppsED_Ini);
	
		//op��o de saida
		gotoxy(2, 28);
		printf("Para desligar o MobileED pressione ';'");
		
		//Recebendo opera��o selecionada
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