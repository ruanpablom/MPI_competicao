#include<stdio.h>
#include<mpi.h>
//#include"senha3.h"
#include<stdlib.h>
#include<string.h>

//Global variables
int MAQ = 26;
int P_T = 10;
int D_T = 64;
int nCRACK = 30;
char d[] = "./abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

//Functions
char *senha_pos(int P_T, char *i_pass, unsigned long int salt, int MAQ, int D_T);
long unsigned int lpow(long unsigned int base, int expoente);
char **initPassInits(char *initP,char **initsV,unsigned long int qtPasss, int procss, int P_T, int D_T);
void crack(char *initPa, char **pCrackL, char **saltL, int P_T, int D_T,int qtPCRACK);

int main(int argc, char **argv){
    int rank,size,i;
    char **inits;
    char initPASS[]="..........";
    long unsigned int qtPASS = lpow(D_T,P_T);
    MPI_Status status;
    MPI_Request *request;
    FILE *file;
    char **pCrackL;
    char **saltL;
    char *dadoSalt;
    char *dadoP;


    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size); 

    request=(MPI_Request*)malloc((3*size+3)*sizeof(MPI_Request));
    if(request==NULL)exit(0);
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

    inits =(char**)malloc(size-1*sizeof(char*));
    if(inits==NULL) exit(0);
    for(i=0;i<size;i++){
        inits[i]=(char*)malloc((P_T+1)*sizeof(char));
    }

    inits = initPassInits(initPASS,inits,qtPASS, size-1, P_T, D_T);

    if(rank == 0){
        file = fopen("input.in","r");
        for(i=0;i<nCRACK;i++){
            fscanf(file,"%s",pCrackL[i]);
            memcpy(saltL[i],pCrackL[i],sizeof(char)*3);
            saltL[i][2]='\0';
        }
        fclose(file); 

        for(i=1;i<size-1;i++){
            //MPI_Isend(&inits[i],P_T,MPI_CHAR,i,0,MPI_COMM_WORLD,&request[3*i+1]);
            MPI_Isend(&pCrackL,14*nCRACK,MPI_CHAR,i,0,MPI_COMM_WORLD,&request[3*i+2]);
            MPI_Isend(&saltL,3*nCRACK,MPI_CHAR,i,0,MPI_COMM_WORLD,&request[3*i+3]);
        }

    }else{
        //MPI_Irecv(&inits[rank],P_T,MPI_CHAR,0,0,MPI_COMM_WORLD,&request[3*rank+1]);
        MPI_Irecv(&pCrackL,14*nCRACK,MPI_CHAR,0,0,MPI_COMM_WORLD,&request[3*rank+2]);
        MPI_Irecv(&saltL,3*nCRACK,MPI_CHAR,0,0,MPI_COMM_WORLD,&request[3*rank+3]);
        crack(inits[rank],pCrackL,saltL,P_T,D_T,nCRACK);
        //for(i=0;i<nCRACK;i++){
        //  printf("%s %s\n",pCrackL[i],saltL[i]);
        //}
        //printf("%s %i\n",inits[rank-1],rank);
    }

    MPI_Finalize();
    return 0;
}

long unsigned int lpow(long unsigned int base, int expoente){
    int i;
    long unsigned int result=1;
    for(i=0;i<expoente;i++){
        result*=base;
    }
    return result;
}

char *senha_pos(int P_T, char *i_pass, unsigned long int salt, int MAQ, int D_T){
    int j=0,k=0;
    int pass[P_T];
    int pos;
    int aux;
    char *c_pass;
    unsigned long int dtDiv = 0;


    c_pass = (char*)malloc((P_T+1)*sizeof(char));
    if(c_pass==NULL) exit(0);
    memcpy(c_pass,i_pass,sizeof(char)*(P_T+1));

    for(j=0;j<P_T;j++){
        for(k=0;k<D_T;k++){
            if(c_pass[j]==d[k]){
                pass[j] = k;
                break;
            }
        }
    }

    while(salt > D_T){
        aux = 1;
        pos = P_T-1;
        dtDiv = salt/D_T;

        while(aux<=P_T){ 
            if(dtDiv > lpow(D_T,aux)){
                pos--;
                aux++;
            }
            else break;
        }
        pass[pos-1]++;
        salt-=lpow(D_T,aux);
    }

    pass[P_T-1] += salt-1;

    for(j=P_T-1;j>0;j--){
        if(pass[j] > (D_T-1)){
            pass[j]-=D_T;
            pass[j-1]++;
        }
    }
    for(j=0;j<P_T;j++)c_pass[j] = d[pass[j]];

    return c_pass;
}

char **initPassInits(char *initP, char **initsV, long unsigned int qtPasss, int nProcs, int P_T, int D_T){
    int i;
    long unsigned int sa = qtPasss/nProcs;
    char *dados;

    dados = (char*)malloc(nProcs*sizeof(char)*(P_T+1));
    if(dados==NULL) exit(0);
    initsV = (char**)malloc(nProcs*sizeof(char*));
    if(initsV==NULL) exit(0);
    for(i=0;i<nProcs;i++) initsV[i] = &dados[i*(P_T+1)];

    memcpy(initsV[0],initP,sizeof(char)*(P_T+1));
    initsV[P_T]='\0';

    for(i=1;i<nProcs-1;i++){
        memcpy(initsV[i],senha_pos(P_T, initsV[i-1], sa, nProcs, D_T),sizeof(char)*(P_T+1));
    } 
    memcpy(initsV[nProcs-1], senha_pos(P_T, initsV[nProcs-2],qtPasss-(sa*(nProcs-1)), nProcs, D_T),sizeof(char)*(P_T+1));

    return initsV;
}

void crack(char *initPa, char **pCrackL, char **saltL, int P_T, int D_T,int qtPCRACK){
    int pass[P_T];
    char c_pass[P_T];
    int j,ok=1,k,h,q=0;
    char *result;

    memcpy(c_pass,initPa,sizeof(char)*P_T+1);
    if(c_pass==NULL) exit(0);
    for(j=0;j<P_T;j++){
        for(k=0;k<D_T;k++){
            if(c_pass[j]==d[k]){
                pass[j] = k;
                break;
            }
        }
    }
    
    //for(j=0;j<qtPCRACK;j++)printf("%s\n",saltL[j]);

    j=0;
    while(j!=-1){    
        if(q==qtPCRACK)break;
        for(j = pass[P_T-1] ; j < D_T ; j++){ 
            pass[P_T-1] = j;
            c_pass[P_T-1] = d[j];
            for(k = P_T-1 ; k>=0 ; k--){
                for(h = 0 ; h < qtPCRACK ; h++){
                    if(saltL[h][0]!='\0'){ 
                            result = crypt(&c_pass[k], saltL[h]); 
                            //printf("%s %s\n",result,pCrackL[h]);
                            ok = strcmp(result,pCrackL[h]);
                        if(!ok){
                            printf("%s %s\n",result,pCrackL[h]);
                            ok=1;
                            saltL[h][0]='\0';
                            q++;
                            printf("A %iª senha é:  %s\n",h+1,&c_pass[k]);
                            if(q==qtPCRACK)break;
                        }
                    }
                }
                if(q==qtPCRACK)break;
            }
            if(q==qtPCRACK)break;
        }
        pass[P_T-1]=0;
        c_pass[P_T-1] = d[0];
        for(j = P_T-2 ; j>=0 ; j--){
            if(pass[j] <D_T-1){
                pass[j]++;
                c_pass[j]=d[pass[j]];
                break;
            }else{
                pass[j] = 0;
                c_pass[j] = d[0];
                continue;
            }
        }
    }
}


