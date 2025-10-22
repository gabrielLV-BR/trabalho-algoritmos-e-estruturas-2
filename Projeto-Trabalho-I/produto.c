#include "types.h"
#include "sort.h"
#include "produto.h"

void adicionar_produto(ListaProduto *lp, Produto novoProduto)
{
    lp->lista = (Produto*)realloc(lp->lista,(size_t)(lp->qtdProduto+1)*sizeof(Produto));
    if (lp->lista == NULL){ printf("Nao foi possivel alocar memoria"); return; }
    lp->lista[lp->qtdProduto] = novoProduto;
    lp->qtdProduto++;
}

void adicionar_index_produto(ListaIndexProduto *li, Produto novoProduto, int posicao)
{
    IndexProduto ip;
    strcpy(ip.id_produto, novoProduto.id_produto);
    ip.posicao = posicao; ip.qtdExtensao = 0; ip.excluido = 0; ip.elo = -1; ip.tamExtensao = 10;

    li->listaIndex = (IndexProduto*)realloc(li->listaIndex,(size_t)(li->qtdIndex+1)*sizeof(IndexProduto));
    if (!li->listaIndex){ printf("Nao foi possivel alocar memoria\n"); return; }
    li->listaIndex[li->qtdIndex] = ip; li->qtdIndex++;
}

void imprimir_lista_index_produto(ListaIndexProduto *li)
{
    for(int i=0;i<li->qtdIndex;i++)
        printf("\nID_PRODUTO:%s POSICAO:%d",li->listaIndex[i].id_produto, li->listaIndex[i].posicao);
}

void imprimir_lista_produtos(ListaProduto *lp)
{
    for(int i=0;i<lp->qtdProduto;i++) printf("\nID_PRODUTO: %s",lp->lista[i].id_produto);
}

void lerProdutos(const char *nome_arquivo, ListaIndexProduto *li)
{
    FILE *f = fopen(nome_arquivo, "rb");
    if (!f) { perror("Erro ao abrir produto.bin"); return; }

    Produto p; int cursor = 0; int count = 0;
    while (fread(&p, sizeof(Produto), 1, f) == 1) {
        p.id_produto[19]='\0'; p.alias[20]='\0'; p.preco[9]='\0';
        p.genero[1]='\0'; p.cor[10]='\0'; p.material[10]='\0'; p.joia[10]='\0';
        if (strcmp(p.id_produto, "9999999999999999999") != 0)
            adicionar_index_produto(li, p, cursor);
        cursor++; count++;
    }
    printf("\nTotal de produtos lidos: %d\n", count);
    fclose(f);
}

int cria_indice_produto(ListaIndexProduto *li, int *nivel, int *qtdBlocos, int tamanhoBloco)
{
    char nome[50]; sprintf(nome, "IndiceProdutoNivel-%d.bin", *nivel);
    long cursor = 0; size_t qtdEscrita = 0;

    if (*nivel == 1){
        FILE *arquivo = fopen(nome, "wb");
        if (!arquivo){ printf("\nNao foi possivel abrir arquivo de indice de produto"); return -1; }
        qtdEscrita = fwrite(li->listaIndex, sizeof(IndexProduto), (size_t)li->qtdIndex, arquivo);
        if (qtdEscrita != (size_t)li->qtdIndex) printf("\nNem todos os indices de produto foram gravados corretamente");
        fclose(arquivo);
        *qtdBlocos = 0;
        printf("\nNivel %d criado: %d indices de produto (%d blocos)\n", *nivel, li->qtdIndex, *qtdBlocos);
        (*nivel)++; return li->qtdIndex;
    }

    sprintf(nome, "IndiceProdutoNivel-%d.bin", (*nivel) - 1);
    FILE *arquivoAnterior = fopen(nome, "rb");
    if (!arquivoAnterior){ printf("\nNao foi possivel abrir arquivo anterior de produto para criacao do indice"); return -1; }

    ListaIndexProduto temp; temp.listaIndex = NULL; temp.qtdIndex = 0;
    IndexProduto indexTemp; Produto produtoTemp;

    cursor = 0; int move = 1;
    while (1){
        if (fseek(arquivoAnterior, ((move * tamanhoBloco) - 1) * (long)sizeof(IndexProduto), SEEK_SET) != 0) break;
        if (fread(&indexTemp, sizeof(indexTemp), 1, arquivoAnterior) != 1) break;
        strcpy(produtoTemp.id_produto, indexTemp.id_produto);
        adicionar_index_produto(&temp, produtoTemp, (int)cursor);
        cursor += tamanhoBloco; move++;
    }

    *qtdBlocos = move;
    fclose(arquivoAnterior);

    sprintf(nome, "IndiceProdutoNivel-%d.bin", *nivel);
    FILE *arquivoNovo = fopen(nome, "wb");
    if (!arquivoNovo){ printf("\nErro ao criar novo arquivo de indice de produto"); return -1; }
    fwrite(temp.listaIndex, sizeof(IndexProduto), (size_t)temp.qtdIndex, arquivoNovo);
    fclose(arquivoNovo);

    (*nivel)++;
    printf("\nNivel %d criado: %d indices de produto (%d blocos)\n", *nivel - 1, temp.qtdIndex, *qtdBlocos);
    return temp.qtdIndex;
}

int organiza_indice_produto()
{
    int nivelIndice = 1, qtdBlocos = 0, tamanhoBloco = 100;
    printf("\nCriando Arquivo de Indice de Produtos...");

    ListaIndexProduto li; li.listaIndex = NULL; li.qtdIndex = 0;
    lerProdutos("produto.bin", &li);
    qsort(li.listaIndex, (size_t)li.qtdIndex, sizeof(IndexProduto), comparaIndexProduto);

    int qtd = li.qtdIndex;
    while (qtd > 10) qtd = cria_indice_produto(&li, &nivelIndice, &qtdBlocos, tamanhoBloco);

    printf("\n[OK] Indice de produtos organizado. Nivel inicial: %d", nivelIndice - 1);
    return nivelIndice - 1;
}

int pesquisa_por_id_produto(char idProduto[20], int nivel, int *posicao)
{
    char nome[50]; sprintf(nome, "IndiceProdutoNivel-%d.bin", nivel);
    printf("\n[Nivel %d] Procurando no bloco (posicao %d)...", nivel, *posicao);

    IndexProduto indexTemp; int cursor = 0;

    if (nivel > 1){
        printf("\nENTROU NO IF nivel > 1");
        FILE *arquivo = fopen(nome, "rb");
        if (!arquivo){ printf("\nErro ao abrir arquivo"); return -2; }
        if (fseek(arquivo, (*posicao) * (long)sizeof(IndexProduto), SEEK_SET) != 0){
            printf("Erro ao posicionar no bloco %d\n", *posicao); fclose(arquivo); return -2;
        }
        while (fread(&indexTemp, sizeof(indexTemp), 1, arquivo) == 1){
            if (strcmp(idProduto, indexTemp.id_produto) <= 0) break;
            cursor++;
        }
        fclose(arquivo);
        *posicao = indexTemp.posicao;
        return pesquisa_por_id_produto(idProduto, nivel - 1, posicao);
    } else {
        printf("\nENTROU NO ELSE nivel < 1");
        FILE *arquivo = fopen(nome, "rb");
        if (!arquivo){ printf("\nErro ao abrir arquivo"); return -2; }

        int posicaoIndice;
        if (fseek(arquivo, (*posicao) * (long)sizeof(IndexProduto), SEEK_SET) != 0){
            printf("Erro ao posicionar no bloco %d\n", *posicao); fclose(arquivo); return -2;
        }

        while (fread(&indexTemp, sizeof(indexTemp), 1, arquivo) == 1){
            (*posicao)++;
            if (strcmp(idProduto, indexTemp.id_produto) < 0) break;
            cursor++;
        }

        posicaoIndice = (*posicao > 0) ? (*posicao) - 1 : 0;

        if (strcmp(idProduto, indexTemp.id_produto) == 0 && indexTemp.excluido == 0){
            printf("\nENTROU NO STRCMP ID PRODUTO INDEX.ID PRODUTO && INDEX.EXCLUIDO == 0");
            Produto p; FILE *arquivoProduto = fopen("produto.bin", "rb");
            if (!arquivoProduto){ printf("\nErro ao abrir produto.bin"); fclose(arquivo); return -2; }
            fseek(arquivoProduto, indexTemp.posicao * (long)sizeof(Produto), SEEK_SET);
            fread(&p, sizeof(p), 1, arquivoProduto);
            printf("\nProduto encontrado\nID: %s\nAlias: %s\nPreco: %s", p.id_produto, p.alias, p.preco);
            printf("\nPosicao no arquivo de dados %d\n", indexTemp.posicao);
            fclose(arquivoProduto); fclose(arquivo);
            return indexTemp.posicao;
        }
        else if (indexTemp.excluido == 1){
            printf("\nENTROU NO ELSE IF INDEX.EXCLUIDO == 1");
            Produto p; FILE *arquivoProduto = fopen("produto.bin", "rb");
            if (!arquivoProduto){ printf("\nErro ao abrir produto.bin"); fclose(arquivo); return -2; }
            fseek(arquivoProduto, indexTemp.posicao * (long)sizeof(Produto), SEEK_SET);
            fread(&p, sizeof(p), 1, arquivoProduto);
            printf("\nProduto (excluido) encontrado\nID: %s\nAlias: %s\nPreco: %s", p.id_produto, p.alias, p.preco);
            printf("\nPosicao no arquivo de dados %d\n", indexTemp.posicao);
            fclose(arquivoProduto); fclose(arquivo);
            return indexTemp.posicao;
        }
        else if (indexTemp.elo != -1){
            printf("\nTENTOU CHECAR A EXTENSAO?");
            fclose(arquivo);
            Produto p; FILE *arquivoProduto = fopen("produto.bin", "rb");
            if (!arquivoProduto){ printf("\nErro ao abrir produto.bin"); return -2; }

            int qtdLeitura = 0, maxLeitura; *posicao = indexTemp.elo; maxLeitura = indexTemp.tamExtensao;
            if (fseek(arquivoProduto, (*posicao) * (long)sizeof(Produto), SEEK_SET) != 0){
                printf("Erro ao posicionar no bloco %d\n", *posicao); fclose(arquivoProduto); return -2;
            }

            while (qtdLeitura < indexTemp.qtdExtensao && fread(&p, sizeof(Produto), 1, arquivoProduto) == 1){
                printf("\n[DEBUG] Lendo extensao pos=%d | id_produto=%s", *posicao, p.id_produto);
                if (strcmp(idProduto, p.id_produto) == 0){
                    printf("\nProduto encontrado (na extensão)\nID: %s\nAlias: %s\nPreco: %s\n", p.id_produto, p.alias, p.preco);
                    fclose(arquivoProduto);
                    return (*posicao);
                }
                qtdLeitura++; (*posicao)++;
            }
            fclose(arquivoProduto);
            printf("\nProduto não encontrado na extensão (lidos %d de %d)\n", qtdLeitura, maxLeitura);
            return -1;
        } else {
            printf("\nENTROU NO ELSE DO FIM");
            int leituraPos = (posicaoIndice > 0) ? (posicaoIndice - 1) : 0;

            fseek(arquivo, leituraPos * (long)sizeof(indexTemp), SEEK_SET);
            fread(&indexTemp, sizeof(indexTemp), 1, arquivo);

            printf("POSICAO PONTEIRO %d | LEITURA POSICAO %d", *posicao, leituraPos);
            printf(
                "\nPOSICAO NO ARQ INDICE: %d |INDICE QUE PAROU: %s | ELO %d | EXCLUIDO %d | TAM_EXTENSAO %d | POSICAO ARQ DADOS %d",
                posicaoIndice, indexTemp.id_produto, indexTemp.elo, indexTemp.excluido,
                indexTemp.qtdExtensao, indexTemp.posicao
            );

            if (strcmp(idProduto, indexTemp.id_produto) == 0 && indexTemp.excluido == 0){
                printf("\n[OK] Registro localizado diretamente no índice (posicao %d)", leituraPos);
                *posicao = leituraPos;
                fclose(arquivo);
                return indexTemp.posicao;
            }

            printf("\nCHEGAGEM DA AREA DE EXTENSAO:");

            if (indexTemp.elo != -1){
                printf("\nTENTOU CHECAR A EXTENSAO");
                fclose(arquivo);

                Produto p; FILE *arquivoProduto = fopen("produto.bin", "rb");
                if (!arquivoProduto){ printf("\nErro ao abrir produto.bin"); return -2; }

                int qtdLeitura = 0, maxLeitura; *posicao = indexTemp.elo; maxLeitura = indexTemp.tamExtensao;
                if (fseek(arquivoProduto, (*posicao) * (long)sizeof(Produto), SEEK_SET) != 0){
                    printf("Erro ao posicionar no bloco %d\n", *posicao); fclose(arquivoProduto); return -2;
                }

                while (qtdLeitura < indexTemp.qtdExtensao && fread(&p, sizeof(Produto), 1, arquivoProduto) == 1){
                    printf("\n[DEBUG] Lendo extensao pos=%d | id_produto=%s", *posicao, p.id_produto);
                    if (strcmp(idProduto, p.id_produto) == 0){
                        printf("\nProduto encontrado (na extensão)\nID: %s\nAlias: %s\nPreco: %s\n", p.id_produto, p.alias, p.preco);
                        fclose(arquivoProduto);
                        return (*posicao);
                    }
                    qtdLeitura++; (*posicao)++;
                }

                fclose(arquivoProduto);
                printf("\nProduto não encontrado na extensão (lidos %d de %d)\n", qtdLeitura, maxLeitura);
            }

            printf("\nNao foi possivel encontrar produto.");
            (*posicao) = leituraPos;
            fclose(arquivo);
            return -1;
        }
    }
}

int inserir_produto(Produto p, int nivel)
{
    int pesquisa = -1; int posicao = 0; IndexProduto indexTemp;

    printf("\n================ INSERCAO DE PRODUTO ================");
    printf("\nProduto a inserir: ID=%s | Alias=%s | Preco=%s", p.id_produto, p.alias, p.preco);

    pesquisa = pesquisa_por_id_produto(p.id_produto, nivel, &posicao);
    printf("\nResultado da pesquisa: %d | Posicao retornada: %d", pesquisa, posicao);

    if (pesquisa == -2){ printf("\n[ERRO] Falha durante a pesquisa no indice."); return -1; }
    else if (pesquisa != -1){
        printf("\n[AVISO] Produto ja inserido na posicao: %d", pesquisa);

        FILE *arquivoIndice = fopen("IndiceProdutoNivel-1.bin", "rb+");
        FILE *arquivoDados  = fopen("produto.bin", "rb+");
        if (!arquivoIndice || !arquivoDados){
            printf("\n[ERRO] Falha ao abrir arquivos.");
            if (arquivoIndice) fclose(arquivoIndice);
            if (arquivoDados)  fclose(arquivoDados);
            return -1;
        }

        fseek(arquivoIndice, posicao * (long)sizeof(IndexProduto), SEEK_SET);
        if (fread(&indexTemp, sizeof(IndexProduto), 1, arquivoIndice) != 1){
            printf("\n[ERRO] Falha ao ler indice na posicao %d.", posicao);
            fclose(arquivoIndice); fclose(arquivoDados); return -1;
        }

        if (indexTemp.excluido == 1){
            printf("\n[CASO] Reativando indice excluido...");
            if (indexTemp.elo != -1){
                printf("\n[VERIFICACAO] Checando ID na area de extensao...");
                FILE *arquivoProduto = fopen("produto.bin", "rb");
                if (!arquivoProduto){ printf("\n[ERRO] Falha ao abrir produto.bin."); fclose(arquivoIndice); fclose(arquivoDados); return -1; }

                Produto pExt; int posAtual = indexTemp.elo; int encontrado = 0;
                fseek(arquivoProduto, posAtual * (long)sizeof(Produto), SEEK_SET);
                for (int i = 0; i < indexTemp.qtdExtensao; i++){
                    if (fread(&pExt, sizeof(Produto), 1, arquivoProduto) != 1) break;
                    if (strcmp(pExt.id_produto, p.id_produto) == 0){
                        encontrado = 1;
                        printf("\n[AVISO] ID %s ja existe na extensao (pos %d).", p.id_produto, posAtual + i);
                        break;
                    }
                }
                fclose(arquivoProduto);
                if (encontrado){ fclose(arquivoIndice); fclose(arquivoDados); printf("\n[ABORTADO] Reativacao cancelada (ID duplicado)."); return 0; }
            }

            indexTemp.excluido = 0;
            strcpy(indexTemp.id_produto, p.id_produto);
            fseek(arquivoDados, indexTemp.posicao * (long)sizeof(Produto), SEEK_SET);
            fwrite(&p, sizeof(Produto), 1, arquivoDados);
            printf("\n[OK] Produto regravado na posicao de dados %d.", indexTemp.posicao);

            fseek(arquivoIndice, posicao * (long)sizeof(IndexProduto), SEEK_SET);
            fwrite(&indexTemp, sizeof(IndexProduto), 1, arquivoIndice);
            printf("\n[OK] Indice atualizado e reativado.");
        }

        fflush(arquivoDados); fflush(arquivoIndice);
        fclose(arquivoDados); fclose(arquivoIndice);
        printf("\n[FINALIZADO] Insercao concluida.\n");
        return 1;
    } else {
        printf("\n[CASO] Inserindo novo produto em posicao livre (%d)...", posicao);

        FILE *arquivoIndice = fopen("IndiceProdutoNivel-1.bin", "rb+");
        FILE *arquivoDados  = fopen("produto.bin", "rb+");
        if (!arquivoIndice || !arquivoDados){
            printf("\n[ERRO] Falha ao abrir arquivos.");
            if (arquivoIndice) fclose(arquivoIndice);
            if (arquivoDados)  fclose(arquivoDados);
            return -1;
        }

        fseek(arquivoIndice, posicao * (long)sizeof(IndexProduto), SEEK_SET);
        if (fread(&indexTemp, sizeof(IndexProduto), 1, arquivoIndice) != 1){
            printf("\n[ERRO] Falha ao ler indice na posicao %d.", posicao);
            fclose(arquivoIndice); fclose(arquivoDados); return -1;
        }

        if (indexTemp.elo != -1){
            printf("\n[CASO] Inserindo na area de extensao existente...");
            long posInsercao = (long)indexTemp.elo + indexTemp.qtdExtensao;

            if (indexTemp.qtdExtensao < indexTemp.tamExtensao){
                fseek(arquivoDados, posInsercao * (long)sizeof(Produto), SEEK_SET);
                fwrite(&p, sizeof(Produto), 1, arquivoDados);

                indexTemp.qtdExtensao++;
                fseek(arquivoIndice, posicao * (long)sizeof(IndexProduto), SEEK_SET);
                fwrite(&indexTemp, sizeof(IndexProduto), 1, arquivoIndice);

                printf("\n[OK] Produto inserido na extensao (posicao %ld).", posInsercao);
                printf("\n[OK] qtdExtensao=%d/%d.", indexTemp.qtdExtensao, indexTemp.tamExtensao);
            } else {
                printf("\n[ERRO] Extensao cheia (elo=%d, tam=%d).", indexTemp.elo, indexTemp.tamExtensao);
            }
        } else {
            printf("\n[CASO] Criando nova area de extensao...");

            Produto vazio; strcpy(vazio.id_produto, "9999999999999999999"); strcpy(vazio.alias, "VAZIO"); strcpy(vazio.preco, "0.00");

            fseek(arquivoDados, 0, SEEK_END);
            long inicioExtensao = ftell(arquivoDados) / (long)sizeof(Produto);

            int tamanhoExtensao = (indexTemp.tamExtensao > 0) ? indexTemp.tamExtensao : 10;

            for (int i = 0; i < tamanhoExtensao; i++) fwrite(&vazio, sizeof(Produto), 1, arquivoDados);

            fseek(arquivoDados, inicioExtensao * (long)sizeof(Produto), SEEK_SET);
            fwrite(&p, sizeof(Produto), 1, arquivoDados);

            indexTemp.elo = (int)inicioExtensao; indexTemp.qtdExtensao = 1; indexTemp.tamExtensao = tamanhoExtensao;
            fseek(arquivoIndice, posicao * (long)sizeof(IndexProduto), SEEK_SET);
            fwrite(&indexTemp, sizeof(IndexProduto), 1, arquivoIndice);

            printf("\n[OK] Nova extensao criada (inicio=%ld, tam=%d).", inicioExtensao, tamanhoExtensao);
            printf("\n[OK] Produto inserido e indice atualizado.");
        }

        fflush(arquivoDados); fflush(arquivoIndice);
        fclose(arquivoDados); fclose(arquivoIndice);
        printf("\n[FINALIZADO] Insercao de novo produto concluida com sucesso.\n");
        return 1;
    }
}

void excluir_produto(char id[20], int nivel)
{
    printf("\n================ EXCLUSAO DE PRODUTO ================");
    printf("\n[INFO] Produto a excluir: ID=%s", id);

    int posicao = 0;
    int pesquisa = pesquisa_por_id_produto(id, nivel, &posicao);
    if (pesquisa == -2){ printf("\n[ERRO] Nao foi possivel realizar a pesquisa pelo id\n"); return; }
    if (pesquisa == -1){ printf("\n[ERRO] Produto nao encontrado para exclusao.\n"); return; }

    char nome[50]; sprintf(nome, "IndiceProdutoNivel-%d.bin", 1);
    FILE *arquivoIndice = fopen(nome, "rb+");
    FILE *arquivoDados  = fopen("produto.bin", "rb+");
    if (!arquivoIndice || !arquivoDados){
        printf("\n[ERRO] Falha ao abrir arquivos para exclusao.\n");
        if (arquivoIndice) fclose(arquivoIndice);
        if (arquivoDados)  fclose(arquivoDados);
        return;
    }

    IndexProduto indexTemp;
    fseek(arquivoIndice, posicao * (long)sizeof(IndexProduto), SEEK_SET);
    fread(&indexTemp, sizeof(IndexProduto), 1, arquivoIndice);

    if (indexTemp.excluido == 1) {
        printf("\n[AVISO] Produto %s ja esta marcado como excluido (posicao %d).", id, posicao);
        if (indexTemp.elo != -1) {
            FILE *arquivoProdutos = fopen("produto.bin", "rb+");
            Produto pExt; int posAtual = indexTemp.elo; int encontrado = 0;
            for (int i = 0; i < indexTemp.qtdExtensao; i++) {
                fseek(arquivoProdutos, (posAtual + i) * (long)sizeof(Produto), SEEK_SET);
                fread(&pExt, sizeof(Produto), 1, arquivoProdutos);
                if (strcmp(pExt.id_produto, id) == 0) {
                    strcpy(pExt.id_produto, "9999999999999999999");
                    strcpy(pExt.alias, "VAZIO");
                    strcpy(pExt.preco, "0.00");
                    fseek(arquivoProdutos, (posAtual + i) * (long)sizeof(Produto), SEEK_SET);
                    fwrite(&pExt, sizeof(Produto), 1, arquivoProdutos);
                    fflush(arquivoProdutos);
                    printf("\n[OK] Produto ID=%s excluido da area de extensao (posicao %d).", id, posAtual + i);
                    encontrado = 1; break;
                }
            }
            fclose(arquivoProdutos);
            if (!encontrado) printf("\n[ERRO] Produto nao encontrado na area de extensao.");
        }
        printf("\n[FINALIZADO] Exclusao concluida (indice ja estava excluido).\n");
        fclose(arquivoIndice); fclose(arquivoDados); return;
    }

    if (indexTemp.excluido == 0 && strcmp(indexTemp.id_produto, id) == 0) {
        indexTemp.excluido = 1;
        fseek(arquivoIndice, posicao * (long)sizeof(IndexProduto), SEEK_SET);
        fwrite(&indexTemp, sizeof(IndexProduto), 1, arquivoIndice);
        fflush(arquivoIndice);
        printf("\n[OK] Indice marcado como excluido (posicao %d).", posicao);

        Produto p;
        fseek(arquivoDados, indexTemp.posicao * (long)sizeof(Produto), SEEK_SET);
        fread(&p, sizeof(Produto), 1, arquivoDados);
        strcpy(p.id_produto, "9999999999999999999");
        strcpy(p.alias, "VAZIO");
        strcpy(p.preco, "0.00");
        fseek(arquivoDados, indexTemp.posicao * (long)sizeof(Produto), SEEK_SET);
        fwrite(&p, sizeof(Produto), 1, arquivoDados);
        fflush(arquivoDados);
        printf("\n[OK] Registro fisico sobrescrito no arquivo de dados (posicao %d).", indexTemp.posicao);
    }
    else if (indexTemp.excluido == 0 && strcmp(indexTemp.id_produto, id) != 0) {
        printf("\n[DEBUG] Procurando ID na area de extensao...");
        if (indexTemp.elo != -1) {
            FILE *arquivoProdutos = fopen("produto.bin", "rb+");
            if (!arquivoProdutos){ printf("\n[ERRO] Falha ao abrir produto.bin"); fclose(arquivoIndice); fclose(arquivoDados); return; }
            Produto pExt; int posAtual = indexTemp.elo; int encontrado = 0;
            for (int i = 0; i < indexTemp.qtdExtensao; i++) {
                fseek(arquivoProdutos, (posAtual + i) * (long)sizeof(Produto), SEEK_SET);
                fread(&pExt, sizeof(Produto), 1, arquivoProdutos);
                if (strcmp(pExt.id_produto, id) == 0) {
                    printf("\n[DEBUG] Produto encontrado na extensao (pos=%d). Gravando exclusao...", posAtual + i);
                    strcpy(pExt.id_produto, "9999999999999999999");
                    strcpy(pExt.alias, "VAZIO");
                    strcpy(pExt.preco, "0.00");
                    fseek(arquivoProdutos, (posAtual + i) * (long)sizeof(Produto), SEEK_SET);
                    fwrite(&pExt, sizeof(Produto), 1, arquivoProdutos);
                    fflush(arquivoProdutos);
                    printf("\n[OK] Produto ID=%s excluido na posicao %d.", id, posAtual + i);
                    fseek(arquivoProdutos, (posAtual + i) * (long)sizeof(Produto), SEEK_SET);
                    fread(&pExt, sizeof(Produto), 1, arquivoProdutos);
                    printf("\n[DEBUG] Pos %d agora contem ID=%s", posAtual + i, pExt.id_produto);
                    encontrado = 1; break;
                }
            }
            fclose(arquivoProdutos);

            if (encontrado) {
                fseek(arquivoIndice, posicao * (long)sizeof(IndexProduto), SEEK_SET);
                fwrite(&indexTemp, sizeof(IndexProduto), 1, arquivoIndice);
                fflush(arquivoIndice);
                printf("\n[OK] Indice principal atualizado apos exclusao na extensao.");
            } else {
                printf("\n[ERRO] Produto nao encontrado na area de extensao.");
            }
        }

        if (pesquisa >= indexTemp.elo && indexTemp.elo != -1) {
            printf("\n[INFO] Exclusao de produto localizado na area de extensao (posicao %d)", pesquisa);
            FILE *arquivoProdutos = fopen("produto.bin", "rb+");
            if (!arquivoProdutos){ printf("\n[ERRO] Falha ao abrir produto.bin para sobrescrever."); fclose(arquivoIndice); fclose(arquivoDados); return; }
            Produto pExt;
            fseek(arquivoProdutos, pesquisa * (long)sizeof(Produto), SEEK_SET);
            fread(&pExt, sizeof(Produto), 1, arquivoProdutos);
            printf("\n[DEBUG] Antes da exclusao: ID=%s | Alias=%s | Preco=%s", pExt.id_produto, pExt.alias, pExt.preco);
            strcpy(pExt.id_produto, "9999999999999999999");
            strcpy(pExt.alias, "VAZIO");
            strcpy(pExt.preco, "0.00");
            fseek(arquivoProdutos, pesquisa * (long)sizeof(Produto), SEEK_SET);
            fwrite(&pExt, sizeof(Produto), 1, arquivoProdutos);
            fflush(arquivoProdutos);
            printf("\n[OK] Produto sobrescrito em posicao %d com marcacao de exclusao.", pesquisa);
            fclose(arquivoProdutos);
            fflush(arquivoIndice); fflush(arquivoDados);
            fclose(arquivoIndice); fclose(arquivoDados);
            printf("\n[FINALIZADO] Exclusao de produto na area de extensao concluida com sucesso.\n");
            return;
        }
    }

    fflush(arquivoIndice); fflush(arquivoDados);
    fclose(arquivoIndice); fclose(arquivoDados);
    printf("\n[FINALIZADO] Exclusao concluida com sucesso.\n");
}
