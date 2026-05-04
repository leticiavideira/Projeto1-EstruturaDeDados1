#include <stdlib.h>
#include <stdio.h>

#include "ponto.h"

typedef struct {
    double x, y;
} PontoSt;

PONTO criarPonto(double x, double y) {
    PontoSt *p = malloc(sizeof(PontoSt));
        if (p == NULL)
            return NULL;

    p->x = x;
    p->y = y;
    return p;
}

void getPonto(PONTO p, double *x, double *y) {
    PontoSt *pt = p;
    *x = pt->x;
    *y = pt->y;
}

void killPonto(PONTO p) {
    free(p);
}