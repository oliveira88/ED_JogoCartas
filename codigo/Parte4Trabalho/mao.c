#include "mao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trocaCarta(int destino, int origem, Lista **l) {
    TCarta *aux;
    aux = (TCarta*)malloc(sizeof(TCarta));
    Lista *cartaDestino, *cartaOrigem;

    cartaOrigem = *l;
    cartaDestino = *l;
    for (int m = 1; m < origem; m++)
    {
        cartaOrigem = (cartaOrigem)->next;
    }

    for (int m = 1; m < destino; m++)
    {
        cartaDestino = cartaDestino->next;
    }

    *aux = cartaOrigem->carta;
    cartaOrigem->carta = cartaDestino->carta;
    cartaDestino->carta = *aux;

    free(aux);

}

void insereLista(Lista **l, TCarta carta) {
    Lista *novaLista, *aux;
    novaLista = (Lista *)malloc(sizeof(Lista));
    novaLista->next = NULL;
    novaLista->carta = carta;
    if (*l == NULL) {
         *l = novaLista;
    } else {
        for (aux = *l; aux->next != NULL; aux = aux->next)
            ;
        aux->next = novaLista;
    }
}

void deleteLista(Lista **l, int qtd, Recursos *recursos) {
    TCarta descartadas[qtd];
    int qtdCopas = 0, qtdEspadas = 0, qtdPaus = 0, qtdOuros = 0;
    int par = 0, trinca = 0, quadra = 0;
    int sequencia = 0, msmNaipe = 0;
    int total = 0;
    for (int i = 0; i < qtd; i++) {
        Lista *a = (*l);
        descartadas[i] = a->carta;
        if (a->carta.naipe == 'C') {
            recursos->copas += a->carta.valor;
            qtdCopas++;
        }
        if (a->carta.naipe == 'E') {
            recursos->espadas += a->carta.valor;
            qtdEspadas++;
        }
        if (a->carta.naipe == 'P') {
            recursos->paus += a->carta.valor;
            qtdPaus++;
        }
        if (a->carta.naipe == 'O') {
            recursos->ouros += a->carta.valor;
            qtdOuros++;
        }
        (*l) = (*l)->next;
        free(a);
    }

    if (qtdCopas > 1) {
        msmNaipe += qtdCopas;
    }
    if (qtdEspadas > 1) {
        msmNaipe += qtdEspadas;
    }
    if (qtdPaus > 1) {
        msmNaipe += qtdPaus;
    }
    if (qtdOuros > 1) {
        msmNaipe += qtdOuros;
    }

    int valorDoPrimeiroPar = 0;
    int valorDoSegundoPar = 0;
    int valorDaTrinca = 0;
    for (int i = 0; i < qtd; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (descartadas[i].valor == descartadas[j].valor) {
                if (descartadas[i].valor != valorDoPrimeiroPar &&
                    descartadas[i].valor != valorDoSegundoPar &&
                    descartadas[i].valor != valorDaTrinca) {
                    par++;
                    if (valorDoPrimeiroPar == 0) {
                        valorDoPrimeiroPar = descartadas[i].valor;
                    } else {
                        valorDoSegundoPar = descartadas[i].valor;
                    }
                } else if (descartadas[i].valor != valorDaTrinca) {
                    par--;
                    trinca++;
                    valorDaTrinca = descartadas[i].valor;
                } else {
                    if (i==0)
                    {
                        trinca--;
                        quadra++;
                    }  
                }
            }
        }
    }

    int seq[qtd];
    for (int i = 0; i < qtd; i++) {
        seq[i] = -1;
    }
    int k = 0;
    for (int i = 0; i < (qtd - 1); i++) {
        if (descartadas[i].valor == (descartadas[i + 1].valor - 1)) {
            if (descartadas[i].valor != seq[k]) {
                if (k != 0) {
                    k++;
                }
                seq[k] = descartadas[i].valor;
                k++;
                seq[k] = descartadas[i + 1].valor;
            } else {
                k++;
                seq[k] = descartadas[i + 1].valor;
            }
        }
    }
    for (int i = 0; i < qtd; i++) {
        if (seq[i] != -1) {
            sequencia++;
        }
    }
    if (sequencia > 0) {
        printf("Vc fez uma sequencia de tamanho %d\n", sequencia);
        total = total + (2 * sequencia);
    }
    if (msmNaipe > 0) {
        printf("Vc fez um mesmo naipe de tamanho %d\n", msmNaipe);
        total = total + (3 * msmNaipe);
    }
    if (par > 0) {
        printf("Vc fez %d par(es)\n", par);
        total = total + (2 * par);
    }
    if (trinca > 0) {
        printf("Vc fez uma trinca\n");
        total = total + 5;
    }
    if (quadra > 0) {
        printf("Vc fez uma quadra\n");
        total = total + 20;
    }
    if (total > 0) {
        int bonus;
        printf("Voce fez um bonus de %d\n\nPara onde deseja por seu bonus?: 1 - Paus, 2 - Espadas, 3 - Ouros, 4 - Copas\n", total);
        scanf("%d", &bonus);
        while((bonus < 1 || bonus > 4) ){
            printf("\n%d nao esta associado a nenhum naipe, por favor digite um numero valido\n1 - Paus, 2 - Espadas, 3 - Ouros, 4 - Copas\n", bonus);
            scanf("%d", &bonus);
        }
        if (bonus == 1) {
            recursos->paus += total;
        } else if (bonus == 2) {
            recursos->espadas += total;
        } else if (bonus == 3) {
            recursos->ouros += total;
        } else if (bonus == 4) {
            recursos->copas += total;
        }
    }
}
int tamanhoLista(Lista **lista){
    int cont = 0;
    Lista *aux = (*lista);
    while (aux != NULL){
        cont++;
        aux = aux->next;
    }
    return cont;
}
void printaMao(Lista *l) {
    Lista *aux;
    aux = l;

    printf("Sua mao:\n");
    while (aux != NULL) {
        printf("%s - %c\t\t", aux->carta.face, aux->carta.naipe);
        aux = aux->next;
    }

    printf("\n\n\n");
}

void freeLista(Lista **lista) {
    Lista *aux;
    while (*lista != NULL) {
        aux = *lista;
        (*lista) = (*lista)->next;
        free(aux);
    }
}