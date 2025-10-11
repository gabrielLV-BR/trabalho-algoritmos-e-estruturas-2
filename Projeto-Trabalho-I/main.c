#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct
{
    char Data[100];
    int maxData;

    int maxPedido;


    int maxProduto;


    int maxAlias;


    int maxPreco;


    int maxGenero;


    int maxCor;


    int maxMaterial;


    int maxJoia;

}BufferLeitura;

typedef struct{

    char *data;
    char *idPedido;
    char *idProduto;
    char *alias;
    char *preco;
    char *cor;
    char *material;
    char *joia;

}Linha;

typedef struct
{
   unsigned int quantidadeLinhas;
   Linha *linhas;

}HeaderArquivo;

void inicializaBuffer( BufferLeitura *b)
{

    b->maxData=0;
    b->maxProduto =0;
    b->maxAlias=0;
    b->maxPreco=0;
    b->maxGenero=0;
    b->maxCor=0;
    b->maxMaterial=0;
    b->maxJoia=0;

}

void criaArquivosDeDados()
{
    //LEITURA DO DIRETORIO PARA CRIACAO OU NAO DOS ARQUIVOS DE DADOS
    char* caminho = "D:\\repos\\trabalho I\\Dados";

    FILE *jewelryArquivo = fopen("D://repos//trabalho I//arquivos//jewelry_tratado.csv","r");

    if(!jewelryArquivo)
    {
        printf("\nfuncao<criaArquivosDeDados>Nao foi possivel encontrar o arquivo csv jewlery_tratado.csv");
        return;
    }


    DWORD infos = GetFileAttributesA(caminho);


    if (infos == INVALID_FILE_ATTRIBUTES || !(infos & FILE_ATTRIBUTE_DIRECTORY)) {
        if (CreateDirectoryA(caminho, NULL)) {
            printf("\nCriando arquivos de dados...");
        } else {
            printf("Erro ao criar diretorio. Codigo: %lu\n", GetLastError());
        }
    }

    //ler arquivo csv



     HeaderArquivo *headerPedidos= malloc(sizeof(HeaderArquivo));// arquivo de acesso compras (pedidos).
     HeaderArquivo *headerCadastro= malloc(sizeof(HeaderArquivo));//arquivo de joias (cadastro

     BufferLeitura buffer;
     inicializaBuffer(&buffer);

     char linha[256];
     //IGNORAR O HEADER
     fgets(linha, sizeof(linha), jewelryArquivo);


      int qtdLinhas =0;

while (fgets(linha, sizeof(linha), jewelryArquivo)) {
    char *campo = strtok(linha, ",");
    qtdLinhas++;
    int campoIndex = 0;

    while (campo != NULL) {
        int tam = strlen(campo);
       switch (campoIndex) {
    case 0: buffer.maxData     = MAX(tam, buffer.maxData);     break;
    case 1: buffer.maxPedido   = MAX(tam, buffer.maxPedido);   break;
    case 2: buffer.maxProduto  = MAX(tam, buffer.maxProduto);  break;
    case 3: buffer.maxAlias    = MAX(tam, buffer.maxAlias);    break;
    case 4: buffer.maxGenero   = MAX(tam, buffer.maxGenero);   break;
    case 5: buffer.maxCor      = MAX(tam, buffer.maxCor);      break;
    case 6: buffer.maxMaterial = MAX(tam, buffer.maxMaterial); break;
    case 7: buffer.maxJoia     = MAX(tam, buffer.maxJoia);     break;
       }

        campo = strtok(NULL, ",");
        campoIndex++;
    }
}

    printf("Quantidade de linhas: %d", qtdLinhas);
    //separar em dois  arquivo de joias (cadastro), e arquivo de acesso compras (pedidos).
    //os arquivos devem estar ordenados por algum dos campos, preferencialmente chave


    //ordenar o arquivo de pedidos com id_pedido+id_produto ( chave primaria))
    //arquivo de joias, limpar repetidos
}


int main()
{
    criaArquivosDeDados();

    return 0;
}
