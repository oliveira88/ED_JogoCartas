#include <stdio.h>
#include <stdlib.h>

typedef struct TCartas{
	char face[2];
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
//		fread(arqCartas, "%s %c %d %s", cartas[i].face, &cartas[i].naipe, &cartas[i].valor, cartas[i].nome);
		fread(&cartas[i], sizeof(TCartas), 1, arqCartas);
       
        i++;
	}


	for(i = 0; i < 1; i++){
		printf("%s %c %d %s\n", cartas[i].face, cartas[i].naipe, cartas[i].valor, cartas[i].nome);
	}
	fclose(arqCartas);
}
