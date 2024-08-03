#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 4

int encontrarPaginaOtimo(int *sequenciaEntrada, int numPaginas, int *frames, int numFrames, int paginaIndex) {
    int index = -1;
    int farthest = -1;

    for (int i = 0; i < numFrames; i++) {
        int j;
        for (j = paginaIndex + 1; j < numPaginas; j++) {
            if (sequenciaEntrada[j] == frames[i]) {
                break;
            }
        }

        if (j == numPaginas) {
            return i; // se a página não for usada no futuro, escolhe esta página
        } else if (j > farthest) {
            farthest = j;
            index = i;
        }
    }

    return (index == -1) ? 0 : index;
}

int otimoPageFaults(int *sequenciaEntrada, int numPaginas, int numFrames) {
    int pageFaults = 0;

    int *frames = (int *)malloc(numFrames * sizeof(int));

    // inicializa os frames com -1 (indicando que estão vazios)
    for (int i = 0; i < numFrames; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < numPaginas; i++) {
        int paginaAtual = sequenciaEntrada[i];

        // verifica se a página já está nos frames
        int indicePagina = -1;
        for (int j = 0; j < numFrames; j++) {
            if (frames[j] == paginaAtual) {
                indicePagina = j;
                break;
            }
        }

        if (indicePagina == -1) {
            // se a página não estiver nos frames, ocorre um Page Fault
            pageFaults++;

            // sncontra o indice do frame que contém a página que não será usada pelo maior período de tempo no futuro
            int indiceSubstituir = encontrarPaginaOtimo(sequenciaEntrada, numPaginas, frames, numFrames, i);

            // substitui a página no frame
            frames[indiceSubstituir] = paginaAtual;
        }
    }

    free(frames);
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
            break; // encerra a entrada quando -1 é inserido
        }
        paginas[quantidadePaginas++] = pagina;
    }

    int pageFaults = otimoPageFaults(paginas, quantidadePaginas, numFrames);

    printf("\nTotal de Page Faults Otimo: %d\n", pageFaults);

    free(paginas);
    return 0;
}
