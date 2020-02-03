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
        if(!feof(arqTarefas)){
            if (*t == NULL) {
                *t = nova;
            } else {
                for (aux = *t; aux->next != NULL; aux = aux->next)
                    ;
                aux->next = nova;
            }
        } else {
            free(nova);
        }
        
    }
}

void printaTarefas(Tarefa *tarefa, int turnoAtual) {
    Tarefa *p;
    printf("\n");
    for (p = tarefa; p != NULL && (p->turnoAparecimento <= turnoAtual); p = p->next) {
        if (p->prazo > 0)
        {
            printf("Tarefa %d: (P:%d E:%d O:%d C:%d) prazo : %d\n", p->turnoAparecimento, p->recursosPaus, p->recursosEspadas, p->recursosOuros, p->recursosCopas, p->prazo);
        }
        
        
    }
}

void cumpreTarefas(Recursos *recursos, Tarefa **tarefas, int turnoAtual) {
    printf("\n");
    if(*tarefas != NULL){
        if ((*tarefas)->turnoAparecimento <= turnoAtual ) {
            if ((recursos->copas >= (*tarefas)->recursosCopas) && (recursos->espadas >= (*tarefas)->recursosEspadas) &&
            (recursos->paus >= (*tarefas)->recursosPaus) && (recursos->ouros >= (*tarefas)->recursosOuros)) {
                printf("Tarefa Cumprida\n");
                recursos->copas -= (*tarefas)->recursosCopas;
                recursos->espadas -= (*tarefas)->recursosEspadas;
                recursos->paus -= (*tarefas)->recursosPaus;
                recursos->ouros -= (*tarefas)->recursosOuros;
                recursos->embaralhamento += (*tarefas)->premio;
                Tarefa *aux = (*tarefas);
                (*tarefas) = (*tarefas)->next;
                free(aux);
            } else {
                printf("Recursos insuficientes\n");
            }
        } else {
            printf("Nao ha tarefas disponiveis\n");
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
    if((*tarefas) != NULL){
        while((*tarefas)->prazo <= 0) {
            aux = *tarefas;
            (*tarefas) = (*tarefas)->next;
            free(aux);
            if ((*tarefas) == NULL)
            {
                    break;
            }
        }
    }
}