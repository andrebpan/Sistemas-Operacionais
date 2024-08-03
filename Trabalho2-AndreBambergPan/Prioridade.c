#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int id;
    int prioridade;
    int tempoCPU;
    int tempo_espera;
} Processo;

void trocarProcessos(Processo *a, Processo *b) 
{
    Processo aux = *a;
    *a = *b;
    *b = aux;
}

//bubble sort
void ordenarPrioridade(Processo *processos, int n) 
{
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (processos[j].prioridade > processos[j + 1].prioridade) 
            {
                trocarProcessos(&processos[j], &processos[j + 1]);
            }
        }
    }
}

void gantt(Processo *processos, int n)
{
    int i,j;
     for (i = 0; i < n; i++) 
     {
        printf("P%d ", processos[i].id);
        for (j = 0; j < processos[i].tempo_espera; j++) 
        {
            printf(" ");
        }
        for (j = 0; j < processos[i].tempoCPU; j++) 
        {
            printf("#");
        }
        printf("\n");
    }
    printf("\n");
}

int main(void) 
{
    int n;
    
    printf("Informe o numero de processos: ");
    scanf("%d", &n);

    Processo *processos = (Processo *)malloc(sizeof(Processo) * n);

    for (int i = 0; i < n; i++) 
    {
        processos[i].id = i;
        printf("Informe a prioridade do P%d: ", i);
        scanf("%d", &processos[i].prioridade);
        printf("Informe o tempo de execucao do P%d: ", i);
        scanf("%d", &processos[i].tempoCPU);
        processos[i].tempo_espera = 0;
    }

    ordenarPrioridade(processos, n);

    int tempoTotal = 0;
    for (int i = 0; i < n; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            processos[j].tempo_espera += processos[i].tempoCPU;
        }
        tempoTotal += processos[i].tempo_espera;
    }

    printf("\nProcesso\tPrioridade\tTempo de CPU\tTempo de espera\n");
    for (int i = 0; i < n; i++) 
    {
        printf("P%d\t\t    ",processos[i].id);
        printf("%d\t\t     ",processos[i].prioridade);
        printf("%d\t\t      ",processos[i].tempoCPU);
        printf("%d\n",processos[i].tempo_espera);
    }

    float mediaEspera = 0;
    mediaEspera = (float)tempoTotal / n;
    printf("\nTempo de espera medio: %.2f u.t\n", mediaEspera);

    printf("\nDiagrama de gantt:\n");
    gantt(processos, n);
}
