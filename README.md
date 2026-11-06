# 🌳 Árvore de Segmentos (*Segment Tree*) em Linguagem C

![Linguagem C](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Padrão](https://img.shields.io/badge/Padrão-C99-informational.svg)
![Compilador](https://img.shields.io/badge/GCC-Linux%20%7C%20MinGW-green.svg)
![Status](https://img.shields.io/badge/Testes-100%25%20Aprovados-brightgreen.svg)

Trabalho prático avaliativo da disciplina **Estrutura de Dados** do **Curso Superior de Tecnologia em Análise e Desenvolvimento de Sistemas (ADS)** — **Instituto Federal Baiano (Campus Guanambi)**.

* **Professor:** Reinaldo Cotrim
* **Tema:** Árvore de Segmentos (*Segment Tree* para Soma de Intervalos)
* **Desenvolvedores / Integrantes:**
  * **Hiago Souza** ([@HiagoLBP](https://github.com/HiagoLBP))
  * **Vinicius Benevides Reis** ([@Vini-Be](https://github.com/Vini-Be))

---

## 📌 1. Sobre a Árvore de Segmentos

A **Árvore de Segmentos** (*Segment Tree*) é uma estrutura de dados em árvore binária projetada para responder eficientemente a **consultas em intervalos** (*Range Queries*) e permitir **atualizações pontuais** (*Point Updates*) em tempo logarítmico.

### ⚡ Complexidades:
| Operação | Vetor Tradicional | Árvore de Segmentos |
|---|:---:|:---:|
| **Construção (*Build*)** | $O(N)$ | $O(N)$ |
| **Consulta de Soma em Intervalo $[L, R]$** | $O(N)$ | $O(\log N)$ |
| **Atualização de Elemento Pontual** | $O(1)$ | $O(\log N)$ |

### 📐 Representação Linear em Vetor:
Seguindo as orientações do trabalho, a árvore é armazenada diretamente em um **vetor** linear de tamanho $4 \times N$:
* A **raiz** é o elemento de índice `1` (armazena a soma total do vetor `[0..N-1]`).
* Para qualquer nó no índice `i`:
  * O filho esquerdo fica em `2 * i`.
  * O filho direito fica em `2 * i + 1`.
  * As folhas contêm os elementos originais do vetor.

```text
Exemplo com o vetor: [1, 3, 5, 7, 9, 11]

                        [No 1: Soma=36]  <-- Raiz (Faixa [0..5])
                         /           \
            [No 2: Soma=9]           [No 3: Soma=27]
             /          \             /           \
     [No 4: 4]     [No 5: 5]    [No 6: 16]    [No 7: 11]
      /     \                    /      \
  [No 8: 1] [No 9: 3]       [No 12: 7] [No 13: 9]
```

---

## 📂 2. Estrutura do Projeto

O projeto segue rigorosamente o padrão exigido na folha do trabalho:

```text
Trabalho-Arvore-de-Segmentos/
├── codigo/
│   ├── segtree.h        # Struct SegmentTree e protótipos de funções
│   ├── segtree.c        # Implementação das operações fundamentais da árvore
│   └── main.c           # Menu iterativo no terminal e testes automáticos
├── testes/
│   └── casos_de_teste.txt # Registro detalhado de casos de teste e instruções
├── README.txt           # Arquivo textual oficial exigido pelo IF Baiano
├── README.md            # Documentação completa formatada para o GitHub
└── .gitignore           # Ignora binários e arquivos gerados
```

---

## ⚙️ 3. Compilação e Execução

### No Linux (Terminal com GCC):
```bash
# Compilar
gcc -Wall -Wextra -std=c99 codigo/main.c codigo/segtree.c -o programa

# Executar
./programa
```

### No Windows (PowerShell / Prompt de Comando com MinGW):
```powershell
# Compilar
gcc -Wall -Wextra -std=c99 codigo/main.c codigo/segtree.c -o programa.exe

# Executar
.\programa.exe
```

---

## 🧪 4. Os 4 Testes Obrigatórios Oficiais

Ao abrir o menu principal, você pode digitar `6` para rodar os 4 testes oficiais do professor em sequência automática:

1. **Teste 1 – Construção:** Constrói a árvore a partir do vetor `[1, 3, 5, 7, 9, 11]`. Exibe a árvore e confirma que a raiz armazena a soma total **36**.
2. **Teste 2 – Consulta de Intervalo:** Consulta a soma de `[1, 3]` (`3 + 5 + 7`). Resultado obtido: **15**.
3. **Teste 3 – Atualização Pontual:** Altera o índice `2` de `5` para `10`. A árvore propaga a alteração e recalcula a nova raiz para **41**.
4. **Teste 4 – Consulta Pós-Atualização:** Repete a consulta de `[1, 3]` (`3 + 10 + 7`). Novo resultado obtido: **20**.

---

## 👥 Colaboradores
* [Hiago Souza (HiagoLBP)](https://github.com/HiagoLBP)
* [Vinicius Benevides Reis (Vini-Be)](https://github.com/Vini-Be)
