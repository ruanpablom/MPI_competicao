#include<stdio.h>
#include<omp.h>
#include<string.h>
#include"senha3.h"
#include<stdlib.h>

int main(){
    long unsigned int qtPass = lpow(D_T,P_T);
    long unsigned int sa;
    char pInitial[] = "..........";
    //char initials[omp_get_num_procs()][P_T+1];
    char **initials;
    int procss = omp_get_num_procs();
    int i;
    FILE *file;
    char **pCrackL;
    char **saltL;
    char *dadoSalt;
    char *dadoP;
    
    dadoSalt = (char*)malloc(sizeof(char)*nCRACK*3);
    if(dadoSalt==NULL)exit(0);
    saltL = (char**)malloc(nCRACK*sizeof(char*));
    if(saltL==NULL) exit(0);
    for(i=0;i<nCRACK;i++)saltL[i] = &dadoSalt[i*3]; 
    dadoP = (char*)malloc(sizeof(char)*nCRACK*14);
    if(dadoP==NULL)exit(0);
    pCrackL = (char**)malloc(nCRACK*sizeof(char*));
    if(pCrackL==NULL) exit(0);
    for(i=0;i<nCRACK;i++)pCrackL[i] = &dadoP[i*14];

    file = fopen("input.in","r");
    for(i=0;i<nCRACK;i++){
        fscanf(file,"%s",pCrackL[i]);
        //pCrackL[i][]='\0';
        memcpy(saltL[i],pCrackL[i],sizeof(char)*3);
        saltL[i][2]='\0';
    }
    fclose(file);

    initials = initPassInits(pInitial,initials,qtPass,procss,P_T,D_T);  
        
    //#pragma omp parallel shared(initials,nCRACK,saltL,pCrackL,P_T,D_T) private(i)
    //{   
        //#pragma omp for
            for(i=0;i<procss;i++){
                crack(initials[i],pCrackL,saltL,P_T,D_T,nCRACK);
                //printf("teste\n");
            }
    //}
    //crack(initials[0],pCrackL,saltL,P_T,D_T,nCRACK);
    return 0;
}
