#include <stdio.h>
#include <stdlib.h>
#include "unity.h"

#include "../gerais/leitorQry.h"
#include "../gerais/leitorGeo.h"
#include "../gerais/leitorDeArquivos.h"
#include "../estruturas/lista.h"

void setUp(void) {}
void tearDown(void) {}

/* =======================================================
   AUXILIARES
   ======================================================= */

void criarGeo(const char* path) {
    FILE* f = fopen(path, "w");
    fprintf(f, "c 1 10 10 5 red blue\n");
    fprintf(f, "r 2 20 20 10 5 green yellow\n");
    fclose(f);
}

void criarQry(const char* path) {
    FILE* f = fopen(path, "w");
    fprintf(f, "del 1\n");  // exemplo de comando simples
    fclose(f);
}

/* =======================================================
   TESTES
   ======================================================= */

void test_executarQry_Valido() {
    criarGeo("teste.geo");
    criarQry("teste.qry");

    DadosArquivo geo = criarDadosArq("teste.geo");
    DadosArquivo qry = criarDadosArq("teste.qry");

    SISTEMA s = processarGeo(geo);
    LISTA formas = getListaFormas(s);

    executarQry(qry, geo, formas, "./");

    TEST_ASSERT_NOT_NULL(formas);

    killSistemaGeo(s);
    destruirDadosArq(geo);
    destruirDadosArq(qry);
}

void test_executarQry_parametrosNull() {
    executarQry(NULL, NULL, NULL, NULL);
    // não deve crashar
}

void test_executarQry_qryInvalido() {
    DadosArquivo geo = criarDadosArq("teste.geo");

    SISTEMA s = processarGeo(geo);
    LISTA formas = getListaFormas(s);

    executarQry(NULL, geo, formas, "./");

    killSistemaGeo(s);
    destruirDadosArq(geo);
}

/* =======================================================
   MAIN
   ======================================================= */

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_executarQry_Valido);
    RUN_TEST(test_executarQry_parametrosNull);
    RUN_TEST(test_executarQry_qryInvalido);

    return UNITY_END();
}