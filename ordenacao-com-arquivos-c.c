#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARQUIVO_DADOS "dados.txt"
#define ARQUIVO_ORDENADO "dados_ordenados.txt"
#define MAX_DADOS 10000

/* Le os numeros de um arquivo e devolve a quantidade encontrada. */
int carregarDados(int vetor[], const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    int quantidade = 0;

    if (arquivo == NULL) {
        printf("Nao foi possivel abrir %s. Gere os dados primeiro.\n", nomeArquivo);
        return -1;
    }

    while (quantidade < MAX_DADOS && fscanf(arquivo, "%d", &vetor[quantidade]) == 1) {
        quantidade++;
    }

    fclose(arquivo);
    return quantidade;
}

/* Cria uma lista de numeros aleatorios e grava em dados.txt. */
void gerarArquivo(void) {
    FILE *arquivo;
    int quantidade, i, valor;

    printf("Quantos numeros deseja gerar? (1 a %d): ", MAX_DADOS);
    if (scanf("%d", &quantidade) != 1 || quantidade < 1 || quantidade > MAX_DADOS) {
        printf("Quantidade invalida.\n");
        return;
    }

    arquivo = fopen(ARQUIVO_DADOS, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    for (i = 0; i < quantidade; i++) {
        valor = rand() % 1000; /* Valores entre 0 e 999. */
        fprintf(arquivo, "%d\n", valor);
    }

    fclose(arquivo);
    printf("%d numeros foram gravados em %s.\n", quantidade, ARQUIVO_DADOS);
}

/* Mostra os valores armazenados no arquivo original. */
void mostrarDados(void) {
    int dados[MAX_DADOS];
    int quantidade = carregarDados(dados, ARQUIVO_DADOS);
    int i;

    if (quantidade <= 0) {
        if (quantidade == 0) printf("O arquivo esta vazio.\n");
        return;
    }

    printf("\nDados do arquivo %s:\n", ARQUIVO_DADOS);
    for (i = 0; i < quantidade; i++) {
        printf("%d", dados[i]);
        if (i < quantidade - 1) printf(" | ");
    }
    printf("\nTotal: %d valores.\n", quantidade);
}

/* Bubble Sort: compara valores vizinhos e troca quando estao fora de ordem. */
void bubbleSort(int v[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (v[j] > v[j + 1]) {
                temp = v[j]; v[j] = v[j + 1]; v[j + 1] = temp;
            }
        }
    }
}

/* Insertion Sort: insere cada elemento na posicao correta da parte ordenada. */
void insertionSort(int v[], int n) {
    int i, j, chave;
    for (i = 1; i < n; i++) {
        chave = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

/* Selection Sort: procura o menor valor restante e coloca-o na posicao atual. */
void selectionSort(int v[], int n) {
    int i, j, menor, temp;
    for (i = 0; i < n - 1; i++) {
        menor = i;
        for (j = i + 1; j < n; j++) {
            if (v[j] < v[menor]) menor = j;
        }
        temp = v[i]; v[i] = v[menor]; v[menor] = temp;
    }
}

/* Junta duas partes ja ordenadas, etapa utilizada pelo Merge Sort. */
void intercalar(int v[], int inicio, int meio, int fim) {
    int auxiliar[MAX_DADOS];
    int i = inicio, j = meio + 1, k = inicio;

    while (i <= meio && j <= fim) {
        if (v[i] <= v[j]) auxiliar[k++] = v[i++];
        else auxiliar[k++] = v[j++];
    }
    while (i <= meio) auxiliar[k++] = v[i++];
    while (j <= fim) auxiliar[k++] = v[j++];
    for (i = inicio; i <= fim; i++) v[i] = auxiliar[i];
}

/* Merge Sort: divide o vetor, ordena as partes e depois intercala. */
void mergeSort(int v[], int inicio, int fim) {
    int meio;
    if (inicio < fim) {
        meio = inicio + (fim - inicio) / 2;
        mergeSort(v, inicio, meio);
        mergeSort(v, meio + 1, fim);
        intercalar(v, inicio, meio, fim);
    }
}

/* Particiona o vetor para o Quick Sort. */
int particionar(int v[], int inicio, int fim) {
    int pivo = v[fim];
    int i = inicio - 1, j, temp;

    for (j = inicio; j < fim; j++) {
        if (v[j] <= pivo) {
            i++;
            temp = v[i]; v[i] = v[j]; v[j] = temp;
        }
    }
    temp = v[i + 1]; v[i + 1] = v[fim]; v[fim] = temp;
    return i + 1;
}

/* Quick Sort: organiza o vetor usando um pivo e chamadas recursivas. */
void quickSort(int v[], int inicio, int fim) {
    int posicaoPivo;
    if (inicio < fim) {
        posicaoPivo = particionar(v, inicio, fim);
        quickSort(v, inicio, posicaoPivo - 1);
        quickSort(v, posicaoPivo + 1, fim);
    }
}

/* Salva o vetor ordenado em um novo arquivo. */
void salvarOrdenado(int v[], int n) {
    FILE *arquivo = fopen(ARQUIVO_ORDENADO, "w");
    int i;

    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo de saida.\n");
        return;
    }

    for (i = 0; i < n; i++) fprintf(arquivo, "%d\n", v[i]);
    fclose(arquivo);
    printf("Resultado salvo em %s.\n", ARQUIVO_ORDENADO);
}

/* Permite substituir um valor pela sua posicao (contagem iniciada em 1). */
void alterarValor(void) {
    int dados[MAX_DADOS];
    int quantidade = carregarDados(dados, ARQUIVO_DADOS);
    int posicao, novoValor, i;
    FILE *arquivo;

    if (quantidade <= 0) {
        if (quantidade == 0) printf("O arquivo esta vazio.\n");
        return;
    }

    printf("Digite a posicao que deseja alterar (1 a %d): ", quantidade);
    if (scanf("%d", &posicao) != 1 || posicao < 1 || posicao > quantidade) {
        printf("Posicao invalida.\n");
        return;
    }

    printf("Digite o novo valor: ");
    if (scanf("%d", &novoValor) != 1) {
        printf("Valor invalido.\n");
        return;
    }

    dados[posicao - 1] = novoValor;
    arquivo = fopen(ARQUIVO_DADOS, "w");
    if (arquivo == NULL) {
        printf("Erro ao atualizar o arquivo.\n");
        return;
    }

    for (i = 0; i < quantidade; i++) fprintf(arquivo, "%d\n", dados[i]);
    fclose(arquivo);
    printf("Valor alterado com sucesso. Escolha a opcao de ordenar novamente.\n");
}

/* Le o arquivo, aplica o algoritmo escolhido e grava o resultado. */
void ordenarDados(void) {
    int dados[MAX_DADOS];
    int quantidade = carregarDados(dados, ARQUIVO_DADOS);
    int algoritmo;

    if (quantidade <= 0) {
        if (quantidade == 0) printf("O arquivo esta vazio.\n");
        return;
    }

    printf("\nEscolha o algoritmo de ordenacao:\n");
    printf("1 - Bubble Sort\n");
    printf("2 - Insertion Sort\n");
    printf("3 - Selection Sort\n");
    printf("4 - Merge Sort\n");
    printf("5 - Quick Sort\n");
    printf("Opcao: ");

    if (scanf("%d", &algoritmo) != 1) {
        printf("Opcao invalida.\n");
        return;
    }

    switch (algoritmo) {
        case 1: bubbleSort(dados, quantidade); break;
        case 2: insertionSort(dados, quantidade); break;
        case 3: selectionSort(dados, quantidade); break;
        case 4: mergeSort(dados, 0, quantidade - 1); break;
        case 5: quickSort(dados, 0, quantidade - 1); break;
        default:
            printf("Algoritmo inexistente.\n");
            return;
    }

    printf("Dados ordenados com sucesso.\n");
    salvarOrdenado(dados, quantidade);
}

int main(void) {
    int opcao;
    srand((unsigned int) time(NULL));

    do {
        printf("\n========== SISTEMA DE ORDENACAO ==========");
        printf("\n1 - Gerar arquivo com numeros aleatorios");
        printf("\n2 - Ler e mostrar os dados do arquivo");
        printf("\n3 - Ordenar dados e salvar em novo arquivo");
        printf("\n4 - Alterar um valor no arquivo original");
        printf("\n0 - Sair");
        printf("\nEscolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Encerrando o programa.\n");
            break;
        }

        switch (opcao) {
            case 1: gerarArquivo(); break;
            case 2: mostrarDados(); break;
            case 3: ordenarDados(); break;
            case 4: alterarValor(); break;
            case 0: printf("Programa encerrado.\n"); break;
            default: printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
