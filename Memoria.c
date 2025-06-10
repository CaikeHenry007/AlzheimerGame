#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // Para Sleep e system("cls")

#define TAM 4
#define TOTAL_PARES 8

// Função para gerar a matriz com pares embaralhados
void gerarMatriz(int matriz[TAM][TAM]) {
    int pares[16];
    int usados[10] = {0};
    int count = 0;

    srand(time(NULL)); // Garante números diferentes a cada execução

    // Gera 8 pares de números aleatórios de 0 a 9, sem repetir mais de 2 vezes
    while (count < TOTAL_PARES) {
        int num = rand() % 10;
        if (usados[num] < 2) {
            pares[count * 2] = num;
            pares[count * 2 + 1] = num;
            usados[num] += 2;
            count++;
        }
    }

    // Embaralhar os pares
    for (int i = 15; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = pares[i];
        pares[i] = pares[j];
        pares[j] = temp;
    }

    // Preencher a matriz 4x4 com os pares embaralhados
    int k = 0;
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            matriz[i][j] = pares[k++];
        }
    }
}

// Função para mostrar a matriz visível (com os números descobertos ou escondidos)
void mostrarMatrizVisivel(char visivel[TAM][TAM]) {
    printf("\n    0   1   2   3\n");
    printf("  +---+---+---+---+\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d |", i);
        for (int j = 0; j < TAM; j++) {
            printf(" %c |", visivel[i][j]);
        }
        printf("\n  +---+---+---+---+\n");
    }
}

// Função para mostrar os números reais da matriz (por 5 segundos)
void mostrarMatrizNumeros(int matriz[TAM][TAM]) {
    printf("\n    0   1   2   3\n");
    printf("  +---+---+---+---+\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d |", i);
        for (int j = 0; j < TAM; j++) {
            printf(" %d |", matriz[i][j]);
        }
        printf("\n  +---+---+---+---+\n");
    }
    Sleep(5000); // Aguarda 5 segundos
    system("cls"); // Limpa a tela
}

// Verifica se a coordenada digitada é válida
int coordenadaValida(int l, int c) {
    return l >= 0 && l < TAM && c >= 0 && c < TAM;
}

// Função para executar uma rodada do jogo
int jogarRodada(int matriz[TAM][TAM], char visivel[TAM][TAM], int *acertos, int *erros) {
    int l1, c1, l2, c2;

    mostrarMatrizVisivel(visivel); // Mostra a matriz atual

    // Entrada da 1ª posição
    do {
        printf("\nDigite linha e coluna da 1ª posicao (0 a 3): ");
        scanf("%d %d", &l1, &c1);
    } while (!coordenadaValida(l1, c1));

    printf("Valor na posição (%d,%d): %d\n", l1, c1, matriz[l1][c1]);

    // Entrada da 2ª posição
    do {
        printf("Digite linha e coluna da 2ª posicao (0 a 3): ");
        scanf("%d %d", &l2, &c2);
    } while (!coordenadaValida(l2, c2));

    printf("Valor na posicao (%d,%d): %d\n", l2, c2, matriz[l2][c2]);

    // Verifica se formou um par válido
    if (matriz[l1][c1] == matriz[l2][c2] && (l1 != l2 || c1 != c2)) {
        visivel[l1][c1] = matriz[l1][c1] + '0';
        visivel[l2][c2] = matriz[l2][c2] + '0';
        (*acertos)++;
        putchar(7); // Beep do sistema
        printf("Par encontrado! Acertos: %d\n", *acertos);
    } else {
        printf("Errado!\n");
        (*erros)++;
        Sleep(2000); // Espera 2 segundos
    }

    // Termina se acertou todos os pares ou errou mais de 10 vezes
    return *acertos == 8 || *erros > 10;
}

// Função para salvar a pontuação no arquivo
void salvarPontuacao(int acertos, int erros) {
    char nome[50];
    char salvar;

    printf("Deseja salvar sua pontuacao? (s/n): ");
    scanf(" %c", &salvar);

    if (salvar == 's' || salvar == 'S') {
        printf("Digite seu nome: ");
        scanf("%s", nome);

        FILE *arquivo = fopen("jogomemoria2025.txt", "a");
        if (arquivo) {
            fprintf(arquivo, "Nome: %s | Acertos: %d | Erros: %d\n", nome, acertos, erros);
            fclose(arquivo);
            printf("Pontuacao salva!\n");
        } else {
            printf("Erro ao salvar a pontuacao.\n");
        }
    }
}

// Função para exibir o menu principal
void exibirMenu() {
    char simbolo1 = 16; // Caractere ASCII (Seta para direita)
    char simbolo2 = 17; // Caractere ASCII (Seta para esquerda)

    printf(
        "\n"
        "     _    _     _          _                        ____                      \n"
        "    / \\  | |___| |__   ___(_)_ __ ___   ___ _ __   / ___| __ _ _ __ ___   ___ \n"
        "   / _ \\ | |_  / '_ \\ / _ \\ | '_ ` _ \\ / _ \\ '__| | |  _ / _` | '_ ` _ \\ / _ \\\n"
        "  / ___ \\| |/ /| | | |  __/ | | | | | |  __/ |    | |_| | (_| | | | | | |  __/\n"
        " /_/   \\_\\_/___|_| |_|\\___|_|_| |_| |_|\\___|_|     \\____|\\__,_|_| |_| |_|\\___|\n"
        "                                                                              \n"
        "                                \n"
    );

    printf("\n MENU PRINCIPAL\n");
    printf("%c 1 Iniciar Jogo\n", simbolo1);
    printf("%c 2 Sair\n", simbolo2);
    printf("\nEscolha uma opcao: ");
}

// Função principal do jogo
void iniciarJogo() {
    int matriz[TAM][TAM];
    char visivel[TAM][TAM];
    char simbolo = 3; // Caractere ASCII (coração)
    char jogarNovamente;

    do {
        int acertos = 0, erros = 0;

        gerarMatriz(matriz);
        mostrarMatrizNumeros(matriz);

        // Preenche a matriz visível com símbolos
        for (int i = 0; i < TAM; i++)
            for (int j = 0; j < TAM; j++)
                visivel[i][j] = simbolo;

        int fim = 0;
        while (!fim) {
            fim = jogarRodada(matriz, visivel, &acertos, &erros);
        }

        printf("\nFim do jogo. Acertos: %d | Erros: %d\n", acertos, erros);
        salvarPontuacao(acertos, erros);

        printf("Deseja jogar novamente? (s/n): ");
        scanf(" %c", &jogarNovamente);
        system("cls");

    } while (jogarNovamente == 's' || jogarNovamente == 'S');
}

// Função principal do programa
int main() {
    int opcao;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                iniciarJogo();
                break;
            case 2:
                printf("\nSaindo...\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
                Sleep(1500);
                system("cls");
        }

    } while (opcao != 2);

    printf("Saiu!\n");
    return 0;
}
