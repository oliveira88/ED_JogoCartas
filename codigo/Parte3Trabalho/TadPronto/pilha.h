#include "mao.h"

typedef struct Pilha{
    TCarta carta;
    struct Pilha *next;
} Pilha;

void inserePilha(TCarta carta, Pilha **pilha);
void removePilha(Pilha **pilha);
void freePilha(Pilha **pilha);