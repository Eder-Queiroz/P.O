#include <stdio.h>
#include <stdlib.h>
void merge(int vet[], int esquerda, int middle, int direita, int *count);

void sort(int vet[], int esquerda, int direita, int *count);

int main()
{
    int n = -1;
    int *vetor;
    int count = 0;

    do
    {

        scanf("%i", &n);

        count = 0;

        vetor = (int *)malloc(n * sizeof(int));

        if (n != 0)
        {
            for (int i = 0; i < n; i++)
            {
                scanf("%i", &vetor[i]);
            }

            sort(vetor, 0, n - 1, &count);

            if (count % 2)
                printf("Marcelo\n");
            else
                printf("Carlos\n");

            free(vetor);
        }

    } while (n != 0);

    return 0;
}

void merge(int vetor[], int esquerda, int meio, int direita, int *count)
{
    int i, j, k;
    int indice1 = meio - esquerda + 1;
    int indice2 = direita - meio;

    int *L = (int *)malloc(indice1 * sizeof(int));
    int *R = (int *)malloc(indice2 * sizeof(int));

    for (i = 0; i < indice1; i++)
        L[i] = vetor[esquerda + i];

    for (j = 0; j < indice2; j++)
        R[j] = vetor[meio + 1 + j];

    i = 0;
    j = 0;
    k = esquerda;

    while (i < indice1 && j < indice2)
    {
        if (L[i] < R[j])
        {
            vetor[k] = L[i];
            i++;
        }
        else
        {
            vetor[k] = R[j];
            (*count) += indice1 - i;
            j++;
        }
        k++;
    }

    while (i < indice1)
    {
        vetor[k] = L[i];
        i++;
        k++;
    }

    while (j < indice2)
    {
        vetor[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void sort(int vetor[], int esquerda, int direita, int *count)
{
    if (esquerda < direita)
    {
        int meio = esquerda + (direita - esquerda) / 2;

        sort(vetor, esquerda, meio, count);

        sort(vetor, meio + 1, direita, count);

        merge(vetor, esquerda, meio, direita, count);
    }
}