#include <stdio.h>
#include <omp.h>
#include <unistd.h> // Para a função sleep

int saldo = 100;
omp_lock_t lock;

void sacar(int valor) {
    omp_set_lock(&lock);

    printf("Thread %d: Realizando saque de %d\n", omp_get_thread_num(), valor);

    if (saldo >= valor) {
        saldo -= valor;
    }

    printf("Thread %d: Saldo após saque: %d\n", omp_get_thread_num(), saldo);

    omp_unset_lock(&lock);

    // Pausa por 1 segundo para simular processamento
    sleep(2);
}

void depositar(int valor) {
    omp_set_lock(&lock);

    printf("Thread %d: Realizando depósito de %d\n", omp_get_thread_num(), valor);

    saldo += valor;

    printf("Thread %d: Saldo após depósito: %d\n", omp_get_thread_num(), saldo);

    omp_unset_lock(&lock);

    // Pausa por 1 segundo para simular processamento
    sleep(2);
}

int main() {
    omp_init_lock(&lock);

    int max_threads = omp_get_max_threads();
    printf("\nNúmero máximo de threads disponíveis: %d\n\n", max_threads);

    // Define o número de threads
    omp_set_num_threads(max_threads);

    #pragma omp parallel
    {
        // Cada thread realiza operações de saque e depósito
        sacar(10);
        depositar(5);
    }

    printf("Saldo final: %d\n", saldo);

    omp_destroy_lock(&lock);

    return 0;
}
