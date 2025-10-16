#if !defined(__escreve_h__)
#define __escreve_h__

#include <stdio.h>

#include "./hash.h"

// funções relacionadas à manipulação dos arquivos de índices

// salva indice hash no arquivo
void salva_indice_hash(FILE *arquivo, indice_hash indice);

// carrega indice hash do arquivo
void carrega_indice_hash(FILE *arquivo, indice_hash *indice);

#endif // __escreve_h__
