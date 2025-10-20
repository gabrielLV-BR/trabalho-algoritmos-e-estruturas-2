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
        printf("%\n[%.3d]ID_PEDIDO:%s",i,lp->lista[i].id_pedido);
    }
}
void imprimir_lista_index_pedido(ListaIndexPedido *li)
{
    for(int i =0; i < li->qtdIndex; i ++)
    {
        printf("%\n[%.3d]ID_PEDIDO:%s ",i,li->listaIndex[i].id_pedido);
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

    int cursor = 0;
    while (fread(&p, sizeof(Pedido), 1, f)) {


        p.data[10] = '\0';
        p.id_pedido[19] = '\0';
        p.preco[9] = '\0';

        //adicionar_pedido(lp,p);
        adicionar_index_pedido(li,p,cursor);
        cursor++;
    }


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


//CRIACAO DE INDICE POR NIVEl - PEDIDO ============


int cria_indice_pedido(ListaIndexPedido *li, int *nivel,int *qtdBlocos, int tamanhoBloco)
{

    char nome[50];
    sprintf(nome, "IndicePedidoNivel-%d.bin", *nivel);
    long cursor =0;
    size_t qtdEscrita = 0;

    if(*nivel == 1)//nivel 1 insere todos os indices
    {

    FILE *arquivo = fopen(nome,"wb");
        if(arquivo == NULL)
        {
            printf("\nNao foi possivel abrir arquivo de indice");
            return -1;
        }

    qtdEscrita = fwrite(li->listaIndex,sizeof(IndexPedido),li->qtdIndex,arquivo);

        if(qtdEscrita != li->qtdIndex)
        {
        printf("\nNem todos os indices foram gravados corretamente");
        }

         fclose(arquivo);

         *qtdBlocos = 0;
         printf("\nNivel %d criado: %d indices (%d blocos)\n", *nivel, li->qtdIndex, *qtdBlocos);

         (*nivel)++;

         return li->qtdIndex;
    }
      sprintf(nome, "IndicePedidoNivel-%d.bin", ((*nivel)-1));

      FILE *arquivoAnterior = fopen(nome,"rb"); //abre o anterior
      if(arquivoAnterior == NULL)
      {
          printf("\nNão foi possivel abrir arquivo anterior para criacao do indice");
          return -1;
      }


      ListaIndexPedido temp;
      temp.listaIndex= NULL;
      temp.qtdIndex =0;

      IndexPedido indexTemp;
      Pedido pedidoTemp;

    cursor =0;
    int move = 1;
    while(1)
    {
        if(fseek(arquivoAnterior,((move*tamanhoBloco)-1)*sizeof(IndexPedido),SEEK_SET)!= 0 ) break;

        //LE O ULTIMO PEDIDO DO BLOCO
        if(fread(&indexTemp,sizeof(indexTemp),1,arquivoAnterior) != 1 ) break;

        //COPIA ID PRO PEDIDO
        strcpy(pedidoTemp.id_pedido,indexTemp.id_pedido);

        //REUTILIZA A FUNCAO DE ADICIONAR PEDIDO NA LISTA DE INDEX
        //POSICAO PASSADA É DE ONDE COMEÇA O BLOCO, LOGO É O VALOR DO CURSOR
        //RESPEITA AS REGRAS DE INDICE CLUSTERIZADO MANTENDO O VALOR FINAL+INICIO DO BLOCO
        adicionar_index_pedido(&temp,pedidoTemp,cursor);


        cursor+=tamanhoBloco;
        move++;
    }

     *qtdBlocos = move;
    //AO TERMINO DO WHILE TEMOS UMA LISTA TEMP SOMENTE COM O ARQUIVO ANTERIOR
    //PARTICIONADO ENTRE INICIO DO BLOCO E VALOR FINAL DA CHAVE

    imprimir_lista_index_pedido(&temp);
    fclose(arquivoAnterior);


    sprintf(nome, "IndicePedidoNivel-%d.bin", *nivel);

    FILE *arquivoNovo = fopen(nome,"wb");
    fwrite(temp.listaIndex,sizeof(IndexPedido),temp.qtdIndex,arquivoNovo);

    fclose(arquivoNovo);

    (*nivel)++;

    printf("\nNivel %d criado: %d indices (%d blocos)\n", *nivel - 1, temp.qtdIndex, *qtdBlocos);



return temp.qtdIndex;
}

int organizaIndice()
{
    int nivelIndice = 1;
    int qtdBlocos =0;
    int tamanhoBloco = 100;

    ListaIndexPedido li;
    li.listaIndex = NULL;
    li.qtdIndex=0;

    lerPedidos("pedido.bin",&li);
    quickSort(li.listaIndex,0,li.qtdIndex-1,sizeof(IndexPedido),comparaIndexPedido);

    int qtd = li.qtdIndex;

    while(qtd > 10)
    {
      qtd = cria_indice_pedido(&li,&nivelIndice,&qtdBlocos,tamanhoBloco);

    }
return nivelIndice-1;
}

void pesquisa_por_id_pedido(char idPedido[20],int nivel,int posicao){

    char nome[50];
    sprintf(nome, "IndicePedidoNivel-%d.bin", nivel);

    printf("[Nivel %d] Procurando no bloco (posicao %d)...\n", nivel, posicao);

    IndexPedido indexTemp;
    int cursor =0;

    if(nivel > 1)
    {
        FILE *arquivo = fopen(nome,"rb");
        if(arquivo == NULL)
        {
            printf("\nErro ao abrir arquivo");
            return;
        }

        if (fseek(arquivo,posicao * sizeof(IndexPedido), SEEK_SET) != 0)
        {
            printf("Erro ao posicionar no bloco %ld\n", cursor);
            fclose(arquivo);
            return;
        }

        while (fread(&indexTemp,sizeof(indexTemp), 1, arquivo) == 1)
        {
            if (strcmp(idPedido, indexTemp.id_pedido) <= 0) break;

            cursor++;

        }
        fclose(arquivo);
        pesquisa_por_id_pedido(idPedido,nivel-1,indexTemp.posicao);
    }
    else
    {
        //SE FOR NO NIVEL 1 (FINAL)
    FILE *arquivo = fopen(nome,"rb");
        if(arquivo == NULL)
        {
            printf("\nErro ao abrir arquivo");
            return;
        }



        if (fseek(arquivo,posicao* sizeof(IndexPedido), SEEK_SET) != 0)
        {
            printf("Erro ao posicionar no bloco %ld\n", cursor);
            fclose(arquivo);
            return;
        }

        while (fread(&indexTemp, sizeof(indexTemp), 1, arquivo) == 1)
        {
            if (strcmp(idPedido, indexTemp.id_pedido) <= 0) break;

            cursor++;

        }
        if(strcmp(idPedido,indexTemp.id_pedido) == 0 && indexTemp.excluido == 0 )
        {
            Pedido p;
            FILE *arquivoPedido = fopen("pedido.bin","rb");

            if (arquivoPedido == NULL)
            {
                printf("\nErro ao abrir pedido.bin");
                fclose(arquivo);
                return;
            }

            fseek(arquivoPedido,indexTemp.posicao*sizeof(Pedido),SEEK_SET);

            fread(&p,sizeof(p),1,arquivoPedido);

             printf("\nPedido encontrado\nID: %s\nData: %s\nPreco: %s\n",p.id_pedido, p.data, p.preco);
            fclose(arquivoPedido);
        }
        else
        {
            printf("\nNao foi possivel econtrar pedido");
        }
        fclose(arquivo);

    }

}

//=================================================

int main() {


 int nivel = organizaIndice();

    pesquisa_por_id_pedido("1924719191579951782",nivel,0);
    /* //INDEX PEDIDOS ========
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
