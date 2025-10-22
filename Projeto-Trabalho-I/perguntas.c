#include "perguntas.h"

#include "associacao.h"
#include <stdio.h>

void opcao_produtos_em_pedido() {
    id_pedido pedido;
    lista_produtos *produtos;
    int num_produtos = 0;

    printf("Qual pedido você deseja visualizar?\n : ");
    
    if (!scanf("%ld", &pedido)) {
        fprintf(stderr, "Ocorreu um erro ao ler o número do pedido.\n");
        return;
    }

    printf("Buscando pelo pedido %ld\n", pedido);
    produtos = produtos_associados_a_pedido(pedido);

    while (produtos) {
        num_produtos++;
        printf("%2d) %ld\n", num_produtos, produtos->id_produto);
        produtos = produtos->proximo;
    }

    printf("%d produtos no pedido.\n", num_produtos);

    printf("Buscando só por um pra ver a brisa...\n");
    printf("Pedido encontrado: %ld\n", busca_indice_arvorebp(indice_associacao, pedido));
}