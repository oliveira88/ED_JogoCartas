#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

void insereArvore(Arvore **arvore, TCarta carta){
    // Arvore *aux = (*arvore);
    Arvore *nova = (Arvore*)malloc(sizeof(Arvore));

    if((*arvore) == NULL){
        nova->carta = carta;
        nova->dir = NULL;
        nova->esq = NULL;
        (*arvore) = nova;
    } else {
        if(carta.valor >= (*arvore)->carta.valor){
            insereArvore(&((*arvore)->dir), carta);
        } else {
            insereArvore(&((*arvore)->esq), carta);
        }
    }
}

int calculaMenor(Arvore **arvore){
    if((*arvore)!= NULL){

    
        if((*arvore)->esq == NULL && (*arvore)->dir == NULL) {
            return 0;
        } else if((*arvore)->esq == NULL && (*arvore)->dir != NULL){
            return calculaMenor(&((*arvore)->dir)) + 1;
        } else if((*arvore)->esq != NULL && (*arvore)->dir == NULL){
            return calculaMenor(&((*arvore)->esq)) + 1;
        } else{
            int e = calculaMenor(&((*arvore)->esq)) + 1;
            int d = calculaMenor(&((*arvore)->dir)) + 1;
            return (e < d)?e:d;
        }
    }
}