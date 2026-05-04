#include <stdio.h>
#include "unity.h"
#include "../estruturas/fila.h"

void setUp(void) {}
void tearDown(void) {}

/* =======================================================
   CRIAÇÃO
   ======================================================= */

void test_criarFila_Valido() {
    FILA f = criarFila();
    TEST_ASSERT_NOT_NULL(f);
    killFila(f);
}

void test_criarFila_comecarVazia() {
    FILA f = criarFila();
    TEST_ASSERT_EQUAL_INT(1, filaVazia(f));
    killFila(f);
}

/* =======================================================
   PUSH
   ======================================================= */

void test_pushFila_Valido() {
    FILA f = criarFila();
    int x = 10;

    int r = pushFila(f, &x);

    TEST_ASSERT_EQUAL_INT(1, r);
    TEST_ASSERT_EQUAL_INT(1, tamanhoFila(f));

    killFila(f);
}

void test_pushFila_Invalido() {
    int x = 10;
    int r = pushFila(NULL, &x);

    TEST_ASSERT_EQUAL_INT(0, r);
}

/* =======================================================
   POP
   ======================================================= */

void test_popFila_Valido_FIFO() {
    FILA f = criarFila();

    int a = 1, b = 2;
    pushFila(f, &a);
    pushFila(f, &b);

    int *r = (int*) popFila(f);

    TEST_ASSERT_EQUAL_INT(1, *r);
    TEST_ASSERT_EQUAL_INT(1, tamanhoFila(f));

    killFila(f);
}

void test_popFila_Vazia() {
    FILA f = criarFila();

    TEST_ASSERT_NULL(popFila(f));

    killFila(f);
}

void test_popFila_Invalido() {
    TEST_ASSERT_NULL(popFila(NULL));
}

/* =======================================================
   PRIMEIRO ELEMENTO
   ======================================================= */

void test_primeiroElementoFila_Valido() {
    FILA f = criarFila();
    int x = 5;

    pushFila(f, &x);

    int *r = (int*) primeiroElementoFila(f);

    TEST_ASSERT_EQUAL_INT(5, *r);

    killFila(f);
}

void test_primeiroElementoFila_Vazia() {
    FILA f = criarFila();

    TEST_ASSERT_NULL(primeiroElementoFila(f));

    killFila(f);
}

/* =======================================================
   TAMANHO / VAZIA
   ======================================================= */

void test_tamanhoFila_Valido() {
    FILA f = criarFila();
    int x = 1;

    pushFila(f, &x);

    TEST_ASSERT_EQUAL_INT(1, tamanhoFila(f));

    killFila(f);
}

void test_tamanhoFila_Invalido() {
    TEST_ASSERT_EQUAL_INT(0, tamanhoFila(NULL));
}

void test_filaVazia_Valido() {
    FILA f = criarFila();
    TEST_ASSERT_EQUAL_INT(1, filaVazia(f));

    int x = 1;
    pushFila(f, &x);

    TEST_ASSERT_EQUAL_INT(0, filaVazia(f));

    killFila(f);
}

void test_filaVazia_Invalido() {
    TEST_ASSERT_EQUAL_INT(-1, filaVazia(NULL));
}

/* =======================================================
   LIMPAR / KILL
   ======================================================= */

void test_limparFila_Valido() {
    FILA f = criarFila();
    int x = 1;

    pushFila(f, &x);
    limparFila(f);

    TEST_ASSERT_EQUAL_INT(1, filaVazia(f));

    killFila(f);
}

void test_killFila_Valido() {
    FILA f = criarFila();
    killFila(f);
}

/* =======================================================
   MAIN
   ======================================================= */

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criarFila_Valido);
    RUN_TEST(test_criarFila_comecarVazia);

    RUN_TEST(test_pushFila_Valido);
    RUN_TEST(test_pushFila_Invalido);

    RUN_TEST(test_popFila_Valido_FIFO);
    RUN_TEST(test_popFila_Vazia);
    RUN_TEST(test_popFila_Invalido);

    RUN_TEST(test_primeiroElementoFila_Valido);
    RUN_TEST(test_primeiroElementoFila_Vazia);

    RUN_TEST(test_tamanhoFila_Valido);
    RUN_TEST(test_tamanhoFila_Invalido);

    RUN_TEST(test_filaVazia_Valido);
    RUN_TEST(test_filaVazia_Invalido);

    RUN_TEST(test_limparFila_Valido);
    RUN_TEST(test_killFila_Valido);

    return UNITY_END();
}