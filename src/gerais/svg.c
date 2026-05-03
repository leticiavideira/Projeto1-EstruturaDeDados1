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


typedef struct {
    double x, y;
} PontoRemovido;

void gerarSVG_QRY(LISTA banco, LISTA selecionados, LISTA removidos, double sel_x, double sel_y, double sel_w, double sel_h, const char *saidaPath, DadosArquivo arqGeo, DadosArquivo arqQry) {
    char baseGeo[256], baseQry[256];

    strcpy(baseGeo, getNomeArq(arqGeo));
    strcpy(baseQry, getNomeArq(arqQry));

    strtok(baseGeo, ".");
    strtok(baseQry, ".");

    size_t tam = strlen(saidaPath) + strlen(baseGeo) + strlen(baseQry) + 10;

    char *caminho = malloc(tam);
    if (!caminho) {
        printf("Erro de memoria\n");
        return;
    }

    snprintf(caminho, tam, "%s/%s-%s.svg", saidaPath, baseGeo, baseQry);

    FILE *arq = fopen(caminho, "w");
    if (!arq) {
        printf("Erro ao criar SVG QRY\n");
        free(caminho);
        return;
    }

    fprintf(arq, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(arq, "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 1000 1000\">\n");

    // =========================
    // 1. DESENHA FORMAS DO BANCO
    // =========================
    void *el = getInicioLista(banco);

    while (el) {

        FORMA f = getConteudoElemLista(el);

        switch (getTipoForma(f)) {

            case FORMA_CIRCULO: {
                CIRCULO c = getDataForma(f);

                fprintf(arq,
                    "<circle cx='%.2f' cy='%.2f' r='%.2f' fill='%s' stroke='%s' fill-opacity='0.6' stroke-opacity='0.9'/>\n",
                    getX_C(c), getY_C(c), getR_C(c),
                    getCorP_C(c), getCorB_C(c)
                );
                break;
            }
            case FORMA_RETANGULO: {
                RETANGULO r = getDataForma(f);

                fprintf(arq,
                    "<rect x='%.2f' y='%.2f' width='%.2f' height='%.2f' fill='%s' stroke='%s' fill-opacity='0.6' stroke-opacity='0.9'/>\n",
                    getX_R(r), getY_R(r),
                    getW_R(r), getH_R(r),
                    getCorP_R(r), getCorB_R(r)
                );
                break;
            }

            case FORMA_LINHA: {
                LINHA l = getDataForma(f);

                fprintf(arq,
                    "<line x1='%.2f' y1='%.2f' x2='%.2f' y2='%.2f' stroke='%s'/>\n",
                    getX1_L(l), getY1_L(l),
                    getX2_L(l), getY2_L(l),
                    getCor_L(l)
                );
            break;
            }

            case FORMA_TEXTO: {
                TEXTO t = getDataForma(f);

                char *anchor = "start";
                char a = getA_T(t);

                if (a == 'm') anchor = "middle";
                if (a == 'f') anchor = "end";

                fprintf(arq,
                    "<text x='%.2f' y='%.2f' fill='%s' stroke='%s' text-anchor='%s'>%s</text>\n",
                    getX_T(t), getY_T(t),
                    getCorp_T(t), getCorb_T(t),
                    anchor,
                    getTxto_T(t)
                );
                break;
            }

            default:
                break;
        }

        el = getProximoLista(banco, el);
    }

    // =========================
    // 2. DESENHAR REGIÃO DE SELEÇÃO
    // =========================
    if (sel_w > 0 && sel_h > 0) {
        fprintf(arq,
            "<rect x='%.2f' y='%.2f' width='%.2f' height='%.2f' "
            "fill='none' stroke='red' stroke-dasharray='5,5'/>\n",
            sel_x, sel_y, sel_w, sel_h
        );
    }

    // =========================
    // 3. DESENHAR ÂNCORAS SELECIONADAS
    // =========================
    el = getInicioLista(selecionados);

    while (el) {
        FORMA f = getConteudoElemLista(el);

        double x, y;
        getAncoraForma(f, &x, &y);

        fprintf(arq,
            "<circle cx='%.2f' cy='%.2f' r='5' fill='none' stroke='red' stroke-width='2'/>\n",
            x, y
        );

        el = getProximoLista(selecionados, el);
    }

    // =========================
    // 4. DESENHAR X DAS REMOVIDAS
    // =========================
    el = getInicioLista(removidos);

    while (el) {

        PontoRemovido *p = getConteudoElemLista(el);

        double x = p->x;
        double y = p->y;

        double s = 5;

        fprintf(arq,
            "<line x1='%.2f' y1='%.2f' x2='%.2f' y2='%.2f' stroke='red'/>\n",
            x - s, y - s, x + s, y + s
        );

        fprintf(arq,
            "<line x1='%.2f' y1='%.2f' x2='%.2f' y2='%.2f' stroke='red'/>\n",
            x - s, y + s, x + s, y - s
        );

        el = getProximoLista(removidos, el);
    }

    fprintf(arq, "</svg>\n");

    fclose(arq);
    free(caminho);
}
