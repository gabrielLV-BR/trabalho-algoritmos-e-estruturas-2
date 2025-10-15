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

void lerAssociacaoBinario(const char *caminhoArquivo) {
    FILE *arquivo = fopen(caminhoArquivo, "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    unsigned int qtdLinhas;
    int maxProduto, maxPedido;

    // Lê o cabeçalho
    fread(&qtdLinhas, sizeof(unsigned int), 1, arquivo);
    fread(&maxProduto, sizeof(int), 1, arquivo);
    fread(&maxPedido, sizeof(int), 1, arquivo);

    printf("Qtd Linhas: %u\n", qtdLinhas);
    printf("Max Produto: %d\n", maxProduto);
    printf("Max Pedido: %d\n", maxPedido);
    printf("====================================\n");

    // Aloca buffers temporários para leitura dos campos
    char *idPedido = (char *)malloc(maxProduto + 1);
    char *idProduto = (char *)malloc(maxPedido + 1);

    for (unsigned int i = 0; i < 10; i++) {
        fread(idPedido, sizeof(char)*maxProduto,1, arquivo);
        fread(idProduto, sizeof(char)*maxPedido,1, arquivo);


        idPedido[maxProduto] = '\0';//COLOCA CARACTER DE FIM DE STRING
        idProduto[maxPedido] = '\0';//COLOCA CARACTER DE FIM DE STRING

        printf("Linha %u:\n", i + 1);
        printf("  Pedido : %s\n", idPedido);
        printf("  Produto: %s\n", idProduto);
    }

    // Libera memória e fecha arquivo
    free(idPedido);
    free(idProduto);
    fclose(arquivo);
}

void lerJoiaBinario(const char *caminhoArquivo) {
    FILE *arquivo = fopen(caminhoArquivo, "rb");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de joias");
        return;
    }

    // === Leitura do cabeçalho ===
    unsigned int qtdLinhas;
    int maxProduto, maxAlias, maxPreco, maxGenero, maxCor, maxMaterial, maxJoia;

    fread(&qtdLinhas, sizeof(unsigned int), 1, arquivo);
    fread(&maxProduto, sizeof(int), 1, arquivo);
    fread(&maxAlias, sizeof(int), 1, arquivo);
    fread(&maxPreco, sizeof(int), 1, arquivo);
    fread(&maxGenero, sizeof(int), 1, arquivo);
    fread(&maxCor, sizeof(int), 1, arquivo);
    fread(&maxMaterial, sizeof(int), 1, arquivo);
    fread(&maxJoia, sizeof(int), 1, arquivo);

    printf("Qtd Linhas: %u\n", qtdLinhas);
    printf("Max Produto: %d\n", maxProduto);
    printf("Max Alias: %d\n", maxAlias);
    printf("Max Preco: %d\n", maxPreco);
    printf("Max Genero: %d\n", maxGenero);
    printf("Max Cor: %d\n", maxCor);
    printf("Max Material: %d\n", maxMaterial);
    printf("Max Joia: %d\n", maxJoia);
    printf("====================================\n");

    // === Aloca buffers temporários para leitura ===
    char *idProduto = (char *)malloc(maxProduto + 1);
    char *alias = (char *)malloc(maxAlias + 1);
    char *preco = (char *)malloc(maxPreco + 1);
    char *genero = (char *)malloc(maxGenero + 1);
    char *cor = (char *)malloc(maxCor + 1);
    char *material = (char *)malloc(maxMaterial + 1);
    char *joia = (char *)malloc(maxJoia + 1);

    if (!idProduto || !alias || !preco || !genero || !cor || !material || !joia) {
        printf("Erro de alocação de memória!\n");
        fclose(arquivo);
        return;
    }


        int limite =  10;
    for (int i = 0; i < limite; i++) {
        fread(idProduto, sizeof(char) * (maxProduto + 1), 1, arquivo);
        fread(alias, sizeof(char) * (maxAlias + 1), 1, arquivo);
        fread(preco, sizeof(char) * (maxPreco + 1), 1, arquivo);
        fread(genero, sizeof(char) * (maxGenero + 1), 1, arquivo);
        fread(cor, sizeof(char) * (maxCor + 1), 1, arquivo);
        fread(material, sizeof(char) * (maxMaterial + 1), 1, arquivo);
        fread(joia, sizeof(char) * (maxJoia + 1), 1, arquivo);

        // Garante o fim de string
        idProduto[maxProduto] = '\0';
        alias[maxAlias] = '\0';
        preco[maxPreco] = '\0';
        genero[maxGenero] = '\0';
        cor[maxCor] = '\0';
        material[maxMaterial] = '\0';
        joia[maxJoia] = '\0';

        printf("Linha %u:\n", i + 1);
        printf("  Produto : %s\n", idProduto);
        printf("  Alias   : %s\n", alias);
        printf("  Preço   : %s\n", preco);
        printf("  Gênero  : %s\n", genero);
        printf("  Cor     : %s\n", cor);
        printf("  Material: %s\n", material);
        printf("  Joia    : %s\n", joia);
        printf("------------------------------------\n");
    }

    // === Libera memória e fecha o arquivo ===
    free(idProduto);
    free(alias);
    free(preco);
    free(genero);
    free(cor);
    free(material);
    free(joia);
    fclose(arquivo);
}

void criaArquivosDeDados()
{
    int dbg = 0;
    //LEITURA DO DIRETORIO PARA CRIACAO OU NAO DOS ARQUIVOS DE DADOS
    char *caminhoPasta = "C:\\Users\\jmartins\\repos\\trabalho-algoritmos-e-estruturas-2\\Dados";
    char *caminhoJewelryTratado="C:\\Users\\jmartins\\repos\\trabalho-algoritmos-e-estruturas-2\\Arquivos\\jewelry_tratado.csv";
    char *caminhoAssociacao = "C:\\Users\\jmartins\\repos\\trabalho-algoritmos-e-estruturas-2\\Dados\\associacao.bin";
    char *caminhoJoia = "C:\\Users\\jmartins\\repos\\trabalho-algoritmos-e-estruturas-2\\Dados\\joia.bin";

    DWORD infos = GetFileAttributesA(caminhoPasta);

        FILE *jewelryArquivo = fopen(caminhoJewelryTratado,"r");

        if(!jewelryArquivo)
            {
                printf("\nfuncao<criaArquivosDeDados>Nao foi possivel encontrar o arquivo csv jewlery_tratado.csv");
                return;
            }


    if (infos == INVALID_FILE_ATTRIBUTES || !(infos & FILE_ATTRIBUTE_DIRECTORY))
    {
        if (CreateDirectoryA(caminhoPasta, NULL))// TROCAR 1 Por CreateDirectoryA(caminho, NULL)
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


        //CRIANDO ARQUIVO BINARIO DE ASSOCIACAO CHAVE PEDIDO + CHAVE PRODUTO
           FILE *associacaoArquivo = fopen(caminhoAssociacao,"wb");

            fwrite(&arquivoFonteJoalheria.qtdLinhas,sizeof(unsigned int),1,associacaoArquivo); //GUARDA NO ARQUIVO DE DADOS DE ASSOCIACAO QUANTAS LINHAS TEM
            fwrite(&buffer.maxProduto,sizeof(int),1,associacaoArquivo); // TAMANHO DA LINHA
            fwrite(&buffer.maxPedido,sizeof(int),1,associacaoArquivo); // TAMANHO DA LINHA

         for(int linha = 0 ; linha < arquivoFonteJoalheria.qtdLinhas; linha++)
         {
            fwrite(arquivoFonteJoalheria.linhas[linha]->idPedido,sizeof(char)*buffer.maxPedido,1,associacaoArquivo);
            fwrite(arquivoFonteJoalheria.linhas[linha]->idProduto,sizeof(char)*buffer.maxProduto,1,associacaoArquivo);

          }
         fclose(associacaoArquivo);
        //=====================================================================================

        lerAssociacaoBinario(caminhoAssociacao);

        //CRIANDO ARQUIVO BINARIO DE JOIA
               //CRIANDO ARQUIVO BINARIO DE JOIA
           FILE *joiaArquivo = fopen(caminhoJoia,"wb");

            fwrite(&arquivoFonteJoalheria.qtdLinhas,sizeof(unsigned int),1,joiaArquivo); //GUARDA NO ARQUIVO DE DADOS DE ASSOCIACAO QUANTAS LINHAS TEM
            fwrite(&buffer.maxProduto,sizeof(int),1,joiaArquivo);
            fwrite(&buffer.maxAlias,sizeof(int),1,joiaArquivo);
            fwrite(&buffer.maxPreco,sizeof(int),1,joiaArquivo);
            fwrite(&buffer.maxGenero,sizeof(int),1,joiaArquivo);
            fwrite(&buffer.maxCor,sizeof(int),1,joiaArquivo);
            fwrite(&buffer.maxMaterial,sizeof(int),1,joiaArquivo);
            fwrite(&buffer.maxJoia,sizeof(int),1,joiaArquivo);

         for(int linha = 0 ; linha < arquivoFonteJoalheria.qtdLinhas; linha++)
         {

            fwrite(arquivoFonteJoalheria.linhas[linha]->idProduto,(sizeof(char)*buffer.maxProduto)+1,1,joiaArquivo); //(sizeof(char)buffer)+1 = +1 para o caracter de fim de string '\0'
            fwrite(arquivoFonteJoalheria.linhas[linha]->alias,(sizeof(char)*buffer.maxAlias)+1,1,joiaArquivo);
            fwrite(arquivoFonteJoalheria.linhas[linha]->preco,(sizeof(char)*buffer.maxPreco)+1,1,joiaArquivo);
            fwrite(arquivoFonteJoalheria.linhas[linha]->genero,(sizeof(char)*buffer.maxGenero)+1,1,joiaArquivo);
            fwrite(arquivoFonteJoalheria.linhas[linha]->cor,(sizeof(char)*buffer.maxCor)+1,1,joiaArquivo);
            fwrite(arquivoFonteJoalheria.linhas[linha]->material,(sizeof(char)*buffer.maxMaterial)+1,1,joiaArquivo);
            fwrite(arquivoFonteJoalheria.linhas[linha]->joia,(sizeof(char)*buffer.maxJoia)+1,1,joiaArquivo);

          }
         fclose(joiaArquivo);
      // =====================================================================================

        lerJoiaBinario(caminhoJoia);
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
