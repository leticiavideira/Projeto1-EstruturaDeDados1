#include <stdio.h>
#include "unity.h"
#include "../gerais/poligono.h"


/* =======================================================
   Funções de Teste
   ======================================================= */

//CRIAÇÃO

//POLIGONO criarPoligono ();
void test_criarPoligono_Valido() {
    POLIGONO p = criarPoligono();
    TEST_ASSERT_NOT_NULL(p);
    kill_Poligono(p);
}
void test_criarPoligono_comecarVazio_Valido(){
    POLIGONO p = criarPoligono();

    int r = estaVazio_Poligono(p);

    TEST_ASSERT_EQUAL_INT(1, r);

    kill_Poligono(p);
}


//INSERÇÃO

//int insertVertice_Poligono (POLIGONO p, double x, double y);
void test_insertVerticePoligono_Valido () {
    POLIGONO p = criarPoligono();

    int r = insertVertice_Poligono(p, 10, 20);

    TEST_ASSERT_EQUAL_INT(1, r);
    TEST_ASSERT_EQUAL_INT(1, getNumeroVertices_Poligono(p));

    kill_Poligono (p);
}
void test_insertVerticePoligono_Invalido () {
    int r = insertVertice_Poligono (NULL, 10, 20);

    TEST_ASSERT_EQUAL_INT(-1, r);
}


//GETTERS

//int getNumeroVertices_Poligono (POLIGONO p);
void test_getNumeroVerticesPoligono_Valido(){
    POLIGONO p = criarPoligono();

    insertVertice_Poligono(p, 1, 1);
    insertVertice_Poligono(p, 2, 2);


    TEST_ASSERT_EQUAL_INT(2, getNumeroVertices_Poligono(p));

    kill_Poligono(p);
}

void test_getNumeroVerticesPoligono_Invalido(){
    int r = getNumeroVertices_Poligono(NULL);

    TEST_ASSERT_EQUAL_INT(-1, r);
}


//FILA getFilaVertices_Poligono (POLIGONO p);
void test_getFilaVerticesPoligono_Valido() {
    POLIGONO p = criarPoligono();
    insertVertice_Poligono(p, 1, 1);

    FILA f = getFilaVertices_Poligono(p);

    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL_INT(1, tamanhoFila(f));
}

void test_getFilaVerticesPoligono_Invalido() {
    TEST_ASSERT_NULL(getFilaVertices_Poligono(NULL));
}


//int getBoundingBox_Poligono (POLIGONO p, double *x, double *y, double *w, double *h);
void test_getBoundingBoxPoligono_formatoRegular_Valido(){
    POLIGONO p = criarPoligono();

    insertVertice_Poligono(p, 0, 0);
    insertVertice_Poligono(p, 2, 0);
    insertVertice_Poligono(p, 2, 2);
    insertVertice_Poligono(p, 0, 2);

    double x, y, w, h;
    int r = getBoundingBox_Poligono(p, &x, &y, &w, &h);

    TEST_ASSERT_EQUAL_INT(1, r);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 0, x);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 0, y);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 2, w);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 2, h);

    kill_Poligono(p);
}
void test_getBoundingBoxPoligono_formatoIrregular_Valido(){
    POLIGONO p = criarPoligono();

    insertVertice_Poligono(p, -1, 3);
    insertVertice_Poligono(p, 4, 2);
    insertVertice_Poligono(p, 2, -2);

    double x, y, w, h;
    int r = getBoundingBox_Poligono(p, &x, &y, &w, &h);

    TEST_ASSERT_EQUAL_INT(1, r);
    TEST_ASSERT_FLOAT_WITHIN(0.001, -1, x);
    TEST_ASSERT_FLOAT_WITHIN(0.001, -2, y);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 5, w);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 5, h);

    kill_Poligono(p);
}
void test_getBoundingBoxPoligono_Invalido(){
    double x, y, w, h;
    int r = getBoundingBox_Poligono(NULL, &x, &y, &w, &h);

    TEST_ASSERT_EQUAL_INT(-1, r);
}



//int produzBorda_Poligono (POLIGONO p, FILA f);
void test_produzBordaPoligono_Valido(){
    POLIGONO p = criarPoligono();

    insertVertice_Poligono(p, 0, 0);
    insertVertice_Poligono(p, 0, 2);
    insertVertice_Poligono(p, 2, 2);
    insertVertice_Poligono(p, 2, 0);

    FILA f = criarFila();
    int r = produzBorda_Poligono(p, f);

    TEST_ASSERT_EQUAL_INT(4, r);
    TEST_ASSERT_EQUAL_INT(4, tamanhoFila(f));

    killFila(f);
    kill_Poligono(p);
}
void test_produzBordaPoligono_poligonoVazio_Invalido(){
    POLIGONO p = criarPoligono();
    FILA f = criarFila();

    int r = produzBorda_Poligono(p, f);

    TEST_ASSERT_EQUAL_INT(-1, r);

    killFila(f);
    kill_Poligono(p);
}
void test_produzBordaPoligono_menosDe3Vertices_Invalido(){
    POLIGONO p = criarPoligono();
    FILA f = criarFila();

    insertVertice_Poligono(p, 0, 0);
    insertVertice_Poligono(p, 1, 1);

    int r = produzBorda_Poligono(p, f);

    TEST_ASSERT_EQUAL_INT(-1, r);

    killFila(f);
    kill_Poligono(p);
}
void test_produzBordaPoligono_poligonoNULL_Invalido(){
    FILA f = criarFila();

    int r = produzBorda_Poligono(NULL, f);

    TEST_ASSERT_EQUAL_INT(-1, r);

    killFila(f);
}
void test_produzBordaPoligono_filaNULL_Invalido(){
    POLIGONO p = criarPoligono();

    int r = produzBorda_Poligono(p, NULL);

    TEST_ASSERT_EQUAL_INT(-1, r);

    kill_Poligono(p);
}


//int hachura_Poligono (POLIGONO p, double distancia, char* corp, char* corb, FILA f)
void test_hachuraPoligono_Valido(){
    POLIGONO p = criarPoligono();
    insertVertice_Poligono(p, 1, 1);
    insertVertice_Poligono(p, 1, 4);
    insertVertice_Poligono(p, 4, 4);
    insertVertice_Poligono(p, 4, 1);

    char* corp = "grey", corb = "magenta";
    FILA f = criarFila();

    int r = hachura_Poligono(p, 0.1, corp, corb, f);

    TEST_ASSERT_EQUAL_INT(1, r);

    TEST_ASSERT_TRUE(tamanhoFila(f) > 0);

    killFila(f);
    kill_Poligono(p);
}
void test_hachuraPoligono_menosDe3Vertices_Invalido(){
    POLIGONO p = criarPoligono();
    insertVertice_Poligono(p, 1, 1);
    insertVertice_Poligono(p, 2, 2);

    FILA f = criarFila();

    int r = hachura_Poligono(p, 0.1, "grey", "black", f);

    TEST_ASSERT_EQUAL_INT(-1, r);

    killFila(f);
    kill_Poligono(p);
}
void test_hachuraPoligono_poligonoNULL_Invalido(){
    char* corp = "grey", corb = "magenta";
    FILA f = criarFila();

    int r = hachura_Poligono(NULL, 0.1, corp, corb, f);

    TEST_ASSERT_EQUAL_INT(-1, r);

    killFila(f);
}
void test_hachuraPoligono_filaNULL_Invalido(){
    char* corp = "grey", corb = "magenta";
    POLIGONO p = criarPoligono();

    int r = hachura_Poligono(p, 0.1, corp, corb, NULL);

    TEST_ASSERT_EQUAL_INT(-1, r);

    kill_Poligono(p);
}



//int isInside_Poligono (POLIGONO p, double x, double y);
void test_isInsidePoligono_estaDentro_Valido(){
    POLIGONO p = criarPoligono();
    insertVertice_Poligono(p, 0, 0);
    insertVertice_Poligono(p, 4, 0);
    insertVertice_Poligono(p, 4, 4);
    insertVertice_Poligono(p, 0, 4);

    int r = isInside_Poligono(p, 2, 2);

    TEST_ASSERT_EQUAL_INT(1, r);

    kill_Poligono(p);
}
void test_isInsidePoligono_naoEstaDentro_Valido(){
    POLIGONO p = criarPoligono();
    insertVertice_Poligono(p, 0, 0);
    insertVertice_Poligono(p, 4, 0);
    insertVertice_Poligono(p, 4, 4);
    insertVertice_Poligono(p, 0, 4);

    int r = isInside_Poligono(p, 8, 2);

    TEST_ASSERT_EQUAL_INT(0, r);

    kill_Poligono(p);
}
void test_isInsidePoligono_naBorda_Valido(){
    POLIGONO p = criarPoligono();
    insertVertice_Poligono(p, 0, 0);
    insertVertice_Poligono(p, 4, 0);
    insertVertice_Poligono(p, 4, 4);
    insertVertice_Poligono(p, 0, 4);

    int r = isInside_Poligono(p, 0, 2);

    TEST_ASSERT_TRUE(r == 0);

    kill_Poligono(p);
}
void test_isInsidePoligono_Invalido(){
    int r = isInside_Poligono(NULL, 1, 1);

    TEST_ASSERT_EQUAL_INT(-1, r);
}



//int estaVazio_Poligono (POLIGONO p);
void test_estaVazioPoligono_vazio_Valido(){
    POLIGONO p = criarPoligono();
    
    TEST_ASSERT_EQUAL_INT(1, estaVazio_Poligono(p));

    kill_Poligono(p);
}
void test_estaVazioPoligono_naoVazio_Valido(){
    POLIGONO p = criarPoligono();
    insertVertice_Poligono(p, 1, 1);

    TEST_ASSERT_EQUAL_INT(0, estaVazio_Poligono(p));

    kill_Poligono(p);
}
void test_estaVazioPoligono_Invalido(){
    int r = estaVazio_Poligono(NULL);

    TEST_ASSERT_EQUAL_INT(-1, r);
}



//int removeVertice_Poligono (POLIGONO p, double x, double y);
void test_removeVerticePoligono_Valido(){
    POLIGONO p = criarPoligono();
    insertVertice_Poligono(p, 1, 1);
    insertVertice_Poligono(p, 2, 2);
    int r = removeVertice_Poligono(p, 1, 1);

    TEST_ASSERT_EQUAL_INT(1, r);
    TEST_ASSERT_EQUAL_INT(1, getNumeroVertices_Poligono(p));

    kill_Poligono(p);
}
void test_removeVerticePoligono_removeTudo_Valido(){
    POLIGONO p = criarPoligono();
    insertVertice_Poligono(p, 1, 1);

    removeVertice_Poligono(p, 1, 1);

    TEST_ASSERT_EQUAL_INT(1, estaVazio_Poligono(p));

    kill_Poligono(p);
}
void test_removeVerticePoligono_coordenadaInexistente_Invalido(){
    POLIGONO p = criarPoligono();
    insertVertice_Poligono(p, 1, 2);

    int r = removeVertice_Poligono(p, 4, 5);

    TEST_ASSERT_EQUAL_INT(-1, r);

    kill_Poligono(p);
}
void test_removeVerticePoligono_poligonoNULL_Invalido(){
    int r = removeVertice_Poligono(NULL, 1, 1);

    TEST_ASSERT_EQUAL_INT(-1, r);
}


//int kill_Poligono (POLIGONO p);
void test_killPoligono_Valido(){
    POLIGONO p = criarPoligono();
    int r = kill_Poligono(p);

    TEST_ASSERT_EQUAL_INT(1, r);
}
void test_killPoligono_Invalido(){
    int r = kill_Poligono(NULL);

    TEST_ASSERT_EQUAL_INT(-1, r);
}

/* =======================================================
   MAIN
   ======================================================= */

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_criarPoligono_Valido);
    RUN_TEST(test_criarPoligono_comecarVazio_Valido);

    RUN_TEST(test_insertVerticePoligono_Valido);
    RUN_TEST(test_insertVerticePoligono_Invalido);

    RUN_TEST(test_getNumeroVerticesPoligono_Valido);
    RUN_TEST(test_getNumeroVerticesPoligono_Invalido);

    RUN_TEST(test_getFilaVerticesPoligono_Valido);
    RUN_TEST(test_getFilaVerticesPoligono_Invalido);

    RUN_TEST(test_getBoundingBoxPoligono_formatoRegular_Valido);
    RUN_TEST(test_getBoundingBoxPoligono_formatoIrregular_Valido);
    RUN_TEST(test_getBoundingBoxPoligono_Invalido);

    RUN_TEST(test_produzBordaPoligono_Valido);
    RUN_TEST(test_produzBordaPoligono_menosDe3Vertices_Invalido);
    RUN_TEST(test_produzBordaPoligono_poligonoVazio_Invalido);
    RUN_TEST(test_produzBordaPoligono_filaNULL_Invalido);
    RUN_TEST(test_produzBordaPoligono_poligonoNULL_Invalido);

    RUN_TEST(test_hachuraPoligono_Valido);
    RUN_TEST(test_hachuraPoligono_menosDe3Vertices_Invalido);
    RUN_TEST(test_hachuraPoligono_filaNULL_Invalido);
    RUN_TEST(test_hachuraPoligono_poligonoNULL_Invalido);

    RUN_TEST(test_isInsidePoligono_estaDentro_Valido);
    RUN_TEST(test_isInsidePoligono_naoEstaDentro_Valido);
    RUN_TEST(test_isInsidePoligono_naBorda_Valido);
    RUN_TEST(test_isInsidePoligono_Invalido);

    RUN_TEST(test_estaVazioPoligono_vazio_Valido);
    RUN_TEST(test_estaVazioPoligono_naoVazio_Valido);
    RUN_TEST(test_estaVazioPoligono_Invalido);

    RUN_TEST(test_removeVerticePoligono_Valido);
    RUN_TEST(test_removeVerticePoligono_removeTudo_Valido);
    RUN_TEST(test_removeVerticePoligono_coordenadaInexistente_Invalido);
    RUN_TEST(test_removeVerticePoligono_poligonoNULL_Invalido);

    RUN_TEST(test_killPoligono_Valido);
    RUN_TEST(test_killPoligono_Invalido);

    return UNITY_END();
}