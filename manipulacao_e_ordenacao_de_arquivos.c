#include <stdio.h>
#include <string.h>
#define MAX 100


int main() {

    int opcao, opcaoArquivo;
    int dados[MAX];
    int n1, n2;

    // Menu arquivo
    printf("\n======================================\nMENU DE ARQUIVO\n");
    printf("\nOpcao 1 - Criar arquivo\nOpcao 2 - Ler/Exibir dados\nOpcao 3 - Editar arquivo\nOpcao 4 - Ordenar arquivo\n");
    printf("\nEscolha qual opcao deseja utilizar: ");
    scanf("%d", &opcaoArquivo);
    printf("\n======================================\n");

    // 
    switch (opcaoArquivo) {

        case 1: { // Criar arquivo
            FILE *arquivo = fopen("dados.txt", "w"); // Abre para subescrever ou cria um novo arquivo
            
            if (arquivo == NULL) { // Verifica se o arquivo abriu ou foi criado corretamente
                printf("Erro ao abrir/criar o arquivo!\n");
                return 1;   // encerra o programa, ja que nao ha como continuar sem o arquivo
            }

            do {
                printf("\nQuantos valores deseja cadastrar (maximo %d)? ", MAX);
                scanf("%d", &n1);
                if (n1 > MAX || n1 <= 0) {
                    printf("Valor invalido! Digite um valor entre 1 e %d\n", MAX);
                }
            } while (n1 > MAX || n1 <= 0);

            printf("\n");

            for (int i = 0; i < n1; i++) {
                printf("Digite o numero que deseja guardar na linha %d do arquivo: ", i+1);
                scanf("%d", &dados[i]);
                fprintf(arquivo, "%d\n", dados[i]); // Escreve um numero por linha dentro do arquivo
            }

            fclose(arquivo); // Fecha o arquivo e salva o conteudo
            printf("\n\n");

            printf("\n========================================\nArquivo 'dados.txt' gerado com sucesso!\n\n");
            for (int i = 0; i < n1; i++) {
                printf("'%d' inserido na linha: %d\n", dados[i], i+1);
            }
            printf("\n========================================\n");
            break;
        }

        case 2: { // Ler arquivo
            n1 = 0;
            FILE *arquivo = fopen("dados.txt", "r");   // Abre o arquivo para LEITURA
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo!\n");
                return 1;
            }

            while (fscanf(arquivo, "%d", &dados[n1]) == 1) { // Enquanto conseguir ler um dado do arquivo, guarda e avanca o contador
                n1++;
            }

            fclose(arquivo); // fecha o arquivo

            printf("Total de dados lidos do arquivo: %d\n\n", n1); // Mostra quantos numeros foram lidos, e quais sao
            for (int i = 0; i < n1; i++) {
                printf("'%d' inserido na linha: %d\n", dados[i], i+1);
            }
            printf("\n");
            break;
        }

        case 3: { //Editar arquivo

            FILE *arquivo = fopen("dados.txt", "r");   // abre o arquivo para LEITURA
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo!\n");
                return 1;
            }

            n1 = 0;
            
            while (fscanf(arquivo, "%d", &dados[n1]) == 1) { // Enquanto conseguir ler um numero, guarda e avanca o contador
                n1++;
            }

            printf("O arquivo possui %d linhas preenchidas\n", n1); // Mostra quantos numeros foram lidos, e quais sao
            printf("\n========================================\n");

            arquivo = fopen("dados.txt", "a");   // abre o arquivo para anexar algo

            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo!\n");
                return 1;
            }

            do {
            printf("Quantos valores deseja adicionar (maximo %d)? ", MAX - n1);
            scanf("%d", &n2);

            if (n2 > MAX - n1 || n2 <= 0) {
                printf("Valor invalido! Digite um valor entre 1 e %d\n", MAX - n1);
            }
            } while (n2 > (MAX - n1) || n2 <= 0);

            printf("\n");

            for (int i = n1; i < (n1 + n2); i++) {
                printf("Digite o numero que deseja guardar na linha %d do arquivo: ", i+1);
                scanf("%d", &dados[i]);
                fprintf(arquivo, "%d\n", dados[i]); // Escreve um numero por linha dentro do arquivo
            }

            fclose(arquivo); // Fecha o arquivo e salva o conteudo

            printf("\n========================================\nArquivo 'dados.txt' alterado com sucesso!\n\n");
            for (int i = n1; i < (n1 + n2); i++) {
                printf("'%d' inserido na linha: %d\n", dados[i], i+1);
            }
            printf("\n========================================\n");
            break;
        }

        case 4: { // Ordenar arquivo
            printf("\n");
        }
    }
    return 0;
}