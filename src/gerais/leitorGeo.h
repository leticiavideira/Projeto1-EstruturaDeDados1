#ifndef LEITOR_GEO_H
#define LEITOR_GEO_H

#include "../estruturas/lista.h"
#include "leitorDeArquivos.h"

typedef void* SISTEMA;

SISTEMA processarGeo (DadosArquivo arqData);

LISTA getListaFormas(SISTEMA s);

void killSistemaGeo (SISTEMA s);

#endif