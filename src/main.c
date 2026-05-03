#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gerais/leitorDeArquivos.h"
#include "gerais/leitorGeo.h"
#include "gerais/leitorQry.h"
#include "gerais/svg.h"

int main(int argc, char *argv[]) {

    char *geoPath = NULL;
    char *outPath = ".";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            geoPath = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outPath = argv[++i];
        }
    }

    if (!geoPath) {
        printf("Arquivo .geo não informado\n");
        return 1;
    }

    char *qryPath = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc)
            geoPath = argv[++i];

        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc)
            outPath = argv[++i];

        else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) // 🔧 NOVO
            qryPath = argv[++i];
    }

    DadosArquivo arq = criarDadosArq(geoPath);

    if (!arq) {
        printf("Erro ao ler arquivo\n");
        return 1;
    }

    SISTEMA sis = processarGeo(arq);

    gerarSVG(getListaFormas(sis), outPath, arq, NULL);

    if (qryPath) {
        DadosArquivo arqQry = criarDadosArq(qryPath);

        executarQry(arqQry, getListaFormas(sis), outPath);

        destruirDadosArq(arqQry);
    }

    killSistemaGeo(sis);
    destruirDadosArq(arq);

    printf("SVG gerado com sucesso.\n");

    return 0;

}