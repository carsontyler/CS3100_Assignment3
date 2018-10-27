// Carson Tyler
// 09.23.2018
// CS 3100
// Assignment 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main (int argc, char* argv[]) {

    int pid1, pid2, pid3, i, min, max, index, j;
    i = 0;
    j = 0;
    index = 0;
    int cp[2];
    char ch;
    char buf[12];
    clock_t beginC = clock();
    
    printf("Carson Tyler\n\n");

    if(argc != 3) {
        printf("ERROR: 3 arguments must be passed in\n");
        return 0;
    }
    char* filename = argv[2];
    switch(strtol(argv[1],NULL,10)) {
        case 1:
            if (pipe(cp) < 0)
            {
                printf("didn't work, couldn't not establish pipe.\n");
                return -1;
            }
            pid1 = fork();
            if (pid1 == 0) {
                close(1);
                dup2(cp[1],1);
                close(0);
                close(cp[0]);
                execl("read","read",filename,(char*) 0);
            }
            break;
        case 4:
            if (pipe(cp) < 0)
            {
                printf("didn't work, couldn't not establish pipe.\n");
                return -1;
            }
            pid1 = fork();
            pid2 = fork();

            if(pid1 == 0 && pid2 == 0) {
                close(1);
                dup2(cp[1],1);
                close(0);
                close(cp[0]);
                pid3 = fork();
                if(pid3 == 0)
                    execl("read","read",filename,"0",(char*) 0);

                else
                    execl("read","read",filename,"3",(char*) 0);
            }

            if(pid1 == 0 && pid2 != 0) { 
                close(1);
                dup2(cp[1],1);
                close(0);
                close(cp[0]);
                execl("read","read",filename,"1",(char*) 0);
            }
            if(pid1 != 0 && pid2 == 0) {
                close(1);
                dup2(cp[1],1);
                close(0);
                close(cp[0]);
                execl("read","read",filename,"2",(char*) 0);
            }
            break;
        default:
            printf("ERROR: Must pass in a 1 or 4\n");
            return -1;
    }
    close(cp[1]);

    for(j = 0; j < 12; j++)
        buf[j] = 0;

    while( read(cp[0], &ch, 1) == 1) {
        if (ch == '\n') {
            int temp = atoi(buf); 
            if (i == 0) {
                max = temp;
                min = temp;
            }
            if (temp > max)
                max = temp;
            else if (temp < min)
                min = temp;
            i++;
            for(j = 0; j <= index; j++)
                buf[j] = 0;
            index = 0;
        }
        else {
            buf[index++] = ch;
        }
    }
    printf("MIN: %i; MAX: %i\n", min, max);

    clock_t endC = clock();
    double time_spent = (double)(endC - beginC) / CLOCKS_PER_SEC;
    printf("Time: %f\n", time_spent);
    return 0;
}
