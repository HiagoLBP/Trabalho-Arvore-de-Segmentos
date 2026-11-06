#include <stdio.h>
#include <stdlib.h>
#include "segtree.h"

/*
 * ============================================================================
 * FUNCOES AUXILIARES PRIVADAS (RECURSIVAS)
 * ============================================================================
 */

/*
 * construirRecursivo:
 * Percorre recursivamente a arvore dividindo o intervalo ao meio ate chegar
 * nas folhas (inicio == fim). No retorno da recursao, calcula a soma dos filhos.
 * 
 * Parametros:
 *   - st: ponteiro para a estrutura SegmentTree
 *   - no: indice do no atual no vetor da arvore (a raiz comeca em 1)
 *   - inicio: indice inicial do segmento correspondente no vetor original
 *   - fim: indice final do segmento correspondente no vetor original
 */
static void construirRecursivo(SegmentTree *st, int no, int inicio, int fim) {
    /* Caso Base: o segmento possui apenas um elemento (eh uma folha da arvore) */
    if (inicio == fim) {
        st->arvore[no] = st->vetorOriginal[inicio];
        return;
    }

    /* Ponto medio para dividir o segmento em duas metades */
    int meio = inicio + (fim - inicio) / 2;
    int filhoEsquerdo = 2 * no;
    int filhoDireito = 2 * no + 1;

    /* Constroi recursivamente a subarvore esquerda e a subarvore direita */
    construirRecursivo(st, filhoEsquerdo, inicio, meio);
    construirRecursivo(st, filhoDireito, meio + 1, fim);

    /* O valor do no pai eh a soma dos valores de seus dois filhos */
    st->arvore[no] = st->arvore[filhoEsquerdo] + st->arvore[filhoDireito];
}

/*
 * consultarSomaRecursivo:
 * Consulta a soma dos elementos no intervalo [L, R] de forma eficiente em O(log N).
 * 
 * Tres casos possiveis:
 * 1. O segmento atual esta totalmente fora do intervalo de consulta: retorna 0.
 * 2. O segmento atual esta totalmente contido no intervalo de consulta: retorna o valor do nó.
 * 3. O segmento atual se sobrepoe parcialmente: consulta ambos os filhos e soma os resultados.
 */
static int consultarSomaRecursivo(SegmentTree *st, int no, int inicio, int fim, int L, int R) {
    /* Caso 1: Fora do intervalo consultado */
    if (R < inicio || L > fim) {
        return 0;
    }

    /* Caso 2: Totalmente contido no intervalo consultado */
    if (L <= inicio && fim <= R) {
        return st->arvore[no];
    }

    /* Caso 3: Sobreposicao parcial (divide a busca nos filhos) */
    int meio = inicio + (fim - inicio) / 2;
    int filhoEsquerdo = 2 * no;
    int filhoDireito = 2 * no + 1;

    int somaEsquerda = consultarSomaRecursivo(st, filhoEsquerdo, inicio, meio, L, R);
    int somaDireita = consultarSomaRecursivo(st, filhoDireito, meio + 1, fim, L, R);

    return somaEsquerda + somaDireita;
}

/*
 * atualizarRecursivo:
 * Atualiza o valor do elemento no 'indice' e propaga o novo calculo
 * de soma recursivamente de baixo para cima ate a raiz.
 */
static void atualizarRecursivo(SegmentTree *st, int no, int inicio, int fim, int indice, int novoValor) {
    /* Caso Base: alcancou a folha referente ao indice a ser modificado */
    if (inicio == fim) {
        st->vetorOriginal[indice] = novoValor;
        st->arvore[no] = novoValor;
        return;
    }

    int meio = inicio + (fim - inicio) / 2;
    int filhoEsquerdo = 2 * no;
    int filhoDireito = 2 * no + 1;

    /* Se o indice procurado esta a esquerda, desce para o filho esquerdo */
    if (indice <= meio) {
        atualizarRecursivo(st, filhoEsquerdo, inicio, meio, indice, novoValor);
    } else {
        /* Caso contrario, desce para o filho direito */
        atualizarRecursivo(st, filhoDireito, meio + 1, fim, indice, novoValor);
    }

    /* Apos atualizar o filho, recalcula o valor do nó pai */
    st->arvore[no] = st->arvore[filhoEsquerdo] + st->arvore[filhoDireito];
}

/*
 * exibirNosRecursivo:
 * Percorre a arvore em pré-ordem para exibir detalhadamente cada nó,
 * a faixa de indices [inicio..fim] que ele cobre e o seu valor calculado.
 */
static void exibirNosRecursivo(SegmentTree *st, int no, int inicio, int fim, int nivel) {
    if (inicio > fim) {
        return;
    }

    /* Indentacao visual para representar os niveis da arvore */
    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }

    if (inicio == fim) {
        printf("|-- [No %2d] Folha [indice %d] = %d\n", no, inicio, st->arvore[no]);
        return;
    }

    printf("|-- [No %2d] Faixa [%d..%d] (Soma = %d)\n", no, inicio, fim, st->arvore[no]);

    int meio = inicio + (fim - inicio) / 2;
    exibirNosRecursivo(st, 2 * no, inicio, meio, nivel + 1);
    exibirNosRecursivo(st, 2 * no + 1, meio + 1, fim, nivel + 1);
}

/*
 * ============================================================================
 * FUNCOES PUBLICAS DA BIBLIOTECA
 * ============================================================================
 */

/*
 * inicializarArvore:
 * Aloca a memoria necessaria para o vetor original e para a arvore de segmentos.
 * Retorna 1 em caso de sucesso ou 0 em caso de erro.
 */
int inicializarArvore(SegmentTree *st, int n) {
    if (st == NULL || n <= 0) {
        return 0;
    }

    /* Se ja houver memoria alocada anteriormente, libera antes de realocar */
    liberarArvore(st);

    st->tamanho = n;
    st->capacidade = 4 * n;

    st->vetorOriginal = (int *)malloc(n * sizeof(int));
    if (st->vetorOriginal == NULL) {
        printf("\n  [ERRO] Falha ao alocar memoria para o vetor original!\n");
        return 0;
    }

    st->arvore = (int *)calloc(st->capacidade, sizeof(int));
    if (st->arvore == NULL) {
        printf("\n  [ERRO] Falha ao alocar memoria para a Arvore de Segmentos!\n");
        free(st->vetorOriginal);
        st->vetorOriginal = NULL;
        return 0;
    }

    return 1;
}

/*
 * liberarArvore:
 * Libera toda a memoria alocada dinamicamente e redefine os ponteiros para NULL.
 */
void liberarArvore(SegmentTree *st) {
    if (st == NULL) {
        return;
    }

    if (st->vetorOriginal != NULL) {
        free(st->vetorOriginal);
        st->vetorOriginal = NULL;
    }

    if (st->arvore != NULL) {
        free(st->arvore);
        st->arvore = NULL;
    }

    st->tamanho = 0;
    st->capacidade = 0;
}

/*
 * estaVazia:
 * Verifica se a arvore ja foi construida ou se esta vazia/nao inicializada.
 */
int estaVazia(SegmentTree *st) {
    return (st == NULL || st->arvore == NULL || st->tamanho <= 0);
}

/*
 * construirArvore:
 * Copia os valores para o vetor original e dispara a construcao recursiva.
 */
void construirArvore(SegmentTree *st, int valores[], int n) {
    if (!inicializarArvore(st, n)) {
        return;
    }

    for (int i = 0; i < n; i++) {
        st->vetorOriginal[i] = valores[i];
    }

    /* O no raiz eh o indice 1, cobrindo o intervalo de 0 ate n - 1 */
    construirRecursivo(st, 1, 0, n - 1);
}

/*
 * consultarSoma:
 * Valida os limites do intervalo informado pelo usuario e chama a funcao recursiva.
 */
int consultarSoma(SegmentTree *st, int L, int R) {
    if (estaVazia(st)) {
        printf("\n  [AVISO] A arvore esta vazia! Construa a arvore primeiro.\n");
        return 0;
    }

    /* Validacao dos limites do intervalo */
    if (L < 0 || R >= st->tamanho || L > R) {
        printf("\n  [ERRO] Intervalo [%d, %d] invalido! Os limites permitidos sao [0, %d].\n",
               L, R, st->tamanho - 1);
        return 0;
    }

    return consultarSomaRecursivo(st, 1, 0, st->tamanho - 1, L, R);
}

/*
 * atualizarElemento:
 * Valida o indice e aplica a atualizacao pontual propagando ate a raiz.
 */
int atualizarElemento(SegmentTree *st, int indice, int novoValor) {
    if (estaVazia(st)) {
        printf("\n  [AVISO] A arvore esta vazia! Construa a arvore primeiro.\n");
        return 0;
    }

    if (indice < 0 || indice >= st->tamanho) {
        printf("\n  [ERRO] Indice %d fora dos limites validos [0, %d]!\n", indice, st->tamanho - 1);
        return 0;
    }

    int valorAntigo = st->vetorOriginal[indice];
    atualizarRecursivo(st, 1, 0, st->tamanho - 1, indice, novoValor);

    printf("\n  [OK] Indice [%d] atualizado com sucesso: %d -> %d\n", indice, valorAntigo, novoValor);
    printf("  [PROPAGACAO] A alteracao foi propagada para os nos pais ate a raiz (Nova Raiz = %d).\n",
           obterValorRaiz(st));
    return 1;
}

/*
 * obterValorRaiz:
 * Retorna o valor contido no no 1 (raiz), que representa a soma de todos os elementos.
 */
int obterValorRaiz(SegmentTree *st) {
    if (estaVazia(st)) {
        return 0;
    }
    return st->arvore[1];
}

/*
 * exibirVetorOriginal:
 * Imprime o vetor de dados original informado pelo usuario.
 */
void exibirVetorOriginal(SegmentTree *st) {
    if (estaVazia(st)) {
        printf("  [Vetor Original]: (vazio)\n");
        return;
    }

    printf("  [Vetor Original] (Tamanho N = %d):\n  ", st->tamanho);
    for (int i = 0; i < st->tamanho; i++) {
        printf("[%d]: %-3d  ", i, st->vetorOriginal[i]);
    }
    printf("\n");
}

/*
 * exibirEstruturaArvore:
 * Exibe o vetor interno que armazena os nós da Segment Tree e destaca a raiz.
 */
void exibirEstruturaArvore(SegmentTree *st) {
    if (estaVazia(st)) {
        printf("\n  [AVISO] A arvore esta vazia! Nada para exibir.\n");
        return;
    }

    printf("\n  ===============================================================\n");
    printf("                  ESTADO DA ARVORE DE SEGMENTOS\n");
    printf("  ===============================================================\n");
    exibirVetorOriginal(st);
    printf("\n  [RAIZ DA ESTRUTURA]: No 1 = %d (Soma Total do Vetor)\n", obterValorRaiz(st));
    printf("  [REPRESENTACAO EM VETOR DA ARVORE] (Indices ocupados no array):\n  ");

    int nosExibidos = 0;
    for (int i = 1; i < st->capacidade; i++) {
        if (st->arvore[i] != 0 || i == 1) {
            printf("[No %2d]=%-3d ", i, st->arvore[i]);
            nosExibidos++;
            if (nosExibidos % 6 == 0) {
                printf("\n  ");
            }
        }
    }
    printf("\n  ===============================================================\n");
}

/*
 * exibirDetalhesNos:
 * Exibe a arvore em formato hierarquico passo a passo, mostrando os nós e faixas.
 */
void exibirDetalhesNos(SegmentTree *st) {
    if (estaVazia(st)) {
        printf("\n  [AVISO] A arvore esta vazia!\n");
        return;
    }

    printf("\n  --- HIERARQUIA DOS NOS DA ARVORE (FAIXAS DE SOMA) ---\n");
    exibirNosRecursivo(st, 1, 0, st->tamanho - 1, 0);
    printf("  -----------------------------------------------------\n");
}
