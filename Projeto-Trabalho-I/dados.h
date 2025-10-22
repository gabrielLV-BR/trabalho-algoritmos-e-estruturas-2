#if !defined(__dados_h__)
#define __dados_h__

typedef unsigned long id_pedido;
typedef unsigned long id_produto;

typedef struct {
    char data[11];
    char id_pedido[20];
    char preco[10];
} Pedido;

typedef struct
{
    char id_pedido[20];
    int posicao;
    int excluido;

}IndexPedido;

typedef struct
{
    IndexPedido *listaIndex;
    int qtdIndex;

}ListaIndexPedido;

typedef struct{
    Pedido *lista;
    int qtdPedido;
}ListaPedido;

typedef struct{
    int posicaoInicio;

}ArquivoIndice;

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

typedef struct{
    Produto *lista;
    int qtdProduto;
}ListaProduto;

typedef struct
{
    char id_produto[20];
    int posicao;
    int excluido;

}IndexProduto;

typedef struct
{
    IndexProduto *listaIndex;
    int qtdIndex;

}ListaIndexProduto;

#endif // __dados_h__
