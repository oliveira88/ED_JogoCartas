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
	int nroElementos;
} Lista;

TCarta funcaoSorteiaDeovo(TCarta *cartas, Lista *lista);

void main(){

	TCarta cartas[52];
	Lista *lista;
	
	

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
    lista->nroElementos = 0;
	if(n == 1){
		
		for(int i = 0; i < 5; i++){
			lista->cartas = funcaoSorteiaDeovo(cartas,lista);
			lista->nroElementos++;
		}
	} 
		
	
	
	for(int i = 0; i < 5; i++){
		printf("\n                CARTAS SORTEADA: %s %c %d %s\n", lista->cartas.face,lista->cartas.naipe,lista->cartas.valor,lista->cartas.nome);
	}
	

	fclose(arqCartas);
}


TCarta funcaoSorteiaDeovo(TCarta *cartas, Lista *lista){
	srand(time(NULL));
		
	int aleatorio = rand() % 52;
		
	for(int i = 0; i < 5; i++){
		if(lista[i].cartas.naipe == cartas[aleatorio].naipe && lista[i].cartas.valor == cartas[aleatorio].valor ){
			return funcaoSorteiaDeovo(cartas, lista);
		}else{
			return cartas[aleatorio];
		}
	}
		
}


