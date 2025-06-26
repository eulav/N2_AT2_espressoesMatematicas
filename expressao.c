#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>    // Para sin, cos, sqrt, pow
#include <ctype.h>
#include "expressao.h"

// Definindo o valor de pi
#define PI 3.14159265358979323846

// Pilha de char (operadores)

PilhaChar* criarPilhaChar() {
    PilhaChar *p = malloc(sizeof(PilhaChar));
    p->topo = NULL;
    return p;
}

void empilharChar(PilhaChar *p, char valor) {
    NoChar *novo = malloc(sizeof(NoChar));
    novo->dado = valor;
    novo->prox = p->topo;
    p->topo = novo;
}

char desempilharChar(PilhaChar *p) {
    if (p->topo == NULL) return '\0';
    NoChar *temp = p->topo;
    char valor = temp->dado;
    p->topo = temp->prox;
    free(temp);
    return valor;
}

char topoChar(PilhaChar *p) {
    return p->topo ? p->topo->dado : '\0';
}

int pilhaCharVazia(PilhaChar *p) {
    return p->topo == NULL;
}

void liberarPilhaChar(PilhaChar *p) {
    while (!pilhaCharVazia(p)) {
        desempilharChar(p);
    }
    free(p);
}

// Define precedência dos operadores e funções
int precedencia(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^' || op == 'R') return 3;
    if (op == 's' || op == 'c') return 4;
    return 0; // '(' e outros
}

// Conversão infixo para posfixo
char* infixposfix(char *inf) {
    int n = strlen(inf);
    char *posf = malloc(4 * n);
    if (!posf) return NULL;

    PilhaChar *pilha = criarPilhaChar();
    int i = 0, j = 0;

    while (inf[i] != '\0') {
        if (isspace(inf[i])) {
            i++;
            continue;
        }

        // Detecta seno e cosseno: s(NUM) ou c(NUM)
        if ((inf[i] == 's' || inf[i] == 'c') && inf[i+1] == '(') {
            char func = inf[i];
            i += 2; // pula "s(" ou "c("
            int start = i;
            while (isdigit(inf[i]) || inf[i] == '.') i++;
            int len = i - start;
            char numStr[32];
            memcpy(numStr, inf + start, len);
            numStr[len] = '\0';

            float num = strtof(numStr, NULL);
            float resultado;
            if (func == 's') {
                resultado = sin(num * PI / 180.0);
            } else {
                resultado = cos(num * PI / 180.0);
            }
            char resStr[32];
            snprintf(resStr, sizeof(resStr), "%.6f", resultado);
            int k = 0;
            while (resStr[k] != '\0') posf[j++] = resStr[k++];
            posf[j++] = ' ';

            if (inf[i] == ')') i++;
            continue;
        }

        // Números (incluindo floats)
        if (isdigit(inf[i]) || inf[i] == '.') {
            int start = i;
            while (isdigit(inf[i]) || inf[i] == '.') i++;
            int len = i - start;
            memcpy(posf + j, inf + start, len);
            j += len;
            posf[j++] = ' ';
        } else {
            char c = inf[i];
            if (c == '(') {
                empilharChar(pilha, c);
            } else if (c == ')') {
                while (!pilhaCharVazia(pilha) && topoChar(pilha) != '(') {
                    posf[j++] = desempilharChar(pilha);
                    posf[j++] = ' ';
                }
                if (!pilhaCharVazia(pilha)) desempilharChar(pilha);
                else {
                    free(posf);
                    liberarPilhaChar(pilha);
                    return NULL;
                }
            } else {
                while (!pilhaCharVazia(pilha) && topoChar(pilha) != '(' &&
                       precedencia(topoChar(pilha)) >= precedencia(c)) {
                    posf[j++] = desempilharChar(pilha);
                    posf[j++] = ' ';
                }
                empilharChar(pilha, c);
            }
            i++;
        }
    }

    while (!pilhaCharVazia(pilha)) {
        char op = desempilharChar(pilha);
        if (op == '(') {
            free(posf);
            liberarPilhaChar(pilha);
            return NULL;
        }
        posf[j++] = op;
        posf[j++] = ' ';
    }
    if (j > 0) j--;
    posf[j] = '\0';

    liberarPilhaChar(pilha);
    return posf;
}

// Pilha de float para avaliação
typedef struct no_float {
    float dado;
    struct no_float *prox;
} NoFloat;

typedef struct {
    NoFloat *topo;
} PilhaFloat;

PilhaFloat* criarPilhaFloat() {
    PilhaFloat *p = malloc(sizeof(PilhaFloat));
    p->topo = NULL;
    return p;
}

void empilharFloat(PilhaFloat *p, float valor) {
    NoFloat *novo = malloc(sizeof(NoFloat));
    novo->dado = valor;
    novo->prox = p->topo;
    p->topo = novo;
}

float desempilharFloat(PilhaFloat *p) {
    if (p->topo == NULL) return 0.0/0.0;
    NoFloat *temp = p->topo;
    float valor = temp->dado;
    p->topo = temp->prox;
    free(temp);
    return valor;
}

int pilhaFloatVazia(PilhaFloat *p) {
    return p->topo == NULL;
}

void liberarPilhaFloat(PilhaFloat *p) {
    while (!pilhaFloatVazia(p)) {
        desempilharFloat(p);
    }
    free(p);
}

// Avalia expressão pós-fixada
float avaliarPosfixada(char *posf) {
    PilhaFloat *p = criarPilhaFloat();
    char token[64];
    int i = 0, j = 0;

    while (1) {
        while (posf[i] == ' ') i++;
        if (posf[i] == '\0') break;

        j = 0;
        while (posf[i] != ' ' && posf[i] != '\0') {
            token[j++] = posf[i++];
        }
        token[j] = '\0';

        if (strlen(token) == 1 &&
            (token[0] == '+' || token[0] == '-' || token[0] == '*' ||
             token[0] == '/' || token[0] == '^' || token[0] == 'R')) {

            float res;

            if (token[0] == 'R') {
                if (pilhaFloatVazia(p)) {
                    liberarPilhaFloat(p);
                    printf("Erro: pilha vazia para R\n");
                    return 0;
                }
                float a = desempilharFloat(p);
                if (a < 0) {
                    liberarPilhaFloat(p);
                    printf("Erro: raiz de número negativo\n");
                    return 0;
                }
                res = sqrtf(a);
            } else {
                if (pilhaFloatVazia(p)) {
                    liberarPilhaFloat(p);
                    printf("Erro: pilha vazia\n");
                    return 0;
                }
                float b = desempilharFloat(p);

                if (pilhaFloatVazia(p)) {
                    liberarPilhaFloat(p);
                    printf("Erro: pilha vazia\n");
                    return 0;
                }
                float a = desempilharFloat(p);

                switch(token[0]) {
                    case '+': res = a + b; break;
                    case '-': res = a - b; break;
                    case '*': res = a * b; break;
                    case '/':
                        if (b == 0) {
                            liberarPilhaFloat(p);
                            printf("Erro: divisao por zero\n");
                            return 0;
                        }
                        res = a / b; break;
                    case '^': res = powf(a, b); break;
                    default:
                        liberarPilhaFloat(p);
                        printf("Erro: operador desconhecido\n");
                        return 0;
                }
            }
            empilharFloat(p, res);
        } else {
            float val = strtof(token, NULL);
            empilharFloat(p, val);
        }
    }

    if (pilhaFloatVazia(p)) {
        printf("Expressao vazia\n");
        return 0;
    }
    float resultado = desempilharFloat(p);
    if (!pilhaFloatVazia(p)) {
        printf("Expressao invalida\n");
        liberarPilhaFloat(p);
        return 0;
    }

    liberarPilhaFloat(p);
    return resultado;
}

// Avalia expressão infixa (função auxiliar)
float avaliarInfixa(char *inf) {
    char *posf = infixposfix(inf);
    if (!posf) {
        printf("Erro na conversao infixa para posfixa\n");
        return 0;
    }
    float resultado = avaliarPosfixada(posf);
    free(posf);
    return resultado;
}

// Conversão posfixa para infixa (para visualização)

typedef struct no_str {
    char *dado;
    struct no_str *prox;
} NoStr;

typedef struct {
    NoStr *topo;
} PilhaStr;

void empilharStr(PilhaStr *p, char *valor) {
    NoStr *novo = malloc(sizeof(NoStr));
    novo->dado = valor;
    novo->prox = p->topo;
    p->topo = novo;
}

char* desempilharStr(PilhaStr *p) {
    if (p->topo == NULL) return NULL;
    NoStr *temp = p->topo;
    char *valor = temp->dado;
    p->topo = temp->prox;
    free(temp);
    return valor;
}

char* posfixainfix(char *posf) {
    PilhaStr pilha = { NULL };

    int i = 0;
    char token[64];
    while (1) {
        while (posf[i] == ' ') i++;
        if (posf[i] == '\0') break;

        int j = 0;
        while (posf[i] != ' ' && posf[i] != '\0') {
            token[j++] = posf[i++];
        }
        token[j] = '\0';

        if (strlen(token) == 1 &&
           (token[0]=='+' || token[0]=='-' || token[0]=='*' || token[0]=='/' ||
            token[0]=='^' || token[0] == 'R')) {
            char *b = desempilharStr(&pilha);
            char *a = desempilharStr(&pilha);
            if (!a || !b) {
                free(a);
                free(b);
                while (pilha.topo) free(desempilharStr(&pilha));
                return NULL;
            }
            int tamanho = strlen(a) + strlen(b) + 6;
            char *expr = malloc(tamanho);
            snprintf(expr, tamanho, "(%s %c %s)", a, token[0], b);
            free(a);
            free(b);
            empilharStr(&pilha, expr);
        } else {
            empilharStr(&pilha, strdup(token));
        }
    }

    char *resultado = desempilharStr(&pilha);
    if (pilha.topo != NULL) {
        free(resultado);
        while (pilha.topo) free(desempilharStr(&pilha));
        return NULL;
    }
    return resultado;
}
