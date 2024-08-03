#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 4

// função para encontrar uma página nos frames
int encontrarPagina(int *frames, int numFrames, int paginaAlvo) {
    for (int i = 0; i < numFrames; i++) {
        if (frames[i] == paginaAlvo) {
            return i; // página encontrada na posição i
        }
    }
    return -1; // página não encontrada nos frames
}

int fifopagefaults(int *sequenciaentrada, int numpaginas, int numframes) {
    int pagefaults = 0;
    int ponteiroframe = 0;

    int *frames = (int *)malloc(numframes * sizeof(int));

    // inicializa os frames com -1 (indicando que estão vazios)
    for (int i = 0; i < numframes; i++) {
        frames[i] = -1;
    }

    printf("\nentrada\t\t");
    for (int i = 0; i < numframes; i++) {
        printf("frame %d\t\t", i + 1);
    }
    printf("\n");

    for (int i = 0; i < numpaginas; i++) {
        int paginaatual = sequenciaentrada[i];

        // verifica se a página já está nos frames
        int indicepagina = encontrarPagina(frames, numframes, paginaatual);
        if (indicepagina == -1) {
            // se a página não estiver nos frames, ocorre um page fault
            pagefaults++;
            // substitui a página no frame apontado pelo ponteiroframe
            frames[ponteiroframe] = paginaatual;
            // atualiza o ponteiroframe para apontar para o próximo frame no próximo ciclo
            ponteiroframe = (ponteiroframe + 1) % numframes;
        }

        // imprime a entrada atual e o estado dos frames
        printf("%d\t\t", paginaatual);
        for (int j = 0; j < numframes; j++) {
            if (frames[j] != -1) {
                printf("  %d\t\t", frames[j]);
            } else {
                printf("  -\t\t");
            }
        }
        printf("\n");
    }

    free(frames);
    return pagefaults;
}

int main() {
    int numframes;
    printf("digite o numero de frames (3 ou 4): ");
    scanf("%d", &numframes);

    if (numframes != 3 && numframes != 4) {
        printf("numero de frames invalido. deve ser 3 ou 4.\n");
        return 1;
    }

    printf("digite as paginas separadas por espaco (insira -1 para encerrar): ");

    int tamanhopaginas = 10;  // tamanho inicial do array de páginas
    int *paginas = (int *)malloc(tamanhopaginas * sizeof(int));
    int quantidadepaginas = 0;
    int pagina;

    while (1) {
        scanf("%d", &pagina);
        if (pagina == -1) {
            break;
        }
        paginas[quantidadepaginas++] = pagina;
    }

    int pagefaults = fifopagefaults(paginas, quantidadepaginas, numframes);

    printf("\nTotal de Page Faults FIFO: %d\n", pagefaults);

    free(paginas);
    return 0;
}
