#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"

#include "../estruturas/lista.h"

#include "../formas/forma.h"
#include "../formas/circulo.h"
#include "../formas/retangulo.h"
#include "../formas/linha.h"
#include "../formas/texto.h"
#include "../formas/estiloTexto.h"

// =========================
// FUNÇÃO AUXILIAR: montar caminho
// =========================
static char *montarCaminhoSVG(const char *saidaPath, DadosArquivo arqData, const char *sufixo) {

    char *nomeOriginal = getNomeArq(arqData);
    if (!nomeOriginal) return NULL;

    char nomeBase[256];
    strcpy(nomeBase, nomeOriginal);

    // remove extensão
    char *ponto = strrchr(nomeBase, '.');
    if (ponto) *ponto = '\0';

    // adiciona sufixo
    if (sufixo) {
        strcat(nomeBase, "-");
        strcat(nomeBase, sufixo);
    }

    // monta caminho final
    size_t tam = strlen(saidaPath) + strlen(nomeBase) + 6;
    char *caminho = malloc(tam);

    if (!caminho) return NULL;

    snprintf(caminho, tam, "%s/%s.svg", saidaPath, nomeBase);

    return caminho;
}


// =========================
// FUNÇÃO PRINCIPAL
// =========================
void gerarSVG(LISTA formas, const char *saidaPath, DadosArquivo arqData, const char *sufixo) {

    if (!formas || !saidaPath || !arqData) {
        printf("Erro: parametros invalidos em gerarSVG\n");
        return;
    }

    // montar caminho
    char *caminho = montarCaminhoSVG(saidaPath, arqData, sufixo);

    if (!caminho) {
        printf("Erro ao montar caminho SVG\n");
        return;
    }

    FILE *arq = fopen(caminho, "w");

    if (!arq) {
        printf("Erro ao criar arquivo SVG\n");
        free(caminho);
        return;
    }

    // =========================
    // CABEÇALHO
    // =========================
    fprintf(arq, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(arq, "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 1000 1000\">\n");

    // =========================
    // ITERAÇÃO NA LISTA (CORRETA)
    // =========================
    void *el = getInicioLista(formas);

    while (el != NULL) {

        FORMA f = getConteudoElemLista(el);

        switch (getTipoForma(f)) {

            case FORMA_CIRCULO: {
                CIRCULO c = getDataForma(f);

                fprintf(arq,
                    "<circle cx='%.2f' cy='%.2f' r='%.2f' fill='%s' stroke='%s'/>\n",
                    getX_C(c),
                    getY_C(c),
                    getR_C(c),
                    getCorP_C(c),
                    getCorB_C(c)
                );
                break;
            }

            case FORMA_RETANGULO: {
                RETANGULO r = getDataForma(f);

                fprintf(arq,
                    "<rect x='%.2f' y='%.2f' width='%.2f' height='%.2f' fill='%s' stroke='%s'/>\n",
                    getX_R(r),
                    getY_R(r),
                    getW_R(r),
                    getH_R(r),
                    getCorP_R(r),
                    getCorB_R(r)
                );
                break;
            }

            case FORMA_LINHA: {
                LINHA l = getDataForma(f);

                fprintf(arq,
                    "<line x1='%.2f' y1='%.2f' x2='%.2f' y2='%.2f' stroke='%s'/>\n",
                    getX1_L(l),
                    getY1_L(l),
                    getX2_L(l),
                    getY2_L(l),
                    getCor_L(l)
                );
                break;
            }

            case FORMA_TEXTO: {
                TEXTO t = getDataForma(f);

                char ancora = getA_T(t);
                char *txtA = "start";

                if (ancora == 'm' || ancora == 'M') txtA = "middle";
                else if (ancora == 'f' || ancora == 'F') txtA = "end";

                fprintf(arq,
                    "<text x='%.2f' y='%.2f' fill='%s' stroke='%s' text-anchor='%s'>%s</text>\n",
                    getX_T(t),
                    getY_T(t),
                    getCorp_T(t),
                    getCorb_T(t),
                    txtA,
                    getTxto_T(t)
                );
                break;
            }

            case FORMA_ESTILO_TEXTO:
                // opcional: ignorar ou implementar depois
                break;
        }

        el = getProximoLista(formas, el);
    }

    // =========================
    // FINALIZAÇÃO
    // =========================
    fprintf(arq, "</svg>\n");

    fclose(arq);
    free(caminho);
}