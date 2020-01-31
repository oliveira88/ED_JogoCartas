#include "tarefas.h"
#include <stdio.h>
#include <stdlib.h>

void deleteTarefa(Tarefa **t) {
    Tarefa *a = *t;
    *t = (*t)->next;
    free(a);
}

void inicializaTarefas(Tarefa **t, FILE *arqTarefas) {
    Tarefa *aux, *nova;
    while (!feof(arqTarefas)) {
        nova = (Tarefa *)malloc(sizeof(Tarefa));
        nova->next = NULL;
        fscanf(arqTarefas, "%d %d %d %d %d %d %d", &nova->turnoAparecimento, &nova->prazo, &nova->recursosPaus,
               &nova->recursosEspadas, &nova->recursosOuros, &nova->recursosCopas, &nova->premio);
        if (*t == NULL) {
            *t = nova;
        } else {
            for (aux = *t; aux->next != NULL; aux = aux->next)
                ;
            aux->next = nova;
        }
    }
}

void printaTarefas(Tarefa *tarefa, int turnoAtual) {
    Tarefa *p;
    printf("\n");
    for (p = tarefa; p != NULL && (p->turnoAparecimento <= turnoAtual); p = p->next) {
        printf("Tarefa %d: (P:%d E:%d O:%d C:%d)\n", p->turnoAparecimento, p->recursosPaus, p->recursosEspadas, p->recursosOuros, p->recursosCopas);
    }
}

void cumpreTarefas(Recursos *recursos, Tarefa **tarefas, int turnoAtual) {
    printf("\n");
    if ((*tarefas)->turnoAparecimento <= turnoAtual) {
        if ((recursos->copas >= (*tarefas)->recursosCopas) && (recursos->espadas >= (*tarefas)->recursosEspadas) &&
        (recursos->paus >= (*tarefas)->recursosPaus) && (recursos->ouros >= (*tarefas)->recursosOuros)) {
            printf("Tarefa Cumprida\n");
            recursos->copas -= (*tarefas)->recursosCopas;
            recursos->espadas -= (*tarefas)->recursosEspadas;
            recursos->paus -= (*tarefas)->recursosPaus;
            recursos->ouros -= (*tarefas)->recursosOuros;
            Tarefa *aux = (*tarefas);
            (*tarefas) = (*tarefas)->next;
            free(aux);
        } else {
            printf("Recursos insuficientes\n");
        }
    } else {
        printf("Nao ha tarefas disponiveis\n");
    }
}

void freeTarefas(Tarefa **tarefas) {
    Tarefa *aux;
    while (*tarefas != NULL) {
        aux = *tarefas;
        (*tarefas) = (*tarefas)->next;
        free(aux);
    }
}

void verificaPrazoTarefa(Tarefa **tarefas, int turnoAtual) {
    Tarefa *aux;
    if (turnoAtual >= (*tarefas)->turnoAparecimento + (*tarefas)->prazo) {
        aux = *tarefas;
        (*tarefas) = (*tarefas)->next;
        free(aux);
    }
}