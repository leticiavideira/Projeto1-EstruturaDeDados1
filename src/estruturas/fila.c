#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

typedef struct elementoFila{
    void *conteudo;
    struct elementoFila *prox;
} elementoFila;

typedef struct {
    elementoFila *inicio;
    elementoFila *fim;
    int tamanho;
} Fila;

FILA criarFila () {
    Fila *f = (Fila *) malloc (sizeof (Fila));
        if (f == NULL) {
            printf ("Erro ao alocar memoria para fila.\n");
            return NULL;
        }

    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;

    return ((Fila *) f);
}

int pushFila (FILA f, void *conteudo) {
    if (f == NULL) 
        return 0;
    
    Fila *f1 = ((Fila *) f);

    elementoFila *new = (elementoFila *) malloc (sizeof (elementoFila));
        if (new == NULL){
            printf ("Erro ao alocar memoria para novo elemento da fila.\n");
                return 0;
        }
    
    new->conteudo = conteudo;
    new->prox = NULL;

    if (filaVazia (f1)){
        f1->inicio = new;

    } else {
        f1->fim->prox = new;

    }

    f1->fim = new;
    f1->tamanho++;

    return 1;
}

void *popFila (FILA f) {
    if (f == NULL)
        return NULL;
    
    Fila *f1 = ((Fila *) f);
        if(f1->inicio == NULL)
            return NULL;

    elementoFila *remover = f1->inicio;
    void *conteudo = remover->conteudo;

        if (f1->inicio == f1->fim)
            f1->fim = NULL;
    
    f1->inicio = remover->prox;
    free (remover);
    f1->tamanho--;

    return (conteudo);
}

void *primeiroElementoFila (FILA f) {
    if (f == NULL)
        return NULL;
    
    Fila *f1 = (Fila *) f;
        if (f1->inicio == NULL)
            return NULL;
    return (f1->inicio->conteudo);
}

int tamanhoFila (FILA f) {
    if (f == NULL)
        return 0;
    
    Fila *f1 = ((Fila *) f);

    return (f1->tamanho);
}

int filaVazia (FILA f) {
    if (f == NULL)
        return -1;

    Fila *f1 = ((Fila *) f);

    return (f1->tamanho == 0);
}

void imprimirConteudoFila (FILA f) {
    if (f == NULL)
        return;
    
    Fila *f1 = ((Fila *) f);
    elementoFila *aux = f1->inicio;

    if (aux == NULL){
        printf ("Fila vazia.\n");
    } else {
        while (aux != NULL) {
            printf ("- %s\n", (char *) aux->conteudo);
            aux = aux->prox;
        }
    }
    
    return;
}

void limparFila (FILA f) {
    if (f == NULL)
        return;
    
    Fila *f1 = ((Fila *) f);

    while (f1->tamanho != 0) {
        popFila (f1);
    }
    return;
}

void killFila (FILA f){
    if (f == NULL)
        return;
    
    Fila *f1 = ((Fila *) f);

    limparFila (f1);
    free (f1);
    return;
}