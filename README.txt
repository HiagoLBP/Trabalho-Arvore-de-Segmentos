================================================================================
TRABALHO AVALIATIVO: ESTRUTURAS DE ARVORES
Instituto Federal de Educacao, Ciencia e Tecnologia Baiano - Campus Guanambi
Curso Superior de Tecnologia em Analise e Desenvolvimento de Sistemas (ADS)
Disciplina: Estrutura de Dados
Professor: Reinaldo Cotrim
================================================================================

1. IDENTIFICACAO DO TEMA E EQUIPE
--------------------------------------------------------------------------------
Tema: Arvore de Segmentos (Segment Tree para Soma de Intervalos)
Integrantes:
  - Hiago Souza
  - Vinicius Benevides Reis

2. DESCRICAO DO PROGRAMA
--------------------------------------------------------------------------------
O programa implementa a estrutura de dados Arvore de Segmentos (Segment Tree) em
linguagem C, utilizando representacao linear sobre vetor (array) de tamanho 4 * N,
conforme definido na proposta aprovada.

Principais funcionalidades implementadas:
- Construcao recursiva da arvore a partir de um vetor original de tamanho N em O(N).
- Consulta de soma em qualquer intervalo [L, R] informado pelo usuario em O(log N).
- Atualizacao pontual de um elemento no indice 'i', propagando automaticamente as
  novas somas pelos nós ancestrais ate a raiz em O(log N).
- Exibicao completa da representacao em vetor, detalhamento hierarquico dos nós e
  destaque para o valor da raiz (soma total).
- Menu interativo no terminal com opcao de execucao automatica dos 4 testes
  obrigatorios especificados no trabalho.
- Gerenciamento rigoroso de memoria (alocacao dinamica com malloc/calloc e liberacao
  completa com free).

3. ESTRUTURA DOS ARQUIVOS
--------------------------------------------------------------------------------
EquipeXX_SegmentTree/
├── codigo/
│   ├── segtree.h        -> Definicao da struct SegmentTree e prototipos das funcoes
│   ├── segtree.c        -> Implementacao das operacoes da Arvore de Segmentos
│   └── main.c           -> Interface de menu no terminal e execucao de testes
├── testes/
│   └── casos_de_teste.txt -> Casos de teste com entradas, saidas e reproducao
└── README.txt           -> Este arquivo de instrucoes e identificacao

4. INSTRUCOES DE COMPILACAO NO LINUX COM GCC
--------------------------------------------------------------------------------
Abra o terminal na pasta raiz do projeto (onde se encontra este README.txt) e execute:

   gcc -Wall -Wextra -std=c99 codigo/main.c codigo/segtree.c -o programa

Flags utilizadas:
-Wall   : Ativa avisos sobre possiveis construcoes problematicas no codigo.
-Wextra : Ativa avisos adicionais para garantir padrao rigoroso de qualidade.
-std=c99: Utiliza o padrao C99 da linguagem C.
-o      : Define o nome do executavel de saida ('programa').

5. MODO DE EXECUCAO NO LINUX
--------------------------------------------------------------------------------
Apos a compilacao com sucesso, execute o comando:

   ./programa

No Windows (usando MinGW / GCC no PowerShell ou CMD):
   gcc -Wall -Wextra -std=c99 codigo/main.c codigo/segtree.c -o programa.exe
   .\programa.exe

6. DEMONSTRACAO DOS TESTES OBRIGATORIOS
--------------------------------------------------------------------------------
Ao iniciar o programa, basta digitar o numero 6 no menu principal para executar a
demonstracao automatica dos 4 testes oficiais exigidos pelo professor:
- Teste 1: Vetor [1, 3, 5, 7, 9, 11] -> Constroi a arvore e comprova Raiz = 36.
- Teste 2: Consulta de intervalo [1, 3] -> Comprova soma = 15 (3 + 5 + 7).
- Teste 3: Atualiza indice 2 para 10 -> Comprova propagacao e Nova Raiz = 41.
- Teste 4: Consulta de intervalo [1, 3] apos atualizacao -> Comprova soma = 20.
================================================================================
