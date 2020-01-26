#include "recursos.h"
#include <stdio.h>

void inicializaRecursos(struct Recursos *recursos) {
    recursos->copas = 0;
    recursos->espadas = 0;
    recursos->paus = 0;
    recursos->ouros = 0;
}
void printaRecursos(struct Recursos *recursos) {
    printf("Seus recursos sao:\nP - %d\t\tE - %d\t\tO - %d\t\tC - %d\n\n", recursos->paus, recursos->espadas, recursos->ouros, recursos->copas);
}