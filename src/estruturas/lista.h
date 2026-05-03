#ifndef LISTA_H
#define LISTA_H

/*
 * @file lista.h
 * @brief Interface para o módulo de Lista.
 *
 * Este arquivo define a interface pública para criação, manipulação e destruição
 * de listas genéricas. A lista armazena elementos do tipo void*, permitindo o uso
 * com diferentes tipos de dados.
 *
 * O módulo utiliza um tipo opaco (handle) para encapsular a implementação interna,
 * oferecendo operações de inserção e remoção no início e no fim, busca e remoção
 * por conteúdo, consulta de tamanho, verificação de lista vazia, além de funções
 * para impressão e gerenciamento de memória.
 */

/**
 * @brief Tipo abstrato que representa uma lista.
 */
typedef void* LISTA;

/**
 * @brief Cria e inicializa uma nova lista vazia.
 *
 * @return LISTA Ponteiro para a lista criada
 * @return NULL Em caso de erro de alocação
 */
LISTA criarLista ();

/**
 * @brief Insere um elemento no início da lista.
 *
 * @param l Lista
 * @param conteudo Ponteiro para o conteúdo a ser inserido
 *
 * @return int 1 sucesso
 * @return int 0 erro
 */
int pushInicioLista (LISTA l, void *conteudo);

/**
 * @brief Insere um elemento no final da lista.
 *
 * @param l Lista
 * @param conteudo Ponteiro para o conteúdo a ser inserido
 *
 * @return int 1 sucesso
 * @return int 0 erro
 */
int pushFimLista (LISTA l, void *conteudo);

/**
 * @brief Retorna o primeiro elemento (nó) da lista.
 *
 * @param l Lista
 *
 * @return void* Ponteiro para o elemento interno (nó da lista)
 * @return NULL se lista vazia ou erro
 */
void* getInicioLista(LISTA l);

/**
 * @brief Retorna o próximo elemento (nó) da lista a partir de um elemento atual.
 *
 * @param l Lista
 * @param atual Elemento atual (obtido previamente da lista)
 *
 * @return void* Próximo elemento
 * @return NULL se não houver próximo ou erro
 */
void* getProximoLista(LISTA l, void* atual);

/**
 * @brief Retorna o conteúdo armazenado em um elemento da lista.
 *
 * @param elemento Elemento interno da lista
 *
 * @return void* Conteúdo armazenado
 * @return NULL em caso de erro
 */
void* getConteudoElemLista (void *elemento);

/**
 * @brief Remove e retorna o elemento do início da lista.
 *
 * @param l Lista
 *
 * @return void* Conteúdo removido
 * @return NULL erro ou lista vazia
 */
void *popInicioLista (LISTA l);

/**
 * @brief Remove e retorna o elemento do final da lista.
 *
 * @param l Lista
 *
 * @return void* Conteúdo removido
 * @return NULL erro ou lista vazia
 */
void *popFimLista (LISTA l);

/**
 * @brief Remove e retorna um elemento da lista com base no conteúdo.
 *
 * @param l Lista
 * @param conteudo Conteúdo a ser removido (critério de comparação)
 *
 * @return void* Conteúdo removido
 * @return NULL se não encontrado ou erro
 */
void *popIdLista (LISTA l, void *conteudo);

/**
 * @brief Busca um elemento na lista com base no conteúdo.
 *
 * @param l Lista
 * @param conteudo Conteúdo a ser buscado
 *
 * @return void* Conteúdo encontrado
 * @return NULL se não encontrado ou erro
 */
void *buscaIdLista (LISTA l, void *conteudo);

/**
 * @brief Retorna o número de elementos da lista.
 *
 * @param l Lista
 *
 * @return int Tamanho da lista
 * @return int -1 erro (l == NULL)
 */
int tamanhoLista (LISTA l);

/**
 * @brief Verifica se a lista está vazia.
 *
 * @param l Lista
 *
 * @return int 1 vazia
 * @return int 0 não vazia
 * @return int -1 erro (l == NULL)
 */
int listaVazia (LISTA l);

/**
 * @brief Imprime o conteúdo da lista.
 *
 * @param l Lista
 */
void imprimirConteudoLista (LISTA l);

/**
 * @brief Remove todos os elementos da lista, mantendo a estrutura alocada.
 *
 * @param l Lista
 */
void limparLista (LISTA l);

/**
 * @brief Libera toda a memória associada à lista.
 *
 * @param l Lista
 */
void killLista (LISTA l);

#endif