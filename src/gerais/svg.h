#ifndef SVG_H
#define SVG_H

#include "../estruturas/lista.h"
#include "leitorDeArquivos.h"

// Gera arquivo SVG a partir da lista de formas
void gerarSVG(LISTA formas, const char *saidaPath, DadosArquivo arqData, const char *sufixo);

void gerarSVG_QRY(LISTA banco, LISTA selecionados, LISTA removidos, double sel_x, double sel_y, double sel_w, double sel_h, const char *saidaPath, DadosArquivo arqGeo, DadosArquivo arqQry);

#endif