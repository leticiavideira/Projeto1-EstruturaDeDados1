#ifndef LEITOR_QRY_H
#define LEITOR_QRY_H

#include "../estruturas/lista.h"
#include "../estruturas/fila.h"
#include "leitorDeArquivos.h"

/*
 * @file leitorQry.h
 * @brief Interface para o processamento de arquivos QRY.
 *
 * Este módulo é responsável por interpretar e executar comandos contidos
 * em arquivos QRY, aplicando operações sobre as formas previamente carregadas
 * a partir de um arquivo GEO.
 *
 * As operações podem incluir:
 * - Seleção de formas
 * - Remoção de elementos
 * - Alterações de propriedades
 * - Geração de saídas (ex: SVG, TXT)
 *
 * O módulo atua diretamente sobre as estruturas fornecidas, podendo modificar
 * seu estado e gerar arquivos de saída.
 */

/**
 * @brief Executa os comandos de um arquivo QRY sobre um conjunto de formas.
 *
 * @param arqQry Dados do arquivo QRY
 * @param arqGeo Dados do arquivo GEO
 * @param formasGeo Lista de formas carregadas do GEO
 * @param saidaPath Caminho base para geração dos arquivos de saída
 */
void executarQry(DadosArquivo arqQry, DadosArquivo arqGeo, LISTA formasGeo, char *saidaPath);

#endif