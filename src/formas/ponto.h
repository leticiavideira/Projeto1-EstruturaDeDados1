#ifndef PONTO_H
#define PONTO_H

typedef void* PONTO;

PONTO criarPonto(double x, double y);

void getPonto(PONTO p, double *x, double *y);

void killPonto(PONTO p);

#endif