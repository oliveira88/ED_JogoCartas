#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>

void inserePilha(TCarta carta, Pilha **pilha){
    Pilha *nova, *aux = (*pilha);
    nova = (Pilha*)malloc(sizeof(Pilha));
    nova->carta = carta;
    nova->next = NULL;
    if (*pilha == NULL) {
         *pilha = nova;
    } else {
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        aux->next = nova;
    }
}

void removePilha(Pilha **pilha){
    Pilha *anterior = (*pilha), *aux = anterior->next;
    while (aux->next != NULL)
    {
        anterior = aux;
        aux = aux->next;
    }
    anterior->next = NULL;
    free(aux);
}

void freePilha(Pilha **pilha){
    Pilha *aux;
    while (*pilha != NULL) {
        aux = *pilha;
        (*pilha) = (*pilha)->next;
        free(aux);
    }
}