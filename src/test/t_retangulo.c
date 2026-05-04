#include <stdio.h>
#include "unity.h"
#include "../formas/retangulo.h"

void setUp(void) {}
void tearDown(void) {}

void test_criaRetangulo_Valido() {
    RETANGULO r = criaRetangulo(1, 0, 0, 10, 5, "b", "p");
    TEST_ASSERT_NOT_NULL(r);
    kill_R(r);
}

void test_gettersRetangulo_Valido() {
    RETANGULO r = criaRetangulo(1, 1, 2, 3, 4, "b", "p");

    TEST_ASSERT_EQUAL_INT(1, getId_R(r));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 1, getX_R(r));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 2, getY_R(r));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 3, getW_R(r));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 4, getH_R(r));

    kill_R(r);
}

void test_calcularAreaRetangulo_Valido() {
    RETANGULO r = criaRetangulo(1,0,0,5,2,"b","p");

    TEST_ASSERT_FLOAT_WITHIN(0.001, 10, calcularArea_R(r));

    kill_R(r);
}

void test_calcularAreaRetangulo_Invalido() {
    TEST_ASSERT_EQUAL_FLOAT(0, calcularArea_R(NULL));
}

void test_settersRetangulo_Valido() {
    RETANGULO r = criaRetangulo(1,1,1,1,1,"a","b");

    setW_R(r, 10);
    setH_R(r, 5);

    TEST_ASSERT_FLOAT_WITHIN(0.001, 10, getW_R(r));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 5, getH_R(r));

    kill_R(r);
}

void test_settersRetangulo_Invalido() {
    setW_R(NULL, 1);
    setH_R(NULL, 1);
}

void test_killRetangulo() {
    RETANGULO r = criaRetangulo(1,0,0,1,1,"a","b");
    kill_R(r);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criaRetangulo_Valido);
    RUN_TEST(test_gettersRetangulo_Valido);

    RUN_TEST(test_calcularAreaRetangulo_Valido);
    RUN_TEST(test_calcularAreaRetangulo_Invalido);

    RUN_TEST(test_settersRetangulo_Valido);
    RUN_TEST(test_settersRetangulo_Invalido);

    RUN_TEST(test_killRetangulo);

    return UNITY_END();
}