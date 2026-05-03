#ifndef FILA_H
#define FILA_H

/*
 * @file fila.h
 * @brief Interface para o módulo de Fila.
 *
 * Este arquivo define a interface pública para criação, manipulação e destruição
 * de filas genéricas. A fila armazena elementos do tipo genérico (void*),
 * permitindo reutilização para diferentes tipos de dados.
 *
 * A estrutura segue a política FIFO (First In, First Out), onde o primeiro
 * elemento inserido é o primeiro a ser removido.
 *
 * O módulo utiliza um tipo opaco (handle) para encapsular a implementação interna,
 * garantindo abstração e segurança na manipulação da estrutura.
 */

/**
 * @brief Tipo abstrato que representa uma fila.
 */
typedef void *FILA;

/**
 * @brief Cria e inicializa uma nova fila vazia.
 *
 * @return FILA Ponteiro para a fila criada
 * @return NULL Em caso de erro de alocação
 */
FILA criarFila ();

/**
 * @brief Insere um elemento no final da fila.
 *
 * @param f Fila
 * @param conteudo Ponteiro para o conteúdo a ser inserido
 *
 * @return int 1 se inserido com sucesso
 * @return int 0 em caso de erro (fila NULL ou falha de alocação)
 */
int pushFila (FILA f, void *conteudo);

/**
 * @brief Remove e retorna o primeiro elemento da fila.
 *
 * @param f Fila
 *
 * @return void* Ponteiro para o elemento removido
 * @return NULL em caso de erro ou fila vazia
 */
void *popFila (FILA f);

/**
 * @brief Retorna o primeiro elemento da fila sem removê-lo.
 *
 * @param f Fila
 *
 * @return void* Ponteiro para o primeiro elemento
 * @return NULL em caso de erro ou fila vazia
 */
void *primeiroElementoFila (FILA f);

/**
 * @brief Retorna a quantidade de elementos na fila.
 *
 * @param f Fila
 *
 * @return int Número de elementos
 * @return int 0 em caso de erro (f == NULL)
 */
int tamanhoFila (FILA f);

/**
 * @brief Verifica se a fila está vazia.
 *
 * @param f Fila
 *
 * @return int 1 se vazia
 * @return int 0 se não vazia
 * @return int -1 em caso de erro (f == NULL)
 */
int filaVazia (FILA f);

/**
 * @brief Imprime o conteúdo da fila.
 *
 * @param f Fila
 *
 * @note A forma de impressão depende do tipo de dado armazenado.
 *       Este módulo pode exigir que os elementos tenham uma função
 *       de impressão definida externamente.
 */
void imprimirConteudoFila (FILA f);

/**
 * @brief Remove todos os elementos da fila, mantendo a estrutura válida.
 *
 * @param f Fila
 *
 * @note Não libera necessariamente o conteúdo apontado pelos elementos,
 *       apenas os nós internos da fila.
 */
void limparFila (FILA f);

/**
 * @brief Libera toda a memória associada à fila.
 *
 * @param f Fila
 *
 * @note Após a chamada, a fila não deve mais ser utilizada.
 */
void killFila (FILA f);

#endif