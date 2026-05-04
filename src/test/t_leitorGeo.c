#include <stdio.h>
#include <stdlib.h>
#include "unity.h"

#include "../gerais/leitorGeo.h"
#include "../gerais/leitorDeArquivos.h"
#include "../estruturas/lista.h"

void setUp(void) {}
void tearDown(void) {}

/* =======================================================
   AUXILIAR
   ======================================================= */

void criarArquivoGeoSimples(const char* path) {
    FILE* f = fopen(path, "w");
    fprintf(f, "c 1 10 10 5 red blue\n");
    fprintf(f, "r 2 20 20 10 5 green yellow\n");
    fclose(f);
}

/* =======================================================
   TESTES
   ======================================================= */

void test_processarGeo_Valido() {
    const char* path = "teste.geo";
    criarArquivoGeoSimples(path);

    DadosArquivo d = criarDadosArq((char*)path);
    SISTEMA s = processarGeo(d);

    TEST_ASSERT_NOT_NULL(s);

    LISTA l = getListaFormas(s);
    TEST_ASSERT_NOT_NULL(l);
    TEST_ASSERT_TRUE(tamanhoLista(l) > 0);

    killSistemaGeo(s);
    destruirDadosArq(d);
}

void test_processarGeo_ArquivoInexistente() {
    DadosArquivo d = criarDadosArq("nao_existe.geo");

    TEST_ASSERT_NULL(d);
}

void test_getListaFormas_Invalido() {
    TEST_ASSERT_NULL(getListaFormas(NULL));
}

void test_killSistemaGeo_Null() {
    killSistemaGeo(NULL); // não deve crashar
}

/* =======================================================
   MAIN
   ======================================================= */

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_processarGeo_Valido);
    RUN_TEST(test_processarGeo_ArquivoInexistente);
    RUN_TEST(test_getListaFormas_Invalido);
    RUN_TEST(test_killSistemaGeo_Null);

    return UNITY_END();
}