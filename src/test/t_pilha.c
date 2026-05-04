#include <stdio.h>
#include "unity.h"
#include "../estruturas/pilha.h"

void setUp(void) {}
void tearDown(void) {}

/* =======================================================
   CRIAÇÃO
   ======================================================= */

void test_criarPilha_Valido() {
    PILHA p = criarPilha();
    TEST_ASSERT_NOT_NULL(p);
    killPilha(p);
}

/* =======================================================
   PUSH
   ======================================================= */

void test_pushPilha_Valido() {
    PILHA p = criarPilha();
    int x = 10;

    TEST_ASSERT_EQUAL_INT(1, pushPilha(p, &x));
    TEST_ASSERT_EQUAL_INT(1, tamanhoPilha(p));

    killPilha(p);
}

void test_pushPilha_Invalido() {
    int x = 10;
    TEST_ASSERT_EQUAL_INT(0, pushPilha(NULL, &x));
}

/* =======================================================
   POP
   ======================================================= */

void test_popPilha_LIFO() {
    PILHA p = criarPilha();

    int a = 1, b = 2;
    pushPilha(p, &a);
    pushPilha(p, &b);

    int *r = (int*) popPilha(p);

    TEST_ASSERT_EQUAL_INT(2, *r);

    killPilha(p);
}

void test_popPilha_Vazia() {
    PILHA p = criarPilha();
    TEST_ASSERT_NULL(popPilha(p));
    killPilha(p);
}

/* =======================================================
   TOPO
   ======================================================= */

void test_topoPilha_Valido() {
    PILHA p = criarPilha();
    int x = 5;

    pushPilha(p, &x);

    int *r = (int*) topoPilha(p);

    TEST_ASSERT_EQUAL_INT(5, *r);

    killPilha(p);
}

void test_topoPilha_Vazia() {
    PILHA p = criarPilha();
    TEST_ASSERT_NULL(topoPilha(p));
    killPilha(p);
}

/* =======================================================
   TAMANHO / VAZIA
   ======================================================= */

void test_tamanhoPilha_Valido() {
    PILHA p = criarPilha();
    int x = 1;

    pushPilha(p, &x);

    TEST_ASSERT_EQUAL_INT(1, tamanhoPilha(p));

    killPilha(p);
}

void test_tamanhoPilha_Invalido() {
    TEST_ASSERT_EQUAL_INT(-1, tamanhoPilha(NULL));
}

void test_pilhaVazia_Valido() {
    PILHA p = criarPilha();
    TEST_ASSERT_EQUAL_INT(1, pilhaVazia(p));

    int x = 1;
    pushPilha(p, &x);

    TEST_ASSERT_EQUAL_INT(0, pilhaVazia(p));

    killPilha(p);
}

void test_pilhaVazia_Invalido() {
    TEST_ASSERT_EQUAL_INT(-1, pilhaVazia(NULL));
}

/* =======================================================
   LIMPAR / KILL
   ======================================================= */

void test_limparPilha_Valido() {
    PILHA p = criarPilha();
    int x = 1;

    pushPilha(p, &x);
    limparPilha(p);

    TEST_ASSERT_EQUAL_INT(1, pilhaVazia(p));

    killPilha(p);
}

/* =======================================================
   MAIN
   ======================================================= */

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criarPilha_Valido);

    RUN_TEST(test_pushPilha_Valido);
    RUN_TEST(test_pushPilha_Invalido);

    RUN_TEST(test_popPilha_LIFO);
    RUN_TEST(test_popPilha_Vazia);

    RUN_TEST(test_topoPilha_Valido);
    RUN_TEST(test_topoPilha_Vazia);

    RUN_TEST(test_tamanhoPilha_Valido);
    RUN_TEST(test_tamanhoPilha_Invalido);

    RUN_TEST(test_pilhaVazia_Valido);
    RUN_TEST(test_pilhaVazia_Invalido);

    RUN_TEST(test_limparPilha_Valido);

    return UNITY_END();
}