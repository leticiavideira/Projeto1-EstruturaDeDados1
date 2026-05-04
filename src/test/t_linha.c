#include <stdio.h>
#include "unity.h"
#include "../formas/linha.h"

void setUp(void) {}
void tearDown(void) {}

/* =======================================================
   CRIAÇÃO
   ======================================================= */

void test_criaLinha_Valido() {
    LINHA l = criaLinha(1, 0, 0, 3, 4, "black");
    TEST_ASSERT_NOT_NULL(l);
    kill_L(l);
}

void test_criaLinha_parametrosNegativos() {
    LINHA l = criaLinha(1, -1, -2, -3, -4, "red");
    TEST_ASSERT_NOT_NULL(l);
    kill_L(l);
}

/* =======================================================
   GETTERS
   ======================================================= */

void test_gettersLinha_Valido() {
    LINHA l = criaLinha(1, 1, 2, 3, 4, "blue");

    TEST_ASSERT_EQUAL_INT(1, getId_L(l));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 1, getX1_L(l));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 2, getY1_L(l));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 3, getX2_L(l));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 4, getY2_L(l));
    TEST_ASSERT_EQUAL_STRING("blue", getCor_L(l));

    kill_L(l);
}

void test_gettersLinha_Invalido() {
    TEST_ASSERT_EQUAL_INT(0, getId_L(NULL));
}

/* =======================================================
   ÁREA (CONSISTÊNCIA)
   ======================================================= */

void test_calcularAreaLinha_Valido() {
    LINHA l = criaLinha(1, 0, 0, 3, 4, "x");

    double area = calcularArea_L(l);

    // distancia = 5 → área = 10
    TEST_ASSERT_FLOAT_WITHIN(0.001, 10, area);

    kill_L(l);
}

void test_calcularAreaLinha_Invalido() {
    TEST_ASSERT_EQUAL_FLOAT(0, calcularArea_L(NULL));
}

/* =======================================================
   SETTERS
   ======================================================= */

void test_settersLinha_Valido() {
    LINHA l = criaLinha(1, 0, 0, 1, 1, "a");

    setX1_L(l, 5);
    setY1_L(l, 6);
    setX2_L(l, 7);
    setY2_L(l, 8);
    setCor_L(l, "green");

    TEST_ASSERT_FLOAT_WITHIN(0.001, 5, getX1_L(l));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 6, getY1_L(l));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 7, getX2_L(l));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 8, getY2_L(l));
    TEST_ASSERT_EQUAL_STRING("green", getCor_L(l));

    kill_L(l);
}

void test_settersLinha_Invalido() {
    setX1_L(NULL, 1);
    setY1_L(NULL, 1);
    setX2_L(NULL, 1);
    setY2_L(NULL, 1);
    setCor_L(NULL, "x");
}

/* =======================================================
   KILL
   ======================================================= */

void test_killLinha() {
    LINHA l = criaLinha(1,0,0,1,1,"a");
    kill_L(l);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criaLinha_Valido);
    RUN_TEST(test_criaLinha_parametrosNegativos);

    RUN_TEST(test_gettersLinha_Valido);
    RUN_TEST(test_gettersLinha_Invalido);

    RUN_TEST(test_calcularAreaLinha_Valido);
    RUN_TEST(test_calcularAreaLinha_Invalido);

    RUN_TEST(test_settersLinha_Valido);
    RUN_TEST(test_settersLinha_Invalido);

    RUN_TEST(test_killLinha);

    return UNITY_END();
}