#include "tarefas.h"

typedef struct TCarta {
    char face[3];
    char naipe;
    int valor;
    char nome[30];

} TCarta;

typedef struct Lista {
    TCarta carta;
    struct Lista *next;
} Lista;

void trocaCarta(int destino, int origem, Lista **l);
void insereLista(Lista **l, TCarta carta);
void deleteLista(Lista **l, int qtd, Recursos *recursos);
int tamanhoLista(Lista **lista);
void printaMao(Lista *l);
void freeLista(Lista **lista);