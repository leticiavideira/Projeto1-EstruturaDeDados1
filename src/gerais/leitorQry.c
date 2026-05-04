#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "leitorQry.h"

#include "../estruturas/lista.h"
#include "../estruturas/fila.h"
#include "leitorDeArquivos.h"
#include "svg.h"
#include "poligono.h"
#include "../formas/forma.h"
#include "../formas/ponto.h"
#include "../formas/linha.h"
#include "../formas/circulo.h"
#include "../formas/retangulo.h"
#include "../formas/texto.h"
#include "../formas/estiloTexto.h"

#define MAX_POL 11

typedef struct {
    LISTA geo;
    LISTA selecionados;
    LISTA banco;
    FILE *txt;
    POLIGONO poligonos[MAX_POL];

    double sel_x, sel_y, sel_w, sel_h;
    int temSelecao;

    LISTA ancorasSelecionadas;
    LISTA pontosRemovidos;
} QrySt;

typedef struct {
    double x, y;
} PontoRemovido;

/* ======================== FUNÇÕES AUXILIARES ======================== */

static void exeInp(QrySt *q, char *params);
static void exeRmp(QrySt *q, char *params);
static void exePol(QrySt *q, char *params);
static void exeClp(QrySt *q, char *params);
static void exeSel(QrySt *q, char *params);
static void exeDels(QrySt *q);
static void exeMcs(QrySt *q, char *params);

static POLIGONO getPoligono(QrySt *q, int p);
static FORMA buscarFormaPorId(LISTA lista, int id);
static int formaDentroRegiao(FORMA f, double x, double y, double w, double h);

/* ======================== FUNÇÃO PRINCIPAL ======================== */

void executarQry(DadosArquivo arqQry, DadosArquivo arqGeo, LISTA formasGeo, char *saidaPath) {
    if (arqQry == NULL || arqGeo == NULL || formasGeo == NULL || saidaPath == NULL)
        return;
        
    QrySt q;
    q.geo = formasGeo;
    q.selecionados = criarLista();
    q.banco = formasGeo;

    q.ancorasSelecionadas = criarLista();
    q.pontosRemovidos = criarLista();

    q.temSelecao = 0;

    for (int i = 1 ; i <= 10 ; i++)
        q.poligonos[i] = criarPoligono();

    //cria nome do txt
    char *nomeGeo = getNomeArq (arqGeo);
    char *nomeQry = getNomeArq (arqQry);

    char baseQry[256], baseGeo[256];
    strcpy (baseGeo, nomeGeo);
    strcpy (baseQry, nomeQry);
    strtok (baseGeo, ".");
    strtok (baseQry, ".");

    size_t tam = strlen(saidaPath) + strlen(baseGeo) + strlen(baseQry) + 10;

    char *pathTxt = malloc(tam);
    if (!pathTxt) {
        printf("Erro de memoria\n");
        return;
    }
    snprintf(pathTxt, tam, "%s/%s-%s.txt", saidaPath, baseGeo, baseQry);

    q.txt = fopen (pathTxt, "w");
        if (!q.txt){
            printf ("Erro ao criar arquivo txt.\n");
            return;
        }
    
    free (pathTxt);


    while (!filaVazia (getFilaLinhasArq (arqQry))) {
        char *linha = (char *) popFila(getFilaLinhasArq (arqQry));
        char *cmd = strtok(linha, " \t\r\n");

        if (!cmd) continue;

        char *params = strtok(NULL, "\n");

        if (strcmp(cmd, "inp") == 0) {
            exeInp(&q, params);

        } else if (strcmp(cmd, "rmp") == 0) {
            exeRmp(&q, params);

        } else if (strcmp(cmd, "clp") == 0) {
            exeClp(&q, params);

        } else if (strcmp(cmd, "sel") == 0) {
            exeSel(&q, params);

        } else if (strcmp(cmd, "dels") == 0) {
            exeDels(&q);
        
        } else if (strcmp(cmd, "mcs") == 0) {
            exeMcs(&q, params);

        } else if (strcmp(cmd, "pol") == 0) {
            exePol(&q, params);

        } else {
            fprintf(q.txt, "Comando desconhecido: %s\n", cmd);
        }
    }

    gerarSVG_QRY(
        q.banco,
        q.selecionados,
        q.pontosRemovidos,
        q.sel_x, q.sel_y, q.sel_w, q.sel_h,
        saidaPath,
        arqGeo,
        arqQry
    );
    
    fclose(q.txt);
    killLista (q.selecionados);
    killLista(q.ancorasSelecionadas);

    for (int i = 1; i <= 10; i++) {
        kill_Poligono(q.poligonos[i]);
    }

    // liberar pontos removidos
    void *el = getInicioLista(q.pontosRemovidos);
    while (el) {
        free(getConteudoElemLista(el));
        el = getProximoLista(q.pontosRemovidos, el);
    }
    killLista(q.pontosRemovidos);
}


/* ======================== IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES ======================== */
static void exeInp(QrySt *q, char *params){
    int p, id;
    sscanf(params, "%d %d", &p, &id);

    FORMA f = buscarFormaPorId(q->geo, id);
    if (!f) return;

    double x, y;
    getAncoraForma(f, &x, &y);

    POLIGONO pol = getPoligono(q, p);
    if (!pol) return;

    insertVertice_Poligono(pol, x, y);

    fprintf(q->txt, "[*] inp %d id=%d (%.2f, %.2f)\n", p, id, x, y);
}

static void exeRmp(QrySt *q, char *params){
    int p;
    sscanf(params, "%d", &p);

    POLIGONO pol = getPoligono(q, p);

    double x, y;
    int ok = removePrimeiroVertice_Poligono (pol, &x, &y);

    if (ok) {
        fprintf (q->txt, "[*] rmp %d (%.2f, %.2f)\n", p, x, y);

    } else {
        fprintf (q->txt, "[*] rmp %d vazio.\n", p);
    }
}

static void exePol(QrySt *q, char *params){
    int p, id;
    double d;
    char corb[32], corp[32];

    sscanf(params, "%d %d %lf %s %s", &p, &id, &d, corb, corp);

    POLIGONO pol = getPoligono(q, p);
    if (!pol) return;

    FILA linhas = criarFila();

    // gera borda
    int qtdBorda = produzBorda_Poligono(pol, linhas);

    // gera preenchimento (hachura)
    hachura_Poligono(pol, d, corp, linhas);

    int idAtual = id;

    int count = 0;

    while (!filaVazia(linhas)) {

        LINHA l = popFila(linhas);

        setId_L(l, idAtual++);

        if (count < qtdBorda) {
            // borda
            setCor_L(l, corb);
        } else {
            // hachura (preenchimento)
            setCor_L(l, corp);
        }

        FORMA f = criarForma(FORMA_LINHA, l);
        pushFimLista(q->banco, f);

        count++;
    }

    killFila(linhas);

    fprintf(q->txt,
        "[*] pol p=%d idInicial=%d d=%.2f corb=%s corp=%s\n",
        p, id, d, corb, corp
    );
}

static void exeClp(QrySt *q, char *params){
    int p;
    sscanf(params, "%d", &p);

    POLIGONO pol = getPoligono(q, p);
    if (!pol) return;

    limparPoligono(pol);

    fprintf(q->txt, "[*] clp p=%d\n", p);
}

static void exeSel(QrySt *q, char *params){

    double x,y,w,h;
    sscanf(params, "%lf %lf %lf %lf", &x,&y,&w,&h);
    
    limparLista(q->selecionados);
    limparLista(q->ancorasSelecionadas);

    q->sel_x = x;
    q->sel_y = y;
    q->sel_w = w;
    q->sel_h = h;
    q->temSelecao = 1;

    fprintf(q->txt, "[*] sel %.2f %.2f %.2f %.2f\n", x,y,w,h);

    void *el = getInicioLista(q->banco);

    while (el) {
        FORMA f = getConteudoElemLista(el);

        if (formaDentroRegiao(f, x,y,w,h)) {

            pushFimLista(q->selecionados, f);

            double fx, fy;
            getAncoraForma(f, &fx, &fy);

            PONTO p = criarPonto(fx, fy);
            pushFimLista(q->ancorasSelecionadas, p);

            fprintf(q->txt, "  -> %d: %s\n",
                getIdForma(f),
                getNomeForma(f)
            );
        }

        el = getProximoLista(q->banco, el);
    }
}

static void exeDels(QrySt *q){
    void *el = getInicioLista(q->selecionados);

    fprintf(q->txt, "[*] dels\n");

    while (el) {

        FORMA f = getConteudoElemLista(el);

        double x,y;
        getAncoraForma(f, &x, &y);

        PontoRemovido *p = malloc(sizeof(PontoRemovido));
        p->x = x;
        p->y = y;
        pushFimLista(q->pontosRemovidos, p);

        fprintf(q->txt, "removido id=%d (%s) (%.2f, %.2f)\n",
            getIdForma(f),
            getNomeForma(f),
            x, y
        );
        printFormaTXT(q->txt, f);

        void *prox = getProximoLista(q->selecionados, el);

        popIdLista(q->banco, f);

        el = prox;
    }

    limparLista(q->selecionados);
}

static void exeMcs(QrySt *q, char *params){

    double dx, dy;
    char corb[32], corp[32];

    sscanf(params, "%lf %lf %s %s", &dx, &dy, corb, corp);

    void *el = getInicioLista(q->selecionados);

    while (el) {

        FORMA f = getConteudoElemLista(el);

        moverForma(f, dx, dy);
        setCorBordaForma(f, corb);
        setCorPreenchimentoForma(f, corp);

        el = getProximoLista(q->selecionados, el);
    }

    fprintf(q->txt,
        "[*] mcs dx=%.2f dy=%.2f corb=%s corp=%s\n",
        dx, dy, corb, corp
    );
}

static POLIGONO getPoligono(QrySt *q, int p) {
    if (p < 1 || p > 10) return NULL;
    return q->poligonos[p];
}

static FORMA buscarFormaPorId(LISTA lista, int id) {
    void *el = getInicioLista(lista);

    while (el != NULL) {
        FORMA f = getConteudoElemLista(el);

        if (getIdForma(f) == id)
            return f;

        el = getProximoLista(lista, el);
    }

    return NULL;
}

static int formaDentroRegiao(FORMA f, double x, double y, double w, double h) {

    FormaTipo tipo = getTipoForma(f);

    if (tipo == FORMA_CIRCULO) {
        CIRCULO c = getDataForma(f);

        double cx = getX_C(c);
        double cy = getY_C(c);
        double r = getR_C(c);

        return (cx - r >= x &&
                cx + r <= x + w &&
                cy - r >= y &&
                cy + r <= y + h);
    }

    if (tipo == FORMA_RETANGULO) {
        RETANGULO r = getDataForma(f);

        double rx = getX_R(r);
        double ry = getY_R(r);
        double rw = getW_R(r);
        double rh = getH_R(r);

        return (rx >= x &&
                rx + rw <= x + w &&
                ry >= y &&
                ry + rh <= y + h);
    }

    if (tipo == FORMA_LINHA) {
        LINHA l = getDataForma(f);

        double x1 = getX1_L(l), y1 = getY1_L(l);
        double x2 = getX2_L(l), y2 = getY2_L(l);

        return (x1 >= x && x1 <= x+w && y1 >= y && y1 <= y+h &&
                x2 >= x && x2 <= x+w && y2 >= y && y2 <= y+h);
    }

    if (tipo == FORMA_TEXTO) {
        TEXTO t = getDataForma(f);

        double tx = getX_T(t);
        double ty = getY_T(t);

        return (tx >= x && tx <= x+w && ty >= y && ty <= y+h);
    }

    return 0;
}
