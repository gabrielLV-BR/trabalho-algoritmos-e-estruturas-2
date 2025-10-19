#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char data[11];
    char id_pedido[20];
    char preco[10];
} Pedido;


typedef struct {
    char id_pedido[20];
    char id_produto[20];
} Associacao;

typedef struct {
    char id_produto[20];
    char alias[21];
    char preco[10];
    char genero[2];
    char cor[11];
    char material[11];
    char joia[11];
} Produto;


void lerPedidos(const char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "rb");
    if (!f) {
        perror("Erro ao abrir pedido.bin");
        return;
    }

    Pedido p;
    int count = 0;

    printf("=== PEDIDOS ===\n");
    while (fread(&p, sizeof(Pedido), 1, f)) {
        // Garante que as strings tenham terminador nulo
        p.data[10] = '\0';
        p.id_pedido[19] = '\0';
        p.preco[9] = '\0';

        printf("[%04d] Data: %s | Pedido: %s | Preco: %s\n",
               ++count, p.data, p.id_pedido, p.preco);
    }

    printf("\nTotal de pedidos lidos: %d\n", count);
    fclose(f);
}

void lerAssociacoes(const char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "rb");
    if (!f) {
        perror("Erro ao abrir associacao.bin");
        return;
    }

    Associacao a;
    int count = 0;

    printf("=== ASSOCIACOES ===\n");
    while (fread(&a, sizeof(Associacao), 1, f)) {
        a.id_pedido[19] = '\0';
        a.id_produto[19] = '\0';
        printf("[%04d] Pedido: %s | Produto: %s\n", ++count, a.id_pedido, a.id_produto);
    }

    printf("\nTotal de associações lidas: %d\n\n", count);
    fclose(f);
}


void lerProdutos(const char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "rb");
    if (!f) {
        perror("Erro ao abrir produto.bin");
        return;
    }

    Produto p;
    int count = 0;

    printf("=== PRODUTOS ===\n");
    while (fread(&p, sizeof(Produto), 1, f))
    {

        p.id_produto[19] = '\0';
        p.alias[20]     = '\0';
        p.preco[9]      = '\0';
        p.genero[1]     = '\0';
        p.cor[10]       = '\0';
        p.material[10]  = '\0';
        p.joia[10]      = '\0';

        printf("[%04d] %s | %s | %s | %s | %s | %s | %s | %s\n",++count,p.id_produto, p.alias, p.preco,p.genero, p.cor, p.material, p.joia, "");
    }

    printf("\nTotal de produtos lidos: %d\n", count);
    fclose(f);
}

hash
int main() {

    lerPedidos("pedido.bin");
    lerAssociacoes("associacao.bin");
    lerProdutos("produto.bin");



    return 0;
}
