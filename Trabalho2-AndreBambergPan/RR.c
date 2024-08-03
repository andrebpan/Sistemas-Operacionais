#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int id;
    int tempoCPU;
    int tempo_espera;
} Processo;

void RR(Processo *processos, int n, int quantum) 
{
    int tempo_restante[n];
    int tempoAtual = 0;
    int proc_concluido = 0;
 
    for (int i = 0; i < n; i++) 
    {
        tempo_restante[i] = processos[i].tempoCPU;
        processos[i].tempo_espera = 0;
    }

    while (proc_concluido < n) 
    {
        for (int i = 0; i < n; i++) 
        {
            if (tempo_restante[i] > 0) 
            {
                int tempo_exec = (tempo_restante[i] < quantum) ? tempo_restante[i] : quantum;
                tempo_restante[i] -= tempo_exec;
                tempoAtual += tempo_exec;

                printf("\nexecutando p%d\n",i);

                for (int j = 0; j < n; j++) 
                {
                    if (j != i && tempo_restante[j] > 0) 
                    {
                        processos[j].tempo_espera += tempo_exec;
                    }
                }

                if (tempo_restante[i] == 0) 
                {
                    proc_concluido++;
                }
            }
        }
    }
}

int main(void) 
{
    int n, quantum;

    printf("Informe o numero de processos: ");
    scanf("%d", &n);

    printf("Informe o tempo quantum: ");
    scanf("%d", &quantum);

    Processo *processos = (Processo *)malloc(sizeof(Processo) * n);

    for (int i = 0; i < n; i++) 
    {
        processos[i].id = i;
        printf("Informe o tempo de execucao do P%d: ", i);
        scanf("%d", &processos[i].tempoCPU);
    }

    RR(processos, n, quantum);

    printf("\nProcesso\t Unidade de tempo\t Tempo de espera\n");
    for(int i = 0; i < n; i++)
    {
        printf("P%d\t\t\t%d\t\t\t%d\n",processos[i].id,processos[i].tempoCPU,processos[i].tempo_espera);
    }

    float esperaTotal = 0;
    for (int i = 0; i < n; i++) 
    {
        esperaTotal += processos[i].tempo_espera;
    }
    float mediaEspera = 0.0;
    mediaEspera = esperaTotal / n;
    printf("\nTempo de espera medio: %.1f",mediaEspera);
    printf("\n");

}
