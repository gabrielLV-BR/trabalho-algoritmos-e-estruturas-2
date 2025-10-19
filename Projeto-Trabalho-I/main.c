#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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








//FUNCOES ARQUICO PEDIDO
void adicionar_pedido(ListaPedido *lp, Pedido novoPedido)
{
    lp->lista = (Pedido*) realloc(lp->lista,(lp->qtdPedido+1)*sizeof(Pedido));
    if (lp->lista == NULL)
    {
        printf("Nao foi possivel alocar memoria");
        return;
    }

    lp->lista[lp->qtdPedido] = novoPedido;
    lp->qtdPedido++;
}
void adicionar_index_pedido(ListaIndexPedido *li, Pedido novoPedido, int posicao)
{
        IndexPedido ip;
        strcpy(ip.id_pedido,novoPedido.id_pedido);
        ip.posicao = posicao;
        ip.excluido = 0;

        li->listaIndex = (IndexPedido*) realloc(li->listaIndex,(li->qtdIndex+1)*sizeof(IndexPedido));
    if (li->listaIndex == NULL)
    {
        printf("Nao foi possivel alocar memoria");
        return;
    }

    li->listaIndex[li->qtdIndex] = ip;
    li->qtdIndex++;
}

void imprimir_lista_pedidos(ListaPedido *lp)
{
    for(int i =0; i < lp->qtdPedido; i ++)
    {
        printf("%\nID_PEDIDO:%s",lp->lista[i].id_pedido);
    }
}
void imprimir_lista_index_pedido(ListaIndexPedido *li)
{
    for(int i =0; i < li->qtdIndex; i ++)
    {
        printf("%\nID_PEDIDO:%s ",li->listaIndex[i].id_pedido);
        printf("POSICAO:%d",li->listaIndex[i].posicao);
    }
}

void lerPedidos(const char *nome_arquivo,ListaIndexPedido *li) {
    FILE *f = fopen(nome_arquivo, "rb");
    if (!f) {
        perror("Erro ao abrir pedido.bin");
        return;
    }

    Pedido p;
    int count = 0;

    int cursor = 0;
    while (fread(&p, sizeof(Pedido), 1, f)) {


        p.data[10] = '\0';
        p.id_pedido[19] = '\0';
        p.preco[9] = '\0';

        //adicionar_pedido(lp,p);
        adicionar_index_pedido(li,p,cursor);
        cursor++;
    }

    printf("\nTotal de pedidos lidos: %d\n", count);
    fclose(f);
}
//===================================================================
void lerAssociacoes(const char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "rb");
    if (!f) {
        perror("Erro ao abrir associacao.bin");
        return;
    }

    Associacao a;
    int count = 0;

    while (fread(&a, sizeof(Associacao), 1, f)) {
        a.id_pedido[19] = '\0';
        a.id_produto[19] = '\0';

    }

    printf("\nTotal de associações lidas: %d\n\n", count);
    fclose(f);
}


//FUNCOES ARQUIVO JOIAS
void adicionar_produto(ListaProduto *lp, Produto novoProduto)
{
    lp->lista = (Produto*) realloc(lp->lista,(lp->qtdProduto+1)*sizeof(Produto));
    if (lp->lista == NULL)
    {
        printf("Nao foi possivel alocar memoria");
        return;
    }

    lp->lista[lp->qtdProduto] = novoProduto;
    lp->qtdProduto++;
}

void adicionar_index_produto(ListaIndexProduto *li, Produto novoProduto, int posicao)
{
        IndexProduto ip;

        strcpy(ip.id_produto,novoProduto.id_produto);
        ip.posicao = posicao;
        ip.excluido = 0;

        li->listaIndex = (IndexProduto*) realloc(li->listaIndex,(li->qtdIndex+1)*sizeof(IndexProduto));
    if (li->listaIndex == NULL)
    {
        printf("Nao foi possivel alocar memoria");
        return;
    }

    li->listaIndex[li->qtdIndex] = ip;
    li->qtdIndex++;
}
void imprimir_lista_index_produto(ListaIndexProduto *li)
{
    for(int i=0; i < li->qtdIndex;i++)
    {
        printf("\nID_PRODUTO:%s POSICAO:%d",li->listaIndex[i].id_produto, li->listaIndex[i].posicao);
    }
}

void imprimir_lista_produtos(ListaProduto *lp)
{
    for(int i=0; i < lp->qtdProduto;i++)
    {
        printf("\nID_PRODUTO: %s",lp->lista[i].id_produto);
    }
}


void lerProdutos(const char *nome_arquivo,ListaIndexProduto *li) {
    FILE *f = fopen(nome_arquivo, "rb");
    if (!f) {
        perror("Erro ao abrir produto.bin");
        return;
    }

    Produto p;
    int count = 0;

    int cursor = 0;
    while (fread(&p, sizeof(Produto), 1, f))
    {
        p.id_produto[19] = '\0';
        p.alias[20]      = '\0';
        p.preco[9]       = '\0';
        p.genero[1]      = '\0';
        p.cor[10]        = '\0';
        p.material[10]   = '\0';
        p.joia[10]       = '\0';

       adicionar_index_produto(li,p,cursor);
       cursor++;
    count++;
    }

    printf("\nTotal de produtos lidos: %d\n", count);
    fclose(f);
}

//===================================================================
//QUICK SORT PARA ID PRODUTO E ID PEDIDO
 typedef int (*cmp_fn)(const void*, const void*);//FUNCAO DE COMPARACAO GENERICA

 int comparaProduto(const void *a, const void *b) {
    const Produto *p1 = a;
    const Produto *p2 = b;
    return strcmp(p1->id_produto, p2->id_produto);
}
 int comparaPedido(const void *a, const void *b) {
    const Pedido *p1 = a;
    const Pedido *p2 = b;
    return strcmp(p1->id_pedido, p2->id_pedido);
}

 int comparaIndexPedido(const void *a, const void *b) {
    const IndexPedido *p1 = a;
    const IndexPedido *p2 = b;
    return strcmp(p1->id_pedido, p2->id_pedido);
}
int comparaIndexProduto(const void *a, const void *b) {
    const IndexProduto *p1 = a;
    const IndexProduto *p2 = b;
    return strcmp(p1->id_produto, p2->id_produto);
}



void *escolhePivo(void *base, int inicio, int fim, size_t size, cmp_fn cmp)
{
    char *arr = (char*) base;
    int meio = (inicio + fim) / 2;

    void *inicioPtr = arr + inicio * size;
    void *meioPtr   = arr + meio   * size;
    void *fimPtr    = arr + fim    * size;
    void *pivo;


    if (cmp(inicioPtr, meioPtr) < 0) {
        if (cmp(meioPtr, fimPtr) < 0)        pivo = meioPtr;
        else if (cmp(inicioPtr, fimPtr) < 0) pivo = fimPtr;
        else                                 pivo = inicioPtr;
    } else {
        if (cmp(inicioPtr, fimPtr) < 0)      pivo = inicioPtr;
        else if (cmp(meioPtr, fimPtr) < 0)   pivo = fimPtr;
        else                                 pivo = meioPtr;
    }

    return pivo;
}

void troca(void *a, void *b, size_t size) {
    unsigned char *pa = a, *pb = b, tmp;
    for (size_t i = 0; i < size; i++) {
        tmp = pa[i];
        pa[i] = pb[i];
        pb[i] = tmp;
    }
}

int particiona(void *base, int inicio, int fim, size_t size, cmp_fn cmp) {
    char *arr = (char*)base;

    void *pivo = escolhePivo(base,inicio,fim,size,cmp);

    int i = inicio;
    int j = fim;

    while (i <= j) {
        while (cmp(arr + i * size, pivo) < 0) i++;
        while (cmp(arr + j * size, pivo) > 0) j--;
        if (i <= j) {
            troca(arr + i * size, arr + j * size, size);
            i++; j--;
        }
    }
    return i;
}

void quickSort(void *base, int inicio, int fim, size_t size, cmp_fn cmp) {
    if (inicio < fim) {
        int index = particiona(base, inicio, fim, size, cmp);
        quickSort(base, inicio, index - 1, size, cmp);
        quickSort(base, index, fim, size, cmp);
    }
}

//====================

int main() {


    ListaIndexPedido listaIndexPed;
    listaIndexPed.listaIndex=NULL;
    listaIndexPed.qtdIndex=0;


    ListaIndexProduto listaIndexProd;
    listaIndexProd.listaIndex = NULL;
    listaIndexProd.qtdIndex =0;


    /* //PEDIDOS ========


    lerPedidos("pedido.bin",&listaIndexPed);
    quickSort(listaIndexPed.listaIndex,0,listaIndexPed.qtdIndex-1,sizeof(IndexPedido),comparaIndexPedido);
    imprimir_lista_index_pedido(&listaIndexPed);
   //===============================*/

    /* //INDEX PRODUTOS=======

    lerProdutos("produto.bin",&listaIndexProd);
    quickSort(listaIndexProd.listaIndex,0,listaIndexProd.qtdIndex-1,sizeof(IndexProduto),comparaIndexProduto);
     imprimir_lista_index_produto(&listaIndexProd);
    //=========== */


    return 0;
}
