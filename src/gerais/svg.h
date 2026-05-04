#ifndef SVG_H
#define SVG_H

#include "../estruturas/lista.h"
#include "leitorDeArquivos.h"

/*
 * @file svg.h
 * @brief Interface para geração de arquivos SVG.
 *
 * Este módulo é responsável por gerar representações visuais (arquivos SVG)
 * a partir de estruturas de dados contendo formas geométricas.
 *
 * Ele atua como camada de saída do sistema, convertendo objetos internos
 * (armazenados em estruturas de dados) em elementos gráficos compatíveis com o padrão SVG.
 */

/**
 * @brief Gera um arquivo SVG a partir de uma lista de formas.
 *
 * @param formas Lista de formas a serem renderizadas
 * @param saidaPath Caminho base do arquivo de saída
 * @param arqData Estrutura com dados do arquivo de entrada (.geo)
 * @param sufixo Sufixo adicional para composição do nome do arquivo
 *
 * @note Cada forma da lista deve ser interpretável pelo módulo de forma.
 */
void gerarSVG(LISTA formas, const char *saidaPath, DadosArquivo arqData, const char *sufixo);

/**
 * @brief Gera um arquivo SVG considerando comandos do arquivo QRY.
 *
 * @param banco Lista principal de formas (estado atual)
 * @param selecionados Lista de formas selecionadas
 * @param removidos Lista de formas removidas
 * @param sel_x Coordenada x da região de seleção
 * @param sel_y Coordenada y da região de seleção
 * @param sel_w Largura da região de seleção
 * @param sel_h Altura da região de seleção
 * @param saidaPath Caminho base do arquivo de saída
 * @param arqGeo Dados do arquivo .geo
 * @param arqQry Dados do arquivo .qry
 *
 * @note Este método representa o estado do sistema após execução de comandos QRY,
 *       incluindo marcações visuais como seleção e remoção.
 */
void gerarSVG_QRY(LISTA banco, LISTA selecionados, LISTA removidos, double sel_x, double sel_y, double sel_w, double sel_h, const char *saidaPath, DadosArquivo arqGeo, DadosArquivo arqQry);

#endif