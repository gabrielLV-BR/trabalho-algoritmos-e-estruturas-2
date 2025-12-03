#include "./arquivo_indice.h"

#include <stdlib.h>

void salva_indice_hash(FILE *arquivo, indice_hash indice) {
    int i;
    indice_hash_node *node;
    // salva tamanho do dicionário do indice
    fwrite(&indice.tamanho, sizeof(indice.tamanho), 1, arquivo);

    for (i = 0; i < indice.tamanho; i++) {
        node = indice.valores[i];

        while (node) {
            // escreve cada entrada do dicionário
            fwrite(&node->chave, sizeof(chave_t), 1, arquivo);
            fwrite(&node->valor, sizeof(valor_t), 1, arquivo);
            node = node->proximo;
        }
    }
}

void carrega_indice_hash(FILE *arquivo, indice_hash *indice) {
    int i;
    chave_t chave;
    valor_t valor;
    fread(&i, sizeof(indice->tamanho), 1, arquivo);

    *indice = cria_indice_hash();

    for (i = 0; i < indice->tamanho; i++) {
        // recarrega nós do arquivo
        fread(&chave, sizeof(chave_t), 1, arquivo);
        fread(&valor, sizeof(valor_t), 1, arquivo);
        insere_indice_hash(indice, chave, valor);
    }
}


// salva indice árvore B+ no arquivo
void salva_indice_arvorebp(FILE *arquivo, indice_arvorebp *arvore) {
    int i;

    if (!arvore) {
        return;
    }

    fwrite(&arvore->num_chaves, sizeof(arvore->num_chaves), 1, arquivo);

    for (i = 0; i <= arvore->num_chaves; i++) {
        if (!arvore->folha) {
            salva_indice_arvorebp(arquivo, arvore->filhos[i]);
        }

        if (i < arvore->num_chaves) {
            fwrite(&arvore->chaves[i], sizeof(chave_t), 1, arquivo);
            fwrite(&arvore->valores[i], sizeof(valor_t), 1, arquivo);
        }
    }
}

// carrega indice árvore B+ do arquivo
void carrega_indice_arvorebp(FILE *arquivo, indice_arvorebp *arvore) {
    chave_t chave;
    valor_t valor;

    char chave_str[20];
    char valor_str[20];

    while ((fscanf(arquivo, "%20s", chave_str) == 1)
        && (fscanf(arquivo, "%20s", valor_str) == 1)) {
        
        chave = str_para_long(chave_str);
        valor = str_para_long(valor_str);

        insere_indice_arvorebp(arvore, chave, valor);
    }
}