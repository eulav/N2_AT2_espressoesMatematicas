#ifndef EXPRESSOES_H
#define EXPRESSOES_H

typedef struct no{
    float dado;
    struct no* prox;        
} No;

typedef struct{
    No* topo;
    int tamanho;
} Pilha;

// PILHA
Pilha* criarPilha();
void empilhar(Pilha* p, float valor);
float desempilhar(Pilha* p);
int estaVazia(Pilha* p);
void mostrarPilha(Pilha *p);
void liberarPilha(Pilha *p);

// OPERAÇÕES
int lerOpcao();
void converte(Pilha* p, int opcao);
// Converter infixada -> pos-Fixada
void posFixada(Pilha* p);

#endif
