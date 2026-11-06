#ifndef SEGTREE_H
#define SEGTREE_H

/*
 * ============================================================================
 * TRABALHO AVALIATIVO: ESTRUTURAS DE ARVORES
 * Instituto Federal Baiano - Campus Guanambi
 * Curso Superior de Tecnologia em Analise e Desenvolvimento de Sistemas (ADS)
 * Disciplina: Estrutura de Dados
 * Professor: Reinaldo Cotrim
 * 
 * TEMA: Arvore de Segmentos (Segment Tree para Soma de Intervalos)
 * ============================================================================
 * 
 * Descricao:
 * Uma Arvore de Segmentos e uma estrutura de dados baseada em arvore binaria
 * perfeitamente balanceada, implementada sobre um vetor (array linear).
 * Ela permite consultar somas em intervalos [L, R] e atualizar valores
 * individuais em tempo O(log N).
 * 
 * Representacao no vetor:
 * - O no raiz fica no indice 1 (representando a soma de todo o vetor [0..N-1]).
 * - O filho esquerdo de um no 'i' fica no indice: 2 * i.
 * - O filho direito de um no 'i' fica no indice: 2 * i + 1.
 * - O tamanho maximo necessario para o vetor da arvore e 4 * N.
 * ============================================================================
 */

/* Estrutura que representa a Arvore de Segmentos */
typedef struct {
    int *vetorOriginal; /* Vetor contendo os valores originais informados */
    int *arvore;        /* Vetor que armazena os nós da Arvore de Segmentos */
    int tamanho;        /* Quantidade de elementos do vetor original (N) */
    int capacidade;     /* Tamanho alocado para o vetor da arvore (4 * N) */
} SegmentTree;

/* Funcoes principais do ciclo de vida da estrutura */
int inicializarArvore(SegmentTree *st, int n);
void liberarArvore(SegmentTree *st);
int estaVazia(SegmentTree *st);

/* Operacoes fundamentais exigidas no trabalho */
void construirArvore(SegmentTree *st, int valores[], int n);
int consultarSoma(SegmentTree *st, int L, int R);
int atualizarElemento(SegmentTree *st, int indice, int novoValor);

/* Funcoes de exibicao e informacao */
int obterValorRaiz(SegmentTree *st);
void exibirVetorOriginal(SegmentTree *st);
void exibirEstruturaArvore(SegmentTree *st);
void exibirDetalhesNos(SegmentTree *st);

#endif /* SEGTREE_H */
