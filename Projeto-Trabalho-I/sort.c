#include "sort.h"

int comparaProduto(const void *a, const void *b) {
    const Produto *p1 = (const Produto*)a;
    const Produto *p2 = (const Produto*)b;
    return strcmp(p1->id_produto, p2->id_produto);
}
int comparaPedido(const void *a, const void *b) {
    const Pedido *p1 = (const Pedido*)a;
    const Pedido *p2 = (const Pedido*)b;
    return strcmp(p1->id_pedido, p2->id_pedido);
}
int comparaIndexPedido(const void *a, const void *b) {
    const IndexPedido *p1 = (const IndexPedido*)a;
    const IndexPedido *p2 = (const IndexPedido*)b;
    return strcmp(p1->id_pedido, p2->id_pedido);
}
int comparaIndexProduto(const void *a, const void *b) {
    const IndexProduto *p1 = (const IndexProduto*)a;
    const IndexProduto *p2 = (const IndexProduto*)b;
    return strcmp(p1->id_produto, p2->id_produto);
}
