#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // Para Sleep e system("cls")

#define TAM 4
#define TOTAL_PARES 8

void gerarMatriz(int matriz[TAM][TAM])
{
    int pares[16];
    int usados[10] = {0};
    int count = 0;

    srand(time(NULL));

    while (count < TOTAL_PARES)
    {
        int num = rand() % 10;
        if (usados[num] < 2)
        {
            pares[count * 2] = num;
            pares[count * 2 + 1] = num;
            usados[num] += 2;
            count++;
        }
    }

    // Embaralhar
    for (int i = 15; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = pares[i];
        pares[i] = pares[j];
        pares[j] = temp;
    }

    // Preencher matriz
    int k = 0;
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            matriz[i][j] = pares[k++];
}

void mostrarMatrizNumeros(int matriz[TAM][TAM])
{
    printf("\n    0   1   2   3\n");
    printf("  +---+---+---+---+\n");
    for (int i = 0; i < TAM; i++)
    {
        printf("%d |", i);
        for (int j = 0; j < TAM; j++)
        {
            printf(" %d |", matriz[i][j]);
        }
        printf("\n  +---+---+---+---+\n");
    }
    Sleep(5000); // 5 segundos
    system("cls");
}

void mostrarMatrizVisivel(char visivel[TAM][TAM])
{
    printf("\n    0   1   2   3\n");
    printf("  +---+---+---+---+\n");
    for (int i = 0; i < TAM; i++)
    {
        printf("%d |", i);
        for (int j = 0; j < TAM; j++)
        {
            printf(" %c |", visivel[i][j]);
        }
        printf("\n  +---+---+---+---+\n");
    }
}

int coordenadaValida(int l, int c)
{
    return l >= 0 && l < TAM && c >= 0 && c < TAM;
}

int jogarRodada(int matriz[TAM][TAM], char visivel[TAM][TAM], int *acertos, int *erros)
{
    int l1, c1, l2, c2;

    mostrarMatrizVisivel(visivel);

    do
    {
        printf("\nDigite linha e coluna da 1ª posição (0 a 3): ");
        scanf("%d %d", &l1, &c1);
    } while (!coordenadaValida(l1, c1));

    printf("Valor na posição (%d,%d): %d\n", l1, c1, matriz[l1][c1]);

    do
    {
        printf("Digite linha e coluna da 2ª posição (0 a 3): ");
        scanf("%d %d", &l2, &c2);
    } while (!coordenadaValida(l2, c2));

    printf("Valor na posição (%d,%d): %d\n", l2, c2, matriz[l2][c2]);

    if (matriz[l1][c1] == matriz[l2][c2] && (l1 != l2 || c1 != c2))
    {
        visivel[l1][c1] = matriz[l1][c1] + '0';
        visivel[l2][c2] = matriz[l2][c2] + '0';
        (*acertos)++;
        putchar(7); // som (beep)
        printf("Par encontrado! Acertos: %d\n", *acertos);
    }
    else
    {
        printf("Errado!\n");
        (*erros)++;
        Sleep(2000); // 2 segundos
    }

    return *acertos == 8 || *erros > 10;
}

void salvarPontuacao(int acertos, int erros)
{
    char nome[50];
    char salvar;

    printf("Deseja salvar sua pontuação? (s/n): ");
    scanf(" %c", &salvar);

    if (salvar == 's' || salvar == 'S')
    {
        printf("Digite seu nome: ");
        scanf("%s", nome);

        FILE *arquivo = fopen("jogomemoria2025.txt", "a");
        if (arquivo)
        {
            fprintf(arquivo, "Nome: %s | Acertos: %d | Erros: %d\n", nome, acertos, erros);
            fclose(arquivo);
            printf("Pontuação salva!\n");
        }
        else
        {
            printf("Erro ao salvar a pontuação.\n");
        }
    }
}

int main()
{
    int matriz[TAM][TAM];
    char visivel[TAM][TAM];
    char jogarNovamente;
    char simbolo = '*';

    do
    {
        int acertos = 0, erros = 0;

        gerarMatriz(matriz);
        mostrarMatrizNumeros(matriz);

        for (int i = 0; i < TAM; i++)
            for (int j = 0; j < TAM; j++)
                visivel[i][j] = simbolo;

        int fim = 0;
        while (!fim)
        {
            fim = jogarRodada(matriz, visivel, &acertos, &erros);
        }

        printf("\nFim do jogo. Acertos: %d | Erros: %d\n", acertos, erros);
        salvarPontuacao(acertos, erros);

        printf("Deseja jogar novamente? (s/n): ");
        scanf(" %c", &jogarNovamente);
        system("cls");

    } while (jogarNovamente == 's' || jogarNovamente == 'S');

    printf("Obrigado por jogar!\n");
    return 0;
}
