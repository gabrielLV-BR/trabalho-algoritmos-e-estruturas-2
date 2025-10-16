#include "./arquivo_indice.h"

void salva_elemento(FILE *arquivo, indice_hash_elemento elemento) {
    fwrite(&elemento.tamanho, sizeof(elemento.tamanho), 1, arquivo);
    fwrite(elemento.dados, elemento.tamanho, sizeof(char), arquivo);
}

void carrega_elemento(FILE *arquivo, indice_hash_elemento *elemento) {
    fread(&elemento->tamanho, sizeof(elemento->tamanho), 1, arquivo);
    fread(&elemento->dados, elemento->tamanho, sizeof(char), arquivo);
}

void salva_indice_hash(FILE *arquivo, indice_hash indice) {
    int i;
    indice_hash_node *node;
    // salva tamanho do dicionário do indice
    fwrite(&indice.tamanho, sizeof(indice.tamanho), 1, arquivo);

    for (i = 0; i < indice.tamanho; i++) {
        node = indice.valores[i];

        while (node) {
            // escreve cada entrada do dicionário
            salva_elemento(arquivo, node->chave);
            salva_elemento(arquivo, node->valor);
            node = node->proximo;
        }
    }
}


void carrega_indice_hash(FILE *arquivo, indice_hash *indice) {
    int i;
    indice_hash_elemento chave, valor;
    fread(&i, sizeof(indice->tamanho), 1, arquivo);

    *indice = cria_indice_hash(i);

    for (i = 0; i < indice->tamanho; i++) {
        // recarrega nós do arquivo
        carrega_elemento(arquivo, &chave);
        carrega_elemento(arquivo, &valor);

        insere_indice_hash(indice, chave, valor);
    }
}