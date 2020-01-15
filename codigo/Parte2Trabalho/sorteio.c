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
	TCarta cartas[5];
	int nroElementos;
} Lista;

void sorteiaNumeros(int *vetor);

void main(){

	TCarta cartas[52];
	Lista *lista;
	int numSorteados[5];

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
	do{
		printf("Deseja sortear uma mão?\n1 - sim\n0 - nao\n");
		scanf("%d", &n);
		if(n == 1){
			sorteiaNumeros(numSorteados);
			for(int i = 0; i < 5; i++){
				strcpy(lista->cartas[i].face ,cartas[numSorteados[i]].face);
				lista->cartas[i].naipe = cartas[numSorteados[i]].naipe;
				lista->cartas[i].valor = cartas[numSorteados[i]].valor;
				strcpy(lista->cartas[i].nome, cartas[numSorteados[i]].nome);
			}
			for(int i = 0; i < 5; i++){
				printf("%s %c %d %s\n", lista->cartas[i].face, lista->cartas[i].naipe, lista->cartas[i].valor, lista->cartas[i].nome);
			}	
		}
	}while(n == 1);
	

	fclose(arqCartas);
}

void sorteiaNumeros(int *vetor){
	for(int i= 0; i < 5; i++){
		vetor[i] = -1;
	}
	srand(time(NULL));
	int verifica = 0;
	int i = 0;
	while( i < 5 ){
		int aleatorio = rand() % 52;
		for(int j = 0; j < 5; j++){
			if(vetor[j] == aleatorio){
				verifica++;
			}

		}
		if(verifica == 0 ){
			vetor[i] = aleatorio;
			i++;
		}
	}
}