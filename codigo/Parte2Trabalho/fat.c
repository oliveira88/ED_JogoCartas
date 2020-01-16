#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct TCarta {
    char face[3];
    char naipe;
    int valor;
    char nome[30];

} TCarta;

typedef struct Lista {
    TCarta carta;
    int cont;
    struct Lista *next;
} Lista;

void sorteiaNumeros(int *vetor);
void trocaCarta(int destino, int origem, Lista *l);
void insereLista(Lista *l, TCarta carta);
void printaLista(Lista *l);
int tamanhoLista(Lista *l);

void main() {
    TCarta cartas[52];
    Lista *listaInicio;
    //Lista *listaSegundo;
    //Lista *listaTerceiro;
    //Lista *listaQuarto;
    //Lista *listaQuinto;
    listaInicio = NULL;
    int numSorteados[5];

    listaInicio = (Lista *)malloc(sizeof(struct Lista));
    /*
    listaSegundo = (Lista *)malloc(sizeof(struct Lista));
    listaTerceiro = (Lista *)malloc(sizeof(struct Lista));
    listaQuarto = (Lista *)malloc(sizeof(struct Lista));
    listaQuinto = (Lista *)malloc(sizeof(struct Lista));
	*/

    FILE *arqCartas;
    arqCartas = fopen("Cartas.txt", "r");
    int n, i = 0;
    if (arqCartas == NULL)
        printf("Nenhum arquivo\n");

    while (!feof(arqCartas)) {
        fscanf(arqCartas, "%s %c %d %[^\n]s", cartas[i].face, &cartas[i].naipe, &cartas[i].valor, cartas[i].nome);

        i++;
    }
    sorteiaNumeros(numSorteados);

    printf("%c  %d\n", cartas[numSorteados[0]].naipe, cartas[numSorteados[0]].valor);
    printf("%c  %d\n", cartas[numSorteados[1]].naipe, cartas[numSorteados[1]].valor);
    printf("%c  %d\n", cartas[numSorteados[2]].naipe, cartas[numSorteados[2]].valor);
    printf("%c  %d\n", cartas[numSorteados[3]].naipe, cartas[numSorteados[3]].valor);
    printf("%c  %d\n", cartas[numSorteados[4]].naipe, cartas[numSorteados[4]].valor);
    srand(time(NULL));

    printf("Deseja sortear uma mao?\n1 - sim\n0 - nao\n");
    scanf("%d", &n);
    if (n == 1) {
        for (int i = 4; i > -1 ; i--) {
           
            insereLista(listaInicio, cartas[numSorteados[i]]);
            
        } 
        printaLista(listaInicio);   
    }

    while (n != 0) {
        printf("Deseja reposicionar as cartas?\n2 - sim\n0 - nao\n");
        scanf("%d", &n);
        if (n == 2) {
            int carta1, carta2;
            printf("Qual cartas quieres trocar de posicao: ");
            scanf("%d", &carta1);
            scanf("%d", &carta2);
            trocaCarta(carta1, carta2, listaInicio);
            printaLista(listaInicio); 
        }
    }

    fclose(arqCartas);
    free(listaInicio);
    /*
    free(listaSegundo);
    free(listaTerceiro);
    free(listaQuarto);
    free(listaQuinto);
	*/
}

void sorteiaNumeros(int *vetor) {
    for (int i = 0; i < 5; i++) {
        vetor[i] = -1;
    }
    srand(time(NULL));
    int verifica = 0;
    int i = 0;
    while (i < 5) {
        int aleatorio = rand() % 52;
        for (int j = 0; j < 5; j++) {
            if (vetor[j] == aleatorio) {
                verifica++;
            }
        }
        if (verifica == 0) {
            vetor[i] = aleatorio;
            i++;
        }
    }
}

void trocaCarta(int destino, int origem, Lista *l) {
    TCarta *aux;
    TCarta *cartaDestino, *cartaOrigem;

    while(l != NULL){
      if(l->cont == destino){
            /*
            strcpy(cartaDestino->face,l->carta.face);

            cartaDestino->naipe = l->carta.naipe;
            cartaDestino->valor = l->carta.valor;
            strcpy(cartaDestino->nome,l->carta.nome);
*/          cartaDestino = &l->carta;


      }
      if(l->cont == origem){
/*
            strcpy(cartaOrigem->face,l->carta.face);

            cartaOrigem->naipe = l->carta.naipe;
            cartaOrigem->valor = l->carta.valor;
            strcpy(cartaOrigem->nome,l->carta.nome);
*/          cartaOrigem = &l->carta;
      }

        l = l->next;
    } 

    aux = cartaDestino;
    cartaDestino = cartaOrigem;
    cartaOrigem = aux;
}


void insereLista(Lista *l, TCarta carta) {
    Lista *novaLista;
    novaLista = (Lista *)malloc(sizeof(Lista));
    novaLista->carta = carta;
    novaLista->cont = tamanhoLista(l);
    novaLista->next = l->next;
    l->next = novaLista;
}

int tamanhoLista(Lista *l){
    int n = 5;    
    while(l!= NULL){
        n--;
        l = l->next;
    }
    return n;
}

void printaLista(Lista *l) {
    Lista *aux;
    aux = l->next;

    while (aux != NULL) {
        printf("%c  %d %d\n", aux->carta.naipe, aux->carta.valor, aux->cont);
        aux = aux->next;
    }
    printf("\n");
}
