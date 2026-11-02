#include <stdio.h>
#include <string.h>
#define MAX 100

void bubbleSort(int v[], int n) { int i, j, aux; for (i = 0; i < n - 1; i++) { for (j = 0; j < n - i - 1; j++) { if (v[j] > v[j + 1]) { aux = v[j]; v[j] = v[j + 1]; v[j + 1] = aux;}}}}
void insertionSort(int v[], int n) { int i, j, chave; for (i = 1; i < n; i++) { chave = v[i]; j = i - 1; while (j >= 0 && v[j] > chave) { v[j + 1] = v[j]; j--; } v[j + 1] = chave; }}
void selectionSort(int v[], int n) { int i, j, min, aux; for (i = 0; i < n - 1; i++) { min = i; for (j = i + 1; j < n; j++) { if (v[j] < v[min]) min = j; } aux = v[i]; v[i] = v[min]; v[min] = aux; }}
void merge(int v[], int inicio, int meio, int fim) { int i = inicio, j = meio + 1, k = 0; int aux[fim - inicio + 1]; while (i <= meio && j <= fim) { if (v[i] <= v[j]) aux[k++] = v[i++]; else aux[k++] = v[j++]; } while (i <= meio) aux[k++] = v[i++]; while (j <= fim) aux[k++] = v[j++]; for (i = inicio, k = 0; i <= fim; i++, k++) v[i] = aux[k]; }
void mergeSort(int v[], int inicio, int fim) { if (inicio < fim) { int meio = (inicio + fim) / 2; mergeSort(v, inicio, meio); mergeSort(v, meio + 1, fim); merge(v, inicio, meio, fim); }}
void quickSort(int v[], int inicio, int fim) { int i = inicio, j = fim, pivo = v[(inicio + fim) / 2], aux; while (i <= j) { while (v[i] < pivo) i++; while (v[j] > pivo) j--; if (i <= j) { aux = v[i]; v[i] = v[j]; v[j] = aux; i++; j--; } } if (inicio < j) quickSort(v, inicio, j); if (i < fim) quickSort(v, i, fim); }

int main() {

    int opcao;
    int dados[MAX];
    int n1;

    //LEITURA DO ARQUIVO
    n1 = 0;
    FILE *arquivo = fopen("dados.txt", "r");   // abre o arquivo para LEITURA
    if (arquivo == NULL) { // verifica se o arquivo abriu ou foi criado corretamente
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
 
    while (fscanf(arquivo, "%d", &dados[n1]) == 1) { // enquanto conseguir ler um dado do arquivo, guarda o dado no elemento 'i' do vetor e avanca o contador
        n1++;
    }

    fclose(arquivo); // fecha o arquivo

    printf("Total de dados lidos do arquivo: %d\n", n1); // Mostra quantos dados foram lidos

    //MENU ORDENACAO
    printf("\n======================================\nMENU DE ORDENACAO\n");
    printf("\nOpcao 1 - Bubble Sort\nOpcao 2 - Insertion Sort\nOpcao 3 - Selection Sort\nOpcao 4 - Merge Sort\nOpcao 5 - Quick Sort\n");
    do {
        printf("\nEscolha qual opcao deseja utilizar: ");
        scanf("%d", &opcao);
        printf("\n======================================\n");
    if (opcao <= 0 || opcao > 5) {
        printf("Opcao invalida! Escolha entre 1 e 5\n");
    }
    } while (opcao <= 0 || opcao > 5);

    // 
    switch (opcao) {

        case 1: {
            bubbleSort(dados, n1);
            
            printf("\nVetor ordenado (Bubble Sort)\n\n");
            for (int i = 0; i < n1; i++) {
                printf("'%d' inserido na linha: %d\n", dados[i], i+1);
            }
            break;
        }

        case 2: {
            insertionSort(dados, n1);

            printf("\nVetor ordenado (Insertion Sort)\n\n");
            for (int i = 0; i < n1; i++) {
                printf("'%d' inserido na linha: %d\n", dados[i], i+1);
            }
            break;
        }

        case 3: {
            selectionSort(dados, n1);

            printf("\nVetor ordenado (Selection Sort)\n\n");
            for (int i = 0; i < n1; i++) {
                printf("'%d' inserido na linha: %d\n", dados[i], i+1);
            }
            break;
        }

        case 4: {
           mergeSort(dados, 0, n1 - 1);

            printf("\nVetor ordenado (Merge Sort)\n\n");
            for (int i = 0; i < n1; i++) {
                printf("'%d' inserido na linha: %d\n", dados[i], i+1);
            }
            break;
        }

        case 5: {
            quickSort(dados, 0, n1 - 1);

            printf("\nVetor ordenado (Quick Sort)\n\n");
            for (int i = 0; i < n1; i++) {
                printf("'%d' inserido na linha: %d\n", dados[i], i+1);
            }
            break;
        }
    }
    return 0;
}