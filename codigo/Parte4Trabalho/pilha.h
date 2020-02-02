#include "mao.h"

typedef struct Pilha{
    TCarta carta;
    struct Pilha *next;
} Pilha;

void inserePilha(TCarta carta, Pilha **pilha);
void removePilha(Pilha **pilha);
int tamanhoPilha(Pilha **pilha);
void freePilha(Pilha **pilha);
int sorteiaNumeros(TCarta *vetorDeCartas, int range);
void reembaralhar(Pilha **monte, TCarta *cartas);