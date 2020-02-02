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
    int range = 52;

    inicializaBonus(&recursos);

    listaInicio = NULL;
    tarefas = NULL;
    monte = NULL;
    descarte = NULL;

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

    

    for (int i = 0; i < 52; i++)
    {
        TCarta aux;
        int numSorteado = sorteiaNumeros(cartas, range);        
        TCarta carta = cartas[numSorteado];
        printf("%d : %d %c\n", numSorteado, carta.valor, carta.naipe);
        inserePilha(carta, &monte);

        aux = cartas[numSorteado];              //troca a carta sorteada com a ultima carta e sorteia até range --
        cartas[numSorteado] = cartas[range-1];    //para que não sorteie cartas repetidas
        cartas[range-1] = aux;
        range--;
    }

    
    range = 52;
    
    for (int i = 0; i < 5; i++) {
        Pilha *insereaux = monte;
        while(insereaux->next != NULL){
            insereaux = insereaux->next;
        }
        printf("%s", insereaux->carta.face);
        insereLista(&listaInicio, insereaux->carta);
        removePilha(&monte);
    }
     
    printf("\nTurno atual: %d\n", turnoAtual);
    printaTarefas(tarefas, turnoAtual);
    printaRecursos(&recursos);
    printaMao(listaInicio);

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
            Lista *auxdescarte = listaInicio;

            for (int i = 0; i < qtdDescarte; i++)
            {
                inserePilha(auxdescarte->carta, &descarte);
                auxdescarte = auxdescarte->next;
            }

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
            printaMao(listaInicio);
            totalDescarte = 0;
        }
    }

    fclose(arqCartas);
    freeLista(&listaInicio);
    freeTarefas(&tarefas);
    fclose(arqTarefas);
}