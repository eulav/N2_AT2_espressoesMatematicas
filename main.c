#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expressao.h"

#define MAX_EXPR 256

int main() {
    char expr[MAX_EXPR];
    char *conv = NULL;
    float res;
    int opcao;

    do {
        printf(
        "\n--- MENU ---\n"
        "1. Converter infixa para pos-fixada\n"
        "2. Converter pos-fixada para infixa\n"
        "3. Avaliar expressao pos-fixada\n"
        "4. Sair\n"
        "Escolha uma opcao: "
        );

        if (scanf("%d", &opcao) != 1) {
            // Limpar stdin em caso de entrada inválida
            while (getchar() != '\n');
            printf("Entrada invalida.\n");
            continue;
        }
        getchar(); // consumir '\n'

        switch (opcao) {
            case 1:
                printf("Digite a expressao infixada: ");
                if (!fgets(expr, MAX_EXPR, stdin)) {
                    printf("Erro na leitura\n");
                    break;
                }
                expr[strcspn(expr, "\n")] = '\0';
                conv = infixposfix(expr);
                if (!conv) {
                    printf("Erro na conversao.\n");
                } else {
                    printf("Expressao pos-fixada: %s\n", conv);
                    free(conv);
                }
                break;

            case 2:
                printf("Digite a expressao pos-fixada: ");
                if (!fgets(expr, MAX_EXPR, stdin)) {
                    printf("Erro na leitura\n");
                    break;
                }
                expr[strcspn(expr, "\n")] = '\0';
                conv = posfixainfix(expr);
                if (!conv) {
                    printf("Expressao pos-fixada invalida.\n");
                } else {
                    printf("Expressao infixada: %s\n", conv);
                    free(conv);
                }
                break;

            case 3:
                printf("Digite a expressao pos-fixada para avaliar: ");
                if (!fgets(expr, MAX_EXPR, stdin)) {
                    printf("Erro na leitura\n");
                    break;
                }
                expr[strcspn(expr, "\n")] = '\0';
                res = avaliarPosfixada(expr);
                printf("Resultado: %.6f\n", res);
                break;

            case 4:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida.\n");
                break;
        }
       
    } while (opcao != 4);

    system("clear");

    return 0;
}
