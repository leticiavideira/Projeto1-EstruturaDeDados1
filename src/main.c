#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gerais/leitorDeArquivos.h"
#include "gerais/leitorGeo.h"
#include "gerais/leitorQry.h"
#include "gerais/svg.h"

int main(int argc, char *argv[]) {

    char *dirEntrada = NULL;
    char *geoNome = NULL;
    char *qryNome = NULL;
    char *dirSaida = NULL;

    // =========================
    // LEITURA DOS ARGUMENTOS
    // =========================
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0 && i + 1 < argc)
            dirEntrada = argv[++i];

        else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
            geoNome = argv[++i];

        else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc)
            qryNome = argv[++i];

        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
            dirSaida = argv[++i];
    }

    // =========================
    // VALIDAÇÃO
    // =========================
    if (!geoNome || !dirSaida) {
        printf("Uso: ./ted [-e <dirEntrada>] -f <geo> [-q <qry>] -o <dirSaida>\n");
        return 1;
    }

    if (!dirEntrada)
        dirEntrada = ".";

    // =========================
    // MONTA CAMINHO GEO
    // =========================
    char pathGeo[1024];

    if (geoNome[0] == '/' || geoNome[0] == '.')
        snprintf(pathGeo, sizeof(pathGeo), "%s", geoNome);
    else
        snprintf(pathGeo, sizeof(pathGeo), "%s/%s", dirEntrada, geoNome);

    // =========================
    // LÊ GEO
    // =========================
    DadosArquivo arqGeo = criarDadosArq(pathGeo);
    if (!arqGeo) {
        printf("Erro ao ler GEO: %s\n", pathGeo);
        return 1;
    }

    SISTEMA sis = processarGeo(arqGeo);

    gerarSVG(getListaFormas(sis), dirSaida, arqGeo, NULL);

    // =========================
    // MONTA E EXECUTA QRY
    // =========================
    if (qryNome) {

        char pathQry[1024];

        if (qryNome[0] == '/' || qryNome[0] == '.')
            snprintf(pathQry, sizeof(pathQry), "%s", qryNome);
        else
            snprintf(pathQry, sizeof(pathQry), "%s/%s", dirEntrada, qryNome);

        DadosArquivo arqQry = criarDadosArq(pathQry);

        if (!arqQry) {
            printf("Erro ao ler QRY: %s\n", pathQry);
            destruirDadosArq(arqGeo);
            killSistemaGeo(sis);
            return 1;
        }

        executarQry(arqQry, arqGeo, getListaFormas(sis), dirSaida);

        destruirDadosArq(arqQry);
    }

    // =========================
    // FINALIZAÇÃO
    // =========================
    killSistemaGeo(sis);
    destruirDadosArq(arqGeo);

    printf("Execução finalizada com sucesso.\n");

    return 0;
}