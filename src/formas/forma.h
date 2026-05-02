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

FormaTipo getTipoForma(FORMA f);

void* getDataForma(FORMA f);

void killForma(FORMA f);

#endif