#include <stdio.h>
#include "unity.h"
#include "../gerais/poligono.h"
#include "../estruturas/fila.h"

void setUp(void) {}
void tearDown(void) {}

/* =======================================================
   CRIAÇÃO
   ======================================================= */

void test_criarPoligono_Valido() {
    POLIGONO p = criarPoligono();
    TEST_ASSERT_NOT_NULL(p);
    kill_Poligono(p);
}

/* =======================================================
   INSERÇÃO + CONTAGEM
   ======================================================= */

void test_insertVertice_Valido() {
    POLIGONO p = criarPoligono();

    insertVertice_Poligono(p, 1, 1);
    insertVertice_Poligono(p, 2, 2);

    TEST_ASSERT_EQUAL_INT(2, getNumeroVertices_Poligono(p));

    kill_Poligono(p);
}

void test_insertVertice_Invalido() {
    TEST_ASSERT_EQUAL_INT(-1, insertVertice_Poligono(NULL, 1, 1));
}

/* =======================================================
   REMOÇÃO FIFO
   ======================================================= */

void test_removePrimeiroVertice_Valido() {
    POLIGONO p = criarPoligono();

    insertVertice_Poligono(p, 1, 1);
    insertVertice_Poligono(p, 2, 2);

    double x, y;
    int r = removePrimeiroVertice_Poligono(p, &x, &y);

    TEST_ASSERT_EQUAL_INT(1, r);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 1, x);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 1, y);

    kill_Poligono(p);
}

void test_removePrimeiroVertice_vazio() {
    POLIGONO p = criarPoligono();

    double x, y;
    int r = removePrimeiroVertice_Poligono(p, &x, &y);

    TEST_ASSERT_EQUAL_INT(-1, r);

    kill_Poligono(p);
}

/* =======================================================
   BOUNDING BOX
   ======================================================= */

void test_boundingBox_Valido() {
    POLIGONO p = criarPoligono();

    insertVertice_Poligono(p, 0, 0);
    insertVertice_Poligono(p, 4, 2);

    double x,y,w,h;
    int r = getBoundingBox_Poligono(p, &x,&y,&w,&h);

    TEST_ASSERT_EQUAL_INT(1, r);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 0, x);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 0, y);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 4, w);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 2, h);

    kill_Poligono(p);
}

void test_boundingBox_Invalido() {
    double x,y,w,h;
    TEST_ASSERT_EQUAL_INT(-1, getBoundingBox_Poligono(NULL,&x,&y,&w,&h));
}

/* =======================================================
   BORDA
   ======================================================= */

void test_produzBorda_Valido() {
    POLIGONO p = criarPoligono();
    FILA f = criarFila();

    insertVertice_Poligono(p,0,0);
    insertVertice_Poligono(p,0,1);
    insertVertice_Poligono(p,1,1);

    int r = produzBorda_Poligono(p,f);

    TEST_ASSERT_TRUE(r > 0);
    TEST_ASSERT_TRUE(tamanhoFila(f) > 0);

    killFila(f);
    kill_Poligono(p);
}

void test_produzBorda_Invalido() {
    FILA f = criarFila();

    TEST_ASSERT_EQUAL_INT(-1, produzBorda_Poligono(NULL, f));

    killFila(f);
}

/* =======================================================
   HACHURA
   ======================================================= */

void test_hachura_Valido() {
    POLIGONO p = criarPoligono();
    FILA f = criarFila();

    insertVertice_Poligono(p,0,0);
    insertVertice_Poligono(p,0,4);
    insertVertice_Poligono(p,4,4);
    insertVertice_Poligono(p,4,0);

    int r = hachura_Poligono(p, 0.5, "red", f);

    TEST_ASSERT_EQUAL_INT(1, r);
    TEST_ASSERT_TRUE(tamanhoFila(f) > 0);

    killFila(f);
    kill_Poligono(p);
}

void test_hachura_Invalido() {
    FILA f = criarFila();

    TEST_ASSERT_EQUAL_INT(-1, hachura_Poligono(NULL, 1, "x", f));

    killFila(f);
}

/* =======================================================
   INSIDE
   ======================================================= */

void test_isInside_Valido() {
    POLIGONO p = criarPoligono();

    insertVertice_Poligono(p,0,0);
    insertVertice_Poligono(p,4,0);
    insertVertice_Poligono(p,4,4);
    insertVertice_Poligono(p,0,4);

    TEST_ASSERT_EQUAL_INT(1, isInside_Poligono(p,2,2));
    TEST_ASSERT_EQUAL_INT(0, isInside_Poligono(p,10,10));

    kill_Poligono(p);
}

void test_isInside_Invalido() {
    TEST_ASSERT_EQUAL_INT(-1, isInside_Poligono(NULL,1,1));
}

/* =======================================================
   LIMPAR
   ======================================================= */

void test_limparPoligono() {
    POLIGONO p = criarPoligono();

    insertVertice_Poligono(p,1,1);

    limparPoligono(p);

    TEST_ASSERT_EQUAL_INT(1, estaVazio_Poligono(p));

    kill_Poligono(p);
}

/* =======================================================
   KILL
   ======================================================= */

void test_killPoligono() {
    POLIGONO p = criarPoligono();
    TEST_ASSERT_EQUAL_INT(1, kill_Poligono(p));
}

void test_killPoligono_Invalido() {
    TEST_ASSERT_EQUAL_INT(-1, kill_Poligono(NULL));
}

/* =======================================================
   MAIN
   ======================================================= */

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criarPoligono_Valido);

    RUN_TEST(test_insertVertice_Valido);
    RUN_TEST(test_insertVertice_Invalido);

    RUN_TEST(test_removePrimeiroVertice_Valido);
    RUN_TEST(test_removePrimeiroVertice_vazio);

    RUN_TEST(test_boundingBox_Valido);
    RUN_TEST(test_boundingBox_Invalido);

    RUN_TEST(test_produzBorda_Valido);
    RUN_TEST(test_produzBorda_Invalido);

    RUN_TEST(test_hachura_Valido);
    RUN_TEST(test_hachura_Invalido);

    RUN_TEST(test_isInside_Valido);
    RUN_TEST(test_isInside_Invalido);

    RUN_TEST(test_limparPoligono);

    RUN_TEST(test_killPoligono);
    RUN_TEST(test_killPoligono_Invalido);

    return UNITY_END();
}