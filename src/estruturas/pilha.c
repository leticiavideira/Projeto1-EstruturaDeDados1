#include <stdio.h>
#include <stdlib.h>

#include "pilha.h"

typedef struct elementoPilha{
    void *conteudo;
    struct elementoPilha *prox;
} elementoPilha;

typedef struct {
    elementoPilha *topo;
    int tamanho;
} Pilha;

PILHA criarPilha (){
    Pilha *p = (Pilha *) malloc (sizeof (Pilha));
        if (p == NULL) {
            printf ("Erro ao alocar memoria para criacao da pilha.\n");
            return NULL;
        }
    
    p->topo = NULL;
    p->tamanho = 0;

    return ((Pilha *) p);
}

int pushPilha (PILHA p, void *conteudo) {
    if (p == NULL)
        return 0;
    
    Pilha *p1 = ((Pilha *) p);

    elementoPilha *new = (elementoPilha *) malloc (sizeof (elementoPilha));
        if (new == NULL){
            printf ("Erro ao alocar memoria para novo elemento pilha. \n");
            return 0;
        }
    
    new->conteudo = conteudo;
    new->prox = p1->topo;
    p1->topo = new;
    p1->tamanho++;

    return 1;
}

void *popPilha (PILHA p) {
    if (p == NULL)
        return NULL;

    Pilha *p1 = ((Pilha *) p);
        if (p1->topo == NULL)
            return NULL;

    elementoPilha *remover = p1->topo;
    void *conteudo = remover->conteudo;

    p1->topo = remover->prox;
    free (remover);
    p1->tamanho--;

    return (conteudo);
}

void *topoPilha (PILHA p) {
    if (p == NULL)
        return NULL;

    Pilha *p1 = ((Pilha *) p);
        if (p1->topo == NULL)
            return NULL;
    return (p1->topo->conteudo);
}

int tamanhoPilha (PILHA p) {
    if (p == NULL)
        return -1;
    
    Pilha *p1 = ((Pilha *) p);

    return (p1->tamanho);
}

int pilhaVazia (PILHA p) {
    if (p == NULL)
        return -1;

    Pilha *p1 = ((Pilha *) p);

    return (p1->tamanho == 0);
}

void imprimirConteudoPilha (PILHA p) {
    if (p == NULL)
        return;
    
    Pilha *p1 = ((Pilha *) p);
    elementoPilha *aux = p1->topo;

    if (aux == NULL){
        printf ("Pilha vazia.\n");
    } else {
        while (aux != NULL) {
            printf ("- %s\n", (char *) aux->conteudo);
            aux = aux->prox;
        }
    }
    
    return;
}

void limparPilha (PILHA p) {
    if (p == NULL)
        return;
    
    Pilha *p1 = ((Pilha *) p);

    while (p1->tamanho != 0) {
        popPilha (p1);
    } 
    
    return;
}

void killPilha (PILHA p) {
    if (p == NULL)
        return;

    Pilha *p1 = ((Pilha *) p);

    limparPilha (p1);
    free (p1);
    return;
}