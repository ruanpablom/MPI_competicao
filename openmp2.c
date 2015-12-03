#include<stdio.h>
#include<omp.h>
#include<string.h>
#include"senha4.h"
#include<stdlib.h>

int main(int argc, char **argv){
    char **passwdsTC;
    char **saltFP;
    char *str;
    int qtPTC;
    int nProcs = omp_get_num_procs();
    PassSlice *slices;
    int i;

    if(argv[1]==NULL){
        printf("File name omitted!");
        exit(1);
    }
    if(argv[2]==NULL){
        printf("Number of Passwords omitted!");
        exit(1);
    }

    str = argv[1];

    qtPTC = atoi(argv[2]);

    if(setTp(3)==0)exit(1);
    slices = initSlices(nProcs);
    passwdsTC = passwsToCrack(str,qtPTC);
    saltFP = saltsForPassws(passwdsTC, qtPTC);
    
    #pragma omp parallel shared(slices, qtPTC, saltFP, passwdsTC) private(i)
    {    
    #pragma omp for
        for(i=0;i<nProcs;i++){
            crack(slices[i].begin,passwdsTC, saltFP, qtPTC, slices[i].interval);
        }
    }
    //crack(initials[0],pCrackL,saltL,P_T,D_T,nCRACK);
    return 0;
}
