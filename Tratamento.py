import csv
import pandas as pd

colunas = [
    "data", "id_pedido", "id_produto", "sku_qtd", "categoria_id",
    "alias", "marca", "preco", "usuario_id", "genero",
    "cor", "material", "joia"
]

df = pd.read_csv(".//Arquivos//jewelry.csv", dtype=str, header=None, names=colunas)


# Índice da coluna "gênero do produto"
indice_genero = 9
coluna_genero = df.columns[indice_genero]

# Substitui apenas os vazios ou NaN por "u"
df[coluna_genero] = df[coluna_genero].apply(
    lambda x: "u" if pd.isna(x) or str(x).strip() == "" else x
)

#Remove a parte da hora no campo de data (coluna 0)
coluna_data = df.columns[0]
df[coluna_data] = df[coluna_data].str.slice(0, 10)

# 2. Remove as colunas: |quantidade de SKU1|id de categoria | identificação da marca | id do usuário |
df = df.drop(df.columns[[3, 4,6,8]], axis=1)



# Salva o CSV tratado
df.to_csv(
    "jewelry_tratado.csv",
    index=False,
    quoting=csv.QUOTE_NONE,
    escapechar='\\'
)
