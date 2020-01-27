#include <stdio.h>
#include "recursos.h"

typedef struct Tarefa {
    int turnoAparecimento, premio, prazo, recursosCopas;
    int recursosEspadas, recursosPaus, recursosOuros;
    struct Tarefa *next;
} Tarefa;

void inicializaTarefas(Tarefa **t, FILE *arqTarefas);
void printaTarefas(Tarefa *tarefa, int turnoAtual);
void cumpreTarefas(struct Recursos *recursos, Tarefa **tarefas);