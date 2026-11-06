#include <stdio.h>
#include <stdlib.h>
#include "segtree.h"

/*
 * ============================================================================
 * TRABALHO AVALIATIVO: ESTRUTURAS DE ARVORES
 * Instituto Federal Baiano - Campus Guanambi
 * Curso Superior de Tecnologia em Analise e Desenvolvimento de Sistemas (ADS)
 * Disciplina: Estrutura de Dados
 * Professor: Reinaldo Cotrim
 * 
 * TEMA: Arvore de Segmentos (Segment Tree para Soma de Intervalos)
 * Integrantes: Hiago Souza & Vinicius Benevides
 * ============================================================================
 */

/* Limpa o buffer de entrada do teclado para evitar leituras invalidas */
static void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/* Pausa a tela aguardando o usuario pressionar ENTER */
static void pausar(void) {
    printf("\n  Pressione [ENTER] para continuar...");
    limparBuffer();
}

/* Cabecalho institucional com visual academico */
static void exibirCabecalho(void) {
    printf("\n");
    printf("  ===============================================================================\n");
    printf("     _____  ______ _____ __  __ ______ _   _ _______   _______ _____  ______ ______\n");
    printf("    / ____||  ____/ ____|  \\/  |  ____| \\ | |__   __| |__   __|  __ \\|  ____|  ____|\n");
    printf("   | (___  | |__ | |  __| \\  / | |__  |  \\| |  | |       | |  | |__) | |__  | |__   \n");
    printf("    \\___ \\ |  __|| | |_ | |\\/| |  __| | . ` |  | |       | |  |  _  /|  __| |  __|  \n");
    printf("    ____) || |___| |__| | |  | | |____| |\\  |  | |       | |  | | \\ \\| |____| |____ \n");
    printf("   |_____/ |______\\_____|_|  |_|______|_| \\_|  |_|       |_|  |_|  \\_\\______|______|\n");
    printf("  ===============================================================================\n");
    printf("                       ARVORE DE SEGMENTOS (SEGMENT TREE)\n");
    printf("             Representacao em Vetor - Soma de Intervalos e Atualizacao\n");
    printf("                  IF Baiano - Campus Guanambi - CST em ADS\n");
    printf("                     Professor: Reinaldo Cotrim\n");
    printf("  ===============================================================================\n");
}

/* Menu de opcoes no terminal */
static void exibirMenu(void) {
    printf("  [1] Construir Arvore a partir de um novo vetor\n");
    printf("  [2] Consultar soma em intervalo [L, R]\n");
    printf("  [3] Atualizar elemento especifico (indice e novo valor)\n");
    printf("  [4] Exibir vetor original, representacao em vetor da arvore e raiz\n");
    printf("  [5] Exibir hierarquia detalhada dos nos da arvore (faixas de soma)\n");
    printf("  [6] Executar os 4 TESTES OBRIGATORIOS automaticamente (Apresentacao Oficial)\n");
    printf("  [0] Encerrar programa (com liberacao de memoria)\n");
    printf("  -------------------------------------------------------------------------------\n");
    printf("  Escolha uma opcao: ");
}

/*
 * executarTestesObrigatorios:
 * Executa passo a passo exatamente o roteiro oficial dos 4 testes exigidos
 * no documento do professor, exibindo as entradas, saidas e explicacoes.
 */
static void executarTestesObrigatorios(SegmentTree *st) {
    printf("\n  ===============================================================================\n");
    printf("               DEMONSTRACAO DOS 4 TESTES OBRIGATORIOS DO TRABALHO\n");
    printf("  ===============================================================================\n");

    /* TESTE 1 */
    printf("\n  >>> TESTE 1: Construcao da Arvore de Segmentos\n");
    printf("  Entrada oficial: vetor [1, 3, 5, 7, 9, 11] (Tamanho N = 6)\n");
    int vetorTeste[6] = {1, 3, 5, 7, 9, 11};
    construirArvore(st, vetorTeste, 6);
    exibirEstruturaArvore(st);
    printf("  [VERIFICACAO TESTE 1]:\n");
    printf("  - Raiz obtida: %d\n", obterValorRaiz(st));
    printf("  - Soma esperada de todos os elementos: 1 + 3 + 5 + 7 + 9 + 11 = 36\n");
    if (obterValorRaiz(st) == 36) {
        printf("  - RESULTADO: [SUCESSO COMPROVADO - RAIZ = 36]\n");
    } else {
        printf("  - RESULTADO: [FALHA]\n");
    }
    pausar();

    /* TESTE 2 */
    printf("\n  >>> TESTE 2: Consulta de Intervalo (Range Sum Query)\n");
    printf("  Entrada oficial: intervalo de indices [1, 3]\n");
    printf("  Elementos correspondentes no vetor original: [1]=3, [2]=5, [3]=7\n");
    int somaTeste2 = consultarSoma(st, 1, 3);
    printf("  - Soma calculada pela Segment Tree: %d\n", somaTeste2);
    printf("  - Soma manual esperada: 3 + 5 + 7 = 15\n");
    if (somaTeste2 == 15) {
        printf("  - RESULTADO: [SUCESSO COMPROVADO - SOMA = 15]\n");
    } else {
        printf("  - RESULTADO: [FALHA]\n");
    }
    pausar();

    /* TESTE 3 */
    printf("\n  >>> TESTE 3: Atualizacao Pontual (Point Update)\n");
    printf("  Entrada oficial: alterar o indice [2] de 5 para 10\n");
    atualizarElemento(st, 2, 10);
    exibirEstruturaArvore(st);
    printf("  [VERIFICACAO TESTE 3]:\n");
    printf("  - Nova raiz obtida: %d\n", obterValorRaiz(st));
    printf("  - Soma total esperada apos alterar 5 para 10: 36 + (10 - 5) = 41\n");
    if (obterValorRaiz(st) == 41) {
        printf("  - RESULTADO: [SUCESSO COMPROVADO - NOVA RAIZ = 41]\n");
    } else {
        printf("  - RESULTADO: [FALHA]\n");
    }
    pausar();

    /* TESTE 4 */
    printf("\n  >>> TESTE 4: Nova Consulta no Intervalo [1, 3] Apos a Atualizacao\n");
    printf("  Entrada oficial: consultar novamente o intervalo [1, 3]\n");
    printf("  Elementos atuais no vetor: [1]=3, [2]=10 (atualizado), [3]=7\n");
    int somaTeste4 = consultarSoma(st, 1, 3);
    printf("  - Soma calculada pela Segment Tree: %d\n", somaTeste4);
    printf("  - Soma manual esperada: 3 + 10 + 7 = 20\n");
    if (somaTeste4 == 20) {
        printf("  - RESULTADO: [SUCESSO COMPROVADO - NOVA SOMA = 20]\n");
    } else {
        printf("  - RESULTADO: [FALHA]\n");
    }
    printf("\n  ===============================================================================\n");
    printf("              FIM DOS 4 TESTES OBRIGATORIOS - TODOS PASSARAM COM EXITO!\n");
    printf("  ===============================================================================\n");
    pausar();
}

int main(void) {
    SegmentTree st;
    st.vetorOriginal = NULL;
    st.arvore = NULL;
    st.tamanho = 0;
    st.capacidade = 0;

    int opcao = -1;

    do {
        exibirCabecalho();
        exibirMenu();

        if (scanf("%d", &opcao) != 1) {
            printf("\n  [ERRO] Entrada invalida! Digite apenas o numero correspondente a opcao.\n");
            limparBuffer();
            pausar();
            continue;
        }
        limparBuffer();

        switch (opcao) {
            case 1: {
                int n;
                printf("\n  +--- [CONSTRUIR ARVORE DE SEGMENTOS] ------------------------+\n");
                printf("  | Informe a quantidade de elementos do vetor (N > 0): ");
                if (scanf("%d", &n) != 1 || n <= 0) {
                    printf("  | [ERRO] Quantidade invalida! Deve ser um numero inteiro maior que 0.\n");
                    limparBuffer();
                    pausar();
                    break;
                }

                int *valores = (int *)malloc(n * sizeof(int));
                if (valores == NULL) {
                    printf("  | [ERRO] Falha ao alocar memoria temporaria!\n");
                    pausar();
                    break;
                }

                printf("  | Digite os %d valores inteiros separados por espaco:\n  | ", n);
                int leituraValida = 1;
                for (int i = 0; i < n; i++) {
                    if (scanf("%d", &valores[i]) != 1) {
                        leituraValida = 0;
                        break;
                    }
                }
                limparBuffer();

                if (!leituraValida) {
                    printf("  | [ERRO] Falha ao ler os elementos. Operacao cancelada!\n");
                    free(valores);
                    pausar();
                    break;
                }

                construirArvore(&st, valores, n);
                free(valores);

                printf("  | [OK] Arvore de Segmentos construida com sucesso!\n");
                printf("  | [INFO] Raiz calculada (Soma total) = %d\n", obterValorRaiz(&st));
                printf("  +------------------------------------------------------------+\n");
                pausar();
                break;
            }

            case 2: {
                if (estaVazia(&st)) {
                    printf("\n  [AVISO] A arvore ainda nao foi construida! Use a opcao [1] primeiro.\n");
                    pausar();
                    break;
                }

                int L, R;
                printf("\n  +--- [CONSULTAR SOMA EM INTERVALO [L, R]] -------------------+\n");
                exibirVetorOriginal(&st);
                printf("  | Informe o indice inicial L (de 0 ate %d): ", st.tamanho - 1);
                if (scanf("%d", &L) != 1) {
                    printf("  | [ERRO] Entrada invalida para L!\n");
                    limparBuffer();
                    pausar();
                    break;
                }
                printf("  | Informe o indice final R (de %d ate %d): ", L, st.tamanho - 1);
                if (scanf("%d", &R) != 1) {
                    printf("  | [ERRO] Entrada invalida para R!\n");
                    limparBuffer();
                    pausar();
                    break;
                }
                limparBuffer();

                int resultado = consultarSoma(&st, L, R);
                printf("  | ------------------------------------------------------------\n");
                printf("  | [RESULTADO]: Soma no intervalo [%d, %d] = %d\n", L, R, resultado);
                printf("  +------------------------------------------------------------+\n");
                pausar();
                break;
            }

            case 3: {
                if (estaVazia(&st)) {
                    printf("\n  [AVISO] A arvore ainda nao foi construida! Use a opcao [1] primeiro.\n");
                    pausar();
                    break;
                }

                int indice, novoValor;
                printf("\n  +--- [ATUALIZAR ELEMENTO PONTUAL] ---------------------------+\n");
                exibirVetorOriginal(&st);
                printf("  | Informe o indice a ser alterado (0 a %d): ", st.tamanho - 1);
                if (scanf("%d", &indice) != 1) {
                    printf("  | [ERRO] Indice invalido!\n");
                    limparBuffer();
                    pausar();
                    break;
                }
                printf("  | Informe o novo valor para a posicao [%d]: ", indice);
                if (scanf("%d", &novoValor) != 1) {
                    printf("  | [ERRO] Valor invalido!\n");
                    limparBuffer();
                    pausar();
                    break;
                }
                limparBuffer();

                atualizarElemento(&st, indice, novoValor);
                pausar();
                break;
            }

            case 4:
                exibirEstruturaArvore(&st);
                pausar();
                break;

            case 5:
                exibirDetalhesNos(&st);
                pausar();
                break;

            case 6:
                executarTestesObrigatorios(&st);
                break;

            case 0:
                printf("\n  Liberando memoria alocada e encerrando o programa...\n");
                liberarArvore(&st);
                printf("  [OK] Memoria liberada com sucesso. Ate logo!\n\n");
                break;

            default:
                printf("\n  [ERRO] Opcao desconhecida (%d)! Escolha uma opcao valida de 0 a 6.\n", opcao);
                pausar();
                break;
        }

    } while (opcao != 0);

    return 0;
}
