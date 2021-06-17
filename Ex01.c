/*
    Crie uma função que	receba como	parâmetros dois	vetores	de inteiros: x1	e x2 e as suas respectivas	
    quantidades	de elementos: n1 e n2. A função deverá retornar um ponteiro	para um	terceiro vetor,	
    x3,	alocado	dinamicamente, contendo	a união	de x1 e	x2 e usar o	ponteiro qtd para retornar o tamanho	
    de x3. Sendo x1	= {1, 3, 5, 6, 7} e	x2 = {1, 3,	4, 6, 8}, x3 irá conter	{1,	3, 4, 5, 6,	7, 8}.
    Assinatura da função: int* uniao(int *x1, int *x2, int n1, int n2, int* qtd);        
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Funções auxiliares

/* Retorna o índice do menor valor encontrado*/
int Posicao_Menor_Valor(int *vetor, int inicio, int tamanho)
{
    int menor = vetor[inicio];
    for (int i = inicio + 1; i < tamanho; i++)
    {
        if (vetor[i] < menor)
        {
            menor = vetor[i];
            inicio = i;
        }
    }
    return inicio;
}

/* Realiza uma selection sort */
int *Selection_Sort(int *vetor, int tamanho)
{
    int aux = 0;
    int indice;

    for (int i = 0; i < tamanho - 1; i++)
    {
        indice = Posicao_Menor_Valor(vetor, i, tamanho);
        aux = vetor[i];
        vetor[i] = vetor[indice];
        vetor[indice] = aux;
    }
    return vetor;
}

// Função principal

/* Refetua a união dos elementos de dois vetores */
int *uniao(int *x1, int *x2, int n1, int n2, int *qtd)
{
    int i, j;
    int igual = 0;
    int diferente = 0;
    int qtd_iguais = 0;
    int qtd_diferentes = 0;

    int *iguais = (int *)malloc((n1 + n2) * sizeof(int));
    int *diferentes = (int *)malloc((n1 + n2) * sizeof(int));
    int *u = (int *)malloc((n1 + n2) * sizeof(int));

    // Preenche dinamicamente um vetor com os valores comuns aos dois vetores dados
    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n2; j++)
        {
            if (x1[i] == x2[j])
            {
                iguais[qtd_iguais] = x1[i];
                qtd_iguais++;
            }
        }
    }

    // Preenche dinamicamente um vetor com os valores exclusivos de x1
    for (i = 0; i < n1; i++)
    {
        diferente = 0;
        int j = 0;
        while (j < qtd_iguais)
        {
            if (x1[i] == iguais[j])
            {
                diferente = 1;
            }
            j++;
        }
        if (!diferente)
        {
            diferentes[qtd_diferentes] = x1[i];
            qtd_diferentes++;
        }
    }

    // Preenche dinamicamente um vetor com os valores exclusivos de x2
    for (i = 0; i < n2; i++)
    {
        diferente = 0;
        int j = 0;
        while (j < qtd_iguais)
        {
            if (x2[i] == iguais[j])
            {
                diferente = 1;
            }
            j++;
        }
        if (!diferente)
        {
            diferentes[qtd_diferentes] = x2[i];
            qtd_diferentes++;
        }
    }

    // O tamanho do vetor união
    *qtd = qtd_iguais + qtd_diferentes;
    u = realloc(u, (qtd_iguais + qtd_diferentes) * sizeof(int));

    // Preenchendo o vetor união
    for (i = 0; i < qtd_iguais; i++)
    {
        u[i] = iguais[i];
    }
    for (i = qtd_iguais, j = 0; i < qtd_diferentes + qtd_iguais; i++, j++)
    {
        u[i] = diferentes[j];
    }
    return Selection_Sort(u, *qtd);
}

int main(int argc, char const *argv[])
{
    system("cls");
    srand(time(NULL));

    int i, j;
    int nv1, nv2;
    int *vet1, *vet2, *v_uniao, qtd_numeros;

    // Preenchendo vet1
    printf("\n Informe o tamanho do vetor vet1: ");
    scanf("%d", &nv1);
    fflush(stdin);

    vet1 = (int *)malloc(nv1 * sizeof(int));    
    for (i = 0; i < nv1; i++)
    {
        vet1[i] = rand() % 50;     
    }    

    vet1 = Selection_Sort(vet1, nv1);

    printf(" v1 = {");
    for (i = 0; i < nv1; i++)
    {
        vet1[i] = rand() % 50;
        printf(" %2d", vet1[i]);
    }
    printf(" }\n");

    // Preenchendo vet2
    printf("\n Informe o tamanho do vetor vet2: ");
    scanf("%d", &nv2);
    fflush(stdin);

    vet2 = (int *)malloc(nv2 * sizeof(int));    
    for (i = 0; i < nv2; i++)
    {
        vet2[i] = rand() % 50;        
    }

    vet2 = Selection_Sort(vet2, nv2);
    
    printf(" v2 = {");
    for (i = 0; i < nv2; i++)
    {
        vet2[i] = rand() % 50;
        printf(" %2d", vet2[i]);
    }
    printf(" }\n");


    v_uniao = uniao(vet1, vet2, nv1, nv2, &qtd_numeros);

    // Exibindo o vetor união
    printf("\n\n v1 U v2 = {");
    for (i = 0; i < (qtd_numeros); i++)
    {
        printf(" %2d", v_uniao[i]);
    }
    printf(" }\n\n");
    return 0;
}