import csv
import pandas as pd
import os

# Caminho base da pasta
base_path = r"C:\Users\jmartins\repos\trabalho-algoritmos-e-estruturas-2\Arquivos"

# Garante que a pasta existe
os.makedirs(base_path, exist_ok=True)

# Caminhos dos arquivos
arquivo_origem = os.path.join(base_path, "jewelry.csv")
arquivo_tratado = os.path.join(base_path, "jewelry_tratado.csv")
arquivo_associacao = os.path.join(base_path, "associacao.csv")

# Nomes das colunas do CSV original
colunas = [
    "data", "id_pedido", "id_produto", "sku_qtd", "categoria_id",
    "alias", "marca", "preco", "usuario_id", "genero",
    "cor", "material", "joia"
]

# Lê o arquivo original
df = pd.read_csv(arquivo_origem, dtype=str, header=None, names=colunas)

# Índice da coluna "gênero do produto"
indice_genero = 9
coluna_genero = df.columns[indice_genero]

# Substitui vazios ou NaN por "u"
df[coluna_genero] = df[coluna_genero].apply(
    lambda x: "u" if pd.isna(x) or str(x).strip() == "" else x
)

# Remove a parte da hora na coluna de data (coluna 0)
coluna_data = df.columns[0]
df[coluna_data] = df[coluna_data].str.slice(0, 10)

# Remove colunas indesejadas
df = df.drop(df.columns[[3, 4, 6, 8]], axis=1)

# Salva o CSV tratado
df.to_csv(
    arquivo_tratado,
    index=False,
    quoting=csv.QUOTE_NONE,
    escapechar='\\'
)

# Lê o arquivo tratado
df = pd.read_csv(arquivo_tratado, dtype=str)

# Cria o DataFrame apenas com id_pedido e id_produto
df_associacao = df[["id_pedido", "id_produto"]]

# Salva o novo CSV de associação
df_associacao.to_csv(
    arquivo_associacao,
    index=False,
    quoting=csv.QUOTE_NONE
)

print("Arquivos gerados com sucesso em:")
print(f" - {arquivo_tratado}")
print(f" - {arquivo_associacao}")