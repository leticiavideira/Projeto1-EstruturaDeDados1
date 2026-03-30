#ifndef PILHA_H
#define PILHA_H

typedef void* PILHA;

PILHA criarPilha ();

int pushPilha (PILHA p, void *conteudo);

void *popPilha (PILHA p);

void *topoPilha (PILHA p);

int tamanhoPilha (PILHA p);

int pilhaVazia (PILHA p);

void imprimirConteudoPilha (PILHA p);

void limparPilha (PILHA p);

void killPilha (PILHA p);

#endif