#ifndef SVG_H
#define SVG_H

#include "../estruturas/lista.h"
#include "leitorDeArquivos.h"

// Gera arquivo SVG a partir da lista de formas
void gerarSVG(LISTA formas, const char *saidaPath, DadosArquivo arqData, const char *sufixo);

#endif