#include <stdio.h>
#include <string.h>
#include "unity.h"

#include "../gerais/leitorDeArquivos.h"
#include "../estruturas/fila.h"

void setUp(void) {}
void tearDown(void) {}

/* =======================================================
   AUXILIAR
   ======================================================= */

void criarArquivoTeste() {
    FILE *f = fopen("arquivo.txt", "w");
    fprintf(f, "linha1\nlinha2\nlinha3\n");
    fclose(f);
}

/* =======================================================
   TESTES
   ======================================================= */

void test_criarDadosArq_Valido() {
    criarArquivoTeste();

    DadosArquivo d = criarDadosArq("arquivo.txt");

    TEST_ASSERT_NOT_NULL(d);

    destruirDadosArq(d);
    remove("arquivo.txt");
}

void test_criarDadosArq_inexistente() {
    DadosArquivo d = criarDadosArq("nao_existe.txt");

    TEST_ASSERT_NULL(d);
}

void test_getPathNome() {
    criarArquivoTeste();

    DadosArquivo d = criarDadosArq("arquivo.txt");

    TEST_ASSERT_NOT_NULL(getPathArq(d));
    TEST_ASSERT_NOT_NULL(getNomeArq(d));

    destruirDadosArq(d);
    remove("arquivo.txt");
}

void test_getFilaLinhas() {
    criarArquivoTeste();

    DadosArquivo d = criarDadosArq("arquivo.txt");

    FILA f = getFilaLinhasArq(d);

    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_TRUE(tamanhoFila(f) > 0);

    destruirDadosArq(d);
    remove("arquivo.txt");
}

void test_getFilaLinhas_Invalido() {
    TEST_ASSERT_NULL(getFilaLinhasArq(NULL));
}

void test_destruirDadosArq() {
    criarArquivoTeste();

    DadosArquivo d = criarDadosArq("arquivo.txt");

    destruirDadosArq(d);

    remove("arquivo.txt");
}

/* =======================================================
   MAIN
   ======================================================= */

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criarDadosArq_Valido);
    RUN_TEST(test_criarDadosArq_inexistente);

    RUN_TEST(test_getPathNome);

    RUN_TEST(test_getFilaLinhas);
    RUN_TEST(test_getFilaLinhas_Invalido);

    RUN_TEST(test_destruirDadosArq);

    return UNITY_END();
}