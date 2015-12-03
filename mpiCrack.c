#define _GNU_SOURCE
#include<unistd.h>
#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<string.h>
#include"senha4.h"

#define T_M 10

int main(int argc, char **argv){
    int rank,size,i,j;
    MPI_Status status;
    MPI_Request *request;
    char **pCrackL;
    char *dados;
    char *dadosS;
    char **saltL;
    PassSlice *slices;
    char fileName[] = "input.in";
    int qtPTC;
    char *t;
    FILE *file;
    char src[14];
    MPI_File fh;
    int filesize;
    //I_MPI_MT_MEMCPY=1;
    //int tDes = getDes();

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size); 

    qtPTC = atoi(argv[1]);

    dados = (char*)malloc(qtPTC*(getTDes()+1)*sizeof(char));
    if(dados==NULL)exit(0);

    

    //pCrackL=(char*)malloc(qtPTC*getTDes()*sizeof(char));
    //saltL=(char*)malloc(qtPTC*getTS()*sizeof(char));


    if(rank == 0){
        MPI_File_open(MPI_COMM_WORLD, fileName, MPI_MODE_RDWR, &fh );
        MPI_File_get_size(fh, &filesize);
        printf("%i\n",filesize);
        // if(argv[1]==NULL)exit(0); 
        //t = &pCrackL[0][0];
        //saltL = saltsForPassws(pCrackL,qtPTC);

        /*for(i = 1 ; i < T_M ; i++){
          slice = initSlices(size-1);
          for(j=1;j<size;j++){

          }
          }*/
    }
    //pCrackL=(char*)malloc(qtPTC*getTDes()*sizeof(char));
    //MPI_Bcast (&qtPTC, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast (dados, qtPTC*(getTDes()+1), MPI_CHAR, 0, MPI_COMM_WORLD);
    //for(i=0;i<qtPTC;i++)pCrackL[i] = &dados[i*(getTDes()+1)];
    //MPI_Bcast (saltL, qtPTC*getTS(), MPI_CHAR, 0, MPI_COMM_WORLD);
    //for(i = 0 ; i < qtPTC ; i++){
      //  printf("%i %i %s\n",qtPTC,rank,&dados[i]);
    //}
    //printf("%s\n",pCrackL[0]);
    //setTp(1);
    //openMP(pCrackL, saltL, qtPTC);

    MPI_Finalize();
    return 0;
}


