#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inserePilha(TCarta carta, Pilha **pilha){
    Pilha *nova, *aux = (*pilha);
    nova = (Pilha*)malloc(sizeof(Pilha));
    nova->carta = carta;
    nova->next = NULL;
    if (*pilha == NULL) {
         *pilha = nova;
    } else {
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = nova;
    }
}

void removePilha(Pilha **pilha){
    if((*pilha)->next == NULL){
        free(*pilha);
        *pilha = NULL;
    } else {
        Pilha *anterior = (*pilha), *aux = anterior->next;
        while (aux->next != NULL){
            anterior = aux;
            aux = aux->next;
        }
        anterior->next = NULL;
        free(aux);
    }  
}

int tamanhoPilha(Pilha **pilha){
    int cont = 0;
    Pilha *aux = (*pilha);
    while (aux != NULL){
        cont++;
        aux = aux->next;
    }
    return cont;
}

void freePilha(Pilha **pilha){
    Pilha *aux;
    while (*pilha != NULL) {
        aux = *pilha;
        (*pilha) = (*pilha)->next;
        free(aux);
    }
}

int sorteiaNumeros(TCarta *vetorDeCartas, int range) {
    srand(time(NULL));
    int aleatorio = rand() % range;
    return aleatorio;
}

void reembaralhar(Pilha **monte, TCarta *cartas){
    
    // Embaralhando as cartas (2 for's para deixar mais aleatorio ainda)
    for (int i = 0; i < 2; i++) {
        int range = 52;
        for (int j = 0; j < 52; j++) {
            TCarta aux;
            int numSorteado = sorteiaNumeros(cartas, range);        
            TCarta carta = cartas[numSorteado];

            aux = cartas[numSorteado];
            cartas[numSorteado] = cartas[range-1];    
            cartas[range-1] = aux;
            range--;
        }
    }

    // Inserindo as cartas sorteadas no monte
    for (int i = 0; i < 52; i++) {
        inserePilha(cartas[i], monte);
    }
     
}