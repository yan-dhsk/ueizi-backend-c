# DESCRIÇÃO
Este projeto é destinado a fins educacionais, sendo a implementação em Linguagem C de um back-end para um aplicativo "colaborativo" de alertas de perigo em rodovias brasileiras. Ele é responsável por processar e consolidar dados de alertas (como "Buraco", "Acidente", "Via alagada") "enviados" por motoristas em tempo real, gerando relatórios consolidados para análise.

# ENTRADA DE DADOS
Os dados de alerta são fornecidos em arquivos CSV no formato:
idUsuario;timestamp;br;km;tipoAlerta
12;1761610320;101;10.5;A
15;1761610330;232;121.3;C

# FUNCIONALIDADES
- Processamento e Armazenamento de Dados: Carregamento de arquivos CSV com alertas e armazenamento persistente para consulta posterior.
- Consolidação de Alertas (Upvoting): Agrupamento de alertas próximos (em trechos de 500m) e contagem do número de reportes (upvotes), garantindo a cumulatividade de cargas. Lógica de Agrupamento: Alertas de X.0 a X.49 são consolidados em X.0; alertas de X.5 a X.99 são consolidados em X.5.
- Relatório por Trecho de BR: Geração de arquivo CSV (alertas_por_br.csv) com alertas consolidados e upvotes para um trecho específico da rodovia.
- Relatório de Quantidade por Tipo: Geração de arquivo CSV (alertas_br_todas.csv) com o total de alertas de cada tipo para cada BR na base.

# COMO EXECUTAR
- Clone este repositório.
- Compile o código-fonte C (ex: usando GCC ou CodeBlocks).
- Execute o programa e utilize e siga as instruções do menu.

#AUTORES
[Yan Neves](https://github.com/yan-dhsk)
[Vinicius Meneses](https://github.com/viniciusmeneses-maker)
