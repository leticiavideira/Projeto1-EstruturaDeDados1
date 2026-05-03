#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

typedef struct elementoLista{
    void *conteudo;
    struct elementoLista *prox;
} elementoLista;

typedef struct {
    elementoLista *inicio;
    elementoLista *fim;
    int tamanho;
}Lista;

LISTA criarLista () {
    Lista *l = (Lista *) malloc (sizeof (Lista));
        if (l == NULL) {
            printf ("Erro ao alocar memoria para criar lista");
            return NULL;
        }

    l->inicio = NULL;
    l->fim = NULL;
    l->tamanho = 0;

    return ((Lista *) l);
}

int pushInicioLista (LISTA l, void *conteudo) {
    if (l == NULL)
        return 0;
    
    Lista *l1 = (Lista *) l;

    elementoLista *new = (elementoLista *) malloc (sizeof (elementoLista));
        if (new == NULL){
            printf ("Erro ao alocar memoria para novo elemento lista.\n");
            return 0;
        }
                
    if (l1->inicio == l1->fim){
        l1->fim = new;

    } else {
        new->prox = l1->inicio;
    }
    
    l1->inicio = new;
    new->conteudo = conteudo;
    l1->tamanho++;

    return 1;
}

int pushFimLista (LISTA l, void *conteudo) {
    if (l == NULL)
        return 0;

    Lista *l1 = (Lista *) l;

    elementoLista *new = (elementoLista *) malloc (sizeof (elementoLista));
        if (new == NULL){
            printf ("Erro ao alocar memoria para elemento lista");
            return 0;
        }

    new->conteudo = conteudo;
    new->prox = NULL;

    if (listaVazia(l1)){
        l1->inicio = new;

    } else {
        l1->fim->prox = new;

    }

    l1->fim = new;
    l1->tamanho++;    

    return 1;
}

void* getInicioLista(LISTA l) {
    if (l == NULL)
        return NULL;

    Lista *l1 = (Lista *) l;

    if (!l1->inicio)
        return NULL;

    return (l1->inicio);
}

void* getProximoLista(LISTA l, void* atual) {
    if (l == NULL || atual == NULL)
        return NULL;

    elementoLista *no = (elementoLista *) atual;

    return (no->prox);
}

void* getConteudoElemLista (void *elemento) {
    if (elemento == NULL)
        return NULL;

    elementoLista *no = (elementoLista *) elemento;

    return (no->conteudo);
}

void *popInicioLista (LISTA l) {
    if (l == NULL)
        return NULL;
    
    Lista *l1 = (Lista *) l;

    if (l1->tamanho == 0){
        printf ("Lista vazia, nao eh possivel remover do inicio.\n");
        return NULL;
    }

    elementoLista *remover = l1->inicio;
    void *conteudo = remover->conteudo;

    if (l1->fim == l1->inicio)
        l1->fim = NULL;
    
    l1->inicio = remover->prox;
    free (remover);
    l1->tamanho--;

    return (conteudo);
}

void *popFimLista (LISTA l) {
    if (l == NULL)
        return NULL;

    Lista *l1 = (Lista *) l;

    if (l1->tamanho == 0){
       printf ("Lista vazia, nao eh possivel remover do fim.\n");
       return NULL;
    }

    elementoLista *remover = l1->fim;
    void *conteudo = remover->conteudo;

    if (l1->fim == l1->inicio){
        l1->inicio = NULL;
        l1->fim = NULL;
        
    } else {
        elementoLista *temp = l1->inicio;

        while (temp->prox != l1->fim){
            temp = temp->prox;
        }

        temp->prox = NULL;
        l1->fim = temp;
    }

    free (remover);
    l1->tamanho--;
    return (conteudo);
}

void *popIdLista (LISTA l, void *conteudo) {
    if (l == NULL) 
        return NULL;

    Lista *l1 = (Lista *) l;

    elementoLista *remover = buscaIdLista (l1, conteudo);
    void *c = remover->conteudo;

    if (remover == NULL){
        printf ("Nao foi possivel remover o conteudo.\n");
        return NULL;
    }
    
    if (remover == l1->inicio){
        l1->inicio = remover->prox;

    } else {
        elementoLista *temp = l1->inicio;

        while (temp->prox != remover) {
            temp = temp->prox;
        }

        temp->prox = remover->prox;
    }

    free (remover);
    l1->tamanho--;
    return (c);
}

void *buscaIdLista (LISTA l, void *conteudo) {
    if (l == NULL)
        return NULL;

    Lista *l1 = (Lista *) l;

    if (l1->tamanho == 0){
       printf ("Lista vazia, nao eh possivel buscar elemento.\n");
       return NULL;
    }

    elementoLista *aux = l1->inicio;

    if (aux == NULL) {
        printf ("Lista vazia.\n");
        return NULL;
    }

    while (aux != NULL) {
        if (aux->conteudo == conteudo){
            return (elementoLista *) aux;
        }
        aux = aux->prox;
    }

    printf ("Conteudo nao encontrado na lista.\n");
    return NULL;
}

int tamanhoLista (LISTA l) {
    if (l == NULL)
        return -1;

    Lista *l1 = (Lista *) l;

    return (l1->tamanho);
}

int listaVazia (LISTA l) {
    if (l == NULL)
        return -1;

    Lista *l1 = (Lista *) l;

    return (l1->tamanho == 0);
}

void imprimirConteudoLista (LISTA l) {
    if (l == NULL){
        return;
    }

    Lista *l1 = (Lista *) l;
    elementoLista *aux = l1->inicio;

    if (aux == NULL){
        printf ("Lista vazia.\n");
    } else {
        while (aux != NULL){
            printf ("- %s\n", (char *) aux->conteudo);
            aux = aux->prox;
        }
    }

    return;
}

void limparLista (LISTA l) {
    if (l == NULL)
        return;
    
    Lista *l1 = (Lista *) l;

    if (l1->tamanho == 0){
        return;
        
    } else {
        while (l1->tamanho != 0){
            popInicioLista (l1);
        }
    }
    return;
}

void killLista (LISTA l) {
    if (l == NULL)
        return;
    
    Lista *l1 = (Lista *) l;

    limparLista (l1);
    free (l1);
    return;
}