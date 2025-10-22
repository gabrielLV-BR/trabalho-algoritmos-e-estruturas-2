#include "menuTeste.h"
void menuTeste(){

    int nivelPedido = 0, nivelProduto = 0;
    int opPrincipal = 1, opSecundario = 1;
    char idPesquisa[20];
    Pedido p;
    Produto prod;
    int posicao = 0;

    nivelPedido = organiza_indice_pedido();
    nivelProduto = organiza_indice_produto();

    while (opPrincipal != 0)
    {
        printf("\n=========================================");
        printf("\n\tMENU PRINCIPAL");
        printf("\n=========================================");
        printf("\n1 - Gerenciar Pedidos");
        printf("\n2 - Gerenciar Produtos");
        printf("\n0 - Sair");
        printf("\n-----------------------------------------");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opPrincipal);
        scanf("%*c");

        switch (opPrincipal)
        {
        case 1:
            opSecundario = 1;
            while (opSecundario != 0)
            {
                printf("\n\n======= MENU DE PEDIDOS =======");
                printf("\n1 - Inserir Pedido");
                printf("\n2 - Excluir Pedido");
                printf("\n3 - Pesquisar Pedido");
                printf("\n0 - Voltar ao menu principal");
                printf("\n-------------------------------");
                printf("\nEscolha: ");
                scanf("%d", &opSecundario);
                scanf("%*c");

                switch (opSecundario)
                {
                case 1:
                    printf("\nDigite o ID do pedido: ");
                    scanf("%19s", p.id_pedido);
                    printf("Digite a data (AAAA-MM-DD): ");
                    scanf("%10s", p.data);
                    printf("Digite o preco: ");
                    scanf("%9s", p.preco);
                    printf("\nResumo do pedido digitado:");
                    printf("\nID: %s\nData: %s\nPreco: %s\n", p.id_pedido, p.data, p.preco);
                    inserir_pedido(p, nivelPedido);
                    break;

                case 2:
                    printf("\nDigite o ID do pedido a excluir: ");
                    scanf("%19s", idPesquisa);
                    excluir_pedido(idPesquisa, nivelPedido);
                    break;

                case 3:
                    posicao = 0;
                    printf("\nDigite o ID do pedido a pesquisar: ");
                    scanf("%19s", idPesquisa);
                    printf("\n[INFO] Pesquisando pedido ID=%s...\n", idPesquisa);
                    {
                        int resultado = pesquisa_por_id_pedido(idPesquisa, nivelPedido, &posicao);
                        if (resultado >= 0)      printf("\n[OK] Pedido encontrado na posicao %d.\n", resultado);
                        else if (resultado == -1) printf("\n[ERRO] Pedido nao encontrado.\n");
                        else                      printf("\n[ERRO] Falha na pesquisa.\n");
                    }
                    break;

                case 0: printf("\nRetornando ao menu principal...\n"); break;
                default: printf("\nOpcao invalida.\n");
                }
            }
            break;

        case 2:
            opSecundario = 1;
            while (opSecundario != 0)
            {
                printf("\n\n======= MENU DE PRODUTOS =======");
                printf("\n1 - Inserir Produto");
                printf("\n2 - Excluir Produto");
                printf("\n3 - Pesquisar Produto");
                printf("\n0 - Voltar ao menu principal");
                printf("\n-------------------------------");
                printf("\nEscolha: ");
                scanf("%d", &opSecundario);
                scanf("%*c");

                switch (opSecundario)
                {
                case 1:
                    printf("\nDigite o ID do produto: ");
                    scanf("%19s", prod.id_produto);
                    printf("Digite o alias (nome curto): ");
                    scanf("%19s", prod.alias);
                    printf("Digite o preco: ");
                    scanf("%9s", prod.preco);
                    printf("\nResumo do produto digitado:");
                    printf("\nID: %s\nAlias: %s\nPreco: %s\n", prod.id_produto, prod.alias, prod.preco);
                    inserir_produto(prod, nivelProduto);
                    break;

                case 2:
                    printf("\nDigite o ID do produto a excluir: ");
                    scanf("%19s", idPesquisa);
                    excluir_produto(idPesquisa, nivelProduto);
                    break;

                case 3:
                    posicao = 0;
                    printf("\nDigite o ID do produto a pesquisar: ");
                    scanf("%19s", idPesquisa);
                    printf("\n[INFO] Pesquisando produto ID=%s...\n", idPesquisa);
                    {
                        int resultado = pesquisa_por_id_produto(idPesquisa, nivelProduto, &posicao);
                        if (resultado >= 0)       printf("\n[OK] Produto encontrado na posicao %d.\n", resultado);
                        else if (resultado == -1) printf("\n[ERRO] Produto nao encontrado.\n");
                        else                       printf("\n[ERRO] Falha na pesquisa.\n");
                    }
                    break;

                case 0: printf("\nRetornando ao menu principal...\n"); break;
                default: printf("\nOpcao invalida.\n");
                }
            }
            break;

        case 0: printf("\nEncerrando o programa...\n"); break;
        default: printf("\nOpcao invalida.\n");
        }
    }
    return;
}
