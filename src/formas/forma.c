#include <stdio.h>
#include <stdlib.h>

#include "forma.h"

#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "estiloTexto.h"

typedef struct {
    FormaTipo tipo;
    void *data;
} FormaSt;

FORMA criarForma(FormaTipo tipo, void *data) {
    FormaSt *f = malloc(sizeof(FormaSt));
    if (!f) exit(1);

    f->tipo = tipo;
    f->data = data;

    return f;
}

FormaTipo getTipoForma(FORMA f) {
    return ((FormaSt*)f)->tipo;
}

void* getDataForma(FORMA f) {
    return ((FormaSt*)f)->data;
}

void killForma(FORMA f) {
    FormaSt *forma = (FormaSt*) f;

    switch (forma->tipo) {
        case FORMA_CIRCULO:
            kill_C(forma->data);
            break;

        case FORMA_RETANGULO:
            kill_R(forma->data);
            break;

        case FORMA_LINHA:
            kill_L(forma->data);
            break;

        case FORMA_TEXTO:
            kill_T(forma->data);
            break;

        case FORMA_ESTILO_TEXTO:
            killEstiloTexto(forma->data);
            break;
    }

    free(forma);
}