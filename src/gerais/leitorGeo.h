#ifndef LEITOR_GEO_H
#define LEITOR_GEO_H

#include "../estruturas/lista.h"
#include "leitorDeArquivos.h"

/*
 * @file leitorGeo.h
 * @brief Interface para o processamento de arquivos GEO.
 *
 * Este módulo é responsável por interpretar arquivos de entrada no formato GEO,
 * construindo as estruturas internas do sistema a partir das instruções lidas.
 *
 * O resultado do processamento é um sistema contendo as formas geométricas
 * definidas no arquivo, organizadas em estruturas apropriadas (ex: listas).
 *
 * O módulo utiliza um tipo opaco para encapsular o estado interno do sistema,
 * garantindo abstração e isolamento da implementação.
 */

/**
 * @brief Tipo abstrato que representa o sistema gerado a partir do arquivo GEO.
 */
typedef void* SISTEMA;

/**
 * @brief Processa um arquivo GEO e constrói o sistema correspondente.
 *
 * @param arqData Estrutura contendo informações do arquivo GEO
 *
 * @return SISTEMA Ponteiro para o sistema criado
 * @return NULL Em caso de erro no processamento ou alocação
 *
 * @note O sistema contém as formas geométricas interpretadas do arquivo.
 */
SISTEMA processarGeo (DadosArquivo arqData);

/**
 * @brief Retorna a lista de formas armazenadas no sistema.
 *
 * @param s Sistema
 *
 * @return LISTA Lista de formas
 * @return NULL em caso de erro
 */
LISTA getListaFormas(SISTEMA s);

/**
 * @brief Libera toda a memória associada ao sistema GEO.
 *
 * @param s Sistema
 *
 * @note Após a chamada, o sistema não deve mais ser utilizado.
 */
void killSistemaGeo (SISTEMA s);

#endif