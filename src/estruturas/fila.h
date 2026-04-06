#ifndef FILA_H
#define FILA_H

typedef void *FILA;

FILA criarFila ();

int pushFila (FILA f, void *conteudo);

void *popFila (FILA f);

void *primeiroElementoFila (FILA f);

int tamanhoFila (FILA f);

int filaVazia (FILA f);

void imprimirConteudoFila (FILA f);

void limparFila (FILA f);

void killFila (FILA f);

#endif