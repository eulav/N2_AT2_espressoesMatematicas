#ifndef EXPRESSAO_H
#define EXPRESSAO_H

typedef struct no_char {
    char *dado;
    struct no_char *prox;
} NoChar;

typedef struct {
    NoChar *topo;
} PilhaChar;

// Pilha de float para avaliação
typedef struct no_float {
    float dado;
    struct no_float *prox;
} NoFloat;

typedef struct {
    NoFloat *topo;
} PilhaFloat;


PilhaChar* criarPilhaChar();
PilhaFloat* criarPilhaFloat();
void empilharChar(PilhaChar *p, char *valor);
char* desempilharChar(PilhaChar *p);
char topoChar(PilhaChar *p);
int pilhaCharVazia(PilhaChar *p);
void liberarPilhaChar(PilhaChar *p);
char* infixposfix(char *inf);
float avaliarPosfixada(char *posf);
char* posfixainfix(char *posf);
float avaliarInfixa(char *inf);

#endif