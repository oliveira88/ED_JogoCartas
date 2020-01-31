#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mao.h"

void main() {
    TCarta cartas[52];
    Lista *listaInicio;
    Recursos recursos;
    Tarefa *tarefas;
    int nivel;
    int turnoAtual = 1;

    inicializaBonus(&recursos);

    listaInicio = NULL;
    int numSorteados[5];

    tarefas = NULL;
    FILE *arqCartas, *arqTarefas;
    arqCartas = fopen("Cartas.txt", "r");
    printf("Selecione o nivel\n1 - Facil\t2 - Medio\t3 - Dificil\t4 - Expert\n");
    scanf("%d", &nivel);
    if (nivel == 1) {
        arqTarefas = fopen("tarefasF.txt", "r");
    } else if (nivel == 2) {
        arqTarefas = fopen("tarefasM.txt", "r");
    } else if (nivel == 3) {
        arqTarefas = fopen("tarefasD.txt", "r");
    } else if (nivel == 4) {
        arqTarefas = fopen("tarefasI.txt", "r");
    }

    int n, i = 0;
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

    sorteiaNumeros(numSorteados, 5);

    srand(time(NULL));

    printf("Deseja sortear uma mao?\n1 - sim\n0 - nao\n");
    scanf("%d", &n);
    if (n == 1) {
         for (int i = 0; i < 5; i++) {
             insereLista(&listaInicio, cartas[numSorteados[i]]);
         }
        printf("\nTurno atual: %d\n", turnoAtual);
        printaTarefas(tarefas, turnoAtual);
        printaRecursos(&recursos);
        printaMao(listaInicio);
    }

    int totalDescarte = 0;
    while (n != 0) {
        int qtdDescarte;
        printf("Menu:\n\n1 - Reposicionar cartas\n2 - Descartar cartas\n3 - Cumprir tarefas\n4 - Reembaralhar tudo\n5 - Finalizar turno\n0 - Sair do Jogo\n");
        scanf("%d", &n);
        if (n == 1) {
            int carta1, carta2;
            printf("Quais cartas deseja trocar de posicao?\n");
            printf("Carta: ");
            scanf("%d", &carta1);
            printf("Carta: ");
            scanf("%d", &carta2);
            trocaCarta(carta1, carta2, &listaInicio);
            printf("\nTurno atual: %d\n", turnoAtual);
            printaTarefas(tarefas, turnoAtual);
            printaRecursos(&recursos);
            printaMao(listaInicio);
        }
        if (n == 2) {
            printf("Quantas cartas deseja descartar: ");
            scanf("%d", &qtdDescarte);
            totalDescarte += qtdDescarte;
            deleteLista(&listaInicio, qtdDescarte, &recursos);
            printf("\nTurno atual: %d\n", turnoAtual);
            printaTarefas(tarefas, turnoAtual);
            printaRecursos(&recursos);
            printaMao(listaInicio);
        }
        if (n == 3) {
            cumpreTarefas(&recursos, &tarefas, turnoAtual);
            printf("\nTurno atual: %d\n", turnoAtual);
            printaTarefas(tarefas, turnoAtual);
            printaRecursos(&recursos);
            printaMao(listaInicio);
        }
        if (n == 4) {
            printf("FATAL ERROR\n");
        }
        if (n == 5) {
            turnoAtual++;
            if (totalDescarte > 0) {
                sorteiaNumeros(numSorteados, totalDescarte);
                for (int i = 0; i < totalDescarte; i++) {
                    insereLista(&listaInicio, cartas[numSorteados[i]]);
                }
            }
            printf("\nTurno atual: %d\n", turnoAtual);
            verificaPrazoTarefa(&tarefas, turnoAtual);
            printaTarefas(tarefas, turnoAtual);
            printaRecursos(&recursos);
            printaMao(listaInicio);
            totalDescarte = 0;
        }
    }

    fclose(arqCartas);
    freeLista(&listaInicio);
    freeTarefas(&tarefas);
    fclose(arqTarefas);
}