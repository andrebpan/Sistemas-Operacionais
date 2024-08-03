#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int id;
    int tempoCPU;
    int tempo_espera;
} Processo;

//comparar por tempo
int comparar(const void *a, const void *b) 
{
    return ((Processo*)a)->tempoCPU - ((Processo*)b)->tempoCPU;
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
        printf("Informe o tempo de execucao do Processo P%d: ", i);
        scanf("%d", &processos[i].tempoCPU);
        processos[i].tempo_espera=0;
    }

    qsort(processos, n, sizeof(Processo), comparar);

    int tempoTotal = 0;
    int tempoAtual = 0;

    for (int i = 0; i < n; i++) 
    {
        tempoTotal += tempoAtual;
        tempoAtual += processos[i].tempoCPU;

        for (int j = i + 1; j <n; j++)
        {
            processos[j].tempo_espera += processos[i].tempoCPU;
        }

    }

    printf("\nProcesso	Tempo de CPU	 Tempo de espera\n");
    for(int i=0; i<n; i++)
    {
      printf("P%d\t\t    %d\t\t       %d\n", processos[i].id, processos[i].tempoCPU, processos[i].tempo_espera);
    }

    float mediaEspera = 0.0;
    mediaEspera = (float)tempoTotal / n;
    printf("\nTempo de espera medio: %.2f u.t\n", mediaEspera);

    printf("\nDiagrama de gantt:\n");
    gantt(processos, n);
}
