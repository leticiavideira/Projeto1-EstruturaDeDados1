#include <stdio.h>
#include "unity.h"

#include "../formas/forma.h"
#include "../formas/circulo.h"
#include "../formas/retangulo.h"
#include "../formas/linha.h"
#include "../formas/texto.h"
#include "../formas/estiloTexto.h"

void setUp(void) {}
void tearDown(void) {}

/* =======================================================
   CRIAÇÃO
   ======================================================= */

void test_criarForma_Valido() {
    CIRCULO c = criaCirculo(1, 0, 0, 5, "b", "p");

    FORMA f = criarForma(FORMA_CIRCULO, c);

    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_INT(FORMA_CIRCULO, getTipoForma(f));

    killForma(f);
}

void test_criarForma_dataNULL() {
    FORMA f = criarForma(FORMA_CIRCULO, NULL);
    TEST_ASSERT_NULL(f);
}

/* =======================================================
   GETTERS
   ======================================================= */

void test_getNomeForma_Valido() {
    CIRCULO c = criaCirculo(1,0,0,1,"b","p");
    FORMA f = criarForma(FORMA_CIRCULO, c);

    TEST_ASSERT_EQUAL_STRING("circulo", getNomeForma(f));

    killForma(f);
}

void test_getNomeForma_Invalido() {
    TEST_ASSERT_NULL(getNomeForma(NULL));
}

void test_getIdForma_Valido() {
    RETANGULO r = criaRetangulo(99,0,0,1,1,"b","p");
    FORMA f = criarForma(FORMA_RETANGULO, r);

    TEST_ASSERT_EQUAL_INT(99, getIdForma(f));

    killForma(f);
}

void test_getIdForma_Invalido() {
    TEST_ASSERT_EQUAL_INT(-1, getIdForma(NULL));
}

void test_getDataForma_Valido() {
    CIRCULO c = criaCirculo(1,0,0,1,"b","p");
    FORMA f = criarForma(FORMA_CIRCULO, c);

    TEST_ASSERT_EQUAL_PTR(c, getDataForma(f));

    killForma(f);
}

/* =======================================================
   ÂNCORA
   ======================================================= */

void test_getAncoraForma_Circulo() {
    CIRCULO c = criaCirculo(1, 10, 20, 5, "b", "p");
    FORMA f = criarForma(FORMA_CIRCULO, c);

    double x, y;
    getAncoraForma(f, &x, &y);

    TEST_ASSERT_FLOAT_WITHIN(0.001, 10, x);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 20, y);

    killForma(f);
}

void test_getAncoraForma_Invalido() {
    double x, y;
    getAncoraForma(NULL, &x, &y); // não pode crashar
}

/* =======================================================
   MODIFICAÇÕES
   ======================================================= */

void test_setCorForma_Valido() {
    CIRCULO c = criaCirculo(1,0,0,1,"b","p");
    FORMA f = criarForma(FORMA_CIRCULO, c);

    setCorBordaForma(f, "red");
    setCorPreenchimentoForma(f, "blue");

    TEST_ASSERT_EQUAL_STRING("red", getCorB_C(c));
    TEST_ASSERT_EQUAL_STRING("blue", getCorP_C(c));

    killForma(f);
}

void test_setCorForma_Invalido() {
    setCorBordaForma(NULL, "x");
    setCorPreenchimentoForma(NULL, "x");
}

/* =======================================================
   MOVIMENTO (TESTE IMPORTANTE)
   ======================================================= */

void test_moverForma_Circulo() {
    CIRCULO c = criaCirculo(1, 0, 0, 1, "b", "p");
    FORMA f = criarForma(FORMA_CIRCULO, c);

    moverForma(f, 5, 10);

    TEST_ASSERT_FLOAT_WITHIN(0.001, 5, getX_C(c));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 10, getY_C(c));

    killForma(f);
}

void test_moverForma_Retangulo() {
    RETANGULO r = criaRetangulo(1, 1, 2, 3, 4, "b", "p");
    FORMA f = criarForma(FORMA_RETANGULO, r);

    moverForma(f, 2, 3);

    TEST_ASSERT_FLOAT_WITHIN(0.001, 3, getX_R(r));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 5, getY_R(r));

    killForma(f);
}

void test_moverForma_Invalido() {
    moverForma(NULL, 1, 1);
}

/* =======================================================
   PRINT (não quebra)
   ======================================================= */

void test_printFormaTXT() {
    CIRCULO c = criaCirculo(1,0,0,1,"b","p");
    FORMA f = criarForma(FORMA_CIRCULO, c);

    FILE *fp = fopen("teste.txt", "w");

    printFormaTXT(fp, f);

    fclose(fp);
    remove("teste.txt");

    killForma(f);
}

/* =======================================================
   KILL
   ======================================================= */

void test_killForma() {
    CIRCULO c = criaCirculo(1,0,0,1,"b","p");
    FORMA f = criarForma(FORMA_CIRCULO, c);

    killForma(f);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criarForma_Valido);
    RUN_TEST(test_criarForma_dataNULL);

    RUN_TEST(test_getNomeForma_Valido);
    RUN_TEST(test_getNomeForma_Invalido);

    RUN_TEST(test_getIdForma_Valido);
    RUN_TEST(test_getIdForma_Invalido);

    RUN_TEST(test_getDataForma_Valido);

    RUN_TEST(test_getAncoraForma_Circulo);
    RUN_TEST(test_getAncoraForma_Invalido);

    RUN_TEST(test_setCorForma_Valido);
    RUN_TEST(test_setCorForma_Invalido);

    RUN_TEST(test_moverForma_Circulo);
    RUN_TEST(test_moverForma_Retangulo);
    RUN_TEST(test_moverForma_Invalido);

    RUN_TEST(test_printFormaTXT);

    RUN_TEST(test_killForma);

    return UNITY_END();
}