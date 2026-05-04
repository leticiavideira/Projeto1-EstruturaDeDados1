#include <stdio.h>
#include "unity.h"
#include "../formas/estiloTexto.h"

void setUp(void) {}
void tearDown(void) {}

void test_criaEstiloTexto_Valido() {
    ESTILO_TEXTO e = criaEstiloTexto("Arial", "bold", 12);
    TEST_ASSERT_NOT_NULL(e);
    killEstiloTexto(e);
}

void test_criaEstiloTexto_familyNULL() {
    ESTILO_TEXTO e = criaEstiloTexto(NULL, "bold", 12);
    TEST_ASSERT_NULL(e);
}

void test_gettersEstilo_Valido() {
    ESTILO_TEXTO e = criaEstiloTexto("Arial", "bold", 12);

    TEST_ASSERT_EQUAL_STRING("Arial", getfFamily_T(e));
    TEST_ASSERT_EQUAL_STRING("bold", getfWeight_T(e));
    TEST_ASSERT_EQUAL_INT(12, getfSize_T(e));

    killEstiloTexto(e);
}

void test_gettersEstilo_Invalido() {
    TEST_ASSERT_NULL(getfFamily_T(NULL));
    TEST_ASSERT_EQUAL_INT(-1, getfSize_T(NULL));
}

void test_killEstiloTexto() {
    ESTILO_TEXTO e = criaEstiloTexto("Arial", "bold", 12);
    killEstiloTexto(e);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criaEstiloTexto_Valido);
    RUN_TEST(test_criaEstiloTexto_familyNULL);

    RUN_TEST(test_gettersEstilo_Valido);
    RUN_TEST(test_gettersEstilo_Invalido);

    RUN_TEST(test_killEstiloTexto);

    return UNITY_END();
}