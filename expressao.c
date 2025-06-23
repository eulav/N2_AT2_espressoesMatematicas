#include <stdio.h>
#include <stdbool.h>
#include "expressao.h"

Pilha* criarPilha(){
    Pilha* p = malloc(sizeof(Pilha)); // alocação da estrutura pilha
    p->topo = NULL; // cria o topo como null
    p->tamanho = 0;
    return p;
}

// VERIFICAR QUAL CONVERSÃO DE OPERAÇÃO QUE O USUÁRIO QUER
int verificarOpcao(){    
    int opcao;
    do {
        printf('Escolha uma opção:\n 1. Converter uma operação Pós-fixada -> Infixada.\n 2. Converter uma operação Infixada -> Pós-fixada.');
        scanf("%d", &opcao);
    } while(opcao != 1 || opcao != 2);
    return opcao;
}

// PUSH
void empilhar(Pilha* p, char valor){    
    No* novo = malloc(sizeof(No));
    if (novo){
        novo->dado = valor;   
        novo->prox = p->topo;
        p->topo = novo;
        p->tamanho++;
    } else {
        printf("Erro na alocação.\n");        
    }
}

// POP
float desempilhar(Pilha* p){
   if (p->topo == NULL){
    printf('A pilha está vazia');
    return -1;
   } else {
    No* temp = p->topo; // guardar o dado do topo
    float valor = temp->dado;
    p->topo = temp->prox;
    free(temp); // libera na memória o nó temporário
    return valor; // retorna o valor desempilhado da lista

   }
}

void mostrarPilha(Pilha *p){
    No* temp = p->topo;
    printf("TOPO -> ");
    while (temp != NULL){
        printf(" %f ->", temp->dado);
        temp = temp->prox;
    }
}

// -------------------- OUTRAS OPERAÇÕES -------------------- 

void converte(Pilha* p, int opcao){
    // VERIFICA QUAL CONVERSÃO VOCÊ ESCOLHEU
   if (opcao == 2){
    posFixada(p);
   } else {
    inFixada(p);
   }
}

// Vai receber uma lista de operação Infixada e converter para posFixada
// (3 + 4) * 5
// void posFixada(Pilha* p){
//     bool parenteses;
//     No* atual = p->topo;
//     // Percorrer toda a lista, verifica se tem ()
//     while (atual != NULL){
//         if (atual->dado == '('){
//             parenteses = true;
//             break;
//         }
//         atual = atual->prox;
//     }
//     // se achar, precisa empilhar o próximo número
//     if (parenteses){
//         No* posFixada = malloc(sizeof(No));
//         // empilhando, 
//         posFixada->dado = atual->ant->dado;
//         posFixada->prox = p->topo;
//         p->topo = posFixada;
//         No* temp = p->topo;
//         while (posFixada != NULL){
//             // precisa verificar se é um operador
//             if (posFixada->dado == '+' || posFixada->dado == '-' || posFixada->dado == '*' || posFixada->dado == '/'){
//                 temp = posFixada;
//                 posFixada = posFixada->prox;
//                 posFixada->prox = temp;
//             // Pula quando o nó for um ), a lista posFixada não possui parênteses
//             } else if (posFixada->dado == ')'){
//                 posFixada = posFixada->prox;
//             }
//         }
        
//     }
    
// }

// Exibir o resultado
// void desempilhar(Pilha* p, int opcao){}
