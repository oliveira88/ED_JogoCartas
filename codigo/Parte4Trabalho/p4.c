#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pilha.h"

void main() {
    TCarta cartas[52];
    Lista *listaInicio;
    Recursos recursos;
    Tarefa *tarefas;
    Pilha *monte, *descarte;
    int nivel;
    int n = -1;
    int turnoAtual = 1;

    inicializaRecursos(&recursos);

    listaInicio = NULL;
    tarefas = NULL;
    monte = NULL;
    descarte = NULL;

    FILE *arqCartas, *arqTarefas;
    arqCartas = fopen("Cartas.txt", "r");
    printf("Selecione o nivel\n1 - Facil\t2 - Medio\t3 - Dificil\t4 - Expert\n");
    scanf("%d", &nivel);
    while(nivel < 1 || nivel > 4){
        printf("\n%d nao esta associado a nenhum nivel, por favor digite um numero valido\n1 - Facil\t2 - Medio\t3 - Dificil\t4 - Expert\n", nivel);
        scanf("%d", &nivel);
    }
    if (nivel == 1) {
        arqTarefas = fopen("tarefasF.txt", "r");
    } else if (nivel == 2) {
        arqTarefas = fopen("tarefasM.txt", "r");
    } else if (nivel == 3) {
        arqTarefas = fopen("tarefasD.txt", "r");
    } else if (nivel == 4) {
        arqTarefas = fopen("tarefasI.txt", "r");
    }

    int i = 0;
    inicializaTarefas(&tarefas, arqTarefas);

    if (arqCartas == NULL) {
        printf("Cartas.txt nao encontrado\n");
    }
    if (arqTarefas == NULL) {
        printf("Tarefas.txt nao encontrado\n");
    }

    while (!feof(arqCartas)) {
        fscanf(arqCartas, "%s %c %d %[^\n]s", cartas[i].face, &cartas[i].naipe, &cartas[i].valor, cartas[i].nome);
        i++;
    }
    srand(time(NULL));
    reembaralhar(&monte, cartas);

    for (int i = 0; i < 5; i++) {
        Pilha *insereaux = monte;
        while(insereaux->next != NULL){
            insereaux = insereaux->next;
        }
        insereLista(&listaInicio, insereaux->carta);
        removePilha(&monte);
    }
     
    printf("\nTurno atual: %d\n", turnoAtual);
    printaTarefas(tarefas, turnoAtual);
    printaRecursos(&recursos);
    printf("\nMonte (%d)\t\t\tDescarte (%d)\n\n", tamanhoPilha(&monte), tamanhoPilha(&descarte));
    printaMao(listaInicio);

    int totalDescarte = 0;
    while (n != 0) {
        int qtdDescarte;
        printf("Menu:\n\n1 - Reposicionar cartas\n2 - Descartar cartas\n3 - Cumprir tarefas\n4 - Reembaralhar tudo (*:%d)\n5 - Finalizar turno\n0 - Sair do Jogo\n", recursos.embaralhamento);
        scanf("%d", &n);
        while(n < 0 || n > 5){
            printf("\n%d nao esta associado a nenhum item do menu, por favor digite um numero valido\n\n1 - Reposicionar cartas\n2 - Descartar cartas\n3 - Cumprir tarefas\n4 - Reembaralhar tudo (*:%d)\n5 - Finalizar turno\n0 - Sair do Jogo\n", n, recursos.embaralhamento);
            scanf("%d", &n);
        }
        if (n == 1) {
            int carta1, carta2;
            printf("Quais cartas deseja trocar de posicao?\n");
            printf("Carta: ");
            scanf("%d", &carta1);
            while(carta1 < 1 || carta1 > 5){
                printf("\nPosicao de carta invalida, escolha um posicao de 1 a 5: ");
                scanf("%d", &carta1);

            }
            printf("Carta: ");
            scanf("%d", &carta2);
            while(carta2 < 1 || carta2 > 5){
                printf("\nPosicao de carta invalida, escolha um posicao de 1 a 5: ");
                scanf("%d", &carta2);
            }

            trocaCarta(carta1, carta2, &listaInicio);
            printf("\nTurno atual: %d\n", turnoAtual);
            printaTarefas(tarefas, turnoAtual);
            printaRecursos(&recursos);
            printf("\nMonte (%d)\t\t\tDescarte (%d)\n\n", tamanhoPilha(&monte), tamanhoPilha(&descarte));
            printaMao(listaInicio);
        }
        if (n == 2) {
            printf("Quantas cartas deseja descartar: ");
            scanf("%d", &qtdDescarte);
            while(qtdDescarte < 0 || qtdDescarte > tamanhoLista(&listaInicio)){
                printf("\nQuantidade invalida, por favor digite uma quantia valida: ");
                scanf("%d", &qtdDescarte);
            }
            totalDescarte += qtdDescarte;
            Lista *auxdescarte = listaInicio;

            for (int i = 0; i < qtdDescarte; i++) {
                inserePilha(auxdescarte->carta, &descarte);
                auxdescarte = auxdescarte->next;
            }

            deleteLista(&listaInicio, qtdDescarte, &recursos);
            printf("\nTurno atual: %d\n", turnoAtual);
            printaTarefas(tarefas, turnoAtual);
            printaRecursos(&recursos);
            printf("\nMonte (%d)\t\t\tDescarte (%d)\n\n", tamanhoPilha(&monte), tamanhoPilha(&descarte));
            printaMao(listaInicio);
        }
        if (n == 3) {
            cumpreTarefas(&recursos, &tarefas, turnoAtual);
            verificaPrazoTarefa(&tarefas, turnoAtual);
            printf("\nTurno atual: %d\n", turnoAtual);
            printaTarefas(tarefas, turnoAtual);
            printaRecursos(&recursos);
            printf("\nMonte (%d)\t\t\tDescarte (%d)\n\n", tamanhoPilha(&monte), tamanhoPilha(&descarte));
            printaMao(listaInicio);
        }
        if (n == 4) {
            if(recursos.embaralhamento){
                freePilha(&monte);
                freePilha(&descarte);
                freeLista(&listaInicio);
                reembaralhar(&monte, cartas);
                recursos.embaralhamento--;
                for (int i = 0; i < 5; i++) {
                    Pilha *insereaux = monte;
                    while(insereaux->next != NULL){
                        insereaux = insereaux->next;
                    }
                    insereLista(&listaInicio, insereaux->carta);
                    removePilha(&monte);
                }
            } else {
                printf("\nVoce nao possui recursos de reembaralhamento\n");
            }
            printf("\nTurno atual: %d\n", turnoAtual);
            printaTarefas(tarefas, turnoAtual);
            printaRecursos(&recursos);
            printf("\nMonte (%d)\t\t\tDescarte (%d)\n\n", tamanhoPilha(&monte), tamanhoPilha(&descarte));
            printaMao(listaInicio);
        }
        if (n == 5) {
            turnoAtual++;
            Tarefa *auxiliarTarefa = tarefas;
            while (auxiliarTarefa->turnoAparecimento < turnoAtual)
            {
                auxiliarTarefa->prazo--;
                auxiliarTarefa = auxiliarTarefa->next;
            }
            
            if (totalDescarte > 0) {
                for (int i = 0; i < totalDescarte; i++) {
                    if (monte != NULL)
                    {
                        Pilha *insereaux = monte;
                        while(insereaux->next != NULL){
                            insereaux = insereaux->next;
                        }
                        insereLista(&listaInicio, insereaux->carta);
                        removePilha(&monte);
                    }  
                }
            }
            printf("\nTurno atual: %d\n", turnoAtual);
            verificaPrazoTarefa(&tarefas, turnoAtual);
            printaTarefas(tarefas, turnoAtual);
            printaRecursos(&recursos);
            printf("\nMonte (%d)\t\t\tDescarte (%d)\n\n", tamanhoPilha(&monte), tamanhoPilha(&descarte));
            printaMao(listaInicio);
            totalDescarte = 0;
        }
    }

    fclose(arqCartas);
    freeLista(&listaInicio);
    freeTarefas(&tarefas);
    freePilha(&monte);
    freePilha(&descarte);
    fclose(arqTarefas);
}