#define _GNU_SOURCE
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"senha4.h"
#include<crypt.h>

#define T_DES 13
#define T_S 2
#define T_D 64

//Global variables
char d[] = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
int tP;

/*char *passwsToCrack(char *fileName,int qtWords, char *dados){
    char **result;
    //char *dados;
    FILE *file;
    int i;

    dados = (char*)malloc(qtWords*(T_DES+1)*sizeof(char));
    if(dados==NULL)exit(0);
    //result = (char**)malloc(sizeof(char*)*qtWords);
    //if(result==NULL)exit(0);
    //for(i=0;i<qtWords;i++)result[i] = &dados[i*(T_DES+1)];

    file = fopen(fileName,"r");
    i=0;
    while((fscanf(file,"%s",result[i*(T_DES+1)]))){
        i++;
        //result[i][T_DES]='\0';
    }

    return dados;
}*/

/*char *saltsForPassws(char *passws, int qtPassws){
    char **result;
    char *dados;
    int i;

    dados = (char*)malloc(qtPassws*(T_S+1)*sizeof(char));
    if(dados==NULL)exit(0);
    result = (char**)malloc(sizeof(char*)*qtPassws);
    if(result==NULL)exit(0);
    for(i=0;i<qtPassws;i++){
        result[i] = &dados[i*(T_S+1)];
        //memcpy(result[i],passws[i],sizeof(char)*T_S);
        result[i][T_S]='\0';
    }

    return dados; 
}*/

PassSlice *sliceAlloc(int nprocs){
    PassSlice *result; 
    result = (PassSlice*)malloc(nprocs*sizeof(PassSlice));
    if(result==NULL)exit(0); 

    return result;
}

void freeSlice(int nprocs, PassSlice *slices){
	int i;
	for(i=0;i<nprocs;i++){
		free(slices[i].begin);
		free(slices[i].end);
		free(slices[i]);
	}
}

PassSlice *initSlices(int nprocs,char *begin){
    char *beg;
    PassSlice *result; 
    long unsigned int qtTGen = lpow(T_D,tP);
    unsigned long int interv = qtTGen/nprocs;
    unsigned long int intervL= qtTGen - ((nprocs-1)*interv);
    int i;

    result = sliceAlloc(nprocs);

    beg = (char*)malloc((tP+1)*sizeof(char));
    if(beg==NULL)exit(0);
    beg[tP]='\0';
    memcpy(beg,beegin,sizeof(char)*(tP+1));

    result[0].interval = interv;
    result[0].tPass    = tP; 
    result[0].begin    = beg;
    result[0].end      = senha_pos(result[0].begin,result[0].interval);
    for(i=1;i<nprocs-1;i++){
        result[i].interval = interv;
        result[i].tPass    = tP;
        result[i].begin = (char*)malloc((result[i].tPass+1)*sizeof(char));
        if(result[i].begin==NULL)exit(0);
        memcpy(result[i].begin, senha_pos(result[i-1].end,2), sizeof(char)*(result[i].tPass+1));
        result[i].end      = senha_pos(result[i].begin,result[i].interval); 
    }
    result[i].interval = intervL;
    result[i].tPass    = tP;
    result[i].begin = (char*)malloc((result[i].tPass+1)*sizeof(char));
    if(result[i].begin==NULL)exit(0);
    memcpy(result[i].begin, senha_pos(result[i-1].end,2), sizeof(char)*(result[i].tPass+1));
    result[i].end      = senha_pos(result[i].begin,result[i].interval); 


    return result;
}

char *senha_pos(char *i_pass, unsigned long int interv){
    int j=0,k=0;
    int pass[tP];
    int pos;
    int aux2;
    int aux;
    char *c_pass;
    unsigned long int dtDiv = 0, salt_aux;

    c_pass = (char*)malloc((tP+1)*sizeof(char));
    if(c_pass==NULL) exit(0);
    memcpy(c_pass,i_pass,sizeof(char)*(tP+1));

    for(j=0;j<tP;j++){
        for(k=0;k<T_D;k++){
            if(c_pass[j]==d[k]){
                pass[j] = k;
                break;
            }
        }
    } 
    while(interv > T_D){
        aux = 1;
        pos = tP-1;
        dtDiv = interv/T_D;

        while(aux<=tP){ 
            if(dtDiv > lpow(T_D,aux)){
                pos--;
                aux++;
            }
            else break;
        }
        pass[pos-1]++;
        interv-=lpow(T_D,aux);
    }
    pass[tP-1] += interv-1;

    for(j=tP-1;j>0;j--){
        if(pass[j] > (T_D-1)){
            pass[j]-=T_D;
            pass[j-1]++;
        }
    }
    for(j=0;j<tP;j++)c_pass[j] = d[pass[j]];

    return c_pass;
}

long unsigned int lpow(long unsigned int base, int expoente){
    int i;
    long unsigned int result=1;
    for(i=0;i<expoente;i++){
        result*=base;
    }
    return result;
}

int setTp(int TP){
    tP = TP;
    if(tP==0){
        printf("Tamanho da senha deve ser maior que \"0\"!\n");
        return 0;
    }
    return 1;
}

int crack(char *initPa, char **pCrackL, char **saltL, int qtPCRACK, int intervalo){
    int pass[tP];
    char c_pass[tP];
    int j,ok=1,k,h,q=0;
    char *result;
    unsigned long int qtPGen = 0;

    memcpy(c_pass,initPa,sizeof(char)*tP);
    if(c_pass==NULL) exit(0); 
    for(j=0;j<tP;j++){
        for(k=0;k<T_D;k++){
            if(c_pass[j]==d[k]){
                pass[j] = k;
                break;
            }
        }
    }

    j=0;
    struct crypt_data data;
    data.initialized = 0; 
    while(j!=-1){
        if(q==qtPCRACK)return 1;
        for(j = pass[tP-1] ; j < T_D && qtPGen<intervalo ; j++){
            qtPGen++;
            pass[tP-1] = j;
            c_pass[tP-1] = d[j]; 
            //printf("%s\n",c_pass);
            for(h = 0 ; h < qtPCRACK ; h++){
                if(saltL[h][0]!='\0'){ 
                    result = crypt_r(&c_pass[k], saltL[h],&data); 
                    ok = strcmp(result,pCrackL[h]);
                    if(!ok){
                        //printf("%s %s\n",result,pCrackL[h]);
                        ok=1;
                        saltL[h][0]='\0';
                        q++;
                        printf("A %iª senha é:  %s\n",h+1,&c_pass[k]);
                        if(q==qtPCRACK)return 1;
                    }
                }
            }
        }
        if(qtPGen>=intervalo)return 2;
        pass[tP-1]=0;
        c_pass[tP-1] = d[0];
        for(j = tP-2 ; j>=0 ; j--){
            if(pass[j] <T_D-1){
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
    return 0;
}

int openMP(char **passwdsTC, char **saltFP, int qtPTC){
    //char **passwdsTC;
    //char **saltFP;
    char *str;
    //int qtPTC;
    int nProcs = omp_get_num_procs();
    PassSlice *slices;
    int i;

   /* if(argv[1]==NULL){
        printf("File name omitted!");
        exit(1);
    }
    if(argv[2]==NULL){
        printf("Number of Passwords omitted!");
        exit(1);
    }

    str = argv[1];

    qtPTC = atoi(argv[2]);
    */
    //if(setTp(3)==0)exit(1);
    slices = initSlices(nProcs);
    //passwdsTC = passwsToCrack(str,qtPTC);
    //saltFP = saltsForPassws(passwdsTC, qtPTC);
    
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

int getTDes(){
    return T_DES;
}

int getTS(){
    return T_S;
}

int getTP(){
	return tP;
}

void setTP(int TP){
	tP = TP;
}
