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

void sorteiaNumeros(int *vetor);
void trocaCarta(int destino, int origem, Lista *l);
void insereLista(Lista *l, TCarta carta);
void deleteLista(Lista *l, int qtd, Recursos *recursos);
void printaLista(Lista *l);
int tamanhoLista(Lista *l);
void inicializaBonus(Recursos *bonus);
void printaRecursos(Recursos *recursos);

void main() {
    TCarta cartas[52];
    Lista *listaInicio;
    Recursos recursos;
    inicializaBonus(&recursos);

    listaInicio = NULL;
    int numSorteados[5];

    listaInicio = (Lista *)malloc(sizeof(struct Lista));

    FILE *arqCartas;
    arqCartas = fopen("Cartas.txt", "r");
    int n, i = 0;
    if (arqCartas == NULL)
        printf("Nenhum arquivo\n");

    while (!feof(arqCartas)) {
        fscanf(arqCartas, "%s %c %d %[^\n]s", cartas[i].face, &cartas[i].naipe, &cartas[i].valor, cartas[i].nome);

        i++;
    }
    sorteiaNumeros(numSorteados);

    srand(time(NULL));

    printf("Deseja sortear uma mao?\n1 - sim\n0 - nao\n");
    scanf("%d", &n);
    if (n == 1) {
        for (int i = 4; i > -1; i--) {
            insereLista(listaInicio, cartas[numSorteados[i]]);
        }
        printaLista(listaInicio);
    }

    while (n != 0) {
        printf("O que deseja fazer?\n2 - Trocar cartas\n3 - Descartar cartas\n0 - Sair\n");
        scanf("%d", &n);
        if (n == 2) {
            int carta1, carta2;
            printf("Qual cartas quieres trocar de posicao: ");
            scanf("%d", &carta1);
            scanf("%d", &carta2);
            trocaCarta(carta1, carta2, listaInicio);
            printaLista(listaInicio);
        }
        if (n == 3) {
            int qtdDescarte;
            printf("Quantas cartas deseja descartar: ");
            scanf("%d", &qtdDescarte);
            deleteLista(listaInicio, qtdDescarte, &recursos);
            printaLista(listaInicio);
            printaRecursos(&recursos);
        }
    }

    fclose(arqCartas);
    free(listaInicio);
    /*
    free(listaSegundo);
    free(listaTerceiro);
    free(listaQuarto);
    free(listaQuinto);
	*/
}

void sorteiaNumeros(int *vetor) {
    for (int i = 0; i < 5; i++) {
        vetor[i] = -1;
    }
    srand(time(NULL));
    int verifica = 0;
    int i = 0;
    while (i < 5) {
        int aleatorio = rand() % 52;
        for (int j = 0; j < 5; j++) {
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

            if (descartadas[i].valor + 1 == descartadas[j].valor) {
                sequencia++;
            }
        }
    }

    if (sequencia > 0) {
        //printf("Vc fez uma sequencia de tamanho %d\n", sequencia + 1);
        total = total + (2 * (sequencia + 1));
    }
    if (msmNaipe > 0) {
        //printf("Vc fez um mesmo naipe de tamanho %d\n", msmNaipe);
        total = total + (3 * msmNaipe);
    }
    if (par > 0) {
        //printf("Vc fez %d par(es)\n", par);
        total = total + (2 * par);
    }
    if (trinca > 0) {
        //printf("Vc fez uma trinca\n");
        total = total + 50;
    }
    if (quadra > 0) {
        //printf("Vc fez uma quadra\n");
        total = total + 20;
    }
    if (total > 0) {
        int bonus;
        printf("Voce fez um bonus de %d\nPara onde deseja por seu bonus: 1 - Copas, 2 - Espadas, 3 - Paus, 4 - Ouros?\n", total);
        scanf("%d", &bonus);
        /*
        if (bonus == 'C' || bonus == 'c') {
            recursos->copas += total;
        } else if (bonus == 'E' || bonus == 'e') {
            recursos->espadas += total;
        } else if (bonus == 'P' || bonus == 'p') {
            recursos->paus += total;
        } else if (bonus == 'O' || bonus == 'o') {
            recursos->ouros += total;
        }
        */

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
        printf("%c  %d \n", aux->carta.naipe, aux->carta.valor);
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
    printf("Seus recursos são:\nC - %d\nE - %d\nP - %d\nO - %d\n", recursos->copas, recursos->espadas, recursos->paus, recursos->ouros);
}
