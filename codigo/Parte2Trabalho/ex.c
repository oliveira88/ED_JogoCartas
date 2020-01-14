#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct TCarta{
	char face[3];
	char naipe;
	int valor;
	char nome[30];

} TCarta;


typedef struct Lista{
	TCarta cartas;
	Lista *next;
} Lista;

void inicializaLista(Lista *lista);
void trocaCarta(int carta1, int carta2);

void main(){

	TCarta cartas[52];
	
	Lista lista;
	
	FILE *arqCartas;
	arqCartas = fopen("Cartas.txt", "r");
	int n,i = 0;
	if( arqCartas == NULL)
		printf("Nenhum arquivo\n");	


	while(!feof(arqCartas)){
		fscanf(arqCartas,"%s %c %d %[^\n]s", cartas[i].face, &cartas[i].naipe, &cartas[i].valor, cartas[i].nome);
		
        i++;
	}

	srand(time(NULL));
	printf("Deseja sortear uma mão? 1 - sim - 0 - nao");
	scanf("%d", &n);
	if(n == 1){
		inicializaLista(&lista);
	}
	

	
	
	
	
	void trocaCarta(int carta1, int carta2){
	
	}
	
	void inicializaLista(Lista *lista){
		lista->nroElementos = 0;
	}
	
	
	
	
	/*
	do{
		printf("\n------------------------- Entre com um numero --------------------------\n1 - Gera uma carta aleatória\n0 - Finaliza o programa\n\n");
		scanf("%d", &n);
		switch(n){
			case 1:
				printf("------------------------------------------------------------------------\n ");
				int aleat = (rand() % 52);
				printf("\n                CARTAS SORTEADA: %s %c %d %s\n", cartas[aleat].face,cartas[aleat].naipe,cartas[aleat].valor,cartas[aleat].nome);
				break;
			case 0:
				break;
			default:  
			printf("------------------------------------------------------------------------ ");
			printf("\n\n                            Numero inválido\n");
		}


	}while(n!=0);
	*/
	fclose(arqCartas);
}
