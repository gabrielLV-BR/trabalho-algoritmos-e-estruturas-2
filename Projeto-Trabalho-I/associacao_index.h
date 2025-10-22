#ifndef ASSOCIACAO_INDEX_H_INCLUDED
#define ASSOCIACAO_INDEX_H_INCLUDED
#include "sort.h"
#include "types.h"


/* Constrói:
   - AssociacaoOrdenada.bin  (associacoes ordenadas por id_pedido)
   - IndiceAssociacaoNivel-1.bin (vetor de IndexAssociacao ordenado por id_pedido)
   Retorna a quantidade de entradas no índice, ou -1 em erro. */
int organiza_indice_associacao(void);

/* Busca binária no índice por id_pedido.
   Retorna 0 em sucesso e define *start/*count; -1 se não encontrado; -2 em erro. */
int pesquisa_por_id_associacao(const char id_pedido[20], int *start, int *count);

#endif // ASSOSIACAO_INDEX_H_INCLUDED
