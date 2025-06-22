#ifndef EXPRESSOES_H
#define EXPRESSOES_H

typedef struct no{
    char dado;
    struct no* prox;        
} No;

typedef struct{
    No* topo;
    int tamanho;
} Pilha;



// PILHA
Pilha* criarPilha();
void empilhar(Pilha* p, char valor);
char desempilhar(Pilha* p, char valor);
int estaVazia(Pilha* p);
void mostrarPilha(Pilha *p);
void liberarPilha(Pilha *p);

// OPERAÇÕES
int lerOpcao();
void converte(Pilha* p, int opcao);
// Função para converter Infixada -> pos-fixada
void posFixada(Pilha* p);

#endif
