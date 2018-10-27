// Carson Tyler
// 09.23.2018
// CS 3100
// Assignment 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <math.h>

int main(int argc, char * argv[])
{
    int min, max;
    const char * filename=argv[1];
    FILE * ft= fopen(filename, "rb") ;
    if (ft) {
        fseek (ft,0,SEEK_END); //go to end of file
        long size = ftell(ft); //what byte in file am I at?
        fseek (ft,0,SEEK_SET); //go to beginning of file
        float num = size / sizeof(int);
        int i;
        fseek(ft,0,SEEK_SET);
        // If there are no arguments passed in (if there's one process)
        if (argc == 2) {
            for( i = 0; i < num; i++) {
                int temp = 0;
                fread(&temp,sizeof(int),1,ft);
                if (i == 0) {
                    max = temp;
                    min = temp;
                }
                if (temp > max)
                    max = temp;
                else if (temp < min)
                    min = temp;
            }
            printf("%d\n%d\n",min,max);
        }
        // If there are arguments (if there are four processes)
        else if (argc == 3) {
            float startP = (num/4 * strtol((argv[1]),NULL,10));
            float endP = (startP + num/4);
            startP = floor(startP);
            endP = floor(endP);
            fseek(ft,startP*sizeof(int),SEEK_SET);
            for(i = startP; i < (startP + num/4); i++) {
                int temp = 0;
                fread(&temp, sizeof(int), 1, ft);
                if(i == startP) {
                    max = temp;
                    min = temp;
                }
                if(temp > max) 
                    max = temp;
                else if(temp < min)
                    min = temp;
            }
            printf("%d\n%d\n",min,max);
        }
        fclose( ft ) ;
    }
    return 0;
}
