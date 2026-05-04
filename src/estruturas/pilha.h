#ifndef PILHA_H
#define PILHA_H

/*
 * @file pilha.h
 * @brief Interface para o módulo de Pilha.
 *
 * Este arquivo define a interface pública para criação, manipulação e destruição
 * de pilhas genéricas. A pilha armazena elementos do tipo void*, permitindo o uso
 * com diferentes tipos de dados.
 *
 * A estrutura segue a política LIFO (Last In, First Out), onde o último
 * elemento inserido é o primeiro a ser removido.
 *
 * O módulo utiliza um tipo opaco (handle) para encapsular a implementação interna,
 * garantindo abstração e segurança na manipulação da estrutura.
 */

/**
 * @brief Tipo abstrato que representa uma pilha.
 */
typedef void* PILHA;

/**
 * @brief Cria e inicializa uma nova pilha vazia.
 *
 * @return PILHA Ponteiro para a pilha criada
 * @return NULL Em caso de erro de alocação
 */
PILHA criarPilha ();

/**
 * @brief Insere um elemento no topo da pilha.
 *
 * @param p Pilha
 * @param conteudo Ponteiro para o conteúdo a ser inserido
 *
 * @return int 1 sucesso
 * @return int 0 erro (p == NULL ou falha de alocação)
 */
int pushPilha (PILHA p, void *conteudo);

/**
 * @brief Remove e retorna o elemento do topo da pilha.
 *
 * @param p Pilha
 *
 * @return void* Conteúdo removido
 * @return NULL em caso de erro ou pilha vazia
 */

void *popPilha (PILHA p);

/**
 * @brief Retorna o elemento do topo da pilha sem removê-lo.
 *
 * @param p Pilha
 *
 * @return void* Conteúdo do topo
 * @return NULL em caso de erro ou pilha vazia
 */
void *topoPilha (PILHA p);

/**
 * @brief Retorna o número de elementos na pilha.
 *
 * @param p Pilha
 *
 * @return int Quantidade de elementos
 * @return int -1 erro (p == NULL)
 */
int tamanhoPilha (PILHA p);

/**
 * @brief Verifica se a pilha está vazia.
 *
 * @param p Pilha
 *
 * @return int 1 se vazia
 * @return int 0 se não vazia
 * @return int -1 erro (p == NULL)
 */
int pilhaVazia (PILHA p);

/**
 * @brief Imprime o conteúdo da pilha.
 *
 * @param p Pilha
 */
void imprimirConteudoPilha (PILHA p);

/**
 * @brief Remove todos os elementos da pilha, mantendo a estrutura válida.
 *
 * @param p Pilha
 *
 * @note Não libera necessariamente os conteúdos apontados pelos elementos.
 */
void limparPilha (PILHA p);

/**
 * @brief Libera toda a memória associada à pilha.
 *
 * @param p Pilha
 *
 * @note Após a chamada, a pilha não deve mais ser utilizada.
 */
void killPilha (PILHA p);

#endif