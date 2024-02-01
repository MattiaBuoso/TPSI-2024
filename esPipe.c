#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NUM_NUMERI 5

int main() {
    pid_t pid;
    int pipefd[2];
    int numeri[NUM_NUMERI];
    int i, moltiplicatore;

    // Crea la pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Genera il processo figlio
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Processo figlio
        close(pipefd[0]); // Chiude il lato di lettura della pipe nel figlio

        // Chiede all'utente di inserire cinque numeri
        printf("Inserisci cinque numeri:\n");
        for (i = 0; i < NUM_NUMERI; i++) {
            scanf("%d", &numeri[i]);
        }

        // Invia l'array di numeri al processo padre tramite la pipe
        write(pipefd[1], numeri, sizeof(numeri));
        close(pipefd[1]); // Chiude il lato di scrittura della pipe nel figlio

        exit(EXIT_SUCCESS);
    } else { // Processo padre
        close(pipefd[1]); // Chiude il lato di scrittura della pipe nel padre

        // Attende che l'utente inserisca i numeri prima di procedere
        wait(NULL);

        // Chiede all'utente il moltiplicatore
        printf("Inserisci il moltiplicatore: ");
        scanf("%d", &moltiplicatore);

        // Legge i numeri inviati dal figlio attraverso la pipe e li stampa moltiplicati per il moltiplicatore
        printf("Numeri ricevuti e moltiplicati:\n");
        read(pipefd[0], numeri, sizeof(numeri));
        for (i = 0; i < NUM_NUMERI; i++) {
            printf("%d ", numeri[i] * moltiplicatore);
        }
        printf("\n");

        close(pipefd[0]); // Chiude il lato di lettura della pipe nel padre

        exit(EXIT_SUCCESS);
    }

    return 0;
}
