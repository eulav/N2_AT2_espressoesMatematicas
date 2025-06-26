#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>   
#include <ctype.h>
#include "expressao.h"

#define PI 3.14159265358979323846



//Pilha e funções de pilha de Char adaptada para string
PilhaChar* criarPilhaChar() {
    PilhaChar *p = malloc(sizeof(PilhaChar));
    p->topo = NULL;
    return p;
}

void empilharChar(PilhaChar *p, char *valor) {
    NoChar *novo = malloc(sizeof(NoChar));
    novo->dado = malloc(strlen(valor) + 1);//fazemos a alocação para a string (+1 para incluir o caractere nulo)
    strcpy(novo->dado, valor);
    novo->prox = p->topo;//passando o antigo topo para próxima posição
    p->topo = novo;//atualiza o topo com o novo valor
}

char* desempilharChar(PilhaChar *p) {
    if (p->topo == NULL){
      return NULL;  
    } 
    NoChar *temp = p->topo;//cria um nó temporário e armazena o topo
    char *valor = temp->dado;//o valor pega o valor do topo 
    p->topo = temp->prox;//o topo é atualizado recebendo o valor anterior ao dado
    //liberamos temp e retornamos o valor retirado
    free(temp);
    return valor;
}

char topoChar(PilhaChar *p) {
     if (p->topo && p->topo->dado) {
        return p->topo->dado[0];  
    } else { //se vazia, retorna nulo
        return '\0';            
    }
}

int pilhaCharVazia(PilhaChar *p) {
    return p->topo == NULL;
}

void liberarPilhaChar(PilhaChar *p) {
    while (!pilhaCharVazia(p)) {
        char *temp = desempilharChar(p);
        free(temp);
    }
    free(p);
}

//Precedência - função para definir a precência das operações para as tranformação de infixa para pos
int precedencia(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^' || op == 'R') return 3;
    if (op == 's' || op == 'c') return 4;
    return 0;
}

// Conversão de Infixa para Posfixa
char* infixposfix(char *inf) {
    int n = strlen(inf);
    char *posf = malloc(4 * n);//aloca memória para a pos fixada
    if (!posf) return NULL;

    PilhaChar *pilha = criarPilhaChar();
    int i = 0, j = 0;

    while (inf[i] != '\0') {
        if (isspace(inf[i])) { //ignorando os espaços
            i++;
            continue;
        }

        //identificando o seno ou cosseno
        if ((inf[i] == 's' || inf[i] == 'c') && inf[i+1] == '(') {
            
            char func = inf[i];
            i += 2; //pula o parênteses e vai para o número a ser calculado
            int start = i; //marca onde o número começa
            while (isdigit(inf[i]) || inf[i] == '.') i++; 
            int len = i - start;
            char numStr[32];
            memcpy(numStr, inf + start, len);
            numStr[len] = '\0';

            float num = strtof(numStr, NULL); //fazendo coonversão para float
            //Calculo do seno ou cossendo
            float resultado = (func == 's') ? sin(num * PI / 180.0) : cos(num * PI / 180.0);
            char resStr[32];
            snprintf(resStr, sizeof(resStr), "%.6f", resultado);//conversão para strings
            int k = 0;
            while (resStr[k] != '\0') posf[j++] = resStr[k++];//coloca o resultado na pós fixa
            posf[j++] = ' ';

            if (inf[i] == ')') i++;
            continue;
        }

        if (isdigit(inf[i]) || inf[i] == '.') { //verifica se pe número para copiar para a pós fixa
            int start = i;
            while (isdigit(inf[i]) || inf[i] == '.') i++;
            int len = i - start;
            memcpy(posf + j, inf + start, len);
            j += len;
            posf[j++] = ' ';
        } else { //se for operador, converte para string
            char c = inf[i];
            char opStr[2] = {c, '\0'};

            if (c == '(') { //se for parênteses aberto, empilha
                empilharChar(pilha, opStr);
            } else if (c == ')') { //se não for, procura o parêntese de abertira
                while (!pilhaCharVazia(pilha) && topoChar(pilha) != '(') {
                    char *op = desempilharChar(pilha);
                    posf[j++] = op[0];
                    posf[j++] = ' ';
                    free(op);
                }
                //se achar, remove o parênteses de abertura
                if (!pilhaCharVazia(pilha)) { 
                    char *discard = desempilharChar(pilha);
                    free(discard);
                } else {// se não, libera a pilha
                    free(posf);
                    liberarPilhaChar(pilha);
                    return NULL;
                }
            } else { //se for operador normal, empilha conforme a maior precedência 
                while (!pilhaCharVazia(pilha) && topoChar(pilha) != '(' &&
                       precedencia(topoChar(pilha)) >= precedencia(c)) {
                    char *op = desempilharChar(pilha);
                    posf[j++] = op[0];
                    posf[j++] = ' ';
                    free(op);
                }
                empilharChar(pilha, opStr);
            }
            i++;
        }
    }

    //desempilhando o restante
    while (!pilhaCharVazia(pilha)) {
        char *op = desempilharChar(pilha);
        if (op[0] == '(') {
            free(op);
            free(posf);
            liberarPilhaChar(pilha);
            return NULL;
        }
        posf[j++] = op[0];
        posf[j++] = ' ';
        free(op);
    }
    if (j > 0) j--;
    posf[j] = '\0';//finalização da string pos-fixada

    //liberação da pilha e retorno da expressão
    liberarPilhaChar(pilha);
    return posf;
}

//Pilha e funções de Float 
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

// Cálculo da expressão pós fixada
float avaliarPosfixada(char *posf) {
    PilhaFloat *p = criarPilhaFloat();
    char token[64]; //armazenando os valores float
    int i = 0, j = 0;

    while (1) {
        //ignorando os espaços em branco e encerrando o loop ao final da string
        while (posf[i] == ' ') i++;
        if (posf[i] == '\0') break;

        j = 0;
        while (posf[i] != ' ' && posf[i] != '\0') token[j++] = posf[i++];//copiando o valor para o token até encontrar espaço ou o fim da string
        token[j] = '\0';//marca o fim do token

        if (strlen(token) == 1 && strchr("+-*/^R", token[0])) { //verifica se é operador
            float res;

            if (token[0] == 'R') { //caso seja raiz quadrada
                if (pilhaFloatVazia(p)) goto erro;
                //desempilhar o operador
                float a = desempilharFloat(p); 
                if (a < 0) goto erro; //"if" para apontar erro se o número for negativo
                res = sqrtf(a); //calcula raiz para casos válidos
                
            } else { //caso sejam as demais operações, os dois próximos números são desempilhados e calculados
                if (pilhaFloatVazia(p)) goto erro;
                float b = desempilharFloat(p);
                if (pilhaFloatVazia(p)) goto erro;
                float a = desempilharFloat(p);

                switch (token[0]) {
                    case '+': res = a + b; break;
                    case '-': res = a - b; break;
                    case '*': res = a * b; break;
                    case '/':
                        if (b == 0) goto erro;
                        res = a / b; break;
                    case '^': res = powf(a, b); break;
                    default: goto erro;
                }
            }
            empilharFloat(p, res); //o resultado é empilhado
            continue;
        }
        //em caso de não achar um operador, ocorre a conversão para float e logo em seguida esse valor é empilhado
        float val = strtof(token, NULL);
        empilharFloat(p, val);
    }

    if (pilhaFloatVazia(p)) goto erro; //em caso de algum erro ocorrer, o código segue para o bloco de erro, exibe a mensagem e libera a memória da pilha
    float resultado = desempilharFloat(p); //salva o valor que está na pilha
    if (!pilhaFloatVazia(p)) goto erro; //se após o cálculo ainda restar algum número, o código vai para o bloco de erro.
    liberarPilhaFloat(p);// liberação da pilha pós o cálculo
    return resultado; //mostra o resultado

    //em caso de erro, os passos abaixo serão seguidos
erro:
    liberarPilhaFloat(p);
    printf("Erro na avaliacao da expressao\n");
    return 0;
}

// Cálculo de infixa --> nessa função, fazemos a conversão para expressão pós fixada e calculamos como pós fixada
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

// Convesão de pós-fixa para infixa
char* posfixainfix(char *posf) {
    PilhaChar pilha = { NULL };
    int i = 0;
    char token[64];

    while (1) {
        while (posf[i] == ' ') i++;
        if (posf[i] == '\0') break;

        int j = 0;
        while (posf[i] != ' ' && posf[i] != '\0') token[j++] = posf[i++];
        token[j] = '\0';

        if (strlen(token) == 1 && strchr("+-*/^R", token[0])) {
            char *b = desempilharChar(&pilha);
            char *a = desempilharChar(&pilha);
            if (!a || !b) {
                free(a); free(b);
                while (pilha.topo) {
                    char *tmp = desempilharChar(&pilha);
                    free(tmp);
                }
                return NULL;
            }
            int tamanho = strlen(a) + strlen(b) + 6;
            char *expr = malloc(tamanho);
            snprintf(expr, tamanho, "(%s %c %s)", a, token[0], b);
            free(a); free(b);
            empilharChar(&pilha, expr);
        } else {
            char *copia = malloc(strlen(token) + 1);
            strcpy(copia, token);
            empilharChar(&pilha, copia);
        }
    }

    char *resultado = desempilharChar(&pilha);
    while (pilha.topo) {
        char *tmp = desempilharChar(&pilha);
        free(tmp);
    }
    return resultado;
}