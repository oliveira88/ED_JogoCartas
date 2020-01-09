#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TCartas{
	char face[3];
	char naipe;
	int valor;
	char nome[30];

} TCartas;

void main(){
	char auxNome1[30], auxNome2[2], auxNome3[8];
	TCartas cartas[52];
	FILE *arqCartas;
	arqCartas = fopen("Cartas.txt", "r");
	int i = 0;
	if( arqCartas == NULL)
		printf("Nenhum arquivo\n");	


	while(!feof(arqCartas)){
		fscanf(arqCartas,"%s %c %d %s %s %s", cartas[i].face, &cartas[i].naipe, &cartas[i].valor, cartas[i].nome, auxNome2, auxNome3);
		strcat(cartas[i].nome, " ");
		strcat(cartas[i].nome, auxNome2);
		strcat(cartas[i].nome, " ");
		strcat(cartas[i].nome, auxNome3);
        i++;
	}

	
	int j = rand() % 52;
		printf("%s %c %d %s\n", cartas[j].face, cartas[j].naipe, cartas[j].valor, cartas[j].nome);
	
	fclose(arqCartas);
}
