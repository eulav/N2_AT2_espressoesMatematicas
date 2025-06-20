# N2 - AT2 - Estrutura de Dados

## Descrição do Projeto

Para este trabalho, a sua equipe deverá desenvolver um programa em linguagem **C** capaz de **avaliar expressões matemáticas escritas**, com suporte a:

- Operações básicas:
  - Adição
  - Subtração
  - Multiplicação
  - Divisão
  - Potenciação
  - Radiciação
- Funções especiais:
  - Seno
  - Cosseno

O programa deverá ser capaz de **converter e avaliar expressões entre as formas infixada e pós-fixada**, utilizando **pilhas** como estrutura fundamental.

---

### Notação Infixada

A notação infixada é o formato mais comum usado pelos seres humanos para escrever expressões matemáticas.

Nela, os **operadores** (como `+`, `-`, `*`, `/`) são escritos **entre os operandos** (números ou variáveis).

**Exemplos:**

- `A + B`
- `3 * (4 + 5)`
- `(7 - 2) / 3`

#### Regras:
- **Precedência dos operadores** (ex.: multiplicação antes da soma)
- **Associatividade** (esquerda ou direita)
- **Parênteses** para explicitar a ordem de avaliação

---

### Notação Pós-Fixada (RPN - Reverse Polish Notation)

Forma de escrever expressões matemáticas onde os **operadores vêm após os operandos**, eliminando a necessidade de parênteses.

**Características:**

- Não usa parênteses para ordem das operações
- Ordem dos operadores define a prioridade
- Avaliação simples por pilha (da esquerda para a direita)

**Exemplo:**

A expressão infixada `(3 + 4) * 5` em notação pós-fixada fica:  
`3 4 + 5 *`

Avaliação da expressão `2 3 4 * +`:

1. Empilha `2`, `3`, `4`
2. Aplica `*` em `3` e `4` → `12`
3. Empilha `12`
4. Aplica `+` em `2` e `12` → Resultado: `14`

---

## Requisitos do Projeto

### I. Conversão de Infixada para Pós-Fixada

- O programa deve:
  - Receber uma expressão no formato infixado (ex.: `(3 + 4) * 5`)
  - Converter para pós-fixada (ex.: `3 4 + 5 *`)
  - Exibir o resultado

- A conversão deve respeitar:
  - Precedência dos operadores (`*` e `/` antes de `+` e `-`)
  - Associatividade (geralmente da esquerda para a direita)
  - Balanceamento de parênteses

---

### II. Conversão de Pós-Fixada para Infixada

- O programa deve:
  - Receber uma expressão pós-fixada (ex.: `3 4 + 5 *`)
  - Reconstruir a forma infixada (ex.: `(3 + 4) * 5`)
  - Exibir o resultado

- Exige:
  - Uso de pilhas para reconstrução
  - Inserção correta de parênteses para preservar a lógica original

---

### III. Testes de Operações

O programa deve realizar testes com:

- Adição
- Subtração
- Multiplicação
- Potenciação
- Radiciação
- Seno
- Cosseno

---

## Estrutura do Código

O código deve ser organizado como um **TAD (Tipo Abstrato de Dados)** nos seguintes arquivos:

- `expressao.h`
- `expressao.c`
- `main.c`

Deve também oferecer suporte a **números decimais** (`float`).
