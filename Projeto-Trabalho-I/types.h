#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char data[11];
    char id_pedido[20];
    char preco[10];
} Pedido;

typedef struct {
    char id_pedido[20];
    int  posicao;
    int  excluido;
    int  elo;
    int  qtdExtensao;
    int  tamExtensao;
} IndexPedido;

typedef struct {
    IndexPedido *listaIndex;
    int qtdIndex;
} ListaIndexPedido;

typedef struct{
    Pedido *lista;
    int qtdPedido;
} ListaPedido;

typedef struct{
    int posicaoInicio;
} ArquivoIndice;

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
} ListaProduto;

typedef struct {
    char id_produto[20];
    int  posicao;
    int  excluido;
    int  elo;
    int  qtdExtensao;
    int  tamExtensao;
} IndexProduto;

typedef struct {
    IndexProduto *listaIndex;
    int qtdIndex;
} ListaIndexProduto;



#endif // TYPES_H_INCLUDED
