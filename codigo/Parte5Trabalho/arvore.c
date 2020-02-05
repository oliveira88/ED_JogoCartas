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
        if((*arvore)->esq == NULL || (*arvore)->dir == NULL) {
            return 1;
        } else{
            int e = calculaMenor(&((*arvore)->esq)) + 1;
            int d = calculaMenor(&((*arvore)->dir)) + 1;
            return (e < d)?e:d;
        }
    }
}

void printaPontuacao(Recursos recursos, Tarefa *tarefasCumpridas, Tarefa *tarefasNaoCumpridas, int PMinac){
    Tarefa *auxc = tarefasCumpridas;
    Tarefa *auxn = tarefasNaoCumpridas;
    int pontuacao, somatorioCumpridas = 0, somatorioNaoCumpridas = 0;
    int metadeDosRecursos = (recursos.paus + recursos.espadas + recursos.ouros + recursos.copas) / 2;

    while (auxc != NULL)
    {
        somatorioCumpridas += (auxc->recursosCopas + auxc->recursosPaus + auxc->recursosEspadas + auxc->recursosOuros) * auxc->prazo;
        auxc = auxc->next;
    }
    while (auxn != NULL){
        somatorioNaoCumpridas += (auxn->recursosCopas + auxn->recursosPaus + auxn->recursosEspadas + auxn->recursosOuros);
        auxn = auxn->next;
    }

    pontuacao = (PMinac * (metadeDosRecursos + somatorioCumpridas)) - somatorioNaoCumpridas;
    printf("A metade dos seus recursos restantes e: %d\n", metadeDosRecursos);
    printf("o somatorio das cumpridas e: %d\n", somatorioCumpridas);
    printf("o somatorio das nao cumpridas e: %d\n", somatorioNaoCumpridas);
    printf("Sua pontuacao foi: %d\n", pontuacao);
}