#if !defined(__hash_h__)
#define __hash_h__

// implementação simples de um hash_map para utilização como índice

typedef struct indice_hash_elemento_t {
    int     tamanho;
    void    *dados;
} indice_hash_elemento;

typedef struct indice_hash_node_t {
    indice_hash_elemento        chave;
    indice_hash_elemento        valor;
    struct indice_hash_node_t   *proximo;
} indice_hash_node;

typedef struct indice_hash_t {
    int                 tamanho;
    indice_hash_node    **valores;
} indice_hash;

// cria um indice_hash_elemento a partir de uma string
indice_hash_elemento elem(const char *str);

// cria índice hash com capacidade para *tamanho_dicionario* elementos
indice_hash cria_indice_hash(int tamanho_dicionario);

// insere a chave com o determinado valor no índice
void insere_indice_hash(indice_hash *indice, indice_hash_elemento chave, indice_hash_elemento valor);

// busca chave dentro do índice, retornando NULL caso não encontre
indice_hash_elemento* busca_indice_hash(indice_hash *indice, indice_hash_elemento chave);

// remove a chave do índice
void remove_indice_hash(indice_hash *indice, indice_hash_elemento chave);

// exclui todas as chaves do índice
void deleta_indice_hash(indice_hash *indice);

#endif // __hash_h__
