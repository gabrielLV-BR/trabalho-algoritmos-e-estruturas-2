#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bptree.h"

indice_arvorebp* _indice_arvorebp_cria_node(int folha) {
    indice_arvorebp *node = calloc(1, sizeof(indice_arvorebp));
    node->folha = folha;

    return node;
}

indice_arvorebp* cria_indice_arvorebp() {
    return _indice_arvorebp_cria_node(0);
}

indice_arvorebp_node* _indice_arvorebp_busca_folha(indice_arvorebp_node *raiz, chave_t chave) {
    int i;

    if (!raiz) {
        return NULL;
    }

    while (!raiz->folha) {
        for (i = 0; i < raiz->num_chaves && chave >= raiz->chaves[i]; i++);

        raiz = raiz->filhos[i];
    }

    return raiz;
}

int busca_indice_arvorebp(indice_arvorebp *raiz, chave_t chave) {
    if (!raiz) {
        return NULL;
    }

    indice_arvorebp_node *folha = _indice_arvorebp_busca_folha(raiz, chave);
    
    if (!folha) {
        return NULL;
    }

    for (int i = 0; i < folha->num_chaves; i++) {
        if (folha->chaves[i] == chave) {
            return folha->valores[i];
        }
    }

    return NULL;
}

void inserir_em_folha(indice_arvorebp_node *folha, chave_t chave, valor_t valor) {
    int i, j;

    for (i = 0; i < folha->num_chaves && folha->chaves[i] < chave; i++);
    
    if (i < folha->num_chaves && folha->chaves[i] == chave) {
        return;
    }

    for (j = folha->num_chaves; j > i; j--) {
        folha->chaves[j] = folha->chaves[j-1];
        folha->valores[j] = folha->valores[j-1];
    }

    folha->chaves[i] = chave;
    folha->valores[i] = valor;
    folha->num_chaves++;
}

void _indice_arvorebp_inserir(indice_arvorebp_node *no, chave_t chave, indice_arvorebp_node *filho_direito) {
    int i;

    for (i = 0; i < no->num_chaves && no->chaves[i] < chave; i++);
    
    for (int j = no->num_chaves; j > i; j--) {
        no->chaves[j] = no->chaves[j-1];
        no->filhos[j+1] = no->filhos[j];
    }

    no->chaves[i] = chave;
    no->filhos[i+1] = filho_direito;
    no->num_chaves++;
    
    if (filho_direito) {
        filho_direito->pai = no;
    }
}

indice_arvorebp_node* indice_arvorebp_split(indice_arvorebp_node *folha) {
    int i, j, corte = (MAX_CHAVES + 1) / 2;
    indice_arvorebp_node *nova_folha = _indice_arvorebp_cria_node(1);
    
    for (i = corte, j = 0; i < folha->num_chaves; i++, j++) {
        nova_folha->chaves[j] = folha->chaves[i];
        nova_folha->valores[j] = folha->valores[i];
        nova_folha->num_chaves++;
    }

    folha->num_chaves = corte;
    nova_folha->proximo = folha->proximo;

    folha->proximo = nova_folha;
    nova_folha->pai = folha->pai;

    return nova_folha;
}

indice_arvorebp_node* _indice_arvorebp_split(indice_arvorebp_node *no, chave_t *chave_promovida) {
    int i, j;
    int corte = (MAX_CHAVES + 1) / 2;
    chave_t chave_meio = no->chaves[corte];
    indice_arvorebp_node *novo = _indice_arvorebp_cria_node(0);

    *chave_promovida = chave_meio;

    for (i = corte + 1, j = 0; i < no->num_chaves; i++, j++) {
        novo->chaves[j] = no->chaves[i];
        novo->filhos[j] = no->filhos[i];
        
        if (novo->filhos[j]) {
            novo->filhos[j]->pai = novo;
        }

        novo->num_chaves++;
    }

    novo->filhos[j] = no->filhos[no->num_chaves];
    
    if (novo->filhos[j]) {
        novo->filhos[j]->pai = novo;
    }

    no->num_chaves = corte;
    novo->pai = no->pai;

    return novo;
}

indice_arvorebp *insere_indice_arvorebp(indice_arvorebp *raiz, chave_t chave, valor_t valor) {
    indice_arvorebp_node *folha, *nova_folha, *nova_raiz, *novo_interno, *pai, *n, *p;
    indice_arvorebp *r, *saida;

    chave_t nova_chave, promovida;
    
    if (!raiz) {
        r = _indice_arvorebp_cria_node(1);
        inserir_em_folha(r, chave, valor);
        return r;
    }

    folha = _indice_arvorebp_busca_folha(raiz, chave);
    
    inserir_em_folha(folha, chave, valor);
    
    if (folha->num_chaves < MAX_CHAVES) {
        return raiz;
    }
    
    nova_folha = indice_arvorebp_split(folha);
    nova_chave = nova_folha->chaves[0];
    
    if (folha->pai == NULL) {
        nova_raiz = _indice_arvorebp_cria_node(0);
        nova_raiz->chaves[0] = nova_chave;
        nova_raiz->filhos[0] = folha;
        nova_raiz->filhos[1] = nova_folha;
        nova_raiz->num_chaves = 1;
        folha->pai = nova_raiz;
        nova_folha->pai = nova_raiz;
        return nova_raiz;
    }
    
    pai = folha->pai;

    _indice_arvorebp_inserir(pai, nova_chave, nova_folha);
    
    n       = pai;
    saida   = raiz;
    
    while (n) {
        if (n->num_chaves < MAX_CHAVES) break;
        promovida = 0;
        novo_interno = _indice_arvorebp_split(n, &promovida);
        if (n->pai == NULL) {
            nova_raiz = _indice_arvorebp_cria_node(0);
            nova_raiz->chaves[0] = promovida;
            nova_raiz->filhos[0] = n;
            nova_raiz->filhos[1] = novo_interno;
            nova_raiz->num_chaves = 1;
            n->pai = nova_raiz;
            novo_interno->pai = nova_raiz;
            saida = nova_raiz;
            break;
        } else {
            p = n->pai;
            _indice_arvorebp_inserir(p, promovida, novo_interno);
            n = p;
        }
    }

    return saida;
}

void exclui_indice_arvorebp(indice_arvorebp *raiz) {
    int i;

    if (!raiz) {
        return;
    }

    if (!raiz->folha) {
        for (i = 0; i <= raiz->num_chaves; i++) {
            exclui_indice_arvorebp(raiz->filhos[i]);
        }
    }

    free(raiz);
}


void imprimir_arvore(indice_arvorebp *raiz) {
    if (!raiz) { printf("<vazia>\n"); return; }
    size_t cap = 256;
    indice_arvorebp_node **fila = malloc(sizeof(indice_arvorebp_node*) * cap);
    size_t ini=0, fim=0;
    fila[fim++] = raiz;
    fila[fim++] = NULL;
    while (ini < fim) {
        indice_arvorebp_node *n = fila[ini++];
        if (!n) {
            printf("\n");
            if (ini < fim) fila[fim++] = NULL;
            continue;
        }
        if (n->folha) {
            printf("[F(");
            for (int i=0;i<n->num_chaves;i++) {
                printf("%d", n->chaves[i]);
                if (i+1<n->num_chaves) printf(",");
            }
            printf(")] ");
        } else {
            printf("[I(");
            for (int i=0;i<n->num_chaves;i++) {
                printf("%d", n->chaves[i]);
                if (i+1<n->num_chaves) printf(",");
            }
            printf(")] ");
        }
        for (int i=0;i<=n->num_chaves;i++) {
            if (n->filhos[i]) {
                if (fim >= cap) {
                    cap *= 2; fila = realloc(fila, sizeof(indice_arvorebp_node*) * cap);
                }
                fila[fim++] = n->filhos[i];
            }
        }
    }
    free(fila);
}

// exemplo de utilização

// int main(void) {
//     indice_arvorebp *raiz = NULL;

//     int valores[] = {20, 5, 15, 25, 30, 2, 8, 12, 27, 26, 18, 19};
    
//     int n = sizeof(valores)/sizeof(valores[0]);
    
//     printf("Construindo Árvore B+ (ORDEM=%d, MAX_CHAVES=%d)\n", ORDEM, MAX_CHAVES);
    
//     for (int i=0;i<n;i++) {
//         raiz = indice_arvorebp_inserir(raiz, valores[i], valores[i]*10);
//         printf("Após inserir %d:\n", valores[i]);
//         imprimir_arvore(raiz);
//         printf("---------------------------\n");
//     }

//     int buscas[] = {15, 27, 100};
//     for (int i=0;i<3;i++) {
//         int valor = indice_arvorebp_buscar(raiz, buscas[i]);
//         printf("Chave %d -> valor: %d\n", buscas[i], valor);
//     }

//     indice_arvorebp_limpar(raiz);
//     return 0;
// }
