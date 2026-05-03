#ifndef FORMA_H
#define FORMA_H

typedef enum {
    FORMA_CIRCULO,
    FORMA_RETANGULO,
    FORMA_LINHA,
    FORMA_TEXTO,
    FORMA_ESTILO_TEXTO
} FormaTipo;

typedef void* FORMA;

FORMA criarForma(FormaTipo tipo, void *data);

char* getNomeForma (FORMA f);

int getIdForma(FORMA f);

void getAncoraForma(FORMA f, double *x, double *y);

FormaTipo getTipoForma(FORMA f);

void* getDataForma(FORMA f);

void setCorBordaForma(FORMA f, char *cor);

void setCorPreenchimentoForma(FORMA f, char *cor);

void moverForma(FORMA f, double dx, double dy);

void printFormaTXT(FILE *txt, FORMA f);

void killForma(FORMA f);

#endif