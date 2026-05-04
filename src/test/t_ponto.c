#include <stdio.h>
#include "unity.h"
#include "../formas/ponto.h"

void setUp(void) {}
void tearDown(void) {}

void test_criarPonto_Valido() {
    PONTO p = criarPonto(1, 2);
    TEST_ASSERT_NOT_NULL(p);
    killPonto(p);
}

void test_criarPonto_negativo() {
    PONTO p = criarPonto(-1, -2);
    TEST_ASSERT_NOT_NULL(p);
    killPonto(p);
}

void test_getPonto_Valido() {
    PONTO p = criarPonto(3, 4);

    double x, y;
    getPonto(p, &x, &y);

    TEST_ASSERT_FLOAT_WITHIN(0.001, 3, x);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 4, y);

    killPonto(p);
}

void test_getPonto_parametrosInvalidos() {
    double x, y;

    getPonto(NULL, &x, &y);      // não deve crashar
    getPonto(NULL, NULL, NULL);  // pior caso
}

void test_killPonto() {
    PONTO p = criarPonto(1,1);
    killPonto(p);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criarPonto_Valido);
    RUN_TEST(test_criarPonto_negativo);

    RUN_TEST(test_getPonto_Valido);
    RUN_TEST(test_getPonto_parametrosInvalidos);

    RUN_TEST(test_killPonto);

    return UNITY_END();
}