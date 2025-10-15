#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct
{
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
    char *genero;
    char *cor;
    char *material;
    char *joia;

}Linha;

typedef struct
{
   unsigned int qtdLinhas;
   Linha **linhas;

}HeaderArquivo;

void inicializaBuffer( BufferLeitura *b)
{

    b->maxData=0;
    b->maxProduto =0;
    b->maxPedido=0;
    b->maxAlias=0;
    b->maxPreco=0;
    b->maxGenero=0;
    b->maxCor=0;
    b->maxMaterial=0;
    b->maxJoia=0;

}

void alocaMaximoPorLinha(Linha *l,BufferLeitura b)
{
   l->data = malloc(sizeof(char)*b.maxData);
   l->idPedido = malloc(sizeof(char)*b.maxPedido);
   l->idProduto = malloc(sizeof(char)*b.maxProduto);
   l->alias = malloc(sizeof(char)*b.maxAlias);
   l->preco = malloc(sizeof(char)*b.maxPreco);
   l->genero = malloc(sizeof(char)*b.maxGenero);
   l->cor = malloc(sizeof(char)*b.maxCor);
   l->material= malloc(sizeof(char)*b.maxMaterial);
   l->joia = malloc(sizeof(char)*b.maxJoia);


}
void imprimeLinhas(HeaderArquivo *h) {
    printf("\n==================== DADOS LIDOS ====================\n");

    for (unsigned int i = 0; i < 20; i++) {
        Linha *l = h->linhas[i];
        printf("Linha %u:\n", i + 1);
        printf("  Data     : %s\n", l->data);
        printf("  Pedido   : %s\n", l->idPedido);
        printf("  Produto  : %s\n", l->idProduto);
        printf("  Alias    : %s\n", l->alias);
        printf("  Preço    : %s\n", l->preco);
        printf("  Gênero   : %s\n", l->genero);
        printf("  Cor      : %s\n", l->cor);
        printf("  Material : %s\n", l->material);
        printf("  Joia     : %s\n", l->joia);
        printf("-----------------------------------------------------\n");
    }
}
void criaArquivosDeDados()
{
    int dbg = 0;
    //LEITURA DO DIRETORIO PARA CRIACAO OU NAO DOS ARQUIVOS DE DADOS
    char* caminho = "C:\\Users\\jmartins\\repos\\trabalho-algoritmos-e-estruturas-2\\Dados";



    DWORD infos = GetFileAttributesA(caminho);

        FILE *jewelryArquivo = fopen("C:\\Users\\jmartins\\repos\\trabalho-algoritmos-e-estruturas-2\\Arquivos\\jewelry_tratado.csv","r");

        if(!jewelryArquivo)
            {
                printf("\nfuncao<criaArquivosDeDados>Nao foi possivel encontrar o arquivo csv jewlery_tratado.csv");
                return;
            }


    if (infos == INVALID_FILE_ATTRIBUTES || !(infos & FILE_ATTRIBUTE_DIRECTORY))
    {
        if (CreateDirectoryA(caminho, NULL))// TROCAR 1 Por CreateDirectoryA(caminho, NULL)
        {
            printf("\nCriando arquivos de dados...");


            HeaderArquivo arquivoFonteJoalheria;

            arquivoFonteJoalheria.qtdLinhas=0;

            BufferLeitura buffer;
            inicializaBuffer(&buffer);

            //ler arquivo csv
            char linha[256];
            //IGNORAR O HEADER
            fgets(linha, sizeof(linha), jewelryArquivo);
            while (fgets(linha, sizeof(linha), jewelryArquivo))
            {
                char *campo = strtok(linha, ",");

                arquivoFonteJoalheria.qtdLinhas++;

                int campoIndex = 0;

                while (campo != NULL)
                {
                    campo[strcspn(campo,"\n")]=0;//retirar o \n que vem do arquivo texto

                    int tam = strlen(campo);
                    switch (campoIndex)
                    {
                    case 0:
                     //   printf("\n%s MAX:%d|", campo, buffer.maxData);
                        buffer.maxData = MAX(tam, buffer.maxData);
                        break;

                    case 1:
                      //  printf("%s MAX:%d|", campo, buffer.maxPedido);
                        buffer.maxPedido = MAX(tam, buffer.maxPedido);
                        break;

                    case 2:
                     //   printf("%s MAX:%d|", campo, buffer.maxProduto);
                        buffer.maxProduto = MAX(tam, buffer.maxProduto);
                        break;

                    case 3:
                       // printf("%s MAX:%d|", campo, buffer.maxAlias);
                        buffer.maxAlias = MAX(tam, buffer.maxAlias);
                        break;

                    case 4:
                      //  printf("%s MAX:%d|", campo, buffer.maxGenero);
                        buffer.maxPreco = MAX(tam, buffer.maxPreco);
                        break;
                    case 5:
                      //  printf("%s MAX:%d|", campo, buffer.maxGenero);
                        buffer.maxGenero = MAX(tam, buffer.maxGenero);
                        break;

                    case 6:
                       // printf("%s MAX:%d|", campo, buffer.maxCor);
                        buffer.maxCor = MAX(tam, buffer.maxCor);
                        break;

                    case 7:
                        //printf("%s MAX:%d|", campo, buffer.maxMaterial);
                        buffer.maxMaterial = MAX(tam, buffer.maxMaterial);
                        break;

                    case 8:
                       // printf("%s MAX:%d|", campo, buffer.maxJoia);
                        buffer.maxJoia = MAX(tam, buffer.maxJoia);
                        break;

                    }
                    campoIndex++;
                    campo = strtok(NULL, ",");
                }

            }
            arquivoFonteJoalheria.linhas = malloc(sizeof(Linha*)*arquivoFonteJoalheria.qtdLinhas);

            for(int i = 0 ; i < arquivoFonteJoalheria.qtdLinhas; i++)
            {
                  arquivoFonteJoalheria.linhas[i] = malloc(sizeof(Linha));
            }

            for(int i = 0 ; i < arquivoFonteJoalheria.qtdLinhas; i++)
            {
                  alocaMaximoPorLinha(arquivoFonteJoalheria.linhas[i],buffer);
            }

            fseek(jewelryArquivo,0,SEEK_SET); //volta pro iniico

            fgets(linha, sizeof(linha), jewelryArquivo); //IGNORAR O HEADER


            int numLinha=0;
            while (fgets(linha, sizeof(linha), jewelryArquivo))
            {
                char *campo = strtok(linha, ",");
                int campoIndex = 0;

                while (campo != NULL)
                {
                    campo[strcspn(campo,"\n")]=0;//retirar o \n que vem do arquivo texto
                    switch (campoIndex)
                    {
                    case 0:
                        strcpy(arquivoFonteJoalheria.linhas[numLinha]->data,campo);
                        break;

                    case 1:
                        strcpy(arquivoFonteJoalheria.linhas[numLinha]->idPedido,campo);
                        break;

                    case 2:
                        strcpy(arquivoFonteJoalheria.linhas[numLinha]->idProduto,campo);
                        break;

                    case 3:
                         strcpy(arquivoFonteJoalheria.linhas[numLinha]->alias,campo);
                        break;

                    case 4:
                         strcpy(arquivoFonteJoalheria.linhas[numLinha]->preco,campo);
                        break;

                    case 5:
                          strcpy(arquivoFonteJoalheria.linhas[numLinha]->genero,campo);
                        break;

                    case 6:
                          strcpy(arquivoFonteJoalheria.linhas[numLinha]->cor,campo);
                        break;

                    case 7:
                         strcpy(arquivoFonteJoalheria.linhas[numLinha]->material,campo);
                        break;
                    case 8:
                         strcpy(arquivoFonteJoalheria.linhas[numLinha]->joia,campo);
                        break;
                    }
                    campoIndex++;
                    campo = strtok(NULL, ",");
                }
                numLinha++;//proxima linha
            }

            imprimeLinhas(&arquivoFonteJoalheria);

           FILE *associacaoArquivo = fopen("C:\\Users\\jmartins\\repos\\trabalho-algoritmos-e-estruturas-2\\Dados\\associacao.bin","wb");

            fwrite(&arquivoFonteJoalheria.qtdLinhas,sizeof(unsigned int),1,associacaoArquivo); //GUARDA NO ARQUIVO DE DADOS DE ASSOCIACAO QUANTAS LINHAS TEM
            fwrite(&buffer.maxProduto,sizeof(int),1,associacaoArquivo); // TAMANHO DA LINHA
            fwrite(&buffer.maxPedido,sizeof(int),1,associacaoArquivo); // TAMANHO DA LINHA

             fclose(associacaoArquivo);

            associacaoArquivo = fopen("C:\\Users\\jmartins\\repos\\trabalho-algoritmos-e-estruturas-2\\Dados\\associacao.bin","rb");
            printf("ARQUVIO DE ASSOCIACAO:\n");

            unsigned int qtdLinhas;
            int tamanho;
            int cursor = 0;

            fseek(associacaoArquivo,cursor*sizeof(unsigned int),SEEK_SET);
            fread(&qtdLinhas,sizeof(unsigned int),1,associacaoArquivo);
            printf("%d\n", qtdLinhas);

            cursor++;
            while(1)
            {
                 if(fseek(associacaoArquivo,cursor*sizeof(int),SEEK_SET)!= 0 ) break;

                 if(fread(&tamanho,sizeof(int),1,associacaoArquivo) != 1 ) break;
                 printf("%d\n", tamanho);
                 cursor++;
            }


            fclose(associacaoArquivo);
            //separar em dois  arquivo de joias (cadastro), e arquivo de acesso compras (pedidos).
            //os arquivos devem estar ordenados por algum dos campos, preferencialmente chave


            //ordenar o arquivo de pedidos com id_pedido+id_produto ( chave primaria))
            //arquivo de joias, limpar repetidos

        }

    }
    else
    {
        printf("Erro ao criar diretorio. Codigo: %lu\n", GetLastError());
    }


     fclose(jewelryArquivo);
}




int main()
{
    criaArquivosDeDados();

    return 0;
}
