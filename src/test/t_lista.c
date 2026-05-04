#include <stdio.h>
#include "unity.h"
#include "../estruturas/lista.h"

void setUp(void) {}
void tearDown(void) {}

/* =======================================================
   CRIAÇÃO
   ======================================================= */

void test_criarLista_Valido() {
    LISTA l = criarLista();
    TEST_ASSERT_NOT_NULL(l);
    killLista(l);
}

/* =======================================================
   PUSH
   ======================================================= */

void test_pushInicioLista_Valido() {
    LISTA l = criarLista();
    int x = 1;

    TEST_ASSERT_EQUAL_INT(1, pushInicioLista(l, &x));
    TEST_ASSERT_EQUAL_INT(1, tamanhoLista(l));

    killLista(l);
}

void test_pushFimLista_Valido() {
    LISTA l = criarLista();
    int x = 2;

    TEST_ASSERT_EQUAL_INT(1, pushFimLista(l, &x));
    TEST_ASSERT_EQUAL_INT(1, tamanhoLista(l));

    killLista(l);
}

/* =======================================================
   POP
   ======================================================= */

void test_popInicioLista_Valido() {
    LISTA l = criarLista();
    int x = 1;

    pushInicioLista(l, &x);

    int *r = (int*) popInicioLista(l);

    TEST_ASSERT_EQUAL_INT(1, *r);

    killLista(l);
}

void test_popFimLista_Valido() {
    LISTA l = criarLista();
    int x = 1;

    pushFimLista(l, &x);

    int *r = (int*) popFimLista(l);

    TEST_ASSERT_EQUAL_INT(1, *r);

    killLista(l);
}

/* =======================================================
   BUSCA / REMOÇÃO POR ID
   ======================================================= */

void test_buscaIdLista_Valido() {
    LISTA l = criarLista();
    int x = 10;

    pushFimLista(l, &x);

    void *elem = buscaIdLista(l, &x);
    TEST_ASSERT_NOT_NULL(elem);

    int *r = (int*) getConteudoElemLista(elem);

    TEST_ASSERT_EQUAL_INT(10, *r);

    killLista(l);
}

void test_buscaIdLista_Invalido() {
    LISTA l = criarLista();
    int x = 10;

    TEST_ASSERT_NULL(buscaIdLista(l, &x));

    killLista(l);
}

void test_popIdLista_Valido() {
    LISTA l = criarLista();
    int x = 10;

    pushFimLista(l, &x);

    int *r = (int*) popIdLista(l, &x);

    TEST_ASSERT_EQUAL_INT(10, *r);

    killLista(l);
}

/* =======================================================
   ITERAÇÃO
   ======================================================= */

void test_getInicioEProximoLista_Valido() {
    LISTA l = criarLista();
    int a = 1, b = 2;

    pushFimLista(l, &a);
    pushFimLista(l, &b);

    void *e = getInicioLista(l);
    int *v1 = (int*) getConteudoElemLista(e);

    void *e2 = getProximoLista(l, e);
    int *v2 = (int*) getConteudoElemLista(e2);

    TEST_ASSERT_EQUAL_INT(1, *v1);
    TEST_ASSERT_EQUAL_INT(2, *v2);

    killLista(l);
}

/* =======================================================
   TAMANHO / VAZIA
   ======================================================= */

void test_tamanhoLista_Valido() {
    LISTA l = criarLista();
    int x = 1;

    pushFimLista(l, &x);

    TEST_ASSERT_EQUAL_INT(1, tamanhoLista(l));

    killLista(l);
}

void test_tamanhoLista_Invalido() {
    TEST_ASSERT_EQUAL_INT(-1, tamanhoLista(NULL));
}

void test_listaVazia_Valido() {
    LISTA l = criarLista();

    TEST_ASSERT_EQUAL_INT(1, listaVazia(l));

    int x = 1;
    pushFimLista(l, &x);

    TEST_ASSERT_EQUAL_INT(0, listaVazia(l));

    killLista(l);
}

/* =======================================================
   LIMPAR / KILL
   ======================================================= */

void test_limparLista_Valido() {
    LISTA l = criarLista();
    int x = 1;

    pushFimLista(l, &x);
    limparLista(l);

    TEST_ASSERT_EQUAL_INT(1, listaVazia(l));

    killLista(l);
}

/* =======================================================
   MAIN
   ======================================================= */

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criarLista_Valido);

    RUN_TEST(test_pushInicioLista_Valido);
    RUN_TEST(test_pushFimLista_Valido);

    RUN_TEST(test_popInicioLista_Valido);
    RUN_TEST(test_popFimLista_Valido);

    RUN_TEST(test_buscaIdLista_Valido);
    RUN_TEST(test_buscaIdLista_Invalido);
    RUN_TEST(test_popIdLista_Valido);

    RUN_TEST(test_getInicioEProximoLista_Valido);

    RUN_TEST(test_tamanhoLista_Valido);
    RUN_TEST(test_tamanhoLista_Invalido);

    RUN_TEST(test_listaVazia_Valido);

    RUN_TEST(test_limparLista_Valido);

    return UNITY_END();
}