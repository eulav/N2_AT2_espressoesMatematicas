#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "expressao.h"

#define MAX_EXPR 256

int main() {
    if (!setlocale(LC_ALL, "Portuguese"))
        setlocale(LC_ALL, "pt_BR.UTF-8");

    char expr[MAX_EXPR];
    char *conv = NULL;
    float res;
    int opcao;

    do {
        printf(
            "\n--- MENU ---\n"
            "1. Converter infixa para pos-fixada - OBS: Le seno e cosseno\n"
            "2. Converter pos-fixada para infixa - OBS: Não suporta seno ou cosseno\n"
            "3. Avaliar expressao pos-fixada\n"
            "4. Sair\n"
            "Escolha uma opcao: "
        );

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // limpa stdin
            printf("Entrada invalida.\n");
            continue;
        }
        getchar(); // consome \n

        switch (opcao) {
            case 1:
                printf("Digite a expressao infixada:\n");
                printf("Para seno ou cosseno, use s(NUM) ou c(NUM)\n");
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
                    res = avaliarPosfixada(conv);
                    printf("Resultado: %.6f\n", res);
                    free(conv);
                }
                break;

            case 2:
                printf("Digite a expressao pos-fixada:\n");
                printf("Obs: Não suporta seno/cosseno aqui, informe valores ja calculados.\n");
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
                    res = avaliarPosfixada(expr);
                    printf("Resultado: %.6f\n", res);
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

    return 0;
}
