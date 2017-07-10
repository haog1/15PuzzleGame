/*
 hao, 692216
 Assignment 2, Data Structure and Algorithms
 Oct. 2015
 */

#include "ida.h"

int main(int argc, char **argv){
    
    int S0[SIZE][SIZE];
    
    S0[0][0] = readInput(argv[1], S0);
    
    processIDA(S0);
    
    return 0;
}


/* read input */
int readInput(char *input, int S[][SIZE]){
    
    int i = 0, j;
    FILE *fp = fopen(input,"r");
        
    if(fp == NULL){
        printf("READERROR\n");
        exit(EXIT_FAILURE);
    }
    
    while(i < SIZE){
        j = 0;
        while(j < SIZE){
            if(fscanf(fp,"%d", &S[i][j]) == 1){
                j += 1;
            }
        }
        i += 1;
    }
    
    fclose(fp);
    
    return S[0][0];
}