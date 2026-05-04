#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "leitorGeo.h"

#include "../estruturas/lista.h"
#include "../estruturas/fila.h"
#include "../gerais/leitorDeArquivos.h"

#include "../formas/forma.h"
#include "../formas/circulo.h"
#include "../formas/retangulo.h"
#include "../formas/linha.h"
#include "../formas/texto.h"
#include "../formas/estiloTexto.h"


typedef struct {
    LISTA formas;   // banco de dados principal
} SistemaSt;

/* ======================== FUNÇÕES AUXILIARES ======================== */
static void exeCmd_Circulo(SistemaSt *sis);
static void exeCmd_Retangulo(SistemaSt *sis);
static void exeCmd_Linha(SistemaSt *sis);
static void exeCmd_Texto(SistemaSt *sis);
static void exeCmd_EstiloTexto(SistemaSt *sis);

/* ======================== FUNÇÔES PRINCIPAIS ======================== */
SISTEMA processarGeo (DadosArquivo arqData){
    SistemaSt *sis = malloc (sizeof (SistemaSt));
        if (sis == NULL){
            printf ("Erro ao alocar memoria. \n");
            exit(1);
        }
    
    sis->formas = criarLista();

    while (!filaVazia(getFilaLinhasArq(arqData))){
        char *linha = (char *) popFila (getFilaLinhasArq(arqData));
        char *cmd = strtok (linha, " ");

        if (!cmd) continue;

        if (strcmp (cmd, "c") == 0) {
            exeCmd_Circulo(sis);

        } else if (strcmp(cmd, "r") == 0) {
            exeCmd_Retangulo(sis);

        } else if (strcmp(cmd, "l") == 0) {
            exeCmd_Linha(sis);

        } else if (strcmp(cmd, "t") == 0) {
            exeCmd_Texto(sis);

        } else if (strcmp(cmd, "ts") == 0) {
            exeCmd_EstiloTexto(sis);

        } else {
            printf("Comando invalido para forma: %s\n", cmd);
        }
    }

    return sis;    
}


LISTA getListaFormas(SISTEMA s) {
    if (s == NULL)
        return NULL;
    SistemaSt *sis = (SistemaSt *) s;
    return sis->formas;
}


void killSistemaGeo (SISTEMA s){
    if (s == NULL)
        return;
    SistemaSt *sis = (SistemaSt *) s;
    
    while (!listaVazia(sis->formas)) {
        FORMA f = popInicioLista (sis->formas);
        killForma (f);
    }

    
    killLista (sis->formas);
    free (sis);
}

/* ======================== IMPLEMENTAÇÃO DAS FUNÇÕES AUXILIARES ======================== */

static void exeCmd_Circulo(SistemaSt *sis) {
    char *id = strtok(NULL, " ");
    char *x = strtok(NULL, " ");
    char *y = strtok(NULL, " ");
    char *raio = strtok(NULL, " ");
    char *corb = strtok(NULL, " ");
    char *corp = strtok(NULL, " ");

    CIRCULO c = criaCirculo(
        atoi(id),
        atof(x),
        atof(y),
        atof(raio),
        corb,
        corp
    );

    FORMA f = criarForma (FORMA_CIRCULO, c);

    pushFimLista (sis->formas, f);
}

static void exeCmd_Retangulo(SistemaSt *sis) {
    char *id = strtok(NULL, " ");
    char *x = strtok(NULL, " ");
    char *y = strtok(NULL, " ");
    char *w = strtok(NULL, " ");
    char *h = strtok(NULL, " ");
    char *corb = strtok(NULL, " ");
    char *corp = strtok(NULL, " ");

    RETANGULO r = criaRetangulo(
        atoi(id),
        atof(x),
        atof(y),
        atof(w),
        atof(h),
        corb,
        corp
    );
    
    FORMA f = criarForma (FORMA_RETANGULO, r);

    pushFimLista (sis->formas, f);
}

static void exeCmd_Linha(SistemaSt *sis) {
    char *id = strtok(NULL, " ");
    char *x1 = strtok(NULL, " ");
    char *y1 = strtok(NULL, " ");
    char *x2 = strtok(NULL, " ");
    char *y2 = strtok(NULL, " ");
    char *cor = strtok(NULL, " ");

    LINHA l = criaLinha(
        atoi(id),
        atof(x1),
        atof(y1),
        atof(x2),
        atof(y2),
        cor
    );

    FORMA f = criarForma (FORMA_LINHA, l);

    pushFimLista (sis->formas, f);
}

static void exeCmd_Texto(SistemaSt *sis) {
    char *id = strtok(NULL, " ");
    char *x = strtok(NULL, " ");
    char *y = strtok(NULL, " ");
    char *corb = strtok(NULL, " ");
    char *corp = strtok(NULL, " ");
    char *a = strtok(NULL, " ");

    char *txto = strtok(NULL, ""); //pega o resto da linha

    TEXTO t = criaTexto(
        atoi(id),
        atof(x),
        atof(y),
        corb,
        corp,
        *a,
        txto
    );

    FORMA f = criarForma (FORMA_TEXTO, t);

    pushFimLista (sis->formas, f);
}

static void exeCmd_EstiloTexto(SistemaSt *sis) {
    char *fF = strtok(NULL, " ");
    char *fW = strtok(NULL, " ");
    char *fS = strtok(NULL, " ");

    ESTILO_TEXTO ts = criaEstiloTexto(
        fF,
        fW,
        atof(fS)
    );

    FORMA f = criarForma (FORMA_ESTILO_TEXTO, ts);

    pushFimLista (sis->formas, f);
}