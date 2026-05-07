202500560090 Letícia Videira Gois
# TED — Trabalho I de Estrutura de Dados I (2026)

**Aluna:** Letícia Videira Gois  
**Número de matrícula:** 202500560090  
**Disciplina:** Estrutura de Dados I — 2026  
**Professor:** Evandro Baccarin

---

# Sobre o projeto

O projeto implementa o Trabalho I da disciplina de Estrutura de Dados I da UEL.

O programa `ted` processa arquivos `.geo` e `.qry`, manipulando formas geométricas em um plano cartesiano utilizando estruturas de dados implementadas manualmente conforme as especificações do trabalho.

O sistema gera arquivos SVG com representação visual das formas e arquivos TXT contendo o resultado textual das consultas executadas.

---

# Estruturas de dados utilizadas

- Lista duplamente encadeada dinâmica;
- Fila circular estática;
- Armazenamento genérico com `void *`;
- Modularização completa em `.h` e `.c`;
- Testes unitários utilizando Unity Framework.

---


# Como compilar

Dentro da pasta `src/`:

```bash
make
```

Para limpar arquivos objeto e executáveis:

```bash
make clean
```

---

# Como executar

## Apenas arquivo `.geo`

```bash
./ted -e "caminho da pasta do caso teste" -f "nome do arquivo geo" (com .geo) -o "caminho da pasta dos arquivos saída"
```

## Arquivo `.geo` + `.qry`

```bash
./ted -e "caminho da pasta do caso teste" -f "nome do arquivo geo"(com .geo) -q "nome ou caminho do arquivo qry que será usado nessa execução"(com .qry) -o "caminho da pasta dos arquivos saída"
```
---

# Parâmetros do programa

| Parâmetro | Obrigatório | Descrição |
|---|---|---|
| `-e path` | Não | Diretório-base de entrada |
| `-f arq.geo` | Sim | Arquivo `.geo` |
| `-q arq.qry` | Não | Arquivo de consultas |
| `-o path` | Sim | Diretório-base de saída |

---

# Arquivos de entrada

O programa utiliza dois tipos principais de arquivos:

- `.geo` → descrição das figuras geométricas;
- `.qry` → consultas e modificações sobre as figuras.

---

# Comandos do arquivo `.geo`

| Comando | Parâmetros | Descrição |
|---------|------------|-----------|
| `c` | `i x y r corb corp` | Cria círculo |
| `r` | `i x y w h corb corp` | Cria retângulo |
| `l` | `i x1 y1 x2 y2 cor` | Cria linha |
| `t` | `i x y corb corp a texto` | Cria texto |
| `ts` | `fFamily fWeight fSize` | Define estilo dos textos |

---

# Comandos do arquivo `.qry`

| Comando | Parâmetros | Descrição |
|---------|------------|-----------|
| `inp` | `p i` | Insere âncora da figura no polígono |
| `rmp` | `p` | Remove coordenada mais antiga |
| `pol` | `p i d corb corp` | Gera polígono hachurado |
| `clp` | `p` | Limpa polígono |
| `sel` | `x y w h` | Seleciona figuras |
| `dels` | — | Remove figuras selecionadas |
| `mcs` | `dx dy corb corp` | Move e recolore figuras |

---

# Algoritmo de preenchimento do polígono

O comando `pol` utiliza o algoritmo de **scanline horizontal**.

Funcionamento:

1. Cria as bordas do polígono;
2. Calcula `ymin` e `ymax`;
3. Percorre o polígono horizontalmente com passo `d`;
4. Calcula interseções com as bordas;
5. Ordena interseções;
6. Cria linhas de preenchimento entre pares consecutivos.

O algoritmo funciona corretamente para:

- polígonos convexos;
- polígonos côncavos;
- polígonos não convexos;
- polígonos auto-intersectantes.

---

# Arquivos de saída

## Quando apenas `.geo` é utilizado

```text
arquivo.svg
```

---

## Quando `.geo` e `.qry` são utilizados

```text
arquivo.svg
arquivo-consulta.svg
arquivo-consulta.txt
```

---

# Saídas SVG

Os SVGs representam:

- círculos;
- retângulos;
- linhas;
- textos;
- polígonos;
- preenchimentos;
- regiões de seleção;
- marcações auxiliares.

---

# Saídas TXT

Os arquivos TXT registram:

- comandos executados;
- figuras selecionadas;
- coordenadas inseridas/removidas;
- figuras deletadas;
- informações dos polígonos.

Formato:

```text
[*] comando executado
resultado da operação
```

---

# Testes unitários

O projeto utiliza o framework Unity para testes unitários.

Cada módulo possui seu respectivo arquivo de teste:

```text
src/test/t_<modulo>.c
```

Exemplos:

```text
t_lista.c
t_fila.c
t_poligono.c
```

---

# Como executar os testes

Atualmente os testes são compilados manualmente via GCC.

```bash
% gcc -o run_tests src/test/t_arquivo.c src/pasta/arquivo.c src/Unity/src/unity.c -I src/Unity/src -I src/pasta
```
```bash
% ./run_tests
```

---

# O que os testes verificam

Os testes cobrem:

- inserção e remoção;
- tratamento de `NULL`;
- gerenciamento de memória;
- comportamento das estruturas;
- condições de borda;
- funcionamento dos TADs;
- abertura e fechamento de arquivos;
- integridade das operações.

---
# Uso do Valgrind

O projeto foi desenvolvido considerando análise de memória com Valgrind.

Exemplo:

```bash
valgrind \
  --leak-check=full \
  --show-leak-kinds=all \
  --track-origins=yes \
  ./src/ted -e ./testes -f t001.geo -q q1.qry -o ./saida
```

---

# Compilação resumida

```bash
make            # gera src/ted
make clean      # remove .o e executáveis
```
