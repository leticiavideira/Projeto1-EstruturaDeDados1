#ifndef LISTA_H
#define LISTA_H

typedef void* LISTA;

LISTA criarLista ();

int pushInicioLista (LISTA l, void *conteudo);

int pushFimLista (LISTA l, void *conteudo);

void *popInicioLista (LISTA l);

void *popFimLista (LISTA l);

void *popIdLista (LISTA l, void *conteudo);

void *buscaIdLista (LISTA l, void *conteudo);

int tamanhoLista (LISTA l);

int listaVazia (LISTA l);

void imprimirConteudoLista (LISTA l);

void limparLista (LISTA l);

void killLista (LISTA l);

#endif