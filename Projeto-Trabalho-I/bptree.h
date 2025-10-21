#if !defined(__btree_h__)
#define __btree_h__

#include "./util.h"

#define ORDEM 4

#define MAX_CHAVES (ORDEM - 1)
#define MIN_CHAVES ((ORDEM % 2) ? (ORDEM/2) : (ORDEM/2 - 1))

typedef struct indice_arvorebp_node {
    int folha;
    int num_chaves;
    chave_t chaves[MAX_CHAVES];
    valor_t valores[MAX_CHAVES];
    struct indice_arvorebp_node *pai;
    struct indice_arvorebp_node *filhos[ORDEM];
    struct indice_arvorebp_node *proximo;
} indice_arvorebp_node;

typedef indice_arvorebp_node indice_arvorebp;

indice_arvorebp* cria_indice_arvorebp();

indice_arvorebp *insere_indice_arvorebp(indice_arvorebp *raiz, chave_t chave, valor_t valor);

valor_t busca_indice_arvorebp(indice_arvorebp *raiz, chave_t chave);

void exclui_indice_arvorebp(indice_arvorebp *raiz);

void imprimir_arvore(indice_arvorebp *raiz);

#endif // __btree_h__
