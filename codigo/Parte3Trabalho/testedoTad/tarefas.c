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
    for (p = tarefa; p != NULL && (p->turnoAparecimento <= turnoAtual); p = p->next) {
        printf("Tarefas: %d (P:%d E:%d O:%d C:%d)\n", p->turnoAparecimento, p->recursosPaus, p->recursosEspadas, p->recursosOuros, p->recursosCopas);
    }
}

void cumpreTarefas(Recursos *recursos, Tarefa **tarefas) {
    if ((recursos->copas >= (*tarefas)->recursosCopas) && (recursos->espadas >= (*tarefas)->recursosEspadas) &&
        (recursos->paus >= (*tarefas)->recursosPaus) && (recursos->ouros >= (*tarefas)->recursosOuros)) {
        printf("Tarefa Cumprida\n");
        recursos->copas -= (*tarefas)->recursosCopas;
        recursos->espadas -= (*tarefas)->recursosEspadas;
        recursos->paus -= (*tarefas)->recursosPaus;
        recursos->ouros -= (*tarefas)->recursosOuros;
        deleteTarefa(tarefas);
    } else {
        printf("Recursos insuficientes\n");
    }
    printaRecursos(recursos);
}