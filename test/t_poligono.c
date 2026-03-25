#include <stdio.h>
#include "../includes/poligono.h"
#include "unity.h"

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



//LISTA getListaVertices_Poligono (POLIGONO p);
void test_getListaVerticesPoligono_Valido() {
    POLIGONO p = criarPoligono();
    insertVertice_Poligono(p, 1, 1);

    TEST_ASSERT_NOT_NULL(getListaVertices_Poligono(p));
}

void test_getListaVerticesPoligono_Invalido() {
    TEST_ASSERT_NULL(getListaVertices_Poligono(NULL));
}


/**
 * @brief Calcula o bounding box do polígono.
 *
 * @param p Polígono
 * @param x Saída: coordenada x mínima
 * @param y Saída: coordenada y mínima
 * @param w Saída: largura
 * @param h Saída: altura
 *
 * @return int 1 sucesso
 * @return int -1 erro
 */
int getBoundingBox_Poligono (POLIGONO p, double *x, double *y, double *w, double *h);

/**
 * @brief Gera os segmentos da borda do polígono.
 *
 * @param p Polígono
 * @param l Lista de saída de segmentos
 *
 * @return int Quantidade de segmentos gerados
 * @return int -1 erro
 */
int produzBorda_Poligono (POLIGONO p, LISTA l);
/**
 * @brief Gera hachura interna do polígono.
 *
 * @param p Polígono
 * @param distancia Espaçamento entre linhas
 * @param corp Cor de preenchimento
 * @param corb Cor da borda
 * @param l Lista de saída
 *
 * @return int 1 sucesso
 * @return int -1 erro
 */
int hachura_Poligono (POLIGONO p, double distancia, char* corp, char* corb, LISTA l);



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