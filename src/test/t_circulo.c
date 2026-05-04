#include <stdio.h>
#include "unity.h"
#include "../formas/circulo.h"

void setUp(void) {}
void tearDown(void) {}

/* =======================================================
   CRIAÇÃO
   ======================================================= */

void test_criaCirculo_Valido() {
    CIRCULO c = criaCirculo(1, 10, 20, 5, "black", "red");
    TEST_ASSERT_NOT_NULL(c);
    kill_C(c);
}

void test_criaCirculo_parametrosNegativos() {
    CIRCULO c = criaCirculo(1, -10, -20, -5, "black", "red");
    TEST_ASSERT_NOT_NULL(c); // depende do contrato: não proibido
    kill_C(c);
}

/* =======================================================
   GETTERS
   ======================================================= */

void test_gettersCirculo_Valido() {
    CIRCULO c = criaCirculo(1, 10, 20, 5, "black", "red");

    TEST_ASSERT_EQUAL_INT(1, getId_C(c));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 10, getX_C(c));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 20, getY_C(c));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 5, getR_C(c));
    TEST_ASSERT_EQUAL_STRING("black", getCorB_C(c));
    TEST_ASSERT_EQUAL_STRING("red", getCorP_C(c));

    kill_C(c);
}

void test_gettersCirculo_Invalido() {
    TEST_ASSERT_EQUAL_INT(0, getId_C(NULL));
}

/* =======================================================
   ÁREA
   ======================================================= */

void test_calcularAreaCirculo_Valido() {
    CIRCULO c = criaCirculo(1, 0, 0, 2, "b", "p");

    double area = calcularArea_C(c);

    TEST_ASSERT_FLOAT_WITHIN(0.01, 12.566, area);

    kill_C(c);
}

void test_calcularAreaCirculo_Invalido() {
    TEST_ASSERT_EQUAL_FLOAT(0, calcularArea_C(NULL));
}

/* =======================================================
   SETTERS
   ======================================================= */

void test_settersCirculo_Valido() {
    CIRCULO c = criaCirculo(1, 1, 1, 1, "a", "b");

    setId_C(c, 5);
    setX_C(c, 9);
    setY_C(c, 8);
    setR_C(c, 3);
    setCorB_C(c, "blue");
    setCorP_C(c, "green");

    TEST_ASSERT_EQUAL_INT(5, getId_C(c));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 9, getX_C(c));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 8, getY_C(c));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 3, getR_C(c));
    TEST_ASSERT_EQUAL_STRING("blue", getCorB_C(c));
    TEST_ASSERT_EQUAL_STRING("green", getCorP_C(c));

    kill_C(c);
}

void test_settersCirculo_Invalido() {
    setId_C(NULL, 1);
    setX_C(NULL, 1);
    setY_C(NULL, 1);
    setR_C(NULL, 1);
    setCorB_C(NULL, "x");
    setCorP_C(NULL, "x");
}

/* =======================================================
   KILL
   ======================================================= */

void test_killCirculo_Valido() {
    CIRCULO c = criaCirculo(1,1,1,1,"a","b");
    kill_C(c);
}

void test_killCirculo_Invalido() {
    kill_C(NULL);
}

/* =======================================================
   MAIN
   ======================================================= */

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criaCirculo_Valido);
    RUN_TEST(test_criaCirculo_parametrosNegativos);

    RUN_TEST(test_gettersCirculo_Valido);
    RUN_TEST(test_gettersCirculo_Invalido);

    RUN_TEST(test_calcularAreaCirculo_Valido);
    RUN_TEST(test_calcularAreaCirculo_Invalido);

    RUN_TEST(test_settersCirculo_Valido);
    RUN_TEST(test_settersCirculo_Invalido);

    RUN_TEST(test_killCirculo_Valido);
    RUN_TEST(test_killCirculo_Invalido);

    return UNITY_END();
}