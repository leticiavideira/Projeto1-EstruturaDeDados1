#ifndef FORMA_H
#define FORMA_H

/*
 * @file forma.h
 * @brief Interface para o módulo de Forma.
 *
 * Este módulo atua como um wrapper genérico para diferentes tipos de formas
 * geométricas (círculo, retângulo, linha, texto, etc.), permitindo que sejam
 * manipuladas de forma uniforme em estruturas como listas e filas.
 *
 * Cada forma encapsula:
 * - Um tipo (FormaTipo)
 * - Um ponteiro genérico para os dados específicos da forma
 *
 * O uso de tipo opaco garante encapsulamento da implementação interna.
 */

/**
 * @brief Enumeração dos tipos de formas suportadas.
 */
typedef enum {
    FORMA_CIRCULO,
    FORMA_RETANGULO,
    FORMA_LINHA,
    FORMA_TEXTO,
    FORMA_ESTILO_TEXTO
} FormaTipo;

/**
 * @brief Tipo abstrato que representa uma forma.
 */
typedef void* FORMA;

/**
 * @brief Cria uma nova forma genérica.
 *
 * @param tipo Tipo da forma
 * @param data Ponteiro para a estrutura específica da forma
 *
 * @return FORMA Ponteiro para a forma criada
 *
 * @note O conteúdo de data deve ser compatível com o tipo informado.
 */
FORMA criarForma(FormaTipo tipo, void *data);

/**
 * @brief Retorna o nome textual da forma.
 *
 * @param f Forma
 *
 * @return char* Nome da forma (ex: "circulo", "retangulo")
 * @return NULL em caso de erro
 */
char* getNomeForma (FORMA f);

/**
 * @brief Retorna o identificador da forma.
 *
 * @param f Forma
 *
 * @return int ID da forma
 * @return int -1 em caso de erro
 */
int getIdForma(FORMA f);

/**
 * @brief Obtém o ponto âncora da forma.
 *
 * @param f Forma
 * @param x Saída: coordenada x
 * @param y Saída: coordenada y
 *
 * @note O significado da âncora depende do tipo da forma.
 */
void getAncoraForma(FORMA f, double *x, double *y);

/**
 * @brief Retorna o tipo da forma (com base no enum).
 *
 * @param f Forma
 *
 * @return FormaTipo Tipo da forma
 */
FormaTipo getTipoForma(FORMA f);

/**
 * @brief Retorna o ponteiro para os dados internos da forma.
 *
 * @param f Forma
 *
 * @return void* Ponteiro para a estrutura específica da forma
 *
 * @warning O uso deste ponteiro deve respeitar o tipo da forma.
 */
void* getDataForma(FORMA f);

/**
 * @brief Define a cor da borda da forma.
 *
 * @param f Forma
 * @param cor String representando a cor
 */
void setCorBordaForma(FORMA f, char *cor);

/**
 * @brief Define a cor de preenchimento da forma.
 *
 * @param f Forma
 * @param cor String representando a cor
 */
void setCorPreenchimentoForma(FORMA f, char *cor);

/**
 * @brief Move a forma no plano cartesiano.
 *
 * @param f Forma
 * @param dx Deslocamento em x
 * @param dy Deslocamento em y
 */
void moverForma(FORMA f, double dx, double dy);

/**
 * @brief Imprime os dados da forma em formato texto (em um arquivo .txt).
 *
 * @param txt Arquivo de saída
 * @param f Forma
 *
 * @note O formato de saída depende do tipo da forma.
 */
void printFormaTXT(FILE *txt, FORMA f);

/**
 * @brief Libera a memória associada à forma.
 *
 * @param f Forma
 */
void killForma(FORMA f);

#endif