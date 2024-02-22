#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#define NUM_NUMERI 5

int main()
{

    if (mkfifo("myFIFO", 0777) == -1)
    {
        printf("Errore durante la crazioen della FIFO");
        return 1;
    }

    int fd = open("myFIFO", O_WRONLY);
    printf("Ho aperto la FIFO\n");

    int x = 90;

    if (write(fd, &x, sizeof(int)) == -1)
    {
        printf("Errore durante la scrittura");
        return 2;
    }

    printf("Ho scritto nella FIFO");

    close(fd);
    
    return 0;
}
