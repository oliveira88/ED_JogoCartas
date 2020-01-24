#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct TCarta {
    char face[3];
    char naipe;
    int valor;
    char nome[30];

} TCarta;

typedef struct Lista {
    TCarta carta;
    int cont;
    struct Lista *next;
} Lista;

typedef struct Recursos {
    int copas, espadas, paus, ouros;

} Recursos;

typedef struct Tarefa {
    int turnoAparecimento, premio , prazo, recursosCopas;
    int recursosEspadas, recursosPaus, recursosOuros;
    struct Tarefa *next;
} Tarefa;

void sorteiaNumeros(int *vetor, int qtd);
void trocaCarta(int destino, int origem, Lista *l);
void insereLista(Lista *l, TCarta carta);
void deleteLista(Lista *l, int qtd, Recursos *recursos);
void printaLista(Lista *l);
int tamanhoLista(Lista *l);
void inicializaBonus(Recursos *recursos);
void printaRecursos(Recursos *recursos);
void inicializaTarefas(Tarefa *t, FILE *arqTarefas);
void printaTarefas(Tarefa *tarefas);

void main() {
    TCarta cartas[52];
    Lista *listaInicio;
    Recursos recursos;
    Tarefa *tarefas;
    int nivel;
    int turnoAtual = 0;

    inicializaBonus(&recursos);

    listaInicio = NULL;
    int numSorteados[5];
    listaInicio = (Lista *)malloc(sizeof(struct Lista));

    tarefas = (Tarefa *)malloc(sizeof(struct Tarefa));
    tarefas->next = NULL;

    
    

    FILE *arqCartas, *arqTarefas;
    arqCartas = fopen("Cartas.txt", "r");
    printf("Selecione o nivel\n1 - Acefalo\t2 - Medio\t3 - Dificil\n");
    scanf("%d", &nivel);
    if (nivel == 1) {
        arqTarefas = fopen("tarefasF.txt", "r");
    } else if (nivel == 2) {
        arqTarefas = fopen("tarefasM.txt", "r");
    } else if (nivel == 3) {
        arqTarefas = fopen("tarefasD.txt", "r");
    }

    int n, i = 0, j = 0;

    inicializaTarefas(tarefas, arqTarefas);

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

    

    printaTarefas(tarefas);
    sorteiaNumeros(numSorteados, 5);

    srand(time(NULL));

    printf("Deseja sortear uma mao?\n1 - sim\n0 - nao\n");
    scanf("%d", &n);
    if (n == 1) {
        for (int i = 4; i > -1; i--) {
            insereLista(listaInicio, cartas[numSorteados[i]]);
        }
        printaLista(listaInicio);
        turnoAtual++;
    }

    int totalDescarte = 0;
    while (n != 0) {
        int qtdDescarte;
        printf("O que deseja fazer?\n2 - Trocar cartas\n3 - Descartar cartas\n4 - Finalizar turno\n0 - Sair\n");
        scanf("%d", &n);
        if (n == 2) {
            int carta1, carta2;
            printf("Qual cartas deseja trocar de posicao: ");
            scanf("%d", &carta1);
            scanf("%d", &carta2);
            trocaCarta(carta1, carta2, listaInicio);
            printaLista(listaInicio);
        }
        if (n == 3) {
            printf("Quantas cartas deseja descartar: ");
            scanf("%d", &qtdDescarte);
            totalDescarte += qtdDescarte;
            deleteLista(listaInicio, qtdDescarte, &recursos);
            printaLista(listaInicio);
            printaRecursos(&recursos);
        }
        if (n == 4)
        {
            turnoAtual++;
            if(totalDescarte > 0){
                sorteiaNumeros(numSorteados, totalDescarte);
                for (int i = totalDescarte-1 ; i > -1; i--) {
                    insereLista(listaInicio, cartas[numSorteados[i]]);
                }
            }
            printf("Turno atual: %d\n", turnoAtual);
            printaLista(listaInicio);
            totalDescarte = 0;
        }
        
    }

    fclose(arqCartas);
    free(listaInicio);
    free(tarefas);
    fclose(arqTarefas);
}

void sorteiaNumeros(int *vetor, int qtd) {
    for (int i = 0; i < 5; i++) {
        vetor[i] = -1;
    }
    srand(time(NULL));
    int verifica = 0;
    int i = 0;
    while (i < qtd) {
        int aleatorio = rand() % 52;
        for (int j = 0; j < qtd; j++) {
            if (vetor[j] == aleatorio) {
                verifica++;
            }
        }
        if (verifica == 0) {
            vetor[i] = aleatorio;
            i++;
        }
    }
}

void trocaCarta(int destino, int origem, Lista *l) {
    TCarta *aux;
    aux = (TCarta *)malloc(sizeof(TCarta));
    TCarta *cartaDestino, *cartaOrigem;

    while (l != NULL) {
        if (l->cont == destino - 1) {
            cartaDestino = &l->carta;
        }
        if (l->cont == origem - 1) {
            cartaOrigem = &l->carta;
        }
        l = l->next;
    }
    *aux = *cartaDestino;
    *cartaDestino = *cartaOrigem;
    *cartaOrigem = *aux;
    free(aux);
    system("@cls|clear");
}

void deleteTarefa(Tarefa *t){
    Tarefa *a = t;
    t = t->next;
    free(a);
}

void insereLista(Lista *l, TCarta carta) {
    Lista *novaLista;
    novaLista = (Lista *)malloc(sizeof(Lista));
    novaLista->carta = carta;
    novaLista->cont = tamanhoLista(l);
    novaLista->next = l->next;
    l->next = novaLista;
}

void deleteLista(Lista *l, int qtd, Recursos *recursos) {
    int bonusEscolhivel = 0;
    TCarta descartadas[qtd];
    int qtdCopas = 0, qtdEspadas = 0, qtdPaus = 0, qtdOuros = 0;
    int par = 0, trinca = 0, quadra = 0;
    int sequencia = 0, msmNaipe = 0;
    int total = 0;
    for (int i = 0; i < qtd; i++) {
        Lista *a = l->next;
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
        l->next = l->next->next;
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
                    trinca--;
                    quadra++;
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
        total = total + 50;
    }
    if (quadra > 0) {
        printf("Vc fez uma quadra\n");
        total = total + 20;
    }
    system("@cls|clear");
    if (total > 0) {
        int bonus;
        printf("Voce fez um bonus de %d\n\nPara onde deseja por seu bonus?: 1 - Copas, 2 - Espadas, 3 - Paus, 4 - Ouros\n", total);
        scanf("%d", &bonus);
        system("@cls|clear");
        if (bonus == 1) {
            recursos->copas += total;
        } else if (bonus == 2) {
            recursos->espadas += total;
        } else if (bonus == 3) {
            recursos->paus += total;
        } else if (bonus == 4) {
            recursos->ouros += total;
        }
    }
}

int tamanhoLista(Lista *l) {
    int n = 5;
    while (l != NULL) {
        n--;
        l = l->next;
    }
    return n;
}

void printaLista(Lista *l) {
    Lista *aux;
    aux = l->next;

    printf("Sua mao:\n");
    while (aux != NULL) {
        printf("%s - %c\n", aux->carta.face, aux->carta.naipe);
        aux = aux->next;
    }

    printf("\n");
}

void inicializaBonus(Recursos *recursos) {
  
    recursos->copas = 0;
    recursos->espadas = 0;
    recursos->paus = 0;
    recursos->ouros = 0;
}
void printaRecursos(Recursos *recursos) {
    printf("Seus recursos são:\nC - %d\nE - %d\nP - %d\nO - %d\n\n", recursos->copas, recursos->espadas, recursos->paus, recursos->ouros);
}

void inicializaTarefas(Tarefa *t, FILE *arqTarefas){
    while (!feof(arqTarefas)) {
        // Tarefa *tarefas;
        // tarefas = (Tarefa *)malloc(sizeof(Tarefa)); 
        
        // fscanf(arqTarefas, "%d %d %d %d %d %d %d", &tarefas->turnoAparecimento, &tarefas->prazo, &tarefas->recursosPaus,
        //        &tarefas->recursosEspadas, &tarefas->recursosOuros, &tarefas->recursosCopas, &tarefas->premio);
        //        printf("");
        // while(t->next != NULL)
        //     t = t->next;
  
        //     t->next = tarefas;

            Tarefa *p, *q, *nova;
            nova = malloc (sizeof (Tarefa));
            fscanf(arqTarefas, "%d %d %d %d %d %d %d", &nova->turnoAparecimento, &nova->prazo, &nova->recursosPaus,
                &nova->recursosEspadas, &nova->recursosOuros, &nova->recursosCopas, &nova->premio);
            p = t;
            q = t->next;
            while (q != NULL) {
                p = q;
                q = q->next;
            }
            nova->next = q;
            p->next = nova;
    }
}

    void printaTarefas (Tarefa *le) {
        Tarefa *p;
        for (p = le->next; p != NULL && (p->turnoAparecimento > 0 && p->turnoAparecimento <= 10); p = p->next){
            printf ("%d %d\n", p->turnoAparecimento, p->premio);
        }
}