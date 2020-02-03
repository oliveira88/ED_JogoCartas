#include "pilha.h"

typedef struct Arvore
{
    TCarta carta;
    struct Arvore *esq;
    struct Arvore *dir;
} Arvore;

void insereArvore(Arvore **arvore, TCarta carta);
int calculaMenor(Arvore **arvore);