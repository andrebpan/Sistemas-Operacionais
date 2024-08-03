#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int id;   
    int tempoCPU;
    int tempo_espera;  
} Processo;

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
    int n, i;

    printf("Informe o numero de processos: ");
    scanf("%d", &n);

    Processo *processos = (Processo *)malloc(sizeof(Processo) * n);

    for (i = 0; i < n; i++) 
    {
        processos[i].id = i;
        printf("Informe o tempo de execucao do P%d: ", i);
        scanf("%d", &processos[i].tempoCPU);
        processos[i].tempo_espera = 0;
    }

    int tempo_atual = 0;
    int tempo_total=0;
    
    printf("\nProcesso          Tempo de CPU            Tempo de espera\n");
    
    for (i = 0; i < n; i++) 
    {
        processos[i].tempo_espera = tempo_atual;
        tempo_atual += processos[i].tempoCPU;
        tempo_total += processos[i].tempo_espera;

        printf("P%d\t\t\t %d\t\t\t %d\n", processos[i].id,processos[i].tempoCPU, processos[i].tempo_espera);
    }

    float mediaEspera=0;
    mediaEspera = (float)tempo_total /n;

    printf("\nTempo de espera medio: %.1f u.t\n", mediaEspera);
    
    printf("\nDiagrama de gantt:\n");
    gantt(processos, n);
}
