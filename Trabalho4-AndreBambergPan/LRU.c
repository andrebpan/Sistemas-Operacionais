#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 4

// função para encontrar uma página nos frames
int encontrarPagina(int *frames, int numFrames, int paginaAlvo) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == paginaAlvo) {
            return i; // pagina encontrada na posição i
        }
    }
    return -1; // pagina não encontrada nos frames
}

int lruPageFaults(int *sequenciaEntrada, int numPaginas, int numFrames) {
    int pageFaults = 0;

    int *frames = (int *)malloc(numFrames * sizeof(int));
    int *contadorLRU = (int *)malloc(numFrames * sizeof(int));

    // inicializa os frames e contadores com -1 (indicando que estão vazios)
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
        contadorLRU[i] = -1;
    }

    // loop sobre a sequência de páginas de entrada
    for (int i = 0; i < numPaginas; i++) {
        int paginaAtual = sequenciaEntrada[i];

        // verifica se a página já está nos frames
        int indicePagina = encontrarPagina(frames, numFrames, paginaAtual);

        if (indicePagina == -1) {
            // se a pagina não estiver nos frames, ocorre um Page Fault
            pageFaults++;

            // encontra o frame menos recentemente usado (LRU)
            int indiceLRU = 0;
            for (int j = 1; j < numFrames; j++) {
                if (contadorLRU[j] < contadorLRU[indiceLRU]) {
                    indiceLRU = j;
                }
            }

            // substitui a página no frame menos recentemente usado
            frames[indiceLRU] = paginaAtual;
            contadorLRU[indiceLRU] = i; // atualiza o contador para o índice atual
        } else {
            contadorLRU[indicePagina] = i;
        }
    }

    free(frames);
    free(contadorLRU);
    return pageFaults;
}

int main() {
    int numFrames;
    printf("Digite o numero de frames (3 ou 4): ");
    scanf("%d", &numFrames);

    if (numFrames != 3 && numFrames != 4) {
        printf("Numero de frames invalido. Deve ser 3 ou 4.\n");
        return 1; 
    }

    printf("Digite as paginas separadas por espaco (insira -1 para encerrar): ");

    int tamanhoPaginas = 10;  // tamanho inicial do array de páginas
    int *paginas = (int *)malloc(tamanhoPaginas * sizeof(int));
    int quantidadePaginas = 0;
    int pagina;

    while (1) {
        scanf("%d", &pagina);
        if (pagina == -1) {
            break; // Encerra a entrada quando -1 é inserido
        }
        paginas[quantidadePaginas++] = pagina;
    }

    int pageFaults = lruPageFaults(paginas, quantidadePaginas, numFrames);

    printf("\nTotal de Page Faults LRU: %d\n", pageFaults);

    free(paginas);
    return 0;
}
