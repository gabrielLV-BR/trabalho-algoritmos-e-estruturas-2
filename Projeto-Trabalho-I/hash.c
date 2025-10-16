#include "hash.h"

#include <stdlib.h>
#include <string.h>

int hash(indice_hash_elemento chave) {
    int i;
    int acc = 1;
    char *bytes = (char*)chave.dados;

    // faz loucuras com os bytes pra tentar aleatorizar o hash
    for (i = 0; i < chave.tamanho; i++) {
        acc += bytes[i] * 567889;
        acc ^= bytes[i] - 74198;
        acc ^= bytes[i] - 33213;
        acc ^= bytes[i] - 43222;
    }

    return acc;
}

int igual(indice_hash_elemento a, indice_hash_elemento b) {
    int i;
    char *dados_a;
    char *dados_b;

    if (a.tamanho != b.tamanho) return 0;

    dados_a = (char*) a.dados;
    dados_b = (char*) b.dados;
    
    for (i = 0; i < a.tamanho; i++) {
        if (dados_a[i] != dados_b[i]) {
            return 0;
        }
    }

    return 1;
}

indice_hash_node *cria_node(indice_hash_elemento chave, indice_hash_elemento valor) {
    indice_hash_node *node = malloc(sizeof(indice_hash_node));

    node->chave = chave;
    node->valor = valor;
    node->proximo = NULL;

    return node;
}

void libera_node(indice_hash_node *node) {
    free(node->chave.dados);
    free(node->valor.dados);
    free(node);
}

void libera_lista_node(indice_hash_node *node) {
    if (node) {
        libera_lista_node(node->proximo);
    }

    libera_node(node);
}

indice_hash_node *remove_node(indice_hash_node *node, indice_hash_elemento chave) {
    indice_hash_node *proximo;

    if (!node) {
        return NULL;
    }

    if (igual(node->chave, chave)) {
        proximo = node->proximo;
        libera_node(node);
        return proximo;
    }

    node->proximo = remove_node(node->proximo, chave);
    return node;
}


indice_hash cria_indice_hash(int tamanho_dicionario) {
    indice_hash indice;

    indice.tamanho = tamanho_dicionario;
    indice.valores = calloc(tamanho_dicionario, sizeof(indice_hash_elemento));

    return indice;
}

indice_hash_elemento elem(const char *str) {
    indice_hash_elemento elemento;

    elemento.dados   = (void*) str;
    elemento.tamanho = strlen(str);

    return elemento;
}

void insere_indice_hash(indice_hash *indice, indice_hash_elemento chave, indice_hash_elemento valor) {
    indice_hash_node *node;
    indice_hash_node *novo;
    int idx = hash(chave) % indice->tamanho;

    // elemento já existe
    if (busca_indice_hash(indice, chave)) {
        return;
    }

    node = indice->valores[idx];
    novo = cria_node(chave, valor);

    // verifica se houve colisão...
    if (!node) {
        // ...se não, insere na posição diretamente e retorna
        indice->valores[idx] = novo;
        return;
    }

    // ...caso contrário, busca último elemento da lista
    while (node->proximo) node = node->proximo;

    // insere chave e valor na última posição
    node->proximo = novo;
}

indice_hash_elemento* busca_indice_hash(indice_hash *indice, indice_hash_elemento chave) {
    indice_hash_node *node;
    int idx = hash(chave) % indice->tamanho;

    node = indice->valores[idx];

    // iteramos toda a lista enquanto não encontrarmos a mesma chave
    while (node && !igual(node->chave, chave)) node = node->proximo;

    // se o nó é nulo, então varremos toda a lista sem encontrar nosso elemento
    // retorna nulo
    if (!node) {
        return NULL;
    }

    // retorna valor encontrado
    return &node->valor;
}

void remove_indice_hash(indice_hash *indice, indice_hash_elemento chave) {
    indice_hash_node *node;
    int idx = hash(chave) % indice->tamanho;

    indice->valores[idx] = remove_node(indice->valores[idx], chave);
}

void deleta_indice_hash(indice_hash *indice) {
    int i;

    for (i = 0; i < indice->tamanho; i++) {
        libera_node(indice->valores[i]);
    }

    free(indice->valores);
    indice->tamanho = 0;
}