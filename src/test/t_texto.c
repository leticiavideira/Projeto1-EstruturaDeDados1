#include <stdio.h>
#include <string.h>
#include "unity.h"
#include "../formas/texto.h"

void setUp(void) {}
void tearDown(void) {}

/* =======================================================
   CRIAÇÃO
   ======================================================= */

void test_criaTexto_Valido() {
    TEXTO t = criaTexto(1, 10, 20, "black", "red", 'm', "abc");
    TEST_ASSERT_NOT_NULL(t);
    kill_T(t);
}

void test_criaTexto_stringVazia() {
    TEXTO t = criaTexto(1, 0, 0, "b", "p", 'i', "");
    TEST_ASSERT_NOT_NULL(t);
    kill_T(t);
}

/* =======================================================
   GETTERS
   ======================================================= */

void test_gettersTexto_Valido() {
    TEXTO t = criaTexto(1, 1, 2, "b", "p", 'f', "abc");

    TEST_ASSERT_EQUAL_INT(1, getId_T(t));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 1, getX_T(t));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 2, getY_T(t));
    TEST_ASSERT_EQUAL_STRING("b", getCorb_T(t));
    TEST_ASSERT_EQUAL_STRING("p", getCorp_T(t));
    TEST_ASSERT_EQUAL_CHAR('f', getA_T(t));
    TEST_ASSERT_EQUAL_STRING("abc", getTxto_T(t));

    kill_T(t);
}

void test_gettersTexto_Invalido() {
    TEST_ASSERT_EQUAL_INT(0, getId_T(NULL));
    TEST_ASSERT_NULL(getTxto_T(NULL));
}

/* =======================================================
   CONSISTÊNCIA: comprimento vs área
   ======================================================= */

void test_comprimentoTexto_Valido() {
    TEXTO t = criaTexto(1,0,0,"b","p",'m',"abcd");

    double comp = comprimento_T(t);

    TEST_ASSERT_FLOAT_WITHIN(0.001, 40, comp); // 10 * 4

    kill_T(t);
}

void test_areaTexto_consistencia() {
    TEXTO t = criaTexto(1,0,0,"b","p",'m',"abcd");

    double area = calcularArea_T(t);

    TEST_ASSERT_FLOAT_WITHIN(0.001, 80, area); // 20 * 4

    kill_T(t);
}

void test_comprimentoTexto_Invalido() {
    TEST_ASSERT_EQUAL_FLOAT(0, comprimento_T(NULL));
}

/* =======================================================
   SETTERS
   ======================================================= */

void test_settersTexto_Valido() {
    TEXTO t = criaTexto(1,1,1,"a","b",'i',"x");

    setX_T(t, 9);
    setY_T(t, 8);
    setCorb_T(t, "blue");
    setCorp_T(t, "green");
    setA_T(t, 'm');
    setTxto_T(t, "novo");

    TEST_ASSERT_FLOAT_WITHIN(0.001, 9, getX_T(t));
    TEST_ASSERT_FLOAT_WITHIN(0.001, 8, getY_T(t));
    TEST_ASSERT_EQUAL_STRING("blue", getCorb_T(t));
    TEST_ASSERT_EQUAL_STRING("green", getCorp_T(t));
    TEST_ASSERT_EQUAL_CHAR('m', getA_T(t));
    TEST_ASSERT_EQUAL_STRING("novo", getTxto_T(t));

    kill_T(t);
}

void test_settersTexto_Invalido() {
    setX_T(NULL, 1);
    setY_T(NULL, 1);
    setCorb_T(NULL, "x");
    setCorp_T(NULL, "x");
    setA_T(NULL, 'i');
    setTxto_T(NULL, "x");
}

/* =======================================================
   KILL
   ======================================================= */

void test_killTexto() {
    TEXTO t = criaTexto(1,0,0,"a","b",'i',"x");
    kill_T(t);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criaTexto_Valido);
    RUN_TEST(test_criaTexto_stringVazia);

    RUN_TEST(test_gettersTexto_Valido);
    RUN_TEST(test_gettersTexto_Invalido);

    RUN_TEST(test_comprimentoTexto_Valido);
    RUN_TEST(test_areaTexto_consistencia);
    RUN_TEST(test_comprimentoTexto_Invalido);

    RUN_TEST(test_settersTexto_Valido);
    RUN_TEST(test_settersTexto_Invalido);

    RUN_TEST(test_killTexto);

    return UNITY_END();
}