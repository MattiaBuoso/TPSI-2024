#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>

#define DIM 5

int main()
{
    int num[DIM];
    int i;

    mkfifo("sum", 0777);

    for(i = 0; i< DIM; i++){
        num[i] = rand() %100;
        printf("num: %d", num[i]);
    }

    int fd = open("sum", O_WRONLY);
    if(fd == -1){
        printf("errore durante la crazione della pipe");
        exit(EXIT_FAILURE);
    }

    write(fd,num, sizeof(int) == 1);
    
}