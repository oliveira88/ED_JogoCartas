#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct TCartas{
	char face[3];
	char naipe;
	int valor;
	char nome[30];

} TCartas;

void main(){

	TCartas cartas[52];
	FILE *arqCartas;
	arqCartas = fopen("Cartas.txt", "r");
	int i = 0;
	if( arqCartas == NULL)
		printf("Nenhum arquivo\n");	


	while(!feof(arqCartas)){
		fscanf(arqCartas,"%s %c %d %[^\n]s", cartas[i].face, &cartas[i].naipe, &cartas[i].valor, cartas[i].nome);
		
        i++;
	}

	srand(time(NULL));
	int j = rand() % 52;
		printf("%s %c %d %s\n", cartas[j].face, cartas[j].naipe, cartas[j].valor, cartas[j].nome);
	
	fclose(arqCartas);
}
