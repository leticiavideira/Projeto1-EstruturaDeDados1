#include <stdio.h>
#include <string.h>
#include <direct.h> // mkdir
#include "unity.h"

#include "../gerais/svg.h"
#include "../formas/forma.h"
#include "../formas/circulo.h"
#include "../estruturas/lista.h"
#include "../gerais/leitorDeArquivos.h"

void setUp(void) {}
void tearDown(void) {}

/* =========================
   AUXILIAR
   ========================= */

void criarArquivoDummy(const char *nome) {
    FILE *f = fopen(nome, "w");
    fprintf(f, "dummy\n");
    fclose(f);
}

void criarDiretorioSaida() {
    _mkdir("saida");
}

int arquivoExisteENaoVazio(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return 0;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fclose(f);

    return size > 0;
}

int arquivoContem(const char *path, const char *str) {
    FILE *f = fopen(path, "r");
    if (!f) return 0;

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), f)) {
        if (strstr(buffer, str)) {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

/* =========================
   TESTES SVG
   ========================= */

void test_gerarSVG_Valido() {
    criarDiretorioSaida();
    criarArquivoDummy("teste.txt");

    LISTA lista = criarLista();

    CIRCULO c = criaCirculo(1, 10, 10, 5, "black", "red");
    FORMA f = criarForma(FORMA_CIRCULO, c);

    pushFimLista(lista, f);

    DadosArquivo d = criarDadosArq("teste.txt");
    TEST_ASSERT_NOT_NULL(d);

    gerarSVG(lista, "saida", d, "teste");

    TEST_ASSERT_TRUE(arquivoExisteENaoVazio("saida/teste-teste.svg"));
    TEST_ASSERT_TRUE(arquivoContem("saida/teste-teste.svg", "circle"));

    remove("saida/teste-teste.svg");
    remove("teste.txt");

    destruirDadosArq(d);
    killLista(lista);
}

void test_gerarSVG_listaVazia() {
    criarDiretorioSaida();
    criarArquivoDummy("teste.txt");

    LISTA lista = criarLista();

    DadosArquivo d = criarDadosArq("teste.txt");
    TEST_ASSERT_NOT_NULL(d);

    gerarSVG(lista, "saida", d, "vazio");

    TEST_ASSERT_TRUE(arquivoExisteENaoVazio("saida/teste-vazio.svg"));

    remove("saida/teste-vazio.svg");
    remove("teste.txt");

    destruirDadosArq(d);
    killLista(lista);
}

void test_gerarSVG_parametrosInvalidos() {
    gerarSVG(NULL, "x", NULL, "x");
}

/* =========================
   SVG QRY
   ========================= */

void test_gerarSVG_QRY_Valido() {
    criarDiretorioSaida();
    criarArquivoDummy("teste.txt");

    LISTA banco = criarLista();
    LISTA sel = criarLista();
    LISTA rem = criarLista();

    CIRCULO c = criaCirculo(1, 5, 5, 2, "b", "p");
    FORMA f = criarForma(FORMA_CIRCULO, c);

    pushFimLista(banco, f);
    pushFimLista(sel, f);

    DadosArquivo geo = criarDadosArq("teste.txt");
    DadosArquivo qry = criarDadosArq("teste.txt");

    TEST_ASSERT_NOT_NULL(geo);
    TEST_ASSERT_NOT_NULL(qry);

    gerarSVG_QRY(banco, sel, rem, 0,0,10,10, "saida", geo, qry);

    TEST_ASSERT_TRUE(arquivoExisteENaoVazio("saida/teste-teste.svg"));

    remove("saida/teste-teste.svg");
    remove("teste.txt");

    destruirDadosArq(geo);
    destruirDadosArq(qry);

    killLista(banco);
    killLista(sel);
    killLista(rem);
}

void test_gerarSVG_QRY_parametrosInvalidos() {
    gerarSVG_QRY(NULL, NULL, NULL, 0,0,0,0, "x", NULL, NULL);
}

/* =========================
   MAIN
   ========================= */

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_gerarSVG_Valido);
    RUN_TEST(test_gerarSVG_listaVazia);
    RUN_TEST(test_gerarSVG_parametrosInvalidos);

    RUN_TEST(test_gerarSVG_QRY_Valido);
    RUN_TEST(test_gerarSVG_QRY_parametrosInvalidos);

    return UNITY_END();
}