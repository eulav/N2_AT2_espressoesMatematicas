#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressao.h"

int main() {
    char infixa[256];

    printf("Digite uma expressao infixada: ");
    if (!fgets(infixa, sizeof(infixa), stdin)) {
        printf("Erro na leitura\n");
        return 1;
    }
    infixa[strcspn(infixa, "\n")] = '\0'; // remove \n

    char *posf = infixposfix(infixa);
    if (!posf) {
        printf("Erro na conversao infixa para posfixa\n");
        return 1;
    }

    printf("Expressao pos-fixada: %s\n", posf);

    float resultado = avaliarPosfixada(posf);
    printf("Resultado: %.6f\n", resultado);

    free(posf);
    return 0;
}
